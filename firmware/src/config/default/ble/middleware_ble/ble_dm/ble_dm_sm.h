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
  Security Manager Middleware Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_sm.h

  Summary:
    Defines the internal Security Manager interface for the BLE Device Manager.

  Description:
    This header specifies the function prototypes and data structures used by
    the BLE Device Manager's Security Manager. It is intended for internal
    use within the BLE middleware stack to handle security-related tasks such
    as authentication and encryption.
 *******************************************************************************/
 
#ifndef BLE_DM_SM_H
#define BLE_DM_SM_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "stack_mgr.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/**
 * @defgroup BLE_DM_SM BLE device manager security management
 * @brief Header file for the BLE Device Manager (ble_dm_sm) internal module.
 * @{
 */
// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**
 * @brief Main entry point for BLE device manager security events.
 * 
 * @param p_stackEvent[in]  Pointer to the stack event structure.
 */
void BLE_DM_Sm(STACK_Event_T *p_stackEvent);


/**
 * @brief Configures the device manager with auto-accept option.
 * 
 * @param autoAccept[in]    Indicates whether to auto-accept security requests.
 * 
 * @retval MBA_RES_SUCCESS on successful configuration.
 */
uint16_t BLE_DM_SmConfig(bool autoAccept);


/**
 * @brief Initiates pairing or encryption with a BLE device.
 * 
 * @param connHandle[in]    Connection handle to identify the BLE connection.
 * @param repairing[in]     Indicates whether this is a re-pairing attempt.
 * 
 * @retval Result of    the pairing or encryption initiation.
 */
uint16_t BLE_DM_SmPairing(uint16_t connHandle, bool repairing);


/** @brief Initializes the BLE device manager with default values. */
void BLE_DM_SmInit(void);


/**
 * @brief Callback function to handle completion of PDS write operations.
 * 
 * @param devId[in] Device ID for which the write operation was completed.
 */
void BLE_DM_SmWriteCompleteCallback(uint8_t devId);

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif //BLE_DM_SM_H