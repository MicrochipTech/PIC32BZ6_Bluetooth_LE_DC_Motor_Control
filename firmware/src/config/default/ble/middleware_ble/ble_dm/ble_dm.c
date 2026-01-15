/*******************************************************************************
* Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

/*******************************************************************************
  BLE Device Manager Middleware Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm.c

  Summary:
    Implements the BLE Device Manager's core functionalities and event handling.

  Description:
    This source file provides the implementation of the BLE Device Manager's core
    functionalities and event handling mechanisms for the application user. The
    'BLE_DM_Init' function must be invoked within the 'APP_Initialize' function
    to properly initialize this module within the system.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "ble_dm.h"
#include "ble_dm_sm.h"
#include "ble_dm_info.h"
#include "ble_dm_dds.h"
#include "ble_dm_conn.h"
#include "ble_dm_internal.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

BLE_DM_EventCb_T         g_dmEventCb[BLE_DM_MAX_REGISTER_NUM];              // Aarray of callback functions for BLE DM events.
uint8_t                  g_dmCbNum;                                         // Counter for the number of registered DM callbacks.

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************
/**
 * @brief Conveys a BLE Device Manager event to all registered callbacks.
 * 
 * @param[in] p_event Pointer to the BLE_DM_Event_T structure containing event data.
 */
void BLE_DM_ConveyEvent(BLE_DM_Event_T *p_event)
{
    uint8_t             i;
    BLE_DM_InfoConn_T   *p_conn;

    p_conn = BLE_DM_InfoGetConnByHandle(p_event->connHandle);

    if (p_conn != NULL)
    {
        p_event->peerDevId = p_conn->devId;
    }
    else
    {
        p_event->peerDevId = BLE_DM_PEER_DEV_ID_INVALID;
    }

    for(i=0;i<g_dmCbNum; i++)
    {
        if(g_dmEventCb[i]!=NULL)
        {
            g_dmEventCb[i](p_event);
        }
    }
}

/**
 * @brief Initializes the BLE Device Manager module.
 * 
 * @retval true if initialization was successful, false otherwise.
 */
bool BLE_DM_Init(void)
{
    BLE_DM_DdsInit(BLE_DM_SmWriteCompleteCallback);
    BLE_DM_SmInit();
    
    if (BLE_DM_InfoInit() == false)
    {
        return false;
    }            
    
    return BLE_DM_ConnInit();
}

/**
 * @brief Registers a callback for BLE Device Manager events.
 * 
 * @param[in] eventCb       The callback function to register.
 * 
 * @retval MBA_RES_SUCCESS on success.
 * @retval MBA_RES_NO_RESOURCE if the callback list is full.
 */
uint16_t BLE_DM_EventRegister(BLE_DM_EventCb_T eventCb)
{
    if(g_dmCbNum>=BLE_DM_MAX_REGISTER_NUM)
    {
        return MBA_RES_NO_RESOURCE;
    }

    g_dmEventCb[g_dmCbNum]=eventCb;
    g_dmCbNum++;

    return MBA_RES_SUCCESS;
}


/**
 * @brief Handles BLE events and dispatches them to the Device Manager submodule.
 * 
 * @param[in] p_stackEvent  Pointer to the STACK_Event_T structure containing stack event data.
 */
void BLE_DM_BleEventHandler(STACK_Event_T *p_stackEvent)
{
    BLE_DM_Info(p_stackEvent);
    BLE_DM_Sm(p_stackEvent);
    BLE_DM_Conn(p_stackEvent);
}


/**
 * @brief Configures the BLE Device Manager module with the given settings.
 * 
 * @param[in] p_config      Pointer to the BLE_DM_Config_T structure containing configuration data.
 * 
 * @retval MBA_RES_SUCCESS on success, error code otherwise.
 */
uint16_t BLE_DM_Config(BLE_DM_Config_T *p_config)
{
    uint16_t result;
    result = BLE_DM_SmConfig(p_config->secAutoAccept);

    if (result != MBA_RES_SUCCESS)
    {
        return result;
    }
    else
    {
        return BLE_DM_ConnConfig(&p_config->connConfig);
    }
}


/**
 * @brief Initiates or proceeds with BLE security procedures for a given connection.
 * 
 * @param[in] connHandle    The connection handle for which to proceed with security.
 * @param[in] repairing     Flag indicating whether this is a repairing procedure.
 * 
 * @retval MBA_RES_SUCCESS on success, error code otherwise.
 */
uint16_t BLE_DM_ProceedSecurity(uint16_t connHandle, bool repairing)
{
    return BLE_DM_SmPairing(connHandle, repairing);
}


/**
 * @brief Sets the BLE Filter Accept List with the given device identifiers.
 * 
 * @param[in] devCnt        The count of devices to be added to the list.
 * @param[in] p_devId       Pointer to an array of device identifiers.
 * 
 * @retval MBA_RES_SUCCESS on success, error code otherwise.
 */
uint16_t BLE_DM_SetFilterAcceptList(uint8_t devCnt, uint8_t const * p_devId)
{
    return BLE_DM_InfoSetFilterAcceptList(devCnt, p_devId);
}


/**
 * @brief Retrieves the BLE Filter Accept List.
 * 
 * @param[in] p_devCnt      Pointer to store the count of devices in the list.
 * @param[in] p_addr        Pointer to an array of BLE_GAP_Addr_T to store the device addresses.
 * 
 * @retval MBA_RES_SUCCESS on success, error code otherwise.
 */
uint16_t BLE_DM_GetFilterAcceptList(uint8_t *p_devCnt, BLE_GAP_Addr_T *p_addr)
{
    return BLE_DM_InfoGetFilterAcceptList(p_devCnt, p_addr);
}


/**
 * @brief Sets the BLE Resolving List with the given device identifiers and privacy modes.
 * 
 * @param[in] devCnt        The count of devices to be added to the list.
 * @param[in] p_devId       Pointer to an array of device identifiers.
 * @param[in] p_privacyMode Pointer to an array of privacy modes for each device.
 * 
 * @retval MBA_RES_SUCCESS on success, error code otherwise.
 */
uint16_t BLE_DM_SetResolvingList(uint8_t devCnt, uint8_t const *p_devId, uint8_t const *p_privacyMode)
{
    return BLE_DM_InfoSetResolvingList(devCnt, p_devId, p_privacyMode);
}


/**
 * @brief Deletes a paired device from the BLE Device Manager module.
 * 
 * @param[in] devId The identifier of the device to delete.
 * 
 * @retval MBA_RES_SUCCESS on success, error code otherwise.
 */
uint16_t BLE_DM_DeletePairedDevice(uint8_t devId)
{
    return BLE_DM_DdsDeletePairedDevice(devId);
}


/**
 * @brief Retrieves information about a paired device.
 * 
 * @param[in] devId The identifier of the device to retrieve information for.
 * @param[in] p_pairedDevInfo Pointer to a BLE_DM_PairedDevInfo_T structure to store the paired device information.
 * 
 * @retval MBA_RES_SUCCESS on success, error code otherwise.
 */
uint16_t BLE_DM_GetPairedDevice(uint8_t devId, BLE_DM_PairedDevInfo_T *p_pairedDevInfo)
{
    return BLE_DM_DdsGetPairedDevice(devId, p_pairedDevInfo);
}


/**
 * @brief Deletes all paired devices from the BLE Device Manager module.
 * 
 * @retval MBA_RES_SUCCESS on success, error code otherwise.
 */
uint16_t BLE_DM_DeleteAllPairedDevice(void)
{
    return BLE_DM_DdsDeleteAllPairedDevice();
}


/**
 * @brief Retrieves a list of all paired device identifiers.
 * 
 * @param p_devId[out]   Pointer to an array to store the device identifiers.
 * @param p_devCnt[out]  Pointer to store the count of paired devices.
 */
void BLE_DM_GetPairedDeviceList(uint8_t *p_devId, uint8_t *p_devCnt)
{
    uint8_t devId;

    *p_devCnt = 0;

    for (devId = 0; devId < BLE_DM_MAX_PAIRED_DEVICE_NUM; devId++)
    {
        if (BLE_DM_DdsChkDeviceId(devId)==true)
        {
            p_devId[*p_devCnt] = devId;
            (*p_devCnt)++;
        }
    }
}