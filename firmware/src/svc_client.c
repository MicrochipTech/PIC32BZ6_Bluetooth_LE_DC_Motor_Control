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
  BLE Garage Door Motor Control Demo (GDMC) Service Source File

  Company:
    Microchip Technology Inc.

  File Name:
    svc_client.c

  Summary:
    Implements the client-side logic for the Garage Door Motor Control Service over BLE.

  Description:
    This source file provides the necessary functions to interface with peripherals
    that can connect to garage door head unit.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include "osal/osal_freertos.h"
#include "mba_error_defs.h"
#include "ble_gap.h"
#include "ble_util/byte_stream.h"
#include "svc_client.h"
#include "ble_gcm/ble_dd.h"
#include "system/console/sys_console.h"
#include "stdio.h"
#include "motor_control.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
#define BLE_GDMC_UUID_SVC                       (0xCD01U)     // UUID for the GDMC Service. 

#define BLE_GDMC_PROC_IDLE                      (0x00U)       // procedure is idle.
#define BLE_GDMC_PROC_ENABLE_NEW_CCCD           (0x01U)       // Enable notification for new incoming alerts.
#define BLE_GDMC_PROC_ENABLE_UNREAD_CCCD        (0x02U)       // Enable notification for unread alert status.
#define BLE_GDMC_PROC_ENABLE_SESSION            (0x03U)       // Enable notification for control point changes.

#define BLE_GDMC_MAX_CONN_NBR                   BLE_GAP_MAX_LINK_NBR    // Maximum number of concurrent connections supported.

typedef enum BLE_GDMC_CharAlertNotiIndex_T
{
    GDMC_INDEX_CHARAN_NEW_ALERT,                              // Index for the New Alert characteristic.
    GDMC_INDEX_CHARAN_NEW_ALERT_CCC,                          // Index for the New Alert CCCD (Client Characteristic Configuration Descriptor).
    GDMC_INDEX_CHARAN_MAX_NUM                                 // Total number of characteristics in the GDMC .
} BLE_GDMC_CharAlertNotiIndex_T;


typedef enum BLE_GDMC_State_T
{
    BLE_GDMC_STATE_IDLE = 0x00U,                              // State indicating the service is idle.
    BLE_GDMC_STATE_CONNECTED                                  // State indicating the service is connected.
} BLE_GDMC_State_T;
// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/* The structure contains information about BLE GDMC profile connection parameters for recording connection information. */
typedef struct BLE_GDMC_ConnList_T
{
    uint8_t           connIndex;  // Connection index associated with this connection.
    BLE_GDMC_State_T  state;      // State associated with this connection.
    uint16_t          connHandle; // Connection handle associated with this connection.
} BLE_GDMC_ConnList_T;

/* The Structure service database and discovery list for BLE GDMC. */
typedef struct BLE_GDMC_ServiceDb_T
{
    BLE_DD_CharList_T gdmcCharList[BLE_GDMC_MAX_CONN_NBR];
    BLE_DD_DiscInfo_T gdmcDiscInfo[BLE_GDMC_MAX_CONN_NBR];
    BLE_DD_CharInfo_T gdmcCharInfoList[BLE_GDMC_MAX_CONN_NBR][GDMC_INDEX_CHARAN_MAX_NUM];
    BLE_DD_DiscChar_T gdmcDiscCharList[GDMC_INDEX_CHARAN_MAX_NUM];
    BLE_DD_DiscChar_T *p_gdmcDiscCharList[GDMC_INDEX_CHARAN_MAX_NUM];
} BLE_GDMC_ServiceDb_T;

// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************
// Callback routine for GDMC (GDMC Profile Client) events.

// An array to keep track of the connection list for GDMC.
static BLE_GDMC_ConnList_T  *sp_gdmcConnList[BLE_GDMC_MAX_CONN_NBR];

// List of pointers to the discovery information for GDMC characteristics and descriptors.
static BLE_GDMC_ServiceDb_T *sp_gdmcServiceDb;

// UUID for the New Alert characteristic in the ANP.
static const ATT_Uuid_T s_gdmcDiscCharControl = { { UINT16_TO_BYTES(BLE_GDMC_UUID_CONTROL) }, ATT_UUID_LENGTH_2 }; //cd02

// UUID for the Client Characteristic Configuration Descriptor (CCCD) of the New Alert characteristic.
static const ATT_Uuid_T s_gdmcDiscCharControlCcc = { { UINT16_TO_BYTES(UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG) }, ATT_UUID_LENGTH_2 };


// UUID for the Garage Door Motor Control Service.
static const uint8_t s_gdmcDiscServiceUuid[] = { UINT16_TO_BYTES(BLE_GDMC_UUID_SERVICE) }; //
// *****************************************************************************
// *****************************************************************************
// Section: Functions
// ***************************************************************************** 
// *****************************************************************************

/**
 * @brief Retrieves a pointer to the connection list entry by connection handle.
 * 
 * @param connHandle            The handle of the connection.
 * 
 * @retval BLE_GDMC_ConnList_T* Pointer to the connection list entry or NULL if not found.
 */
static BLE_GDMC_ConnList_T *ble_gdmc_GetConnListByHandle(uint16_t connHandle)
{
    uint8_t i;

    for(i=0; i<BLE_GDMC_MAX_CONN_NBR; i++)
    {
        if ((sp_gdmcConnList[i] != NULL) && (sp_gdmcConnList[i]->state == BLE_GDMC_STATE_CONNECTED) && (sp_gdmcConnList[i]->connHandle == connHandle))
        {
            return sp_gdmcConnList[i];
        }
    }
    return NULL;
}


/**
 * @brief Get a free connection list entry for the GDMC.
 *
 * @retval Pointer to the GDMC connection list structure, or NULL if no free entry is available.
 */
static BLE_GDMC_ConnList_T *ble_gdmc_GetFreeConnList(void)
{
    uint8_t i;
    BLE_GDMC_ConnList_T *p_conn = NULL;

    for(i = 0; i < BLE_GDMC_MAX_CONN_NBR; i++)
    {
        if (sp_gdmcConnList[i] == NULL)
        {
            sp_gdmcConnList[i] = OSAL_Malloc(sizeof(BLE_GDMC_ConnList_T));
            p_conn = sp_gdmcConnList[i];
            if (p_conn != NULL)
            {
                (void)memset(p_conn, 0, sizeof(BLE_GDMC_ConnList_T));
                p_conn->state     = BLE_GDMC_STATE_CONNECTED;
                p_conn->connIndex = i;
            }
            break;
        }
    }
    return p_conn;
}


/**
 * @brief Initializes the GDMC characteristic list to zero.
 * 
 * @param connIndex     Index of the connection in the GDMC characteristic list.
 */
static void ble_gdmc_InitServiceCharList(uint8_t connIndex)
{
    (void)memset(&sp_gdmcServiceDb->gdmcDiscInfo[connIndex], 0x0, sizeof(BLE_DD_DiscInfo_T));
    (void)memset(&sp_gdmcServiceDb->gdmcCharList[connIndex], 0x0, sizeof(BLE_DD_CharList_T));
    (void)memset(sp_gdmcServiceDb->gdmcCharInfoList[connIndex], 0x0, sizeof(BLE_DD_CharInfo_T)*GDMC_INDEX_CHARAN_MAX_NUM);
    sp_gdmcServiceDb->gdmcCharList[connIndex].p_charInfo = sp_gdmcServiceDb->gdmcCharInfoList[connIndex];
}


/**
 * @brief Reads the Alert Category characteristic value from the GDMC.
 * 
 * @param connHandle    The handle of the connection.
 * @param index         Index of the GDMC characteristic.
 * 
 * @retval uint16_t     Result of the read operation.
 */
static uint16_t ble_gdmc_ReadAlert(uint16_t connHandle, BLE_GDMC_CharAlertNotiIndex_T index)
{
    BLE_GDMC_ConnList_T *p_conn = ble_gdmc_GetConnListByHandle(connHandle);
    uint16_t charHandle;

    if(p_conn == NULL)
    {
        return MBA_RES_INVALID_PARA;
    } 
    charHandle = sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[index].charHandle;
    if (charHandle == 0U)
    {
        return MBA_RES_FAIL;
    }
    return GATTC_Read(connHandle, charHandle, 0);
}


/**
 * @brief Writes to the Alert Data Client Characteristic Configuration Descriptor (CCCD) to enable or disable notifications.
 * 
 * @param connHandle    The handle of the connection.
 * @param enable        Boolean value to enable or disable notifications.
 * @param index         Index of the GDMC characteristic.
 * 
 * @retval uint16_t Result of the write operation.
 */
static uint16_t ble_gdmc_WriteAlertDataCccd(uint16_t connHandle, bool enable, BLE_GDMC_CharAlertNotiIndex_T index)
{
    GATTC_WriteParams_T *p_writeParams;
    BLE_GDMC_ConnList_T *p_conn;
    uint16_t charHandle, result;
    uint16_t cccValue = 0;

    p_conn = ble_gdmc_GetConnListByHandle(connHandle);
    if (p_conn == NULL)
    {
        return MBA_RES_INVALID_PARA;
    }

    charHandle = sp_gdmcServiceDb->gdmcCharInfoList[p_conn->connIndex][index].charHandle;
    if (charHandle == 0U)
    {
        return MBA_RES_INVALID_PARA;
    }

    if (enable)
    {
        cccValue = NOTIFICATION;
    }

    p_writeParams = OSAL_Malloc(sizeof(GATTC_WriteParams_T));
    if (p_writeParams == NULL)
    {
        return MBA_RES_OOM;
    }

    p_writeParams->charHandle = charHandle;
    p_writeParams->charLength = 0x02;
    U16_TO_BUF_LE(p_writeParams->charValue, cccValue);
    p_writeParams->writeType = ATT_WRITE_REQ;
    p_writeParams->valueOffset = 0x0000;
    p_writeParams->flags = 0;

    result = GATTC_Write(connHandle, p_writeParams);
    OSAL_Free(p_writeParams);
    return result;
}


/**
 * @brief Processes notification or indication received from the GATT server.
 * 
 * @param p_event Pointer to the GATT event structure.
 */
static void ble_gdmc_ProcNotificationInd(GATT_Event_T *p_event)
{
    //uint8_t *p_value = p_event->eventField.onNotification.receivedValue;
    BLE_GDMC_ConnList_T *p_conn = ble_gdmc_GetConnListByHandle(p_event->eventField.onNotification.connHandle);

    if(p_conn == NULL)
    {
        return;
    }
}

extern void sendNotificationMessage(const char* buffer, uint32_t len);


/**
 * @brief Processes the read response event from GATT.
 *
 * @param p_event Pointer to the GATT event structure.
 */
static void ble_gdmc_ProcReadResponse(GATT_Event_T *p_event)
{
    uint8_t *p_value = p_event->eventField.onReadResp.readValue;
    BLE_GDMC_ConnList_T *p_conn = ble_gdmc_GetConnListByHandle(p_event->eventField.onReadResp.connHandle);
    uint8_t data;
    if(p_conn == NULL)
    {
        return;
    }
    if (p_event->eventField.onReadResp.charHandle == sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[GDMC_INDEX_CHARAN_NEW_ALERT].charHandle)
    {
        STREAM_TO_U8(&data, &p_value);
        //SYS_CONSOLE_PRINT("Read 0x%02x from characteristic\r\n", data);
        if (data == 0x01)
        {
 
            Motor_Toggle();
            char buffer[128];
            snprintf(buffer, 128, "Remote Button Toggle");
            sendNotificationMessage(buffer, strlen(buffer));
        }
       SYS_CONSOLE_PRINT("Closing connection handle %d\r\n",p_event->eventField.onReadResp.connHandle);
        // peripheral will close connection immediately after read is complete.
        // BLE_GDMC_EnableControlNtfy(p_event->eventField.onReadResp.connHandle, true);
        // lets try and close it here because we know we have got the data.
        if (BLE_GAP_Disconnect(p_event->eventField.onReadResp.connHandle, GAP_STATUS_LOCAL_HOST_TERMINATE_CONNECTION) != 0)
        {
            //SYS_CONSOLE_MESSAGE("Failed to close connection\r\n");
        }

    }
    else
    {
		//Shall not enter here
    }

}


/**
 * @brief Processes the write response event from GATT.
 *
 * @param p_event Pointer to the GATT event structure.
 */
static void ble_gdmc_ProcWriteResponse(GATT_Event_T *p_event)
{
    BLE_GDMC_ConnList_T *p_conn = ble_gdmc_GetConnListByHandle(p_event->eventField.onWriteResp.connHandle);
    uint16_t charHandle = p_event->eventField.onWriteResp.charHandle;

    if(p_conn == NULL)
    {
        return;
    }

    if (charHandle == sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[GDMC_INDEX_CHARAN_NEW_ALERT_CCC].charHandle)
    {
        //evt.eventId = BLE_GDMC_EVT_WRITE_NEW_ALERT_NTFY_RSP_IND;
        //evt.eventField.evtWriteControlRspInd.connHandle = p_event->eventField.onWriteResp.connHandle;
        //evt.eventField.evtWriteControlRspInd.errCode = 0x00;
    }
    else
    {
        return;
    }
}


/**
 * @brief Processes the error response event from GATT.
 *
 * @param p_event Pointer to the GATT event structure.
 */
static void ble_gdmc_ProcErrorResponse(GATT_Event_T *p_event)
{
    BLE_GDMC_ConnList_T *p_conn = ble_gdmc_GetConnListByHandle(p_event->eventField.onError.connHandle);
    uint16_t charHandle = p_event->eventField.onError.attrHandle;

    if (p_conn == NULL)
    {
        return;
    }

    if (charHandle == sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[GDMC_INDEX_CHARAN_NEW_ALERT_CCC].charHandle)
    {
        //evt.eventId = BLE_GDMC_EVT_WRITE_NEW_ALERT_NTFY_RSP_IND;
        //evt.eventField.evtWriteControlRspInd.connHandle = p_event->eventField.onError.connHandle;
        //evt.eventField.evtWriteControlRspInd.errCode = p_event->eventField.onError.errCode;
    }
    else
    {
        return;
    }
}

/**
 * @brief Free the connection list for the GDMC.
 *
 * @param p_conn        Pointer to the GDMC connection list structure to initialize.
 * @param disconnect    Flag indicating whether to disconnect.
 */
static void ble_gdmc_FreeConnList(BLE_GDMC_ConnList_T *p_conn)
{
    uint8_t i;
    for (i = 0; i < BLE_GDMC_MAX_CONN_NBR; i++)
    {
        if (sp_gdmcConnList[i] == p_conn)
        {
            OSAL_Free(sp_gdmcConnList[i]);
            sp_gdmcConnList[i] = NULL;
            break;
        }
    }
}

/**
 * @brief Processes GATT events and dispatch them to the appropriate handler.
 *
 * @param p_event Pointer to the GATT event structure.
 */
static void ble_gdmc_GattEventProcess(GATT_Event_T *p_event)
{
    //SYS_CONSOLE_PRINT("ble_gdmc_GattEventProcess event:%d\r\n", p_event->eventId);
    switch (p_event->eventId)
    {
        case GATTC_EVT_HV_NOTIFY:
        {
            ble_gdmc_ProcNotificationInd(p_event);
        }
        break;

        case GATTC_EVT_READ_RESP:
        {
            ble_gdmc_ProcReadResponse(p_event);
        }
        break;

        case GATTC_EVT_WRITE_RESP:
        {
            ble_gdmc_ProcWriteResponse(p_event);
        }
        break;

        case GATTC_EVT_ERROR_RESP:
        {
            ble_gdmc_ProcErrorResponse(p_event);
        }
        break;

        default:
        {
            //SYS_CONSOLE_MESSAGE("Not Handled\r\n");
        }
        break;
    }
}


/**
 * @brief Processes GAP events and handle connection-related events.
 *
 * @param p_event Pointer to the GAP event structure.
 */
static void ble_gdmc_GapEventProcess(BLE_GAP_Event_T *p_event)
{
    BLE_GDMC_ConnList_T *p_conn = NULL;
    switch(p_event->eventId)
    {
        case BLE_GAP_EVT_CONNECTED:
        {
            if (p_event->eventField.evtConnect.status == GAP_STATUS_SUCCESS)
            {
                p_conn = ble_gdmc_GetFreeConnList();
                if (p_conn == NULL)
				{
                }
                else
                {
                    //SYS_CONSOLE_PRINT("Connected for connHandle %d\r\n", p_event->eventField.evtConnect.connHandle);
                    p_conn->connHandle = p_event->eventField.evtConnect.connHandle;
                }
            }
        }
        break;

        case BLE_GAP_EVT_DISCONNECTED:
        {
            p_conn = ble_gdmc_GetConnListByHandle(p_event->eventField.evtDisconnect.connHandle);
            if (p_conn != NULL)
            {
                ble_gdmc_FreeConnList(p_conn);
            }
        }
        break;

        default:
        {
            //Do nothing
        }
        break;
    }
}


/**
 * @brief Initializes BLE GDMC Client.
 *
 * @retval MBA_RES_SUCCESS          The client was successfully initialized.
 * @retval MBA_RES_FAIL             The client failed to initialize.
 * @retval MBA_RES_OOM              Internal memory allocation failure.
 */

uint16_t BLE_GDMC_Init(void)
{
    uint8_t i;
    uint16_t ret;
    BLE_DD_DiscSvc_T anpDisc;

    if (sp_gdmcServiceDb)
    {
        return MBA_RES_FAIL;
    }
    sp_gdmcServiceDb = (BLE_GDMC_ServiceDb_T*)OSAL_Malloc(sizeof(BLE_GDMC_ServiceDb_T));
    if (sp_gdmcServiceDb == NULL)
    {
        return MBA_RES_OOM;
    }

    (void)memset(sp_gdmcServiceDb->gdmcDiscCharList, 0x00, sizeof(BLE_DD_DiscChar_T)*GDMC_INDEX_CHARAN_MAX_NUM);
    sp_gdmcServiceDb->gdmcDiscCharList[GDMC_INDEX_CHARAN_NEW_ALERT].p_uuid             = &s_gdmcDiscCharControl;
    sp_gdmcServiceDb->gdmcDiscCharList[GDMC_INDEX_CHARAN_NEW_ALERT_CCC].p_uuid         = &s_gdmcDiscCharControlCcc;
    sp_gdmcServiceDb->gdmcDiscCharList[GDMC_INDEX_CHARAN_NEW_ALERT_CCC].settings       = CHAR_SET_DESCRIPTOR;

    for(i = 0; i < GDMC_INDEX_CHARAN_MAX_NUM; i++)
    {
        sp_gdmcServiceDb->p_gdmcDiscCharList[i] = &sp_gdmcServiceDb->gdmcDiscCharList[i];
    }

    for(i = 0; i < BLE_GDMC_MAX_CONN_NBR; i++)
    {
        ble_gdmc_InitServiceCharList(i);
    }
    anpDisc.svcUuid.uuidLength = ATT_UUID_LENGTH_2;
    (void)memcpy(anpDisc.svcUuid.uuid, s_gdmcDiscServiceUuid, ATT_UUID_LENGTH_2);
    anpDisc.p_discInfo   = sp_gdmcServiceDb->gdmcDiscInfo;
    anpDisc.p_discChars  = sp_gdmcServiceDb->p_gdmcDiscCharList;
    anpDisc.p_charList   = sp_gdmcServiceDb->gdmcCharList;
    anpDisc.discCharsNum = (uint8_t)GDMC_INDEX_CHARAN_MAX_NUM;

    ret = BLE_DD_ServiceDiscoveryRegister(&anpDisc);

    if (ret != MBA_RES_SUCCESS)
    {
        OSAL_Free(sp_gdmcServiceDb);
        sp_gdmcServiceDb = NULL;
    }
    return ret;
}






/**
 * @brief Enables or disables notifications for new alerts.
 *
 * @param[in] connHandle            The connection handle to identify the BLE connection.
 * @param[in] enable                Set to true to enable notifications; false to disable.
 *
 * @retval MBA_RES_SUCCESS          The operation was successful.
 * @retval MBA_RES_INVALID_PARA     The connection handle is invalid.
 * @retval MBA_RES_OOM              Internal memory allocation failure.
 */
uint16_t BLE_GDMC_EnableControlNtfy(uint16_t connHandle, bool enable)
{
    return ble_gdmc_WriteAlertDataCccd(connHandle, enable, GDMC_INDEX_CHARAN_NEW_ALERT_CCC);
}


/**
 * @brief Retrieves a list of discovered GDMC service characteristics.
 * 
 * This function should be called after the BLE_GDMC_EVT_DISC_COMPLETE_IND event.
 *
 * @param[in]  connHandle           The connection handle to identify the BLE connection.
 * @param[in]  charUuid             The UUID of the characteristic to look for.
 * @param[out] p_charList           On success, filled with the discovered characteristics info.
 *
 * @retval MBA_RES_SUCCESS          The characteristic list was successfully retrieved.
 * @retval MBA_RES_INVALID_PARA     The parameters are invalid (e.g., invalid connection handle or UUID).
 */
uint16_t BLE_GDMC_GetCharList(uint16_t connHandle, uint16_t charUuid, BLE_GDMC_CharList_T *p_charList)
{
    uint8_t             idx;
    uint16_t            desUuid;
    BLE_GDMC_ConnList_T *p_conn = ble_gdmc_GetConnListByHandle(connHandle);

    (void)memset(p_charList, 0, sizeof(BLE_GDMC_CharList_T)); 
    for (idx = 0; idx < (uint8_t)GDMC_INDEX_CHARAN_MAX_NUM; idx++)
    {
        BUF_LE_TO_U16(&desUuid, sp_gdmcServiceDb->p_gdmcDiscCharList[idx]->p_uuid->uuid);
        if ((desUuid == charUuid) &&
            ((sp_gdmcServiceDb->p_gdmcDiscCharList[idx]->settings & CHAR_SET_DESCRIPTOR) != CHAR_SET_DESCRIPTOR))
        {
            p_charList->attrHandle = sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[idx].attrHandle; 
            p_charList->property   = sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[idx].property;
            p_charList->charHandle = sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[idx].charHandle;
            break;
        }
    }
    return MBA_RES_SUCCESS;
}


/**
 * @brief Retrieves a list of descriptors within the GDMC Service.
 * 
 * This function should be called after the BLE_GDMC_EVT_DISC_COMPLETE_IND event.
 *
 * @param[in]  connHandle           The connection handle to identify the BLE connection.
 * @param[out] p_descList           On success, filled with the discovered descriptors info.
 *
 * @retval MBA_RES_SUCCESS          The descriptor list was successfully retrieved.
 * @retval MBA_RES_INVALID_PARA     The connection handle is invalid.
 */
uint16_t BLE_GDMC_GetDescList(uint16_t connHandle, BLE_GDMC_DescList_T *p_descList)
{
    uint8_t             idx, descNum = 0;
    BLE_GDMC_ConnList_T *p_conn = ble_gdmc_GetConnListByHandle(connHandle);

    if ((p_conn == NULL) || (p_descList == NULL))
    {
        return MBA_RES_INVALID_PARA;
    } 
    (void)memset(p_descList, 0, sizeof(BLE_GDMC_DescList_T)); 
    for (idx = 0; idx < (uint8_t)GDMC_INDEX_CHARAN_MAX_NUM; idx++)
    {
        if (((sp_gdmcServiceDb->p_gdmcDiscCharList[idx]->settings & CHAR_SET_DESCRIPTOR) != 0U) && (sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[idx].charHandle != 0U))
        {
            p_descList->descInfo[descNum].attrHandle = sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[idx].charHandle;
            VARIABLE_COPY_TO_BUF(&p_descList->descInfo[descNum].uuid, sp_gdmcServiceDb->p_gdmcDiscCharList[idx]->p_uuid->uuid, sp_gdmcServiceDb->p_gdmcDiscCharList[idx]->p_uuid->uuidLength);
            descNum++;
        }
    }
    p_descList->totalNum = descNum; 
    return MBA_RES_SUCCESS;
}


/**
 * @brief Handles BLE Database Discovery (BLE_DD) events.
 *
 * @param[in] p_event               Pointer to the BLE DD event structure.
 *
*/
void BLE_GDMC_BleDdEventHandler(BLE_DD_Event_T *p_event)
{
    switch (p_event->eventId)
    {
        case BLE_DD_EVT_DISC_COMPLETE:
        {
            BLE_GDMC_ConnList_T *p_conn = ble_gdmc_GetConnListByHandle(p_event->eventField.evtDiscResult.connHandle);
            if (sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[GDMC_INDEX_CHARAN_NEW_ALERT].charHandle != 0U)
            {
                //SYS_CONSOLE_PRINT("Discovery Complete handle %d\r\n",p_event->eventField.evtDiscResult.connHandle);
                for (int i = 0; i < GDMC_INDEX_CHARAN_MAX_NUM; i++)
                {
                    //SYS_CONSOLE_PRINT("ConnIndex %d\r\n",p_conn->connIndex);
                    //SYS_CONSOLE_PRINT("H: 0x%x\r\n",sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[i].charHandle);
                    //SYS_CONSOLE_PRINT("P: 0x%x\r\n",sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[i].property);
                    //SYS_CONSOLE_PRINT("A: 0x%x\r\n",sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[i].attrHandle);
                }
                if(p_conn == NULL)
                {
                    return;
                } 
                if (sp_gdmcServiceDb->gdmcCharList[p_conn->connIndex].p_charInfo[GDMC_INDEX_CHARAN_NEW_ALERT].charHandle != 0U)
                {
                    //SYS_CONSOLE_MESSAGE("Discovery complete \r\n");
                }
                
                ble_gdmc_ReadAlert(p_event->eventField.evtDiscResult.connHandle, GDMC_INDEX_CHARAN_NEW_ALERT);
            }
        }
        break;

        default:
        {
            //Do nothing
        }
        break;
    }
}


/**
 * @brief Handles BLE_Stack events.
 * 
 * This function should be called when BLE stack events occur.
 * 
 * @param[in] p_stackEvent          Pointer to the stack event structure.
 *
*/
void BLE_GDMC_BleEventHandler(STACK_Event_T *p_stackEvent)
{
    switch (p_stackEvent->groupId)
    {
        case STACK_GRP_BLE_GAP:
        {
            ble_gdmc_GapEventProcess((BLE_GAP_Event_T *)p_stackEvent->p_event);
        }
        break;

        case STACK_GRP_GATT:
        {
            ble_gdmc_GattEventProcess((GATT_Event_T *)p_stackEvent->p_event);
        }
        break;

        default:
        {
            //Do nothing
        }
        break;
    }
}

