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
  BLE GAP Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_gap.h

  Summary:
    This header file provides the Bluetooth Low Energy (BLE) Generic Access 
    Profile (GAP) interface functions for application developers.


  Description:
    This header file defines the interface for the BLE GAP functions and events 
    that application developers can use. The "BLE_GAP_Init" function must be 
    called within the "APP_Initialize" function to set up the GAP module within 
    the system. This initialization is crucial for the proper functioning of the 
    BLE application.

 *******************************************************************************/
#ifndef BLE_GAP_H
#define BLE_GAP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include "gap_defs.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/**
 * @defgroup BLE_GAP Generic Access Profile (GAP)
 * @brief Defines the interface for the BLE GAP functions provided by the BLE Library.
 *
 * The GAP module is responsible for device discovery, connection establishment, 
 * and security management. It is the foundational layer for building BLE applications.
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**
 * @addtogroup BLE_GAP_DEFINES Defines
 * @{
 */
 
/**
 * @defgroup BLE_GAP_MAX_CONN_HANDLE Maximum connection handle
 * @brief Defines the highest value that can be used as a connection handle in GAP (Generic Access Profile).
 * @{
 */
#define BLE_GAP_MAX_CONN_HANDLE                                 (0x0EFFU)       /**< Maximum valid BLE GAP connection handle. */
/** @} */ 

/**
 * @defgroup BLE_GAP_MAX_ADV_HANDLE Maximum advertising handle
 * @brief Defines the highest value that can be used as an advertising handle.
 * @{
 */
#define BLE_GAP_MAX_ADV_HANDLE                                  (0xEFU)        /**< Maximum valid BLE advertising handle. */
/** @} */ 
 
/**
 * @defgroup BLE_GAP_MAX_LINK_NBR Maximum number of connections
 * @brief Defines the maximum number of simultaneous GAP connections that can be maintained.
 * @{
 */
#define BLE_GAP_MAX_LINK_NBR                                    (0x08U)        /**< Maximum number of allowed simultaneous BLE GAP connections. */
/** @} */

 
/**
 * @defgroup BLE_GAP_ADV_INTERVAL Advertising interval
 * @brief Defines the range for advertising intervals in units of 0.625 ms. The default value is 0x0800 (1.28 seconds).
 * @{
 */
#define BLE_GAP_ADV_INTERVAL_MIN                                (0x0020U)      /**< Minimum advertising interval as 20 ms (32 * 0.625 ms). */
#define BLE_GAP_ADV_INTERVAL_MAX                                (0x4000U)      /**< Maximum advertising interval as 10.24 seconds (16384 * 0.625 ms). */
/** @} */


/**
 * @defgroup BLE_GAP_ADV_TYPE Advertising types
 * @brief Enumerates the different types of advertising that can be performed.
 * @{
 */
#define BLE_GAP_ADV_TYPE_ADV_IND                                (0x00U)        /**< Connectable undirected advertising (ADV_IND). 
                                                                                    This is the default and most common advertising type. */
#define BLE_GAP_ADV_TYPE_ADV_DIRECT_IND                         (0x01U)        /**< Connectable high duty cycle directed advertising (ADV_DIRECT_IND). 
                                                                                    Targets a specific device with high advertising frequency. */
#define BLE_GAP_ADV_TYPE_ADV_SCAN_IND                           (0x02U)        /**< Scannable undirected advertising (ADV_SCAN_IND). 
                                                                                    Allows devices to request scan response data. */
#define BLE_GAP_ADV_TYPE_ADV_NONCONN_IND                        (0x03U)        /**< Non-connectable undirected advertising (ADV_NONCONN_IND). 
                                                                                    Used for broadcasting data with no intention of connecting. */
#define BLE_GAP_ADV_TYPE_ADV_DIRECT_LOW_IND                     (0x04U)        /**< Connectable low duty cycle directed advertising (ADV_DIRECT_IND). 
                                                                                    Similar to high duty cycle but with lower frequency. */
/** @} */


/**
 * @defgroup BLE_GAP_ADDR_TYPE Address types
 * @brief Defines the different types of BLE device addresses.
 * @{
 */
#define BLE_GAP_ADDR_TYPE_PUBLIC                                (0x00U)        /**< Public device address, which is a globally unique and permanent address assigned to the device. */
#define BLE_GAP_ADDR_TYPE_RANDOM_STATIC                         (0x01U)        /**< Static random device address, which is a randomly generated address. */
#define BLE_GAP_ADDR_TYPE_RANDOM_RESOLVABLE                     (0x02U)        /**< Private resolvable random device address, which can be resolved by devices with the appropriate key. */
#define BLE_GAP_ADDR_TYPE_RANDOM_NON_RESOLVABLE                 (0x03U)        /**< Private non-resolvable random device address, which cannot be resolved. */
/** @} */


/**
 * @defgroup BLE_GAP_CP_RANGE Connection parameters range
 * @brief Defines the range of allowable connection parameters.
 * @{
 */
#define BLE_GAP_CP_MIN_CONN_INTVAL_MIN                          (0x0006U)      /**< Minimum permissible value of the minimum connection interval. (Unit: 1.25 ms) */
#define BLE_GAP_CP_MIN_CONN_INTVAL_MAX                          (0x0C80U)      /**< Maximum permissible value of the minimum connection interval. (Unit: 1.25 ms) */
#define BLE_GAP_CP_MAX_CONN_INTVAL_MIN                          (0x0006U)      /**< Minimum permissible value of the maximum connection interval. (Unit: 1.25 ms) */
#define BLE_GAP_CP_MAX_CONN_INTVAL_MAX                          (0x0C80U)      /**< Maximum permissible value of the maximum connection interval. (Unit: 1.25 ms) */
#define BLE_GAP_CP_LATENCY_MIN                                  (0x0000U)      /**< Minimum allowed peripheral latency, defined as the number of connection events the peripheral can skip. */
#define BLE_GAP_CP_LATENCY_MAX                                  (0x01F3U)      /**< Maximum allowed peripheral latency, defined as the number of connection events the peripheral can skip. */
#define BLE_GAP_CP_CONN_SUPV_TIMEOUT_MIN                        (0x000AU)      /**< Minimum permissible supervision timeout for the connection. (Unit: 10 ms) */
#define BLE_GAP_CP_CONN_SUPV_TIMEOUT_MAX                        (0x0C80U)      /**< Maximum permissible supervision timeout for the connection. (Unit: 10 ms) */
/** @} */


/**
 * @defgroup BLE_GAP_ROLE Connection roles
 * @brief Defines the roles a device can assume in a BLE connection.
 * @{
 */
#define BLE_GAP_ROLE_CENTRAL                                    (0x00U)        /**< Device acts as the Central role in a connection. */
#define BLE_GAP_ROLE_PERIPHERAL                                 (0x01U)        /**< Device acts as the Peripheral role in a connection. */
/** @} */


/**
 * @defgroup BLE_GAP_ADV_CHANNEL Advertising channels
 * @brief Defines the advertising channel indices that can be used for BLE advertising.
 * @{
 */
#define BLE_GAP_ADV_CHANNEL_37                                  (0x01U)        /**< Use channel 37 for advertising. */
#define BLE_GAP_ADV_CHANNEL_38                                  (0x02U)        /**< Use channel 38 for advertising. */
#define BLE_GAP_ADV_CHANNEL_39                                  (0x04U)        /**< Use channel 39 for advertising. */
#define BLE_GAP_ADV_CHANNEL_ALL                                 (0x07U)        /**< Use all advertising channels (37, 38, and 39). */
/** @} */

/**
 * @defgroup BLE_GAP_ADV_FILTER_POLICY Advertising filter policies
 * @brief Defines the policies for filtering advertising packets.
 * @{
 */
#define BLE_GAP_ADV_FILTER_DEFAULT                              (0x00U)        /**< No filter applied. Process scan and connection requests from all devices. */
#define BLE_GAP_ADV_FILTER_SCAN                                 (0x01U)        /**< Filter applied to scan requests. Process connection requests from all devices 
                                                                                    and scan requests only from devices in the filter accept list. */
#define BLE_GAP_ADV_FILTER_CONNECT                              (0x02U)        /**< Filter applied to connection requests. Process scan requests from all devices 
                                                                                    and connection requests only from devices in the filter accept list. */
#define BLE_GAP_ADV_FILTER_SCAN_CONNECT                         (0x03U)        /**< Filter applied to both scan and connection requests. Process requests only 
                                                                                    from devices in the filter accept list. */
/** @} */

/**
 * @defgroup BLE_GAP_ADV_OPTION Advertising options
 * @brief Defines the advertising option.
 * @{
 */
#define BLE_GAP_ADV_OPTION_STORE_PARAMS                         (0x00U)        /**< Store advertising parameters in BACKUP RAM. When enabled, only one advertising 
                                                                                    event will be executed.\n This option is effective only when the "enable" parameter 
                                                                                    in the @ref BLE_GAP_SetAdvParams API is set to true. */
#define BLE_GAP_ADV_OPTION_LOAD_PARAMS                          (0x01U)        /**< Load advertising parameters from BACKUP RAM. When enabled, only one advertising event 
                                                                                    will be executed.\n This option is effective only when the "enable" parameter in the 
                                                                                    @ref BLE_GAP_SetAdvParams API is set to true. */
/** @} */


/**
 * @defgroup BLE_GAP_SCAN_FP Scan filter policies
 * @brief Defines the scanning filter policies.
 * @{
 */
#define BLE_GAP_SCAN_FP_ACCEPT_ALL                              (0x00U)        /**< Accept all advertising packets except directed advertising not addressed to this device.*/
#define BLE_GAP_SCAN_FP_ACCEPT_LIST                             (0x01U)        /**< Accept advertising packets only from devices on the filter accept list. */
#define BLE_GAP_SCAN_FP_NOT_RESOLVED_DIRECTED                   (0x02U)        /**< Accept all advertising packets, including directed advertising with a TargetA as a 
                                                                                    resolvable private address that cannot be resolved. Only applicable for 
                                                                                    @ref BLE_GAP_SetExtScanningParams. */
#define BLE_GAP_SCAN_FP_ACCEPT_LIST_NOT_RESOLVED_DIRECTED       (0x03U)        /**< Accept advertising packets from devices on the filter accept list, including directed 
                                                                                    advertising with a TargetA as a resolvable private address that cannot be resolved. 
                                                                                    Only applicable for @ref BLE_GAP_SetExtScanningParams. */
/** @} */

/**
 * @defgroup BLE_GAP_SCAN_CHANNEL Scan channels
 * @brief Defines the channel map bit field for scan.
 * @{
 */
#define BLE_GAP_SCAN_CHANNEL_37                                 (0x01U)        /**< Use Channel 37 for scanning. */
#define BLE_GAP_SCAN_CHANNEL_38                                 (0x02U)        /**< Use Channel 38 for scanning. */
#define BLE_GAP_SCAN_CHANNEL_39                                 (0x04U)        /**< Use Channel 39 for scanning. */
/** @} */


/**
 * @defgroup BLE_GAP_INIT_FP Initiator filter policies
 * @brief Defines the initiator filter policies.
 * @{
 */
#define BLE_GAP_INIT_FP_FAL_NOT_USED                            (0x00U)        /**< Filter Accept List is not used for determining the target advertiser to connect to. */
#define BLE_GAP_INIT_FP_FAL_USED                                (0x01U)        /**< Filter Accept List is used for determining the target advertiser to connect to, 
                                                                                    ignoring the peer address.*/
/** @} */


/**
 * @defgroup BLE_GAP_SCAN_INTERVAL Scan interval
 * @brief Defines the range of LE scan intervals. The interval is specified in units of 0.625 ms.
 * @{
 */
#define BLE_GAP_SCAN_INTERVAL_MIN                               (0x0004U)      /**< Minimum LE scan interval: 2.5 ms (0x0004 * 0.625 ms). */
#define BLE_GAP_SCAN_INTERVAL_MAX                               (0x4000U)      /**< Maximum LE scan interval: 10.24 seconds (0x4000 * 0.625 ms).*/
/** @} */


/**
 * @defgroup BLE_GAP_SCAN_WINDOW Scan window
 * @brief Defines the range of LE scan windows. The window is specified in units of 0.625 ms.
 * @{
 */
#define BLE_GAP_SCAN_WINDOW_MIN                                 (0x0004U)      /**< Minimum LE scan window: 2.5 ms (0x0004 * 0.625 ms). */
#define BLE_GAP_SCAN_WINDOW_MAX                                 (0x4000U)      /**< Maximum LE scan window: 10.24 seconds (0x4000 * 0.625 ms). */
/** @} */


/**
 * @defgroup BLE_GAP_SCAN_TYPE Scan types
 * @brief Defines the types of scanning methods that can be used.
 * @{
 */
#define BLE_GAP_SCAN_TYPE_PASSIVE_SCAN                          (0x00U)        /**< Passive scanning: No SCAN_REQ packets shall be sent. This is the default scan type. */
#define BLE_GAP_SCAN_TYPE_ACTIVE_SCAN                           (0x01U)        /**< Active scanning: SCAN_REQ packets may be sent to request additional advertising data. */
/** @} */


/**
 * @defgroup BLE_GAP_SCAN_FD Scan filter duplicate options
 * @brief Defines the options for filtering duplicate advertising reports during scanning.
 * @{
 */
#define BLE_GAP_SCAN_FD_DISABLE                                 (0x00U)        /**< Duplicate filtering disabled: All advertising packets are reported. */
#define BLE_GAP_SCAN_FD_ENABLE                                  (0x01U)        /**< Duplicate filtering enabled: Only one report is provided for each advertising device. */
#define BLE_GAP_SCAN_FD_ENABLE_RESET                            (0x02U)        /**< Duplicate filtering enabled with reset: Similar to BLE_GAP_SCAN_FD_ENABLE, 
                                                                                    but the list of seen devices is cleared when scanning is restarted. 
                                                                                    Valid only for extended scanning enabled by @ref BLE_GAP_ExtScanningEnable_T. */
/** @} */

/**
 * @defgroup BLE_GAP_SCAN_MODES Scan modes
 * @brief Defines the scanning modes that determine the type of advertising packets that will be reported.
 * @{
 */
#define BLE_GAP_SCAN_MODE_GENERAL_DISCOVERY                     (0x00U)        /**< General discovery: Reports both general and limited advertising mode devices. */
#define BLE_GAP_SCAN_MODE_LIMITED_DISCOVERY                     (0x01U)        /**< Limited discovery: Reports only devices in limited advertising mode. */
#define BLE_GAP_SCAN_MODE_OBSERVER                              (0x02U)        /**< Observer mode: Reports all advertising packets with no filter applied. */
/** @} */


/**
 * @defgroup BLE_GAP_ADV_RPT_EVT_TYPE Event types of advertising reports
 * @brief Defines the different types of BLE advertising report events.
 * @{
 */
#define BLE_GAP_ADV_RPT_EVT_TYPE_ADV_IND                        (0x00U)        /**< Event for connectable undirected advertising (ADV_IND). */
#define BLE_GAP_ADV_RPT_EVT_TYPE_ADV_DIRECT_IND                 (0x01U)        /**< Event for connectable directed advertising (ADV_DIRECT_IND). */
#define BLE_GAP_ADV_RPT_EVT_TYPE_ADV_SCAN_IND                   (0x02U)        /**< Event for scannable undirected advertising (ADV_SCAN_IND). */
#define BLE_GAP_ADV_RPT_EVT_TYPE_ADV_NONCONN_IND                (0x03U)        /**< Event for scannable undirected advertising (ADV_SCAN_IND). */
#define BLE_GAP_ADV_RPT_EVT_TYPE_SCAN_RSP                       (0x04U)        /**< Event for non-connectable undirected advertising (ADV_NONCONN_IND). */
#define BLE_GAP_ADV_RPT_EVT_TYPE_AUX_ADV_IND                    (0x07U)        /**< Event for auxiliary connectable undirected advertising (AUX_ADV_IND). */
/** @} */

/**
 * @defgroup BLE_GAP_EXT_ADV_EVT_PROP Extended advertising event properties
 * @brief Defines the properties of extended advertising events.
 * @{
 */
#define BLE_GAP_EXT_ADV_EVT_PROP_CONNECTABLE_ADV                (1U << 0U)    /**< Property indicating connectable advertising. */
#define BLE_GAP_EXT_ADV_EVT_PROP_SCANNABLE_ADV                  (1U << 1U)    /**< Property indicating scannable advertising. */
#define BLE_GAP_EXT_ADV_EVT_PROP_DIRECTED_ADV                   (1U << 2U)    /**< Property indicating directed advertising. */
#define BLE_GAP_EXT_ADV_EVT_PROP_HIGH_DUTY_DIRECTED_CONN_ADV    (1U << 3U)    /**< Property indicating high duty cycle directed connectable advertising (<= 3.75 ms interval). */
#define BLE_GAP_EXT_ADV_EVT_PROP_LEGACY_ADV                     (1U << 4U)    /**< Property indicating the use of legacy advertising PDUs. */
#define BLE_GAP_EXT_ADV_EVT_PROP_OMIT_ADDRESS                   (1U << 5U)    /**< Property indicating the omission of the advertiser's address from all PDUs (anonymous advertising). */
#define BLE_GAP_EXT_ADV_EVT_PROP_TX_POWER                       (1U << 6U)    /**< Property indicating the inclusion of TxPower in the extended header of the advertising PDU. */
#define BLE_GAP_EXT_ADV_EVT_PROP_ALL                            (BLE_GAP_EXT_ADV_EVT_PROP_CONNECTABLE_ADV \
                                                                |BLE_GAP_EXT_ADV_EVT_PROP_SCANNABLE_ADV \
                                                                |BLE_GAP_EXT_ADV_EVT_PROP_DIRECTED_ADV  \
                                                                |BLE_GAP_EXT_ADV_EVT_PROP_HIGH_DUTY_DIRECTED_CONN_ADV \
                                                                |BLE_GAP_EXT_ADV_EVT_PROP_LEGACY_ADV    \
                                                                |BLE_GAP_EXT_ADV_EVT_PROP_OMIT_ADDRESS  \
                                                                |BLE_GAP_EXT_ADV_EVT_PROP_TX_POWER) /**< Combination of all properties. */
/** @} */

/**
 * @defgroup BLE_GAP_EXT_ADV_DATA_OPERAION Extended advertising data operations
 * @brief Defines the operations related to extended advertising data.
 * @{
 */
#define BLE_GAP_EXT_ADV_DATA_OP_COMPLETE                        (0x03U)        /**< Operation indicating complete extended advertising data. */
#define BLE_GAP_EXT_ADV_DATA_OP_UNCHANGED                       (0x04U)        /**< Operation indicating unchanged data (only update the Advertising DID). */
/** @} */

/**
 * @defgroup BLE_GAP_EXT_ADV_DATA_FRAG_PREF Fragment preference for extended advertising data
 * @brief Defines the preference on fragmenting extended advertising data.
 * @{
 */
#define BLE_GAP_EXT_ADV_DATA_FRAG_ALL                           (0x00U)        /**< BLE Stack may fragment all advertising data. */
#define BLE_GAP_EXT_ADV_DATA_FRAG_MIN                           (0x01U)        /**< BLE Stack should not fragment or should minimize fragmentation of advertising data. */
/** @} */

/**
 * @defgroup BLE_GAP_EXT_PRIMARY_ADV_INTERVAL Extended primary advertising interval range
 * @brief Defines the range for the LE extended primary advertising interval in units of 0.625 ms.
 * @{
 */
#define BLE_GAP_EXT_PRIM_ADV_INTVL_MIN                          (0x0020U)      /**< Minimum LE extended primary advertising interval: 20 ms. */
#define BLE_GAP_EXT_PRIM_ADV_INTVL_MAX                          (0x1F4000UL)   /**< Maximum LE extended primary advertising interval: 1280 sec. */
/** @} */

/**
 * @defgroup BLE_GAP_PERIODIC_ADV_PROP Periodic advertising properties
 * @brief Defines the properties of periodic advertising.
 * @{
 */
#define BLE_GAP_PERIODIC_ADV_PROP_TX_POWER                      (1U << 6U)    /**< Property indicating the inclusion of TxPower in the advertising PDU. */
/** @} */

/**
 * @defgroup BLE_GAP_PERIODIC_ADV_DATA_OPERAION Operation of periodic advertising data
 * @brief Defines operations related to periodic advertising data.
 * @{
 */
#define BLE_GAP_PERIODIC_ADV_DATA_OP_COMPLETE                   (0x03U)        /**< Indicates that the periodic advertising data is complete and ready for use or broadcast. */
#define BLE_GAP_PERIODIC_ADV_DATA_OP_UNCHANGED                  (0x04U)        /**< Operation indicating unchanged data (only update the Advertising DID). */
/** @} */


/**
 * @defgroup BLE_GAP_PERIODIC_ACA The accuracy of the periodic advertiser's clock
 * @brief Defines the clock accuracy for periodic advertising.
 * @{
 */
#define BLE_GAP_PERIODIC_ACA_500_PPM                            (0x00U)        /**< Clock accuracy of 500 parts per million (ppm). */
#define BLE_GAP_PERIODIC_ACA_250_PPM                            (0x01U)        /**< Clock accuracy of 250 ppm. */
#define BLE_GAP_PERIODIC_ACA_150_PPM                            (0x02U)        /**< Clock accuracy of 150 ppm. */
#define BLE_GAP_PERIODIC_ACA_100_PPM                            (0x03U)        /**< Clock accuracy of 100 ppm. */
#define BLE_GAP_PERIODIC_ACA_75_PPM                             (0x04U)        /**< Clock accuracy of 75 ppm. */
#define BLE_GAP_PERIODIC_ACA_50_PPM                             (0x05U)        /**< Clock accuracy of 50 ppm. */
#define BLE_GAP_PERIODIC_ACA_30_PPM                             (0x06U)        /**< Clock accuracy of 30 ppm. */
#define BLE_GAP_PERIODIC_ACA_20_PPM                             (0x07U)        /**< Clock accuracy of 20 ppm. */
/** @} */

/**
 * @defgroup BLE_GAP_CTE_TYPE Type of constant tone extension
 * @brief Defines the type of Constant Tone Extension (CTE) used.
 * @{
 */
#define BLE_GAP_CTE_TYPE_AOA                                    (0x00U)        /**< Angle of Arrival (AoA) Constant Tone Extension. */
#define BLE_GAP_CTE_TYPE_AOD_WITH_1US                           (0x01U)        /**< Angle of Departure (AoD) Constant Tone Extension with 1 microsecond slots. */
#define BLE_GAP_CTE_TYPE_AOD_WITH_2US                           (0x02U)        /**< Angle of Departure (AoD) Constant Tone Extension with 2 microsecond slots. */
#define BLE_GAP_CTE_TYPE_NO                                     (0x03U)        /**< No Constant Tone Extension used. */
/** @} */

/**
 * @defgroup BLE_GAP_DATA_STATUS Received data status
 * @brief Defines the status of received data in a BLE operation.
 * @{
 */
#define BLE_GAP_DATA_STATUS_COMPLETE                            (0x00U)        /**< All expected data has been received completely. */
#define BLE_GAP_DATA_STATUS_MORE_DATA                           (0x01U)        /**< Data received is incomplete; more data is expected to follow. */
#define BLE_GAP_DATA_STATUS_DATA_TRUNCATED                      (0x02U)        /**< Data received is incomplete and truncated; no further data is expected. */

/** @} */

/**
 * @defgroup BLE_GAP_PERIODIC_ADV_FRAGMENT_DATA_LEN Maximum periodic advertising fragment data length
 * @brief Defines the maximum data length for a single fragment of periodic advertising data.
 * @{
 */
#define BLE_GAP_PERIODIC_ADV_FRAGMENT_MAX_LENGTH                (0xF7U)        /**< Maximum length in bytes for a single fragment of periodic advertising data. */
/** @} */


/**
 * @defgroup BLE_GAP_EXT_SCAN_DATA_LEN Extended scan data length
 * @brief Defines the range of extended scan data length.
 * @{
 */
#define BLE_GAP_EXT_SCAN_DATA_LEN_MIN                           (0x004AU)      /**< Minimum extended scan data length. */
#define BLE_GAP_EXT_SCAN_DATA_LEN_MAX                           (0x0672U)      /**< Maximum extended scan data length. */
/** @} */

/**
 * @defgroup BLE_GAP_EXT_SCAN_2ND_ADV_NUM Maximum secondary advertisements for extended scan
 * @brief Defines the maximum number of secondary advertisements for extended scanning.
 * @{
 */
#define BLE_GAP_EXT_SCAN_2ND_ADV_NUM                            (0x10U)       /**< Maximum number of secondary advertising packets for extended scanning. */
/** @} */


/**
 * @defgroup BLE_GAP_EXT_SCAN_INTERVAL Extended scan interval
 * @brief Defines the range of LE extended scan intervals. (Unit: 0.625 ms)
 * @{
 */
#define BLE_GAP_EXT_SCAN_INTERVAL_MIN                           (0x0004U)      /**< Minimum LE extended scan interval: 2.5 ms. */
#define BLE_GAP_EXT_SCAN_INTERVAL_MAX                           (0xFFFFU)      /**< Maximum LE extended scan interval: 40.959375 seconds. */
/** @} */


/**
 * @defgroup BLE_GAP_EXT_SCAN_WINDOW Extended scan window
 * @brief Defines the range of LE extended scan windows. (Unit: 0.625 ms)
 * @{
 */
#define BLE_GAP_EXT_SCAN_WINDOW_MIN                             (0x0004U)      /**< Minimum LE extended scan window: 2.5 ms. */
#define BLE_GAP_EXT_SCAN_WINDOW_MAX                             (0xFFFFU)      /**< Maximum LE extended scan window: 40.959375 seconds. */
/** @} */

/**
 * @defgroup BLE_GAP_PRIODIC_ADV_INTERVAL Periodic advertising interval
 * @brief Defines the range of LE periodic advertising intervals. (Unit: 1.25 ms)
 * @{
 */
#define BLE_GAP_PERIODIC_ADV_INTVL_MIN                          (0x0006U)      /**< Minimum LE periodic advertising interval: 7.5 ms. */
#define BLE_GAP_PERIODIC_ADV_INTVL_MAX                          (0xFFFFU)      /**< Maximum LE periodic advertising interval: 81.91875 seconds. */
/** @} */


/**
 * @defgroup BLE_GAP_EXT_ADV_REPORT_EVT_TYPE Event type for extended advertising reports
 * @brief Defines the event types for extended advertising reports.
 * @{
 */
#define BLE_GAP_EXT_ADV_RPT_TYPE_CONNECTABLE                    (1U << 0U)    /**< Indicates connectable advertising. */
#define BLE_GAP_EXT_ADV_RPT_TYPE_SCANNABLE                      (1U << 1U)    /**< Indicates scannable advertising. */
#define BLE_GAP_EXT_ADV_RPT_TYPE_DIRECTED                       (1U << 2U)    /**< Indicates directed advertising. */
#define BLE_GAP_EXT_ADV_RPT_TYPE_SCAN_RSP                       (1U << 3U)    /**< Indicates a scan response. */
#define BLE_GAP_EXT_ADV_RPT_TYPE_LEGACY                         (1U << 4U)    /**< Indicates that legacy advertising PDUs are used.  */
/** @} */


/**
 * @defgroup BLE_GAP_EXT_ADV_REPORT_DATA_STATUS Data status for extended advertising reports
 * @brief Defines the data status for extended advertising reports.
 * @{
 */
#define BLE_GAP_EXT_ADV_RPT_DATA_COMPLETE                       (0x00U)        /**< Data is complete. */
#define BLE_GAP_EXT_ADV_RPT_DATA_MORE                           (0x01U)        /**< Data is incomplete; more data to come.  */
#define BLE_GAP_EXT_ADV_RPT_DATA_TRUNCATED                      (0x02U)        /**< Data is incomplete and truncated; no more data to come. */
/** @} */

/**
 * @defgroup BLE_GAP_EXT_ADV_REPORT_PHY PHY settings for extended advertising reports
 * @brief Defines the PHY settings for extended advertising reports.
 * @{
 */
#define BLE_GAP_EXT_ADV_RPT_PHY_NO                              (0x00U)        /**< No packets on the secondary advertising channel. */
#define BLE_GAP_EXT_ADV_RPT_PHY_1M                              (0x01U)        /**< Advertiser's PHY is LE 1M. */
#define BLE_GAP_EXT_ADV_RPT_PHY_2M                              (0x02U)        /**< Advertiser's PHY is LE 2M. */
#define BLE_GAP_EXT_ADV_RPT_PHY_CODED                           (0x03U)        /**< Advertiser's PHY is LE Coded. */
/** @} */


/**
 * @defgroup BLE_GAP_PRIVACY_MODE Privacy modes
 * @brief Defines the privacy modes.
 * @{
 */
#define BLE_GAP_PRIVACY_MODE_NETWORK                            (0x00U)        /**< Network Privacy Mode is used. */
#define BLE_GAP_PRIVACY_MODE_DEVICE                             (0x01U)        /**< Device Privacy Mode is used. */
#define BLE_GAP_PRIVACY_MODE_OFF                                (0xFFU)        /**< Privacy Mode is disabled (off). */
/** @} */


/**
 * @defgroup BLE_GAP_RPA_TIMEOUT RPA timeouts
 * @brief Defines the Resolvable Private Address (RPA) timeouts.
 * @{
 */
#define BLE_GAP_RPA_TIMEOUT_MIN                                 (0x0001U)        /**< Minimum value for RPA timeout. */
#define BLE_GAP_RPA_TIMEOUT_MAX                                 (0x0708U)        /**< Maximum value for RPA timeout. */
/** @} */


/**
 * @defgroup BLE_GAP_ADV_DATA_LEN Maximum advertising data length
 * @brief Defines the maximum length of advertising data in bytes.
 * @{
 */
#define BLE_GAP_ADV_MAX_LENGTH                                  (0x1FU)        /**< Maximum length of advertising data in bytes (31 bytes). */
/** @} */

/**
 * @defgroup BLE_GAP_EXT_ADV_FRAGMENT_DATA_LEN Maximum extended advertising fragment data length
 * @brief Defines the maximum length of extended advertising fragment data in bytes.
 * @{
 */
#define BLE_GAP_EXT_ADV_FRAGMENT_MAX_LENGTH                     (0xE5U)        /**< Maximum length of extended advertising fragment data in bytes (229 bytes). */
/** @} */


/**
 * @defgroup BLE_GAP_ADV_SID_RANGE Advertising Set Identifier (SID) range
 * @brief Defines the range of values for the Advertising Set Identifier (SID).
 * @{
 */
#define BLE_GAP_ADV_SID_MIN                                     (0x00U)        /**< The minimum value for advertising SID (0). */
#define BLE_GAP_ADV_SID_MAX                                     (0x0FU)        /**< The maximum value for advertising SID (15). */
/** @} */


/**
 * @defgroup BLE_GAP_CODED_PHY_OPTIONS LE Coded PHY options
 * @brief Defines the Host preferred options when transmitting on the LE Coded PHY.
 * @{
 */
#define BLE_GAP_CODED_PHY_HOST_NO_PREFERRED                     (0x00U)         /**< The Host has no preferred or required coding when transmitting on the LE Coded PHY. */
#define BLE_GAP_CODED_PHY_HOST_PREFER_S2                        (0x01U)         /**< The Host prefers that S=2 coding be used when transmitting on the LE Coded PHY. */
#define BLE_GAP_CODED_PHY_HOST_PREFER_S8                        (0x02U)         /**< The Host prefers that S=8 coding be used when transmitting on the LE Coded PHY. */
#define BLE_GAP_CODED_PHY_HOST_REQUIRE_S2                       (0x03U)         /**< The Host requires that S=2 coding be used when transmitting on the LE Coded PHY. */
#define BLE_GAP_CODED_PHY_HOST_REQUIRE_S8                       (0x04U)         /**< The Host requires that S=8 coding be used when transmitting on the LE Coded PHY. */
/** @} */

/**
 * @defgroup BLE_GAP_SYNC_CREATE_OPTION Options for creating synchronization
 * @brief Defines the options for creating synchronization with a periodic advertising train.
 * @{
 */
#define BLE_GAP_SYNC_CREATE_OPTION_USE_ADV_LIST                 (1U << 0U)    /**< Option to use the Periodic Advertiser List for synchronization. */
#define BLE_GAP_SYNC_CREATE_OPTION_REPORT_DISABLED              (1U << 1U)    /**< Option to disable reporting initially when synchronization is created. */
#define BLE_GAP_SYNC_CREATE_OPTION_FILTER_ENABLED               (1U << 2U)    /**< Option to enable duplicate filtering initially when synchronization is created. */
/** @} */

/**
 * @defgroup BLE_GAP_SYNC_TIMEOUT Synchronization timeout
 * @brief Defines the synchronization timeout range for the periodic advertising train.
 * @{
 */
#define BLE_GAP_SYNC_TIMEOUT_MIN                                (0x000AU)      /**< The minimum synchronization timeout value (10 units, with each unit being 10 ms). */
#define BLE_GAP_SYNC_TIMEOUT_MAX                                (0x4000U)      /**< The maximum synchronization timeout value (16384 units, with each unit being 10 ms). */
/** @} */

/**
 * @defgroup BLE_GAP_SYNC_SKIP Maximum number of skipped periodic advertising events
 * @brief Defines the maximum number of periodic advertising events that can be skipped.
 * @{
 */
#define BLE_GAP_SYNC_SKIP_MAX                                   (0x1F3U)       /**< Maximum number of periodic advertising events that can be skipped. */
/** @} */


/**
 * @defgroup BLE_GAP_MAX_FILTER_ACCEPT_LIST_NUM Maximum filter accept list size
 * @brief Defines the maximum size of the filter accept list.
 * @{
 */
#define BLE_GAP_MAX_FILTER_ACCEPT_LIST_NUM                      (0x08U)        /**< Maximum size of the filter accept list. */
/** @} */

/**
 * @defgroup BLE_GAP_MAX_RESOLV_NUM Maximum resolving list size
 * @brief Defines the maximum size of the resolving list.
 * @{
 */
#define BLE_GAP_MAX_RESOLV_NUM                                  (0x08U)        /**< Maximum size of the resolving list. */
/** @} */


/**
 * @defgroup BLE_GAP_PHY_OPTION PHY options for transmission and reception
 * @brief Defines the PHY options for transmission (TX) and reception (RX).
 * @{
 */
#define BLE_GAP_PHY_OPTION_NO_PREF                              (0U)          /**< No PHY preference. */
#define BLE_GAP_PHY_OPTION_1M                                   (1U <<0U)     /**< Preference for using the LE 1M PHY.*/
#define BLE_GAP_PHY_OPTION_2M                                   (1U <<1U)     /**< Preference for using the LE 2M PHY. */
#define BLE_GAP_PHY_OPTION_CODED                                (1U <<2U)     /**< Preference for using the LE Coded PHY. */
/** @} */


/**
 * @defgroup BLE_GAP_PHY_PREF Preferred PHY coding preference
 * @brief Defines the preferred PHY coding for transmission on the LE Coded PHY.
 * @{
 */
#define BLE_GAP_PHY_PREF_NO                                     (0U)           /**< No preferred PHY coding. */
#define BLE_GAP_PHY_PREF_S2                                     (1U)           /**< Preference for S=2 coding on the LE Coded PHY. */
#define BLE_GAP_PHY_PREF_S8                                     (2U)           /**< Preference for S=8 coding on the LE Coded PHY. */
/** @} */


/**
 * @defgroup BLE_GAP_PHY_TYPE PHY types
 * @brief Defines the PHY type for BLE connections.
 * @{
 */
#define BLE_GAP_PHY_TYPE_LE_1M                                  (0x01U)        /**< Connection uses LE 1M PHY (1 Mbps). */
#define BLE_GAP_PHY_TYPE_LE_2M                                  (0x02U)        /**< Connection uses LE 2M PHY (2 Mbps). */
#define BLE_GAP_PHY_TYPE_LE_CODED                               (0x03U)        /**< Connection uses LE Coded PHY for long range and reliability. */
/** @} */


/**
 * @defgroup BLE_GAP_MAX_DEV_NUM Maximum advertiser list size
 * @brief Defines the maximum number of devices that can be included in the advertiser list.
 * @{
 */
#define BLE_GAP_MAX_DEV_NUM                                     (0x08U)        /**< Maximum number of devices in the advertiser list. */
/** @} */


/**
 * @defgroup BLE_GAP_TRANSMITTER_PHY_TYPE Transmitter PHY type
 * @brief Defines the PHY types for transmitter test packets.
 * @{
 */
#define BLE_GAP_TX_1M_PHY                                       (0x01U)        /**< Transmitter uses LE 1M PHY for test packets. */
#define BLE_GAP_TX_2M_PHY                                       (0x02U)        /**< Transmitter uses LE 2M PHY for test packets. */
#define BLE_GAP_TX_CODED_PHY_S_8                                (0x03U)        /**< Transmitter uses LE Coded PHY with S=8 data coding for test packets. */
#define BLE_GAP_TX_CODED_PHY_S_2                                (0x04U)        /**< Transmitter uses LE Coded PHY with S=2 data coding for test packets. */
/** @} */

/**
 * @defgroup BLE_SCAN_FILTER_ARRAY_SIZE Scan filter length
 * @brief Defines the maximum length of various scan filter fields.
 * @{
 */
#define BLE_GAP_SCAN_SERVICE_DATA_MAX_LEN                       (16U)          /**< Maximum length of the service data array in bytes. */
#define BLE_GAP_SCAN_MSD_MAX_LEN                                (16U)          /**< Maximum length of the manufacturer-specific data array in bytes. */
#define BLE_GAP_SCAN_NAME_MAX_LEN                               (16U)          /**< Maximum length of the name filter array in bytes. */
/** @} */


/**
 * @defgroup BLE_GAP_TX_POWER_REPORTING_REASON TX power change reason
 * @brief Enumerates the reasons for reporting a change in TX (transmit) power.
 * @{
 */
#define BLE_GAP_LOCAL_TX_POWER_CHANGED                          (0U)           /**< Indicates that the local device's transmit power has changed. */
#define BLE_GAP_REMOTE_TX_POWER_CHANGED                         (1U)           /**< Indicates that the remote device's transmit power has changed. */
#define BLE_GAP_READ_REMOTE_POWER_COMPLETED                     (2U)           /**< Indicates that reading the remote device's transmit power level has completed successfully. */
/** @} */

/**
 * @defgroup BLE_GAP_EXT_ADV_DATA_LEN Maximum extended advertising data length
 * @brief Defines the maximum length of extended advertising data in bytes.
 * @{
 */
#define BLE_GAP_EXT_ADV_DATA_LEN                                (1650U)         /**< Maximum length of extended advertising data in bytes. */
/** @} */

/**
 * @defgroup BLE_GAP_PERI_ADV_DATA_LEN Maximum periodic advertising data length
 * @brief Defines the maximum length of periodic advertising data in bytes.
 * @{
 */
#define BLE_GAP_PERI_ADV_DATA_LEN                               (1650U)         /**< Maximum length of periodic advertising data in bytes. */
/** @} */

/**
 * @defgroup BLE_GAP_PATH_LOSS_ZONE Path loss zones
 * @brief Defines the zones based on the level of path loss detected.
 * @{
 */
#define BLE_GAP_PATH_LOSS_ZONE_LOW                              (0x00U)        /**< Indicates low path loss.  */
#define BLE_GAP_PATH_LOSS_ZONE_MID                              (0x01U)        /**< Indicates moderate path loss. */
#define BLE_GAP_PATH_LOSS_ZONE_HIGH                             (0x02U)        /**< Indicates high path loss.  */
/** @} */


/**
 * @defgroup BLE_GAP_TPL_FLAG The transmit power levels
 * @brief Defines the flags for transmit power levels.
 * @{
 */
#define BLE_GAP_TPL_FLAG_LOW                                    (0x00U)        /**< Transmit power level is low (reduced power). */
#define BLE_GAP_TPL_FLAG_MID                                    (0x01U)        /**< Transmit power level is medium. */
/** @} */


/**
 * @defgroup BLE_GAP_SUBRATE_RANGE Subrate parameters range
 * @brief Defines the range of allowable subrate parameters.
 * @{
 */
#define BLE_GAP_SUBRATE_MIN_SUBRATE_MIN                         (0x0001U)      /**< Minimum permissible value of the minimum subrate factor. */
#define BLE_GAP_SUBRATE_MIN_SUBRATE_MAX                         (0x01F4U)      /**< Maximum permissible value of the minimum subrate factor. */
#define BLE_GAP_SUBRATE_MAX_SUBRATE_MIN                         (0x0001U)      /**< Minimum permissible value of the maximum subrate factor. */
#define BLE_GAP_SUBRATE_MAX_SUBRATE_MAX                         (0x01F4U)      /**< Maximum permissible value of the maximum subrate factor. */
#define BLE_GAP_SUBRATE_LATENCY_MIN                             (0x0000U)      /**< Minimum allowed peripheral latency, defined as the number of the connection 
                                                                                    in units of subrated connection intervals. */
#define BLE_GAP_SUBRATE_LATENCY_MAX                             (0x01F3U)      /**< Maximum allowed peripheral latency, defined as the number of the connection 
                                                                                    in units of subrated connection intervals. */
#define BLE_GAP_SUBRATE_CONT_NUM_MIN                            (0x0000U)      /**< Minimum permissible value of the underlying connection events to remain active 
                                                                                    after a packet containing a PDU with a non-zero Length field is sent or received. */
#define BLE_GAP_SUBRATE_CONT_NUM_MAX                            (0x01F3U)      /**< Maximum permissible value of the underlying connection events to remain active 
                                                                                    after a packet containing a PDU with a non-zero Length field is sent or received. */
#define BLE_GAP_SUBRATE_SUPV_TIMEOUT_MIN                        (0x000AU)      /**< Minimum permissible supervision timeout for the connection. (Unit: 10 ms) */
#define BLE_GAP_SUBRATE_SUPV_TIMEOUT_MAX                        (0x0C80U)      /**< Maximum permissible supervision timeout for the connection. (Unit: 10 ms) */
/** @} */

/**
 * @defgroup BLE_GAP_PA_ENABLE_OPTION Options for enabling periodic advertising
 * @brief Defines the options for enabling periodic advertising.
 * @{
 */
#define BLE_GAP_PA_ENABLE_OPTION_EN                             (1U <<0U)      /**< Enable periodic advertising.*/
#define BLE_GAP_PA_ENABLE_OPTION_ADI                            (1U <<1U)      /**< Include the ADI field in AUX_SYNC_IND PDUs. */

/** @} */

/**
 * @defgroup BLE_GAP_PA_ENABLE_RX_OPTION Options for enabling periodic advertising train
 * @brief Defines the options for enabling periodic advertising train.
 * @{
 */
#define BLE_GAP_PA_ENABLE_RX_OPTION_EN                          (1U << 0U)     /**< Indicates to enable reporting. */
#define BLE_GAP_PA_ENABLE_RX_OPTION_FILTER                      (1U << 1U)     /**< Indicates to enable duplicate filtering. */
/** @} */

/**
 * @defgroup BLE_GAP_EXT_ADV_ADDR_CHG_REASON Reasons for changing the address
 * @brief Defines the reason for changing the address.
 * @{
 */
#define BLE_GAP_EXT_ADV_ADDR_CHG_WTIH_ADV_DATA                  (1U << 0U)     /**< Indicates to change the address whenever the advertising data changes. */
#define BLE_GAP_EXT_ADV_ADDR_CHG_WTIH_SCAN_RESP_DATA            (1U << 1U)     /**< Indicates to change the address whenever the scan response data changes. */
/** @} */


/** @} */ //BLE_GAP_DEFINES

/**
 * @addtogroup BLE_GAP_ENUMS Enumerations
 * @{
 */
 
/** @brief Enumeration of GAP events delivered to application from BLE Stack. */
typedef enum BLE_GAP_EventId_T
{
    BLE_GAP_EVT_CONNECTED,                                                     /**< BLE link established. See @ref BLE_GAP_EvtConnect_T for the event details. */
    BLE_GAP_EVT_DISCONNECTED,                                                  /**< BLE link terminated. See @ref BLE_GAP_EvtDisconnect_T for the event details. */
    BLE_GAP_EVT_CONN_PARAM_UPDATE,                                             /**< BLE link parameters updated.
                                                                                    See @ref BLE_GAP_EvtConnParamUpdateParams_T for the event details. */
    BLE_GAP_EVT_ENCRYPT_STATUS,                                                /**< BLE link encryption status. See @ref BLE_GAP_EvtEncryptStatus_T for the event details. */
    BLE_GAP_EVT_ADV_REPORT,                                                    /**< Advertising report received. See @ref BLE_GAP_EvtAdvReport_T for the event details. */
    BLE_GAP_EVT_ENC_INFO_REQUEST,                                              /**< Encryption information request received. See @ref BLE_GAP_EvtEncInfoRequest_T for the event details. */
    BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST,                                     /**< Remote connection parameter change request. See @ref BLE_GAP_EvtRemoteConnParamRequest_T 
                                                                                    for the event details. */
    BLE_GAP_EVT_EXT_ADV_REPORT,                                                /**< Extended advertising report received. See @ref BLE_GAP_EvtExtAdvReport_T for the event details. */
    BLE_GAP_EVT_ADV_TIMEOUT,                                                   /**< Advertising terminated due to timeout. */
    BLE_GAP_EVT_TX_BUF_AVAILABLE,                                              /**< ACL transmit buffer is available. See @ref BLE_GAP_EvtTxBufAvailable_T. */
    BLE_GAP_EVT_DEVICE_NAME_CHANGED,                                           /**< Device name changed remotely. 
                                                                                    See @ref BLE_GAP_EvtDeviceNameChanged_T for the event details. */
    BLE_GAP_EVT_AUTH_PAYLOAD_TIMEOUT,                                          /**< Authenticated payload timeout occurred. See @ref BLE_GAP_EvtAuthPayloadTimeout_T for the event details. */
    BLE_GAP_EVT_PHY_UPDATE,                                                    /**< PHY update completed. See @ref BLE_GAP_EvtPhyUpdate_T for the event details. */
    BLE_GAP_EVT_SCAN_REQ_RECEIVED,                                             /**< Scan request received. See @ref BLE_GAP_EvtScanReqReceived_T for the event details. */
    BLE_GAP_EVT_DIRECT_ADV_REPORT,                                             /**< Direct advertising report received. See @ref BLE_GAP_EvtDirectAdvReport_T for the event details. */
    BLE_GAP_EVT_PERI_ADV_SYNC_EST,                                             /**< Periodic advertising sync established. See @ref BLE_GAP_EvtPeriAdvSyncEst_T for the event details. */
    BLE_GAP_EVT_PERI_ADV_REPORT,                                               /**< Periodic advertising report received. See @ref BLE_GAP_EvtPeriAdvReport_T for the event details. */
    BLE_GAP_EVT_PERI_ADV_SYNC_LOST,                                            /**< Periodic advertising sync lost. See @ref BLE_GAP_EvtPeriAdvSyncLost_T for the event details. */
    BLE_GAP_EVT_ADV_SET_TERMINATED,                                            /**< Advertising set terminated. See @ref BLE_GAP_EvtAdvSetTerminated_T for the event details. */
    BLE_GAP_EVT_SCAN_TIMEOUT,                                                  /**< Scan terminated due to timeout. */
    BLE_GAP_EVT_TRANSMIT_POWER_REPORTING,                                      /**< Transmit power level reporting for the ACL connection identified by the Connection_Handle. 
                                                                                    See @ref BLE_GAP_EvtTxPowerReporting_T for the event details. */
    BLE_GAP_EVT_ADV_COMPL,                                                     /**< One-time advertising completed. See @ref BLE_GAP_EvtAdvCompl_T for the event details. */
    BLE_GAP_EVT_PATH_LOSS_THRESHOLD,                                           /**< Path loss threshold crossing reported on the ACL connection. 
                                                                                    See @ref BLE_GAP_EvtPathLossThreshold_T for the event details. */
    BLE_GAP_EVT_FEATURE_EXCHANGE_COMPL,                                        /**< Feature exchange with the remote device completed. */
    BLE_GAP_EVT_SUBRATE_CHANGE,                                                /**< indicate that a Connection Subrate Update procedure has completed and some parameters of 
                                                                                    the specified connection have changed.  See @ref BLE_GAP_EvtSubrateChange_T for the event details. */
    BLE_GAP_EVT_END                                                            /**< End of BLE GAP event enumeration. */
}BLE_GAP_EventId_T;

/** @} */ //BLE_GAP_ENUMS

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup BLE_GAP_STRUCTS Structures
 * @{
 */
 
/** @brief Structure for Bluetooth address. */
typedef struct BLE_GAP_Addr_T
{
    uint8_t                 addrType;                               /**< Address type indicating public or random address. Refer to @ref BLE_GAP_ADDR_TYPE for possible values. */
    uint8_t                 addr[GAP_MAX_BD_ADDRESS_LEN];           /**< Device's Bluetooth address in Least Significant Byte (LSB) format. */
} BLE_GAP_Addr_T;


/** @brief Structure for configuring advertising parameters. */
typedef struct BLE_GAP_AdvParams_T
{
    uint16_t                intervalMin;                            /**< Minimum advertising interval. Value range defined in @ref BLE_GAP_ADV_INTERVAL. Unit: 0.625 ms. */
    uint16_t                intervalMax;                            /**< Maximum advertising interval. Value range defined in @ref BLE_GAP_ADV_INTERVAL. Unit: 0.625 ms. */
    uint8_t                 type;                                   /**< Type of advertising. Refer to @ref BLE_GAP_ADV_TYPE for possible values. */
    BLE_GAP_Addr_T          peerAddr;                               /**< Peer device's Bluetooth address and type. See @ref BLE_GAP_Addr_T for structure details. */
    uint8_t                 advChannelMap;                          /**< Bitmap indicating which of the three advertising channels will be used. 
                                                                         See @ref BLE_GAP_ADV_CHANNEL for the definitions. */
    uint8_t                 filterPolicy;                           /**< Advertising filter policy to determine how the advertiser filters scan and connection requests. 
                                                                         See @ref BLE_GAP_ADV_FILTER_POLICY for options. */
} BLE_GAP_AdvParams_T;


/** @brief Structure for configuring connection parameters. */
typedef struct BLE_GAP_ConnParams_T
{
    uint16_t                intervalMin;                            /**< Minimum allowed connection interval in 1.25ms units. Value must not exceed intervalMax. 
                                                                         See @ref BLE_GAP_CP_RANGE for the valid ranges. */
    uint16_t                intervalMax;                            /**< Maximum allowed connection interval in 1.25ms units. See @ref BLE_GAP_CP_RANGE for the valid ranges. */
    uint16_t                latency;                                /**< Peripheral latency for the connection in terms of number of connection events. 
                                                                         See @ref BLE_GAP_CP_RANGE for the valid ranges. */
    uint16_t                supervisionTimeout;                     /**< Supervision timeout for the connection in 10ms units. Must be equal to or greater than (1 + latency) * intervalMax * 2. 
                                                                         See @ref BLE_GAP_CP_RANGE for valid ranges. */
} BLE_GAP_ConnParams_T;


/** @brief Structure for configuring advertising data. */
typedef struct BLE_GAP_AdvDataParams_T
{
    uint8_t                 advLen;                                 /**< Length of advertising data. Maximum length defined by @ref BLE_GAP_ADV_DATA_LEN. */
    uint8_t                 advData[BLE_GAP_ADV_MAX_LENGTH];        /**< Advertising data buffer. Contains the actual advertising payload. */
} BLE_GAP_AdvDataParams_T;


/** @brief Structure for configuring resolving list.*/
typedef struct BLE_GAP_ResolvingListParams_T
{
    BLE_GAP_Addr_T          peerIdAddr;                             /**< Peer identity address. Used to identify the peer device. See @ref BLE_GAP_Addr_T. */
    uint8_t                 peerIrk[16];                            /**< IRK (Identity Resolving Key) of the peer device. Used for address resolution and privacy. */
    uint8_t                 localIrk[16];                           /**< IRK of the local device. Used for generating Resolvable Private Addresses (RPAs). */
    uint8_t                 privacyMode;                            /**< Privacy mode. Defines how the device will handle privacy for this peer. 
                                                                         See @ref BLE_GAP_PRIVACY_MODE for possible values. */
} BLE_GAP_ResolvingListParams_T;


/** @brief Structure for configuring privacy parameters. */
typedef struct BLE_GAP_LocalPrivacyParams_T
{
    uint8_t                 privacyAddrType;                        /**< Type of the private address. Only resolvable (BLE_GAP_ADDR_TYPE_RANDOM_RESOLVABLE) or 
                                                                         non-resolvable (BLE_GAP_ADDR_TYPE_RANDOM_NON_RESOLVABLE) random addresses are allowed. */
    uint16_t                addrTimeout;                            /**< Time interval in seconds before the device changes its Random Private Address. 
                                                                         Range defined by @ref BLE_GAP_RPA_TIMEOUT. */
    uint8_t                 localIrk[16];                           /**< Local IRK. If all zeros, the default IRK will be used. Used for generating own RPAs. */
} BLE_GAP_LocalPrivacyParams_T;


/** @brief Structure for configuring scanning parameters. */
typedef struct BLE_GAP_ScanningParams_T
{
    uint8_t                 type;                                   /**< Scanning type (active or passive). See @ref BLE_GAP_SCAN_TYPE for possible values. */
    uint16_t                interval;                               /**< Time interval from when the device starts its last scan until it begins the subsequent scan (0.625 ms units). 
                                                                         See @ref BLE_GAP_SCAN_INTERVAL for valid ranges. */
    uint16_t                window;                                 /**< Duration of the scan window when the device is listening for advertising packets (0.625 ms units). 
                                                                         See @ref BLE_GAP_SCAN_WINDOW for valid ranges. */
    uint8_t                 filterPolicy;                           /**< Filter policy to apply during scanning. See @ref BLE_GAP_SCAN_FP for possible values. */
    uint8_t                 disChannel;                             /**< Bitmask to disable specific channels during scanning. See @ref BLE_GAP_SCAN_CHANNEL for structure details */
} BLE_GAP_ScanningParams_T;


/** @brief Structure for configuring parameters to create a BLE connection. */
typedef struct BLE_GAP_CreateConnParams_T
{
    uint16_t                scanInterval;                           /**< Scan interval used during connection establishment (0.625 ms units). See @ref BLE_GAP_SCAN_INTERVAL. */
    uint16_t                scanWindow;                             /**< Scan window used during connection establishment (0.625 ms units). 
                                                                         Must be less than or equal to scanInterval. See @ref BLE_GAP_SCAN_WINDOW. */
    uint8_t                 filterPolicy;                           /**< Initiator filter policy used to determine if the Filter Accept List is used. See @ref BLE_GAP_INIT_FP for possible values. 
                                                                         If the Filter Accept List is not used, the peerAddr argument specifies the address type and address 
                                                                         of the advertising device to connect to. */
    BLE_GAP_Addr_T          peerAddr;                               /**< Address of the peer device to connect to. Ignored if filterPolicy is set to use the Filter Accept List. See @ref BLE_GAP_Addr_T. */
    BLE_GAP_ConnParams_T    connParams;                             /**< Desired connection parameters. See @ref BLE_GAP_ConnParams_T for structure details. */
} BLE_GAP_CreateConnParams_T;


/** @brief Structure for configuring supplementary parameters for extended connection creation. */
typedef struct BLE_GAP_ExtCreateConnParams_T
{
    bool                    enable;                                 /**< Indicates if the extended connection creation parameters are to be used. */
    uint16_t                scanInterval;                           /**< Extended scan interval (0.625 ms units). See @ref BLE_GAP_EXT_SCAN_INTERVAL for valid ranges. */
    uint16_t                scanWindow;                             /**< Extended scan window (0.625 ms units). See @ref BLE_GAP_EXT_SCAN_WINDOW for valid ranges. */
    BLE_GAP_ConnParams_T    connParams;                             /**< Connection parameters for extended connection creation. See @ref BLE_GAP_ConnParams_T for structure details. */
}BLE_GAP_ExtCreateConnParams_T;


/** @brief Structure for configuring PHY-specific settings for extended connection creation. */
typedef struct BLE_GAP_ExtCreateConnPhy_T
{
    BLE_GAP_ExtCreateConnParams_T    le1mPhy;                       /**< Scan connectable advertisements on the LE 1M PHY, and the connection parameters for the LE 1M PHY are provided. See @ref BLE_GAP_ExtCreateConnParams_T.*/
    BLE_GAP_ExtCreateConnParams_T    le2mPhy;                       /**< The connection parameters for the LE 2M PHY are provided. See @ref BLE_GAP_ExtCreateConnParams_T. */
    BLE_GAP_ExtCreateConnParams_T    leCodedPhy;                    /**< Scan connectable advertisements on the LE Coded PHY, and the connection parameters for the LE 1M Coded are provided. See @ref BLE_GAP_ExtCreateConnParams_T. */
}BLE_GAP_ExtCreateConnPhy_T;


/** @brief Structure for configuring extended advertising parameters. */
typedef struct BLE_GAP_ExtAdvParams_T
{
    uint8_t                 advHandle;                              /**< Identifies the advertising set whose parameters are being configured. Valid range: 0 to 0xEF. 
                                                                        Refer to @ref BLE_GAP_MAX_ADV_HANDLE for the maximum value. */
    uint16_t                evtProperies;                           /**< The type of advertising event that is being configured and its properties. 
                                                                         Combinations of bits from @ref BLE_GAP_EXT_ADV_EVT_PROP are used to define the event properties. */
    uint32_t                priIntervalMin;                         /**< Minimum primary advertising interval. Valid range: 0x20 to 0x1F4000. Unit: 0.625 ms. 
                                                                         Refer to @ref BLE_GAP_EXT_PRIMARY_ADV_INTERVAL for more details. */
    uint32_t                priIntervalMax;                         /**< Maximum primary advertising interval. Valid range: 0x20 to 0x1F4000. Unit: 0.625 ms. 
                                                                         Refer to @ref BLE_GAP_EXT_PRIMARY_ADV_INTERVAL for more details. */
    uint8_t                 priChannelMap;                          /**< Bitfield indicating the advertising channels to be used. Refer to @ref BLE_GAP_ADV_CHANNEL for channel definitions. 
                                                                         Note: BLE_GAP_ADV_CHANNEL_ALL is not permitted. */
    BLE_GAP_Addr_T          peerAddr;                               /**< Remote Bluetooth address and address type. Refer to @ref BLE_GAP_Addr_T for structure details. */
    uint8_t                 filterPolicy;                           /**< Advertising filter policy. Refer to @ref BLE_GAP_ADV_FILTER_POLICY for possible values. */
    int8_t                  txPower;                                /**< The maximum transmit power level for advertising packets on the advertising channels. 
                                                                         Set to 0x7F if no preference is specified. The level will be adjusted if the value is out of range. */
    uint8_t                 priPhy;                                 /**< The PHY on which the advertising packets are transmitted on the primary advertising channel. 
                                                                         Note: 2M PHY cannot be used for primary advertising. Refer to @ref BLE_GAP_PHY_TYPE for possible values. */
    uint8_t                 secMaxSkip;                             /**< The maximum number of advertising events that can be skipped before sending an AUX_ADV_IND. */
    uint8_t                 secPhy;                                 /**< The PHY on which the advertising packets are transmitted on the secondary advertising channel. 
                                                                         Refer to @ref BLE_GAP_PHY_TYPE for possible values. */
    uint8_t                 sid;                                    /**< The value to be transmitted in the Advertising SID subfield of the ADI field in the Extended Header. 
                                                                         Refer to @ref BLE_GAP_ADV_SID_RANGE for the valid range. */
    bool                    scanReqNotifiEnable;                    /**< Indicates whether notifications should be sent upon receipt of a scan request PDU. 
                                                                         Set to true to enable notifications, or false to disable them. */
    uint8_t                 priPhyOptions;                          /**< Host prefer coding scheme if primary advertising uses LE Coded PHY. 
                                                                         Refer to @ref BLE_GAP_CODED_PHY_OPTIONS for options. */
    uint8_t                 secPhyOptions;                          /**< Host prefer coding scheme if secondary advertising uses LE Coded PHY. 
                                                                         Refer to @ref BLE_GAP_CODED_PHY_OPTIONS for options. */
} BLE_GAP_ExtAdvParams_T;


/** @brief Structure for configuring extended advertising data parameters. */
typedef struct BLE_GAP_ExtAdvDataParams_T
{
    uint8_t                 advHandle;                              /**< Identifies the advertising set whose data parameters are being configured. 
                                                                         Valid range: 0 to 0xEF. Refer to @ref BLE_GAP_MAX_ADV_HANDLE for the maximum value. */
    uint8_t                 operation;                              /**< Specifies how the advertising data should be set. Refer to @ref BLE_GAP_EXT_ADV_DATA_OPERAION for possible values. 
                                                                         Note: BLE_GAP_EXT_ADV_DATA_OP_UNCHANGED cannot be used with BLE_GAP_SetExtScanRspData. */
    uint8_t                 fragPreference;                         /**< Configures whether advertising data should be fragmented. Refer to @ref BLE_GAP_EXT_ADV_DATA_FRAG_PREF for possible values. */
    uint16_t                advLen;                                 /**< Length of the advertising data. Valid range: 0 to 1650 bytes. 
                                                                         Refer to @ref BLE_GAP_EXT_ADV_DATA_LEN for the definition. */
    uint8_t                 *p_advData;                             /**< Pointer to the advertising data buffer. */
} BLE_GAP_ExtAdvDataParams_T;


/** @brief Structure for configuring extended advertising enable parameters. */
typedef struct BLE_GAP_ExtAdvEnableParams_T
{
    uint8_t                 advHandle;                              /**< Identifies the advertising set to be enabled or disabled. Valid range: 0 to 0xEF. 
                                                                         Refer to @ref BLE_GAP_MAX_ADV_HANDLE for the maximum value. */
    uint16_t                duration;                               /**< Duration for which the advertising set is enabled. Set to 0x0000 for continuous advertising until 
                                                                         manually disabled. Unit: 10 ms. */
    uint8_t                 maxExtAdvEvts;                          /**< Maximum number of extended advertising events to be sent before the advertising set is disabled, 
                                                                         even if the duration has not expired. */
}BLE_GAP_ExtAdvEnableParams_T;


/** @brief Structure for configuring periodic advertising parameters. */
typedef struct BLE_GAP_PeriAdvParams_T
{
    uint8_t                 advHandle;                              /**< Identifies the advertising set whose periodic advertising parameters are being configured. 
                                                                         Valid range: 0 to 0xEF. Refer to @ref BLE_GAP_MAX_ADV_HANDLE for the maximum value. */
    uint16_t                intervalMin;                            /**< Minimum interval for periodic advertising. Unit: 1.25 ms. Refer to @ref BLE_GAP_PRIODIC_ADV_INTERVAL 
                                                                         for more details. */
    uint16_t                intervalMax;                            /**< Maximum interval for periodic advertising. Unit: 1.25 ms. Refer to @ref BLE_GAP_PRIODIC_ADV_INTERVAL 
                                                                         for more details. */
    uint16_t                properties;                             /**< Bitfield indicating the fields to be included in the advertising packet. 
                                                                         Combinations of bits from @ref BLE_GAP_PERIODIC_ADV_PROP define the properties. */
} BLE_GAP_PeriAdvParams_T;


/** @brief Structure for configuring periodic advertising data. */
typedef struct BLE_GAP_PeriAdvDataParams_T
{
    uint8_t                 advHandle;                              /**< Identifies the advertising set whose periodic advertising parameters are being configured. 
                                                                         Valid range: 0 to 0xEF. Refer to @ref BLE_GAP_MAX_ADV_HANDLE for the maximum value. */
    uint8_t                 operation;                              /**< Specifies how the advertising data should be set. Refer to @ref BLE_GAP_PERIODIC_ADV_DATA_OPERAION 
                                                                         for possible values. */
    uint16_t                advLen;                                 /**< Length of the advertising data. Valid range: 0 to 1650 bytes. Refer to @ref BLE_GAP_PERI_ADV_DATA_LEN 
                                                                         for the definition. */
    uint8_t                 *p_advData;                             /**< Pointer to the advertising data buffer. */
} BLE_GAP_PeriAdvDataParams_T;


/** @brief Structure for the Device Name characteristic with write property configuration. */
typedef struct BLE_GAP_CharDeviceName_T
{
    bool                    enableWriteProperty;                    /**< True to enable write access to the Device Name characteristic, false to disable. */
} BLE_GAP_CharDeviceName_T;


/** @brief Structure for the Appearance characteristic containing the appearance value. */
typedef struct BLE_GAP_CharAppearance_T
{
    uint16_t                appearance;                             /**< Appearance value as defined by the Bluetooth SIG Assigned Numbers for Appearance characteristic. 
                                                                         See @ref GAP_APPEARANCE_DEF. */
} BLE_GAP_CharAppearance_T;


/** @brief Structure for the Peripheral Preferred Connection Parameters characteristic. */
typedef struct BLE_GAP_CharPeriPreferConnParams_T
{
    bool                    enable;                                 /**< True to enable the Peripheral Preferred Connection Parameters characteristic, false to disable. */
    uint16_t                minConnInterval;                        /**< Minimum connection interval in 1.25ms units. See @ref BLE_GAP_CP_RANGE. */
    uint16_t                maxConnInterval;                        /**< Maximum connection interval in 1.25ms units. See @ref BLE_GAP_CP_RANGE. */
    uint16_t                peripheralLatency;                      /**< Number of connection events the peripheral can skip (latency). See @ref BLE_GAP_CP_RANGE. */
    uint16_t                connSupervisionTimeoutMulti;            /**< Connection supervision timeout multiplier (in 10ms units). */
} BLE_GAP_CharPeriPreferConnParams_T;


/** @brief Structure for the Encrypted Data Key Material characteristic. */
typedef struct BLE_GAP_CharEncDataKeyMatl_T
{
    bool                    enable;                                 /**< True to enable the Encrypted Data Key Material characteristic, false to disable. */
} BLE_GAP_CharEncDataKeyMatl_T;

/** @brief Structure for the LE GATT Security Levels characteristic. */
typedef struct BLE_GAP_CharLeGattSecLvls_T
{
    bool                    enable;                                 /**< True to enable the LE GATT Security Levels characteristic, false to disable. */
} BLE_GAP_CharLeGattSecLvls_T;

/** @brief Structure for configuring built-in service options. */
typedef struct BLE_GAP_ServiceOption_T
{
    BLE_GAP_CharDeviceName_T                charDeviceName;             /**< Configuration for the Device Name characteristic. See @ref BLE_GAP_CharDeviceName_T. */
    BLE_GAP_CharAppearance_T                charAppearance;             /**< Configuration for the Appearance characteristic. See @ref BLE_GAP_CharAppearance_T. */
    BLE_GAP_CharPeriPreferConnParams_T      charPeriPreferConnParam;    /**< Configuration for the Peripheral Preferred Connection Parameters characteristic. 
                                                                                See @ref BLE_GAP_CharPeriPreferConnParams_T.*/
    BLE_GAP_CharEncDataKeyMatl_T            charEncDataKeyMatl;         /**< Configuration for the Encrypted Data Key Material characteristic. See @ref BLE_GAP_CharEncDataKeyMatl_T. */
    BLE_GAP_CharLeGattSecLvls_T             charLeGattSecLvls;          /**< Configuration for the LE GATT Security Levels characteristic. See @ref BLE_GAP_CharLeGattSecLvls_T. */
} BLE_GAP_ServiceOption_T;


/** @brief Structure for configuring extended scan parameters. */
typedef struct BLE_GAP_ExtScanningParams_T
{
    bool                    enable;                                 /**< Indicates if the extended scan configuration is active. */
    uint8_t                 type;                                   /**< Type of scanning to perform, as defined in @ref BLE_GAP_SCAN_TYPE. */
    uint16_t                interval;                               /**< Time between scan windows, specified in units of 0.625 ms. See @ref BLE_GAP_EXT_SCAN_INTERVAL 
                                                                         for valid ranges. */
    uint16_t                window;                                 /**< Duration of a scan window, specified in units of 0.625 ms. See @ref BLE_GAP_EXT_SCAN_WINDOW 
                                                                         for valid ranges. */
    uint8_t                 disChannel;                             /**< Channel to be disabled during scanning, as defined in @ref BLE_GAP_SCAN_CHANNEL. */
} BLE_GAP_ExtScanningParams_T;


/** @brief Structure for configuring PHY-specific extended scan. */
typedef struct BLE_GAP_ExtScanningPhy_T
{
    BLE_GAP_ExtScanningParams_T    le1mPhy;                         /**< Configuration for scanning on the LE 1M PHY. See @ref BLE_GAP_ExtScanningParams_T. */
    BLE_GAP_ExtScanningParams_T    leCodedPhy;                      /**< Configuration for scanning on the LE Coded PHY. See @ref BLE_GAP_ExtScanningParams_T. */
} BLE_GAP_ExtScanningPhy_T;


/** @brief Structure for enabling or disabling extended scanning. */
typedef struct BLE_GAP_ExtScanningEnable_T
{
    bool                    enable;                                 /**< Flag to enable or disable scanning. */
    uint8_t                 filterDuplicates;                       /**< Setting for duplicate filtering, as defined in @ref BLE_GAP_SCAN_FD. */
    uint16_t                duration;                               /**< Duration of the scanning process, in units of 10 ms. A value of 0x0000 means continuous scanning.*/
    uint16_t                period;                                 /**< Interval between consecutive scan durations, in units of 1.28 seconds. 
                                                                         A value of 0x0000 disables periodic scanning. */
} BLE_GAP_ExtScanningEnable_T;


/** @brief Structure for creating synchronization with periodic advertising. */
typedef struct BLE_GAP_CreateSync_T
{
    uint8_t                 options;                                /**< Options for using the Periodic Advertiser List and enabling/disabling reports, as defined 
                                                                         in @ref BLE_GAP_SYNC_CREATE_OPTION. */
    uint8_t                 advSid;                                 /**< Advertising Set Identifier for identifying the Periodic Advertising, as defined in @ref BLE_GAP_ADV_SID_RANGE. */
    BLE_GAP_Addr_T          advAddr;                                /**< Address of the advertiser, either public or random (static) identity. See @ref BLE_GAP_Addr_T. */
    uint16_t                skip;                                   /**< Number of periodic advertising packets that can be skipped after a successful receive, 
                                                                         ranging from 0x0000 to 0x01F3. Refer to @ref BLE_GAP_SYNC_SKIP for maximun value. */
    uint16_t                syncTimeout;                            /**< Timeout for synchronization with the periodic advertising train, in units of 10 ms. 
                                                                         Must be equal to or greater than (2+skip)*(periodic advertising interval). 
                                                                         Refer to @ref BLE_GAP_SYNC_TIMEOUT for valid ranges. */
}BLE_GAP_CreateSync_T;


/** @brief Structure for configuring synchronization device parameters. */
typedef struct BLE_GAP_SyncSetDev_T
{
    BLE_GAP_Addr_T          advAddr;                                /**< Advertiser address. Can be either a public address or a random (static) identity address. See @ref BLE_GAP_Addr_T. */
    uint8_t                 advSid;                                 /**< Advertising Set Identifier (SID). Used to identify the Periodic Advertising. 
                                                                         Refer to @ref BLE_GAP_ADV_SID_RANGE for valid ranges. */
}BLE_GAP_SyncSetDev_T;


/** @brief Structure for configuring a manufacturer-specific data filter in BLE GAP scanning. */
typedef struct BLE_GAP_ScanFilterMsd_T
{
    uint8_t                 companyId[2];                           /**< Manufacturer Company Identifier: Unique two-byte identifier assigned by the Bluetooth SIG to member companies. */
    uint8_t                 msdLen;                                 /**< Length of the manufacturer-specific data to be compared. */
    uint8_t                 msd[BLE_GAP_SCAN_MSD_MAX_LEN];          /**< Manufacturer-specific data for comparison. */
} BLE_GAP_ScanFilterMsd_T;


/** @brief Structure for configuring a service data filter in BLE GAP scanning. */
typedef struct BLE_GAP_ScanFilterServiceData_T
{
    uint8_t                 uuidLen;                                /**< Length of the Service UUID to be compared. Valid lengths are 2, 4, or 16 bytes for 16-bit, 32-bit, 
                                                                         or 128-bit Service UUIDs, respectively. */
    uint8_t                 uuidData[16];                           /**< Service UUID data for comparison. */
    uint8_t                 svcDataLen;                             /**< Length of the service data to be compared. Maximum length is defined by @ref BLE_GAP_SCAN_SERVICE_DATA_MAX_LEN. */
    uint8_t                 svcData[BLE_GAP_SCAN_SERVICE_DATA_MAX_LEN];   /**< Service data for comparison. */
} BLE_GAP_ScanFilterServiceData_T;


/** @brief Structure for configuring a name filte in BLE GAP scanning. */
typedef struct BLE_GAP_ScanFilterName_T
{
    uint8_t                 nameLen;                                /**< Length of the target name to be compared. */
    uint8_t                 targetName[BLE_GAP_SCAN_NAME_MAX_LEN];  /**< Target name data for comparison. */
} BLE_GAP_ScanFilterName_T;


/** @brief Structure for configuring path loss reporting parameters. */
typedef struct BLE_GAP_PathLossReportingParams_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint8_t                 highThreshold;                          /**< High threshold for path loss detection. Exceeding this value triggers an event. (Unit: dBm) */
    uint8_t                 highHysteresis;                         /**< Hysteresis for the high threshold to prevent frequent reporting due to small changes in path loss. (Unit: dBm) */
    uint8_t                 lowThreshold;                           /**< Low threshold for path loss detection. Falling below this value triggers an event. (Unit: dBm) */
    uint8_t                 lowHysteresis;                          /**< Hysteresis for the low threshold to prevent frequent reporting due to small changes in path loss. (Unit: dBm) */
    uint16_t                minTimeSpent;                           /**< Minimum time (in number of connection events) that the path loss must be observed beyond 
                                                                         the threshold before an event is reported. */
} BLE_GAP_PathLossReportingParams_T;


/** @brief Structure for configuring subrate parameters. */
typedef struct BLE_GAP_SubrateParams_T
{
    uint16_t                subrateMin;                             /**< Minimum subrate value. See @ref BLE_GAP_SUBRATE_RANGE for the valid ranges. */
    uint16_t                subrateMax;                             /**< Maximum subrate value. See @ref BLE_GAP_SUBRATE_RANGE for the valid ranges. */
    uint16_t                maxLatency;                             /**< Maximum allowed latency. See @ref BLE_GAP_SUBRATE_RANGE for the valid ranges. */
    uint16_t                continuationNum;                        /**< Number of continuation packets. See @ref BLE_GAP_SUBRATE_RANGE for the valid ranges. */
    uint16_t                supervisionTimeout;                     /**< Supervision timeout. See @ref BLE_GAP_SUBRATE_RANGE for the valid ranges. */
}BLE_GAP_SubrateParams_T;


/** @brief Structure for configuring scan filter parameters. */
typedef struct BLE_GAP_ScanFilterConfig_T
{
    uint8_t                         nameFilterEnable    : 1;        /**< Set to 1 to enable filtering by name, 0 to disable. */
    uint8_t                         svcDataFilterEnable : 1;        /**< Set to 1 to enable filtering by service data, 0 to disable. */
    uint8_t                         msdFilterEnable     : 1;        /**< Set to 1 to enable filtering by manufacturer specific data, 0 to disable. */
    BLE_GAP_ScanFilterName_T        nameFilter;                     /**< Configuration for name filter. See @ref BLE_GAP_ScanFilterName_T. */
    BLE_GAP_ScanFilterServiceData_T serviceDataFilter;              /**< Configuration for service data filter. See @ref BLE_GAP_ScanFilterServiceData_T. */
    BLE_GAP_ScanFilterMsd_T         msdFilter;                      /**< Configuration for manufacturer specific data filter. See @ref BLE_GAP_ScanFilterMsd_T. */
} BLE_GAP_ScanFilterConfig_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_DISCONNECTED event.
 * This event is triggered when a BLE connection is terminated.
 */
typedef struct BLE_GAP_EvtDisconnect_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint8_t                 reason;                                 /**< Reason for disconnection, as defined in @ref GAP_STATUS. */
} BLE_GAP_EvtDisconnect_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_CONNECTED event.
 * This event is triggered upon the completion of a BLE connection.
 */
typedef struct BLE_GAP_EvtConnect_T
{
    uint8_t                 status;                                 /**< Connection status, as defined in @ref GAP_STATUS. */
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint8_t                 role;                                   /**< Role in the connection, as defined in @ref BLE_GAP_ROLE. */
    BLE_GAP_Addr_T          remoteAddr;                             /**< Bluetooth address of the remote device. See @ref BLE_GAP_Addr_T for structure details. */
    uint8_t                 localRpaAddr[GAP_MAX_BD_ADDRESS_LEN];   /**< Local Resolvable Private Address used, if privacy is enabled; otherwise, all zeros. */
    uint8_t                 remoteRpaAddr[GAP_MAX_BD_ADDRESS_LEN];  /**< Peer's Resolvable Private Address, if address resolution is successful; otherwise, all zeros. */
    uint16_t                interval;                               /**< Connection interval in use, in units of 1.25ms. */
    uint16_t                latency;                                /**< Peripheral latency for the connection in number of connection events. */
    uint16_t                supervisionTimeout;                     /**< Supervision timeout for the connection, in units of 10ms. */
} BLE_GAP_EvtConnect_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_CONN_PARAM_UPDATE event.
 * This event is triggered when the connection parameter is updated.
 */
typedef struct BLE_GAP_EvtConnParamUpdateParams_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint8_t                 status;                                 /**< Status of the connection parameter update, as defined in @ref GAP_STATUS. */
    BLE_GAP_ConnParams_T    connParam;                              /**< Updated connection parameters. See @ref BLE_GAP_ConnParams_T for structure details. */
} BLE_GAP_EvtConnParamUpdateParams_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_ENCRYPT_STATUS event.
 * This event is triggered when the encryption status is changed.
 */
typedef struct BLE_GAP_EvtEncryptStatus_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint8_t                 status;                                 /**< Encryption status: GAP_STATUS_SUCCESS for successful encryption, other values indicate failure 
                                                                         reasons as defined in @ref GAP_STATUS. */
} BLE_GAP_EvtEncryptStatus_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_ADV_REPORT event.
 * This event is generated when an advertising report is received.
 */
typedef struct BLE_GAP_EvtAdvReport_T
{
    uint8_t                 eventType;                              /**< Type of advertising event. Refer to @ref BLE_GAP_ADV_RPT_EVT_TYPE for possible values. */
    BLE_GAP_Addr_T          addr;                                   /**< Bluetooth address of the advertising device. See @ref BLE_GAP_Addr_T. */
    uint8_t                 length;                                 /**< Length of the advertising data in bytes. */
    uint8_t                 advData[BLE_GAP_ADV_MAX_LENGTH];        /**< Buffer containing the advertising data. */
    int8_t                  rssi;                                   /**< Received Signal Strength Indication for the advertising packet. */
} BLE_GAP_EvtAdvReport_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_ENC_INFO_REQUEST event.
 * This event is triggered when a encryption information request is received.
 */
typedef struct BLE_GAP_EvtEncInfoRequest_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
} BLE_GAP_EvtEncInfoRequest_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST event.
 * This event is triggered when a connection parameter update request is received.
 */
typedef struct BLE_GAP_EvtRemoteConnParamRequest_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint16_t                intervalMin;                            /**< Minimum requested value for the connection interval, in 1.25ms units. */
    uint16_t                intervalMax;                            /**< Maximum requested value for the connection interval, in 1.25ms units. */
    uint16_t                latency;                                /**< Requested peripheral latency, defining the number of connection events the peripheral can ignore. */
    uint16_t                timeout;                                /**< Requested supervision timeout, defining the time after which the connection is considered lost 
                                                                         if no data is received, in 10ms units. */
} BLE_GAP_EvtRemoteConnParamRequest_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_EXT_ADV_REPORT event.
 * This event is generated when a extended advertising report is received.
 */
typedef struct BLE_GAP_EvtExtAdvReport_T
{
    uint8_t                 eventType;                              /**< Type of extended advertising event. Refer to @ref BLE_GAP_EXT_ADV_REPORT_EVT_TYPE for possible values. */
    uint8_t                 dataStatus;                             /**< Status of the advertising data. Refer to @ref BLE_GAP_EXT_ADV_REPORT_DATA_STATUS for status values. */
    BLE_GAP_Addr_T          addr;                                   /**< Bluetooth address of the advertising device. See @ref BLE_GAP_Addr_T. */
    uint8_t                 priPhy;                                 /**< Primary advertising PHY. Refer to @ref BLE_GAP_EXT_ADV_REPORT_PHY for PHY types. */
    uint8_t                 secPhy;                                 /**< Secondary advertising PHY. Refer to @ref BLE_GAP_EXT_ADV_REPORT_PHY for PHY types. */
    uint8_t                 sid;                                    /**< Advertising Set Identifier. Values 0x00 to 0x0F correspond to the SID subfield in the ADI field of the PDU. 
                                                                         Value 0xFF indicates no ADI field in the PDU. */
    int8_t                  txPower;                                /**< Transmit power of the advertising packet in dBm. */
    int8_t                  rssi;                                   /**< Received Signal Strength Indication for the advertising packet. */
    uint16_t                periodAdvInterval;                      /**< Interval of periodic advertising, in 1.25ms units. */
    BLE_GAP_Addr_T          directAddr;                             /**< Targeted address for directed advertising. See @ref BLE_GAP_Addr_T. */
    uint8_t                 length;                                 /**< Length of the extended advertising data in bytes. */
    uint8_t                 advData[BLE_GAP_EXT_ADV_FRAGMENT_MAX_LENGTH];   /**< Buffer containing the fragmented extended advertising data. */
} BLE_GAP_EvtExtAdvReport_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_TX_BUF_AVAILABLE event.
 * This event is triggered when data transmission buffer is available.
 */
typedef struct BLE_GAP_EvtTxBufAvailable_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
} BLE_GAP_EvtTxBufAvailable_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_DEVICE_NAME_CHANGED event.
 * This event is triggered when the device name is changed.
 */
typedef struct BLE_GAP_EvtDeviceNameChanged_T
{
    uint8_t                 length;                                 /**< Length of the device name in bytes. */
    uint8_t                 devName[GAP_MAX_DEVICE_NAME_LEN];       /**< Buffer containing the new device name. */
} BLE_GAP_EvtDeviceNameChanged_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_AUTH_PAYLOAD_TIMEOUT event.*/
typedef struct BLE_GAP_EvtAuthPayloadTimeout_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
} BLE_GAP_EvtAuthPayloadTimeout_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_PHY_UPDATE event.
 * This event is triggered when PHY is updated during a BLE connection.
 */ 
typedef struct BLE_GAP_EvtPhyUpdate_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint8_t                 status;                                 /**< Result of the PHY update procedure. See @ref GAP_STATUS for possible values.*/
    uint8_t                 txPhy;                                  /**< Configured PHY for transmissions. See @ref BLE_GAP_PHY_TYPE for possible values. */
    uint8_t                 rxPhy;                                  /**< Configured PHY for receptions. See @ref BLE_GAP_PHY_TYPE for possible values. */
}BLE_GAP_EvtPhyUpdate_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_SCAN_REQ_RECEIVED event.
 * This event is triggered when a scan request is received during advertising.
 */
typedef struct BLE_GAP_EvtScanReqReceived_T
{
    uint8_t                 advHandle;                              /**< Handle identifying the advertising set that received the scan request. */
    BLE_GAP_Addr_T          scannerAddr;                            /**< Bluetooth address of the device that sent the scan request. See @ref BLE_GAP_Addr_T. */
}BLE_GAP_EvtScanReqReceived_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_DIRECT_ADV_REPORT event.
 * This event is generated when a directed advertising report is received.
 */
typedef struct BLE_GAP_EvtDirectAdvReport_T
{
    uint8_t                 numReports;                             /**< Number of directed advertisements reports in the event. */
    uint8_t                 eventType;                              /**< Even type. See @ref BLE_GAP_ADV_RPT_EVT_TYPE for possible values. */
    BLE_GAP_Addr_T          addr;                                   /**< The address of the advertiser sending the directed advertisements. See @ref BLE_GAP_Addr_T. */
    BLE_GAP_Addr_T          directAddr;                             /**< The address the directed advertisements are being directed to. See @ref BLE_GAP_Addr_T. */
    int8_t                  rssi;                                   /**< Received Signal Strength Indication in dBm. */
}BLE_GAP_EvtDirectAdvReport_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_PERI_ADV_SYNC_EST event.
 * This event is raised when synchronization with a periodic advertiser is established.
 */
typedef struct BLE_GAP_EvtPeriAdvSyncEst_T
{
    uint8_t                 status;                                 /**< Status of the periodic advertising sync establishment. See @ref GAP_STATUS for possible values.*/
    uint16_t                syncHandle;                             /**< Handle identifying the periodic advertising sync. */
    uint8_t                 advSid;                                 /**< Advertising Set Identifier of the periodic advertiser. */
    BLE_GAP_Addr_T          advAddr;                                /**< Address of the periodic advertiser. See @ref BLE_GAP_Addr_T. */
    uint8_t                 advPhy;                                 /**< PHY on which the advertising packets are received. See @ref BLE_GAP_PHY_TYPE for possible values. */
    uint16_t                periAdvInterval;                        /**< Periodic advertising interval in units of 1.25 ms. */
    uint8_t                 advClkAccuracy;                         /**< Clock accuracy of the advertiser. See @ref BLE_GAP_PERIODIC_ACA for possible values. */
}BLE_GAP_EvtPeriAdvSyncEst_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_PERI_ADV_REPORT event.
 * This event is triggered when a periodic advertising packet is received.
 */
typedef struct BLE_GAP_EvtPeriAdvReport_T
{
    uint16_t                syncHandle;                             /**< Handle identifying the periodic advertising sync. */
    uint8_t                 txPwr;                                  /**< Transmit power of the periodic advertising packet in dBm. */
    int8_t                  rssi;                                   /**< Received Signal Strength Indication for the received packet in dBm. */
    uint8_t                 cteType;                                /**< Constant Tone Extension type of the periodic advertising packet. 
                                                                         See @ref BLE_GAP_CTE_TYPE for possible values. */
    uint8_t                 dataStatus;                             /**< Data status indicating completeness of the periodic advertising data. 
                                                                         See @ref BLE_GAP_DATA_STATUS for possible values. */
    uint8_t                 dataLength;                             /**< Length of the advertising data in bytes. */
    uint8_t                 advData[BLE_GAP_PERIODIC_ADV_FRAGMENT_MAX_LENGTH];    /**< Buffer containing the periodic advertising data. */
}BLE_GAP_EvtPeriAdvReport_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_PERI_ADV_SYNC_LOST event.
 * This event is triggered when synchronization with a periodic advertiser is lost.
 */
typedef struct BLE_GAP_EvtPeriAdvSyncLost_T
{
    uint16_t                syncHandle;                             /**< Handle identifying the periodic advertising sync that was lost. */
}BLE_GAP_EvtPeriAdvSyncLost_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_ADV_SET_TERMINATED event.
 * This event is triggered when an advertising set is terminated.
 */
typedef struct BLE_GAP_EvtAdvSetTerminated_T
{
    uint8_t                 status;                                 /**< Status of the terminated advertising set. See @ref GAP_STATUS for possible values. */
    uint8_t                 advHandle;                              /**< Advertising handle for which advertising has ended. */
    uint16_t                connHandle;                             /**< Connection handle for the connection that was established, causing the advertising to end. */
    uint8_t                 numComplExtAdvEvents;                   /**< Number of completed extended advertising events that were transmitted before termination. */
}BLE_GAP_EvtAdvSetTerminated_T;


/**
 * @brief Structure for the  @ref BLE_GAP_EVT_TRANSMIT_POWER_REPORTING event.
 * This event is triggered when there is a report available regarding transmit power changes.
 */
typedef struct BLE_GAP_EvtTxPowerReporting_T
{
    uint8_t                 status;                                 /**< Status of the transmit power reporting event. See @ref GAP_STATUS for possible values. */
    uint16_t                connHandle;                             /**< Connection handle for the connection related to this transmit power report. */
    uint8_t                 reason;                                 /**< Reason for the transmit power change. See @ref BLE_GAP_TX_POWER_REPORTING_REASON for possible reasons. */
    uint8_t                 phy;                                    /**< PHY type for which the transmit power level is reported. 
                                                                         See @ref BLE_GAP_TRANSMITTER_PHY_TYPE for PHY types. */
    int8_t                  txPowerLevel;                           /**< Current transmit power level for the specified PHY. (Units: dBm) */
    uint8_t                 txPowerLevelFlag;                       /**< Flag indicating if the transmit power level has reached its minimum or maximum level. 
                                                                         See @ref BLE_GAP_TPL_FLAG for possible values. */
    int8_t                  delta;                                  /**< The magnitude of the change in transmit power level being reported. (Units: dB) */
}BLE_GAP_EvtTxPowerReporting_T;


/**
 * @brief Structure for the @ref BLE_GAP_EVT_ADV_COMPL event.
 * This event is triggered when deep sleep advertising is completed.
 */
typedef struct BLE_GAP_EvtAdvCompl_T
{
    uint8_t                 status;                                 /**< Status of the deep sleep advertising completion. See @ref GAP_STATUS for possible values. */
}BLE_GAP_EvtAdvCompl_T;

/**
 * @brief Structure for the  @ref BLE_GAP_EVT_PATH_LOSS_THRESHOLD event.
 * This event is triggered when the path loss between two devices crosses predefined threshold levels.
 */
typedef struct BLE_GAP_EvtPathLossThreshold_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint8_t                 currentPathLoss;                        /**< Current path loss value. This is a measure of signal attenuation. (Units: dB) */
    uint8_t                 zoneEntered;                            /**< Zone entered as a result of the path loss change. See @ref BLE_GAP_PATH_LOSS_ZONE for zone definitions. */
}BLE_GAP_EvtPathLossThreshold_T;

/**
 * @brief Structure for the  @ref BLE_GAP_EVT_FEATURE_EXCHANGE_COMPL event.
 * This event is triggered when feature exchange is completed.
 */
typedef struct BLE_GAP_EvtFeatureExchangeCompl_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
}BLE_GAP_EvtFeatureExchangeCompl_T;

/**
 * @brief Structure for the @ref BLE_GAP_EVT_SUBRATE_CHANGE event.
 * This event is triggered when a Connection Subrate Update procedure has completed 
 * and some parameters of the specified connection have changed.
 */
typedef struct BLE_GAP_EvtSubrateChange_T
{
    uint8_t                 status;                                 /**< Status of the subrate change event. See @ref GAP_STATUS for possible values. */
    uint16_t                connHandle;                             /**< Connection handle for the connection related to this subrate change. */
    uint16_t                subrateFactor;                          /**< New subrate factor applied to the specified underlying connection interval. */
    uint16_t                periLatency;                            /**< New Peripheral latency for the connection in number of subrated connection events. */
    uint16_t                continuationNum;                        /**< Number of underlying connection events to remain active after a packet containing 
                                                                            a PDU with a non-zero Length field is sent or received. */
    uint16_t                supervisionTimeout;                     /**< New supervision timeout for this connection. */
}BLE_GAP_EvtSubrateChange_T;


/** @brief Union of BLE GAP callback event data types. */
typedef union
{
    BLE_GAP_EvtConnect_T                   evtConnect;              /**< Data for @ref BLE_GAP_EVT_CONNECTED event. */
    BLE_GAP_EvtDisconnect_T                evtDisconnect;           /**< Data for @ref BLE_GAP_EVT_DISCONNECTED event. */
    BLE_GAP_EvtConnParamUpdateParams_T     evtConnParamUpdate;      /**< Data for @ref BLE_GAP_EVT_CONN_PARAM_UPDATE event. */
    BLE_GAP_EvtEncryptStatus_T             evtEncryptStatus;        /**< Data for @ref BLE_GAP_EVT_ENCRYPT_STATUS event. */
    BLE_GAP_EvtAdvReport_T                 evtAdvReport;            /**< Data for @ref BLE_GAP_EVT_ADV_REPORT event. */
    BLE_GAP_EvtEncInfoRequest_T            evtEncInfoReq;           /**< Data for @ref BLE_GAP_EVT_ENC_INFO_REQUEST event.*/
    BLE_GAP_EvtRemoteConnParamRequest_T    evtRemoteConnParamReq;   /**< Data for @ref BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST event.*/
    BLE_GAP_EvtExtAdvReport_T              evtExtAdvReport;         /**< Data for @ref BLE_GAP_EVT_EXT_ADV_REPORT event. */
    BLE_GAP_EvtTxBufAvailable_T            evtTxBufAvailable;       /**< Data for @ref BLE_GAP_EVT_TX_BUF_AVAILABLE event. */
    BLE_GAP_EvtDeviceNameChanged_T         evtDevNameChanged;       /**< Data for @ref BLE_GAP_EVT_DEVICE_NAME_CHANGED event. */
    BLE_GAP_EvtAuthPayloadTimeout_T        evtAuthPayloadTimeout;   /**< Data for @ref BLE_GAP_EVT_AUTH_PAYLOAD_TIMEOUT event. */
    BLE_GAP_EvtPhyUpdate_T                 evtPhyUpdate;            /**< Data for @ref BLE_GAP_EVT_PHY_UPDATE event. */
    BLE_GAP_EvtScanReqReceived_T           evtScanReqReceived;      /**< Data for @ref BLE_GAP_EVT_SCAN_REQ_RECEIVED event. */
    BLE_GAP_EvtDirectAdvReport_T           evtDirectAdvReport;      /**< Data for @ref BLE_GAP_EVT_DIRECT_ADV_REPORT event. */
    BLE_GAP_EvtPeriAdvSyncEst_T            evtPeriAdvSyncEst;       /**< Data for @ref BLE_GAP_EVT_PERI_ADV_SYNC_EST event. */
    BLE_GAP_EvtPeriAdvReport_T             evtPeriAdvReport;        /**< Data for @ref BLE_GAP_EVT_PERI_ADV_REPORT event. */
    BLE_GAP_EvtPeriAdvSyncLost_T           evtPeriAdvSyncLost;      /**< Data for @ref BLE_GAP_EVT_PERI_ADV_SYNC_LOST event. */
    BLE_GAP_EvtAdvSetTerminated_T          evtAdvSetTerminated;     /**< Data for @ref BLE_GAP_EVT_ADV_SET_TERMINATED event. */
    BLE_GAP_EvtTxPowerReporting_T          evtTxPowerReporting;     /**< Data for @ref BLE_GAP_EVT_TRANSMIT_POWER_REPORTING event. */
    BLE_GAP_EvtAdvCompl_T                  evtAdvCompl;             /**< Data for @ref BLE_GAP_EVT_ADV_COMPL event. */
    BLE_GAP_EvtPathLossThreshold_T         evtPathLossThreshold;    /**< Data for @ref BLE_GAP_EVT_PATH_LOSS_THRESHOLD event. */
    BLE_GAP_EvtFeatureExchangeCompl_T      evtFeatureExchangeCompl; /**< Data for @ref BLE_GAP_EVT_FEATURE_EXCHANGE_COMPL event. */
    BLE_GAP_EvtSubrateChange_T             evtSubrateChange;        /**< Data for @ref BLE_GAP_EVT_SUBRATE_CHANGE event. */
} BLE_GAP_EventField_T;


/** @brief BLE GAP callback event structure.*/
typedef struct  BLE_GAP_Event_T
{
    BLE_GAP_EventId_T       eventId;                                /**< Identifier for the BLE GAP event. See @ref BLE_GAP_EventId_T. */
    BLE_GAP_EventField_T    eventField;                             /**< Union containing the data payload for the event. See @ref BLE_GAP_EventField_T. */
} BLE_GAP_Event_T;

/**@} */ //BLE_GAP_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup BLE_GAP_FUNS Functions
 * @{
 */
 
/**
 * @brief Initializes the BLE GAP main module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initializes the BLE GAP main module.
 * @retval MBA_RES_FAIL                     Fail to initialize BLE GAP main module.
 */
uint16_t BLE_GAP_Init(void);


/**
 * @brief Initializes the BLE GAP legacy advertising module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initializes the BLE GAP advertising module.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_GAP_AdvInit(void);


/**
 * 
 * @brief Initializes the BLE GAP legacy scan module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initializes the BLE GAP scan module.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_GAP_ScanInit(void);


/**
 * @brief Initializes the BLE GAP extended advertising module.
 * @note  @ref BLE_GAP_AdvInit must be called prior to enabling this module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initializes the BLE GAP extended advertising module.
 */
uint16_t BLE_GAP_ExtAdvInit(void);


/**
 * @brief Initializes the BLE GAP periodic advertising module.
 * @note  Periodic advertising is part of the extended advertising feature. Both @ref BLE_GAP_AdvInit and 
 *          @ref BLE_GAP_ExtAdvInit must be called prior to enabling this module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initializes the BLE GAP periodic advertising module.
 */
uint16_t BLE_GAP_PeriodicAdvInit(void);


/**
 * @brief Initializes the BLE GAP extended scanning module.
 * @note  @ref BLE_GAP_ScanInit must be called prior to enabling this module.
 *
 * @param[in] maxDataLen                    The maximum PDU payload size that the scanner can receive. 
 *                                          See @ref BLE_GAP_EXT_SCAN_DATA_LEN.
 * @param[in] maxNumOfSecPkts               The maximum number of advertising packets on the secondary channel 
 *                                          that the scanner can receive. See @ref BLE_GAP_EXT_SCAN_2ND_ADV_NUM. 
 *                                          A value of 0 adjusts the maximum number automatically.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initializes the BLE GAP extended scanning module.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_GAP_ExtScanInit(uint16_t maxDataLen, uint8_t maxNumOfSecPkts);


/**
 * @brief Initializes the BLE GAP connection peripheral module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initializes the BLE GAP connection peripheral module.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_GAP_ConnPeripheralInit(void);


/**
 * @brief Initializes the BLE GAP connection central module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initializse the BLE GAP connection central module.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_GAP_ConnCentralInit(void);


/**
 * @brief Initializes BLE GAP extended connection central module.
 * @note  @ref BLE_GAP_ConnCentralInit is also required for this module enabling.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initializes the BLE GAP extended connection central module.
 */
uint16_t BLE_GAP_ExtConnCentralInit(void);


/**
 * @brief Initializes BLE GAP sync module, which refers to periodic advertising synchronization.
 * @note  Synchronization is part of the extended advertising feature.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initializes the BLE GAP periodic advertising synchronization module.
 */
uint16_t BLE_GAP_SyncInit(void);


/**
 * @brief Sets the Bluetooth device address (identity address).
 * @note The address type must be either @ref BLE_GAP_ADDR_TYPE_PUBLIC or @ref BLE_GAP_ADDR_TYPE_RANDOM_STATIC. 
 *          The address identifies the device to other Bluetooth devices. The default IRK (Identity Resolving Key) 
 *          is automatically changed if the Bluetooth device address is updated.
 *
 * @param[in] p_addr                        Pointer to the device address buffer. See @ref BLE_GAP_Addr_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets the device address.
 * @retval MBA_RES_FAIL                     Failed to set device address due to invalid address type or other conditions.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_GAP_SetDeviceAddr(BLE_GAP_Addr_T *p_addr);


/**
 * @brief Retrieves the current Bluetooth device address.
 *
 * @param[out] p_addr                       Pointer to the device address buffer. See @ref BLE_GAP_Addr_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully retrieved the device address.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_GAP_GetDeviceAddr(BLE_GAP_Addr_T *p_addr);


/**
 * @brief Sets the local device name.
 *
 * @param[in] len                           Length of the device name. See @ref GAP_MAX_DEVICE_NAME_LEN.
 * @param[in] p_deviceName                  Pointer to a UTF-8 string containing the device name.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets the local device name.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, if the length of the device name exceeds the maximum allowed.
 */
uint16_t BLE_GAP_SetDeviceName(uint8_t len, uint8_t *p_deviceName);


/**
 * @brief Retrieves the local device name along with its length.
 *
 * @param[out] p_len                        Pointer to the length of the device name buffer.
 * @param[out] p_deviceName                 Pointer to the device name buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully retrieves the local device name.
 */
uint16_t BLE_GAP_GetDeviceName(uint8_t *p_len, uint8_t *p_deviceName);


/**
 * @brief Sets advertising data from the input "p_advData".
 * @note  If advertising is currently enabled, the new data will be used in subsequent advertising events. 
 *          If an advertising event is in progress when this command is issued, the new data may not be used 
 *          for that event. This API is part of the legacy advertising feature and will be disallowed if any 
 *          extended advertising feature API has been used prior to this call. See @ref BLE_GAP_ADV_CATS for 
 *          details on advertising APIs. The @ref BLE_GAP_AdvInit function must be called prior to using this API.
 *
 * @param[in] p_advData                     Pointer to the structure containing advertising data to be set. See @ref BLE_GAP_AdvDataParams_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets advertising data.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, if the advertising data length exceeds @ref BLE_GAP_ADV_DATA_LEN.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed when extended advertising feature is in use.
 */
uint16_t BLE_GAP_SetAdvData(BLE_GAP_AdvDataParams_T *p_advData);


/**
 * @brief Sets scan response data.
 * @note  If advertising is currently enabled, the new data will be used in subsequent advertising events. 
 *          If an advertising event is in progress when this command is issued, the new data may not be used 
 *          for that event. This API is part of the legacy advertising feature and will be disallowed if any 
 *          extended advertising feature API has been used prior to this call. See @ref BLE_GAP_ADV_CATS for 
 *          details on advertising APIs. The @ref BLE_GAP_AdvInit function must be called prior to using this API.
 *
 * @param[in] p_scanData                    Pointer to the structure containing scan response data to be set. See @ref BLE_GAP_AdvDataParams_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets scan response data.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters. Scan response data length exceeds @ref BLE_GAP_ADV_DATA_LEN.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed when extended advertising feature is in use.
 */
uint16_t BLE_GAP_SetScanRspData(BLE_GAP_AdvDataParams_T *p_scanData);


/**
 * @brief Sets advertising parameters.
 * @note  This command shall not be issued when advertising is enabled. This API belongs to legacy advertising 
 *          feature. It will be disallowed if any one API belongs extended advertising feature is issued before. 
 *          Refer to @ref BLE_GAP_ADV_CATS for details of advertising APIs. The @ref BLE_GAP_AdvInit function 
 *          must be called prior to using this API.
 *
 * @param[in] p_advParams                   Pointer to advertising parameters buffer. See @ref BLE_GAP_AdvParams_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets advertising parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_GAP_SetAdvParams(BLE_GAP_AdvParams_T *p_advParams);


/**
 * @brief Starts or stop advertising.
 * @note  The duration parameter is only applicable when the advertising type is not set to Directed Advertising. 
 *          Advertising will continue for the specified duration, until stopped by a command, until a connection is 
 *          established, or until it times out due to high duty cycle Directed Advertising. This API is part of the 
 *          legacy advertising feature and will be disallowed if any extended advertising feature API has been used. 
 *          See @ref BLE_GAP_ADV_CATS for details on advertising APIs. The @ref BLE_GAP_AdvInit function must be 
 *          called prior to using this API. The @ref BLE_GAP_SetAdvParams function should be called before this API 
 *          to set the advertising parameters. The @ref BLE_GAP_SetAdvData or @ref BLE_GAP_SetScanRspData function 
 *          should be called before this API to set the advertising or scan response data.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONNECTED is generated when a connection is established.
 * @ref BLE_GAP_EVT_ADV_TIMEOUT is generated when advertising times out.
 *
 * @param[in] enable                        Control flag to start or stop advertising.
 * @param[in] duration                      Duration for advertising in 10 ms units. Set to 0 for continuous advertising.
 *
 * @retval MBA_RES_SUCCESS                  Successfully starts or stops advertising.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed when extended advertising feature is in use.
 */
uint16_t BLE_GAP_SetAdvEnable(bool enable, uint16_t duration);


/**
 * @brief Starts a one-time advertising event.
 * @note This API is part of the legacy advertising feature set. It will be disallowed if any API from the extended 
 *          advertising feature set has been used prior to this call. See @ref BLE_GAP_ADV_CATS for details on advertising APIs. 
 *          The @ref BLE_GAP_AdvInit function must be called prior to using this API. If the option is set to 
 *          BLE_GAP_ADV_OPTION_STORE_PARAMS, the APIs @ref BLE_GAP_SetAdvParams, @ref BLE_GAP_SetAdvData, or @ref BLE_GAP_SetScanRspData 
 *          must be called beforehand to set the appropriate parameters.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_ADV_COMPL is generated when one time advertising event is completed. 
 * If a connection is established, @ref BLE_GAP_EVT_CONNECTED is generated instead of @ref BLE_GAP_EVT_ADV_COMPL.
 *
 * @param[in] option                        Option for one time advertising. See @ref BLE_GAP_ADV_OPTION.
 *
 * @retval MBA_RES_SUCCESS                  Successfully starts advertising.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed when extended advertising feature is in use.
 */
uint16_t BLE_GAP_EnableOneTimeAdv(uint8_t option);


/**
 * @brief Sets data related address changes.
 * @note  This function refreshes the Resolvable Private Address used by the advertising set identified by the advHandle
 *          parameter, whether or not the address timeout period has been reached.
 *          The changeReasons parameter specifies the reason(s) for refreshing addresses.
 *          If any legacy advertising feature API has been used previously, the advHandle parameter is ignored.
 *
 * @param[in] advHandle                     Identifies the advertising set.
 * @param[in] changeReasons                 Indicates when to change the address, see @ref BLE_GAP_EXT_ADV_ADDR_CHG_REASON.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets data related address changes.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetDataRelatedAddrChange(uint8_t advHandle, uint8_t changeReasons);


/**
 * @brief Unlocks BLE data traffic.
 * @note The BLE stack will lock data traffic when @ref BLE_GAP_EnableOneTimeAdv is called and a connection 
 *          is established automatically. The application should call this function to unlock BLE data traffic 
 *          after all necessary BLE modules have been initialized.
 *
 * @retval MBA_RES_SUCCESS                  Successfully unlocks BLE data traffic.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_GAP_TrafficUnlock(void);


/**
 * @brief Terminates an existing connection.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_DISCONNECTED is generated upon disconnection.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] reason                        Disconnection reason. See @ref GAP_STATUS.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issues a disconnection.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             Invalid connection handle.
 */
uint16_t BLE_GAP_Disconnect(uint16_t connHandle, uint8_t reason);


/**
 * @brief Updates connection parameters for an existing connection.
 * @note  This command should only be used after the @ref BLE_GAP_EVT_FEATURE_EXCHANGE_COMPL event has been received.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONN_PARAM_UPDATE is generated when the connection parameters update is complete.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_connParams                  Pointer to the @ref BLE_GAP_ConnParams_T structure containing the new parameters.
 *
 * @retval MBA_RES_SUCCESS                  Successfully updates the connection parameters.
 * @retval MBA_RES_FAIL                     Connection update is in progress.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, or if any of the connection update parameters are out of range
 *                                          (see @ref BLE_GAP_CP_RANGE), or if the connection with the specified handle does not exist.
 * @retval MBA_RES_UNSUPPORT_REMOTE_FEATURE Unsupported remote feature.
 */
uint16_t BLE_GAP_UpdateConnParam(uint16_t connHandle, BLE_GAP_ConnParams_T *p_connParams);


/**
 * @brief Retrieves the absolute Received Signal Strength Indication (RSSI) value in dBm.
 * @note  The RSSI metric represents an absolute receiver signal strength value in dBm.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[out] p_rssi                       Pointer to the buffer where the RSSI value will be stored.
 *
 * @retval MBA_RES_SUCCESS                  Successfully retrieves the RSSI value.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             Connection with the specified handle does not exist.
 */
uint16_t BLE_GAP_GetRssi(uint16_t connHandle, int8_t *p_rssi);


/**
 * @brief Adds devices to the filter accept list.
 * @note  This API is not permitted under the following conditions:\n
 *        - If the advertising filter policy uses the filter accept list and advertising is enabled.\n
 *        - If the scanning filter policy uses the filter accept list and scanning is enabled.\n
 *        - If the initiator filter policy uses the filter accept list and a create connection command is outstanding.\n
 *
 * @param[in] num                           Number of address set. See @ref BLE_GAP_MAX_FILTER_ACCEPT_LIST_NUM.
 * @param[in] p_addr                        Pointer to @ref BLE_GAP_Addr_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully adds the device to the filter accept list.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, such as if the address type does not match any of the @ref BLE_GAP_ADDR_TYPE.
 */
uint16_t BLE_GAP_SetFilterAcceptList(uint8_t num, BLE_GAP_Addr_T *p_addr);


/**
 * @brief Sets devices to the resolving list.
 * @note  This API is not permitted under the following conditions:\n
 *        - If advertising is enabled.\n
 *        - If scanning is enabled.\n
 *        - If a create connection command is outstanding (see @ref BLE_GAP_CreateConnection, @ref BLE_GAP_ExtCreateConnection, or @ref BLE_GAP_CreateSync).\n
 *
 * @param[in] num                           Number of devices to include in the resolving list. See @ref BLE_GAP_MAX_RESOLV_NUM.
 * @param[in] p_resolvingList               Pointer to the @ref BLE_GAP_ResolvingListParams_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully adds the device to the resolving list.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             When the number exceeds @ref BLE_GAP_MAX_RESOLV_NUM.
 * @retval MBA_RES_BAD_STATE                Resolving list cannot be configured while advertising, scanning or creating a connection.
 */
uint16_t BLE_GAP_SetResolvingList(uint8_t num, BLE_GAP_ResolvingListParams_T *p_resolvingList);


/**
 * @brief Retrieves the current local privacy mode setting parameters.
 *
 * @param[out] p_enable                     True if local privacy is enabled, otherwise false.
 * @param[out] p_privacyParams              Pointer to the @ref BLE_GAP_LocalPrivacyParams_T structure to store the current privacy parameters.
 *
 * @retval MBA_RES_SUCCESS                  Successfully retrieves privacy parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_GAP_GetLocalPrivacy(bool * p_enable, BLE_GAP_LocalPrivacyParams_T *p_privacyParams);


/**
 * @brief Configures privacy parameters.
 *
 * @note Local Privacy settings cannot be changed while advertising, scanning, or creating a connection.
 *
 * @param[in] enable                        True to enable local privacy, false to disable it.
 * @param[in] p_privacyParams               Pointer to the @ref BLE_GAP_LocalPrivacyParams_T structure containing the privacy configurations. 
 *                                          If enabling local privacy, the configurations must be valid. 
 *                                          If disabling local privacy, this parameter can be NULL.
 * 
 * @retval MBA_RES_SUCCESS                  Successfully configures privacy parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_BAD_STATE                Privacy parameters cannot be configured while advertising, scanning, or creating a connection.
 */
uint16_t BLE_GAP_SetLocalPrivacy(bool enable, BLE_GAP_LocalPrivacyParams_T *p_privacyParams);


/**
 * @brief Sets the scanning parameters.
 * @note  This API should not be called while scanning is active. It is part of the legacy advertising feature set 
 *          and will be disallowed if any API from the extended advertising feature set has been used previously. 
 *          See @ref BLE_GAP_ADV_CATS for details on advertising APIs. The @ref BLE_GAP_ScanInit function must be 
 *          called prior to using this API.
 *
 * @param[in] p_scanParams                  Pointer to a @ref BLE_GAP_ScanningParams_T structure containing the desired scanning parameters.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets scanning parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, such as out-of-range scanning parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed when the extended advertising feature is in use.
 */
uint16_t BLE_GAP_SetScanningParam(BLE_GAP_ScanningParams_T *p_scanParams);


/**
 * @brief Starts or stops scanning for advertising devices.
 * @note  Scanning is used to discover nearby advertising devices. If scanning is already active, setting 
 *          the enable parameter to true will update the filterDuplicate setting. This API is part of the legacy 
 *          advertising feature set and will be disallowed if any API from the extended advertising feature set 
 *          has been used previously. See @ref BLE_GAP_ADV_CATS for details on advertising APIs. The 
 *          @ref BLE_GAP_ScanInit function must be called prior to using this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_ADV_REPORT is generated when scan is enabled.
 * @ref BLE_GAP_EVT_DIRECT_ADV_REPORT is generated when scanning is enabled and a direct advertisement is received.
 * @ref BLE_GAP_EVT_SCAN_TIMEOUT is generated when scanning is enabled and times out.
 *
 * @param[in] enable                        Start (true) or stop (false) scanning.
 * @param[in] filterDuplicate               Duplicate filtering policy, see @ref BLE_GAP_SCAN_FD. 
 *                                          Valid values are BLE_GAP_SCAN_FD_DISABLE and BLE_GAP_SCAN_FD_ENABLE.
 * @param[in] mode                          Scan mode, see @ref BLE_GAP_SCAN_MODES.
 * @param[in] duration                      Scan duration in units of 100 ms.
 *
 * @retval MBA_RES_SUCCESS                  Successfully starts or stop scanning.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, such as out-of-range values.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed when the extended advertising feature is in use.
 */
uint16_t BLE_GAP_SetScanningEnable(bool enable, uint8_t filterDuplicate, uint8_t mode, uint16_t duration);


/**
 * @brief Initiates a BLE connection to a connectable advertiser.
 * @note  This API is part of the legacy advertising feature set and will be disallowed if any extended 
 *          advertising feature API has been used prior to this call. See @ref BLE_GAP_ADV_CATS for advertising 
 *          API details. Initialization with @ref BLE_GAP_ConnCentralInit is required before using this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONNECTED is generated when the connection is established.
 *
 * @param[in] p_createConnParam             Pointer to the structure containing connection parameters. 
 *                                          See @ref BLE_GAP_CreateConnParams_T for details.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initiates a BLE connection with the specified device.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, if any of the connection parameters are out of range. 
 *                                          Refer to @ref BLE_GAP_CreateConnParams_T for parameter ranges.
 * @retval MBA_RES_NO_RESOURCE              Exceeded the maximum number of concurrent connections.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_CreateConnection(BLE_GAP_CreateConnParams_T *p_createConnParam);


/**
 * @brief Cancels the ongoing BLE connection creation process.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONNECTED is generated with a corresponding status code when the cancellation is complete.
 *
 * @retval MBA_RES_SUCCESS                  Successfully cancel the ongoing connection creation process.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_CreateConnectionCancel(void);


/**
 * @brief Initiates a BLE connection using the extended advertising feature set.
 * @note  This API is part of the extended advertising feature set and will be disallowed if any legacy 
 *          advertising feature API has been used prior to this call. See @ref BLE_GAP_ADV_CATS for advertising 
 *          API details. Initialization with both @ref BLE_GAP_ConnCentralInit and @ref BLE_GAP_ExtConnCentralInit 
 *          is required before using this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONNECTED is generated when the connection is established.
 *
 * @param[in] filterPolicy                  Determines whether the filter accept list is used. See @ref BLE_GAP_INIT_FP for details.
 * @param[in] p_peerAddr                    Pointer to the structure containing the remote Bluetooth address and address type. See @ref BLE_GAP_Addr_T.
 * @param[in] p_createConnPhy               Pointer to the structure containing the connection PHY parameters. See @ref BLE_GAP_ExtCreateConnPhy_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initiates the create connection process.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_ExtCreateConnection(uint8_t filterPolicy, BLE_GAP_Addr_T *p_peerAddr, BLE_GAP_ExtCreateConnPhy_T *p_createConnPhy);


/**
 * @brief Sets local channel map.
 * @note  If not called, the status of all 37 channels defaults to unknown. The application should call this API within 
 *          10 seconds of determining that the channel classification has changed. There should be at least a one-second 
 *          interval between successive calls. The BLE stack uses this channel map along with its own assessment. This API 
 *          is only effective in the Central role.
 *
 * @param[in] p_map                         5-byte channel map array with 37 1-bit fields corresponding to the 37 data channels. 
 *                                          A '0' indicates a bad channel, and a '1' indicates an unknown channel status.
 *                                          The most significant bits are reserved and must be set to 0.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets the channel map.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, such as setting bits corresponding to advertising 
 *                                          channels (3 most significant bits of p_map[4]).
 */
uint16_t BLE_GAP_SetChannelMap(uint8_t *p_map);


/**
 * @brief Retrieves the channel map for the specific connection.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[out] p_map                        5-byte channel map array with 37 1-bit fields corresponding to the 37 data channels. 
 *                                          A '0' indicates a bad channel, and a '1' indicates an unknown channel status.The most
 *                                          significant bits are reserved and must be set to 0.
 *
 * @retval MBA_RES_SUCCESS                  Successfully retrieves the channel map.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_UNKNOWN_CONN_ID          Unknown connection identifier.
 */
uint16_t BLE_GAP_ReadChannelMap(uint16_t connHandle, uint8_t *p_map);


/**
 * @brief Responds negatively to an LE encryption information request event.
 * @note  This API should only be called in response to a @ref BLE_GAP_EVT_ENC_INFO_REQUEST 
 *        event and only if the device is in the peripheral role.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_ENCRYPT_STATUS is generated when encrypted status is updated.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issues a negative response to the LE encryption information request event.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 */
uint16_t BLE_GAP_EncInfoReqNegativeReply(uint16_t connHandle);


/**
 * @brief Responds to an LE encryption information request event.
 * @note  This API should only be called in response to a @ref BLE_GAP_EVT_ENC_INFO_REQUEST event 
 *          and only if the device is in the peripheral role.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_ENCRYPT_STATUS is generated when the encryption status is updated.
 * @ref BLE_GAP_EVT_DISCONNECTED is generated if the provided encryption information is incorrect and leads to a disconnection.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_ltk                         Pointer to the 128-bit Long Term Key (LTK) used for encryption.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issues a reply to the encryption information request event.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_EncInfoReqReply(uint16_t connHandle, uint8_t *p_ltk);


/**
 * @brief Replies to an LE remote connection parameters request event if the device accepts the 
 *          remote device's request to change connection parameters.
 * @note  This API is called in response to the @ref BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST event.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONN_PARAM_UPDATE is generated when the connection parameters update is complete.
 * 
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_connParams                  Pointer to the desired connection parameters. See @ref BLE_GAP_ConnParams_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issues a reply to the LE remote connection parameters request event.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_RemoteConnParamsReqReply(uint16_t connHandle,  BLE_GAP_ConnParams_T *p_connParams);


/**
 * @brief Replies to an LE remote connection parameters request event if the device rejects the 
 *          remote device's request to change connection parameters.
 * @note  This API is called in response to the @ref BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST event.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] reason                        The reason for rejecting the remote connection parameter request. See @ref GAP_STATUS.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issues a negative reply to the LE remote connection parameters request event.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_RemoteConnParamsReqNegativeReply(uint16_t connHandle, uint8_t reason);


/**
 * @brief Authenticates and encrypts the connection using the provided encryption key.
 * @note  This command should only be used when the local device's role is Central.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_ENCRYPT_STATUS is generated  when the encryption status is updated.
 * @ref BLE_GAP_EVT_DISCONNECTED is generated if encryption fails.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_random                      Pointer to a 64-bit random number.
 * @param[in] p_ediv                        Pointer to a 16-bit encrypted diversifier.
 * @param[in] p_ltk                         Pointer to a 128-bit long-term key (LTK).
 *
 * @retval MBA_RES_SUCCESS                  Successfully starts the encryption process.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_EnableEncryption(uint16_t connHandle, uint8_t *p_random, uint8_t *p_ediv, uint8_t *p_ltk);


/**
 * @brief Sets the RF Tx power level for Advertising physical channel PDUs.
 * @note  Advertising physical channel PDUs encompass advertising, scanning, and initiating PDUs. 
 *          This setting can be overridden for a specific Advertising handle by using @ref BLE_GAP_SetExtAdvParams. 
 *          It is recommended to call this function during application initialization.
 *
 * @param[in] advTxPower                    The desired advertising transmit power level.
 * @param[out] p_selectedTxPower            Pointer to the actual transmit power level set. (Unit: dBm)
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets the transmit power level.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
*/
uint16_t BLE_GAP_SetAdvTxPowerLevel(int8_t advTxPower, int8_t *p_selectedTxPower);


/**
 * @brief Sets the RF Tx power level for LE connection Data physical channel PDUs before LE 
 *          power control is activated.
 * @note  If both connected devices support the LE Power Control feature, the RF Tx power level 
 *          will be adjusted by the BLE stack automatically.
 *
 * @param[in] connTxPower                   The transmit power level to be used after connection and before LE power control activation.
 * @param[out] p_selectedTxPower            Pointer to the actual transmit power level set. (Unit: dBm)
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets the transmit power level.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
*/
uint16_t BLE_GAP_SetConnTxPowerLevel(int8_t connTxPower, int8_t *p_selectedTxPower);


/**
 * @brief Reads the current and maximum transmit power levels for a specific LE connection handle. (Unit: dBm)
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] phy                           The PHY for which to read the power levels. See @ref BLE_GAP_TRANSMITTER_PHY_TYPE.
 * @param[out] p_txPower                    Pointer to the current transmit power level. (Unit: dBm)
 * @param[out] p_txPowerMax                 Pointer to the maximum transmit power level. (Unit: dBm)
 *
 * @retval MBA_RES_SUCCESS                  Successfully retrieves the transmit power level.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_ReadTxPowerLevel(uint16_t connHandle, uint8_t phy, int8_t *p_txPower, int8_t *p_txPowerMax);


/**
 * @brief Requests the transmit power level used by the remote device on a specific connection.
 * @note  This command should only be used after receiving the @ref BLE_GAP_EVT_FEATURE_EXCHANGE_COMPL event.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_TRANSMIT_POWER_REPORTING is generated to provide Tx power level information.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] phy                           The PHY for which to request the power level. See @ref BLE_GAP_TRANSMITTER_PHY_TYPE.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issues the request for the remote device's transmit power level.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_ReadRemoteTxPowerLevel(uint16_t connHandle, uint8_t phy);


/**
 * @brief Reads the maximum and minimum factory RF transmit power levels. (Unit: dBm)
 *
 * @param[out] p_minTxPower                 Pointer to the minimum transmit power level. (Unit: dBm)
 * @param[out] p_maxTxPower                 Pointer to the maximum transmit power level. (Unit: dBm)
 *
 * @retval MBA_RES_SUCCESS                  Successfully retrieves the factory transmit power levels.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_GAP_ReadFactoryTxPowerLevel(int8_t *p_minTxPower, int8_t *p_maxTxPower);


/**
 * @brief Sets the golden receive power range.
 *
 * @param[out] upperLimit                   The upper limit of the golden range, not to exceed -50dBm. (Unit: dBm)
 * @param[out] lowerLimit                   The lower limit of the golden range, not to be less than -80dBm. (Unit: dBm)
 * @param[out] stepDecreasePower            The maximum decrement in power for each step. (Unit: dBm)
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets the golden receive power range.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 */
uint16_t BLE_GAP_SetGoldenRxPowerRange(int8_t upperLimit, int8_t lowerLimit, uint8_t stepDecreasePower);


/**
 * @brief Enables or disables reporting of transmit power level changes for a specific connection.
 * @note  This command should be used only after the @ref BLE_GAP_EVT_FEATURE_EXCHANGE_COMPL event has been received.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] localEnable                   Enable (true) or disable (false) local transmit power reports.
 * @param[in] remoteEnable                  Enable (true) or disable (false) remote transmit power reports.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issues the request.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_SetTxPowerReportingEnable(uint16_t connHandle, bool localEnable, bool remoteEnable);


/**
 * @brief Configures the extended advertising parameters.
 * @note  This API is part of the extended advertising feature and is disallowed if any legacy advertising 
 *          feature API has been used prior. See @ref BLE_GAP_ADV_CATS for advertising API details. Initialization 
 *          with @ref BLE_GAP_AdvInit or @ref BLE_GAP_ExtAdvInit is required before calling this API. When using 
 *          coded PHY, the default coding scheme is S=8 (S: Transmitted Symbols). Use @ref BLE_GAP_SetExtAdvCodingScheme 
 *          to change the coding scheme.\n
 * 
 *      If legacy advertising PDU types are being used and the advertising set already contains data, the type shall 
 *      be one that supports advertising data, and the amount of data shall not exceed 31 bytes.\n
 *          If extended advertising PDU types are being used, then:\n
 *          - High duty cycle directed connectable advertising shall not be used (bit 3 = 0).
 *
 * @param[in] p_extAdvParams                Pointer to the structure containing extended advertising parameters. See @ref BLE_GAP_ExtAdvParams_T.
 * @param[out] p_selectedTxPower            Pointer to the variable where the selected transmit power level will be stored. (Unit: dBm)
 *
 * @retval MBA_RES_SUCCESS                  Successfully configures the extended advertising parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_SetExtAdvParams(BLE_GAP_ExtAdvParams_T *p_extAdvParams, int8_t *p_selectedTxPower);


/**
 * @brief Sets the preferred PHY coding scheme for extended advertising.
 * @note  This function configures the coding scheme used for the PHY layer in extended advertising. 
 *          There are two possible coding schemes based on the number of transmitted symbols: S=2 or S=8. 
 *          Before using this function, initialize the advertising module with @ref BLE_GAP_AdvInit or @ref BLE_GAP_ExtAdvInit.
 *
 * @param[in] codingScheme                  The coding scheme for advertising PDUs: 0 for S=8 coding, 1 for S=2 coding.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets the extended advertising coding scheme.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Operation disallowed if advertising is not initialized.
 */
uint16_t BLE_GAP_SetExtAdvCodingScheme(uint8_t codingScheme);


/**
 * @brief Configures extended advertising data.
 * @note  This API can be called at any time after creating an advertising set with @ref BLE_GAP_SetExtAdvParams, 
 *          regardless of whether advertising is enabled or disabled. This API is part of the extended advertising 
 *          feature and is disallowed if any legacy advertising feature API has been used prior. Initialization 
 *          with @ref BLE_GAP_AdvInit or @ref BLE_GAP_ExtAdvInit is required before calling this API.
 *
 * @param[in] p_advDataParam                Pointer to the structure containing extended advertising data parameters. See @ref BLE_GAP_ExtAdvDataParams_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully configures extended advertising data.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetExtAdvData(BLE_GAP_ExtAdvDataParams_T *p_advDataParam);


/**
 * @brief Configures extended scan response data for an advertising set.
 * @note  This function sets the scan response data associated with an advertising set created by @ref BLE_GAP_SetExtAdvParams. 
 *          It can be called at any time, regardless of whether advertising for the set is currently enabled or disabled. This 
 *          function is part of the extended advertising feature and cannot be used if legacy advertising APIs have been used. 
 *          See @ref BLE_GAP_ADV_CATS for a categorization of advertising APIs. Initialization with @ref BLE_GAP_AdvInit and 
 *          @ref BLE_GAP_ExtAdvInit is required before calling this function.
 *
 * @param[in] p_scanDataParam               Pointer to a @ref BLE_GAP_ExtAdvDataParams_T structure containing the scan response data.
 *
 * @retval MBA_RES_SUCCESS                  Successfully configures extended scan response data.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetExtScanRspData(BLE_GAP_ExtAdvDataParams_T *p_scanDataParam);


/**
 * @brief Enables or disables one or more advertising sets.
 * @note  If enable is set to false and numOfSets is 0x00, then all advertising sets are disabled. Advertising 
 *          will be disabled after the maximum number of extended advertising events have been sent, even if the 
 *          set duration has not expired. For more details, see @ref BLE_GAP_ExtAdvEnableParams_T. This API is part 
 *          of the extended advertising feature and is incompatible with legacy advertising APIs. See @ref BLE_GAP_ADV_CATS 
 *          for details on advertising APIs. Initialization with @ref BLE_GAP_AdvInit and @ref BLE_GAP_ExtAdvInit is 
 *          required before calling this API. Set the advertising parameters with @ref BLE_GAP_SetExtAdvParams before 
 *          calling this API. Set the advertising and scan response data with @ref BLE_GAP_SetExtAdvData and 
 *          @ref BLE_GAP_SetExtScanRspData before calling this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONNECTED is generated when when connectable advertising starts and a connection is established.
 * @ref BLE_GAP_EVT_SCAN_REQ_RECEIVED is generated when extended advertising is enabled.
 * @ref BLE_GAP_EVT_ADV_SET_TERMINATED is generated when extended advertising is enabled and times out.
 *
 * @param[in] enable                        Enable (true) or disable (false) one or more advertising sets.
 * @param[in] numOfSets                     The number of advertising sets to be enabled or disabled.
 * @param[in] p_advParam                    Pointer to a @ref BLE_GAP_ExtAdvEnableParams_T structure containing the enable parameters.
 *
 * @retval MBA_RES_SUCCESS                  Successfully enables or disables the advertising sets.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetExtAdvEnable(bool enable, uint8_t numOfSets, BLE_GAP_ExtAdvEnableParams_T *p_advParam);


/**
 * @brief Starts a one-time extended advertising event.
 * @note This API is part of the extended advertising feature set. It will be disallowed if any API from the legacy 
 *          advertising feature set has been used prior to this call. See @ref BLE_GAP_ADV_CATS for details on advertising APIs. 
 *          Initialization with @ref BLE_GAP_AdvInit or @ref BLE_GAP_ExtAdvInit is required before calling this API. If the option is set to 
 *          BLE_GAP_ADV_OPTION_STORE_PARAMS, the APIs @ref BLE_GAP_SetExtAdvParams, @ref BLE_GAP_SetExtAdvData, or @ref BLE_GAP_SetExtScanRspData 
 *          must be called beforehand to set the appropriate parameters. The combined advertising or scanRsp data length must not be over 230 bytes.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_ADV_COMPL is generated when one time extended advertising event is completed. 
 * If a connection is established, @ref BLE_GAP_EVT_CONNECTED is generated instead of @ref BLE_GAP_EVT_ADV_COMPL.
 *
 * @param[in] option                        Option for one time advertising. See @ref BLE_GAP_ADV_OPTION.
 * @param[in] advHandle                     The advertising handle identifying the advertising set to be enabled.
 *
 * @retval MBA_RES_SUCCESS                  Successfully starts advertising.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed when extended advertising feature is in use.
 */
uint16_t BLE_GAP_EnableOneTimeExtAdv(uint8_t option, uint8_t advHandle);

/**
 * @brief Removes an advertising set.
 * @note  This API is part of the extended advertising feature and is incompatible with legacy advertising APIs. 
 *          See @ref BLE_GAP_ADV_CATS for details on advertising APIs. 
 *          Initialization with @ref BLE_GAP_AdvInit and @ref BLE_GAP_ExtAdvInit is required before calling this API.
 *
 * @param[in] advHandle                     The advertising handle identifying the advertising set to be removed.
 *
 * @retval MBA_RES_SUCCESS                  Successfully removes an advertising set.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_RemoveExtAdvSet(uint8_t advHandle);


/**
 * @brief Removes all existing advertising sets.
 * @note  This API is part of the extended advertising feature. It is disallowed if any legacy advertising feature 
 *          API has been issued prior to this call. See @ref BLE_GAP_ADV_CATS for details on advertising APIs. Initialization 
 *          with @ref BLE_GAP_AdvInit and @ref BLE_GAP_ExtAdvInit is required before using this API.
 *
 * @retval MBA_RES_SUCCESS                  Successfully removes all advertising sets.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_ClearExtAdvSet(void);


/**
 * @brief Retrieves the advertising address used in advertising events for a given advertising handle.
 *
 * @param[in] advHandle                     The advertising handle. Use value 0xF0 to retrieve the address of legacy advertising.
 * @param[in] p_addr                        Pointer to a @ref BLE_GAP_Addr_T structure to store the advertiser's Bluetooth 
 *                                          address and address type.
 *
 * @retval MBA_RES_SUCCESS                  Successfully retrieves the advertisier advertising address.
 * @retval MBA_RES_FAIL                     Anonymous advertisement; no address available.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_GetAdvAddr(uint8_t advHandle, BLE_GAP_Addr_T *p_addr);


/**
 * @brief Configures periodic advertising parameters.
 * @note  This API can be called at any time and is part of the extended advertising feature. It is disallowed 
 *          if any legacy advertising feature API has been issued prior to this call. See @ref BLE_GAP_ADV_CATS 
 *          for details on advertising APIs. Initialization with @ref BLE_GAP_AdvInit, @ref BLE_GAP_ExtAdvInit, 
 *          and @ref BLE_GAP_PeriodicAdvInit is required before using this API. If periodic advertising is currently 
 *          enabled for the specified advertising set, the new data will be used in subsequent periodic advertising 
 *          events. If a periodic advertising event is in progress when this command is issued, either the old or new 
 *          data may be used for that event.
 * 
 * @param[in] p_periAdvParams               Pointer to a @ref BLE_GAP_PeriAdvParams_T structure containing the periodic advertising parameters.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets periodic advertising parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetPeriAdvParams(BLE_GAP_PeriAdvParams_T *p_periAdvParams);


/**
 * @brief Sets periodic advertising data.
 * @note  This API can be called at any time. If periodic advertising is enabled for the specified advertising set, 
 *          the new data will be used in subsequent periodic advertising events. If a periodic advertising event is 
 *          in progress when this command is issued, either the old or new data may be used for that event. This API 
 *          is part of the extended advertising feature and is disallowed if any legacy advertising feature API has 
 *          been used previously. See @ref BLE_GAP_ADV_CATS for details on advertising APIs. Initialization with 
 *          @ref BLE_GAP_AdvInit, @ref BLE_GAP_ExtAdvInit, and @ref BLE_GAP_PeriodicAdvInit is required before using this API.
 *
 * @param[in] p_advDataParam                Pointer to a @ref BLE_GAP_PeriAdvDataParams_T structure containing the advertising data.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets periodic advertising data.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetPeriAdvData(BLE_GAP_PeriAdvDataParams_T *p_advDataParam);


/**
 * @brief Enables or disables periodic advertising for a specified advertising set.
 * @note  If the advertising set is not currently enabled (see @ref BLE_GAP_SetExtAdvEnable), periodic advertising 
 *          will not start until the advertising set is enabled. Periodic advertising continues until this API is 
 *          called with 'enable' set to false. This API is part of the extended advertising feature and is disallowed 
 *          if any legacy advertising feature API has been used previously. See @ref BLE_GAP_ADV_CATS for details on 
 *          advertising APIs. Initialization with @ref BLE_GAP_AdvInit, @ref BLE_GAP_ExtAdvInit, and @ref BLE_GAP_PeriodicAdvInit 
 *          is required before using this API.
 *
 * @param[in] enable                        Set @ref BLE_GAP_PA_ENABLE_OPTION to enable periodic advertising; otherwise, set it to 0.
 * @param[in] advHandle                     Advertising set identifier to enable or disable periodic advertising for.
 *
 * @retval MBA_RES_SUCCESS                  Successfully enables or disables the periodic advertising.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetPeriAdvEnable(uint8_t enable, uint8_t advHandle);


/**
 * @brief Sets the extended scan parameters for advertising physical channels.
 * @note  This API is part of the extended advertising feature and is disallowed if any legacy advertising feature API has 
 *          been used previously. See @ref BLE_GAP_ADV_CATS for details on advertising APIs. Initialization with 
 *          @ref BLE_GAP_ScanInit and @ref BLE_GAP_ExtScanInit is required before using this API.
 *
 * @param[in] filterPolicy                  Scanning filter policy. Refer to @ref BLE_GAP_SCAN_FP for possible values.
 * @param[in] p_extScanPhy                  Pointer to a @ref BLE_GAP_ExtScanningPhy_T structure containing the scan parameters.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets the extended scan parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_SetExtScanningParams(uint8_t filterPolicy, BLE_GAP_ExtScanningPhy_T *p_extScanPhy);


/**
 * @brief Enables or disables extended scanning.
 * @note  If scanning is already enabled and this API is called with 'enable' set to true, the scan duration 
 *          and period timers are reset to the new values, and a new scan period begins. The scan period duration 
 *          includes time spent scanning on both primary and secondary advertising channels. When an advertising 
 *          packet or scan response is received, the @ref BLE_GAP_EVT_EXT_ADV_REPORT event is generated. This API 
 *          is part of the extended advertising feature and is disallowed if any legacy advertising feature API has 
 *          been used previously. See @ref BLE_GAP_ADV_CATS for details on advertising APIs. Initialization with 
 *          @ref BLE_GAP_ScanInit and @ref BLE_GAP_ExtScanInit is required before using this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_EXT_ADV_REPORT is generated when an advertising packet or scan response is received during extended scanning.
 * @ref BLE_GAP_EVT_SCAN_TIMEOUT is generated when the scan period ends due to reaching the specified duration.
 *
 * @param[in] mode                          Scan mode. Refer to @ref BLE_GAP_SCAN_MODES for possible values.
 * @param[in] p_enable                      Pointer to a @ref BLE_GAP_ExtScanningEnable_T structure specifying scan enable parameters.
 *
 *
 * @retval MBA_RES_SUCCESS                  Successfully enables or disables extended scanning.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_SetExtScanningEnable(uint8_t mode, BLE_GAP_ExtScanningEnable_T *p_enable);


/**
 * @brief Sets the PHY preferences for the specified connection.
 * @note  The BLE Stack might not be able to make the change immediately. An event will be generated 
 *          if one or both PHYs change.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_PHY_UPDATE is generated when the PHY is updated.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] txPhys                        Transmitter PHYs. A bit field that indicates the preferred transmitter PHYs.
 *                                          Refer to @ref BLE_GAP_PHY_OPTION for possible values.
 * @param[in] rxPhys                        Receiver PHYs. A bit field that indicates the preferred receiver PHYs.
 *                                          Refer to @ref BLE_GAP_PHY_OPTION for possible values.
 * @param[in] phyOptions                    PHY options. Refer to @ref BLE_GAP_PHY_PREF for possible values.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets the PHY preferences for the specified connection.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_UNKNOWN_CONN_ID          Unknown connection identifier.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_SetPhy(uint16_t connHandle, uint8_t txPhys, uint8_t rxPhys, uint8_t phyOptions);


/**
 * @brief Reads the current transmitter PHY and receiver PHY on the specified connection.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_txPhy                       Pointer to a buffer where the current transmitter PHY will be stored.
 *                                          Refer to @ref BLE_GAP_PHY_TYPE for possible PHY types.
 * @param[in] p_rxPhy                       Pointer to a buffer where the current receiver PHY will be stored.
 *                                          Refer to @ref BLE_GAP_PHY_TYPE for possible PHY types.
 *
 *
 * @retval MBA_RES_SUCCESS                  Successfully reads the current transmitter and receiver PHY.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_UNKNOWN_CONN_ID          Unknown connection identifier.
 */
uint16_t BLE_GAP_ReadPhy(uint16_t connHandle, uint8_t *p_txPhy, uint8_t *p_rxPhy);


/**
 * @brief Specifies the preferred values for the transmitter PHY and receiver PHY to be used for all subsequent connections.
 *
 * @param[in] txPhys                        Transmitter PHYs. Indicates the preferred transmitter PHYs.
 *                                          Refer to @ref BLE_GAP_PHY_OPTION for possible values.
 * @param[in] rxPhys                        Receiver PHYs. Indicates the preferred receiver PHYs.
 *                                          Refer to @ref BLE_GAP_PHY_OPTION for possible values.
 *
 * @retval MBA_RES_SUCCESS                  Successfully specifies the preferred PHY values for future connections.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 */
uint16_t BLE_GAP_SetDefaultPhy(uint8_t txPhys, uint8_t rxPhys);


/**
 * @brief Reads the authenticated payload timeout value for a BLE connection.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[out] p_authPayloadTo              Pointer to store the authenticated payload timeout value (Unit: 10ms).
 *
 * @retval MBA_RES_SUCCESS                  Successfully reads the authenticated payload timeout value.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_UNKNOWN_CONN_ID          Unknown connection identifier.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_ReadAuthPayloadTimeout(uint16_t connHandle, uint16_t *p_authPayloadTo);


/**
 * @brief Sets the authenticated payload timeout parameter for a BLE connection.
 * @note  This configuration determines when the LE ping sequence should be initiated to maintain a 
 *          secure connection. The timeout value must be chosen considering the connection interval and 
 *          peripheral latency.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] authPayloadTo                 Authenticated payload timeout value (Unit: 10 ms).
 *                                          The value must be equal to or greater than connInterval*(1 + peripheralLatency).
 *                                          See @ref BLE_GAP_EvtConnect_T for more details.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets the authenticated payload timeout value.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_UNKNOWN_CONN_ID          Unknown connection identifier.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_WriteAuthPayloadTimeout(uint16_t connHandle, uint16_t authPayloadTo);


/**
 * @brief Configures the built-in Generic Access Service for a BLE device.
 * @note  This function allows customization of optional characteristics and values within the mandatory 
 *          Generic Access Service. It is recommended to call this function during initialization and not 
 *          when a connection is active. Once configured, the options should not be changed; if multiple 
 *          configurations are required, consider the implications of service changes.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_DEVICE_NAME_CHANGED is generated when the device name characteristic is writable and is written by a remote peer.
 *
 * @param[in] p_serviceOptions              Pointer to a structure defining the service options to be configured. See @ref BLE_GAP_ServiceOption_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully configures the built-in Generic Access Service.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_GAP_ConfigureBuildInService(BLE_GAP_ServiceOption_T *p_serviceOptions);


/**
 * @brief Synchronizes with a periodic advertising train from an advertiser and begin receiving 
 *          periodic advertising packets.
 * @note  This API can be called regardless of the current scanning state. Scanning can be enabled 
 *        or disabled while this command is pending. However, synchronization can only occur when 
 *        scanning is enabled. Refer to @ref BLE_GAP_SetExtScanningEnable for more information.
 *        This API is part of the extended advertising feature set and is not compatible with legacy 
 *        advertising APIs. See @ref BLE_GAP_ADV_CATS for details. Initialization with @ref BLE_GAP_ScanInit, 
 *        @ref BLE_GAP_ExtScanInit, and @ref BLE_GAP_SyncInit is required before using this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_PERI_ADV_SYNC_EST is generated when synchronization is established.
 * @ref BLE_GAP_EVT_PERI_ADV_REPORT is generated when a periodic advertising report is received.
 *
 * @param[in] p_periSync                    Pointer to a @ref BLE_GAP_CreateSync_T structure containing synchronization parameters.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issues a request to synchronize with a periodic advertising train.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_CONN_ALREADY_EXISTS      Connection already exists.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_CreateSync(BLE_GAP_CreateSync_T *p_periSync);


/**
 * @brief Cancels the synchronization process initiated by @ref BLE_GAP_CreateSync while it is pending.
 * @note  This API is part of the extended advertising feature set and is not compatible with legacy 
 *          advertising APIs. See @ref BLE_GAP_ADV_CATS for details. Initialization with @ref BLE_GAP_ScanInit, 
 *          @ref BLE_GAP_ExtScanInit, and @ref BLE_GAP_SyncInit is required before using this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_PERI_ADV_SYNC_EST is generated with a corresponding status code when the cancellation is processed.
 *
 * @retval MBA_RES_SUCCESS                  Successfully cancels the synchronization process.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_CreateSyncCancel(void);


/**
 * @brief Stops reception of the periodic advertising train identified by the provided syncHandle.
 * @note  This API is part of the extended advertising feature set and is not compatible with legacy 
 *          advertising APIs. See @ref BLE_GAP_ADV_CATS for details. Initialization with @ref BLE_GAP_ScanInit, 
 *          @ref BLE_GAP_ExtScanInit, and @ref BLE_GAP_SyncInit is required before using this API.
 *
 * @param[in] syncHandle                    Identity of the periodic advertising train. Range: 0x0000 to 0x0EFF.
 *
 * @retval MBA_RES_SUCCESS                  Successfully stops reception of the periodic advertising train.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_TerminateSync(uint16_t syncHandle);


/**
 * @brief Adds one or more devices to the Periodic Advertiser list.
 * @note  This function sets one or multiple entries in the Periodic Advertiser list, which is used 
 *          for synchronization with periodic advertising.
 *
 * @param[in] num                           Number of devices to be added to the list. Must not exceed @ref BLE_GAP_MAX_DEV_NUM.
 * @param[in] p_syncSetDev                  Pointer to an array of @ref BLE_GAP_SyncSetDev_T structures containing the devices to be added.
 * 
 * @retval MBA_RES_SUCCESS                  Successfully adds the devices to the Periodic Advertiser list.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 */
uint16_t BLE_GAP_SetDevToPeriAdvList(uint8_t num, BLE_GAP_SyncSetDev_T *p_syncSetDev);


/**
 * @brief Enables or disables reports for the periodic advertising train identified by the "syncHandle".
 * @note  This API is part of the extended advertising feature set and is incompatible with legacy 
 *          advertising APIs. See @ref BLE_GAP_ADV_CATS for details on advertising APIs. Initialization 
 *          with @ref BLE_GAP_ScanInit, @ref BLE_GAP_ExtScanInit, and @ref BLE_GAP_SyncInit is required 
 *          before using this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_PERI_ADV_REPORT is generated when reporting is enabled.
 *
 * @param[in] syncHandle                    Identity of the periodic advertising train.
 * @param[in] enable                        Set @ref BLE_GAP_PA_ENABLE_RX_OPTION to enable reporting; otherwise, set it to 0.
 *
 * @retval MBA_RES_SUCCESS                  Successfully enables or disables for the periodic advertising train.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetPeriAdvRxEnable(uint16_t syncHandle, uint8_t enable);


/**
 * @brief Sets the scanning filter parameters to filter received advertising or scan response PDUs based on specific data types.
 * @note  There are three Advertising Data Type (AD_Type) content filter options that can be enabled individually:\n
 *          - Name Filter: Filters by Shortened Local Name (AD_Type=0x08) or Complete Local Name (AD_Type=0x09).\n
 *          - Service Data Filter: Filters by Service Data (AD_Type=0x16).\n
 *          - Manufacturer Data Filter: Filters by Manufacturer Specific Data (AD_Type=0xFF).\n
 *      When enabled, PDUs with matching AD_Type data are reported via @ref BLE_GAP_EVT_ADV_REPORT or @ref BLE_GAP_EVT_EXT_ADV_REPORT 
 *      events. This scanning filter is applied after the filterPolicy setting in the @ref BLE_GAP_SetScanningParam 
 *      or @ref BLE_GAP_SetExtScanningParams API.
 *
 * @param[in] p_param                       Pointer to a @ref BLE_GAP_ScanFilterConfig_T structure containing the filter configuration.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets the scanning filter parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 */
uint16_t BLE_GAP_SetScanningFilter(BLE_GAP_ScanFilterConfig_T *p_param);


/**
 * @brief Sets the path loss threshold reporting parameters for a specific connection.
 * @note  This command should be used only after the @ref BLE_GAP_EVT_FEATURE_EXCHANGE_COMPL event has been received.
 *
 * @param[in] p_params                      Pointer to a @ref BLE_GAP_PathLossReportingParams_T structure containing the reporting parameters.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets the path loss threshold reporting parameters for specific connection.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 */
uint16_t BLE_GAP_SetPathLossReportingParams(BLE_GAP_PathLossReportingParams_T *p_params);


/**
 * @brief Enables or disables path loss reporting for a specific connection.
 * @note  This command should be used only after the @ref BLE_GAP_EVT_FEATURE_EXCHANGE_COMPL event has been received.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] enable                        Set to true to enable path loss reporting, or false to disable it.
 *
 * @retval MBA_RES_SUCCESS                  Successfully enables or disables Channel number calculated as (F - 2402) / 2, 
 *                                          where F is the frequency in MHz ranging from 2402 to 2480 MHz. path loss reporting
 *                                          for specific connection.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_SetPathLossReportingEnable(uint16_t connHandle, bool enable);


/**
 * @brief Sets the initial values for the acceptable parameters for subrating requests.
 * @note  This command should be used only after the @ref BLE_GAP_EVT_FEATURE_EXCHANGE_COMPL event has been received.
 *          The following conditions will result in an MBA_RES_INVALID_PARA response:\n
 *          - Subrate Max x (Max Latency + 1) is greater than 500.\n
 *          - Current connection interval x Subrate Max x (Max Latency + 1) is greater than or equal to half the 
 *              Supervision Timeout parameter.\n
 *          - Subrate Max is less than Subrate Min.\n
 *          - Continuation Number is greater than or equal to Subrate Max.\n
 *
 * @param[in] p_subrateParams               Pointer to a @ref BLE_GAP_SubrateParams_T structure containing the subrate parameters.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sets the initial values for the acceptable parameters for subrating requests.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 */
uint16_t BLE_GAP_SetDefaultSubrate(BLE_GAP_SubrateParams_T  *p_subrateParams);


/**
 * @brief Request a change to the subrating factor and/or other parameters.
 * @note  This command should be used only after the @ref BLE_GAP_EVT_FEATURE_EXCHANGE_COMPL event has been received.
 *          The following conditions will result in an MBA_RES_INVALID_PARA response:\n
 *          - Subrate Max x (Max Latency + 1) is greater than 500.\n
 *          - Current connection interval x Subrate Max x (Max Latency + 1) is greater than or equal to half the 
 *              Supervision Timeout parameter.\n
 *          - Subrate Max is less than Subrate Min.\n
 *          - Continuation Number is greater than or equal to Subrate Max.\n
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_subrateParams               Pointer to a @ref BLE_GAP_SubrateParams_T structure containing the subrate parameters.
 *
 * @retval MBA_RES_SUCCESS                  Successfully request a change to the subrating factor and/or other parameters.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed due to a conflicting operation or state.
 */
uint16_t BLE_GAP_SubrateRequest(uint16_t connHandle, BLE_GAP_SubrateParams_T  *p_subrateParams);


/**
 * @brief Reads AFH channel assessment mode.
 *
 * @param[out] p_enable                     Pointer to a bool containing true if the mode is enabled, otherwise false.
 *
 * @retval MBA_RES_SUCCESS                  Successfully read the mode.
 * @retval MBA_RES_FAIL                     The mode is not supported.
 * @retval MBA_RES_INVALID_PARA             The parameters provided are invalid.
 */
uint16_t BLE_GAP_ReadAfhChannelAssessMode(bool *p_enable);


/**
 * @brief Writes AFH channel assessment mode.
 *
 * @param[in] enable                        Set to true to enable the mode, or false to disable it.
 *
 * @retval MBA_RES_SUCCESS                  Successfully write the mode.
 * @retval MBA_RES_FAIL                     The mode is not supported.
 */
uint16_t BLE_GAP_WriteAfhChannelAssessMode(bool enable);


/** @} */ //BLE_GAP_FUNS

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif//BLE_GAP_H
