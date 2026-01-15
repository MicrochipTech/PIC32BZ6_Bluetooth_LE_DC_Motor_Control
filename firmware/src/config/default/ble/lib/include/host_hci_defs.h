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
  Host HCI Definitions Header File

  Company:
    Microchip Technology Inc.

  File Name:
    host_hci_defs.h

  Summary:
    Defines HCI (Host Controller Interface) constants and parameters used by the
    host side of a Bluetooth stack.

  Description:
    This header file specifies HCI commands, events, and data structures that
    facilitate communication between the host layer and the Bluetooth controller.
 *******************************************************************************/


#ifndef HOST_HCI_DEFS_H
#define HOST_HCI_DEFS_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/** 
 * @defgroup HOST_HCI HOST HCI
 * @brief Definitions for the Bluetooth Host Controller Interface (HCI).
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**
 * @addtogroup HOST_HCI_DEFINES Defines
 * @{
 */


/**
 * @defgroup HCI_BD_ADDRESS_LEN Bluetooth Device Address length
 * @brief Defines the length of a Bluetooth Device Address.
 * @{
 */
#define HCI_BD_ADDRESS_LEN                                  (0x06U)        /**< Length of a Bluetooth Device Address in bytes. */
/** @} */


/**
 * @defgroup HCI_ADV_DEFS Advertising definitions
 * @brief Defines parameters related to Bluetooth advertising.
 * @{
 */
#define HCI_MAX_ADV_LENGTH                                  (0x1FU)        /**< Maximum length of advertising data in bytes. */
#define HCI_MAX_ADV_REPORTS                                 (0x01U)        /**< Maximum number of advertising reports in a single HCI_EvtLeAdvReport_T event. 
                                                                                The specification defines a maximum of 0x19. */
/** @} */


/**
 * @defgroup HCI_KEY_LEN Maximum key length
 * @brief Defines the maximum length of encryption keys.
 * @{
 */
#define HCI_MAX_KEY_LENGTH                                  (0x10U)        /**< Maximum length of an encryption key in bytes. */
/** @} */


/**
 * @defgroup HCI_MAX_EXT_ADV_SET Maximum number of extended advertising sets
 * @brief Defines the maximum number of extended advertising sets.
 * @{
 */
#define HCI_MAX_EXTENDED_ADVERTISING_SETS                   (0x3FU)        /**< Maximum number of extended advertising sets as per the HCI_LE_SET_EXT_ADV_ENABLE command. */
/** @} */


/**
 * @defgroup HCI_MAX_EXT_ADV_DATA_LEN Maximum length of extended advertising data
 * @brief Defines the maximum length of extended advertising data.
 * @{
 */
#define HCI_CMD_MAX_EXTENDED_ADVERTISING_DATA_LENGTH        (0xFBU)        /**< Maximum length of extended advertising data for the HCI_LE_SET_EXT_ADV_DATA command. */
#define HCI_EVT_MAX_EXTENDED_ADVERTISING_DATA_LENGTH        (0xE5U)        /**< Maximum length of extended advertising data for the HCI_LE_EXTENDED_ADVERTISING_REPORT event. */
/** @} */


/**
 * @defgroup HCI_MAX_PADV_DATA_LEN Maximum length of periodic advertising data
 * @brief Defines the maximum length of periodic advertising data.
 * @{
 */
#define HCI_CMD_MAX_PERIODIC_ADVERTISING_DATA_LENGTH        (0xFCU)        /**< Maximum length of periodic advertising data for the HCI_LE_SET_PA_DATA command. */
#define HCI_EVT_MAX_PERIODIC_ADVERTISING_DATA_LENGTH        (0xF7U)        /**< Maximum length of periodic advertising data for the HCI_LE_PA_REPORT event. */
/** @} */


/**
 * @defgroup HCI_EXT_SCAN_PHY_NUM Number of supported PHYs in LE extended scan
 * @brief Defines the number of supported PHYs for LE extended scanning.
 * @{
 */
#define HCI_SUPPORTED_EXT_SCAN_PHYS                         (0x02U)        /**< Number of PHYs supported for LE extended scanning as defined in the HCI_LE_SET_EXTENDED_SCAN_PARAM command. */
/** @} */


/**
 * @defgroup HCI_EXT_CREATE_CONN_PHY_NUM Number of supported PHYs in LE extended create connection
 * @brief Defines the number of supported PHYs for LE extended create connection.
 * @{
 */
#define HCI_SUPPORTED_EXT_CREATE_CONNECTION_PHYS            (0x03U)        /**< Number of PHYs supported for LE extended create connection as defined in the HCI_LE_SET_EXTENDED_CREATE_CONNECTION command. */


/**
 * @defgroup HCI_MAX_CONN_NUM Maximum number of allowed connections
 * @brief Defines the maximum number of allowed connections.
 * @{
 */
#define HCI_MAX_NUM_CONN_HANDLE                             (0x08U)        /**< Maximum number of connections allowed. */
/** @} */


/**
 * @defgroup HCI_FEATURES_LENGTH Length of the bit mask list of supported features
 * @brief Defines the length of the bit mask list for supported features.
 * @{
 */
#define HCI_FEATURES_BITMASK_LENGTH                         (0x08U)        /**< Length of the bit mask list for supported features. */
/** @} */


/**
 * @defgroup HCI_LTK_RAND_SIZE Size of the random number used in encryption with LTK
 * @brief Defines the size of the random number used when encrypting with LTK.
 * @{
 */
#define HCI_LTK_RANDOM_SIZE                                 (0x08U)        /**< Size of the random number (in octets) used in encryption with LTK. */
/** @} */


/**
 * @defgroup HCI_LE_TRANSMITTER_SPL_RANGE Range of Switching Pattern Length for LE Transmitter
 * @brief Defines the range of Switching Pattern Length for the LE Transmitter.
 * @{
 */
#define HCI_LE_TRANSMITTER_SPL_MIN                          (0x02U)        /**< Minimum value of Switching Pattern Length for the LE Transmitter. */
#define HCI_LE_TRANSMITTER_SPL_MAX                          (0x4BU)        /**< Maximum value of Switching Pattern Length for the LE Transmitter. */
/** @} */


/**
 * @defgroup HCI_PHY_OPTION LE PHY options
 * @brief Defines the options for LE PHYs.
 * @{
 */
#define HCI_PHY_OPTION_1M                                   (1U << 0U)    /**< Option for LE 1M PHY. */
#define HCI_PHY_OPTION_2M                                   (1U << 1U)    /**< Option for LE 2M PHY. */
#define HCI_PHY_OPTION_CODED                                (1U << 2U)    /**< Option for LE Coded PHY. */
/** @} */


/**
 * @defgroup HCI_OGF HCI opcode group field
 * @brief Defines the HCI opcode group field
 * @{
 */
#define HCI_LC                                              (0x01U)        /**< Link Control Commands. */
#define HCI_LP                                              (0x02U)        /**< Link Policy Commands. */
#define HCI_HC                                              (0x03U)        /**< Host Controller and Baseband Commands. */
#define HCI_IP                                              (0x04U)        /**< Informational Parameters Commands. */
#define HCI_SP                                              (0x05U)        /**< Status Parameters Commands. */
#define HCI_TC                                              (0x06U)        /**< Testing Commands. */
#define HCI_LE_CTRL                                         (0x08U)        /**< LE Controller Commands. */
#define MANUFACTURER_SPEC                                   (0x3FU)        /**< Manufacturer-Specific Commands. */
/** @} */


/**
 * @defgroup HCI_OCF_LC HCI opcode command field for Link Control
 * @brief Defines the command field for the Link Control group.
 * @{
 */
#define HCI_DISCONNECT                                      (0x06U)         /**< Disconnect Command. */
/** @} */


/**
 * @defgroup HCI_OCF_HC HCI opcode command field for Host Controller and Baseband
 * @brief Defines the command field for the Host Controller and Baseband group.
 * @{
 */
#define HCI_READ_AFH_CHANNEL_ASSESS_MODE                    (0x48U)        /**< Read AFH Channel Assessment Mode Command. */
#define HCI_WRITE_AFH_CHANNEL_ASSESS_MODE                   (0x49U)        /**< Write AFH Channel Assessment Mode Command. */
#define HCI_READ_AUTHENTICATED_PAYLOAD_TIMEOUT              (0x7BU)        /**< Read Authenticated Payload Timeout Command. */
#define HCI_WRITE_AUTHENTICATED_PAYLOAD_TIMEOUT             (0x7CU)        /**< Write Authenticated Payload Timeout Command. */
/** @} */


/**
 * @defgroup HCI_OCF_IP HCI opcode command Field for Informational Parameters
 * @brief Defines the command field for the Informational Parameters group.
 * @{
 */
#define HCI_READ_BD_ADDR                                    (0x09U)        /**< Read Blluetooth device address Command. */
/** @} */


/**
 * @defgroup HCI_OCF_SP HCI opcode command Field for Status Parameters
 * @brief Defines the command field for the Status Parameters group.
 * @{
 */
#define HCI_READ_RSSI                                       (0x05U)         /**< Read RSSI Command. */
/** @} */


/**
 * @defgroup HCI_OCF_LE HCI opcode command field for LE Controller
 * @brief Defines the command field for the LE Controller group.
 * @{
 */
#define HCI_LE_SET_RANDOM_ADDRESS                           (0x05U)        /**< LE Set Random Address command. */
#define HCI_LE_SET_ADVERTISING_PARAMS                       (0x06U)        /**< LE Set Advertising Parameters command. */
#define HCI_LE_SET_ADVERTISING_DATA                         (0x08U)        /**< LE Set Advertising Data command. */
#define HCI_LE_SET_SCAN_RESPONSE_DATA                       (0x09U)        /**< LE Set Scan Response Data command. */
#define HCI_LE_SET_ADVERTISING_ENABLE                       (0x0AU)        /**< LE Set Advertising Enable command. */
#define HCI_LE_SET_SCAN_PARAMS                              (0x0BU)        /**< LE Set Scan Parameters command. */
#define HCI_LE_SET_SCAN_ENABLE                              (0x0CU)        /**< LE Set Scan Enable command. */
#define HCI_LE_CREATE_CONNECTION                            (0x0DU)        /**< LE Create Connection command. */
#define HCI_LE_CREATE_CONNECTION_CANCEL                     (0x0EU)        /**< LE Create Connection Cancel command. */
#define HCI_LE_CLEAR_FILTER_ACCEPT_LIST                     (0x10U)        /**< LE Clear Filter Accept List command. */
#define HCI_LE_ADD_DEVICE_TO_FILTER_ACCEPT_LIST             (0x11U)        /**< LE Add Device To Filter Accept List command. */
#define HCI_LE_CONNECTION_UPDATE                            (0x13U)        /**< LE Connection Update command. */
#define HCI_LE_SET_HOST_CHANNEL_CLASSIFICATION              (0x14U)        /**< LE Set Host Channel Classification command. */
#define HCI_LE_READ_CHANNEL_MAP                             (0x15U)        /**< LE Read Channel Map command. */
#define HCI_LE_READ_REMOTE_FEATURES                         (0X16U)        /**< LE Read Remote Features command. */
#define HCI_LE_ENABLE_ENCRYPTION                            (0x19U)        /**< LE Enable Encryption command. */
#define HCI_LE_LONG_TERM_KEY_REQ_REPLY                      (0x1AU)        /**< LE Long Term Key Request Reply command. */
#define HCI_LE_LONG_TERM_KEY_REQ_NEGATIVE_REPLY             (0x1BU)        /**< LE Long Term Key Request Negative Reply command. */
#define HCI_LE_RECEIVER_TEST_V1                             (0x1DU)        /**< LE Receiver Test command (version 1). */
#define HCI_LE_TRANSMITTER_TEST_V1                          (0x1EU)        /**< LE Transmitter Test command (version 1). */
#define HCI_LE_TEST_END                                     (0x1FU)        /**< LE Test End command. */
#define HCI_LE_REMOTE_CONN_PARAM_REQ_REPLY                  (0x20U)        /**< LE Remote Connection Parameter Request Reply command. */
#define HCI_LE_REMOTE_CONN_PARAM_REQ_NEGATIVE_REPLY         (0x21U)        /**< LE Remote Connection Parameter Request Negative Reply command. */
#define HCI_LE_SET_DATA_LENGTH                              (0x22U)        /**< LE Set Data Length command. */
#define HCI_LE_ADD_DEVICE_TO_RESOLVING_LIST                 (0x27U)        /**< LE Add Device To Resolving List command. */
#define HCI_LE_CLEAR_RESOLVING_LIST                         (0x29U)        /**< LE Clear Resolving List command. */
#define HCI_LE_SET_ADDR_RESOLUTION_ENABLE                   (0x2DU)        /**< LE Set Address Resolution Enable command. */
#define HCI_LE_SET_RPA_TIMEOUT                              (0x2EU)        /**< LE Set Resolvable Private Address Timeout. */
#define HCI_LE_READ_PHY                                     (0x30U)        /**< LE Read PHY command. */
#define HCI_LE_SET_DEFAULT_PHY                              (0x31U)        /**< LE Set Default PHY command. */
#define HCI_LE_SET_PHY                                      (0x32U)        /**< LE Set PHY command. */
#define HCI_LE_RECEIVER_TEST_V2                             (0x33U)        /**< LE Receiver Test command (version 2). */
#define HCI_LE_TRANSMITTER_TEST_V2                          (0x34U)        /**< LE Transmitter Test command (version 2). */
#define HCI_LE_SET_ADVERTISING_SET_RANDOM_ADDR              (0x35U)        /**< LE Set Advertising Set Random Address command.  */
#define HCI_LE_SET_EXT_ADV_PARAM                            (0x36U)        /**< LE Set Extended Advertising Parameters command. */
#define HCI_LE_SET_EXT_ADV_DATA                             (0x37U)        /**< LE Set Extended Advertising Data command. */
#define HCI_LE_SET_EXTENDED_SCAN_RSP_DATA                   (0x38U)        /**< LE Set Extended Scan Response Data command. */
#define HCI_LE_SET_EXT_ADV_ENABLE                           (0x39U)        /**< LE Set Extended Advertising Enable command. */
#define HCI_LE_REMOVE_ADVERTISING_SET                       (0x3CU)        /**< LE Remove Advertising Set command. */
#define HCI_LE_CLEAR_ADVERTISING_SETS                       (0x3DU)        /**< LE Clear Advertising Sets command. */
#define HCI_LE_SET_PA_PARAM                                 (0x3EU)        /**< LE Set Periodic Advertising Parameters command. */
#define HCI_LE_SET_PA_DATA                                  (0x3FU)        /**< LE Set Periodic Advertising Data command. */
#define HCI_LE_SET_PA_ENABLE                                (0x40U)        /**< LE Set Periodic Advertising Enable command. */
#define HCI_LE_SET_EXTENDED_SCAN_PARAM                      (0x41U)        /**< LE Set Extended Scan Parameters command. */
#define HCI_LE_SET_EXTENDED_SCAN_ENABLE                     (0x42U)        /**< LE Set Extended Scan Enable command. */
#define HCI_LE_EXTENDED_CREATE_CONNECTION                   (0x43U)        /**< LE Extended Create Connection command. */
#define HCI_LE_PA_CREATE_SYNC                               (0x44U)        /**< LE Periodic Advertising Create Sync command. */
#define HCI_LE_PA_CREATE_SYNC_CANCEL                        (0x45U)        /**< LE Periodic Advertising Create Sync Cancel command. */
#define HCI_LE_PA_TERMINATE_SYNC                            (0x46U)        /**< LE Periodic Advertising Terminate Sync command. */
#define HCI_LE_ADD_DEV_TO_PERIODIC_ADVERTISER_LIST          (0x47U)        /**< LE Add Device To Periodic Advertiser List command. */
#define HCI_LE_CLEAR_PERIODIC_ADVERTISER_LIST               (0x49U)        /**< LE Clear Periodic Advertiser List command. */
#define HCI_LE_READ_TRANSMIT_POWER                          (0x4BU)        /**< LE Read Transmit Power command. */
#define HCI_LE_SET_PRIVACY_MODE                             (0x4EU)        /**< LE Set Privacy Mode command. */
#define HCI_LE_RECEIVER_TEST_V3                             (0x4FU)        /**< LE Receiver Test command (version 3). */
#define HCI_LE_TRANSMITTER_TEST_V3                          (0x50U)        /**< LE Transmitter Test command (version 3). */
#define HCI_LE_SET_PA_RECEIVE_ENABLE                        (0x59U)        /**< LE Set Periodic Advertising Reveive Enable command. */
#define HCI_LE_ENHANCED_READ_TRANSMIT_POWER_LEVEL           (0x76U)        /**< LE Enhanced Read Transmit Power Level command. */
#define HCI_LE_READ_REMOTE_TRANSMIT_POWER_LEVEL             (0x77U)        /**< LE Read Remote Transmit Power Level command. */
#define HCI_LE_SET_PLR_PARAMS                               (0x78U)        /**< LE Set Path Loss Reporting Parameters command. */
#define HCI_LE_SET_PLR_ENABLE                               (0x79U)        /**< LE Set Path Loss Reporting Enable command. */
#define HCI_LE_SET_TRANSMIT_POWER_REPORTING_ENABLE          (0x7AU)        /**< LE Set Transmit Power Reporting Enable command. */
#define HCI_LE_TRANSMITTER_TEST_V4                          (0x7BU)        /**< LE Transmitter Test command (version 4). */
#define HCI_LE_SET_DATA_REL_ADDR_CHG                        (0x7CU)        /**< LE_Set Data Related Address Changes command. */
#define HCI_LE_SET_DEFAULT_SUBRATE                          (0x7DU)        /**< LE Set Default Subrate command. */
#define HCI_LE_SET_HOST_FEATURE                             (0x74U)        /**< LE Set Host Feature command. */
#define HCI_LE_SUBRATE_REQUEST                              (0x7EU)        /**< LE Subrate Request command. */
/** @} */


/**
 * @defgroup HCI_EVT_CODE HCI event codes
 * @brief Defines the HCI event codes. 
 * @{
 */
#define HCI_DISCONNECTION_COMPLETE                          (0x05U)        /**< Event for Disconnection Complete. */
#define HCI_ENCRYPTION_CHANGE                               (0x08U)        /**< Event for Encryption Change. */
#define HCI_READ_REMOTE_VERSION_INFORMATION_COMPLETE        (0x0CU)        /**< Event for Read Remote Version Information Complete. */
#define HCI_COMMAND_COMPLETE                                (0x0EU)        /**< Event for Command Complete. */
#define HCI_COMMAND_STATUS                                  (0x0FU)        /**< Event for Command Status. */
#define HCI_NBR_OF_COMPLETED_PACKETS                        (0x13U)        /**< Event for Number Of Completed Packets. */
#define HCI_ENCRYPTION_KEY_REFRESH_COMPLETE                 (0x30U)        /**< Event for Encryption Key Refresh Complete. */
#define HCI_LE_META_EVENT                                   (0x3EU)        /**< Event for LE Meta. */
#define HCI_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED           (0x57U)        /**< Event for Authenticated Payload Timeout Expired. */
/** @} */


/**
 * @defgroup HCI_LE_META_SUB_EVT_CODE HCI LE Meta subevent codes
 * @brief Defines the subevent codes within the HCI LE Meta event.
 * @{
 */
#define HCI_LE_CONNECT_COMPLETE                             (0x01U)        /**< Subevent for LE Connection Complete. */
#define HCI_LE_ADVERTISING_REPORT                           (0x02U)        /**< Subevent for LE Advertising Report. */
#define HCI_LE_CONNECTION_UPDATE_COMPLETE                   (0x03U)        /**< Subevent for LE Connection Update Complete. */
#define HCI_LE_READ_REMOTE_FEATURES_COMPLETE                (0x04U)        /**< Subevent for LE Read Remote Features Complete. */
#define HCI_LE_LONG_TERM_KEY_REQUEST                        (0x05U)        /**< Subevent for LE Long Term Key Request. */
#define HCI_LE_REMOTE_CONNECTION_PARAMETER_REQUEST          (0x06U)        /**< Subevent for LE Remote Connection Parameter Request. */
#define HCI_LE_DATA_LENGTH_CHANGE                           (0x07U)        /**< Subevent for LE Data Length Change. */
#define HCI_LE_ENHANCED_CONNECTION_COMPLETE                 (0x0AU)        /**< Subevent for LE Enhanced Connection Complete. */
#define HCI_LE_DIRECT_ADVERTISING_REPORT                    (0x0BU)        /**< Subevent for LE Directed Advertising Report. */
#define HCI_LE_PHY_UPDATE_COMPLETE                          (0x0CU)        /**< Subevent for LE PHY Update Complete. */
#define HCI_LE_EXTENDED_ADVERTISING_REPORT                  (0x0DU)        /**< Subevent for LE Extended Advertising Report. */
#define HCI_LE_PA_SYNC_ESTABLISHED                          (0x0EU)        /**< Subevent for LE Periodic Advertising Sync Established. */
#define HCI_LE_PA_REPORT                                    (0x0FU)        /**< Subevent for LE Periodic Advertising Report. */
#define HCI_LE_PA_SYNC_LOST                                 (0x10U)        /**< Subevent for LE Periodic Advertising Sync Lost. */
#define HCI_LE_SCAN_TIMEOUT                                 (0x11U)        /**< Subevent for LE Scan Timeout. */
#define HCI_LE_ADVERTISING_SET_TERMINATED                   (0x12U)        /**< Subevent for LE Advertising Set Terminated. */
#define HCI_LE_SCAN_REQUEST_RECEIVED                        (0x13U)        /**< Subevent for LE Scan Request Received. */
#define HCI_LE_CHANNEL_SELECTION_ALGORITHM                  (0x14U)        /**< Subevent for LE Channel Selection Algorithm. */
#define HCI_LE_PATH_LOSS_THRESHOLD                          (0x20U)        /**< Subevent for LE Path Loss Threshold. */
#define HCI_LE_TRANSMIT_POWER_REPORTING                     (0x21U)        /**< Subevent for LE Transmit Power Reporting. */
#define HCI_LE_SUBRATE_CHANGE                               (0x3EU)        /**< Subevent for LE Subrate Change. */
/** @} */


/**
 * @defgroup HCI_CMD_SIZE Pre-defined size of HCI command packet
 * @brief Defines the size of parameters of each HCI command packet.
 * @{
 */
#define HCI_CMD_SIZE_DISCONNECT                             (0x03U)        /**< Size for HCI Disconnect command. See @ref HCI_Disconnect_T. */
#define HCI_CMD_SIZE_READ_AFH_CHAN_ASSESS_MODE              (0x00U)        /**< Size for HCI Read AFH Channel Assessment Mode command. No parameters required. */
#define HCI_CMD_SIZE_WRITE_AFH_CHAN_ASSESS_MODE             (0x01U)        /**< Size for HCI Write AFH Channel Assessment Mode command. See @ref HCI_WriteAfhChannelAssessMode_T. */
#define HCI_CMD_SIZE_READ_AUTH_PAYLOAD_TO                   (0x02U)        /**< Size for HCI Read Authenticated Payload Timeout command. See @ref HCI_ReadAuthenticatedPayloadTimeout_T. */
#define HCI_CMD_SIZE_WRITE_AUTH_PAYLOAD_TO                  (0x04U)        /**< Size for HCI Write Authenticated Payload Timeout command. See @ref HCI_WriteAuthenticatedPayloadTimeout_T. */
#define HCI_CMD_SIZE_READ_BD_ADDR                           (0x00U)        /**< Size for HCI Read BD_ADDR command. No parameters required. */
#define HCI_CMD_SIZE_READ_RSSI                              (0x02U)        /**< Size for HCI Read RSSI command. See @ref HCI_ReadRssi_T. */
#define HCI_CMD_SIZE_SET_RANDOM_ADDR                        (0x06U)        /**< Size for HCI LE Set Random Address command. See @ref HCI_LE_SetRandomAddress_T. */
#define HCI_CMD_SIZE_SET_ADV_PARAMS                         (0x0FU)        /**< Size for HCI LE Set Advertising Parameters command. See @ref HCI_LE_SetAdvertisingParameters_T. */
#define HCI_CMD_SIZE_SET_ADV_DATA                           (0x20U)        /**< Size for HCI LE Set Advertising Data command. See @ref HCI_LE_SetAdvertisingData_T. */
#define HCI_CMD_SIZE_SET_SCAN_RSP_DATA                      (0x20U)        /**< Size for HCI LE Set Scan Response Data command. See @ref HCI_LE_SetScanResponseData_T. */
#define HCI_CMD_SIZE_SET_ADV_ENABLE                         (0x01U)        /**< Size for HCI LE Set Advertising Enable command. See @ref HCI_LE_SetAdvertisingEnable_T. */
#define HCI_CMD_SIZE_SET_SCAN_PARAMS                        (0x07U)        /**< Size for HCI LE Set Scan Parameters command. See @ref HCI_LE_SetScanParameters_T. */
#define HCI_CMD_SIZE_SET_SCAN_ENABLE                        (0x02U)        /**< Size for HCI LE Set Scan Enable command. See @ref HCI_LE_SetScanEnable_T. */
#define HCI_CMD_SIZE_CREATE_CONN                            (0x19U)        /**< Size for HCI LE Create Connection command. See @ref HCI_LE_CreateConnection_T. */
#define HCI_CMD_SIZE_CREATE_CONN_CANCEL                     (0x00U)        /**< Size for HCI LE Create Connection Cancel command. No parameters required. */
#define HCI_CMD_SIZE_CLEAR_FILTER_ACCEPT_LIST               (0x00U)        /**< Size for HCI LE Clear Filter Accept List command. No parameters required. */
#define HCI_CMD_SIZE_ADD_DEV_TO_FILTER_ACCEPT_LIST          (0x07U)        /**< Size for HCI LE Add Device To Filter Accept List command. See @ref HCI_LE_AddDeviceToFilterAcceptList_T. */
#define HCI_CMD_SIZE_CONN_UPDATE                            (0x0EU)        /**< Size for HCI LE Connection Update command. See @ref HCI_LE_ConnectionUpdate_T. */
#define HCI_CMD_SIZE_SET_HOST_CHANNEL_CLASSIFY              (0x05U)        /**< Size for HCI LE Set Host Channel Classification command. Consists of 37 1-bit fields (5 octets). */
#define HCI_CMD_SIZE_READ_CHANNEL_MAP                       (0x02U)        /**< Size for HCI LE Read Channel Map command. See @ref HCI_LE_ReadChannelMap_T. */
#define HCI_CMD_SIZE_READ_REMOTE_FEATURES                   (0x02U)        /**< Size for HCI LE Read Remote Features command. See @ref HCI_LE_ReadRemoteFeatures_T. */
#define HCI_CMD_SIZE_ENABLE_ENCRYPTION                      (0x1CU)        /**< Size for HCI LE Enable Encryption command. See @ref HCI_LE_EnableEncryption_T. */
#define HCI_CMD_SIZE_LTK_REQ_REPLY                          (0x12U)        /**< Size for HCI LE Long Term Key Request Reply command. See @ref HCI_LE_LongTermKeyRequestReply_T. */
#define HCI_CMD_SIZE_LTK_REQ_NEG_REPLY                      (0x02U)        /**< Size for HCI LE Long Term Key Request Negative Reply command. See @ref HCI_LE_LongTermKeyRequestNegativeReply_T. */
#define HCI_CMD_SIZE_RECEIVER_TEST_V1                       (0x01U)        /**< Size for HCI LE Receiver Test V1 command. See @ref HCI_LE_ReceiverTestV1_T. */
#define HCI_CMD_SIZE_TX_TEST_V1                             (0x03U)        /**< Size for HCI LE Transmitter Test V1 command. See @ref HCI_LE_TransmitterTestV1_T. */
#define HCI_CMD_SIZE_TEST_END                               (0x00U)        /**< Size for HCI Test End command. No parameters required. */
#define HCI_CMD_SIZE_REMOTE_CP_REQ_REPLY                    (0x0EU)        /**< Size for HCI LE Remote Connection Parameter Request Reply command. See @ref HCI_LE_RemoteConnParamReqReply_T. */
#define HCI_CMD_SIZE_REMOTE_CP_REQ_NEG_REPLY                (0x03U)        /**< Size for HCI LE Remote Connection Parameter Request Negative Reply command. See @ref HCI_LE_RemoteConnParamReqNegReply_T. */
#define HCI_CMD_SIZE_SET_DATA_LENGTH                        (0x06U)        /**< Size for HCI LE Set Data Length command. See @ref HCI_LE_SetDataLength_T. */
#define HCI_CMD_SIZE_ADD_DEV_TO_RES_LIST                    (0x27U)        /**< Size for HCI LE Add Device To Resolving List command. See @ref HCI_LE_AddDeviceToResolvingList_T. */
#define HCI_CMD_SIZE_CLEAR_RES_LIST                         (0x00U)        /**< Size for HCI LE Clear Resolving List command. No parameters required. */
#define HCI_CMD_SIZE_SET_ADDR_RES_ENABLE                    (0x01U)        /**< Size for HCI LE Set Address Resolution Enable command. See @ref HCI_LE_SetAddressResolutionEnable_T. */
#define HCI_CMD_SIZE_SET_RPA_TIMEOUT                        (0x02U)        /**< Size for HCI LE Set RPA Timeout command. See @ref HCI_LE_SetRpaTimeout_T. */
#define HCI_CMD_SIZE_READ_PHY                               (0x02U)        /**< Size for HCI LE Read PHY command. See @ref HCI_LE_ReadPhy_T. */
#define HCI_CMD_SIZE_SET_DEFAULT_PHY                        (0x03U)        /**< Size for HCI LE Set Default PHY command. See @ref HCI_LE_SetDefaultPhy_T. */
#define HCI_CMD_SIZE_SET_PHY                                (0x07U)        /**< Size for HCI LE Set PHY command. See @ref HCI_LE_SetPhy_T. */
#define HCI_CMD_SIZE_RECEIVER_TEST_V2                       (0x03U)        /**< Size for HCI LE Receiver Test V2 command. See @ref HCI_LE_ReceiverTestV2_T. */
#define HCI_CMD_SIZE_TX_TEST_V2                             (0x04U)        /**< Size for HCI LE Transmitter Test V2 command. See @ref HCI_LE_TransmitterTestV2_T. */
#define HCI_CMD_SIZE_SET_ADV_SET_RANDOM_ADDR                (0x07U)        /**< Size for HCI LE Set Advertising Set Random Address command. See @ref HCI_LE_SetAdvertisingSetRandomAddr_T. */
#define HCI_CMD_SIZE_SET_EXT_ADV_PARAMS                     (0x1BU)        /**< Size for HCI LE Set Extended Advertising Parameters command. See @ref HCI_LE_SetExtAdvertisingParameters_T. */
#define HCI_CMD_SIZE_SET_EXT_ADV_DATA                       (0xFFU)        /**< Size for HCI LE Set Extended Advertising Data command. See @ref HCI_LE_SetExtAdvertisingData_T. */
#define HCI_CMD_SIZE_SET_EXT_SCAN_RSP_DATA                  (0xFFU)        /**< Size for HCI LE Set Extended Scan Response Data command. See @ref HCI_LE_SetExtScanRespData_T. */
#define HCI_CMD_SIZE_SET_EXT_ADV_ENABLE                     (0xFEU)        /**< Size for HCI LE Set Extended Advertising Enable command. See @ref HCI_LE_SetExtAdvertisingEnable_T. */
#define HCI_CMD_SIZE_REMOVE_ADV_SET                         (0x01U)        /**< Size for HCI LE Remove Advertising Set command. See @ref HCI_LE_RemoveAdvertisingSet_T. */
#define HCI_CMD_SIZE_CLEAR_ADV_SET                          (0x00U)        /**< Size for HCI LE Clear Advertising Sets command. No parameters required. */
#define HCI_CMD_SIZE_SET_PERIODIC_ADV_PARAMS                (0x07U)        /**< Size for HCI LE Set Periodic Advertising Parameters command. See @ref HCI_LE_SetPeriodicAdvertisingParams_T. */
#define HCI_CMD_SIZE_SET_PERIODIC_ADV_DATA                  (0xFFU)        /**< Size for HCI LE Set Periodic Advertising Data command. See @ref HCI_LE_SetPeriodicAdvertisingData_T. */
#define HCI_CMD_SIZE_SET_PERIODIC_ADV_ENABLE                (0x02U)        /**< Size for HCI LE Set Periodic Advertising Enable command. See @ref HCI_LE_SetPeriodicAdvertisingEnable_T. */
#define HCI_CMD_SIZE_SET_EXT_SCAN_PARAMS                    (0x0DU)        /**< Size for HCI LE Set Extended Scan Parameters command. See @ref HCI_LE_SetExtScanParams_T. */
#define HCI_CMD_SIZE_SET_EXT_SCAN_ENABLE                    (0x06U)        /**< Size for HCI LE Set Extended Scan Enable command. See @ref HCI_LE_SetExtScanEnable_T. */
#define HCI_CMD_SIZE_EXT_CREATE_CONN                        (0x3AU)        /**< Size for HCI LE Extended Create Connection command. See @ref HCI_LE_ExtCreateConnParam_T. */
#define HCI_CMD_SIZE_PA_CREATE_SYNC                         (0x0EU)        /**< Size for HCI LE Periodic Advertising Create Sync command. See @ref HCI_LE_PeriodicAdvertisingCreateSync_T. */
#define HCI_CMD_SIZE_PA_CREATE_SYNC_CANCEL                  (0x00U)        /**< Size for HCI LE Periodic Advertising Create Sync Cancel command. No parameters required. */
#define HCI_CMD_SIZE_PA_TERMINATE_SYNC                      (0x02U)        /**< Size for HCI LE Periodic Advertising Terminate Sync command. See @ref HCI_LE_PeriodicAdvertisingTerminateSync_T. */
#define HCI_CMD_SIZE_ADD_DEV_TO_PERIODIC_ADV_LIST           (0x08U)        /**< Size for HCI LE Add Device To Periodic Advertising List command. See @ref HCI_LE_AddDevToPeriodicAdvList_T. */
#define HCI_CMD_SIZE_CLEAR_PERIODIC_ADV_LIST                (0x00U)        /**< Size for HCI LE Clear Periodic Advertising List command. No parameters required. */
#define HCI_CMD_SIZE_READ_TRANSMIT_POWER                    (0x00U)        /**< Size for HCI Read Transmit Power Level command. No parameters required. */
#define HCI_CMD_SIZE_SET_PRIVACY_MODE                       (0x08U)        /**< Size for HCI LE Set Privacy Mode command. See @ref HCI_LE_SetPrivacyMode_T. */
#define HCI_CMD_SIZE_SET_PERIODIC_ADV_RX_ENABLE             (0x03U)        /**< Size for HCI LE Set Periodic Advertising Receive Enable command. See @ref HCI_LE_SetPeriodicAdvReceiveEnable_T. */
#define HCI_CMD_SIZE_ENHANCED_READ_TRANSMIT_POWER_LEVEL     (0x03U)        /**< Size for HCI LE Enhanced Read Transmit Power Level command. See @ref HCI_LE_EnhancedReadTransmitPowerLevel_T. */
#define HCI_CMD_SIZE_READ_REMOTE_TRANSMIT_POWER_LEVEL       (0x03U)        /**< Size for HCI LE Read Remote Transmit Power Level command. See @ref HCI_LE_ReadRemoteTransmitPowerLevel_T. */
#define HCI_CMD_SIZE_SET_TRANSMIT_POWER_REPORTING_ENABLE    (0x04U)        /**< Size for HCI LE Set Transmit Power Reporting Enable command. See @ref HCI_LE_SetTransmitPowerReportingEnable_T. */
#define HCI_CMD_SIZE_TX_TEST_V4                             (0x08U)        /**< Size for HCI LE Transmitter Test V4 command. See @ref HCI_LE_TransmitterTestV4_T. */
#define HCI_CMD_SIZE_SET_PATH_LOSS_PARAMS                   (0x08U)        /**< Size for HCI LE Set Path Loss Reporting Parameters command. See @ref HCI_LE_SetPathLossReportingParams_T. */
#define HCI_CMD_SIZE_SET_PATH_LOSS_ENABLE                   (0x03U)        /**< Size for HCI LE Set Path Loss Reporting Enable command. See @ref HCI_LE_SetPathLossReportingEnable_T. */
#define HCI_CMD_SIZE_SET_DEFAULT_SUBRATE                    (0x0AU)        /**< Size for HCI LE Set Default Subrate command. See @ref HCI_LE_SetDefaultSubrate_T. */
#define HCI_CMD_SIZE_SUBRATE_REQUEST                        (0x0CU)        /**< Size for HCI LE Subrate Request command. See @ref HCI_LE_SubrateRequest_T. */
#define HCI_CMD_SIZE_SET_HOST_FEATURE                       (0x02U)        /**< Size for HCI LE Subrate Request command. See @ref HCI_LE_SetHostFeature_T. */
#define HCI_CMD_SIZE_SET_DATA_REL_ADDR_CHANGE               (0x02U)        /**< Size for HCI LE Set Data Related Address Changes command. See @ref HCI_LE_SetDataRelatedAddrChange_T. */
/** @} */


/**
 * @defgroup HCI_EVT_SIZE Pre-defined size of HCI event packet
 * @brief Defines the size of parameters for each HCI event packet.
 * @{
 */
#define HCI_EVT_SIZE_DISCONNECTION                          (0x04U)        /**< Size of the Disconnection Complete event parameter. See @ref HCI_EvtDisconnect_T. */
#define HCI_EVT_SIZE_ENCRYPTION_CHANGE                      (0x04U)        /**< Size of the Encryption Change event parameter. See @ref HCI_EvtEncryptChange_T. */
#define HCI_EVT_SIZE_REMOTE_VERSION_INFORMATION_COMPLETE    (0x08U)        /**< Size of the Remote Version Information Complete event parameter. See @ref HCI_EvtReadRemoteVer_T. */
#define HCI_EVT_SIZE_NBR_OF_COMPLETED_PKTS                  (0x19U)        /**< Size of the Number Of Completed Packets event parameter. See @ref HCI_EvtNumOfCompletePacket_T. */
#define HCI_EVT_SIZE_KEY_REFRESH_COMPLETE                   (0x03U)        /**< Size of the Key Refresh Complete event parameter. See @ref HCI_EvtKeyRefreshComplete_T. */
#define HCI_EVT_SIZE_AUTH_PAYLOAD_TO_EXPIRED                (0x02U)        /**< Size of the Authenticated Payload Timeout Expired event parameter. See @ref HCI_EvtAuthPayloadTimeout_T. */
/** @} */


/**
 * @defgroup HCI_LE_META_SUB_EVT_SIZE HCI subevent size definition of LE Meta event
 * @brief Defines the size of parameters for each subevent in the HCI LE Meta event.
 * @{
 */
#define HCI_EVT_SIZE_CONNECT_COMPLETE                    (0x12U)           /**< Size of the LE Connection Complete subevent parameter. See @ref HCI_EvtLeConnect_T. */
#define HCI_EVT_SIZE_ADV_REPORT                          (0x2AU)           /**< Size of the LE Advertising Report subevent parameters. See @ref HCI_EvtLeAdvReport_T. */
#define HCI_EVT_SIZE_CONNECTION_UPDATE_COMPLETE          (0x09U)           /**< Size of the LE Connection Update Complete subevent parameters. See @ref HCI_EvtLeConnParamUpdate_T. */
#define HCI_EVT_SIZE_READ_REMOTE_FEATURES_COMPLETE       (0x0BU)           /**< Size of the LE Read Remote Features Complete subevent parameters. See @ref HCI_EvtLeReadRemoteFeature_T. */
#define HCI_EVT_SIZE_LONG_TERM_KEY_REQUEST               (0x0CU)           /**< Size of the LE Long Term Key Request subevent parameters. See @ref HCI_EvtLeLongTermKeyReq_T. */
#define HCI_EVT_SIZE_REMOTE_CONNECTION_UPDATE_REQUEST    (0x0AU)           /**< Size of the LE Remote Connection Parameter Request subevent parameters. See @ref HCI_EvtLeRemoteConnParamsReq_T. */
#define HCI_EVT_SIZE_DATA_LENGTH_CHANGE                  (0x0AU)           /**< Size of the LE Data Length Change subevent parameters. See @ref HCI_EvtLeDataLengthChange_T. */
#define HCI_EVT_SIZE_ENHANCED_CONNECTION_COMPLETE        (0x1EU)           /**< Size of the LE Enhanced Connection Complete subevent parameters. See @ref HCI_EvtLeEnhanceConnect_T. */
#define HCI_EVT_SIZE_DIRECT_ADV_REPORT                   (0x11U)           /**< Size of the LE Direct Advertising Report subevent parameters. See @ref HCI_EvtLeDirectAdvReport_T. */
#define HCI_EVT_SIZE_PHY_UPDATE_COMPLETE                 (0x05U)           /**< Size of the LE PHY Update Complete subevent parameters. See @ref HCI_EvtLePhyUpdate_T. */
#define HCI_EVT_SIZE_EXTENDED_ADV_REPORT                 (0xFEU)           /**< Size of the LE Extended Advertising Report subevent parameters. See @ref HCI_EvtLeExtAdvReport_T. */
#define HCI_EVT_SIZE_PA_SYNC_ESTABLISHED                 (0x0FU)           /**< Size of the LE Periodic Advertising Sync Established subevent parameters. See @ref HCI_EvtLePeriodicAdvSyncEst_T. */
#define HCI_EVT_SIZE_PA_REPORT                           (0xFEU)           /**< Size of the LE Periodic Advertising Report subevent parameters. See @ref HCI_EvtLePeriodicAdvReport_T. */
#define HCI_EVT_SIZE_PA_SYNC_LOST                        (0x02U)           /**< Size of the LE Periodic Advertising Sync Lost subevent parameters. See @ref HCI_EvtLePeriodicAdvSyncLost_T. */
#define HCI_EVT_SIZE_SCAN_TIMEOUT                        (0x00U)           /**< Size of the LE Scan Timeout subevent parameters. No parameters are included. */
#define HCI_EVT_SIZE_ADV_SET_TERMINATED                  (0x05U)           /**< Size of the LE Advertising Set Terminated subevent parameters. See @ref HCI_EvtLeAdvSetTerminated_T. */
#define HCI_EVT_SIZE_SCAN_REQUEST_RECEIVED               (0x08U)           /**< Size of the LE Scan Request Received subevent parameters. See @ref HCI_EvtLeScanReqReceived_T. */
#define HCI_EVT_SIZE_CHANNEL_SELECT_ALGORITHM            (0x03U)           /**< Size of the LE Channel Selection Algorithm subevent parameters. See @ref HCI_EvtLeChannelSelectAlgorithm_T. */
#define HCI_EVT_SIZE_TX_POWER_REPORTING                  (0x08U)           /**< Size of the LE Transmit Power Reporting subevent parameters. See @ref HCI_EvtLeTxPowerReporting_T. */
#define HCI_EVT_SIZE_PATH_LOSS_THRESHOLD                 (0x04U)           /**< Size of the LE Path Loss Threshold subevent parameters. See @ref HCI_EvtLePathLossThreshold_T. */
#define HCI_EVT_SIZE_SUBRATE_CHANGE                      (0x0BU)           /**< Size of the LE Subrate Change subevent parameters. See @ref HCI_EvtLeSubrateChange_T. */
/** @} */


/**
 * @defgroup HCI_CC_EVT_SIZE Pre-defined size of HCI command complete event packet
 * @brief Defines the size of parameters for the HCI command complete event for different opcodes.
 * @{
 */
#define HCI_CC_EVT_SIZE_STATUS                              (0x01U)        /**< Size of command complete event whose returned parameter containing only status parameter. */
#define HCI_CC_EVT_SIZE_READ_AFH_CHAN_ASSESS_MODE           (0x02U)        /**< Size of the Read AFH Channel Assessment Mode command complete event. See @ref HCI_CC_ReadAfhChannelAssessMode_T. */
#define HCI_CC_EVT_SIZE_READ_AUTH_PAYLOAD_TO                (0x05U)        /**< Size of the Read Authenticated Payload Timeout command complete event. See @ref HCI_CC_ReadAuthenticatedPayloadTimeout_T. */
#define HCI_CC_EVT_SIZE_WRITE_AUTH_PAYLOAD_TO               (0x03U)        /**< Size of the Write Authenticated Payload Timeout command complete event. See @ref HCI_CC_WriteAuthenticatedPayloadTimeout_T. */
#define HCI_CC_EVT_SIZE_READ_BD_ADDR                        (0x07U)        /**< Size of the Read BD_ADDR command complete event. See @ref HCI_CC_ReadBdAddr_T. */
#define HCI_CC_EVT_SIZE_READ_RSSI                           (0x04U)        /**< Size of the Read RSSI command complete event. See @ref HCI_CC_ReadRssi_T. */
#define HCI_CC_EVT_SIZE_READ_CHANNEL_MAP                    (0x08U)        /**< Size of the LE Read Channel Map command complete event. See @ref HCI_CC_LE_ReadChannelMap_T. */
#define HCI_CC_EVT_SIZE_LTK_REQUEST_REPLY                   (0x03U)        /**< Size of the LE Long Term Key Request Reply command complete event. See @ref HCI_CC_LE_LtkReqReply_T. */
#define HCI_CC_EVT_SIZE_LTK_REQUEST_NEGATIVE_REPLY          (0x03U)        /**< Size of the LE Long Term Key Request Negative Reply command complete event. See @ref HCI_CC_LE_LtkReqNegativeReply_T. */
#define HCI_CC_EVT_SIZE_TEST_END                            (0x03U)        /**< Size of the LE Test End command complete event. See @ref HCI_CC_LE_TestEnd_T. */
#define HCI_CC_EVT_SIZE_REMOTE_CP_REQ_REPLY                 (0x03U)        /**< Size of the LE Remote Connection Parameter Request Reply command complete event. See @ref HCI_CC_LE_RemoteConnParamReqReply_T. */
#define HCI_CC_EVT_SIZE_REMOTE_CP_REQ_NEG_REPLY             (0x03U)        /**< Size of the LE Remote Connection Parameter Request Negative Reply command complete event. See @ref HCI_CC_LE_RemoteConnParamReqNegReply_T. */
#define HCI_CC_EVT_SIZE_SET_DATA_LENGTH                     (0x03U)        /**< Size of the LE Set Data Length command complete event. See @ref HCI_CC_LE_SetDataLength_T. */
#define HCI_CC_EVT_SIZE_READ_PHY                            (0x05U)        /**< Size of the LE Read PHY command complete event. See @ref HCI_CC_LE_ReadPhy_T. */
#define HCI_CC_EVT_SIZE_SET_EXT_ADV_PARAMS                  (0x02U)        /**< Size of the LE Set Extended Advertising Parameters command complete event. See @ref HCI_CC_LE_SetExtAdvertisingParameters_T. */
#define HCI_CC_EVT_SIZE_READ_TRANSMIT_POWER                 (0x03U)        /**< Size of the LE Read Transmit Power command complete event. See @ref HCI_CC_LE_ReadTransmitPower_T. */
#define HCI_CC_EVT_SIZE_ENHANCED_READ_TRANSMIT_POWER        (0x06U)        /**< Size of the LE Enhanced Read Transmit Power command complete event. See @ref HCI_CC_LE_EnhancedReadTransmitPower_T. */
#define HCI_CC_EVT_SIZE_SET_PLR_PARAMS                      (0x03U)        /**< Size of the LE Set Path Loss Reporting Parameters command complete event. See @ref HCI_CC_LE_SetPathLossReportingParams_T. */
#define HCI_CC_EVT_SIZE_SET_PLR_ENABLE                      (0x03U)        /**< Size of the LE Set Path Loss Reporting Enable command complete event. See @ref HCI_CC_LE_SetPathLossReportingEnable_T. */
#define HCI_CC_EVT_SIZE_SET_TRANSMIT_POWER_REPORTING_ENABLE (0x03U)        /**< Size of the LE Set Transmit Power Reporting Enable command complete event. See @ref HCI_CC_LE_SetTransmitPowerReportingEnable_T. */
/** @} */

/** @} */ //HOST_HCI_DEFINES

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

/**
 * @addtogroup HOST_HCI_STRUCTS Structures
 * @{
 */

/** @brief Structure for the HCI Disconnect command parameters. */
typedef struct HCI_Disconnect_T
{
    uint16_t            connHandle;                                        /**< The handle of the connection to be disconnected. */
    uint8_t             reason;                                            /**< The reason code explaining why the disconnection occurred. */
} HCI_Disconnect_T;

/** @brief Structure for parameters of the "Write AFH Channel Assessment Mode" command. */
typedef struct HCI_WriteAfhChannelAssessMode_T
{
    uint8_t             AfhChannelAssessMode;                              /**< AFH Channel Assessment Mode is enabled (1) or disabled (0). */
} HCI_WriteAfhChannelAssessMode_T;

/** @brief Structure for the HCI Read Authenticated Payload Timeout command parameters. */
typedef struct HCI_ReadAuthenticatedPayloadTimeout_T
{
    uint16_t            connHandle;                                        /**< The handle of the connection for which the authenticated payload timeout is to be read. */
} HCI_ReadAuthenticatedPayloadTimeout_T;


/** @brief Structure for the HCI Write Authenticated Payload Timeout command parameters. */
typedef struct HCI_WriteAuthenticatedPayloadTimeout_T
{
    uint16_t            connHandle;                                        /**< The handle of the connection for which the authenticated payload timeout is to be written. */
    uint16_t            authenticatedPayloadTimeout;                       /**< The new authenticated payload timeout value in 10 ms units. */
} HCI_WriteAuthenticatedPayloadTimeout_T;


/** @brief Structure for the HCI Read RSSI command parameters. */
typedef struct HCI_ReadRssi_T
{
    uint16_t            connHandle;                                        /**< The handle of the connection for which the RSSI is to be read. */
} HCI_ReadRssi_T;


/** @brief Structure for the HCI LE Set Random Address command parameters. */
typedef  struct HCI_LE_SetRandomAddress_T
{
    uint8_t             randomAddr[HCI_BD_ADDRESS_LEN];                    /**< The random device address to be used by the controller. */
} HCI_LE_SetRandomAddress_T;


/** @brief Structure for the HCI LE Set Advertising Parameters command parameters. */
typedef  struct HCI_LE_SetAdvertisingParameters_T
{
    uint16_t            intervalMin;                                       /**< The minimum advertising interval for undirected and low duty cycle directed advertising. */
    uint16_t            intervalMax;                                       /**< The maximum advertising interval for undirected and low duty cycle directed advertising. */
    uint8_t             type;                                              /**< The type of advertising to perform. */
    uint8_t             ownAddrType;                                       /**< The type of the address being used in the advertising packets. */
    uint8_t             peerAddrType;                                      /**< The type of the peer address, if directed advertising is used. */
    uint8_t             peerAddr[HCI_BD_ADDRESS_LEN];                      /**< The peer's Bluetooth device address, if directed advertising is used. */
    uint8_t             advChannelMap;                                     /**< The channel map indicating which of the three advertising channels will be used. */
    uint8_t             filterPolicy;                                      /**< The advertising filter policy to apply. */
} HCI_LE_SetAdvertisingParameters_T;


/** @brief Structure for setting advertising data. */
typedef struct HCI_LE_SetAdvertisingData_T
{
    uint8_t             advLen;                                            /**< Length of the advertising data in bytes. Maximum length defined by @ref HCI_MAX_ADV_LENGTH. */
    uint8_t             advData[HCI_MAX_ADV_LENGTH];                       /**< Array containing the advertising data. */
} HCI_LE_SetAdvertisingData_T;


/** @brief Structure for setting scan response data. */
typedef struct HCI_LE_SetScanResponseData_T
{
    uint8_t             advScanRspLen;                                     /**< Length of the scan response data in bytes. Maximum length defined by @ref HCI_MAX_ADV_LENGTH. */
    uint8_t             advScanRspData[HCI_MAX_ADV_LENGTH];                /**< Array containing the scan response data. */
} HCI_LE_SetScanResponseData_T;


/** @brief Structure for enabling or disabling advertising. */
typedef struct HCI_LE_SetAdvertisingEnable_T
{
    uint8_t             enable;                                            /**< Flag to enable (1) or disable (0) advertising. */
} HCI_LE_SetAdvertisingEnable_T;


/** @brief Structure for setting scanning parameters. */
typedef  struct HCI_LE_SetScanParameters_T
{
    uint8_t             scanType;                                          /**< Type of scan to perform (e.g., passive or active). */
    uint16_t            scanInterval;                                      /**< Time interval between consecutive scans. */
    uint16_t            scanWindow;                                        /**< Duration of the scanning window. Must be less than or equal to scanInterval. */
    uint8_t             ownAddrType;                                       /**< Type of the scanner's own Bluetooth address. */
    uint8_t             filterPolicy;                                      /**< Scanning filter policy to apply. */
    uint8_t             disChannel;                                        /**< Proprietary feature to disable a specific channel during scanning. */
} HCI_LE_SetScanParameters_T;


/** @brief Structure for enabling or disabling scanning. */
typedef struct HCI_LE_SetScanEnable_T
{
    uint8_t             enable;                                            /**< Flag to enable (1) or disable (0) scanning. */
    uint8_t             filterDuplicates;                                  /**< Policy for filtering duplicate packets. */
} HCI_LE_SetScanEnable_T;


/** @brief Structure for creating a connection. */
typedef struct HCI_LE_CreateConnection_T
{
    uint16_t            scanInterval;                                      /**< Time interval between consecutive scans when looking for advertising packets to connect to. */
    uint16_t            scanWindow;                                        /**< Duration of the scanning window when looking for advertising packets to connect to. Must be less than or equal to scanInterval. */
    uint8_t             filterPolicy;                                      /**< Initiator filter policy to determine the use of the Filter Accept List. */
    uint8_t             peerAddrType;                                      /**< Type of the peer's Bluetooth address. Ignored if filterPolicy is enabled. */
    uint8_t             peerAddr[HCI_BD_ADDRESS_LEN];                      /**< Peer's Bluetooth address. Ignored if filterPolicy is enabled. */
    uint8_t             ownAddrType;                                       /**< Type of the initiator's own Bluetooth address. */
    uint16_t            intervalMin;                                       /**< Minimum allowed connection interval. Must not exceed intervalMax. */
    uint16_t            intervalMax;                                       /**< Maximum allowed connection interval. */
    uint16_t            latency;                                           /**< Connection latency in terms of the number of connection events. */
    uint16_t            supervisionTimeout;                                /**< Supervision timeout for the connection. Must be greater than (1 + latency) * intervalMax * 2. */
    uint16_t            minCeLength;                                       /**< Minimum length of a connection event required for this connection. */
    uint16_t            maxCeLength;                                       /**< Maximum length of a connection event allowed for this connection. */
} HCI_LE_CreateConnection_T;


/** @brief Structure for adding a device to the filter accept list command parameters. */
typedef struct HCI_LE_AddDeviceToFilterAcceptList_T
{
    uint8_t             addrType;                                          /**< Type of address being used. Typically public (0x00) or random (0x01). */
    uint8_t             addr[HCI_BD_ADDRESS_LEN];                          /**< 6-byte Bluetooth device address. */
} HCI_LE_AddDeviceToFilterAcceptList_T;


/** @brief Structure for connection update command parameters. */
typedef struct HCI_LE_ConnectionUpdate_T
{
    uint16_t            connHandle;                                        /**< Handle identifying the connection to be updated. */
    uint16_t            intervalMin;                                       /**< Minimum value for the connection event interval. This shall be less than or equal to intervalMax. */
    uint16_t            intervalMax;                                       /**< Maximum value for the connection event interval. */
    uint16_t            latency;                                           /**< Number of connection events the peripheral can skip (peripheral latency). */
    uint16_t            supervisionTimeout;                                /**< Supervision timeout for the LE link. It shall be large enough to accommodate the latency * intervalMax * 2 formula. */
    uint16_t            minCeLength;                                       /**< Minimum length of connection event needed for this connection. */
    uint16_t            maxCeLength;                                       /**< Maximum length of connection event allowed for this connection. */
} HCI_LE_ConnectionUpdate_T;


/** @brief Structure for read channel map command parameters. */
typedef struct HCI_LE_ReadChannelMap_T
{
    uint16_t            connHandle;                                        /**< Handle identifying the connection for which the channel map is being read. */
} HCI_LE_ReadChannelMap_T;


/** @brief Structure for read remote features command parameters. */
typedef struct HCI_LE_ReadRemoteFeatures_T
{
    uint16_t            connHandle;                                        /**< Handle identifying the connection for which the remote features are being read. */
} HCI_LE_ReadRemoteFeatures_T;


/** @brief Structure for enable encryption command parameters. */
typedef struct HCI_LE_EnableEncryption_T
{
    uint16_t            connHandle;                                        /**< Handle identifying the connection to be encrypted. */
    uint8_t             randomNum[HCI_LTK_RANDOM_SIZE];                    /**< 64-bit random number used in the encryption process. */
    uint16_t            encryptedDiversifier;                              /**< 16-bit encrypted diversifier used in the encryption process. */
    uint8_t             longTermKey[HCI_MAX_KEY_LENGTH];                   /**< 128-bit Long Term Key (LTK) used to encrypt the connection. */
} HCI_LE_EnableEncryption_T;


/** @brief Structure for long term key request reply command parameters. */
typedef struct HCI_LE_LongTermKeyRequestReply_T
{
    uint16_t            connHandle;                                        /**< Handle identifying the connection for which the LTK is being provided. */
    uint8_t             longTermKey[HCI_MAX_KEY_LENGTH];                   /**< 128-bit Long Term Key (LTK) to be used for the connection. */
} HCI_LE_LongTermKeyRequestReply_T;


/** @brief Structure for long term key request negative reply command parameters. */
typedef struct HCI_LE_LongTermKeyRequestNegativeReply_T
{
    uint16_t            connHandle;                                        /**< Handle identifying the connection for which the LTK request is being rejected. */
} HCI_LE_LongTermKeyRequestNegativeReply_T;


/** @brief Structure for the 'LE Receiver Test Version 1' command parameters. */
typedef struct HCI_LE_ReceiverTestV1_T
{
    uint8_t             rxChannel;                                         /**< RF channel for receiver testing. */
} HCI_LE_ReceiverTestV1_T;


/** @brief Structure for the 'LE Transmitter Test Version 1' command parameters. */
typedef struct HCI_LE_TransmitterTestV1_T
{
    uint8_t             txChannel;                                         /**< RF channel for transmitter testing. */
    uint8_t             testDataLen;                                       /**< Length of test data payload in test packets. */
    uint8_t             packetPayload;                                     /**< Payload content for test packets. */
} HCI_LE_TransmitterTestV1_T;


/** @brief Structure for the 'LE Remote Connection Parameter Request Reply' command parameters. */
typedef struct HCI_LE_RemoteConnParamReqReply_T
{
    uint16_t            connHandle;                                        /**< Handle for the connection to apply these parameters. */
    uint16_t            intervalMin;                                       /**< Minimum value for the connection interval. Must not exceed intervalMax. */
    uint16_t            intervalMax;                                       /**< Maximum value for the connection interval. */
    uint16_t            latency;                                           /**< Maximum latency for the connection in number of connection events. */
    uint16_t            supervisionTimeout;                                /**< Supervision timeout for the connection, in milliseconds. Must be greater than (1 + latency) * intervalMax * 2. */
    uint16_t            minCeLength;                                       /**< Minimum connection event length required for this connection. */
    uint16_t            maxCeLength;                                       /**< Maximum connection event length allowed for this connection. */
} HCI_LE_RemoteConnParamReqReply_T;


/** @brief Structure for the 'LE Remote Connection Parameter Request Negative Reply' command parameters. */
typedef struct HCI_LE_RemoteConnParamReqNegReply_T
{
    uint16_t            connHandle;                                        /**< Handle for the connection associated with this negative reply. */
    uint8_t             reason;                                            /**< Reason code for rejecting the connection parameter request. */
} HCI_LE_RemoteConnParamReqNegReply_T;


/** @brief Structure for the 'LE Set Data Length' command parameters. */
typedef struct HCI_LE_SetDataLength_T
{
    uint16_t            connHandle;                                        /**< Handle for the connection to set the data length. */
    uint16_t            txOctets;                                          /**< Maximum number of payload octets for a single LL Data PDU. */
    uint16_t            txTime;                                            /**< Maximum time in microseconds for transmitting a single LL Data PDU. */
} HCI_LE_SetDataLength_T;


/** @brief Structure for the 'LE Add Device To Resolving List' command parameters. */
typedef struct HCI_LE_AddDeviceToResolvingList_T
{
    uint8_t             peerIdAddrType;                                    /**< Type of the peer device's address. */
    uint8_t             peerIdAddr[HCI_BD_ADDRESS_LEN];                    /**< Public or static random address of the peer device. */
    uint8_t             peerIrk[HCI_MAX_KEY_LENGTH];                       /**< Identity Resolving Key (IRK) of the peer device. */
    uint8_t             localIrk[HCI_MAX_KEY_LENGTH];                      /**< IRK of the local device. */
} HCI_LE_AddDeviceToResolvingList_T;


/** @brief Structure for the 'LE Set Address Resolution Enable' command parameters. */
typedef struct HCI_LE_SetAddressResolutionEnable_T
{
    uint8_t             addressResolutionEnable;                           /**< Enable or disable address resolution in the controller. */
} HCI_LE_SetAddressResolutionEnable_T;


/** @brief Structure for setting the resolvable private address timeout. */
typedef struct HCI_LE_SetRpaTimeout_T
{
    uint16_t            rpaTimeout;                                        /**< Timeout for using a new resolvable private address, in seconds. */
} HCI_LE_SetRpaTimeout_T;


/** @brief Structure for reading the PHY type of a connection. */
typedef struct HCI_LE_ReadPhy_T
{
    uint16_t            connHandle;                                        /**< Handle for the connection to read the PHY from. */
} HCI_LE_ReadPhy_T;


/** @brief Structure for setting the default PHY preferences. */
typedef struct HCI_LE_SetDefaultPhy_T
{
    uint8_t             allPhys;                                           /**< Bit field to specify the Host's preference among supported PHYs in a given direction. */
    uint8_t             txPhys;                                            /**< Bit field to indicate preferred transmitter PHYs. */
    uint8_t             rxPhys;                                            /**< Bit field to indicate preferred receiver PHYs. */
} HCI_LE_SetDefaultPhy_T;


/** @brief Structure for setting PHY preferences for a connection. */
typedef struct HCI_LE_SetPhy_T
{
    uint16_t            connHandle;                                        /**< Handle for the connection to set the PHY for. */
    uint8_t             allPhys;                                           /**< Bit field to specify the Host's preference among supported PHYs in a given direction. */
    uint8_t             txPhys;                                            /**< Bit field to indicate preferred transmitter PHYs. */
    uint8_t             rxPhys;                                            /**< Bit field to indicate preferred receiver PHYs. */
    uint16_t            phyOptions;                                        /**< Bit field to specify PHY options. */
} HCI_LE_SetPhy_T;


/** @brief Structure for parameters of the receiver test (version 2). */
typedef struct HCI_LE_ReceiverTestV2_T
{
    uint8_t             rxChannel;                                         /**< RF channel for the receiver test. */
    uint8_t             phy;                                               /**< PHY to use during the receiver test. */
    uint8_t             modulationIndex;                                   /**< Indicates if the receiver assumes a stable modulation index. */
} HCI_LE_ReceiverTestV2_T;


/**@brief Structure for parameters of the transmitter test (version 2). */
typedef struct HCI_LE_TransmitterTestV2_T
{
    uint8_t             txChannel;                                         /**< RF channel for the transmitter test. */
    uint8_t             testDataLen;                                       /**< Length of the test packet payload. */
    uint8_t             packetPayload;                                     /**< Content of the test packet payload. */
    uint8_t             phy;                                               /**< PHY to use during the transmitter test. */
} HCI_LE_TransmitterTestV2_T;


/** @brief Structure for setting the random address for an advertising set. */
typedef struct HCI_LE_SetAdvertisingSetRandomAddr_T
{
    uint8_t             advHandle;                                         /**< Identifier for the advertising set. */
    uint8_t             advRandomAddr[HCI_BD_ADDRESS_LEN];                 /**< Random address for the specified advertising set. */
} HCI_LE_SetAdvertisingSetRandomAddr_T;


/**@brief Structure for setting extended advertising parameters. */
typedef struct HCI_LE_SetExtAdvertisingParameters_T
{
    uint8_t             advhandle;                                         /**< Identifier for the advertising set. */
    uint16_t            evtProperies;                                      /**< Properties for the advertising event. */
    uint8_t             priIntervalMin[3];                                 /**< Minimum primary advertising interval for undirected and low duty cycle directed advertising (in units of 0.625ms). */
    uint8_t             priIntervalMax[3];                                 /**< Maximum primary advertising interval for undirected and low duty cycle directed advertising (in units of 0.625ms). */
    uint8_t             priChannelMap;                                     /**< Channel map for primary advertising. */
    uint8_t             ownAddrType;                                       /**< Type of the advertiser's own Bluetooth address. */
    uint8_t             peerAddrType;                                      /**< Type of the peer's Bluetooth address. */
    uint8_t             peerAddr[HCI_BD_ADDRESS_LEN];                      /**< Peer's Bluetooth address. */
    uint8_t             filterPolicy;                                      /**< Filter policy for advertising. */
    int8_t              txPower;                                           /**< Transmit power for advertising. */
    uint8_t             priPhy;                                            /**< Primary advertising PHY. */
    uint8_t             secMaxSkip;                                        /**< Maximum number of advertising events that can be skipped before sending AUX_ADV_IND packets on the secondary advertising channel. */
    uint8_t             secPhy;                                            /**< Secondary advertising PHY. */
    uint8_t             advSid;                                            /**< Advertising SID subfield value in the ADI field of the PDU. */
    uint8_t             scanReqNotifiEnable;                               /**< Enable or disable scan request notifications. */
    uint8_t             priPhyOptions;                                     /**< Host prefer coding scheme if primary advertising uses LE Coded PHY. */
    uint8_t             secPhyOptions;                                     /**< Host prefer coding shceme if secondary advertising uses LE Coded PHY. */
} HCI_LE_SetExtAdvertisingParameters_T;


/** @brief Structure for setting extended advertising data. */
typedef struct HCI_LE_SetExtAdvertisingData_T
{
    uint8_t             advHandle;                                         /**< Identifier for the advertising set. */
    uint8_t             operation;                                         /**< Operation to be performed on the advertising data. */
    uint8_t             fragPreference;                                    /**< Preference for advertising data fragmentation. */
    uint8_t             advLen;                                            /**< Length of the advertising data in bytes. Maximum length defined by HCI_CMD_MAX_EXTENDED_ADVERTISING_DATA_LENGTH. */
    uint8_t             advData[HCI_CMD_MAX_EXTENDED_ADVERTISING_DATA_LENGTH]; /**< Buffer containing the advertising data. */
} HCI_LE_SetExtAdvertisingData_T;


/** @brief Structure for setting extended scan response data. */
typedef struct HCI_LE_SetExtScanRespData_T
{
    uint8_t             advHandle;                                         /**< Identifier for the advertising set. */
    uint8_t             operation;                                         /**< Operation to be performed on the scan response data. */
    uint8_t             fragPreference;                                    /**< Preference for scan response data fragmentation. */
    uint8_t             scanRspLen;                                        /**< Length of the scan response data in bytes. Maximum length defined by HCI_CMD_MAX_EXTENDED_ADVERTISING_DATA_LENGTH. */
    uint8_t             scanRspData[HCI_CMD_MAX_EXTENDED_ADVERTISING_DATA_LENGTH]; /**< Buffer containing the scan response data. */
} HCI_LE_SetExtScanRespData_T;


/** @brief Structure representing an advertising set's parameters. */
typedef struct HCI_LE_ExtAdvertisingSet_T
{
    uint8_t             advHandle;                                         /**< Identifier for the advertising set. */
    uint16_t            duration;                                          /**< Duration to enable the advertising set, in units of 10ms. */
    uint8_t             maxExtAdvEvts;                                     /**< Maximum number of extended advertising events to attempt before terminating the advertising. */
} HCI_LE_ExtAdvertisingSet_T;


/** @brief Structure for enabling or disabling extended advertising. */
typedef struct HCI_LE_SetExtAdvertisingEnable_T
{
    uint8_t                         enable;                                /**< Flag to enable (1) or disable (0) extended advertising. */
    uint8_t                         numOfSets;                             /**< Number of advertising sets to be enabled or disabled. */
    HCI_LE_ExtAdvertisingSet_T      advSet[HCI_MAX_EXTENDED_ADVERTISING_SETS]; /**< Array of advertising set parameters. */
} HCI_LE_SetExtAdvertisingEnable_T;


/** @brief Structure for removing an advertising set. */
typedef struct HCI_LE_RemoveAdvertisingSet_T
{
    uint8_t             advHandle;                                         /**< Identifier for the advertising set to be removed. */
} HCI_LE_RemoveAdvertisingSet_T;


/** @brief Structure for setting periodic advertising parameters. */
typedef  struct HCI_LE_SetPeriodicAdvertisingParams_T
{
    uint8_t             advHandle;                                         /**< Identifier for the advertising set. */
    uint16_t            intervalMin;                                       /**< Minimum advertising interval for periodic advertising, in units of 0.625ms. */
    uint16_t            intervalMax;                                       /**< Maximum advertising interval for periodic advertising, in units of 0.625ms. */
    uint16_t            properties;                                        /**< Advertising properties indicating the fields to include in the packet. */
} HCI_LE_SetPeriodicAdvertisingParams_T;


/** @brief Structure for setting periodic advertising data. */
typedef struct HCI_LE_SetPeriodicAdvertisingData_T
{
    uint8_t             advHandle;                                         /**< Identifier for the advertising set. */
    uint8_t             operation;                                         /**< Operation to be performed on the periodic advertising data. */
    uint8_t             advLen;                                            /**< Length of the periodic advertising data in bytes. Maximum length defined by HCI_CMD_MAX_PERIODIC_ADVERTISING_DATA_LENGTH. */
    uint8_t             advData[HCI_CMD_MAX_PERIODIC_ADVERTISING_DATA_LENGTH]; /**< Buffer containing the periodic advertising data. */
} HCI_LE_SetPeriodicAdvertisingData_T;


/** @brief Structure for enabling or disabling periodic advertising. */
typedef struct HCI_LE_SetPeriodicAdvertisingEnable_T
{
    uint8_t             enable;                                            /**< Flag to enable (1) or disable (0) periodic advertising. */
    uint8_t             advHandle;                                         /**< Identifier for the advertising set. */
} HCI_LE_SetPeriodicAdvertisingEnable_T;


/** @brief Structure for extended scan parameters for each PHY. */
typedef struct HCI_LE_ExtScanParamsByPhy_T
{
    uint8_t             scanType;                                          /**< Type of scan to perform. */
    uint16_t            scanInterval;                                      /**< Interval between scan windows, in units of 0.625ms. */
    uint16_t            scanWindow;                                        /**< Duration of scan window, in units of 0.625ms. Must be less than or equal to scanInterval. */
    uint8_t             disChannel;                                        /**< Channel disablement flag for proprietary use. */
} HCI_LE_ExtScanParamsByPhy_T;


/** @brief Structure for setting extended scan parameters. */
typedef struct HCI_LE_SetExtScanParams_T
{
    uint8_t                         ownAddrType;                           /**< Type of the scanner's own Bluetooth address. */
    uint8_t                         scanFilterPolicy;                      /**< Filter policy applied during scanning. */
    uint8_t                         scanPhys;                              /**< Bit field indicating the PHYs to scan on. */
    HCI_LE_ExtScanParamsByPhy_T     paramsByPhy[HCI_SUPPORTED_EXT_SCAN_PHYS];  /**< Array of scan parameters for each PHY. */
} HCI_LE_SetExtScanParams_T;


/** @brief Structure for enabling or disabling extended scanning. */
typedef struct HCI_LE_SetExtScanEnable_T
{
    uint8_t             enable;                                            /**< Flag to enable or disable extended scanning. */
    uint8_t             filterDuplicates;                                  /**< Policy for filtering duplicate packets. */
    uint16_t            duration;                                          /**< Duration of a single scan window in 10 ms units. */
    uint16_t            period;                                            /**< Interval between scan windows in 1.28 s units. */
} HCI_LE_SetExtScanEnable_T;


/** @brief Structure for creating a connection with extended parameters for a single PHY. */
typedef struct HCI_LE_ExtCreateConnByPhy_T
{
    uint16_t            scanInterval;                                      /**< Interval between scan windows in 0.625 ms units. */
    uint16_t            scanWindow;                                        /**< Duration of scan window in 0.625 ms units. */
    uint16_t            intervalMin;                                       /**< Minimum value for the connection event interval in 1.25 ms units. */
    uint16_t            intervalMax;                                       /**< Maximum value for the connection event interval in 1.25 ms units. */
    uint16_t            latency;                                           /**< Peripheral latency for the connection in number of connection events. */
    uint16_t            supervisionTimeout;                                /**< Supervision timeout for the connection in 10 ms units. */
    uint16_t            minCeLength;                                       /**< Minimum length of connection event in 0.625 ms units. */
    uint16_t            maxCeLength;                                       /**< Maximum length of connection event in 0.625 ms units. */
} HCI_LE_ExtCreateConnByPhy_T;


/** @brief Structure for creating a connection with extended parameters across multiple PHYs. */
typedef struct HCI_LE_ExtCreateConnParam_T
{
    uint8_t                         initFilterPolicy;                      /**< Filter policy used by the initiator. */
    uint8_t                         ownAddrType;                           /**< Type of the initiator's own Bluetooth address. */
    uint8_t                         peerAddrType;                          /**< Type of the peer's Bluetooth address. */
    uint8_t                         peerAddr[HCI_BD_ADDRESS_LEN];          /**< Address of the peer device. */
    uint8_t                         initPhys;                              /**< Bit field indicating the PHYs to use for connection initiation. */
    HCI_LE_ExtCreateConnByPhy_T     paramsByPhy[HCI_SUPPORTED_EXT_CREATE_CONNECTION_PHYS];  /**< Array of connection parameters for each PHY. */
} HCI_LE_ExtCreateConnParam_T;


/**@brief Structure for creating synchronization with periodic advertising. */
typedef struct HCI_LE_PeriodicAdvertisingCreateSync_T
{
    uint8_t             options;                                           /**< Options for synchronization and reporting. */
    uint8_t             advSid;                                            /**< Advertising SID to identify the advertising set. */
    uint8_t             advAddrType;                                       /**< Type of the advertiser's Bluetooth address. */
    uint8_t             advAddr[HCI_BD_ADDRESS_LEN];                       /**< Address of the advertiser. */
    uint16_t            skip;                                              /**< Number of consecutive advertising packets that can be skipped. */
    uint16_t            syncTimeout;                                       /**< Synchronization timeout in 10 ms units. */
    uint8_t             syncCteType;                                       /**< Constant Tone Extension type for synchronization. */
} HCI_LE_PeriodicAdvertisingCreateSync_T;


/** @brief Structure for terminating synchronization with periodic advertising. */
typedef struct HCI_LE_PeriodicAdvertisingTerminateSync_T
{
    uint16_t            syncHandle;                                        /**< Handle identifying the periodic advertising train. */
} HCI_LE_PeriodicAdvertisingTerminateSync_T;


/** @brief Structure for adding a device to the periodic advertiser list. */
typedef struct HCI_LE_AddDevToPeriodicAdvList_T
{
    uint8_t             advAddrType;                                       /**< Type of the advertiser's Bluetooth address. */
    uint8_t             advAddr[HCI_BD_ADDRESS_LEN];                       /**< Address of the advertiser. */
    uint8_t             advSid;                                            /**< Advertising SID to identify the advertising set. */
} HCI_LE_AddDevToPeriodicAdvList_T;


/** @brief Structure for setting the privacy mode for a peer device. */
typedef struct HCI_LE_SetPrivacyMode_T
{
    uint8_t             peerIdentifyAddrType;                              /**< Type of the peer's identity address. */
    uint8_t             peerIdentifyAddr[HCI_BD_ADDRESS_LEN];              /**< Identity address of the peer device. */
    uint8_t             privacyMode;                                       /**< Privacy mode to be used with the peer device. */
} HCI_LE_SetPrivacyMode_T;


/** @brief Structure for enabling or disabling reports for periodic advertising. */
typedef struct HCI_LE_SetPeriodicAdvReceiveEnable_T
{
    uint16_t            syncHandle;                                        /**< Handle identifying the periodic advertising train. */
    uint8_t             enable;                                            /**< Flag to enable or disable reports. */
} HCI_LE_SetPeriodicAdvReceiveEnable_T;


/** @brief Structure for reading the transmit power level for a given PHY. */
typedef struct HCI_LE_EnhancedReadTransmitPowerLevel_T
{
    uint16_t            connHandle;                                        /**< Handle of the connection for which the transmit power level is being read. */
    uint8_t             phy;                                               /**< PHY for which the transmit power level is being read. */
} HCI_LE_EnhancedReadTransmitPowerLevel_T;


/** @brief Structure for parameters of the "Read Remote Transmit Power Level" command. */
typedef struct HCI_LE_ReadRemoteTransmitPowerLevel_T
{
    uint16_t            connHandle;                                        /**< Connection handle for the target connection. */
    uint8_t             phy;                                               /**< PHY for which the transmit power level is to be read. */
} HCI_LE_ReadRemoteTransmitPowerLevel_T;


/** @brief Structure for parameters of the "Set Transmit Power Reporting Enable" command. */
typedef struct HCI_LE_SetTransmitPowerReportingEnable_T
{
    uint16_t            connHandle;                                        /**< Connection handle for the target connection. */
    uint8_t             localEnable;                                       /**< Enable (1) or disable (0) local transmit power reports. */
    uint8_t             remoteEnable;                                      /**< Enable (1) or disable (0) remote transmit power reports. */
} HCI_LE_SetTransmitPowerReportingEnable_T;


/** @brief Structure for parameters of the "Transmitter Test" (version 4) command. */
typedef struct HCI_LE_TransmitterTestV4_T
{
    uint8_t             txChannel;                                         /**< RF channel for transmitter testing. */
    uint8_t             testDataLen;                                       /**< Length of test packet payload. */
    uint8_t             packetPayload;                                     /**< Content of test packet payload. */
    uint8_t             phy;                                               /**< PHY to be used for the test transmission. */
    uint8_t             cteLen;                                            /**< Length of Constant Tone Extension in test packets. */
    uint8_t             cteType;                                           /**< Type of Constant Tone Extension used in test packets. */
    uint8_t             switchingPatternLen;                               /**< Length of the antenna switching pattern. */
    uint8_t             antennaIds[HCI_LE_TRANSMITTER_SPL_MAX];            /**< Antenna IDs for the switching pattern. */
    int8_t              txPowerLevel;                                      /**< Transmit power level for the test transmission. */
} HCI_LE_TransmitterTestV4_T;


/** @brief Structure for parameters of the "Set Path Loss Reporting Parameters" command. */
typedef struct HCI_LE_SetPathLossReportingParams_T
{
    uint16_t            connHandle;                                        /**< Connection handle for the target connection. */
    uint8_t             highThreshold;                                     /**< Path loss high threshold (in dBm). */
    uint8_t             highHysteresis;                                    /**< Hysteresis for the high threshold (in dBm). */
    uint8_t             lowThreshold;                                      /**< Path loss low threshold (in dBm). */
    uint8_t             lowHysteresis;                                     /**< Hysteresis for the low threshold (in dBm). */
    uint16_t            minTimeSpent;                                      /**< Minimum time (in connection events) before generating an event after crossing threshold. */
} HCI_LE_SetPathLossReportingParams_T;


/** @brief Structure for parameters of the "Set Path Loss Reporting Enable" command. */
typedef struct HCI_LE_SetPathLossReportingEnable_T
{
    uint16_t            connHandle;                                        /**< Connection handle for the target connection. */
    uint8_t             reportEnable;                                      /**< Enable (1) or disable (0) path loss reporting. */
} HCI_LE_SetPathLossReportingEnable_T;


/** @brief Structure for parameters of the "Set Default Subrate" command. */
typedef struct HCI_LE_SetDefaultSubrate_T
{
    uint16_t            subrateMin;                                        /**< Minimum subrate value. */
    uint16_t            subrateMax;                                        /**< Maximum subrate value. */
    uint16_t            maxLatency;                                        /**< Maximum allowed latency. */
    uint16_t            continuationNum;                                   /**< Number of continuation packets. */
    uint16_t            supervisionTimeout;                                /**< Supervision timeout. */
}HCI_LE_SetDefaultSubrate_T;


/** @brief Structure for parameters of the "Subrate Request" command. */
typedef struct HCI_LE_SubrateRequest_T
{
    uint16_t            connHandle;                                        /**< Connection handle for the target connection. */
    uint16_t            subrateMin;                                        /**< Minimum subrate value. */
    uint16_t            subrateMax;                                        /**< Maximum subrate value. */
    uint16_t            maxLatency;                                        /**< Maximum allowed latency. */
    uint16_t            continuationNum;                                   /**< Number of continuation packets. */
    uint16_t            supervisionTimeout;                                /**< Supervision timeout. */
}HCI_LE_SubrateRequest_T;

/** @brief Structure for parameters of the "Set Host Feature" command. */
typedef struct HCI_LE_SetHostFeature_T
{
    uint8_t             bitNumber;                                         /**< Bit position in the FeatureSet. */
    uint8_t             bitValue;                                          /**< Enable (1) or disable (0) the bit in the FeatureSet. */
} HCI_LE_SetHostFeature_T;


/** @brief Structure for parameters of the "Set Data Related Address Changes" command. */
typedef struct HCI_LE_SetDataRelatedAddrChange_T
{
    uint8_t             advHandle;                                         /**< Handle identifying the advertising set. */
    uint8_t             changeReasons;                                     /**< Reasons for changing the address. */
} HCI_LE_SetDataRelatedAddrChange_T;

/** @brief Structure for the "Command Complete" event without additional parameters. */
typedef struct HCI_CC_Status_T
{
    uint8_t             status;                                            /**< Status returned for the completed command. */
} HCI_CC_Status_T;

/** @brief Structure for the "Read AFH Channel Assessment Mode" command complete event. */
typedef struct HCI_CC_ReadAfhChannelAssessMode_T
{
    uint8_t             status;                                            /**< Status returned for the completed command. */
    uint8_t             AfhChannelAssessMode;                              /**< AFH Channel Assessment Mode is enabled (1) or disabled (0). */
} HCI_CC_ReadAfhChannelAssessMode_T;

/** @brief Structure for the "Read Authenticated Payload Timeout" command complete event. */
typedef struct HCI_CC_ReadAuthenticatedPayloadTimeout_T

{
    uint8_t             status;                                            /**< Status returned for the completed command. */
    uint16_t            connHandle;                                        /**< Connection handle for the target connection. */
    uint16_t            authenticatedPayloadTimeout;                       /**< Authenticated payload timeout (in 10 ms units). */
} HCI_CC_ReadAuthenticatedPayloadTimeout_T;


/** @brief Structure for the "Write Authenticated Payload Timeout" command complete event. */
typedef struct HCI_CC_WriteAuthenticatedPayloadTimeout_T
{
    uint8_t             status;                                            /**< Status returned for the completed command. */
    uint16_t            connHandle;                                        /**< Connection handle for the target connection. */
} HCI_CC_WriteAuthenticatedPayloadTimeout_T;


/** @brief Structure for the "Read BD_ADDR" command complete event. */
typedef struct HCI_CC_ReadBdAddr_T
{
    uint8_t             status;                                            /**< Status returned for the completed command. */
    uint8_t             bdAddr[HCI_BD_ADDRESS_LEN];                        /**< Bluetooth Device Address of the device. */
} HCI_CC_ReadBdAddr_T;


/** @brief Structure for the Read RSSI Command Complete event parameters. */
typedef struct HCI_CC_ReadRssi_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    uint16_t            connHandle;                                        /**< Connection handle for the associated connection. */
    int8_t              rssi;                                              /**< Received Signal Strength Indicator (RSSI) value. */
} HCI_CC_ReadRssi_T;


/** @brief Structure for the Read Channel Map Command Complete event parameters. */
typedef struct HCI_CC_LE_ReadChannelMap_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    uint16_t            connHandle;                                        /**< Connection handle for the associated connection. */
    uint8_t             channelMap[5];                                     /**< Array representing the channel map with 37 1-bit fields. */
} HCI_CC_LE_ReadChannelMap_T;


/** @brief Structure for the Long Term Key Request Reply Command Complete event parameters. */
typedef struct HCI_CC_LE_LtkReqReply_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    uint16_t            connHandle;                                        /**< Connection handle for the associated connection. */
} HCI_CC_LE_LtkReqReply_T;


/** @brief Structure for the Long Term Key Request Negative Reply Command Complete event parameters. */
typedef struct HCI_CC_LE_LtkReqNegativeReply_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    uint16_t            connHandle;                                        /**< Connection handle for the associated connection. */
} HCI_CC_LE_LtkReqNegativeReply_T;


/** @brief Structure for the Test End Command Complete event parameters. */
typedef struct HCI_CC_LE_TestEnd_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    uint16_t            numPacket;                                         /**< Number of packets received during the test. */
} HCI_CC_LE_TestEnd_T;


/** @brief Structure for the Remote Connection Parameters Request Reply Command Complete event parameters. */
typedef struct HCI_CC_LE_RemoteConnParamReqReply_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    uint16_t            connHandle;                                        /**< Connection handle for the associated connection. */
} HCI_CC_LE_RemoteConnParamReqReply_T;


/** @brief Structure for the Remote Connection Parameters Request Negative Reply Command Complete event parameters. */
typedef struct HCI_CC_LE_RemoteConnParamReqNegReply_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    uint16_t            connHandle;                                        /**< Connection handle for the associated connection. */
} HCI_CC_LE_RemoteConnParamReqNegReply_T;


/** @brief Structure for the Set Data Length Command Complete event parameters. */
typedef struct HCI_CC_LE_SetDataLength_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    uint16_t            connHandle;                                        /**< Connection handle for the associated connection. */
} HCI_CC_LE_SetDataLength_T;


/** @brief Structure for the Read PHY Command Complete event parameters. */
typedef struct HCI_CC_LE_ReadPhy_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    uint16_t            connHandle;                                        /**< Connection handle for the associated connection. */
    uint8_t             txPhy;                                             /**< Transmitter PHY for the connection. */
    uint8_t             rxPhy;                                             /**< Receiver PHY for the connection. */
} HCI_CC_LE_ReadPhy_T;


/** @brief Structure for the Set Extended Advertising Parameters Command Complete event parameters. */
typedef struct HCI_CC_LE_SetExtAdvertisingParameters_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    int8_t              selectTxPower;                                     /**< Selected transmit power level. */
} HCI_CC_LE_SetExtAdvertisingParameters_T;


/** @brief Structure for the Read Transmit Power Command Complete event parameters. */
typedef struct HCI_CC_LE_ReadTransmitPower_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    int8_t              minTxPower;                                        /**< Minimum transmit power level. */
    int8_t              maxTxPower;                                        /**< Maximum transmit power level. */
} HCI_CC_LE_ReadTransmitPower_T;


/** @brief Structure for the parameters of the LE Enhanced Read Transmit Power Command Complete event. */
typedef struct HCI_CC_LE_EnhancedReadTransmitPower_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    uint16_t            connHandle;                                        /**< Handle of the connection for which the command was executed. */
    uint8_t             phy;                                               /**< PHY for which the transmit power is being reported. */
    uint8_t             currentTxPowerLevel;                               /**< Current transmit power level in dBm. */
    uint8_t             maxTxPowerLevel;                                   /**< Maximum transmit power level in dBm. */
} HCI_CC_LE_EnhancedReadTransmitPower_T;


/** @brief Structure for the parameters of the LE Set Path Loss Reporting Parameters Command Complete event. */
typedef struct HCI_CC_LE_SetPathLossReportingParams_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    uint16_t            connHandle;                                        /**< Handle of the connection for which the command was executed. */
} HCI_CC_LE_SetPathLossReportingParams_T;


/** @brief Structure for the parameters of the LE Set Path Loss Reporting Enable Command Complete event. */
typedef struct HCI_CC_LE_SetPathLossReportingEnable_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    uint16_t            connHandle;                                        /**< Handle of the connection for which the command was executed. */
} HCI_CC_LE_SetPathLossReportingEnable_T;


/** @brief Structure for the parameters of the LE Set Transmit Power Reporting Enable Command Complete event. */
typedef struct HCI_CC_LE_SetTransmitPowerReportingEnable_T
{
    uint8_t             status;                                            /**< Status of the command execution. */
    uint16_t            connHandle;                                        /**< Handle of the connection for which the command was executed. */
} HCI_CC_LE_SetTransmitPowerReportingEnable_T;


/** @brief Structure indicating that a connection has been terminated. */
typedef struct HCI_EvtDisconnect_T
{
    uint8_t             status;                                            /**< Status of the disconnection event. */
    uint16_t            connHandle;                                        /**< Handle of the terminated connection. */
    uint8_t             reason;                                            /**< Reason code for the disconnection. */
} HCI_EvtDisconnect_T;


/** @brief Structure indicating the completion of an encryption mode change. */
typedef struct HCI_EvtEncryptChange_T
{
    uint8_t             status;                                            /**< Status of the encryption change event. */
    uint16_t            connHandle;                                        /**< Handle of the connection for which encryption mode has changed. */
    uint8_t             encEnable;                                         /**< Indicates whether encryption is enabled (1) or disabled (0). */
} HCI_EvtEncryptChange_T;


/** @brief Structure indicating the completion of obtaining version information from the remote Controller. */
typedef struct HCI_EvtReadRemoteVer_T
{
    uint8_t             status;                                            /**< Status of the remote version information request. */
    uint16_t            connHandle;                                        /**< Handle of the connection for which version information was requested. */
    uint8_t             version;                                           /**< Version of the LMP in the remote controller. */
    uint16_t            manuName;                                          /**< Manufacturer name of the remote controller. */
    uint16_t            subVersion;                                        /**< Subversion of the LMP in the remote controller. */
} HCI_EvtReadRemoteVer_T;


/** @brief Structure indicating the number of completed packets for a specific connection. */
typedef struct HCI_CompletePacket_T
{
    uint16_t            connHandle;                                        /**< Handle of the connection for which packets have been completed. */
    uint16_t            numPackets;                                        /**< Number of completed packets. */
} HCI_CompletePacket_T;


/** @brief Structure indicating to the Host the number of HCI Data packets completed for each Connection_Handle since the last HCI_NBR_OF_COMPLETED_PACKETS event. */
typedef struct HCI_EvtNumOfCompletePacket_T
{
    uint8_t                 numHandles;                                    /**< Number of connection handles included in this event. */
    HCI_CompletePacket_T    completePacket[HCI_MAX_NUM_CONN_HANDLE];       /**< Array of structures containing the number of completed packets for each connection handle. */
} HCI_EvtNumOfCompletePacket_T;


/** @brief Structure indicating that the encryption key has been refreshed. */
typedef struct HCI_EvtKeyRefreshComplete_T
{
    uint8_t             status;                                            /**< Status of the key refresh event. */
    uint16_t            connHandle;                                        /**< Handle of the connection for which the key has been refreshed. */
} HCI_EvtKeyRefreshComplete_T;


/** @brief Structure indicating to the host that a new connection has been established. */
typedef struct HCI_EvtLeConnect_T
{
    uint8_t             status;                                            /**< Status of the connection establishment. */
    uint16_t            connHandle;                                        /**< Handle of the new connection. */
    uint8_t             role;                                              /**< Role in the connection: Central (0) or Peripheral (1). */
    uint8_t             peerAddrType;                                      /**< Type of the remote peer's Bluetooth address. */
    uint8_t             peerAddr[HCI_BD_ADDRESS_LEN];                      /**< Remote peer's Bluetooth address. */
    uint16_t            connInterval;                                      /**< Connection interval used on this connection, in 1.25 ms units. */
    uint16_t            connLatency;                                       /**< Connection latency in terms of the number of connection events. */
    uint16_t            supervisionTimeout;                                /**< Supervision timeout for the connection, in 10 ms units. */
    uint8_t             centralClkAcc;                                     /**< Clock accuracy of the central device. */
} HCI_EvtLeConnect_T;


/** @brief Structure containing details of an advertising report. */
typedef struct HCI_AdvReportDetails_T
{
    uint8_t             eventType;                                         /**< Type of advertising event. */
    uint8_t             addrType;                                          /**< Type of the advertiser's address. */
    uint8_t             addr[HCI_BD_ADDRESS_LEN];                          /**< Advertiser's Bluetooth device address. */
    uint8_t             advLength;                                         /**< Length of the advertising data. */
    uint8_t             advData[HCI_MAX_ADV_LENGTH];                       /**< Buffer containing the advertising data. */
    int8_t              rssi;                                              /**< Received Signal Strength Indication for the advertisement. */
} HCI_AdvReportDetails_T;


/** @brief Structure for LE advertising reports, indicating that one or more Bluetooth devices have been discovered. */
typedef struct HCI_EvtLeAdvReport_T
{
    uint8_t                 numReports;                                    /**< Number of advertising reports included in the event. */
    HCI_AdvReportDetails_T  reports[HCI_MAX_ADV_REPORTS];                  /**< Array of advertising report details. */
} HCI_EvtLeAdvReport_T;


/** @brief Structure indicating the completion of a connection parameter update process. */
typedef struct HCI_EvtLeConnParamUpdate_T
{
    uint8_t             status;                                            /**< Status of the update process (success or error code). */
    uint16_t            connHandle;                                        /**< Handle identifying the connection. */
    uint16_t            connInterval;                                      /**< Updated connection interval. */
    uint16_t            connLatency;                                       /**< Updated connection latency. */
    uint16_t            supervisionTimeout;                                /**< Updated supervision timeout. */
} HCI_EvtLeConnParamUpdate_T;


/** @brief Structure indicating the completion of reading the LE features from a remote Bluetooth device. */
typedef struct HCI_EvtLeReadRemoteFeature_T
{
    uint8_t             status;                                            /**< Status of the read operation (success or error code). */
    uint16_t            connHandle;                                        /**< Handle identifying the connection. */
    uint8_t             leFeatures[HCI_FEATURES_BITMASK_LENGTH];           /**< Bitmask of supported LE features. */
} HCI_EvtLeReadRemoteFeature_T;


/** @brief Structure indicating a request for the Long Term Key (LTK) to encrypt or re-encrypt a link. */
typedef struct HCI_EvtLeLongTermKeyReq_T
{
    uint16_t            connHandle;                                        /**< Handle identifying the connection. */
    uint8_t             randomNum[HCI_LTK_RANDOM_SIZE];                    /**< Random number used in the encryption process. */
    uint16_t            encDiver;                                          /**< Encrypted diversifier. */
} HCI_EvtLeLongTermKeyReq_T;


/** @brief Structure indicating a remote device's request to change connection parameters. */
typedef struct HCI_EvtLeRemoteConnParamsReq_T
{
    uint16_t            connHandle;                                        /**< Handle identifying the connection. */
    uint16_t            intervalMin;                                       /**< Minimum requested value for the connection interval. */
    uint16_t            intervalMax;                                       /**< Maximum requested value for the connection interval. */
    uint16_t            latency;                                           /**< Requested connection latency. */
    uint16_t            supervisionTimeout;                                /**< Requested supervision timeout. */
} HCI_EvtLeRemoteConnParamsReq_T;


/** @brief Structure notifying the host of changes in data length or transmission time for LL Data PDUs. */
typedef struct HCI_EvtLeDataLengthChange_T
{
    uint16_t            connHandle;                                        /**< Handle identifying the connection. */
    uint16_t            maxTxOctects;                                      /**< Maximum number of payload octets for outgoing LL Data PDUs. */
    uint16_t            maxTxTime;                                         /**< Maximum transmission time for outgoing LL Data PDUs. */
    uint16_t            maxRxOctets;                                       /**< Maximum number of payload octets for incoming LL Data PDUs. */
    uint16_t            maxRxTime;                                         /**< Maximum transmission time for incoming LL Data PDUs. */
} HCI_EvtLeDataLengthChange_T;


/** @brief Structure representing an enhanced connection complete event. */
typedef struct HCI_EvtLeEnhanceConnect_T
{
    uint8_t             status;                                            /**< Connection status. */
    uint16_t            connHandle;                                        /**< Handle for the new connection. */
    uint8_t             role;                                              /**< Role in the connection: central or peripheral. */
    uint8_t             peerAddrType;                                      /**< Type of the peer's Bluetooth address. */
    uint8_t             peerAddr[HCI_BD_ADDRESS_LEN];                      /**< Peer's Bluetooth address. */
    uint8_t             localRpa[HCI_BD_ADDRESS_LEN];                      /**< Local device's Resolvable Private Address (RPA). */
    uint8_t             peerRpa[HCI_BD_ADDRESS_LEN];                       /**< Peer device's Resolvable Private Address (RPA). */
    uint16_t            connInterval;                                      /**< Connection interval. */
    uint16_t            connLatency;                                       /**< Connection latency as the number of connection events. */
    uint16_t            supervisionTimeout;                                /**< Supervision timeout for the connection. */
    uint8_t             centralClkAcc;                                     /**< Accuracy of the central's clock. */
} HCI_EvtLeEnhanceConnect_T;


/** @brief Structure representing the details of a direct advertising report. */
typedef struct HCI_DirectAdvReportDetails_T
{
    uint8_t             eventType;                                         /**< Type of advertising event. */
    uint8_t             addrType;                                          /**< Address type of the advertising device. */
    uint8_t             addr[HCI_BD_ADDRESS_LEN];                          /**< Bluetooth address of the advertising device. */
    uint8_t             directAddrType;                                    /**< Address type used for direct advertising. */
    uint8_t             directAddr[HCI_BD_ADDRESS_LEN];                    /**< Bluetooth address used for direct advertising. */
    int8_t              rssi;                                              /**< Received Signal Strength Indication (RSSI). */
} HCI_DirectAdvReportDetails_T;


/** @brief Structure representing a direct advertising report event. */
typedef struct HCI_EvtLeDirectAdvReport_T
{
    uint8_t                         numReports;                            /**< Number of advertising reports included in the event. */
    HCI_DirectAdvReportDetails_T    reports[HCI_MAX_ADV_REPORTS];          /**< Array of advertising reports. */
} HCI_EvtLeDirectAdvReport_T;


/** @brief Structure representing a PHY update complete event. */
typedef struct HCI_EvtLePhyUpdate_T
{
    uint8_t             status;                                            /**< Status of the PHY update process. */
    uint16_t            connHandle;                                        /**< Handle for the connection related to the PHY update. */
    uint8_t             txPhy;                                             /**< Transmitter PHY for the connection. */
    uint8_t             rxPhy;                                             /**< Receiver PHY for the connection. */
} HCI_EvtLePhyUpdate_T;


/** @brief Structure representing the details of an extended advertising report. */
typedef struct HCI_ExtAdvReportDetails_T
{
    uint16_t            eventType;                                         /**< Type of advertising event. */
    uint8_t             addrType;                                          /**< Address type of the advertising device. */
    uint8_t             addr[HCI_BD_ADDRESS_LEN];                          /**< Bluetooth address of the advertising device. */
    uint8_t             priPhy;                                            /**< Primary advertising PHY. */
    uint8_t             secPhy;                                            /**< Secondary advertising PHY. */
    uint8_t             sid;                                               /**< Advertising SID subfield value. */
    int8_t              txPower;                                           /**< Transmit power of the advertising packet. */
    int8_t              rssi;                                              /**< Received Signal Strength Indication (RSSI). */
    uint16_t            periodicAdvInterval;                               /**< Interval for periodic advertising. */
    uint8_t             directAddrType;                                    /**< Address type for direct advertising. */
    uint8_t             directAddr[HCI_BD_ADDRESS_LEN];                    /**< Bluetooth address for direct advertising. */
    uint8_t             advLength;                                         /**< Length of the advertising data. */
    uint8_t             advData[HCI_EVT_MAX_EXTENDED_ADVERTISING_DATA_LENGTH]; /**< Advertising data. */
} HCI_ExtAdvReportDetails_T;


/** @brief Structure representing an extended advertising report event. */
typedef struct HCI_EvtLeExtAdvReport_T
{
    uint8_t                     numReports;                                /**< Number of advertising reports included in the event. */
    HCI_ExtAdvReportDetails_T   reports[HCI_MAX_ADV_REPORTS];              /**< Array of advertising reports. */
} HCI_EvtLeExtAdvReport_T;


/** @brief Structure representing a periodic advertising sync established event. */
typedef struct HCI_EvtLePeriodicAdvSyncEst_T
{
    uint8_t             status;                                            /**< Status of the periodic advertising sync establishment. */
    uint16_t            syncHandle;                                        /**< Handle identifying the periodic advertising train. */
    uint8_t             advSid;                                            /**< Advertising SID subfield value. */
    uint8_t             advAddrType;                                       /**< Advertising address type. */
    uint8_t             advAddr[HCI_BD_ADDRESS_LEN];                       /**< Advertising Bluetooth address. */
    uint8_t             advPhy;                                            /**< Advertiser PHY. */
    uint16_t            periodicAdvInterval;                               /**< Periodic advertising interval. */
    uint8_t             advClkAccuracy;                                    /**< Advertiser clock accuracy. */
} HCI_EvtLePeriodicAdvSyncEst_T;


/** @brief Structure representing a periodic advertising report event. */
typedef struct HCI_EvtLePeriodicAdvReport_T
{
    uint16_t            syncHandle;                                        /**< Handle identifying the periodic advertising train. */
    uint8_t             txPower;                                           /**< Transmit power of the advertising packet. */
    int8_t              rssi;                                              /**< Received Signal Strength Indication (RSSI). */
    uint8_t             cteType;                                           /**< Constant Tone Extension type. */
    uint8_t             dataStatus;                                        /**< Status of the received advertising data. */
    uint8_t             advLength;                                         /**< Length of the advertising data. */
    uint8_t             advData[HCI_EVT_MAX_PERIODIC_ADVERTISING_DATA_LENGTH]; /**< Periodic advertising data. */
} HCI_EvtLePeriodicAdvReport_T;


/** @brief Structure representing a periodic advertising sync lost event. */
typedef struct HCI_EvtLePeriodicAdvSyncLost_T
{
    uint16_t            syncHandle;                                        /**< Handle identifying the lost periodic advertising train. */
} HCI_EvtLePeriodicAdvSyncLost_T;


/** @brief Structure representing an advertising set terminated event. */
typedef struct HCI_EvtLeAdvSetTerminated_T
{
    uint8_t             status;                                            /**< Status of the advertising set termination. */
    uint8_t             advHandle;                                         /**< Handle identifying the advertising set. */
    uint16_t            connHandle;                                        /**< Handle for the connection related to the advertising set. */
    uint8_t             numComplExtAdvEvents;                              /**< Number of completed extended advertising events. */
} HCI_EvtLeAdvSetTerminated_T;


/** @brief Structure representing a scan request received event. */
typedef struct HCI_EvtLeScanReqReceived_T
{
    uint8_t             advHandle;                                         /**< Handle identifying the advertising set. */
    uint8_t             scannerAddrType;                                   /**< Scanner address type. */
    uint8_t             scannerAddr[HCI_BD_ADDRESS_LEN];                   /**< Scanner Bluetooth address. */
} HCI_EvtLeScanReqReceived_T;


/** @brief Structure representing a channel selection algorithm event. */
typedef struct HCI_EvtLeChannelSelectAlgorithm_T
{
    uint16_t            connHandle;                                        /**< Handle for the connection related to the channel selection. */
    uint8_t             channelSelectAlgorithm;                            /**< Channel selection algorithm used. */
} HCI_EvtLeChannelSelectAlgorithm_T;


/** @brief Structure representing a transmit power reporting event. */
typedef struct HCI_EvtLeTxPowerReporting_T
{
    uint8_t             status;                                            /**< Status of the transmit power reporting process. */
    uint16_t            connHandle;                                        /**< Handle for the connection related to the transmit power. */
    uint8_t             reason;                                            /**< Reason for the transmit power change. */
    uint8_t             phy;                                               /**< PHY type for which the power level is reported. */
    int8_t              txPowerLevel;                                      /**< Current transmit power level. */
    uint8_t             txPowerLevelFlag;                                  /**< Flags indicating if the power level has reached minimum or maximum. */
    int8_t              delta;                                             /**< Change in transmit power level. */
} HCI_EvtLeTxPowerReporting_T;


/** @brief Structure representing a path loss threshold event. */
typedef struct HCI_EvtLePathLossThreshold_T
{
    uint16_t            connHandle;                                        /**< Handle for the connection related to the path loss. */
    uint8_t             currentPathLoss;                                   /**< Current path loss value. */
    uint8_t             zoneEntered;                                       /**< Zone entered based on path loss thresholds. */
} HCI_EvtLePathLossThreshold_T;


/** @brief Structure representing an authenticated payload timeout event. */
typedef struct HCI_EvtAuthPayloadTimeout_T
{
    uint16_t            connHandle;                                        /**< Handle for the connection related to the payload timeout. */
} HCI_EvtAuthPayloadTimeout_T;


/** @brief Structure representing a subrate change event. */
typedef struct HCI_EvtLeSubrateChange_T
{
    uint8_t             status;                                 /**< Status of the subrate change event. See @ref GAP_STATUS for possible values. */
    uint16_t            connHandle;                             /**< Connection handle for the connection related to this subrate change. */
    uint16_t            subrateFactor;                          /**< New subrate factor applied to the specified underlying connection interval. */
    uint16_t            periLatency;                            /**< New Peripheral latency for the connection in number of subrated connection events. */
    uint16_t            continuationNum;                        /**< Number of underlying connection events to remain active after a packet containing 
                                                                        a Link Layer PDU with a non-zero Length field is sent or received. */
    uint16_t            supervisionTimeout;                     /**< New supervision timeout for this connection. */
} HCI_EvtLeSubrateChange_T;


/** @} */ //HOST_HCI_STRUCTS

/** @} */ // end of HOST_HCI

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif//HOST_HCI_DEFS_H

