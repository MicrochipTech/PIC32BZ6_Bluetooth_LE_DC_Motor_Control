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
  BLE Database Discovery Middleware Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dd.h

  Summary:
    Defines the interface for the BLE Database Discovery module.

  Description:
    This header file exposes the BLE Database Discovery module's API and associated events
    to the application layer. The module is responsible for discovering services and
    characteristics on a remote BLE device. Users must invoke "BLE_DD_Init" within the
    "APP_Initialize" function to properly initialize this module before use.
 *******************************************************************************/
#ifndef BLE_DD_H
#define BLE_DD_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "stack_mgr.h"
#include "att_uuid.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/** 
 * @addtogroup BLE_MW BLE Middleware
 * @{
 */

/**
 * @defgroup BLE_DD BLE Database Discovery (BLE_DD)
 * 
 * @brief Manages GATT Client Procedures for service discovery on remote devices.
 * @note This file contains the declarations of the API functions provided by the BLE Database
 *          Discovery module, as well as necessary type definitions and macros. It should be included
 *          where BLE service discovery functionality is required.
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**
 * @addtogroup BLE_DD_DEFINES Defines
 * @{
 */
 
/**
 * @defgroup BLE_DD_CHAR_SETTING Characteristic setting
 * @brief  Defines the related to characteristic settings during discovery.
 * @{
 */
#define CHAR_SET_DESCRIPTOR                         (0x01U)    /**< Flag indicating if this is a characteristic descriptor. */
/** @} */


/**
 * @defgroup BLE_DD_MAX_REG_NUM Maximum register services number
 * @brief Defines the maximum number of services that can be registered in the BLE_DD module.
 * @{
 */
#define BLE_DD_MAX_DISC_SVC_NUM                     (0x06U)    /**< Maximum number of services that can be registered. */
/** @} */


/** @} */ //BLE_DD_DEFINES

/**
 * @addtogroup BLE_DD_ENUMS Enumerations
 * @{
 */
 
/** @brief Enumeration of BLE Device Discovery (BLE_DD) module event identifiers. */
typedef enum BLE_DD_EventId_T
{
    BLE_DD_EVT_DISC_COMPLETE,                                  /**< Discovery of all services completed. Refer to @ref BLE_DD_EvtDiscResult_T for result details. */
    BLE_DD_EVT_SEC_REQUIRED,                                   /**< Security action required for characteristic access. Initiate encryption/authentication as needed. 
                                                                    Refer to @ref BLE_DD_EvtSecRequire_T. */
    BLE_DD_EVT_CONNECTED,                                      /**< BLE connection established. Refer to @ref BLE_DD_EvtConnect_T for event details. */
    BLE_DD_EVT_DISCONNECTED,                                   /**< BLE connection terminated. Refer to @ref BLE_DD_EvtDisconnect_T for event details. */
    BLE_DD_EVT_END                                             /**< End of BLE_DD event identifiers. */
}BLE_DD_EventId_T;

/** @} */ //BLE_DD_ENUMS
// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup BLE_DD_STRUCTS Structures
 * @{
 */

/** @brief Structure representing a universally unique identifier (UUID) for ATT (Attribute Protocol) operations. */
typedef struct ATT_Uuid_T
{
    uint8_t                 uuid[ATT_MAX_UUID_SIZE];/**< Array to store the UUID value. The maximum size is defined by @ref ATT_MAX_UUID_SIZE. */
    uint8_t                 uuidLength;             /**< The actual length of the UUID stored in the array. This can vary depending on whether 
                                                            a 16-bit, 32-bit, or 128-bit UUID is used. */
} ATT_Uuid_T;


/** @brief Structure for configuring parameters for BLE device discovery. */
typedef struct BLE_DD_Config_T
{
    unsigned int      		waitForSecurity:1;      /**< Specifies whether security is required before initiating database discovery. Set to 1 to enable. */
    unsigned int            initDiscInCentral:1;    /**< Enables discovery when the GAP role of the connection is central. Set to 1 to enable. */
    unsigned int            initDiscInPeripheral:1; /**< Enables discovery when the GAP role of the connection is peripheral. Set to 1 to enable. */
    unsigned int            disableConnectedDisc:1; /**< Disables the discovery process once a connection is established. This may be optional for 
                                                            bonded links. Note: This is a one-time setting. Disable unnecessary discovery for each 
                                                            connected instance. */
    unsigned int            reserved:4;             /**< Reserved bits for future use. */
} BLE_DD_Config_T;


/** @brief Structure for information about a specific BLE characteristic. */
typedef struct BLE_DD_CharInfo_T
{
    uint16_t                charHandle;             /**< Handle of the characteristic. */
    uint8_t                 property;               /**< Properties of the characteristic. Relevant when the characteristic type is a characteristic declaration. */
    uint16_t                attrHandle;             /**< Attribute handle associated with the characteristic. */
} BLE_DD_CharInfo_T;


/** @brief Structure for a list of characteristics associated with a BLE connection. */
typedef struct BLE_DD_CharList_T
{
    uint16_t                connHandle;             /**< Connection handle associated with this connection. */
    BLE_DD_CharInfo_T       *p_charInfo;            /**< Pointer to an array of characteristic information structures. See @ref BLE_DD_CharInfo_T. */
} BLE_DD_CharList_T;


/** @brief Structure for the range of a primary service during discovery. */
typedef struct BLE_DD_DiscInfo_T
{
    uint16_t                svcStartHandle;         /**< Starting handle of the discovered service.  */
    uint16_t                svcEndHandle;           /**< Ending handle of the discovered service. */
}BLE_DD_DiscInfo_T;


/** @brief Structure for the characteristic information used during the discovery process. */
typedef struct BLE_DD_DiscChar_T
{
    ATT_Uuid_T const        *p_uuid;                /**< Pointer to the UUID of the characteristic. See @ref ATT_Uuid_T. */
    uint8_t                 settings;               /**< Settings for characteristic discovery. See @ref BLE_DD_CHAR_SETTING for valid value.*/
} BLE_DD_DiscChar_T;


/** @brief Structure for service information used during the discovery process. */
typedef struct BLE_DD_DiscSvc_T
{
    ATT_Uuid_T              svcUuid;                /**< UUID of the service to be discovered. See @ref ATT_Uuid_T. */
    BLE_DD_DiscInfo_T       *p_discInfo;            /**< Pointer to the discovered service information. See @ref BLE_DD_DiscInfo_T. */
    BLE_DD_DiscChar_T       **p_discChars;          /**< Pointer to an array of pointers to characteristic discovery information. 
                                                            Note: Only specified characteristics will be discovered. See @ref BLE_DD_DiscChar_T. */
    BLE_DD_CharList_T       *p_charList;            /**< Pointer to a structure that stores the discovered characteristics' information. 
                                                            The application/profile must provide storage. See @ref BLE_DD_CharList_T. */
    uint8_t                 discCharsNum;           /**< Number of characteristics in the discovery list. */
} BLE_DD_DiscSvc_T;


/** @brief Structure for @ref BLE_DD_EVT_DISC_COMPLETE event. */
typedef struct BLE_DD_EvtDiscResult_T
{
    uint16_t                connHandle;             /**< Connection handle associated with this connection. */
} BLE_DD_EvtDiscResult_T;


/** @brief Structure for @ref BLE_DD_EVT_SEC_REQUIRED event. */
typedef struct BLE_DD_EvtSecRequire_T
{
    uint16_t                connHandle;             /**< Connection handle associated with this connection. */
} BLE_DD_EvtSecRequire_T;


/** @brief Structure for @ref BLE_DD_EVT_CONNECTED event. */
typedef struct BLE_DD_EvtConnect_T
{
    uint16_t                connHandle;             /**< Connection handle associated with this connection. */
} BLE_DD_EvtConnect_T;


/** @brief Structure for @ref BLE_DD_EVT_DISCONNECTED event. */
typedef struct BLE_DD_EvtDisconnect_T
{
    uint16_t                connHandle;             /**< Connection handle associated with this connection. */
} BLE_DD_EvtDisconnect_T;


/** @brief Union of BLE_DD callback event data structures. */
typedef union
{
    BLE_DD_EvtDiscResult_T  evtDiscResult;          /**< Data for @ref BLE_DD_EVT_DISC_COMPLETE event. */
    BLE_DD_EvtSecRequire_T  evtSecRequire;          /**< Data for @ref BLE_DD_EVT_SEC_REQUIRED event. */
    BLE_DD_EvtConnect_T     evtConnect;             /**< Data for @ref BLE_DD_EVT_CONNECTED event. */
    BLE_DD_EvtDisconnect_T  evtDisconnect;          /**< Data for @ref BLE_DD_EVT_DISCONNECTED event. */
} BLE_DD_EventField_T;


/** @brief BLE DD callback event structure. */
typedef struct  BLE_DD_Event_T
{
    BLE_DD_EventId_T        eventId;                /**< Identifier for the type of event. See @ref BLE_DD_EventId_T. */
    BLE_DD_EventField_T     eventField;             /**< Union containing the event data. See @ref BLE_DD_EventField_T. */
} BLE_DD_Event_T;


/**
 * @brief Callback type for BLE_DD events.
 * 
 * This callback function is used to send BLE_DD events to the application.
 * 
 * @param p_event Pointer to the event structure containing event details. See @ref BLE_DD_Event_T.
 */
typedef void (*BLE_DD_EventCb_T)(BLE_DD_Event_T *p_event);

/** @} */ //BLE_DD_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup BLE_DD_FUNS Functions
 * @{
 */
 
/**
 * @brief Initializes the BLE Device Discovery (BLE_DD) module.
 *
 * @retval true                 Initialization of the BLE_DD module was successful.
 * @retval false                Initialization of the BLE_DD module failed.
*/
bool BLE_DD_Init(void);


/**
 * @brief Registers a callback for BLE Device Discovery (BLE_DD) events.
 * @note  This function should be called during the application initialization process.
 *
 * @param[in] eventCb           Pointer to the function to be called when a BLE_DD event occurs. See @ref BLE_DD_EventCb_T.
 *
*/
void BLE_DD_EventRegister(BLE_DD_EventCb_T eventCb);


/**
 * @brief Registers a specific service with the database discovery module.
 * @note  The service discovery process will be initiated by the module after a connection is established.
 *
 * @param[in] p_discSvc          Pointer to the service discovery structure to be registered. See @ref BLE_DD_DiscSvc_T.
 *
 * @retval MBA_RES_SUCCESS       Service successfully registered for discovery.
 * @retval MBA_RES_FAIL          Failed to register service due to exceeding the maximum limit.
*/
uint16_t BLE_DD_ServiceDiscoveryRegister(BLE_DD_DiscSvc_T *p_discSvc);


/**
 * @brief Handles BLE events by passing them to the BLE Device Discovery (BLE_DD) module.
 * @note  This function must be called for each BLE event that occurs.
 *
 * @param[in] p_config          Pointer to the BLE_DD configuration structure. See @ref BLE_DD_Config_T.
 * @param[in] p_stackEvent      Pointer to the BLE stack event structure. See @ref STACK_Event_T.
 *
*/
void BLE_DD_BleEventHandler(BLE_DD_Config_T *p_config, STACK_Event_T *p_stackEvent);


/**
 * @brief Restarts the database discovery process for a specific connection.
 * @note  This function should be called when the remote services have changed and there is a need to rediscover them.
 *
 * @param[in] connHandle        Connection handle associated with this connection.
 *
 * @retval MBA_RES_SUCCESS      Discovery successfully restarted.
 * @retval MBA_RES_OOM          Failed due to memory allocation error.
 * @retval MBA_RES_INVALID_PARA The provided connHandle is invalid.
*/
uint16_t BLE_DD_RestartServicesDiscovery(uint16_t connHandle);

/** @} */ //BLE_DD_FUNS

/** @} */

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif //BLE_DD_H