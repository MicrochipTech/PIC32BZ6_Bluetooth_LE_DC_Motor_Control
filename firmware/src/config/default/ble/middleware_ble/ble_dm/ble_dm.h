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
  BLE Device Manager Middleware Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm.h

  Summary:
    Interface for the BLE Device Manager, facilitating BLE security procedures
    and management of paired device information.

  Description:
    This header defines the API for the BLE Device Manager module. It provides
    necessary functions and events to manage BLE devices within an application.
    Initialize this module by calling 'BLE_DM_Init' during the application's
    initialization phase.
 *******************************************************************************/
#ifndef BLE_DM_H
#define BLE_DM_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include "mba_error_defs.h"
#include "stack_mgr.h"
#include "gap_defs.h"
#include "ble_gap.h"
#include "ble_l2cap.h"
#include "gatt.h"
#include "ble_smp.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/**
 * @addtogroup BLE_MW BLE Middleware
 * @brief Interfaces between the BLE library and the application, simplifying BLE operations.
 * @{
 */

/**
 * @defgroup BLE_DM BLE Device Mananger Module (BLE_DM)
 * 
 * @brief Manages BLE security and paired device information.
 * @note Provides an API for initializing and managing BLE device connections
 *          and security. Include this header and call 'BLE_DM_Init' to prepare
 *          the BLE Device Manager for use.
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup BLE_DM_DEFINES Defines
 * @{
 */

/**
 * @defgroup BLE_DM_MAX_RETISTER_NUM Maximum registration number
 * @brief Defines the maximum number of registrations allowed in BLE Device Manager (BLE_DM).
 * @{
 */
#define BLE_DM_MAX_REGISTER_NUM                 (2U)                                        /**< Maximum number of registrations in BLE_DM. */
/** @} */


/**
 * @defgroup BLE_DM_MAX_PAIRED_DEVICE_NUM Maximum paired devices
 * @brief Defines the maximum number of paired devices that can be stored in flash memory.
 * @{
 */
#define BLE_DM_MAX_PAIRED_DEVICE_NUM            (8U)                                        /**< Maximum number of paired devices stored in flash. */
/** @} */


/**
 * @defgroup BLE_DM_PEER_DEV_ID_INVALID Invalid peer device ID
 * @brief Defines an invalid peer device ID value.
 * @{
 */
#define BLE_DM_PEER_DEV_ID_INVALID              BLE_DM_MAX_PAIRED_DEVICE_NUM                /**< Value representing an invalid peer device ID. */
/** @} */

/**
 * @defgroup BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM Maximum filter accept list size
 * @brief Defines the maximum number of devices that can be included in the filter accept list.
 * @{
 */
#define BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM       BLE_DM_MAX_PAIRED_DEVICE_NUM                /**< Maximum size of the filter accept list. */
/** @} */

/**
 * @defgroup BLE_DM_MAX_RESOLVING_LIST_NUM Maximum resolving list size
 * @brief Defines the maximum number of devices that can be included in the resolving list.
 * @{
 */
#define BLE_DM_MAX_RESOLVING_LIST_NUM           BLE_DM_MAX_PAIRED_DEVICE_NUM                /**< Maximum size of the resolving list. */
/** @} */



/** @} */ //BLE_DM_DEFINES


/**
 * @addtogroup BLE_DM_ENUMS Enumerations
 * @{
 */

/** @brief Enumeration type for BLE Device Manager callback events. */
typedef enum BLE_DM_EventId_T
{
    BLE_DM_EVT_DISCONNECTED,                    /**< BLE link has been terminated. Refer to @ref BLE_DM_Event_T for event details. */
    BLE_DM_EVT_CONNECTED,                       /**< BLE link has been established. Refer to @ref BLE_DM_Event_T for event details. */
    BLE_DM_EVT_SECURITY_START,                  /**< Security procedure has started. Refer to @ref BLE_DM_EvtSecurityStart_T for event detail. */
    BLE_DM_EVT_SECURITY_SUCCESS,                /**< Security procedure has completed successfully. Refer to @ref BLE_DM_EvtSecuritySuccess_T for event detail */
    BLE_DM_EVT_SECURITY_FAIL,                   /**< Security procedure has failed. Refer to @ref BLE_DM_EvtSecurityFail_T for event detail. */
    BLE_DM_EVT_PAIRED_DEVICE_FULL,              /**< Paired device list is full. No new devices can be added. Consider removing unnecessary devices. 
                                                        Refer to @ref BLE_DM_EvtPairedDeviceFull_T for event details. */
    BLE_DM_EVT_PAIRED_DEVICE_UPDATED,           /**< A paired device has been updated. Use peerDevId to retrieve paired device information with @ref BLE_DM_GetPairedDevice. */
    BLE_DM_EVT_CONN_UPDATE_SUCCESS,             /**< Connection parameter update has succeeded. Refer to @ref BLE_DM_Event_T for event details. */
    BLE_DM_EVT_CONN_UPDATE_FAIL,                /**< Connection parameter update has failed. Refer to @ref BLE_DM_Event_T for event details. */

    BLE_DM_EVT_END
}BLE_DM_EventId_T;

/** @brief Enumeration for security processes in BLE Device Manager. */
typedef enum BLE_DM_SecurityProc_T
{
    DM_SECURITY_PROC_PAIRING,                   /**< Pairing procedure is in progress. */
    DM_SECURITY_PROC_ENCRYPTION,                /**< Link encryption is in progress. */
} BLE_DM_SecurityProc_T;

/** @} */ //BLE_DM_ENUMS

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup BLE_DM_STRUCTS Structures
 * @{
 */

/** @brief Structure for @ref BLE_DM_EVT_SECURITY_START event. */
typedef struct BLE_DM_EvtSecurityStart_T
{
    BLE_DM_SecurityProc_T           procedure;                      /**< Security procedure that has been initiated. Refer to @BLE_DM_SecurityProc_T for the definitions. */
} BLE_DM_EvtSecurityStart_T;

/** @brief Structure for @ref BLE_DM_EVT_SECURITY_SUCCESS event. */
typedef struct BLE_DM_EvtSecuritySuccess_T
{
    BLE_DM_SecurityProc_T           procedure;                      /**< Security procedure that completed successfully. Refer to @BLE_DM_SecurityProc_T for the definitions. */
    bool                            bonded;                         /**< Indicates whether the pairing is bonded. True if bonded. */
} BLE_DM_EvtSecuritySuccess_T;


/** @brief Structure for @ref BLE_DM_EVT_SECURITY_FAIL event. */
typedef struct BLE_DM_EvtSecurityFail_T
{
    BLE_DM_SecurityProc_T           procedure;                      /**< Security procedure that failed. Refer to @BLE_DM_SecurityProc_T for the definitions. */
    uint8_t                         error;                          /**< Error code indicating the type of failure. Refer to @ref BLE_SMP_PAIRING_RESULT if procedure is @ref DM_SECURITY_PROC_PAIRING. */
    uint8_t                         reason;                         /**< Specific reason for the failure. Refer to @ref BLE_SMP_PAIRING_FAIL_REASON if error is BLE_SMP_PAIRING_FAIL. */
} BLE_DM_EvtSecurityFail_T;


/** @brief Structure for @ref BLE_DM_EVT_PAIRED_DEVICE_FULL event. */
typedef struct BLE_DM_EvtPairedDeviceFull_T
{
    uint8_t                         pairedDeviceNum;                /**< Current count of paired devices stored in flash. */
} BLE_DM_EvtPairedDeviceFull_T;


/** @brief Union of BLE_DM callback event data types. */
typedef union
{
    BLE_DM_EvtSecurityStart_T       evtSecurityStart;               /**< Data for @ref BLE_DM_EVT_SECURITY_START event.*/
    BLE_DM_EvtSecuritySuccess_T     evtSecuritySuccess;             /**< Data for @ref BLE_DM_EVT_SECURITY_SUCCESS event.*/
    BLE_DM_EvtSecurityFail_T        evtSecurityFail;                /**< Data for @ref BLE_DM_EVT_SECURITY_FAIL event.*/
    BLE_DM_EvtPairedDeviceFull_T    evtPairedDevFull;               /**< Data for @ref BLE_DM_EVT_PAIRED_DEVICE_FULL event. */
} BLE_DM_EventField_T;


/** @brief BLE_DM callback event structure. */
typedef struct  BLE_DM_Event_T
{
    BLE_DM_EventId_T                eventId;                        /**< Identifier for the event.*/
    uint16_t                        connHandle;                     /**< Connection handle associated with this connection. */
    uint8_t                         peerDevId;                      /**< Identifier for the peer device. */
    BLE_DM_EventField_T             eventField;                     /**< Union containing event-specific data. */
} BLE_DM_Event_T;


/** @brief Structure for containing connection parameters configuration. */
typedef struct BLE_DM_ConnConfig_T
{
    uint16_t                        minAcceptConnInterval;          /**< Minimum acceptable connection interval. */
    uint16_t                        maxAcceptConnInterval;          /**< Maximum acceptable connection interval. */
    uint16_t                        minAcceptPeripheralLatency;     /**< Minimum acceptable peripheral latency. */
    uint16_t                        maxAcceptPeripheralLatency;     /**< Maximum acceptable peripheral latency. */
    bool                            autoReplyUpdateRequest;         /**< Enable automatic reply to connection parameter update requests such as 
                                                                        @ref BLE_L2CAP_EVT_CONN_PARA_UPDATE_REQ or @ref BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST if true. */
} BLE_DM_ConnConfig_T;


/** @brief Structure for configuring connection parameters and security settings. */
typedef struct BLE_DM_Config_T
{
    BLE_DM_ConnConfig_T             connConfig;                    /**< Connection parameters configuration. Refer to @ref BLE_DM_ConnConfig_T for the detail. */
    bool                            secAutoAccept;                 /**< Automatically accept pairing or security requests if true. */
} BLE_DM_Config_T;


/** @brief Structure for containing information about paired device information. */
typedef struct BLE_DM_PairedDevInfo_T
{
    BLE_GAP_Addr_T                  remoteAddr;                    /**< Bluetooth address of the paired device. See @ref BLE_GAP_Addr_T for structure details.*/
    uint8_t                         remoteIrk[16];                 /**< Identity resolving key of the paired device. */
    BLE_GAP_Addr_T                  localAddr;                     /**< Bluetooth address of the local device. See @ref BLE_GAP_Addr_T for structure details. */
    uint8_t                         localIrk[16];                  /**< Identity resolving key of the local device. */
    uint8_t                         rv[8];                         /**< Random value used in the pairing process. */
    uint8_t                         ediv[2];                       /**< Encrypted diversifier used in the pairing process. */
    uint8_t                         ltk[16];                       /**< Long term key for the BLE link. */
    unsigned int                    lesc:1;                        /**< Indicates use of LE secure connection if set. */
    unsigned int                    auth:1;                        /**< Indicates authenticated pairing if set. */
    unsigned int                    encryptKeySize:6;              /**< Encryption key size (7-16 bytes). */
}BLE_DM_PairedDevInfo_T;


/** @brief Structure for containing information about connection parameter update. */
typedef struct BLE_DM_ConnParamUpdate_T
{
    uint16_t                        intervalMin;                    /**< Minimum connection interval. */
    uint16_t                        intervalMax;                    /**< Maximum connection interval. */
    uint16_t                        latency;                        /**< Number of connection events the peripheral can skip. */
    uint16_t                        timeout;                        /**< Supervision timeout, after which the connection is considered lost. */
} BLE_DM_ConnParamUpdate_T;


/**
 * @brief Callback type for BLE_DM events.
 * 
 * This callback function is used to send BLE_DM events to the application.
 * 
 * @param p_event Pointer to the event structure containing event details.
 */
typedef void (*BLE_DM_EventCb_T)(BLE_DM_Event_T *p_event);

/** @} */ //BLE_DM_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup BLE_DM_FUNS Functions
 * @{
 */
 
/**
 * @brief Initializes the BLE_DM module.
 *
 * @retval true                     Initialization of BLE_DM module was successful.
 * @retval false                    Initialization of BLE_DM module failed.
*/
bool BLE_DM_Init(void);


/**
 * @brief Registers a callback function for BLE_DM events.
 * @note  This API should be called during the application initialization phase.
 *
 * @param[in] eventCb               The client callback function to register. See @ref BLE_DM_EventCb_T for structure details.
 *
 * @retval MBA_RES_SUCCESS          Callback function registered successfully.
 * @retval MBA_RES_NO_RESOURCE      Failed to register the callback function due to resource constraints.
 * 
*/
uint16_t BLE_DM_EventRegister(BLE_DM_EventCb_T eventCb);


/**
 * @brief Handles BLE stack events.
 * @note  This function should be called when BLE events are received.
 *
 * @param[in] p_stackEvent          Pointer to the BLE events buffer. See @ref STACK_Event_T for structure details.
*/
void BLE_DM_BleEventHandler(STACK_Event_T *p_stackEvent);


/**
 * @brief Configures the BLE_DM module.
 *       
 *
 * @param[in] p_config              Pointer to the configuration structure of type @ref BLE_DM_Config_T.
 *
 * @retval MBA_RES_SUCCESS          Configuration was successful.
 * @retval MBA_RES_INVALID_PARA     The provided configuration parameter is invalid.
*/
uint16_t BLE_DM_Config(BLE_DM_Config_T *p_config);


/**
 * @brief Initiates the security process based on the current role and pairing status.
 * @note  For the Central role, if paired information exists in PDS for the connected peer device,
 *        @ref BLE_GAP_StartEncryption will be called to initiate the encryption procedure.
 *        Otherwise, BLE_SMP_InitiatePairing will be called to start the pairing procedure.\n
 * 
 *        For the Peripheral role, BLE_DM will call @ref BLE_SMP_InitiatePairing to trigger an SMP security request.
 *        The remote Central device will then decide to initiate either pairing or encryption.
 *
 * @param[in] connHandle            Connection handle associated with this connection.
 * @param[in] repairing             For the Central role, set to true to force re-pairing; otherwise, set to false.
 *
 * @retval MBA_RES_SUCCESS          Security process initiated successfully.
 * @retval MBA_RES_OOM              Failed due to internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA     The connection handle is invalid.
*/
uint16_t BLE_DM_ProceedSecurity(uint16_t connHandle, bool repairing);


/**
 * @brief Sets the filter accept list.
 * 
 * @param[in] devCnt                The number of devices to add to the filter accept list. Must be less than or equal to
 *                                  @ref BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM. Pass zero to clear the list.
 * @param[in] p_devId               Pointer to the list of device IDs to add. Pass NULL to clear the list.
 *
 * @retval MBA_RES_SUCCESS          Filter accept list set or cleared successfully.
 * @retval MBA_RES_INVALID_PARA     The devCnt exceeds @ref BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM.
*/
uint16_t BLE_DM_SetFilterAcceptList(uint8_t devCnt, uint8_t const *p_devId);


/**
 * @brief Retrieves the filter accept list.
 * 
 * @param[out] p_devCnt             Pointer to the variable to store the number of devices in the list.
 * @param[out] p_addr               Pointer to the buffer to store the list of @ref BLE_GAP_Addr_T structures.
 *
 * @retval MBA_RES_SUCCESS          Successfully retrieved the filter accept list.
*/
uint16_t BLE_DM_GetFilterAcceptList(uint8_t *p_devCnt, BLE_GAP_Addr_T *p_addr);


/**
 * @brief Sets the resolving list.
 * 
 * @param[in] devCnt                The number of devices to add to the resolving list. Must be less than or equal to
 *                                  @ref BLE_DM_MAX_RESOLVING_LIST_NUM. Pass zero to clear the list.
 * @param[in] p_devId               Pointer to the list of device IDs to add. Pass NULL to clear the list.
 * @param[in] p_privacyMode;        Pointer to the list of privacy modes corresponding to each device ID. Pass NULL to clear the list.
 *                                  Refer to @ref BLE_GAP_PRIVACY_MODE for possibile values.
 *
 * @retval MBA_RES_SUCCESS          Resolving list set or cleared successfully.
 * @retval MBA_RES_INVALID_PARA     The devCnt exceeds @ref BLE_DM_MAX_RESOLVING_LIST_NUM.
*/
uint16_t BLE_DM_SetResolvingList(uint8_t devCnt, uint8_t const *p_devId, uint8_t const * p_privacyMode);


/**
 * @brief Deletes specific paired device information.
 * @note  Use @ref BLE_DM_GetPairedDeviceList to retrieve the list of paired device IDs.
 *
 * @param[in] devId                  The device ID of the paired device to delete.
 *
 * @retval MBA_RES_SUCCESS           Specific paired device information deleted successfully.
 * @retval MBA_RES_INVALID_PARA      The device ID does not correspond to a valid paired device.
 * @retval MBA_RES_FAIL              Deletion operation failed.
*/
uint16_t BLE_DM_DeletePairedDevice(uint8_t devId);


/**
 * @brief Retrieves information for a single paired device by device ID.
 *
 * @param[in] devId                  The device ID within the range of 0 to (@ref BLE_DM_MAX_PAIRED_DEVICE_NUM - 1).
 * @param[out] p_pairedDevInfo       Pointer to the @ref BLE_DM_PairedDevInfo_T structure to store the paired device information.
 *
 * @retval MBA_RES_SUCCESS           Successfully retrieved paired device information.
 * @retval MBA_RES_INVALID_PARA      The device ID is out of range or exceeds the number of paired devices.
 * @retval MBA_RES_FAIL              Retrieval operation failed.
 */
uint16_t BLE_DM_GetPairedDevice(uint8_t devId, BLE_DM_PairedDevInfo_T *p_pairedDevInfo);


/**
 * @brief Deletes all paired device information.
 *
 *
 * @retval MBA_RES_SUCCESS           All paired device information deleted successfully.
 * @retval MBA_RES_FAIL              Deletion operation failed.
*/
uint16_t BLE_DM_DeleteAllPairedDevice(void);


/**
 * @brief Retrieves the list of device IDs for all paired devices.
 *
 * @param[out] p_devId               Pointer to the buffer to store the device IDs.
 * @param[out] p_devCnt              Pointer to the variable to store the count of valid device IDs in p_devId.
 *
*/
void BLE_DM_GetPairedDeviceList(uint8_t *p_devId, uint8_t *p_devCnt);


/**
 * @brief Requests a change in the connection parameters for a specific connection.
 *
 * @param[in] connHandle             Connection handle associated with this connection.
 * @param[in] p_params               Pointer to the @ref BLE_DM_ConnParamUpdate_T structure containing the new parameters.
 *
 * @retval MBA_RES_SUCCESS           Update request sent successfully to the remote device.
 * @retval MBA_RES_FAIL              Update procedure is disallowed under certain conditions.
 * @retval MBA_RES_OOM               Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA      Invalid connection handle.
*/
uint16_t BLE_DM_ConnectionParameterUpdate(uint16_t connHandle, BLE_DM_ConnParamUpdate_T *p_params);

/** @} */ //BLE_DM_FUNS

/** @} */

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif //BLE_DM_H