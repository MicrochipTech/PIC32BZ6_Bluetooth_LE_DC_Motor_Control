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
  Device Information Middleware Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_info.h

  Summary:
    Defines the interface for Device Information submodule within the BLE Device
    Manager module.

  Description:
    This header specifies the functions and data structures used by the BLE
    Device Manager to handle Device Information. It
    is intended for internal use within the BLE middleware stack.
 *******************************************************************************/ 
#ifndef BLE_DM_INFO_H
#define BLE_DM_INFO_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <string.h>
#include "stack_mgr.h"
#include "ble_gap.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/**
 * @defgroup BLE_DM_INFO BLE device manager device information
 * @brief Header file for the BLE Device Manager (ble_dm_info) internal module.
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
typedef enum BLE_DM_InfoState_T
{
    BLE_DM_INFO_STATE_IDLE = 0x00,          /**< State indicating the BLE device manager is idle. */
    BLE_DM_INFO_STATE_CONNECTED             /**< State indicating the BLE device manager is connected to a device. */
}BLE_DM_InfoState_T;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**
 * @brief Structure to hold BLE device connection information.
 *
 * This structure contains information about a BLE connection, including
 * connection handle, role, state, remote address, encryption status, and keys.
 */
typedef struct BLE_DM_InfoConn_T
{
    uint16_t            connHandle;             /**< Connection handle for the BLE connection. */
    uint8_t             role;                   /**< Role of the local device in the connection. */
    BLE_DM_InfoState_T  state;                  /**< Current state of the BLE connection. */
    BLE_GAP_Addr_T      remoteAddr;             /**< Bluetooth address of the remote device. */
    bool                encryptKeyValid;        /**< Flag indicating if the encryption key is valid. */
    uint8_t             encryptKey[16];         /**< Encryption key used in the BLE connection. */
    uint8_t             pairOption;             /**< Pairing options used. */
    uint8_t             encKeySize;             /**< Size of the encryption key. */
    uint8_t             devId;                  /**< Identifier for the device. */
} BLE_DM_InfoConn_T;

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

/**
 * @brief Initialize BLE_DM_InfoInit module.
 *
 * @retval true      Successfully initialize BLE_DM_InfoInit module.
 * @retval false     Fail to initialize BLE_DM_InfoInit module.
*/
bool BLE_DM_InfoInit(void);


/**
 * @brief Function for handling BLE events.
 *        This function should be called for every BLE event
 *
 * @param[in] p_stackEvent        Pointer to BLE events buffer.
 *
*/
void BLE_DM_Info(STACK_Event_T *p_stackEvent);


/**
 * @brief Get a connection object by its handle.
 * 
 * @param[in] connHandle    The handle of the connection to retrieve.
 * 
 * @retval Pointer to the connection object, or NULL if not found.
 */
BLE_DM_InfoConn_T *BLE_DM_InfoGetConnByHandle(uint16_t connHandle);


/**
 * @brief Set the BLE filter accept list.
 * 
 * @param[in] devCnt    Number of devices to add to the list.
 * @param[in] p_devId   Pointer to the array of device IDs to add.
 * 
 * @retval MBA_RES_SUCCESS on success, error code otherwise.
 */
uint16_t BLE_DM_InfoSetFilterAcceptList(uint8_t devCnt, uint8_t const *p_devId);


/**
 * @brief Retrieve the BLE filter accept list.
 * 
 * @param[out] p_devCnt      Pointer to store the count of devices in the list.
 * @param[out] p_addr        Pointer to the array to store the device addresses.
 * 
 * @retval MBA_RES_SUCCESS on success, error code otherwise.
 */
uint16_t BLE_DM_InfoGetFilterAcceptList(uint8_t *p_devCnt, BLE_GAP_Addr_T *p_addr);


/**
 * @brief Set the BLE resolving list.
 * 
 * @param[in] devCnt        Number of devices to add to the list.
 * @param[in] p_devId       Pointer to the array of device IDs to add.
 * @param[in] p_privacyMode Pointer to the array of privacy modes for each device.
 * 
 * @retval MBA_RES_SUCCESS on success, error code otherwise.
 */
uint16_t BLE_DM_InfoSetResolvingList(uint8_t devCnt, uint8_t const *p_devId, uint8_t const *p_privacyMode);


/** @brief Retrieve the connection handle by device ID.
 * 
 * @param devId[in]          The device ID to look up.
 * @param p_connHandle[out]  Pointer to store the connection handle.
 * 
 * @retval MBA_RES_SUCCESS on success, error code otherwise.
 */
uint16_t BLE_DM_InfoGetConnHandleByDevId(uint8_t devId, uint16_t *p_connHandle);

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif //BLE_DM_INFO_H