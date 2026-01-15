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
  BLE Device Manager Middleware Internal Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_internal.h

  Summary:
    Internal functions and definitions for the BLE Device Manager module.

  Description:
    This header file is intended for internal use by the BLE Device Manager
    module. It contains function prototypes and definitions necessary for
    the implementation and maintenance of the module, not intended for
    external use.
 *******************************************************************************/ 
#ifndef BLE_DM_INTERNAL_H
#define BLE_DM_INTERNAL_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include "ble_dm.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/**
 * @defgroup BLE_DM_INTERNAL BLE device manager internal 
 * @brief Header file for the BLE Device Manager (ble_dm_internal) internal module.
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

extern BLE_DM_EventCb_T        g_dmEventCb[BLE_DM_MAX_REGISTER_NUM];      /**< Aarray of callback functions for BLE DM events. */
extern uint8_t                 g_dmCbNum;                                 /**< Counter for the number of registered DM callbacks. */


// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

/**
 * @brief Conveys a BLE Device Manager event to all registered callbacks.
 * 
 * @param[in] p_event Pointer to the BLE_DM_Event_T structure containing event data.
 */
void BLE_DM_ConveyEvent(BLE_DM_Event_T *p_event);

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif //BLE_DM_INTERNAL_H