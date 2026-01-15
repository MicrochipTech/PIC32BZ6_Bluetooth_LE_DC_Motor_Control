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
   BLE Connection Middleware Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_conn.h

  Summary:
    Defines the interface for BLE connection management within the BLE Device 
    Manager module.

  Description:
    This header file declares the functions and data structures used by the BLE 
    Device Manager for handling BLE connections. It is intended for internal 
    use within the BLE Device Manager module and should not be included 
    directly by application code.
 *******************************************************************************/
#ifndef BLE_DM_CONN_H
#define BLE_DM_CONN_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include <stdint.h>
#include "stack_mgr.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/**
 * @defgroup BLE_DM_COMM BLE device manger connection management
 * @brief Header file for the BLE Device Manager (ble_dm_conn) internal module.
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

/**
 * @brief Initializes the BLE Device Manager connection submodule.
 * 
 * @retval true if initialization is successful, false otherwise.
 */
bool BLE_DM_ConnInit(void);


/**
 * @brief Main entry function for BLE Device Manager connection-related events.
 * 
 * @param[in] p_stackEvent Pointer to the stack event structure.
 */
void BLE_DM_Conn(STACK_Event_T *p_stackEvent);


/**
 * @brief Configures the connection parameters.
 * 
 * @param[in] p_config Pointer to the connection configuration structure.
 * 
 * @retval MBA_RES_SUCCESS on success, MBA_RES_INVALID_PARA on invalid parameters.
 */
uint16_t BLE_DM_ConnConfig(BLE_DM_ConnConfig_T *p_config);

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif //BLE_DM_CONN_H

