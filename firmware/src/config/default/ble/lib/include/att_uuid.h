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
  ATT UUID Header File

  Company:
    Microchip Technology Inc.

  File Name:
    att_uuid.h

  Summary:
    Defines universally unique identifiers (UUIDs) used in the Attribute Protocol
    for BLE (Bluetooth Low Energy) services and characteristics.

  Description:
    This header file lists the UUIDs for standard BLE services, characteristics,
    and descriptors as defined by the Bluetooth SIG. These UUIDs are used for
    identifying attributes in the BLE Attribute Protocol (ATT) and are essential
    for BLE device interoperability.


 *******************************************************************************/
#ifndef ATT_UUID_H
#define ATT_UUID_H

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

/**
 * @addtogroup GATT
 * @{
 */
/**************************************************************************************************
  Macros
**************************************************************************************************/
/**
 * @addtogroup GATT_DEFINES Defines
 * @{
 */
 
/**
 * @defgroup GATT_UUID_DEFS  UUID definitions
 * @brief Definitions of universally unique identifiers (UUIDs) for GATT (Generic Attribute Profile).
 * @{
 */
#define UUID_PRIMARY_SERVICE                                (0x2800U)             /**< UUID for Primary Service Declaration. */
#define UUID_SECONDARY_SERVICE                              (0x2801U)             /**< UUID for Secondary Service Declaration. */
#define UUID_INCLUDE                                        (0x2802U)             /**< UUID for Include Declaration. */
#define UUID_CHARACTERISTIC                                 (0x2803U)             /**< UUID for Characteristic Declaration. */
#define UUID_DESCRIPTOR_CHAR_EXT_PROP                       (0x2900U)             /**< UUID for Characteristic Extended Properties Descriptor. */
#define UUID_DESCRIPTOR_USER_DESC                           (0x2901U)             /**< UUID for Characteristic User Description Descriptor. */
#define UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG                  (0x2902U)             /**< UUID for Client Characteristic Configuration Descriptor. */
#define UUID_DESCRIPTOR_SERVER_CHAR_CONFIG                  (0x2903U)             /**< UUID for Server Characteristic Configuration Descriptor. */
#define UUID_DESCRIPTOR_CHAR_PRE_FORMAT                     (0x2904U)             /**< UUID for Characteristic Presentation Format Descriptor. */
#define UUID_DESCRIPTOR_CHAR_AGGRE_FROMAT                   (0x2905U)             /**< UUID for Characteristic Aggregate Format Descriptor. */
#define UUID_DESCRIPTOR_VALID_RANGE                         (0x2906U)             /**< UUID for Valid Range Descriptor. */
#define UUID_DESCRIPTOR_EXTERNAL_REPORT_REF                 (0x2907U)             /**< UUID for External Report Reference Descriptor. */
#define UUID_DESCRIPTOR_REPORT_REF                          (0x2908U)             /**< UUID for Report Reference Descriptor. */
#define UUID_DESCRIPTOR_NUM_OF_DIGITALS                     (0x2909U)             /**< UUID for Number of Digitals Descriptor. */
#define UUID_DESCRIPTOR_VALUE_TRIGGER_SETTING               (0x290AU)             /**< UUID for Value Trigger Setting Descriptor. */
#define UUID_DESCRIPTOR_ENV_SENSING_CONFIG                  (0x290BU)             /**< UUID for Environmental Sensing Configuration Descriptor. */
#define UUID_DESCRIPTOR_ENV_SENSING_MEASURE                 (0x290CU)             /**< UUID for Environmental Sensing Measurement Descriptor. */
#define UUID_DESCRIPTOR_ENV_SENSING_TRIGGER_SETTING         (0x290DU)             /**< UUID for Environmental Sensing Trigger Setting Descriptor. */
#define UUID_DESCRIPTOR_TIME_TRIGGER_SETTING                (0x290EU)             /**< UUID for Time Trigger Setting Descriptor. */
#define UUID_DESCRIPTOR_COMPLETE_BREDR_BLOCK_DATA           (0x290FU)             /**< UUID for Complete BR-EDR Transport Block Data Descriptor. */
#define UUID_DESCRIPTOR_SIG_DEFINED_RESERVED                (0x29FFU)             /**< Reserved range of UUIDs (0x2900-0x29FF) for SIG-defined descriptors. */
/** @} */


/**
 * @defgroup ATT_UUID_LENGTH_TYPES UUID length
 * @brief Definitions of UUID length types.
 * @{
 */
#define ATT_UUID_LENGTH_2                                   (2U)                  /**< Length of a 16-bit Bluetooth UUID. */
#define ATT_UUID_LENGTH_4                                   (4U)                  /**< Length of a 32-bit Bluetooth UUID. */
#define ATT_UUID_LENGTH_16                                  (0x10U)               /**< Length of a 128-bit Bluetooth UUID.  */
/** @} */


/**
 * @defgroup GATT_MAX_UUID_LENGTH Maximum UUID length
 * @brief  Definition of the maximum UUID length.
 * @{
 */
#define ATT_MAX_UUID_SIZE                                   ATT_UUID_LENGTH_16    /**< Maximum length of a UUID, set to 128 bits. */
/** @} */

/** @} */ //GATT_DEFINES

// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup GATT_DEFINES Defines
 * @{
 */
 
/**
 * @defgroup UUID_ARRAY UUID declaration
 * @brief This section contains the declarations of UUIDs used for GATT service table.
 * @{
 */
extern const uint8_t g_gattUuidPrimSvc[ATT_UUID_LENGTH_2];                      /**< UUID for GATT Primary Service declaration. */
extern const uint8_t g_gattUuidSecSvc[ATT_UUID_LENGTH_2];                       /**< UUID for GATT Secondary Service declaration. */
extern const uint8_t g_gattUuidInc[ATT_UUID_LENGTH_2];                          /**< UUID for GATT Include declaration. */
extern const uint8_t g_gattUuidChar[ATT_UUID_LENGTH_2];                         /**< UUID for GATT Characteristic declaration. */

extern const uint8_t g_descUuidCharExtProp[ATT_UUID_LENGTH_2];                  /**< UUID for GATT Characteristic Descriptor: Characteristic Extended Properties. */
extern const uint8_t g_descUuidUserDesc[ATT_UUID_LENGTH_2];                     /**< UUID for GATT Characteristic Descriptor: Characteristic User Description. */
extern const uint8_t g_descUuidCcc[ATT_UUID_LENGTH_2];                          /**< UUID for GATT Characteristic Descriptor: Client Characteristic Configuration. */
extern const uint8_t g_descUuidScc[ATT_UUID_LENGTH_2];                          /**< UUID for GATT Characteristic Descriptor: Server Characteristic Configuration. */
extern const uint8_t g_descUuidPreFormat[ATT_UUID_LENGTH_2];                    /**< UUID for GATT Characteristic Descriptor: Characteristic Presentation Format. */
extern const uint8_t g_descUuidAggFormat[ATT_UUID_LENGTH_2];                    /**< UUID for GATT Characteristic Descriptor: Characteristic Aggregate Format. */
extern const uint8_t g_descUuidValidRange [ATT_UUID_LENGTH_2];                  /**< UUID for GATT Characteristic Descriptor: Valid Range. */
extern const uint8_t g_descUuidExtReportRef[ATT_UUID_LENGTH_2];                 /**< UUID for GATT Characteristic Descriptor: External Report Reference. */
extern const uint8_t g_descUuidReportRef[ATT_UUID_LENGTH_2];                    /**< UUID for GATT Characteristic Descriptor: Report Reference. */
extern const uint8_t g_descUuidNumOfDigitals[ATT_UUID_LENGTH_2];                /**< UUID for GATT Characteristic Descriptor: Number of Digitals. */
extern const uint8_t g_descUuidValueTriggetSet[ATT_UUID_LENGTH_2];              /**< UUID for GATT Characteristic Descriptor: Value Trigger Setting. */
extern const uint8_t g_descUuidEnvSensingConfig[ATT_UUID_LENGTH_2];             /**< UUID for GATT Characteristic Descriptor: Environmental Sensing Configuration. */
extern const uint8_t g_descUuidEnvSensingMeasure[ATT_UUID_LENGTH_2];            /**< UUID for GATT Characteristic Descriptor: Environmental Sensing Measurement. */
extern const uint8_t g_descUuidEnvSensingTriggerSet[ATT_UUID_LENGTH_2];         /**< UUID for GATT Characteristic Descriptor: Environmental Sensing Trigger Setting. */
extern const uint8_t g_descUuidTimeTriggerSet[ATT_UUID_LENGTH_2];               /**< UUID for GATT Characteristic Descriptor: Time Trigger Setting. */
extern const uint8_t g_descUuidCompleteBredrBlockData[ATT_UUID_LENGTH_2];       /**< UUID for GATT Characteristic Descriptor: Complete BR-EDR Transport Block Data. */
/** @} */

/** @} */ //GATT_DEFINES

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif//ATT_UUID_H
