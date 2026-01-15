
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
  BLE Ctrl Service Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_ctrl_svc.h

  Summary:
    This file contains the BLE Ctrl Service functions for application user.

  Description:
    This file contains the BLE Ctrl Service functions for application user.
 *******************************************************************************/


/**
 * @addtogroup BLE_CTRL BLE CTRL
 * @{
 * @brief Header file for the BLE Ctrl Service.
 * @note Definitions and prototypes for the BLE Ctrl Service stack layer application programming interface.
 */
#ifndef BLE_CTRL_H
#define BLE_CTRL_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
/**@defgroup BLE_CTRL_ASSIGN_HANDLE BLE_CTRL_ASSIGN_HANDLE
 * @brief Assigned attribute handles of BLE Ctrl Service.
 * @{ */
#define CTRL_START_HDL                               0x8000                                   /**< The start attribute handle of ctrl service. */
/** @} */

/**@brief Definition of BLE Ctrl Service attribute handle */
typedef enum BLE_CTRL_AttributeHandle_T
{
    CTRL_HDL_SVC = CTRL_START_HDL,           /**< Handle of Primary Service. */
    CTRL_HDL_CHAR_0,                            /**< Handle of characteristic 0. */
    CTRL_HDL_CHARVAL_0,                         /**< Handle of characteristic 0 value. */
    CTRL_HDL_CHAR_1,                            /**< Handle of characteristic 1. */
    CTRL_HDL_CHARVAL_1,                         /**< Handle of characteristic 1 value. */
    CTRL_HDL_CCCD_1,                            /**< Handle of characteristic 1 CCCD . */
}BLE_CTRL_AttributeHandle_T;

/**@defgroup BLE_CTRL_ASSIGN_HANDLE BLE_CTRL_ASSIGN_HANDLE
 * @brief Assigned attribute handles of BLE Ctrl Service.
 * @{ */
#define CTRL_END_HDL                                 (CTRL_HDL_CCCD_1)         /**< The end attribute handle of ctrl service. */
/** @} */


// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**
 *@brief Initialize BLE Ctrl Service callback function.
 *
 *
 *@return MBA_RES_SUCCESS                    Successfully register BLE Ctrl service.
 *@return MBA_RES_NO_RESOURCE                Fail to register service.
 *
 */
uint16_t BLE_MobileCtrl_Add(void);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END


#endif

/**
  @}
 */
