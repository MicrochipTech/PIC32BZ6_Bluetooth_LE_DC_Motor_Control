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
  Bluetooth Sys Log Header File

  Company:
    Microchip Technology Inc.

  File Name:
    bt_sys_log.h

  Summary:
    Defines the Bluetooth system logging interface for the application.

  Description:
    This header file declares the interface and data structures used for
    system-level logging of Bluetooth-related events and activities within
    the application. It is intended to provide a consistent logging mechanism
    to aid in debugging and system monitoring.
 *******************************************************************************/

#ifndef BT_SYS_LOG_H
#define BT_SYS_LOG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdbool.h>
#include <stdint.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/**
 * @addtogroup BT_SYS
 * @{
 */

/** 
 * @defgroup BT_SYS_LOG Bluetooth System Log
 * @brief Defines the interface for the BLE System LOG functions provided by the BLE Library.
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**
 * @addtogroup BT_SYS_LOG_ENUMS Enumerations
 * @{
 */

/** @brief Enumerates the types of HCI (Host Controller Interface) logs. */
typedef enum BT_SYS_LogType_T
{
    BT_SYS_LOG_TYPE_HCI_COMMAND = (0x0100U+0x0001U),        /**< HCI Command log type. */
    BT_SYS_LOG_TYPE_HCI_ACL_TX,                             /**< HCI ACL transmit packet log type. */
    BT_SYS_LOG_TYPE_HCI_ACL_RX,                             /**< HCI ACL receive packet log type. */
    BT_SYS_LOG_TYPE_HCI_EVENT,                              /**< HCI Event packet log type. */
    BT_SYS_LOG_TYPE_HCI_END                                 /**< Sentinel value indicating the end of log types. */
} BT_SYS_LogType_T;

/** @} */ //BT_SYS_LOG_ENUMS

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************

/**
 * @addtogroup BT_SYS_LOG_STRUCTS Structures
 * @{
 */

/** @brief Structure for a Bluetooth system log event. */
typedef struct BT_SYS_LogEvent_T
{
    uint16_t      logType;                /**< Type of the log event, indicating the category or source of the event. */
    uint16_t      logId;                  /**< Unique identifier for the log event. When logType corresponds to @ref BT_SYS_LOG_TYPE_HCI_ACL_TX 
                                                or @ref BT_SYS_LOG_TYPE_HCI_ACL_RX data, this represents the connection handle. */
    uint16_t      paramsLength;           /**< Length of the additional parameters associated with the log event. A value of 0 indicates that 
                                                there are no additional parameters. */
    uint16_t      payloadLength;          /**< Length of the payload data for the log event. A value of 0 indicates that there is no payload. */
    uint8_t       *p_logPayload;          /**< Pointer to the payload data. A NULL pointer indicates that there is no payload. */
    uint8_t       *p_returnParams;        /**< Pointer to the additional parameters. A NULL pointer indicates that there are no additional parameters. */
} BT_SYS_LogEvent_T;

/**
 * @brief Callback type for Bluetooth system log events. 
 * 
 * @param p_event       Pointer to the log event structure containing details about the log event. See @ref BT_SYS_LogEvent_T.
*/
typedef void (*BT_SYS_LogEventCb_T)(BT_SYS_LogEvent_T *p_event);


/** @} */ //BT_SYS_LOG_STRUCTS


/**
 * @addtogroup BT_SYS_LOG_FUNS Functions
 * @{
 */

/**
 * @brief Enables logging for Bluetooth system events.
 *
 * @param logCb         A function pointer to the callback that will handle the Bluetooth system log events. 
 *                      The callback should conform to the @ref BT_SYS_LogEventCb_T type definition.
 *
 */
void BT_SYS_LogEnable(BT_SYS_LogEventCb_T logCb);

/** @} */ //BT_SYS_LOG_FUNS

/** @} */

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif//BT_SYS_LOG_H