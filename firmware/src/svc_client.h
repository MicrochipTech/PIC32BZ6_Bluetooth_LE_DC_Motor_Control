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

  Company:
    Microchip Technology Inc.

  File Name:
    ble_svc_client.h

  Summary:
  Garage Door Motor Control Service definitions.
  Description:
 *******************************************************************************/
#ifndef BLE_SVC_C_H
#define BLE_SVC_C_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "stack_mgr.h"
#include "ble_gcm/ble_dd.h"
#include "gatt.h"

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
/**
 * @addtogroup BLE_GDMC_DEFINES Defines
 * @{
 */

/** 
 * @defgroup BLE_GDMC_ERRCODE    GDMC error codes
 * @brief Defines error code for GDMC.
 * @{
 */
#define BLE_GDMC_ERRCODE_COMMAND_NOT_SUPPORTTED     (0xA0U)     /**< Error code for unsupported command.*/
/** @} */




/** 
 * @defgroup BLE_GDMC_DESC_MAX_NUM   GDMC maximum descriptor count
 * @brief Defines the maximum number of descriptors.
 * @{ 
 */
#define BLE_GDMC_DESC_MAX_NUM 						(2U)	    /**< Maximum number of descriptors allowed. */
/** @} */





/** 
 * @defgroup BLE_GDMC_UUID    UUIDs of characteristics in Alert Notification profile
 * @brief UUIDs for characteristics used within the Alert Notification Service.
 * @{
 */
#define BLE_GDMC_UUID_SERVICE                         (0xCD01U)   /**< UUID GDMC Service. */
#define BLE_GDMC_UUID_CONTROL                         (0xCD02U)   /**< UUID for Control characteristic. */
/** @} */
/** @} */ //BLE_GDMC_DEFINES

/** 
 * @addtogroup BLE_GDMC_ENUMS Enumerations
 * @{ 
 */


/**@} */ //BLE_GDMC_ENUMS

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/** 
 * @addtogroup BLE_GDMC_STRUCTS Structures
 * @{
 */

/** @brief Structure for the @ref BLE_GDMC_EVT_DISC_COMPLETE_IND event. */
typedef struct BLE_GDMC_EvtDiscComplete_T
{
    uint16_t            connHandle;             /**< Connection handle associated with the discovery completion. */
    uint16_t            gdmcStartHandle;         /**< Start handle of the discovered GDMC. */
    uint16_t            gdmcEndHandle;           /**< End handle of the discovered GDMC. */
}BLE_GDMC_EvtDiscComplete_T;




/** @brief Structure representing the characteristic list. */
typedef struct BLE_GDMC_CharList_T
{
    uint16_t            attrHandle;             /**< Attribute handle of the characteristic. */
    uint8_t             property;               /**< Properties of the characteristic. */
    uint16_t            charHandle;             /**< Handle of the characteristic. */
}BLE_GDMC_CharList_T;


/** @brief Structure representing descriptor information. */
typedef struct BLE_GDMC_DescInfo_T
{
    uint16_t            attrHandle;             /**< Attribute handle of the descriptor. */
    uint16_t            uuid;                   /**< UUID of the descriptor. */
}BLE_GDMC_DescInfo_T;


/** @brief Structure representing the descriptor list. */
typedef struct BLE_GDMC_DescList_T
{
    uint8_t 		    totalNum;  		        /**< Total number of descriptors discovered. */
    BLE_GDMC_DescInfo_T descInfo[BLE_GDMC_DESC_MAX_NUM]; /**< Array of discovered descriptor information.*/
}BLE_GDMC_DescList_T;


/** @brief Union of BLE Alert Notification Client callback event data types. */
typedef union
{
    BLE_GDMC_EvtDiscComplete_T           evtDiscComplete;          /**< Data for the @ref BLE_GDMC_EVT_DISC_COMPLETE_IND event. */
}BLE_GDMC_EventField_T;





/**@} */ //BLE_GDMC_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/** 
 * @addtogroup BLE_GDMC_FUNS Functions
 * @{
 */

/**
 * @brief Initializes BLE Alert Notification Client.
 *
 * @retval MBA_RES_SUCCESS          The client was successfully initialized.
 * @retval MBA_RES_FAIL             The client failed to initialize.
 */
uint16_t BLE_GDMC_Init(void);



/**
 * @brief Enables or disables notifications for Control Characteristic.
 *
 * @param[in] connHandle            The connection handle to identify the BLE connection.
 * @param[in] enable                Set to true to enable notifications; false to disable.
 *
 * @retval MBA_RES_SUCCESS          The operation was successful.
 * @retval MBA_RES_INVALID_PARA     The connection handle is invalid.
 * @retval MBA_RES_OOM              Internal memory allocation failure.
 */
uint16_t BLE_GDMC_EnableControlNtfy(uint16_t connHandle, bool enable);


/**
 * @brief Retrieves a list of discovered Alert Notification service characteristics.
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
uint16_t BLE_GDMC_GetCharList(uint16_t connHandle, uint16_t charUuid, BLE_GDMC_CharList_T *p_charList);


/**
 * @brief Retrieves a list of descriptors within the Alert Notification Service.
 * 
 * @note This function should be called after the BLE_GDMC_EVT_DISC_COMPLETE_IND event.
 *
 * @param[in]  connHandle           The connection handle to identify the BLE connection.
 * @param[out] p_descList           On success, filled with the discovered descriptors info.
 *
 * @retval MBA_RES_SUCCESS          The descriptor list was successfully retrieved.
 * @retval MBA_RES_INVALID_PARA     The connection handle is invalid.
 */
uint16_t BLE_GDMC_GetDescList(uint16_t connHandle, BLE_GDMC_DescList_T *p_descList);


/**
 * @brief Handles BLE_Stack events.
 * 
 * @note This function should be called when BLE stack events occur.
 * 
 * @param[in] p_stackEvent          Pointer to the stack event structure.
 *
*/
void BLE_GDMC_BleEventHandler(STACK_Event_T *p_stackEvent);


/**
 * @brief Handles BLE Database Discovery (BLE_DD) events.
 *
 * @note This function should be called when BLE_DD events occur.
 * 
 * @param[in] p_event               Pointer to the BLE DD event structure.
 *
*/
void BLE_GDMC_BleDdEventHandler(BLE_DD_Event_T *p_event);

/**@} */ //BLE_GDMC_FUNS

/** @} */

/** @} */

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif//BLE_GDMC_H