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
  Error Code Definition Header File

  Company:
    Microchip Technology Inc.

  File Name:
    mba_error_desf.h

  Summary:
    Defines a comprehensive list of error codes used throughout the application.

  Description:
    This header file enumerates all the error codes that are utilized by the
    application for error handling and debugging purposes. Each error code is
    associated with a specific error condition and is intended for use by
    developers to identify and resolve issues more efficiently.
 *******************************************************************************/

#ifndef MBA_ERROR_DEFS_H
#define MBA_ERROR_DEFS_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/** 
 * @addtogroup STACK_MGR
 * @{
 */
 
// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup STACK_DEFINES Defines
 * @{
 */
 
/**
 * @defgroup STACK_ERR_CODE Error code definitions
 * @brief Defines result codes for BLE Stack API operations.
 * @{
 */
#define MBA_RES_SUCCESS                         (0x0000U)                                  /**< Execution completed successfully. */
#define MBA_RES_FAIL                            (0x0001U)                                  /**< Execution fail. */
#define MBA_RES_OOM                             (0x0002U)                                  /**< Out of memory error. */
#define MBA_RES_INVALID_PARA                    (0x0003U)                                  /**< Invalid parameter(s) provided. */
#define MBA_RES_NO_RESOURCE                     (0x0004U)                                  /**< Insufficient resources available. */
#define MBA_RES_BAD_STATE                       (0x0005U)                                  /**< Operation not allowed in the current state. */
#define MBA_RES_PENDING_DUE_TO_SECURITY         (0x0006U)                                  /**< Operation pending due to security procedures. */
#define MBA_RES_BUSY                            (0x0007U)                                  /**< Stack is busy; operation could not be executed. */

#define MBA_RES_UNKNOWN_CONN_ID                 (0x0102U)                                  /**< Connection identifier not recognized. */
#define MBA_RES_AUTHENTICATION_FAILURE          (0x0105U)                                  /**< Authentication process failed. */
#define MBA_RES_PIN_OR_KEY_MISSING              (0x0106U)                                  /**< Required PIN or key is missing. */
#define MBA_RES_CONN_TIMEOUT                    (0x0108U)                                  /**< Connection attempt timed out. */
#define MBA_RES_CONN_ALREADY_EXISTS             (0x010BU)                                  /**< Attempted to establish a connection that already exists.  */
#define MBA_RES_COMMAND_DISALLOWED              (0x010CU)                                  /**< Command is not allowed. */
#define MBA_RES_CONN_REJ_LIMITED_RESOURCES      (0x010DU)                                  /**< Connection rejected due to limited resources. */
#define MBA_RES_CONN_REJ_SECURITY_REASONS       (0x010EU)                                  /**< Connection rejected due to security reasons. */
#define MBA_RES_REMOTE_USER_TERM_CONN           (0x0113U)                                  /**< Connection terminated by the remote user. */
#define MBA_RES_PAIRING_NOT_ALLOWED             (0x0118U)                                  /**< Pairing attempt not allowed. */
#define MBA_RES_UNSUPPORT_REMOTE_FEATURE        (0x011AU)                                  /**< Remote feature not supported. */
#define MBA_RES_INSUFFICIENT_SECURITY           (0x012FU)                                  /**< Security level is insufficient for the operation. */
#define MBA_RES_ADVERTISING_TIMEOUT             (0x013CU)                                  /**< Advertising process timed out. */
#define MBA_RES_CONN_TERM_MIC_FAILURE           (0x013DU)                                  /**< Connection terminated due to MIC (Message Integrity Check) failure. */
#define MBA_RES_UNKNOWN_ADV_ID                  (0x0142U)                                  /**< Advertising identifier not recognized.*/
/** @} */

/** @} */ //STACK_DEFINES

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif//MBA_ERROR_DEFS_H
