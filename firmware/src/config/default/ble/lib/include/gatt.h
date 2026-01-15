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
  GATT Header File

  Company:
    Microchip Technology Inc.

  File Name:
    gatt.h

  Summary:
    Interface for the GATT functionalities provided by the BLE stack.

  Description:
    This header file exposes the GATT Server (GATTS) and GATT Client (GATTC)
    functions to the application layer. It allows the application to interact
    with the BLE stack for operations related to attributes, services, and
    characteristics. To initialize the GATT module, the application should
    invoke "BLE_GATTS_Init" for server roles or "BLE_GATTC_Init" for client
    roles within the "APP_Initialize" function during system startup.
 *******************************************************************************/
#ifndef GATT_H
#define GATT_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "att_uuid.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/**
 * @defgroup GATT Generic Attribute Profile (GATT)
 * @brief Defines the interface for the GATT functions provided by the BLE Library.
 * @note  This header file contains the definitions, types, and function prototypes necessary
 * to interface with the GATT layer of the BLE stack. It enables the creation, management,
 * and use of GATT services and characteristics, which are essential for BLE communication.
 * @{
 */
// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**
 * @addtogroup GATT_DEFINES Defines
 * @{
 */
 
 
/**
 * @defgroup GATT_EXEC_WRITE_FLAGS Execute write flags
 * @brief Defines the flags for Execute Write Request operations.
 * @{
 */
#define GATT_EXEC_WRITE_FLAG_CANCEL_ALL                     (0x00U)                /**< Cancel all prepared writes. */
#define GATT_EXEC_WRITE_FLAG_WRITE                          (0x01U)                /**< Writes all pending prepared values immediately. */
#define GATT_EXEC_WRITE_FLAG_INTERNAL_CANCEL                (0x02U)                /**< Cancels all prepared writes due to an internal error. */
/** @} */


/**
 * @defgroup BLE_GATT_MTU_LENGTH MTU length
 * @brief Defines the GATT MTU length.
 * @{
 */
#define BLE_ATT_DEFAULT_MTU_LEN                             (23U)                  /**< Default MTU length for ATT protocol.  */
#define BLE_ATT_MAX_MTU_LEN                                 (247U)                 /**< Maximum supported MTU length by the ATT protocol. */
/** @} */


/**
 * @defgroup GATT_HEADER_SIZE GATT Header size
 * @brief Defines GATT header sizes for various operations.
 * @{
 */
#define ATT_HANDLE_VALUE_HEADER_SIZE                        (3U)                   /**< Header size for ATT Handle Value Notification/Indication. */
#define ATT_WRITE_HEADER_SIZE                               (3U)                   /**< Header size for ATT Write Request/Command. */
#define ATT_READ_RESP_HEADER_SIZE                           (1U)                   /**< Header size for ATT Read Response. */
#define ATT_WRITE_RESP_HEADER_SIZE                          (5U)                   /**< Header size for ATT Prepare Write Response. */
#define ATT_FIND_INFO_RESP_HEADER_SIZE                      (2U)                   /**< Header size for ATT Find Information Response. */
#define ATT_FIND_BY_TYPE_RESP_HEADER_SIZE                   (1U)                   /**< Header size for ATT Find By Type Value Response. */
#define ATT_READ_BY_TYPE_RESP_HEADER_SIZE                   (2U)                   /**< Header size for ATT Read By Type Response. */
#define ATT_READ_BY_GROUP_RESP_HEADER_SIZE                  (2U)                   /**< Header size for ATT Read By Group Type Response. */
#define ATT_PREP_WRITE_RESP_HEADER_SIZE                     (5U)                   /**< Header size for ATT Prepare Write Response. */
#define ATT_NOTI_INDI_HEADER_SIZE                           (3U)                   /**< Header size for ATT Notification/Indication. */
/** @} */


/**
 * @defgroup GATTC_CONFIGURATION_BITS GATT client configuration definitions
 * @brief Defines GATT Client configuration bits.
 * @{
 */
#define GATTC_CONFIG_NONE                                   (0x0000U)              /**< No configuration for any supported functions. */
#define GATTC_CONFIG_MANUAL_CONFIRMATION                    (0x0001U)              /**< Bit 0: Configures ATT stack for manual confirmation of received indications. */
/** @} */


/**
 * @defgroup GATTS_CONFIGURATION_BITS GATT server configuration definitions
 * @brief Defines GATT Server configuration bits.
 * @{
 */
#define GATTS_CONFIG_NONE                                   (0x0000U)              /**< No configuration for any supported functions. */
#define GATTS_CONFIG_CACHING_SUPPORT                        (0x0001U)              /**< Bit 0: Enables caching support on the GATT Server. \n
                                                                                        If caching is enabled, the API @ref GATTS_UpdateBondingInfo 
                                                                                        must be called after a link is established. Failure to do so will result in 
                                                                                        the GATT Server not processing incoming packets. */
/** @} */


/**
 * @defgroup ATT_ERROR_CODES  ATT error codes
 * @brief Defines ATT (Attribute Protocol) error codes used in BLE communication.
 * @{
 */
#define ATT_ERR_INVALID_HANDLE                              (0x01U)                /**< Error Code: The attribute handle given was not valid on this server. */
#define ATT_ERR_READ_NOT_PERMITTED                          (0x02U)                /**< Error Code: The attribute cannot be read. */
#define ATT_ERR_WRITE_NOT_PERMITTED                         (0x03U)                /**< Error Code: The attribute cannot be written. */
#define ATT_ERR_INVALID_PDU                                 (0x04U)                /**< Error Code: The attribute PDU was invalid. */
#define ATT_ERR_INSUF_AUTHN                                 (0x05U)                /**< Error Code: The attribute requires authentication before it can be read or written. */
#define ATT_ERR_REQUEST_NOT_SUPPORT                         (0x06U)                /**< Error Code: Attribute server does not support the request received from the client. */
#define ATT_ERR_INVALID_OFFSET                              (0x07U)                /**< Error Code: Offset specified was past the end of the attribute. */
#define ATT_ERR_INSUF_AUTHZ                                 (0x08U)                /**< Error Code: The attribute requires authorization before it can be read or written. */
#define ATT_ERR_PREPARE_QUEUE_FULL                          (0x09U)                /**< Error Code: Too many prepare writes have been queued. */
#define ATT_ERR_ATTRIBUTE_NOT_FOUND                         (0x0aU)                /**< Error Code: No attribute found within the given attribute handle range. */
#define ATT_ERR_ATTRIBUTE_NOT_LONG                          (0x0bU)                /**< Error Code: The attribute cannot be read or written using the Read Blob Request. */
#define ATT_ERR_INSUF_ENC_KEY_SIZE                          (0x0cU)                /**< Error Code: The Encryption Key Size used for encrypting this link is insufficient. */
#define ATT_ERR_INVALID_ATTRIBUTE_VALUE_LENGTH              (0x0dU)                /**< Error Code: The attribute value length is invalid for the operation. */
#define ATT_ERR_UNLIKELY_ERROR                              (0x0eU)                /**< Error Code: The attribute request that was requested has encountered an error that 
                                                                                                        was unlikely, and therefore could not be completed as requested. */
#define ATT_ERR_INSUF_ENC                                   (0x0fU)                /**< Error Code: The attribute requires encryption before it can be read or written. */
#define ATT_ERR_UNSUPPORTED_GROUP_TYPE                      (0x10U)                /**< Error Code: The attribute type is not a supported grouping attribute as defined 
                                                                                                        by a higher layer specification. */
#define ATT_ERR_INSUF_RESOURCE                              (0x11U)                /**< Error Code: Insufficient Resources to complete the request. */
#define ATT_ERR_DATABASE_OUT_OF_SYNC                        (0x12U)                /**< Error Code: The server requires the client to rediscover the database. */
#define ATT_ERR_VALUE_NOT_ALLOW                             (0x13U)                /**< Error Code: The attribute value is not allowed. */
#define ATT_ERR_APPLICATION_ERROR                           (0x80U)                /**< Error Code: The application has set this error code. */
/** @} */


/**
 * @defgroup ATT_OPCODES ATT opcodes
 * @brief Defines ATT (Attribute Protocol) opcodes used in BLE communication.
 * @{
 */
#define ATT_ERROR_RSP                                       (0x01U)                /**< Opcode for Error Response. */
#define ATT_EXCHANGE_MTU_REQ                                (0x02U)                /**< Opcode for Exchange MTU Request. */
#define ATT_EXCHANGE_MTU_RSP                                (0x03U)                /**< Opcode for Exchange MTU Response. */
#define ATT_FIND_INFORMATION_REQ                            (0x04U)                /**< Opcode for Find Information Request. */
#define ATT_FIND_INFORMATION_RSP                            (0x05U)                /**< Opcode for Find Information Response. */
#define ATT_FIND_BY_TYPE_VALUE_REQ                          (0x06U)                /**< Opcode for Find By Type Value Request. */
#define ATT_FIND_BY_TYPE_VALUE_RSP                          (0x07U)                /**< Opcode for Find By Type Value Response. */
#define ATT_READ_BY_TYPE_REQ                                (0x08U)                /**< Opcode for Read By Type Request. */
#define ATT_READ_BY_TYPE_RSP                                (0x09U)                /**< Opcode for Read By Type Response. */
#define ATT_READ_REQ                                        (0x0aU)                /**< Opcode for Read Request. */
#define ATT_READ_RSP                                        (0x0bU)                /**< Opcode for Read Response. */
#define ATT_READ_BLOB_REQ                                   (0x0cU)                /**< Opcode for Read Blob Request. */
#define ATT_READ_BLOB_RSP                                   (0x0dU)                /**< Opcode for Read Blob Response. */
#define ATT_READ_MULTIPLE_REQ                               (0x0eU)                /**< Opcode for Read Multiple Request. */
#define ATT_READ_MULTIPLE_RSP                               (0x0fU)                /**< Opcode for Read Multiple Response. */
#define ATT_READ_BY_GROUP_TYPE_REQ                          (0x10U)                /**< Opcode for Read By Group Type Request. */
#define ATT_READ_BY_GROUP_TYPE_RSP                          (0x11U)                /**< Opcode for Read By Group Type Response. */
#define ATT_WRITE_REQ                                       (0x12U)                /**< Opcode for Write Request. */
#define ATT_WRITE_RSP                                       (0x13U)                /**< Opcode for Write Response. */
#define ATT_WRITE_CMD                                       (0x52U)                /**< Opcode for Write Command. */
#define ATT_PREPARE_WRITE_REQ                               (0x16U)                /**< Opcode for Prepare Write Request. */
#define ATT_PREPARE_WRITE_RSP                               (0x17U)                /**< Opcode for Prepare Write Response. */
#define ATT_EXECUTE_WRITE_REQ                               (0x18U)                /**< Opcode for Execute Write Request. */
#define ATT_EXECUTE_WRITE_RSP                               (0x19U)                /**< Opcode for Execute Write Response. */
#define ATT_HANDLE_VALUE_NTF                                (0x1bU)                /**< Opcode for Handle Value Notification. */
#define ATT_HANDLE_VALUE_IND                                (0x1dU)                /**< Opcode for Handle Value Indication. */
#define ATT_HANDLE_VALUE_CFM                                (0x1eU)                /**< Opcode for Handle Value Confirmation. */
#define ATT_READ_MUTIPLE_VARIABLE_REQ                       (0x20U)                /**< Opcode for Read Multiple Variable Request. */
#define ATT_READ_MUTIPLE_VARIABLE_RSP                       (0x21U)                /**< Opcode for Read Multiple Variable Response. */
#define ATT_MUTIPLE_HANDLE_VALUE_NTF                        (0x22U)                /**< Opcode for Multiple Handle Value Notification. */
#define ATT_SIGNED_WRITE_COMMAND                            (0xd2U)                /**< Opcode for Signed Write Command. */
/** @} */


/**
 * @defgroup GATT_PROCEDURE_STATUS  Procedure status
 * @brief Represents the status of a GATT procedure.
 * @note GATT procedures may span multiple ATT requests, resulting in multiple events for a single 
 *          procedure. The status within an event indicates whether the procedure is ongoing or has concluded.
 * @{
 */
#define GATT_PROCEDURE_STATUS_CONTINUE                      (0x00U)                /**< Querying procedure continues. Further events will be received. */
#define GATT_PROCEDURE_STATUS_FINISH                        (0x01U)                /**< Querying procedure is complete. Last event of this procedure. */
/** @} */


/**
 * @defgroup GATT_CLIENT_FEATURE GATT client features
 * @brief Defines the features supported by a GATT client as indicated in the Client Supported 
 *          Features characteristic.
 * @{
 */
#define GATT_ROBUST_CACHING                                 (0x01U)                /**< Indicates support for robust caching by the client. */
#define GATT_EATT_BEARER                                    (0x02U)                /**< Indicates support for Enhanced ATT (EATT) bearer by the client. */
#define GATT_MULTI_HANDLE_NOTI                              (0x04U)                /**< Indicates support for multiple handle value notifications by the client. */
/** @} */


/**
 * @defgroup GATT_ATTRIBUTE_PERMISSIONS Attribute permissions
 * @brief Defines the attribute permissions.
 * @{
 */
#define PERMISSION_READ                                     (0x01U)                /**< Read access is permitted. */
#define PERMISSION_READ_AUTHEN                              (0x02U)                /**< Read access requires authenticated encryption with MITM (Man-In-The-Middle) protection. */
#define PERMISSION_READ_AUTHEN_SC                           (0x04U)                /**< Read access requires LE Secure Connections with authenticated encryption and MITM protection. */
#define PERMISSION_READ_ENC                                 (0x08U)                /**< Read access requires encryption without MITM protection. */
#define PERMISSION_WRITE                                    (0x10U)                /**< Write access is permitted. */
#define PERMISSION_WRITE_AUTHEN                             (0x20U)                /**< Write access requires authenticated encryption with MITM protection. */
#define PERMISSION_WRITE_AUTHEN_SC                          (0x40U)                /**< Write access requires LE Secure Connections with authenticated encryption and MITM protection. */
#define PERMISSION_WRITE_ENC                                (0x80U)                /**< Write access requires encryption without MITM protection. */
/** @} */


/**
 * @defgroup GATT_ATTRIBUTE_SETTINGS Attribute settings
 * @brief Defines the attribute settings.
 * @{
*/
#define SETTING_MANUAL_WRITE_RSP                            (0x01U)                /**< Set if the service needs to be informed of write operations on this attribute. 
                                                                                        The service also needs to send a response manually if required. */
#define SETTING_MANUAL_READ_RSP                             (0x02U)                /**< Set if the service needs to be informed of read operations on this attribute. 
                                                                                        The service also needs to send a response manually. */
#define SETTING_UUID_16                                     (0x04U)                /**< Set if the UUID is 16 bytes (128 bits) in length. */
#define SETTING_VARIABLE_LEN                                (0x08U)                /**< Set if the attribute has a variable length value. */
#define SETTING_ALLOW_OFFSET                                (0x10U)                /**< Set if the attribute allows write operations with an offset. */
#define SETTING_CCCD                                        (0x20U)                /**< Set if the attribute is a Client Characteristic Configuration Descriptor (CCCD). */
/** @} */


/**
 * @defgroup GATT_CHARACTERISTIC_PROPERTIES Characteristic properties
 * @brief Defines properties in Characteristic declarations.
 * @{
 */
#define ATT_PROP_BROADCAST                                  (0x01U)                /**< If set, broadcasting of the Characteristic Value is permitted using 
                                                                                        the Server Characteristic Configuration Descriptor. */
#define ATT_PROP_READ                                       (0x02U)                /**< If set, reading the Characteristic Value is permitted. */
#define ATT_PROP_WRITE_CMD                                  (0x04U)                /**< If set, writing the Characteristic Value without response is permitted. */
#define ATT_PROP_WRITE_REQ                                  (0x08U)                /**< If set, writing the Characteristic Value with response is permitted. */
#define ATT_PROP_NOTIFY                                     (0x10U)                /**< If set, notifying the Characteristic Value without acknowledgement is permitted. */
#define ATT_PROP_INDICATE                                   (0x20U)                /**< If set, indicating the Characteristic Value with acknowledgement is permitted. */
#define ATT_PROP_AUTH_WRITES                                (0x40U)                /**< If set, signed writes to the Characteristic Value are permitted. */
#define ATT_PROP_EXTENDED_PROP                              (0x80U)                /**< If set, additional properties are defined in the Characteristic Extended Properties Descriptor. */
/** @} */


/**
 * @defgroup GATT_CHARACTERISTIC_EXTENDED_PROPERTIES Characteristic extended properties
 * @brief Defines the Characteristic Extended Properties bit field.
 * @{
 */
#define RELIABLE_WRITE                                      (0x0001U)              /**< If set, reliable writes to the Characteristic Value are permitted. */
#define WRITABLE_AUXILIARIES                                (0x0002U)              /**< If set, writing to the Characteristic Descriptors is permitted. */
/** @} */


/**
 * @defgroup GATT_CCCD_BITS Client Characteristic Configuration definitions
 * @brief Defines the Client Characteristic Configuration bit field.
 * @{
 */
#define NOTIFICATION                                        (0x0001U)              /**< If set, the Characteristic Value shall be notified. */
#define INDICATION                                          (0x0002U)              /**< If set, the Characteristic Value shall be indicated. */
/** @} */


/**
 * @defgroup GATT_SCCD_BITS Server Characteristic Configuration definitions
 * @brief Defines the Server Characteristic Configuration bit field.
 * @{
 */
#define SCCD_BROADCAST                                      (0x0001U)              /**< If set, the Characteristic Value shall be broadcast. */
/** @} */


/**
 * @defgroup GATT_DB_CHANGE_STATE GATT database change state
 * @brief Defines the state of the GATT server's database with respect 
 *          to its awareness of changes for a specific client.
 * @{
 */
#define GATT_DB_CHANGE_AWARE                                (0x00U)                /**< Indicates that the GATT database is aware of changes for a specific client. */
#define GATT_DB_CHANGE_UNAWARE                              (0x01U)                /**< Indicates that the GATT database is not aware of changes for a specific client. */
/** @} */


/**
 * @defgroup GATTS_APP_SVC_START_HDL Application service start handle
 * @brief Defines the starting handle value for application-registered services.
 * @note  Application-defined services should have a starting handle greater than this value.
 * @{
 */
#define GATTS_APP_ATTRIBUTE_START_HANDLE                    (0x0050U)              /**< The starting handle for application-defined services. */
/** @} */


/** @} */ //GATT_DEFINES

/**
 * @addtogroup GATT_ENUMS Enumerations
 * @{
 */
 
/**
 * @brief Enumeration type of GATT callback events.
 * @note    - Events with "GATTC" in EventID are generated on GATT Client.\n
 *          - Events with "GATTS" are generated on GATT Server.\n
 *          - Events without a specific prefix may be generated on either the GATT Client or Server side.\n
 */
typedef enum GATT_EventId_T
{
    GATTC_EVT_ERROR_RESP = 0x00U,                                               /**< Error Response Event. See @ref GATT_EvtError_T for event details. */
    GATTC_EVT_DISC_PRIM_SERV_RESP,                                              /**< Discover Primary Services Response Event. See @ref GATT_EvtDiscPrimServResp_T for event details. */
    GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP,                                      /**< Discover Primary Services By UUID Response Event. See @ref GATT_EvtDiscPrimServByUuidResp_T for event details. */
    GATTC_EVT_DISC_CHAR_RESP,                                                   /**< Discover All Characteristics Response Event. See @ref GATT_EvtDiscCharResp_T for event details. */
    GATTC_EVT_DISC_DESC_RESP,                                                   /**< Discover All Descriptors Response Event. See @ref GATT_EvtDiscDescResp_T for event details. */
    GATTC_EVT_READ_USING_UUID_RESP,                                             /**< Read Using UUID Response Event. See @ref GATT_EvtReadUsingUuidResp_T for event details. */
    GATTC_EVT_READ_RESP,                                                        /**< Read Response Event. See @ref GATT_EvtReadResp_T for event details. */
    GATTC_EVT_WRITE_RESP,                                                       /**< Write Response Event. See @ref GATT_EvtWriteResp_T for event details. */
    GATTC_EVT_HV_NOTIFY,                                                        /**< Handle Value Notification Event. See @ref GATT_EvtReceiveHandleValue_T for event details. */
    GATTC_EVT_HV_INDICATE,                                                      /**< Handle Value Indication Event. See @ref GATT_EvtReceiveHandleValue_T for event details. */
    GATTS_EVT_READ,                                                             /**< Read Request Event. See @ref GATT_EvtRead_T for event details. */
    GATTS_EVT_WRITE,                                                            /**< Write Request or Command Event. See @ref GATT_EvtWrite_T for event details. */
    GATTS_EVT_HV_CONFIRM,                                                       /**< Handle Value Confirmation Event. See @ref GATT_EvtReceiveCfm_T for event details. */
    ATT_EVT_TIMEOUT,                                                            /**< ATT Stack Timeout Event. */
    ATT_EVT_UPDATE_MTU,                                                         /**< Update MTU Event. See @ref GATT_EvtUpdateMtu_T for event details. */
    GATTC_EVT_DISC_CHAR_BY_UUID_RESP,                                           /**< Discover Characteristics By UUID Response Event. See @ref GATT_EvtDiscCharResp_T for event details. */
    GATTS_EVT_SERVICE_CHANGE,                                                   /**< Service change state for a specific bonded client. This information must 
                                                                                        be kept permanently for the bonded client. See @ref GATT_EvtServiceChange_T for event details. */
    GATTS_EVT_CLIENT_FEATURE_CHANGE,                                            /**< Client Support feature changed by a specific bonded client. This information must be kept 
                                                                                        permanently for the bonded client. See @ref GATT_EvtClientFeatureChange_T for event details. */
    GATTS_EVT_CLIENT_CCCDLIST_CHANGE,                                           /**< CCCD values changed by a specific bonded client. This information must be kept permanently 
                                                                                        for the bonded client. See @ref GATT_EvtClientCccdListChange_T for event details. */
    GATTC_EVT_PROTOCOL_AVAILABLE,                                               /**< Sequential protocol available in client role. See @ref GATT_EvtProtocolAvailable_T for event details. */
    GATTS_EVT_PROTOCOL_AVAILABLE,                                               /**< Sequential protocol available in server role. See @ref GATT_EvtProtocolAvailable_T for event details. */

    GATTS_EVT_ENC_DATA_KEY_MATL_REQ                                             /**< Peer request to read encrypted data key material. See @ref GATT_EvtEncDataKeyMatlReq_T for the event details.*/
} GATT_EventId_T;

/** @} */ //GATT_ENUMS

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup GATT_STRUCTS Structures
 * @{
 */
 
/** @brief Structure for a GATT Write Request. */
typedef struct GATTC_WriteParams_T
{
    uint16_t            charHandle;                                                 /**< Characteristic handle to write to. */
    uint16_t            charLength;                                                 /**< Length of the characteristic data to write. Refer to the size of charValue for maximum value. */
    uint8_t             charValue[BLE_ATT_MAX_MTU_LEN - ATT_WRITE_HEADER_SIZE];     /**< Buffer containing the data to write. */
    uint8_t             writeType;                                                  /**< Write operation type. Valid values are defined in @ref ATT_OPCODES 
                                                                                        (e.g., ATT_WRITE_REQ, ATT_WRITE_CMD, etc.). */
    uint16_t            valueOffset;                                                /**< Offset for the data to be written. Use 0 for normal writes, or specify an 
                                                                                            offset for prepare write requests. */
    uint8_t             flags;                                                      /**< Flags for the write operation, used only with writeType is 
                                                                                        ATT_EXECUTE_WRITE_REQ (see @ref GATT_EXEC_WRITE_FLAGS). Otherwise, set to 0. */
} GATTC_WriteParams_T;


/** @brief Structure for discovering a primary service by UUID. */
typedef struct GATTC_DiscoverPrimaryServiceParams_T
{
    uint16_t            startHandle;                                                /**< Starting handle for the service discovery range. */
    uint16_t            endHandle;                                                  /**< Ending handle for the service discovery range. */
    uint8_t             valueLength;                                                /**< Length of the service UUID. Use 2 for 16-bit UUIDs and 16 for 128-bit UUIDs. */
    uint8_t             value[ATT_MAX_UUID_SIZE];                                   /**< Service UUID to discover, in little-endian format. */
} GATTC_DiscoverPrimaryServiceParams_T;


/** @brief Structure for discovering characteristics by UUID. */
typedef struct GATTC_DiscoverCharacteristicByUuidParams_T
{
    uint16_t            startHandle;                                                /**< Starting handle for the characteristic discovery range. */
    uint16_t            endHandle;                                                  /**< Ending handle for the characteristic discovery range. */
    uint8_t             uuidLength;                                                 /**< Length of the characteristic UUID. */
    uint8_t             uuid[ATT_MAX_UUID_SIZE];                                    /**< Characteristic UUID to discover, in little-endian format. */
} GATTC_DiscoverCharacteristicByUuidParams_T;


/** @brief Structure for a GATT Read By Type Request. */
typedef struct GATTC_ReadByTypeParams_T
{
    uint16_t            startHandle;                                                /**< Starting handle for the read operation. */
    uint16_t            endHandle;                                                  /**< Ending handle for the read operation. */
    uint8_t             attrTypeLength;                                             /**< Length of the attribute type UUID. Use 2 for 16-bit UUIDs and 16 for 128-bit UUIDs. */
    uint8_t             attrType[ATT_MAX_UUID_SIZE];                                /**< Attribute type UUID to read, in little-endian format. */
} GATTC_ReadByTypeParams_T;


/** @brief Structure for sending a GATT Handle Value Notification or Indication. */
typedef struct GATTS_HandleValueParams_T
{
    uint16_t            charHandle;                                                 /**< Characteristic handle for the notification or indication. */
    uint16_t            charLength;                                                 /**< Length of the characteristic data to be sent. Maximum is limited 
                                                                                        by the array size of charValue[]. */
    uint8_t             charValue[BLE_ATT_MAX_MTU_LEN - ATT_HANDLE_VALUE_HEADER_SIZE];  /**< Data buffer containing the characteristic value for notification or indication. */
    uint8_t             sendType;                                                   /**< Type of operation (notification or indication) as defined in 
                                                                                        @ref ATT_OPCODES (ATT_HANDLE_VALUE_NTF or ATT_HANDLE_VALUE_IND). */
} GATTS_HandleValueParams_T;


/** @brief Structure for sending a GATT Read Response. */
typedef struct GATTS_SendReadRespParams_T
{
    uint16_t            attrLength;                                                 /**< Length of the attribute data to be sent in the read response. */
    uint8_t             responseType;                                               /**< Type of read response as defined in @ref ATT_OPCODES (ATT_READ_RSP or ATT_READ_BLOB_RSP). */
    uint8_t             attrValue[BLE_ATT_MAX_MTU_LEN - ATT_READ_RESP_HEADER_SIZE]; /**< Data buffer containing the attribute value for the read response. */
} GATTS_SendReadRespParams_T;


/** @brief Structure for sending a GATT Error Response. */
typedef struct GATTS_SendErrRespParams_T
{
    uint8_t             reqOpcode;                                                  /**< Opcode of the request that resulted in this error response, as defined in @ref ATT_OPCODES. */
    uint8_t             errorCode;                                                  /**< Error code explaining the reason for the error, as defined in @ref ATT_ERROR_CODES. */
    uint16_t            attrHandle;                                                 /**< Handle of the attribute related to this error response. */
} GATTS_SendErrRespParams_T;


/** @brief Structure for sending a GATT Read By Type Response. */
typedef struct GATTS_SendReadByTypeRespParams_T
{
    uint16_t            allPairsLength;                                             /**< Total length of all handle-value pairs included in the response. */
    uint8_t             eachPairLength;                                             /**< Length of a single handle-value pair. The response may include multiple pairs of the same length. */
    uint8_t             attrDataList[BLE_ATT_MAX_MTU_LEN - ATT_READ_BY_TYPE_RESP_HEADER_SIZE];  /**< Buffer containing the list of handle-value pairs 
                                                                                                        in little-endian format to be sent to the client. */
} GATTS_SendReadByTypeRespParams_T;


/** @brief Structure for sending a GATT Write Response. */
typedef struct GATTS_SendWriteRespParams_T
{
    uint8_t             responseType;                                               /**< Type of write response, see @ref ATT_OPCODES. Valid values 
                                                                                        are ATT_WRITE_RSP, ATT_PREPARE_WRITE_RSP, and ATT_EXECUTE_WRITE_RSP. */
    uint16_t            attrHandle;                                                 /**< Attribute handle for which the write response is sent. Relevant for Prepare Write Response. */
    uint16_t            valueOffset;                                                /**< Offset of the data written. Relevant for Prepare Write Response. */
    uint16_t            writeLength;                                                /**< Length of the data written. Should match the length in the corresponding Prepare Write Request. */
    uint8_t             writeValue[BLE_ATT_MAX_MTU_LEN - ATT_WRITE_RESP_HEADER_SIZE];   /**< Data written to the attribute. Should match the data in the corresponding Prepare Write Request. */
} GATTS_SendWriteRespParams_T;


/** @brief Structure for Client Characteristic Configuration Descriptor (CCCD). */
typedef struct GATTS_CccdSetting_T
{
    uint16_t            attrHandle;                                                 /**< Handle of the CCCD attribute. */
    uint16_t            acceptableValue;                                            /**< Acceptable value for the CCCD to enable notifications or indications. */
} GATTS_CccdSetting_T;


/** @brief List of CCCD values for multiple characteristics. */
typedef struct GATTS_CccdList_T
{
    uint16_t            attrHandle;                                                 /**< Handle of the CCCD attribute. */
    uint16_t            cccdValue;                                                  /**< Current value of the CCCD. */
} GATTS_CccdList_T;


/** @brief Structure for bonding information. */
typedef struct GATTS_BondingParams_T
{
    uint8_t             serviceChange;                                              /**< Indicates the service change state. Refer to @ref GATT_DB_CHANGE_STATE for valid value. */
    uint8_t             clientSupportFeature;                                       /**< Indicates supported features of the client, such as reliable writes. 
                                                                                            Refer to @ref GATT_CLIENT_FEATURE for valid value.*/
} GATTS_BondingParams_T;


/** @brief Structure representing a GATT attribute. */
typedef struct GATTS_Attribute_T
{
    uint8_t             *p_uuid;                                                    /**< Pointer to the UUID of the attribute. */
    uint8_t             *p_value;                                                   /**< Pointer to the value of the attribute. */
    uint16_t            *p_len;                                                     /**< Pointer to the length of the attribute's value. */
    uint16_t            maxLen;                                                     /**< Maximum length that the attribute's value can take. */
    uint8_t             settings;                                                   /**< Settings for the attribute, defining how it can be used. Refer
                                                                                            to @ref GATT_ATTRIBUTE_SETTINGS for valid value. */
    uint8_t             permissions;                                                /**< Permissions for the attribute, defining access rights. Refer to 
                                                                                            @ref GATT_ATTRIBUTE_PERMISSIONS for valid value.*/
} GATTS_Attribute_T;


/** @brief Structure for a GATT service with its attributes and handles. */
typedef struct GATTS_Service_T
{
    struct GATTS_Service_T          *p_next;                                        /**< Pointer to the next service in a linked list. For internal chaining of services. */
    GATTS_Attribute_T               *p_attrList;                                    /**< Pointer to the array of attributes within this service. See @ref GATTS_Attribute_T. */
    GATTS_CccdSetting_T const       *p_cccdSetting;                                 /**< Pointer to the CCCD settings for the service. May be NULL if not used. See @ref GATTS_CccdSetting_T. */
    uint16_t                        startHandle;                                    /**< Handle of the first attribute in the service. */
    uint16_t                        endHandle;                                      /**< Handle of the last attribute in the service. */
    uint8_t                         cccdNumber;                                     /**< Count of Client Characteristic Configuration Descriptors (CCCDs) in the service. */
} GATTS_Service_T;


/** @brief Structure for configuration options for a GATT service. */
typedef struct GATTS_GattServiceOptions_T
{
    uint8_t             enable;                                                     /**< Flag to enable or disable the GATT service. Set to 1 to enable, 0 to disable. */
} GATTS_GattServiceOptions_T;


/** @brief Structure for the @ref GATTC_EVT_ERROR_RESP event. */
typedef struct GATT_EvtError_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint8_t             reqOpcode;                                                  /**< Opcode of the request that resulted in an error response. */
    uint16_t            attrHandle;                                                 /**< Handle of the attribute related to the error. */
    uint8_t             errCode;                                                    /**< Error code explaining the reason for the error response (see @ref ATT_ERROR_CODES). */
} GATT_EvtError_T;

/** @brief Structure for the @ref GATTS_EVT_READ event.*/
typedef struct GATT_EvtRead_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint16_t            attrHandle;                                                 /**< Handle of the attribute being read. */
    uint8_t             readType;                                                   /**< Type of read operation being requested. Only ATT_READ_BY_TYPE_REQ/ATT_READ_REQ/ATT_READ_BLOB_REQ 
                                                                                            are allowed. See @ref ATT_OPCODES. */
    uint16_t            readOffset;                                                 /**< Offset for a read blob request; specifies where to start reading. */
} GATT_EvtRead_T;


/** @brief Structure for the @ref GATTS_EVT_WRITE event.*/
typedef struct GATT_EvtWrite_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint16_t            attrHandle;                                                 /**< Handle of the attribute being written to. */
    uint8_t             writeType;                                                  /**< Type of write operation being requested. See @ref ATT_OPCODES. 
                                                                                         Only ATT_WRITE_REQ/ATT_WRITE_CMD/ATT_PREPARE_WRITE_REQ/ATT_EXECUTE_WRITE_REQ are allowed. */
    uint8_t             flags;                                                      /**< Flags specific to an Execute Write Request (see @ref GATT_EXEC_WRITE_FLAGS). */
    uint16_t            valueOffset;                                                /**< Offset for a prepare write request; specifies where to start writing. */
    uint16_t            writeDataLength;                                            /**< Length of the data being written. */
    uint8_t             writeValue[BLE_ATT_MAX_MTU_LEN - ATT_WRITE_HEADER_SIZE];    /**< Data buffer containing the value to write to the attribute. */
} GATT_EvtWrite_T;


/** @brief Structure for the @ref GATTC_EVT_DISC_PRIM_SERV_RESP event.*/
typedef struct GATT_EvtDiscPrimServResp_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint8_t             attrPairLength;                                             /**< Length of each attribute pair in the attribute data list. */
    uint16_t            attrDataLength;                                             /**< Total length of the attribute data list in bytes. */
    uint8_t             attrData[BLE_ATT_MAX_MTU_LEN-ATT_READ_BY_GROUP_RESP_HEADER_SIZE]; /**< Attribute data list containing tuples in the format:
                                                                                                <2-byte service handle> <2-byte End Group Handle> <Service UUID>.
                                                                                                The service handle is the handle of the discovered service.
                                                                                                The End Group Handle is the handle of the last attribute of the discovered service.
                                                                                                The Service UUID may be 16 or 128 bits.
                                                                                                The number of tuples is determined by (attrDataLength / attrPairLength).
                                                                                                Data is in little-endian format. */
    uint8_t             procedureStatus;                                            /**< Indicates if more events are expected in the "Discover All Primary Services" procedure.
                                                                                        See @ref GATT_PROCEDURE_STATUS for possible values. */
} GATT_EvtDiscPrimServResp_T;


/** @brief Structure for the @ref GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP event.*/
typedef struct GATT_EvtDiscPrimServByUuidResp_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint16_t            handleInfoLength;                                           /**< Total length of the handle information list in bytes. */
    uint8_t             handleInfo[BLE_ATT_MAX_MTU_LEN-ATT_FIND_BY_TYPE_RESP_HEADER_SIZE];/**< Handle information list containing handle pairs in the format:
                                                                                                <2-byte service handle> <2-byte End Group Handle>.
                                                                                                The service handle is the handle of the discovered service.
                                                                                                The End Group Handle is the handle of the last attribute of the discovered service.
                                                                                                Multiple handle pairs may exist for multiple instances of the same primary service on the server.
                                                                                                Data is in little-endian format. */
    uint8_t             procedureStatus;                                            /**< Indicates if more events are expected in the "Discover Primary Service By UUID" procedure.
                                                                                        See @ref GATT_PROCEDURE_STATUS for possible values. */
} GATT_EvtDiscPrimServByUuidResp_T;


/** @brief Structure for the @ref GATTC_EVT_DISC_CHAR_RESP event.*/
typedef struct GATT_EvtDiscCharResp_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint8_t             attrPairLength;                                             /**< Length of each handle-value pair in the attribute data list. */
    uint16_t            attrDataLength;                                             /**< Total length of the attribute data list in bytes. */
    uint8_t             attrData[BLE_ATT_MAX_MTU_LEN-ATT_READ_BY_TYPE_RESP_HEADER_SIZE];/**< Attribute data list containing handle-value pairs in the format:
                                                                                            <2-byte Characteristic declaration handle> <1-byte Characteristic property> <2-byte Value Handle> <Characteristic UUID>.
                                                                                            Characteristic properties are defined in @ref GATT_CHARACTERISTIC_PROPERTIES.
                                                                                            The Characteristic UUID may be 16 or 128 bits.
                                                                                            The number of handle-value pairs is determined by (attrDataLength / attrPairLength).
                                                                                            Data is in little-endian format. */
    uint8_t             procedureStatus;                                            /**< Indicates if more events are expected in the "Discover All Characteristics" procedure.
                                                                                        See @ref GATT_PROCEDURE_STATUS for possible values. */

} GATT_EvtDiscCharResp_T;


/** @brief Structure for the @ref GATTC_EVT_DISC_DESC_RESP event.*/
typedef struct GATT_EvtDiscDescResp_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint8_t             infoDataFormat;                                             /**< Format of the received descriptor data:
                                                                                        1 for 16-bit UUIDs,
                                                                                        2 for 128-bit UUIDs,
                                                                                        other values are invalid. */    
    uint16_t            infoDataLength;                                             /**< Total length of the received descriptor information data in bytes. */
    uint8_t             infoData[BLE_ATT_MAX_MTU_LEN-ATT_FIND_INFO_RESP_HEADER_SIZE];/**< Descriptor data list containing handle-UUID pairs in the format:
                                                                                        <2-byte Characteristic descriptor handle> <Characteristic Descriptor UUID>.
                                                                                        The number of handle-UUID pairs is determined by (infoDataLength / 4) for 16-bit UUIDs 
                                                                                            or (infoDataLength / 18) for 128-bit UUIDs. Data is in little-endian format. */
    uint8_t             procedureStatus;                                            /**< Indicates if more events are expected in the "Discover All Descriptors" procedure.
                                                                                        See @ref GATT_PROCEDURE_STATUS for possible values. */
} GATT_EvtDiscDescResp_T;


/** @brief Structure for the @ref GATTC_EVT_READ_USING_UUID_RESP event.*/
typedef struct GATT_EvtReadUsingUuidResp_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint8_t             attrPairLength;                                             /**< Length of each attribute handle-value pair in the list.  */
    uint16_t            attrDataLength;                                             /**< Length of the attribute data list in bytes. */
    uint8_t             attrData[BLE_ATT_MAX_MTU_LEN-ATT_READ_BY_TYPE_RESP_HEADER_SIZE];/**< Attribute data list containing one or more handle-value pairs in the format:
                                                                                             <2-byte Characteristic Value handle> <Characteristic Value>.
                                                                                              The number of handle-value pairs is determined by (attrDataLength / attrPairLength).
                                                                                            Data is in little-endian format. */
} GATT_EvtReadUsingUuidResp_T;


/** @brief Structure for the @ref GATTC_EVT_READ_RESP event.*/
typedef struct GATT_EvtReadResp_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint8_t             responseType;                                               /**< Type of read response. See @ref ATT_OPCODES. Valid values are ATT_READ_RSP and ATT_READ_BLOB_RSP. */
    uint16_t            attrDataLength;                                             /**< Length of the attribute data read. */
    uint8_t             readValue[BLE_ATT_MAX_MTU_LEN-ATT_READ_RESP_HEADER_SIZE];   /**< Buffer containing the data read from the specified attribute. */
    uint16_t            charHandle;                                                 /**< Handle of the characteristic from which data was read. */
} GATT_EvtReadResp_T;


/** @brief Structure for the @ref GATTC_EVT_WRITE_RESP event.*/
typedef struct GATT_EvtWriteResp_T
{
    uint16_t            connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t             responseType;                                                   /**< Type of write response. See @ref ATT_OPCODES. Valid values are ATT_WRITE_RSP, 
                                                                                                ATT_PREPARE_WRITE_RSP, and ATT_EXECUTE_WRITE_RSP. */
    uint16_t            charHandle;                                                     /**< Characteristic handle related to the write operation. */
    uint16_t            valueOffset;                                                    /**< Offset at which the write operation occurred. Valid only if responseType is ATT_PREPARE_WRITE_RSP. */
    uint16_t            writeLength;                                                    /**< Length of the data written. Valid only if responseType is ATT_PREPARE_WRITE_RSP. */
    uint8_t             writeValue[BLE_ATT_MAX_MTU_LEN-ATT_PREP_WRITE_RESP_HEADER_SIZE];/**< Buffer containing the value written. Valid only if responseType is ATT_PREPARE_WRITE_RSP. */
} GATT_EvtWriteResp_T;


/** @brief Structure for the @ref ATT_EVT_UPDATE_MTU event.*/
typedef struct GATT_EvtUpdateMtu_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint16_t            exchangedMTU;                                               /**< MTU size agreed upon by both GATT client and server after the exchange. */
} GATT_EvtUpdateMtu_T;


/** @brief Structure for the @ref GATTC_EVT_HV_NOTIFY or @ref GATTC_EVT_HV_INDICATE event.*/
typedef struct GATT_EvtReceiveHandleValue_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint16_t            charHandle;                                                 /**< Handle of the characteristic for which the notification or indication was received. */
    uint16_t            receivedLength;                                             /**< Length of the received notification or indication value. */
    uint8_t             receivedValue[BLE_ATT_MAX_MTU_LEN-ATT_NOTI_INDI_HEADER_SIZE];   /**< Buffer containing the value received in the notification or indication. */
} GATT_EvtReceiveHandleValue_T;


/** @brief Structure for the @ref GATTS_EVT_HV_CONFIRM event.*/
typedef struct GATT_EvtReceiveCfm_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint16_t            attrHandle;                                                 /**< Handle of the attribute for which the confirmation is an acknowledgment of the indication. */
} GATT_EvtReceiveCfm_T;


/** @brief Structure for the @ref GATTS_EVT_SERVICE_CHANGE event. */
typedef struct GATT_EvtServiceChange_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. Value 0x00 to all the bonded devices. */
    uint8_t             serviceChange;                                              /**< Indicates the state of service change. See @ref GATT_DB_CHANGE_STATE for possible values. */
} GATT_EvtServiceChange_T;


/** @brief Structure for the @ref GATTS_EVT_CLIENT_FEATURE_CHANGE event. */
typedef struct GATT_EvtClientFeatureChange_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint8_t             clientSupportFeature;                                       /**< Bitmask representing the client-supported features. Refer to @ref GATT_CLIENT_FEATURE for details. */
} GATT_EvtClientFeatureChange_T;


/** @brief Structure for the @ref GATTS_EVT_CLIENT_CCCDLIST_CHANGE event. */
typedef struct GATT_EvtClientCccdListChange_T
{
    GATTS_CccdList_T    *p_cccdList;                                                /**< Pointer to the Client Characteristic Configuration Descriptor (CCCD) list. See @ref GATTS_CccdList_T.*/
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
    uint8_t             numOfCccd;                                                  /**< Number of CCCDs in the list. */
} GATT_EvtClientCccdListChange_T;


/** @brief Structure for the @ref GATTC_EVT_PROTOCOL_AVAILABLE or @ref GATTS_EVT_PROTOCOL_AVAILABLE event. */
typedef struct GATT_EvtProtocolAvailable_T
{
    uint16_t            connHandle;                                                 /**< Connection handle associated with this connection. */
} GATT_EvtProtocolAvailable_T;


/** 
 * @brief Structure for the @ref GATTS_EVT_ENC_DATA_KEY_MATL_REQ event.
 * This event is triggered when peer request to read encrypted data key material.
 */
typedef struct GATT_EvtEncDataKeyMatlReq_T
{
    uint16_t                connHandle;                                             /**< Connection handle associated with this connection. */
} GATT_EvtEncDataKeyMatlReq_T;


/** @brief Union of BLE GATT callback event data types. */
typedef union
{
    GATT_EvtError_T                       onError;                              /**< Data for @ref GATTC_EVT_ERROR_RESP event. */
    GATT_EvtRead_T                        onRead;                               /**< Data for @ref GATTS_EVT_READ event. */
    GATT_EvtWrite_T                       onWrite;                              /**< Data for @ref GATTS_EVT_WRITE event. */
    GATT_EvtDiscPrimServResp_T            onDiscPrimServResp;                   /**< Data for @ref GATTC_EVT_DISC_PRIM_SERV_RESP event. */
    GATT_EvtDiscPrimServByUuidResp_T      onDiscPrimServByUuidResp;             /**< Data for @ref GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP event. */
    GATT_EvtDiscCharResp_T                onDiscCharResp;                       /**< Data for @ref GATTC_EVT_DISC_CHAR_RESP event. */
    GATT_EvtDiscDescResp_T                onDiscDescResp;                       /**< Data for @ref GATTC_EVT_DISC_DESC_RESP event. */
    GATT_EvtReadUsingUuidResp_T           onReadUsingUuidResp;                  /**< Data for @ref GATTC_EVT_READ_USING_UUID_RESP event. */
    GATT_EvtReadResp_T                    onReadResp;                           /**< Data for @ref GATTC_EVT_READ_RESP event. */
    GATT_EvtWriteResp_T                   onWriteResp;                          /**< Data for @ref GATTC_EVT_WRITE_RESP event. */
    GATT_EvtUpdateMtu_T                   onUpdateMTU;                          /**< Data for @ref ATT_EVT_UPDATE_MTU event. */
    GATT_EvtReceiveHandleValue_T          onNotification;                       /**< Data for @ref GATTC_EVT_HV_NOTIFY event. */
    GATT_EvtReceiveHandleValue_T          onIndication;                         /**< Data for @ref GATTC_EVT_HV_INDICATE event. */
    GATT_EvtReceiveCfm_T                  onConfirmation;                       /**< Data for @ref GATTS_EVT_HV_CONFIRM event. */
    GATT_EvtDiscCharResp_T                onDiscCharByUuid;                     /**< Data for @ref GATTC_EVT_DISC_CHAR_BY_UUID_RESP event. */
    GATT_EvtServiceChange_T               onServiceChange;                      /**< Data for @ref GATTS_EVT_SERVICE_CHANGE event. */
    GATT_EvtClientFeatureChange_T         onClientFeatureChange;                /**< Data for @ref GATTS_EVT_CLIENT_FEATURE_CHANGE event. */
    GATT_EvtClientCccdListChange_T        onClientCccdListChange;               /**< Data for @ref GATTS_EVT_CLIENT_CCCDLIST_CHANGE event. */
    GATT_EvtProtocolAvailable_T           onClientProtocolAvailable;            /**< Data for @ref GATTC_EVT_PROTOCOL_AVAILABLE event. */
    GATT_EvtProtocolAvailable_T           onServerProtocolAvailable;            /**< Data for @ref GATTS_EVT_PROTOCOL_AVAILABLE event. */
    GATT_EvtEncDataKeyMatlReq_T           onEncDataKeyMatlReq;                  /**< Data for @ref GATTS_EVT_ENC_DATA_KEY_MATL_REQ event. */
} GATT_EventField_T;

/** @brief GATT callback event structure.*/
typedef struct  GATT_Event_T
{
    GATT_EventId_T          eventId;                                            /**< Identifier for the GATT event. See @ref GATT_EventId_T. */
    GATT_EventField_T       eventField;                                         /**< Union containing the data payload for the event. See @ref GATT_EventField_T.  */
} GATT_Event_T;

/** @} */ //GATT_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup GATT_FUNS Functions
 * @{
 */
 
/**
 * @brief Initialize the GATT Client module.
 * @note  The GATT Server must be initialized before this module.
 *
 * @param[in] configuration              A bit-field configuring the GATT Client's functions.
 *                                       See @ref GATTC_CONFIGURATION_BITS for bit definitions.\n
 *                                       - Manual mode: Call @ref GATTC_HandleValueConfirm to send a confirmation 
 *                                          for an indication upon receiving @ref GATTC_EVT_HV_INDICATE.\n
 *                                       - Auto mode: The GATT stack automatically sends confirmations.\n
 *
 * @retval MBA_RES_SUCCESS               Successfully initialize the GATT client module.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
*/
uint16_t GATTC_Init(uint16_t configuration);


/**
 * @brief Initialize the GATT Server module.
 * @note  The GAP/SMP/L2CAP shall be initialized before this module.
 *
 * @param[in] configuration              A bit-field configuring the GATT Server's functions. See 
 *                                      @ref GATTS_CONFIGURATION_BITS for bit definitions.
 *
 * @retval MBA_RES_SUCCESS               Successfully initialize the GATT server module.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
*/
uint16_t GATTS_Init(uint16_t configuration);


/**
 * @brief Initiates a read operation from the GATT Client to the GATT Server.
 * @note  This API is used to read a Characteristic Value or a Characteristic Descriptor. \n
 *        - For non-long attributes, set valueOffset to 0. A Read Request is sent.\n
 *        - For long attributes, read the first (ATT_MTU-1) bytes with valueOffset set to 0. 
 *          Subsequent bytes are read with a non-zero valueOffset using Read Blob Requests. 
 *          Continue issuing @ref GATTC_Read with updated offsets upon receiving each 
 *          @ref GATTC_EVT_READ_RESP until the entire attribute is read.\n
 *
 * @par Events generated
 * @ref GATTC_EVT_ERROR_RESP is generated when Read operation failed.
 * @ref GATTC_EVT_READ_RESP is generated when ead operation successful.
 * @ref ATT_EVT_TIMEOUT is generated when no response from the server.
 *
 * @param[in] connHandle                 Handle of the connection to send read operation.
 * @param[in] charHandle                 The handle of the characteristic or descriptor to read.
 * @param[in] valueOffset                The offset for a Read Blob Request. Set to 0 for a normal Read Request.
 *
 * @retval MBA_RES_SUCCESS               Successfully starts the read operation.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters, such as an invalid connection handle.
 * @retval MBA_RES_BUSY                  GATT Client is busy with another ongoing request.
 */
uint16_t GATTC_Read(uint16_t connHandle, uint16_t charHandle, uint16_t valueOffset);


/**
 * @brief Initiates a write operation from the GATT Client to the GATT Server.
 * @note  Use this API to write a Characteristic Value or a Characteristic Descriptor.
 *        See @ref ATT_OPCODES for write types (ATT_WRITE_REQ, ATT_WRITE_CMD, ATT_PREPARE_WRITE_REQ, ATT_EXECUTE_WRITE_REQ).\n
 *        - For non-long attributes, set valueOffset to 0 and choose Write Request/Write Command.\n
 *        - For long attributes, write the first (ATT_MTU-3) bytes with valueOffset set to 0 and writeType as ATT_PREPARE_WRITE_REQ. 
 *          Subsequent prepare write requests should be made with the correct valueOffset and data upon receiving @ref GATTC_EVT_WRITE_RESP. 
 *          Continue until all bytes are queued on the server. After the last prepare write response, call this API with writeType as 
 *          @ref ATT_EXECUTE_WRITE_REQ and flags as @ref GATT_EXEC_WRITE_FLAG_WRITE.\n
 *
 * @par Events generated
 * @ref GATTC_EVT_ERROR_RESP is generated on write failure.
 * @ref GATTC_EVT_WRITE_RESP is generated on successful write.
 * @ref ATT_EVT_TIMEOUT is generated if the server does not respond.
 *
 * @param[in] connHandle                 Handle of the connection to send write operation.
 * @param[in] p_writeParams              Pointer to the write parameters structure (see @ref GATTC_WriteParams_T).
 *
 * @retval MBA_RES_SUCCESS               Successfully starts the write operation.
 * @retval MBA_RES_FAIL                  Operation not permitted.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters (invalid connection handle or write parameters).
 * @retval MBA_RES_NO_RESOURCE           No resources available to perform the write.
 * @retval MBA_RES_BUSY                  GATT Client is busy with another ongoing request.
 */
uint16_t GATTC_Write(uint16_t connHandle, GATTC_WriteParams_T *p_writeParams);


/**
 * @brief Sends a Handle Value Confirmation from the GATT Client to the GATT Server 
 *          upon receiving a Handle Value Indication.
 * @note  Call this API only after receiving @ref GATTC_EVT_HV_INDICATE, which occurs if 
 *          manual confirmation is enabled (see @ref GATTC_CONFIG_MANUAL_CONFIRMATION).
 *
 * @param[in] connHandle                 Handle of the connection to send Handle Value Confirmation.
 *
 * @retval MBA_RES_SUCCESS               Successfully initiate the Handle Value Confirmation.
 * @retval MBA_RES_FAIL                  Operation not permitted (Automatic mode configured or no Indication received).
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid connection handle.
 */
uint16_t GATTC_HandleValueConfirm(uint16_t connHandle);


/**
 * @brief Initiates an Exchange MTU Request from the GATT Client to the GATT Server.
 * @note  The requested MTU size is adjusted to be within the range of @ref BLE_ATT_DEFAULT_MTU_LEN 
 *          and @ref BLE_ATT_MAX_MTU_LEN. If the requested MTU length is less than @ref BLE_ATT_DEFAULT_MTU_LEN, 
 *          then @ref BLE_ATT_DEFAULT_MTU_LEN is requested. If the requested MTU length is greater than 
 *          @ref BLE_ATT_MAX_MTU_LEN, then @ref BLE_ATT_MAX_MTU_LEN is requested.
 *
 * @par Events generated
 * @ref GATTC_EVT_ERROR_RESP is generated on failure to exchange MTU.
 * @ref ATT_EVT_UPDATE_MTU is generated on successful MTU exchange.
 * @ref ATT_EVT_TIMEOUT is generated if the server does not respond.
 *
 * @param[in] connHandle                 Handle of the connection to send Exchange MTU Request.
 * @param[in] mtuLen                     Requested MTU length (within the range of @ref BLE_ATT_DEFAULT_MTU_LEN to @ref BLE_ATT_MAX_MTU_LEN).
 *
 * @retval MBA_RES_SUCCESS               Successfully initiate the Exchange MTU Request.
 * @retval MBA_RES_FAIL                  Operation rejected.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters, such as an invalid connection handle.
 * @retval MBA_RES_BUSY                  GATT Client is busy with another ongoing request.
 */
uint16_t GATTC_ExchangeMTURequest(uint16_t connHandle, uint16_t mtuLen);


/**
 * @brief Configures the preferred ATT MTU size for the GATT Client in the central role.
 * @note  When connection established with remote peer, GATT client will initiate MTU negotiation 
 *          with remote peer. By default, @ref BLE_ATT_MAX_MTU_LEN will be used to negotiate with 
 *          remote.If user sets preferred MTU, the set value will be used to negotiate with remote. 
 *          The preferred MTU does not apply to existing connections. Use @ref GATTC_ExchangeMTURequest 
 *          for connected state MTU exchange. This API is optional and only affects the central role.
 *
 * @param[in] preferredMtuCentral        Preferred ATT MTU size.
 *
 * @retval MBA_RES_SUCCESS               Successfully configured the preferred MTU.
 * @retval MBA_RES_INVALID_PARA          Invalid MTU size specified.
 */
uint16_t GATTC_SetPreferredMtu(uint16_t preferredMtuCentral);


/**
 * @brief Initiates the discovery of all primary services on the connected GATT server.
 * @note  The discovery process may result in multiple events indicating the status of the 
 *          discovery until all services are found.
 *
 * @par Events generated
 * @ref GATTC_EVT_DISC_PRIM_SERV_RESP indicates ongoing discovery or finalization of the process.
 * @ref GATTC_EVT_ERROR_RESP indicates an error or the end of the discovery process if the last 
 *                                      service's end handle is less than 0xFFFF.
 * @ref ATT_EVT_TIMEOUT indicates a timeout waiting for the server's response.
 *
 * @param[in] connHandle                 Handle of the connection to discover the services for.
 *
 * @retval MBA_RES_SUCCESS               Discovery process successfully started.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters, such as an invalid connection handle.
 * @retval MBA_RES_BUSY                  GATT Client is busy with another ongoing request.
 */
uint16_t GATTC_DiscoverAllPrimaryServices(uint16_t connHandle);


/**
 * @brief Begins the discovery of primary services by UUID within a specified handle range on the GATT server.
 * @note  The discovery may result in multiple events as services are found.
 *
 * @par Events generated
 * @ref @ref GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP indicates ongoing discovery or finalization of the process.
 * @ref @ref GATTC_EVT_ERROR_RESP indicates an error or the end of the discovery process if the last 
 *                                  service's end handle is less than the specified end handle.
 * @ref ATT_EVT_TIMEOUT indicates a timeout waiting for the server's response.
 *
 * @param[in] connHandle                 Handle of the connection to discover the services.
 * @param[in] p_discParams               Pointer to parameters specifying the UUID and handle range for discovery. 
 *                                          See @ref GATTC_DiscoverPrimaryServiceParams_T.
 *
 * @retval MBA_RES_SUCCESS               Discovery process successfully started.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters, such as an invalid connection handle.
 * @retval MBA_RES_BUSY                  GATT Client is busy with another ongoing request.
 */
uint16_t GATTC_DiscoverPrimaryServiceByUUID(uint16_t connHandle, GATTC_DiscoverPrimaryServiceParams_T *p_discParams);


/**
 * @brief Starts the discovery of all characteristics within a specified handle range on the GATT server.
 * @note  The discovery may result in multiple events as characteristics are found. 
 *
 * @par Events generated
 * @ref GATTC_EVT_DISC_CHAR_RESP indicates ongoing discovery or finalization of the process.
 * @ref GATTC_EVT_ERROR_RESP indicates an error or the end of the discovery process if no characteristics 
 *                              are found or the last characteristic's value handle does not match the end handle.
 * @ref ATT_EVT_TIMEOUT indicates a timeout waiting for the server's response.
 *
 * @param[in] connHandle                 Handle of the connection to discover the characteristics for.
 * @param[in] startHandle                Start of the handle range for discovery.
 * @param[in] endHandle                  End of the handle range for discovery.
 *
 * @retval MBA_RES_SUCCESS               Discovery process successfully started.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters, such as an invalid connection handle.
 * @retval MBA_RES_BUSY                  GATT Client is busy with another ongoing request.
 */
uint16_t GATTC_DiscoverAllCharacteristics(uint16_t connHandle, uint16_t startHandle, uint16_t endHandle);


/**
 * @brief Initiates the discovery of characteristics with a specific UUID within a handle range.
 * @note  This function starts the discovery process for characteristics with a specific UUID within 
 *          the provided handle range. The discovery may result in a series of events indicating the 
 *          status and results of the operation.
 * 
 * @par Events generated
 * @ref GATTC_EVT_DISC_CHAR_BY_UUID_RESP with procedureStatus set to 'continue' indicates that one or more characteristics
 *      have been found, but the discovery process is ongoing.
 * @ref GATTC_EVT_DISC_CHAR_BY_UUID_RESP with procedureStatus set to 'finish' indicates the end of the discovery process,
 *      either because the last characteristic has been found or no more characteristics are present within the range.
 * @ref GATTC_EVT_ERROR_RESP with error code @ref ATT_ERR_ATTRIBUTE_NOT_FOUND indicates the discovery process has ended
 *      due to no further characteristics being found.
 * @ref @ref ATT_EVT_TIMEOUT indicates a timeout occurred because the server did not respond to the request.
 *
 * @param[in] connHandle                 Handle of the connection to discover the characteristics for.
 * @param[in] p_discParams               Pointer to parameters specifying the UUID to discover and the handle range.
 *                                          See @ref GATTC_DiscoverCharacteristicByUuidParams_T.
 *
 * @retval MBA_RES_SUCCESS               Discovery process successfully initiated.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters, such as an invalid connection handle.
 * @retval MBA_RES_BUSY                  GATT Client is busy with another ongoing request.
 */
uint16_t GATTC_DiscoverCharacteristicsByUUID(uint16_t connHandle, GATTC_DiscoverCharacteristicByUuidParams_T *p_discParams);


/**
 * @brief Initiates the discovery of all descriptors with a specific UUID within a handle range.
 * @note  This function starts the discovery process for all descriptors with a specific UUID within 
 *          the provided handle range. The discovery may result in a series of events indicating the 
 *          status and results of the operation.
 *
 * @par Events generated
 * @ref GATTC_EVT_DISC_DESC_RESP with procedureStatus set to 'continue' indicates that one or more descriptors
 *      have been found, but the discovery process is ongoing.
 * @ref GATTC_EVT_DISC_DESC_RESP with procedureStatus set to 'finish' indicates the end of the discovery process,
 *      either because the last descriptor has been found or no more descriptors are present within the range.
 * @ref GATTC_EVT_ERROR_RESP with error code @ref ATT_ERR_ATTRIBUTE_NOT_FOUND indicates the discovery process has ended
 *      due to no further descriptors being found.
 * @ref ATT_EVT_TIMEOUT indicates a timeout occurred because the server did not respond to the request.
 *
 * @param[in] connHandle                 Handle of the connection to discover the descriptors for.
 * @param[in] startHandle                Start handle of the range to query.
 * @param[in] endHandle                  End handle of the range to query.
 *
 * @retval MBA_RES_SUCCESS               Discovery process successfully initiated.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters, such as an invalid connection handle.
 * @retval MBA_RES_BUSY                  GATT Client is busy with another ongoing request.
 */
uint16_t GATTC_DiscoverAllDescriptors(uint16_t connHandle, uint16_t startHandle, uint16_t endHandle);


/**
 * @brief Initiates a read operation for a characteristic value by UUID within a handle range.
 * @note  This function starts a read operation for the value of a characteristic specified by UUID within 
 *          the given handle range. The operation may result in a series of events indicating the status 
 *          and results of the read operation.
 * 
 * @par Events generated
 * @ref GATTC_EVT_ERROR_RESP indicates a failure to read the characteristic value.
 * @ref GATTC_EVT_READ_USING_UUID_RESP indicates a successful read operation.
 * @ref ATT_EVT_TIMEOUT indicates a timeout occurred because the server did not respond to the request.
 *
 * @param[in] connHandle                 Handle of the connection to read characteristic value for.
 * @param[in] p_readParams               Pointer to structure containing the UUID of the Characteristic and handle 
 *                                          range to be queried. See @ref GATTC_ReadByTypeParams_T.
 *
 * @retval MBA_RES_SUCCESS               Read operation successfully initiated.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters, such as an invalid connection handle.
 * @retval MBA_RES_BUSY                  GATT Client is busy with another ongoing request.
 */
uint16_t GATTC_ReadUsingUUID(uint16_t connHandle, GATTC_ReadByTypeParams_T *p_readParams);


/**
 * @brief Registers a service with the GATT server.
 * @note  The start handle of the service being registered must be greater than @ref GATTS_APP_SVC_START_HDL.
 *
 * @param[in] p_service                  Pointer to the service information being registered. See @ref GATTS_Service_T.
 * @param[in] numAttributes              Number of attributes in the service being registered.
 *
 * @retval MBA_RES_SUCCESS               Service successfully registered.
 * @retval MBA_RES_FAIL                  Registration failed due to a handle conflict or the start handle being too low.
 */
uint16_t GATTS_AddService(GATTS_Service_T *p_service, uint8_t numAttributes);


/**
 * @brief Removes a previously registered service from the GATT server.
 *
 * @param[in] startHandle                The start handle of the service to remove.
 *
 * @retval MBA_RES_SUCCESS               Service successfully removed.
 * @retval MBA_RES_FAIL                  Removal failed because the service does not exist.
 */
uint16_t GATTS_RemoveService(uint16_t startHandle);


/**
 * @brief Sends a Handle Value Notification or Indication to a GATT client.
 * @note  The type of message sent (notification or indication) is determined by the sendType field in 
 *          the @ref GATTS_HandleValueParams_T structure. sendType in @ref GATTS_HandleValueParams_T determines if a 
 *          notification or Indication is sent. A notification or indication can be sent only if the property matches 
 *          and the CCCD value is configured to be enabled.
 *
 * @par Events generated
 * @ref GATTS_EVT_HV_CONFIRM is generated if an indication is successfully sent.
 * @ref ATT_EVT_TIMEOUT is generated if the client does not respond to an indication.
 *
 * @param[in] connHandle                 Handle of the connection to send Handle Value Notification/Indication.
 * @param[in] p_hvParams                 Pointer to the parameters for the Handle Value operation. See @ref GATTS_HandleValueParams_T.
 *
 * @retval MBA_RES_SUCCESS               Operation successfully started.
 * @retval MBA_RES_FAIL                  Operation failed due to invalid permissions or unavailable memory.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters, such as an invalid connection handle or out-of-range values.
 * @retval MBA_RES_BUSY                  An indication is already in progress.
 * @retval MBA_RES_NO_RESOURCE           No resources available to send the handle value.
 */
uint16_t GATTS_SendHandleValue(uint16_t connHandle, GATTS_HandleValueParams_T *p_hvParams);


/**
 * @brief Sends a Read or Read Blob response to a GATT client. 
 * @note  The type of response (Read or Read Blob) is determined by the responseType field in the GATTS_SendReadRespParams_T 
 *          structure. If the attribute's setting is @ref SETTING_MANUAL_READ_RSP, the @ref GATTS_EVT_READ event with readType 
 *          @ref ATT_READ_REQ or @ref ATT_READ_BLOB_REQ will be sent to the application when the GATT server receives 
 *          these requests. The application should then call this API to send the read response or an error response if the 
 *          request is not permitted.
 *
 * @param[in] connHandle                 Handle of the connection to send the read response.
 * @param[in] p_respParams               Pointer to the Read Response parameters. See @ref GATTS_SendReadRespParams_T.
 *
 * @retval MBA_RES_SUCCESS               Read response successfully initiated.
 * @retval MBA_RES_FAIL                  Operation not permitted; no corresponding read request received.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters, such as an invalid connection handle.
 */
uint16_t GATTS_SendReadResponse(uint16_t connHandle, GATTS_SendReadRespParams_T *p_respParams);


/**
 * @brief Sends an error response from the GATT Server.
 * @note  This function should be called when the application receives a request event that cannot be processed by 
 *          the GATT server,such as a write request without write permission.
 *
 * @param[in] connHandle                 Handle of the connection to send the error response.
 * @param[in] p_errParams                Pointer to the parameters for the error response (see @ref GATTS_SendErrRespParams_T).
 *
 * @retval MBA_RES_SUCCESS               Error response successfully initiated.
 * @retval MBA_RES_FAIL                  Operation not permitted; the error response does not match the received request.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters; the connection handle is not valid.
 */
uint16_t GATTS_SendErrorResponse(uint16_t connHandle, GATTS_SendErrRespParams_T *p_errParams);


/**
 * @brief Sends a Read By Type response from the GATT Server.
 * @note This function should be called in response to a @ref GATTS_EVT_READ event to send the Read By Type 
 *      response. If the attribute's setting is @ref SETTING_MANUAL_READ_RSP, the application will receive 
 *      a @ref GATTS_EVT_READ event when a Read By Type request is received. The application should then 
 *      call this function to send the response or an error response if the request is not allowed.
 *
 * @param[in] connHandle                 Connection handle to send the Read By Type response.
 * @param[in] p_respParams               Pointer to the Read By Type Response parameters (see @ref GATTS_SendReadByTypeRespParams_T).
 *
 * @retval MBA_RES_SUCCESS               Read By Type response successfully started.
 * @retval MBA_RES_FAIL                  Operation not permitted; no prior Read By Type request received.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters; the connection handle is not valid.
 */
uint16_t GATTS_SendReadByTypeResponse(uint16_t connHandle, GATTS_SendReadByTypeRespParams_T *p_respParams);


/**
 * @brief Sends a write response from the GATT Server.
 * @note  This function sends a response for write, prepare write, or execute write requests as indicated 
 *          by the ResponseType in @ref GATTS_SendWriteRespParams_T. If the attribute's setting is 
 *          @ref SETTING_MANUAL_WRITE_RSP, the application will receive a @ref GATTS_EVT_WRITE event 
 *          when a write request is received. The application should then call this function to send the 
 *          appropriate response or an error response if the request is not allowed.
 *
 * @param[in] connHandle                 Connection handle to send the write response.
 * @param[in] p_respParams               Pointer to the Write Response parameters (see @ref GATTS_SendWriteRespParams_T).
 *
 * @retval MBA_RES_SUCCESS               Write response successfully started.
 * @retval MBA_RES_FAIL                  Operation not permitted; no corresponding write request received.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters; the connection handle is not valid.
 */
uint16_t GATTS_SendWriteResponse(uint16_t connHandle, GATTS_SendWriteRespParams_T *p_respParams);


/**
 * @brief Enables the service change indication and notifies clients about changes to the service table.
 * @note This function should be called after services have been added or removed to notify connected clients of the changes.
 *        Clients will receive an indication if configured to do so.
 *
 * @retval MBA_RES_SUCCESS                Successfully notified connected clients of the service change.
 */
uint16_t GATTS_ServiceChanged(void);


/**
 * @brief Notifies the local GATT Server of the bonding information for a connection.
 * @note  This function should be called after a connection is established, regardless of whether the 
 *          connection is bonded. The GATT Server needs the bonding information to process certain requests 
 *          for bonded connections. If the GATT Server is initialized with caching support 
 *          (i.e., @ref GATTS_Init with @ref GATTS_CONFIG_CACHING_SUPPORT), this function must be invoked after the 
 *          connection is established. The GATT module will then begin processing packets once the bonding 
 *          information is received.
 *
 * @param[in] connHandle                 Connection handle.
 * @param[in] p_gattsParams              Pointer to the GATTS bonding parameters structure (See @ref GATTS_BondingParams_T). 
 *                                          Set to NULL for non-bonded connections.
 * @param[in] numOfCccds                 Number of Client Characteristic Configuration Descriptors (CCCDs) for the bonded connection.
 *                                       Set to zero for non-bonded connections.
 * @param[in] p_cccdList                 Pointer to the list of CCCDs for the bonded connection (See @ref GATTS_CccdList_T).
 *                                       Set to NULL for non-bonded connections.
 *
 * @retval MBA_RES_SUCCESS               Successfully notified the GATT Server of the updated parameters.
 * @retval MBA_RES_INVAIID_PARA          Invalid parameters; the connection handle is not valid.
 */
uint16_t GATTS_UpdateBondingInfo(uint16_t connHandle, GATTS_BondingParams_T *p_gattsParams, uint8_t numOfCccds, GATTS_CccdList_T *p_cccdList);


/**
 * @brief Retrieves the value of an attribute from the GATT Server.
 * @note  If the attribute is readable, its value is returned in the provided buffer. The attribute value 
 *          is returned as raw data.
 *
 * @param[in] attrHandle                 Attribute Handle.
 * @param[out] p_attrValue               Pointer to the buffer where the attribute value will be stored. Valid if the API returns MBA_RES_SUCCESS.
  *@param[in] p_attrLength               As an input parameter, it specifies the size of the provided buffer.
 *                                       As an output parameter, it specifies the actual size of the retrieved attribute value when the API returns MBA_RES_SUCCESS.
 *
 * @retval MBA_RES_SUCCESS               Successfully retrieved the attribute value.
 * @retval MBA_RES_FAIL                  The operation is not permitted. The attribute handle is valid, but the attribute cannot be read.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters.
 */
uint16_t GATTS_GetHandleValue(uint16_t attrHandle, uint8_t *p_attrValue, uint16_t *p_attrLength);


/**
 * @brief Configures the built-in GATT service.
 * @note  This function allows enabling or disabling the optional "GATT Service". It is recommended to call 
 *          this function during initialization and not when a connection is active. The enable/disable 
 *          configuration should remain consistent across multiple calls to this function. If the configuration 
 *          changes, service change considerations must be addressed in cases where multiple built-in services 
 *          are configured.
 *
 * @param[in] p_gattServiceOptions       Pointer to the GATT Service configuration structure (See @ref GATTS_GattServiceOptions_T).
 *
 * @retval MBA_RES_SUCCESS               Successfully configured the built-in GATT Service.
 * @retval MBA_RES_FAIL                  The operation is not permitted.
 */
uint16_t GATTS_ConfigureBuildInService(GATTS_GattServiceOptions_T *p_gattServiceOptions);


/**
 * @brief Set minimum encryption key length of a service.
 * @note  This function is used to set minimum key size requirement for accessing attributes in a GATT Service.
 *          Some of attributes required encryption permission to be accessed by remote client.
 *          Encryption with shorter key will be rejected when accessing those attributes.
 *          If this function is not called for the Service, minimum encryption key size requirement of the Service
 *          is 16 bytes by default.
 *
 * @param[in] svcUuidLength              Length of the Service UUID.
 * @param[in] p_svcUuid                  Pointer to Service UUID buffer. UUID in little endian format.
 * @param[in] minKeySize                 Minimum encryption key size requirement of the Service.
 *
 * @retval MBA_RES_SUCCESS               Successfully set the minimum key size of the Service.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid Service UUID specified.
 */
uint16_t GATTS_SetMinEncKeySize(uint8_t svcUuidLength, uint8_t *p_svcUuid, uint8_t minKeySize);

/**
 * @brief Configures the preferred ATT MTU size for the GATT Server.
 * @note  By default, @ref BLE_ATT_MAX_MTU_LEN is used to respond to MTU exchange requests from a remote client. 
 *          If a preferred MTU size is configured, it will be used instead. This API is optional; if not used, 
 *          @ref BLE_ATT_MAX_MTU_LEN will be the default response.
 *
 * @param[in] preferredMtuPeriph         Preferred ATT MTU size when the GAP role is peripheral.
 * @param[in] preferredMtuCentral        Preferred ATT MTU size when the GAP role is central.
 *
 * @retval MBA_RES_SUCCESS               Successfully configured the preferred MTU size for the GATT Server.
 * @retval MBA_RES_INVALID_PARA          Invalid MTU size specified.
 */
uint16_t GATTS_SetPreferredMtu(uint16_t preferredMtuPeriph, uint16_t preferredMtuCentral);

/**
 * @brief Responds to a GATT client's request for encrypted data key material.
 * @note  This function should be called upon receiving the @ref GATTS_EVT_ENC_DATA_KEY_MATL_REQ event.
 *        If either p_key or p_iv is NULL, the read request will be rejected.
 *
 * @param[in] connHandle                 Connection handle for sending the response.
 * @param[in] p_key                      Pointer to the 16-byte shared session key.
 * @param[in] p_iv                       Pointer to the 8-byte initialization vector.
 *
 * @retval MBA_RES_SUCCESS               Response successfully initiated.
 * @retval MBA_RES_FAIL                  Operation not permitted; no corresponding read request received.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters, such as an invalid connection handle.
 */
uint16_t GATTS_EncDataKeyMatlRsp(uint16_t connHandle, uint8_t *p_key, uint8_t *p_iv);

/**
 * @brief Updates the new encrypted data key material for a GATT client.
 *
 * @param[in] connHandle                 Connection handle for the update.
 * @param[in] p_key                      The 16 bytes shared session key.
 * @param[in] p_iv                       The 8 bytes initialization vector.
 *
 * @retval MBA_RES_SUCCESS               Operation successfully started.
 * @retval MBA_RES_FAIL                  Operation failed due to invalid permissions or unavailable memory.
 * @retval MBA_RES_OOM                   Memory allocation failure occurred internally.
 * @retval MBA_RES_INVALID_PARA          Invalid parameters, such as an invalid connection handle or out-of-range values.
 * @retval MBA_RES_BUSY                  An indication is already in progress.
 * @retval MBA_RES_NO_RESOURCE           No resources available to send the handle value.
 */
uint16_t GATTS_UpdateEncDataKeyMatl(uint16_t connHandle, uint8_t *p_key, uint8_t *p_iv);


/** @} */ //GATT_FUNS

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif//GATT_H
