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
  BLE SMP Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_smp.h

  Summary:
    This header file provides the BLE Security Manager Protocol (SMP) functions 
    for application developers.


  Description:
    This header file defines the interface for the BLE Security Manager Protocol 
    (SMP) within the BLE stack. It includes function prototypes and 
    event definitions necessary for an application user to interact with the 
    BLE SMP layer. The "BLE_SMP_Init" function must be invoked during the 
    application initialization phase, typically within the "APP_Initialize" 
    function, to set up the SMP module within the system.
 *******************************************************************************/
#ifndef BLE_SMP_H
#define BLE_SMP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "ble_gap.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/**
 * @defgroup BLE_SMP Security Manager Protocol (SMP)
 * @brief Defines the interface for the BLE SMP functions provided by the BLE Library.
 * @note  This section provides detailed descriptions of the function 
 *        interfaces and events related to the BLE Security Manager Protocol. 
 *        It includes necessary definitions and function prototypes to enable 
 *        application developers to utilize the SMP features in their BLE 
 *        applications. Note that this interface is part of the BLE stack 
 *        layer and is intended for direct use by application developers.
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**
 * @addtogroup BLE_SMP_DEFINESS Defines
 * @{
 */
 
/**
 * @defgroup BLE_SMP_IO_CAPABILITY_DEF IO capability
 * @brief Defines SMP io (Input/Output) capabilities.
 * @{
 */
#define BLE_SMP_IO_DISPLAYONLY                              (0x00U)        /**< Device can display a 6-digit decimal number but lacks input buttons for 'yes' or 'no' confirmation. */
#define BLE_SMP_IO_DISPLAYYESNO                             (0x01U)        /**< Device can display a 6-digit decimal number and has input buttons that can be mapped to 'yes' or 'no' for confirmation. */
#define BLE_SMP_IO_KEYBOARDONLY                             (0x02U)        /**< Device has a numeric keyboard for inputting numbers 0-9 and confirmation, but cannot display a 6-digit decimal number. */
#define BLE_SMP_IO_NOINPUTNOOUTPUT                          (0x03U)        /**< Device lacks both input capabilities (no 'yes' or 'no' confirmation) and the ability to display a 6-digit decimal number. */
#define BLE_SMP_IO_KEYBOARDDISPLAY                          (0x04U)        /**< Device has a numeric keyboard for inputting numbers 0-9 and confirmation, and can display a 6-digit decimal number. */
/** @} */


/**
 * @defgroup BLE_SMP_OPTION Pairing options
 * @brief Defines pairing options for Bluetooth Low Energy Security Manager Protocol (SMP).
 * @note Possible combinations are :
 * - BLE_SMP_OPTION_NONE : No bonding, use LE legacy pairing.
 * - BLE_SMP_OPTION_BONDING  : Bonding requested, use LE legacy pairing.
 * - BLE_SMP_OPTION_SECURE_CONNECTION : No bonding, prefer LE Secure Connections if supported, otherwise use LE legacy pairing.
 * - BLE_SMP_OPTION_BONDING | BLE_SMP_OPTION_SECURE_CONNECTION : Bonding requested, prefer LE Secure Connections if supported, otherwise use LE legacy pairing.
 * - BLE_SMP_OPTION_MITM : Man-In-The-Middle (MITM) protection required, no bonding, use LE legacy pairing.
 * - BLE_SMP_OPTION_BONDING | BLE_SMP_OPTION_MITM : Bonding requested, MITM protection required, use LE legacy pairing.
 * - BLE_SMP_OPTION_MITM | BLE_SMP_OPTION_SECURE_CONNECTION : MITM protection required, no bonding, prefer LE Secure Connections if supported, otherwise use LE legacy pairing.
 * - BLE_SMP_OPTION_BONDING | BLE_SMP_OPTION_MITM | BLE_SMP_OPTION_SECURE_CONNECTION : Bonding requested, MITM protection required, prefer LE Secure Connections if supported, otherwise use LE legacy pairing.
 * - BLE_SMP_OPTION_SECURE_CONNECTION | BLE_SMP_OPTION_KEYPRESS : No bonding, prefer LE Secure Connections if supported, otherwise use LE legacy pairing, enable keypress notifications.
 * - BLE_SMP_OPTION_BONDING | BLE_SMP_OPTION_SECURE_CONNECTION | BLE_SMP_OPTION_KEYPRESS : Bonding requested, prefer LE Secure Connections if supported, otherwise use LE legacy pairing, enable keypress notifications.
 * - BLE_SMP_OPTION_MITM | BLE_SMP_OPTION_SECURE_CONNECTION | BLE_SMP_OPTION_KEYPRESS : MITM protection required, no bonding, prefer LE Secure Connections if supported, otherwise use LE legacy pairing, enable keypress notifications.
 * - BLE_SMP_OPTION_BONDING | BLE_SMP_OPTION_MITM | BLE_SMP_OPTION_SECURE_CONNECTION | BLE_SMP_OPTION_KEYPRESS : Bonding requested, MITM protection required, prefer LE Secure Connections if supported, otherwise use LE legacy pairing, enable keypress notifications.
 *
 * @{
 */
#define BLE_SMP_OPTION_NONE                                 (0x00U)        /**< No bonding; keys are not stored. */
#define BLE_SMP_OPTION_BONDING                              (0x01U)        /**< Bonding allowed; exchange and store security and identity information. */
#define BLE_SMP_OPTION_MITM                                 (0x04U)        /**< Man-In-The-Middle (MITM) protection requested. */
#define BLE_SMP_OPTION_SECURE_CONNECTION                    (0x08U)        /**< LE Secure Connections pairing requested. */
#define BLE_SMP_OPTION_KEYPRESS                             (0x10U)        /**< Keypress notifications enabled. */
/** @} */


/**
 * @defgroup BLE_SMP_CONFIRM Confirm result
 * @brief Defines user confirmation results for pairing.
 * @{
 */
#define BLE_SMP_CONFIRM_YES                                 (0x00U)        /**< User confirms "YES". */
#define BLE_SMP_CONFIRM_NO                                  (0x01U)        /**< User confirms "NO". */
/** @} */


/**
 * @defgroup BLE_SMP_PAIRING_RESULT Pairing result
 * @brief Defines the possible outcomes of the BLE pairing process.
 * @{
 */
#define BLE_SMP_PAIRING_SUCCESS                             (0x00U)        /**< Indicates that the pairing process completed successfully. */
#define BLE_SMP_PAIRING_FAIL                                (0x01U)        /**< Indicates that the pairing process failed to complete. */
#define BLE_SMP_PAIRING_TIMEOUT                             (0x02U)        /**< Indicates that the pairing process did not complete within the expected time frame. */
/** @} */


/**
 * @defgroup BLE_SMP_PAIRING_FAIL_REASON Pairing failure reasons
 * @brief Enumerates the reasons why a BLE pairing process may fail.
 * @{
 */
#define BLE_SMP_REASON_PASSKEY_ENTRY_FAILED                 (0x01U)        /**< User failed to correctly input the passkey. */
#define BLE_SMP_REASON_OOB_NOT_AVAILABLE                    (0x02U)        /**< Out-of-Band (OOB) data required for pairing is not available. */
#define BLE_SMP_REASON_AUTH_REQ                             (0x03U)        /**< Authentication requirements could not be satisfied due to insufficient IO capabilities. */
#define BLE_SMP_REASON_CONFIRM_VALUE_FAILED                 (0x04U)        /**< The confirmation value exchanged during pairing does not match. */
#define BLE_SMP_REASON_PAIRING_NOT_SUPPORTED                (0x05U)        /**< The device does not support pairing. */
#define BLE_SMP_REASON_ENCRYPT_KEY_SIZE                     (0x06U)        /**< The encryption key size is too small for secure communication. */
#define BLE_SMP_REASON_COMMAND_NOT_SUPPORTED                (0x07U)        /**< The received SMP command is not supported by the device. */
#define BLE_SMP_REASON_UNSPECIFIED_REASON                   (0x08U)        /**< Pairing failed for an unspecified reason. */
#define BLE_SMP_REASON_REPEATED_ATTEMPTS                    (0x09U)        /**< Pairing failed due to repeated attempts in a short period. */
#define BLE_SMP_REASON_INVALID_PARAMETERS                   (0x0AU)        /**< Invalid parameters were provided in the SMP command. */
#define BLE_SMP_REASON_DHKEY_CHECK_FAILED                   (0x0BU)        /**< The DHKey Check value does not match the expected value. */
#define BLE_SMP_REASON_NUMERIC_COMPARISON_FAILED            (0x0CU)        /**< Numeric comparison during pairing failed due to mismatched confirmation values. */
/** @} */


/**
 * @defgroup BLE_SMP_FLAG_KEY_VALID Key flags
 * @brief Defines flags indicating the validity of remote keys.
 * @{
 */
#define BLE_SMP_FLAG_ENCRYPT_INFO                           (1U<<0U)      /**< Indicates that the Long Term Key (LTK) is valid. */
#define BLE_SMP_FLAG_CENTRAL_ID                             (1U<<1U)      /**< Indicates that the Encrypted Diversifier (EDIV) and Random Value (Rand) are valid. */
#define BLE_SMP_FLAG_ID_INFO                                (1U<<2U)      /**< Indicates that the Identity Resolving Key (IRK) is valid. */
#define BLE_SMP_FLAG_ID_ADDR_INFO                           (1U<<3U)      /**< Indicates that the identity address is valid. */
#define BLE_SMP_FLAG_SIGNING_INFO                           (1U<<4U)      /**< Indicates that the Signature Resolving Key (SRK) is valid. */
/** @} */

/**
 * @defgroup BLE_SMP_KEYPRESS_NOTI_TYPE Keypress notification types
 * @brief Defines the types of keypress notifications during passkey entry.
 * @{
 */
#define BLE_SMP_KEYPRESS_STARTED                            (0x00U)        /**< Notification that passkey entry has started. */
#define BLE_SMP_KEYPRESS_DIGIT_ENTERED                      (0x01U)        /**< Notification that a digit of the passkey has been entered. */
#define BLE_SMP_KEYPRESS_DIGIT_ERASED                       (0x02U)        /**< Notification that a digit of the passkey has been erased. */
#define BLE_SMP_KEYPRESS_CLEARED                            (0x03U)        /**< Notification that the passkey has been cleared. */
#define BLE_SMP_KEYPRESS_COMPLETED                          (0x04U)        /**< Notification that passkey entry has been completed. */
/** @} */


/** @} */ //BLE_SMP_DEFINES

/**
 * @addtogroup BLE_SMP_ENUMS Enumerations
 * @{
 */
 
/** @brief Enumeration type for BLE SMP (Security Manager Protocol) callback events. */
typedef enum BLE_SMP_EventId_T
{
    BLE_SMP_EVT_PAIRING_COMPLETE,                                       /**< Event indicating the pairing process has completed. 
                                                                             See @ref BLE_SMP_EvtPairingComplete_T for the event details. */
    BLE_SMP_EVT_SECURITY_REQUEST,                                       /**< Event indicating a security request has been received from the remote peripheral device. 
                                                                             See @ref BLE_SMP_EvtSecurityReq_T for the event details. */
    BLE_SMP_EVT_NUMERIC_COMPARISON_CONFIRM_REQUEST,                     /**< Event requesting confirmation of a 6-digit numeric value during the pairing process (Numeric Comparison). 
                                                                             See @ref BLE_SMP_EvtDisplayCompareValueReq_T for the event details. */
    BLE_SMP_EVT_INPUT_PASSKEY_REQUEST,                                  /**< Event requesting input of a passkey during the pairing process (Passkey Entry). 
                                                                             See @ref BLE_SMP_EvtInputPasskeyReq_T for the event details. */
    BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST,                                /**< Event requesting the display of a passkey during the pairing process (Passkey Entry). 
                                                                             See @ref BLE_SMP_EvtDisplayPasskeyReq_T for the event details. */
    BLE_SMP_EVT_NOTIFY_KEYS,                                            /**< Event to notify the application of key information. 
                                                                             See @ref BLE_SMP_EvtNotifyKeys_T for the event details. */        
    BLE_SMP_EVT_PAIRING_REQUEST,                                        /**< Event indicating a pairing request has been received from the remote device. 
                                                                             See @ref BLE_SMP_EvtPairingReq_T for the event details. */
    BLE_SMP_EVT_INPUT_OOB_DATA_REQUEST,                                 /**< Event requesting input of OOB (Out of Band) data for legacy pairing during the pairing process. 
                                                                             See @ref BLE_SMP_EvtInputOobData_T for the event details. */
    BLE_SMP_EVT_INPUT_SC_OOB_DATA_REQUEST,                              /**< Event requesting input of OOB (Out of Band) data for Secure Connections pairing during the pairing process. 
                                                                             See @ref BLE_SMP_EvtInputScOobData_T for the event details. */
    BLE_SMP_EVT_KEYPRESS,                                               /**< Event indicating a keypress notification from the remote device. 
                                                                             See @ref BLE_SMP_EvtKeypress_T for the event details. */
    BLE_SMP_EVT_GEN_SC_OOB_DATA_DONE                                    /**< Event indicating the completion of Secure Connections OOB data generation. 
                                                                             See @ref BLE_SMP_EvtGenScOobDataDone_T for the event details. */
}BLE_SMP_EventId_T;
/** @} */ //BLE_SMP_ENUMS

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

/**
 * @addtogroup BLE_SMP_STRUCTS Structures
 * @{
 */
 
/** @brief Structure for configuring pairing parameters in BLE Security Manager Protocol (SMP). */
typedef struct BLE_SMP_Config_T
{
    uint8_t                 ioCapability;                               /**< I/O capability of the device. Defines how the device can or cannot display or input passkeys. 
                                                                             Refer to @ref BLE_SMP_IO_CAPABILITY_DEF for possible values. */
    uint8_t                 authReqFlag;                                /**< Authentication requirement flag. Specifies the authentication requirements for pairing. 
                                                                             Refer to @ref BLE_SMP_OPTION for possible values. */
    bool                    oobDataFlag;                                /**< Out-of-Band (OOB) data flag.
                                                                                - For LE legacy pairing, set to true if the device has OOB data available for authentication.
                                                                                - For LE Secure Connections pairing, set to true if the device has received OOB data from the remote device. 
                                                                                  OOB pairing is used if at least one device has OOB data. */
    bool                    scOnly;                                     /**< Secure Connections Only mode flag. Set to true to enforce pairing using LE Secure Connections only. */
    bool                    authPairingRequired;                        /**< Authenticated Pairing Requirement flag. Set to true to require an authenticated pairing method. 
                                                                            If set and the device is in the peripheral role with an unauthenticated pairing method, a pairing failure will be triggered. */
}BLE_SMP_Config_T;


/** @brief Structure for storing pairing information post-pairing process. */
typedef struct BLE_SMP_PairInfo_T
{
    unsigned int            auth:1;                                     /**< Authenticated Pairing flag. Set to 1 if the pairing is authenticated. */
    unsigned int            lesc:1;                                     /**< LE Secure Connections flag. Set to 1 if the key is generated using LE Secure Connections. */
    unsigned int            reserve:6;                                  /**< Reserved bits. */
}BLE_SMP_PairInfo_T;


/** @brief Structure for encryption information used in BLE connections. */
typedef struct BLE_SMP_EncInfo_T
{
    uint8_t                 ltk[16];                                    /**< Long Term Key (LTK). Used to encrypt the connection. */
    uint8_t                 ediv[2];                                    /**< Encrypted Diversifier (EDIV). A value used in the key derivation process. */
    uint8_t                 randNum[8];                                 /**< Random Number (Rand). Used alongside the EDIV to identify the LTK. */
    unsigned int            lesc:1;                                     /**< LE Secure Connections flag. Indicates if the key was generated using LE Secure Connections. */
    unsigned int            auth:1;                                     /**< Authenticated Key flag. Indicates if the LTK is an authenticated key. */
    unsigned int            ltkLen:6;                                   /**< Length of the LTK in bytes. */
}BLE_SMP_EncInfo_T;


/** @brief Structure for identity information. */
typedef struct BLE_SMP_IdInfo_T
{
    uint8_t                 irk[16];                                    /**< Identity Resolving Key (IRK). Used to resolve or generate a random device address. */
    BLE_GAP_Addr_T          addr;                                       /**< Identity Address. The device's public or static random address. See @ref BLE_GAP_Addr_T.*/
}BLE_SMP_IdInfo_T;


/** @brief Structure for storing the signature resolving key. */
typedef struct BLE_SMP_SignInfo_T
{
    uint8_t                 srk[16];                                    /**< Signature Resolving Key (SRK) used for signing data. */
}BLE_SMP_SignInfo_T;


/** @brief Structure for storing various security keys. */
typedef struct BLE_SMP_SecKeys_T
{
    BLE_SMP_EncInfo_T       encInfo;                                    /**< Encryption Information containing the Long Term Key (LTK) and associated data. See @ref BLE_SMP_EncInfo_T.*/
    BLE_SMP_IdInfo_T        idInfo;                                     /**< Identity Information containing the Identity Resolving Key (IRK) and public address. See @ref BLE_SMP_IdInfo_T.*/
    BLE_SMP_SignInfo_T      signInfo;                                   /**< Signing Information containing the Signature Resolving Key (SRK). See @ref BLE_SMP_SignInfo_T.*/
}BLE_SMP_SecKeys_T;


/** @brief Structure for storing the security keys of both local and remote devices. */
typedef struct BLE_SMP_KeyList_T
{
    BLE_SMP_SecKeys_T       local;                                      /**< Security keys of the local device. See @ref BLE_SMP_SecKeys_T.*/
    BLE_SMP_SecKeys_T       remote;                                     /**< Security keys of the remote device. See @ref BLE_SMP_SecKeys_T.*/
} BLE_SMP_KeyList_T;


/** @brief Structure for @ref BLE_SMP_EVT_PAIRING_COMPLETE event. */
typedef struct  BLE_SMP_EvtPairingComplete_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    uint8_t                 status;                                     /**< Pairing procedure status. Refer to @ref BLE_SMP_PAIRING_RESULT for possible values. */
    uint8_t                 failReason;                                 /**< Reason for pairing failure, if applicable. Refer to @ref BLE_SMP_PAIRING_FAIL_REASON for details. */
    bool                    bond;                                       /**< Indicates whether the devices have successfully bonded (true) or not (false). */
    uint8_t                 encryptKey[16];                             /**< Encryption key used for securing the connection. */
    BLE_SMP_SecKeys_T       local;                                      /**< Security keys of the local device post-pairing. See @ref BLE_SMP_SecKeys_T. */
    BLE_SMP_SecKeys_T       remote;                                     /**< Security keys of the remote device post-pairing. See @ref BLE_SMP_SecKeys_T. */
} BLE_SMP_EvtPairingComplete_T;


/** @brief Structure for @ref BLE_SMP_EVT_NUMERIC_COMPARISON_CONFIRM_REQUEST event.  */
typedef struct  BLE_SMP_EvtDisplayCompareValueReq_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    uint8_t                 value[6];                                   /**< 6-digit numeric comparison value in ASCII format that the user needs to confirm. */
} BLE_SMP_EvtDisplayCompareValueReq_T;


/** @brief Structure for @ref BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST event.  */
typedef struct  BLE_SMP_EvtDisplayPasskeyReq_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
} BLE_SMP_EvtDisplayPasskeyReq_T;


/** @brief Structure @ref BLE_SMP_EVT_INPUT_PASSKEY_REQUEST event. */
typedef struct  BLE_SMP_EvtInputPasskeyReq_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    bool                    keypress;                                   /**< Indicates whether keypress notifications are required.
                                                                             If true, use @ref BLE_SMP_Keypress to send notifications when keys are entered or erased. */
} BLE_SMP_EvtInputPasskeyReq_T;


/** @brief Structure for @ref BLE_SMP_EVT_INPUT_OOB_DATA_REQUEST event. */
typedef struct  BLE_SMP_EvtInputOobData_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
} BLE_SMP_EvtInputOobData_T;


/** @brief Structure for @ref BLE_SMP_EVT_INPUT_SC_OOB_DATA_REQUEST event. */
typedef struct  BLE_SMP_EvtInputScOobData_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
} BLE_SMP_EvtInputScOobData_T;


/** @brief Structure for @ref BLE_SMP_EVT_SECURITY_REQUEST event. */
typedef struct  BLE_SMP_EvtSecurityReq_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    uint8_t                 authReq;                                    /**< Authentication requirement flags. Refer to @ref BLE_SMP_OPTION for possible values. */
} BLE_SMP_EvtSecurityReq_T;


/** @brief Structure for @ref BLE_SMP_EVT_NOTIFY_KEYS event. */
typedef struct  BLE_SMP_EvtNotifyKeys_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    BLE_SMP_KeyList_T       keys;                                       /**< Set of keys exchanged during pairing. See @ref BLE_SMP_KeyList_T. */
} BLE_SMP_EvtNotifyKeys_T;


/** @brief Structure for @ref BLE_SMP_EVT_PAIRING_REQUEST) event. */
typedef struct  BLE_SMP_EvtPairingReq_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    uint8_t                 authReq;                                    /**< Authentication requirement flags. Refer to @ref BLE_SMP_OPTION for possible values. */
} BLE_SMP_EvtPairingReq_T;


/** @brief Structure for @ref BLE_SMP_EVT_KEYPRESS event. */
typedef struct  BLE_SMP_EvtKeypress_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    uint8_t                 notifyType;                                 /**< Type of keypress notification. Refer to @ref BLE_SMP_KEYPRESS_NOTI_TYPE for possible values. */
} BLE_SMP_EvtKeypress_T;


/** @brief Structure for @ref BLE_SMP_EVT_GEN_SC_OOB_DATA_DONE event. */
typedef struct  BLE_SMP_EvtGenScOobDataDone_T
{
    uint8_t                 confirm[16];                                /**< Confirm value used in the out-of-band (OOB) data generation for LE Secure Connections. */
    uint8_t                 randNum[16];                                /**< Random number used in the OOB data generation for LE Secure Connections. */
} BLE_SMP_EvtGenScOobDataDone_T;


/** @brief Union of BLE SMP callback event data types. */
typedef union
{
    BLE_SMP_EvtPairingComplete_T         evtPairingComplete;            /**< Data for @ref BLE_SMP_EVT_PAIRING_COMPLETE event. */
    BLE_SMP_EvtInputPasskeyReq_T         evtInputPasskeyReq;            /**< Data for @ref BLE_SMP_EVT_INPUT_PASSKEY_REQUEST event. */
    BLE_SMP_EvtDisplayCompareValueReq_T  evtDisplayCompareValueReq;     /**< Data for @ref BLE_SMP_EVT_NUMERIC_COMPARISON_CONFIRM_REQUEST event. */
    BLE_SMP_EvtDisplayPasskeyReq_T       evtDisplayPasskeyReq;          /**< Data for @ref BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST event. */
    BLE_SMP_EvtSecurityReq_T             evtSecurityReq;                /**< Data for @ref BLE_SMP_EVT_SECURITY_REQUEST event. */
    BLE_SMP_EvtNotifyKeys_T              evtNotifyKeys;                 /**< Data for @ref BLE_SMP_EVT_NOTIFY_KEYS event. */
    BLE_SMP_EvtPairingReq_T              evtPairingReq;                 /**< Data for @ref BLE_SMP_EVT_PAIRING_REQUEST event. */
    BLE_SMP_EvtInputOobData_T            evtInputOobData;               /**< Data for @ref BLE_SMP_EVT_INPUT_OOB_DATA_REQUEST event. */
    BLE_SMP_EvtInputScOobData_T          evtInputScOobData;             /**< Data for @ref BLE_SMP_EVT_INPUT_SC_OOB_DATA_REQUEST event. */
    BLE_SMP_EvtKeypress_T                evtKeypress;                   /**< Data for @ref BLE_SMP_EVT_KEYPRESS event. */
    BLE_SMP_EvtGenScOobDataDone_T        evtGenScOobDataDone;           /**< Data for @ref BLE_SMP_EVT_GEN_SC_OOB_DATA_DONE event. */
} BLE_SMP_EventField_T;

/** @brief BLE SMP callback event structure. */
typedef struct  BLE_SMP_Event_T
{
    BLE_SMP_EventId_T       eventId;                                    /**< Identifier for the BLE SMP event type. See @ref BLE_SMP_EventId_T. */
    BLE_SMP_EventField_T    eventField;                                 /**< Union containing the data payload for the event. See @ref BLE_SMP_EventField_T. */
} BLE_SMP_Event_T;

/** @} */ //BLE_SMP_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup BLE_SMP_FUNS Functions
 * @{
 */
 
/**
 * @brief Initializes the BLE Security Manager Protocol (SMP) main module.
 *
 * @note  The Generic Access Profile (GAP) must be initialized before this module.
 *
 * @retval MBA_RES_SUCCESS                  Initialization of the BLE SMP main module was successful.
 * @retval MBA_RES_OOM                      Failed due to internal memory allocation failure.
*/
uint16_t BLE_SMP_Init(void);


/**
 * @brief Configures SMP pairing parameters. 
 * @note  Man-In-The-Middle (MITM) protection is requested if ioCapability is set to anything other than NoInputNoOutput.
 *        Defaults are used if this function is not called:
 *        - ioCapability : @ref BLE_SMP_IO_NOINPUTNOOUTPUT
 *        - oob: false (no Out Of Band (OOB) authentication data)
 *        - authReqFlag : @ref BLE_SMP_OPTION_BONDING | @ref BLE_SMP_OPTION_SECURE_CONNECTION
 *        - scOnly: true (LE secure connection only)
 *
 * @param[in] p_config                      Pointer to the configuration structure. See @ref BLE_SMP_Config_T.
 *
 * @retval MBA_RES_SUCCESS                  Pairing parameters configured successfully.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 */
uint16_t BLE_SMP_Config(BLE_SMP_Config_T * p_config);


/**
 * @brief Responds to a passkey request event with the passkey.
 * @note  Call this in response to @ref BLE_SMP_EVT_INPUT_PASSKEY_REQUEST or @ref BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST events during pairing.
 *
 * @par Events generated
 *      Refer to the events generated by @ref BLE_SMP_InitiatePairing for the pairing procedure context.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_passkey                     Pointer to a 6-byte ASCII passkey buffer.
 *
 * @retval MBA_RES_SUCCESS                  Passkey provided successfully.
 * @retval MBA_RES_FAIL                     The specified connection handle is invalid.
 */
uint16_t BLE_SMP_PasskeyReply(uint16_t connHandle, uint8_t *p_passkey);


/**
 * @brief Indicates inability to provide a passkey in response to a request.
 * @note  Call this in response to @ref BLE_SMP_EVT_INPUT_PASSKEY_REQUEST or @ref BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST events during pairing.
 *
 * @par Events generated
 *      Refer to the events generated by @ref BLE_SMP_InitiatePairing for the pairing procedure context.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 *
 * @retval MBA_RES_SUCCESS                  Indication of no passkey was successful.
 * @retval MBA_RES_FAIL                     The specified connection handle is invalid.
 */
uint16_t BLE_SMP_PasskeyNegativeReply(uint16_t connHandle);


/**
 * @brief Confirms acceptance or rejection of numeric comparison during pairing.
 * @note  Valid during pairing when numeric comparison is used. It should be called 
 *          in response to the @ref BLE_SMP_EVT_NUMERIC_COMPARISON_CONFIRM_REQUEST event. 
 *          A positive confirmation (outcome == YES) allows pairing to continue, while a 
 *          negative confirmation (outcome == NO) results in pairing failure.
 *
 * @par Events generated
 *      Refer to the events generated by @ref BLE_SMP_InitiatePairing for the pairing procedure context.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] outcome                       User confirmation result, where YES and NO are defined in @ref BLE_SMP_CONFIRM.
 *
 * @retval MBA_RES_SUCCESS                  User confirmation sent successfully.
 * @retval MBA_RES_INVALID_PARA             Invalid outcome parameter (not YES or NO).
 * @retval MBA_RES_FAIL                     The specified connection handle is invalid.
 */
uint16_t BLE_SMP_NumericComparisonConfirmReply(uint16_t connHandle, uint8_t outcome);


/**
 * @brief Sends OOB data for pairing in response to an OOB data request.
 * @note  This function should be invoked from the SMP callback function upon receiving the 
 *          @ref BLE_SMP_EVT_INPUT_OOB_DATA_REQUEST event, which occurs when the OOB authentication 
 *          method is used during Legacy pairing.
 *
 * @par Events generated
 *      Refer to the events generated by @ref BLE_SMP_InitiatePairing for the pairing procedure context.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_oobData                     A pointer to the OOB data. If the local device cannot provide OOB data, set this to NULL.
 *                                          The OOB data should be a 16-byte key value.
 *
 * @retval MBA_RES_SUCCESS                  OOB data sent successfully.
 * @retval MBA_RES_FAIL                     The specified connection handle is invalid.
 * @retval MBA_RES_BAD_STATE                The function was called for Secure Connections pairing. Use @ref BLE_SMP_ScOobDataReply instead.
 */
uint16_t BLE_SMP_OobDataReply(uint16_t connHandle, uint8_t *p_oobData);


/**
 * @brief Sends OOB data for LE Secure Connections pairing in response to an OOB data request.
 * @note  This function should be invoked from the SMP callback function upon receiving the 
 *          @ref BLE_SMP_EVT_INPUT_SC_OOB_DATA_REQUEST event, which occurs when the OOB authentication 
 *          method is used during LE Secure Connections pairing.
 *
 * @par Events generated
 *      Refer to the events generated by @ref BLE_SMP_InitiatePairing for the pairing procedure context.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_confirm                     A pointer to the Confirm Value. If the local device cannot provide this information, set this to NULL.
 *                                          The Confirm Value should be a 16-byte value.
 * @param[in] p_rand                        A pointer to the Random Number. If the local device cannot provide this information, set this to NULL.
 *                                          The Random Number should be a 16-byte value.
 *
 * @retval MBA_RES_SUCCESS                  OOB data sent successfully.
 * @retval MBA_RES_FAIL                     The specified connection handle is invalid.
 * @retval MBA_RES_BAD_STATE                The function was called for Legacy pairing. Use @ref BLE_SMP_OobDataReply instead.
 */
uint16_t BLE_SMP_ScOobDataReply(uint16_t connHandle, uint8_t *p_confirm, uint8_t *p_rand);


/**
 * @brief Generates OOB data for the next LE Secure Connections pairing process.
 * @note  This function should be called before initiating the pairing process and the application 
 *          should wait for the @ref BLE_SMP_EVT_GEN_SC_OOB_DATA_DONE event before starting the pairing 
 *          process. It is recommended to call this function before a connection is established. The 
 *          generated OOB data can be sent by the application to the remote device for pairing.
 *
 * @par Events generated
 *      @ref BLE_SMP_EVT_GEN_SC_OOB_DATA_DONE is generated upon successful generation of the SC OOB data.
 *
 * @retval MBA_RES_SUCCESS                  Initiation of SC OOB data generation was successful.
 * @retval MBA_RES_OOM                      Failed due to internal memory allocation failure.
 * @retval MBA_RES_BUSY                     Failed because the SMP module is currently busy with another operation.
 */
uint16_t BLE_SMP_GenerateScOobData(void);


/**
 * @brief Initiates the BLE pairing procedure.
 * @note  This function starts the pairing process between two previously unbonded devices, which involves the following phases:\n
 *          - Phase 1: Exchange of pairing features.\n
 *          - Phase 2: Depending on the pairing method (LE legacy or LE Secure Connections), generate either a Short Term Key (STK) or a Long Term Key (LTK).\n
 *          - Phase 3: Distribution of keys specific to the transport layer.\n
 *      The method used in Phase 2 is determined by the IO Capabilities and the Authentication request flag. 
 *      In Phase 3, the keys distributed may include CSRK and IRK for LE Secure Connections, and additionally, 
 *      the encryption key (LTK, EDIV, Rand) for LE Legacy pairing.
 *
 * @par Events generated
 * @ref BLE_SMP_EVT_PAIRING_COMPLETE is generated when the pairing is completed or fails.
 * @ref BLE_SMP_EVT_NUMERIC_COMPARISON_CONFIRM_REQUEST is generated  for numeric comparison confirmation.
 * @ref BLE_SMP_EVT_INPUT_PASSKEY_REQUEST is generated  when a passkey input is required.
 * @ref BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST is generated when a passkey needs to be displayed.
 * @ref BLE_SMP_EVT_NOTIFY_KEYS is generated upon completion of key distribution.
 * @ref BLE_SMP_EVT_PAIRING_REQUEST is generated when a pairing request is received.
 * @ref BLE_SMP_EVT_INPUT_OOB_DATA_REQUEST is generated for input of OOB data in legacy pairing.
 * @ref BLE_SMP_EVT_INPUT_SC_OOB_DATA_REQUEST is generated for input of OOB data in LE Secure Connections pairing.
 * @ref BLE_SMP_EVT_KEYPRESS is generated when a keypress notification is received from the remote device.
 * 
 * @param[in] connHandle                    Connection handle associated with this connection.
 *
 * @retval MBA_RES_SUCCESS                  Pairing procedure initiated successfully.
 * @retval MBA_RES_FAIL                     The specified connection handle is invalid.
 */
uint16_t BLE_SMP_InitiatePairing(uint16_t connHandle);


/**
 * @brief Generates a six-byte random passkey in ASCII format.
 * @note  This function should be invoked within the SMP callback when the @ref BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST 
 *          event occurs. After calling this function, @ref BLE_SMP_PasskeyReply must be used to provide the 
 *          generated passkey to the BLE Stack. The passkey should also be displayed to the user.
 *
 * @param[out] p_passkey                    Pointer to a buffer where the generated passkey will be stored.
 *
 */
void BLE_SMP_GeneratePasskey(uint8_t *p_passkey);


/**
 * @brief Updates the paired device information to the SMP module.
 * @note  It is recommended to call this function once after a connection is established if the connection 
 *          is bonded. The SMP uses bonding information to verify permissions when processing requests.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] encryptKeySize                Size of the encryption key.
 * @param[in] p_pairInfo                    Pointer to the pairing information buffer (see @ref BLE_SMP_PairInfo_T).
 *
 * @retval MBA_RES_SUCCESS                  Information updated successfully.
 * @retval MBA_RES_INVALID_PARA             Invalid connection handle.
 */
uint16_t BLE_SMP_UpdateBondingInfo(uint16_t connHandle, uint8_t encryptKeySize, BLE_SMP_PairInfo_T *p_pairInfo);


/**
 * @brief Accepts a pairing request.
 * @note  This function should be called to proceed with the pairing process when the @ref BLE_SMP_EVT_PAIRING_REQUEST event is received.
 *
 * @par Events generated
 *      Refer to the events generated by @ref BLE_SMP_InitiatePairing for the pairing procedure context.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 *
 * @retval MBA_RES_SUCCESS                  Pairing response issued with acceptance.
 * @retval MBA_RES_INVALID_PARA             The parameter is invalid.
 */
uint16_t BLE_SMP_AcceptPairingRequest(uint16_t connHandle);


/**
 * @brief Rejects a pairing request.
 * @note  This function should be called to terminate the pairing process when the @ref BLE_SMP_EVT_PAIRING_REQUEST event is received.
 *
 * @par Events generated
 *       Refer to the events generated by @ref BLE_SMP_InitiatePairing for the pairing procedure context.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 *
 * @retval MBA_RES_SUCCESS                  Pairing response issued with rejection.
 * @retval MBA_RES_INVALID_PARA             The parameter is invalid.
 */
uint16_t BLE_SMP_RejectPairingRequest(uint16_t connHandle);


/**
 * @brief Rejects a security request from the peer device.
 * @note  This function should be invoked in response to the @ref BLE_SMP_EVT_SECURITY_REQUEST 
 *          event when the local device, operating in the central role, decides not to establish a secure connection.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 *
 * @retval MBA_RES_SUCCESS                  Security request rejected successfully.
 * @retval MBA_RES_INVALID_PARA             The parameter is invalid.
 */
uint16_t BLE_SMP_RejectSecRequest(uint16_t connHandle);


/**
 * @brief Sends a keypress notification to the remote device to indicate key entry or erasure.
 * @note  This function should be called in response to the @ref BLE_SMP_EVT_INPUT_PASSKEY_REQUEST 
 *          event and only if the keypress field of @ref BLE_SMP_EvtInputPasskeyReq_T is set to true.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] notifyType                    Type of keypress notification. Refer to @ref BLE_SMP_KEYPRESS_NOTI_TYPE for possible values.
 *
 * @retval MBA_RES_SUCCESS                  Keypress notification sent successfully.
 * @retval MBA_RES_INVALID_PARA             The parameter is invalid.
 */
uint16_t BLE_SMP_Keypress(uint16_t connHandle, uint8_t notifyType);


/**
 * @brief Accepts the use of the BLE SMP debug key during the pairing procedure.
 * @note  Invoking this function will prohibit the use of @ref BLE_SMP_EnableDebugMode.
 *
 * @retval MBA_RES_SUCCESS                  Debug key acceptance configured successfully.
 * @retval MBA_RES_FAIL                     Fail to accept the debug key because @ref BLE_SMP_EnableDebugMode has already been called.
*/
uint16_t BLE_SMP_AcceptDebugKey(void);


/**
 * @brief Enables BLE SMP debug mode for the pairing procedure.
 * @note  When debug mode is enabled, the debug public key will be used.
 *        Invoking this function will prohibit the use of @ref BLE_SMP_AcceptDebugKey.
 *
 * @retval MBA_RES_SUCCESS                  SMP debug mode enabled successfully.
 * @retval MBA_RES_FAIL                     Fail to enable debug mode because @ref BLE_SMP_AcceptDebugKey has already been called.
*/
uint16_t BLE_SMP_EnableDebugMode(void);

/** @} */ //BLE_SMP_FUNS

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif//BLE_SMP_H