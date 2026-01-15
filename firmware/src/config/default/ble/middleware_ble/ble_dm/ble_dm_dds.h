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
  Device Information Middleware Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_dds.h

  Summary:
    Interface definitions for the internal Device Data Storage (DDS) 
    functionalities used by the BLE Device Manager.

  Description:
    This header file declares the internal functions and data structures 
    utilized by the BLE Device Manager for storing and managing device-related 
    data. These functions are not intended for direct use by external modules.
 *******************************************************************************/ 
#ifndef BLE_DM_DDS_H
#define BLE_DM_DDS_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "ble_dm.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/**
 * @defgroup BLE_DM_DDS BLE device manager device data storage
 * @brief Header file for the BLE Device Manager (ble_dm_dds) internal module.
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**
 * @brief Callback type for indicating completion of a PDS write operation.
 *
 * @param devId The identifier of the device for which the PDS write operation was performed.
 */
typedef void (*BLE_DM_DdsWriteCompleteCb_T)(uint8_t devId);

/**
 * @brief Retrieve paired device information.
 * 
 * @param[in] devId             Device ID of the paired device.
 * @param[out] p_pairedDevInfo  Pointer to the structure where paired device information will be stored.
 * 
 * @retval MBA_RES_SUCCESS on success.
 * @retval MBA_RES_INVALID_PARA if the device ID is invalid.
 * @retval MBA_RES_FAIL on failure.
 */
uint16_t BLE_DM_DdsGetPairedDevice(uint8_t devId, BLE_DM_PairedDevInfo_T *p_pairedDevInfo);


/**
 * @brief Set paired device information.
 * 
 * @param[in] devId Device ID of the paired device.
 * @param[in] p_pairedDevInfo Pointer to the structure containing the paired device information to be set.
 * 
 * @retval MBA_RES_SUCCESS on success.
 * @retval MBA_RES_INVALID_PARA if the device ID is invalid.
 * @retval MBA_RES_FAIL on failure.
 */
uint16_t BLE_DM_DdsSetPairedDevice(uint8_t devId, BLE_DM_PairedDevInfo_T *p_pairedDevInfo);


/**
 * @brief Get the first free device ID.
 * 
 * @retval The first free device ID.
 */
uint8_t BLE_DM_DdsGetFreeDeviceId(void);


/**
 * @brief Retrieve the device ID for a given Bluetooth address.
 * 
 * @param[in] p_bdAddr Pointer to the Bluetooth address structure.
 * 
 * @retval Device ID on success, or BLE_DM_MAX_PAIRED_DEVICE_NUM if the address is non-resolvable or on failure.
 */
uint8_t BLE_DM_DdsGetDeviceId(BLE_GAP_Addr_T *p_bdAddr);


/**
 * @brief Delete paired device information for a given device ID.
 * 
 * @param[in] devId Device ID of the paired device to be deleted.
 * 
 * @retval MBA_RES_SUCCESS on success.
 * @retval MBA_RES_INVALID_PARA if the device ID is invalid.
 * @retval MBA_RES_FAIL on failure.
 */
uint16_t BLE_DM_DdsDeletePairedDevice(uint8_t devId);


/**
 * @brief Delete all paired device information.
 * 
 * @retval MBA_RES_SUCCESS on success.
 * @retval MBA_RES_FAIL on failure.
 */
uint16_t BLE_DM_DdsDeleteAllPairedDevice(void);


/**
 * @brief Check if a device ID is valid and able to be restored.
 * 
 * @param[in] devId Device ID to be checked.
 * 
 * @retval true if the device ID is valid and able to be restored, false otherwise.
 */
bool BLE_DM_DdsChkDeviceId(uint8_t devId);


/**
 * @brief Initialize the Device Manager Device Data Storage submodule.
 * 
 * @param[in] cb Callback function to be called on write complete event.
 */
void BLE_DM_DdsInit(BLE_DM_DdsWriteCompleteCb_T cb);

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif //BLE_DM_DDS_H