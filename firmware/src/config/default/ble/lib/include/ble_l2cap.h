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
  BLE L2CAP Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_l2cap.h

  Summary:
    This header file provides the BLE L2CAP API for application developers.

  Description:
    This header file declares the BLE L2CAP functions and events available to
    application developers. The "BLE_L2CAP_Init" function must be called within
    the "APP_Initialize" function to set up this module within the system.
 *******************************************************************************/
#ifndef BLE_L2CAP_H
#define BLE_L2CAP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/**
 * @defgroup BLE_L2CAP Logic Link Control And Adaption Protocol (L2CAP)
 * @brief Defines the interface for the BLE L2CAP functions provided by the BLE Library.
 * @note This file includes definitions and prototypes for the BLE L2CAP stack layer,
 *       providing an API for application-level interaction with the BLE stack.
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**
 * @addtogroup BLE_L2CAP_DEFINES Defines
 * @{
 */
 
 
/**
 * @defgroup BLE_L2CAP_SPSM_RANGE L2CAP SPSM dynamic range
 * @brief Defines the range for Simplified Protocol/Service Multiplexer (SPSM) values used in dynamic allocation.
 * @{
 */
#define BLE_L2CAP_SPSM_DYNAMIC_MIN                  (0x0080U)          /**< Minimum value for dynamically allocated SPSM. */
#define BLE_L2CAP_SPSM_DYNAMIC_MAX                  (0x00ffU)          /**< Maximum value for dynamically allocated SPSM. */
/** @} */


/**@defgroup BLE_L2CAP_PDU_SIZE L2CAP maximum PDU size
 * @brief Defines the maximum size for Protocol Data Units (PDU) in bytes.
 * @{ */
#define BLE_L2CAP_MAX_PDU_SIZE                      (1024U)            /**< Maximum size of a L2CAP PDU in bytes. */
/** @} */


/**
 * @defgroup BLE_L2CAP_MTU_SIZE L2CAP minimum MTU size
 * @brief Defines the minimum size for the L2CAP Maximum Transmission Unit (MTU) in bytes.
 * @{
 */
#define BLE_L2CAP_MIN_MTU_SIZE                      (23U)              /**< Minimum size of a L2CAP MTU in bytes. */
/** @} */


/**
 * @defgroup BLE_L2CAP_MPS_SIZE L2CAP minimum MPS size
 * @brief Defines the minimum size for the L2CAP Maximum PDU Payload Size (MPS) in bytes.
 * @{
 */
#define BLE_L2CAP_MIN_MPS_SIZE                      (23U)              /**< Minimum size of a L2CAP MPS in bytes. */
/** @} */


/**
 * @defgroup BLE_L2CAP_SDU_SIZE L2CAP maximum SDU size
 * @brief Defines the maximum size for Service Data Units (SDU) in bytes.
 * @{
 */
#define BLE_L2CAP_MAX_SDU_SIZE                      (739U)             /**< Maximum size of a L2CAP SDU in bytes.  */
/** @} */


/**
 * @defgroup BLE_L2CAP_CB_SPSM_NUM L2CAP maximum SPSM number
 * @brief Defines the maximum number of Service Protocol/Service Multiplexer (SPSM) identifiers that can be registered for credit-based channels.
 * @{
 */
#define BLE_L2CAP_MAX_CB_SPSM_NUM                   (2U)               /**< Maximum number of SPSM identifiers for credit-based channels. */
/** @} */


/**
 * @defgroup BLE_L2CAP_CB_NUM L2CAP maximum credit-based channels
 * @brief Defines the maximum number of L2CAP credit-based channels allowed per connection.
 * @{
 */
#define BLE_L2CAP_MAX_CB_NUM                        (0x05U)            /**< Maximum number of L2CAP credit-based channels per connection. */
/** @} */


/**
 * @defgroup BLE_L2CAP_PERMISSION L2CAP permission definitions
 * @brief Defines the permission levels for L2CAP connections.
 * @{
 */
#define BLE_L2CAP_PERMISSION_NONE                   (0x00U)            /**< No permissions required. */
#define BLE_L2CAP_PERMISSION_AUTHEN                 (0x01U)            /**< Authentication and Man-In-The-Middle (MITM) protection required. */
#define BLE_L2CAP_PERMISSION_ENC                    (0x02U)            /**< Encryption required without MITM protection. */
#define BLE_L2CAP_PERMISSION_AUTHEN_SC              (0x03U)            /**< Secure Connections with encryption and MITM protection required. */
/** @} */


/**
 * @defgroup BLE_L2CAP_CONN_PARAM_RSP_RESULT L2CAP connection parameter update result codes
 * @brief Defines the result codes for L2CAP connection parameter update responses.
 * @{
 */
#define BLE_L2CAP_CONN_PARAMS_ACCEPT                (0x0000U)          /**< Indicates that the requested connection parameters were accepted. */
#define BLE_L2CAP_CONN_PARAMS_REJECT                (0x0001U)          /**< Indicates that the requested connection parameters were rejected. */
/** @} */




/**@defgroup BLE_L2CAP_ERR_REASON L2CAP error enountered reason
 * @brief Defines the reason codes for encountered L2CAP error.
 * @{ */
#define BLE_L2CAP_ERR_INVALID_PACKET                (0x0000U)          /**< Invalid Packet received. */
#define BLE_L2CAP_ERR_UNSUPP_SPSM                   (0x0001U)          /**< SPSM not supported. */
/** @} */

/**
 * @defgroup BLE_L2CAP_CB_CONN_RSP_RESULT L2CAP credit-based connection response result codes
 * @brief Defines the result codes for L2CAP credit-based connection response packets.
 * @{
 */
#define BLE_L2CAP_RES_CONN_SUCCESSFUL               (0x0000U)          /**< Connection successfully established. */
#define BLE_L2CAP_RES_CONN_SPSM_NOT_SUPPORTED       (0x0002U)          /**< Connection refused due to unsupported SPSM. */
#define BLE_L2CAP_RES_CONN_NO_RESOURCES             (0x0004U)          /**< Connection refused due to lack of resources. */
#define BLE_L2CAP_RES_CONN_INSUFF_AUTHENTICATION    (0x0005U)          /**< Connection refused due to insufficient authentication. */
#define BLE_L2CAP_RES_CONN_INSUFF_AUTHORIZATION     (0x0006U)          /**< Connection refused due to insufficient authorization. */
#define BLE_L2CAP_RES_CONN_INSUFF_ENC_KEY_SIZE      (0x0007U)          /**< Connection refused due to insufficient encryption key size. */
#define BLE_L2CAP_RES_CONN_INSUFF_ENC               (0x0008U)          /**< Connection refused due to insufficient encryption. */
#define BLE_L2CAP_RES_CONN_INVALID_SOURCE_CID       (0x0009U)          /**< Connection refused due to invalid Source Channel Identifier (CID). */
#define BLE_L2CAP_RES_CONN_SOURCE_CID_ALLOCATED     (0x000AU)          /**< Connection refused because the Source CID is already allocated. */
#define BLE_L2CAP_RES_CONN_UNACCEPT_PARAMS          (0x000BU)          /**< Connection refused due to unacceptable parameters. */
#define BLE_L2CAP_RES_CONN_REJECT                   (0xFFFFU)          /**< Generic connection rejection. */
/** @} */

/** @} */ //BLE_L2CAP_DEFINES


/**
 * @addtogroup BLE_L2CAP_ENUMS Enumerations
 * @{
 */

/** @brief Enumeration of L2CAP events delivered to the application from the BLE Stack. */
typedef enum BLE_L2CAP_EventId_T
{
    BLE_L2CAP_EVT_CONN_PARA_UPD_REQ = 0x00,                           /**< Event indicating a request to update connection parameters has been received. 
                                                                           Refer to @ref BLE_L2CAP_EvtConnParamUpdateReq_T for details of the event payload. */
    BLE_L2CAP_EVT_CONN_PARA_UPD_RSP,                                  /**< Event indicating a response to the connection parameter update request has been received. 
                                                                           Refer to @ref BLE_L2CAP_EvtConnParamUpdateRsp_T for details of the event payload. */
    BLE_L2CAP_EVT_CB_CONN_IND,                                        /**< Event indicating that a credit-based L2CAP connection has been established. 
                                                                           Refer to @ref BLE_L2CAP_EvtCbConnInd_T for details of the event payload. */
    BLE_L2CAP_EVT_CB_CONN_FAIL_IND,                                   /**< Event indicating that an attempt to establish a credit-based L2CAP connection has failed. 
                                                                           Refer to @ref BLE_L2CAP_EvtCbConnFailInd_T for details of the event payload. */
    BLE_L2CAP_EVT_CB_SDU_IND,                                         /**< Event indicating that a Service Data Unit (SDU) for a credit-based L2CAP connection has been received. 
                                                                           Refer to @ref BLE_L2CAP_EvtCbSduInd_T for details of the event payload. */
    BLE_L2CAP_EVT_CB_ADD_CREDITS_IND,                                 /**< Event indicating that additional credits for a credit-based L2CAP connection have been received. 
                                                                           Refer to @ref BLE_L2CAP_EvtCbAddCreditsInd_T for details of the event payload. */
    BLE_L2CAP_EVT_CB_DISC_IND,                                        /**< Event indicating that a disconnect request for a credit-based L2CAP connection has been received. 
                                                                           Refer to @ref BLE_L2CAP_EvtCbDiscInd_T for details of the event payload. */
    BLE_L2CAP_EVT_ERR_IND,                                            /**< Event indicating that a error handling for an error has been encountered.
                                                                           Refer to @ref BLE_L2CAP_EvtErrInd_T for details of the event payload. */
    BLE_L2CAP_EVT_END                                                 /**< End of BLE L2CAP event enumeration. */
}BLE_L2CAP_EventId_T;

/** @} */ //BLE_L2CAP_ENUMS

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup BLE_L2CAP_STRUCTS Structures
 * @{
 */
 
/** @brief Structure for @ref BLE_L2CAP_EVT_CONN_PARA_UPD_REQ event.*/
typedef struct BLE_L2CAP_EvtConnParamUpdateReq_T
{
    uint16_t                    connHandle;                            /**< Connection handle associated with this request. */
    uint16_t                    intervalMin;                           /**< Minimum value for the connection interval in units of 1.25ms. */
    uint16_t                    intervalMax;                           /**< Maximum value for the connection interval in units of 1.25ms. */
    uint16_t                    latency;                               /**< Peripheral latency for the connection in number of connection events. */
    uint16_t                    timeout;                               /**< Supervision timeout for the connection in units of 10ms. */
} BLE_L2CAP_EvtConnParamUpdateReq_T;


/** @brief Structure for @ref BLE_L2CAP_EVT_CONN_PARA_UPD_RSP event.*/
typedef struct BLE_L2CAP_EvtConnParamUpdateRsp_T
{
    uint16_t                    connHandle;                            /**< Connection handle associated with this response. */
    uint16_t                    result;                                /**< Result of the connection parameters update process, indicating success or the reason for failure. 
                                                                            See @ref BLE_L2CAP_CONN_PARAM_RSP_RESULT. */
} BLE_L2CAP_EvtConnParamUpdateRsp_T;


/** @brief Structure for @ref BLE_L2CAP_EVT_CB_CONN_IND event.*/
typedef struct BLE_L2CAP_EvtCbConnInd_T
{
    uint8_t                     leL2capId;                             /**< Instance identifier of the L2CAP session. */
    uint16_t                    connHandle;                            /**< Connection handle associated with this indication. */
    uint16_t                    spsm;                                  /**< Service Protocol/Service Multiplexer value for the connection. */
    uint16_t                    remoteMtu;                             /**< Remote device's Maximum Transmission Unit size, in bytes. */
    uint16_t                    remoteMps;                             /**< Remote device's Maximum PDU Payload Size, in bytes. */
    uint16_t                    initialCredits;                        /**< Initial number of credits provided to the remote device. */
    uint16_t                    localCid;                              /**< Local Channel Identifier assigned to this connection. */
    uint16_t                    remoteCid;                             /**< Remote Channel Identifier assigned by the remote device. */
} BLE_L2CAP_EvtCbConnInd_T;


/** @brief Structure for @ref BLE_L2CAP_EVT_CB_CONN_FAIL_IND event.*/
typedef struct BLE_L2CAP_EvtCbConnFailInd_T
{
    uint16_t                    connHandle;                            /**< Connection handle associated with this failure indication. */
    uint16_t                    spsm;                                  /**< Service Protocol/Service Multiplexer value associated with the failed connection. */
    uint16_t                    result;                                /**< Result code indicating the reason for the connection failure. */
} BLE_L2CAP_EvtCbConnFailInd_T;


/** @brief Structure for @ref BLE_L2CAP_EVT_CB_SDU_IND event.*/
typedef struct BLE_L2CAP_EvtCbSduInd_T
{
    uint8_t                     leL2capId;                             /**< Instance identifier of the L2CAP session. */
    uint16_t                    length;                                /**< Length of the Service Data Unit (SDU) payload, in bytes.*/
    uint8_t                     payload[BLE_L2CAP_MAX_PDU_SIZE];       /**< Buffer containing the SDU payload. */
    uint8_t                     frames;                                /**< Number of lower-layer frames that were reassembled to form this complete SDU. */
} BLE_L2CAP_EvtCbSduInd_T;


/** @brief Structure for @ref BLE_L2CAP_EVT_CB_ADD_CREDITS_IND event.*/
typedef struct BLE_L2CAP_EvtCbAddCreditsInd_T
{
    uint8_t                     leL2capId;                             /**< Identifier for the L2CAP session instance. */
    uint16_t                    credits;                               /**< Number of additional credits provided. */
} BLE_L2CAP_EvtCbAddCreditsInd_T;


/** @brief Structure for @ref BLE_L2CAP_EVT_CB_DISC_IND event.*/
typedef struct BLE_L2CAP_EvtCbDiscInd_T
{
    uint8_t                     leL2capId;                             /**< Identifier for the L2CAP session instance that was disconnected. */
} BLE_L2CAP_EvtCbDiscInd_T;

/** @brief Structure for @ref BLE_L2CAP_EVT_ERR_IND event.*/
typedef struct BLE_L2CAP_EvtErrInd_T
{
    uint16_t                    connHandle;                            /**< Connection handle associated with this failure indication.*/
    uint16_t                    reason;                                /**< Reason code indicating the reason for the error encountering. 
                                                                            See @ref BLE_L2CAP_ERR_REASON. */
} BLE_L2CAP_EvtErrInd_T;

/** @brief Union of BLE L2CAP callback event data types. */
typedef union
{
    BLE_L2CAP_EvtConnParamUpdateReq_T        evtConnParamUpdateReq;    /**< Data for the BLE_L2CAP_EVT_CONN_PARA_UPD_REQ event. */
    BLE_L2CAP_EvtConnParamUpdateRsp_T        evtConnParamUpdateRsp;    /**< Data for the BLE_L2CAP_EVT_CONN_PARA_UPD_RSP event. */
    BLE_L2CAP_EvtCbConnInd_T                 evtCbConnInd;             /**< Data for the BLE_L2CAP_EVT_CB_CONN_IND event. */
    BLE_L2CAP_EvtCbConnFailInd_T             evtCbConnFailInd;         /**< Data for the BLE_L2CAP_EVT_CB_CONN_FAIL_IND event. */
    BLE_L2CAP_EvtCbSduInd_T                  evtCbSduInd;              /**< Data for the BLE_L2CAP_EVT_CB_SDU_IND event. */
    BLE_L2CAP_EvtCbAddCreditsInd_T           evtCbAddCreditsInd;       /**< Data for the BLE_L2CAP_EVT_CB_ADD_CREDITS_IND event. */
    BLE_L2CAP_EvtCbDiscInd_T                 evtCbDiscInd;             /**< Data for the BLE_L2CAP_EVT_CB_DISC_IND event. */
    BLE_L2CAP_EvtErrInd_T                    evtErrInd;                /**< Data for the BLE_L2CAP_EVT_ERR_IND event. */
} BLE_L2CAP_EventField_T;


/** @brief BLE L2CAP callback event structure. */
typedef struct  BLE_L2CAP_Event_T
{
    BLE_L2CAP_EventId_T         eventId;                               /**< Identifier for the type of BLE L2CAP event. See @ref BLE_L2CAP_EventId_T. */
    BLE_L2CAP_EventField_T      eventField;                            /**< Union containing the data specific to the event type. See @ref BLE_L2CAP_EventField_T. */
} BLE_L2CAP_Event_T;

/** @} */ //BLE_L2CAP_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

/**
 * @addtogroup BLE_L2CAP_FUNS Functions
 * @{
 */
 
/**
 * @brief Initializes the BLE L2CAP main module.
 *
 * @note  The GAP/SMP must be initialized before this module.
 *
 * @retval MBA_RES_SUCCESS      Successfully initialized the BLE L2CAP main module.
 * @retval MBA_RES_OOM          Internal memory allocation failure occurred.
*/
uint16_t BLE_L2CAP_Init(void);


/**
 * @brief Initializes the BLE L2CAP Credit Based Flow Control module.
 *
 * @note  The GAP/SMP must be initialized before this module.
 *
 * @retval MBA_RES_SUCCESS      Successfully initialize the BLE L2CAP credit based module.
 * @retval MBA_RES_OOM          Internal memory allocation failure occurred.
*/
uint16_t BLE_L2CAP_CbInit(void);


/**
 * @brief Issues a connection parameter update request.
 * @note  This API should only be called when the local device is in the LE peripheral role.
 *
 * @par Events generated
 * @ref BLE_L2CAP_EVT_CONN_PARA_UPD_RSP is generated when a connection parameter update response is received.
 *
 * @param[in] connHandle        Connection handle associated with this connection.
 * @param[in] intervalMin       The minimum value for the connection interval. Refer to @ref BLE_GAP_CP_RANGE for valid ranges.
 * @param[in] intervalMax       The maximum value for the connection interval. Refer to @ref BLE_GAP_CP_RANGE for valid ranges.
 * @param[in] latency           The peripheral latency parameter. Refer to @ref BLE_GAP_CP_RANGE for valid ranges.
 * @param[in] timeout           The connection timeout parameter. Refer to @ref BLE_GAP_CP_RANGE for valid ranges.
 *
 * @retval MBA_RES_SUCCESS      Successfully sent a connection parameters update request.
 * @retval MBA_RES_OOM          Internal memory allocation failure occurred.
 * @retval MBA_RES_NO_RESOURCE  No transmit buffers available for sending L2CAP connection   parameters update request.
 * @retval MBA_RES_FAIL         Failed to send the request due to an L2CAP instance error.
 */
uint16_t BLE_L2CAP_ConnParamUpdateReq(uint16_t connHandle, uint16_t intervalMin, uint16_t intervalMax, uint16_t latency, uint16_t timeout);


/**
 * @brief Responds to a connection parameter update request.
 * @note  This function should be called upon receiving @ref BLE_L2CAP_EVT_CONN_PARA_UPD_REQ.
 *
 * @param[in] connHandle        Connection handle associated with this connection.
 * @param[in] result            Accept or reject the request. See @ref BLE_L2CAP_CONN_PARAM_RSP_RESULT for possible values.
 *
 * @retval MBA_RES_SUCCESS      Successfully sent a connection parameters update response.
 * @retval MBA_RES_OOM          Internal memory allocation failure occurred.
 * @retval MBA_RES_NO_RESOURCE  No transmit buffers available for sending L2CAP connection parameters update response.
 * @retval MBA_RES_FAIL         Failed to send the response due to an L2CAP instance error.
 */
uint16_t BLE_L2CAP_ConnParamUpdateRsp(uint16_t connHandle, uint16_t result);


/**
 * @brief Issues a L2CAP credit-based connection request to establish an L2CAP channel.
 * @note  Before calling this API, @ref BLE_L2CAP_CbRegisterSpsm must be called to register an SPSM.
 *
 * @par Events generated
 * @ref BLE_L2CAP_EVT_CB_CONN_IND is generated when a credit-based connection is successfully established.
 * @ref BLE_L2CAP_EVT_CB_CONN_FAIL_IND is generated when there is a failure to establish a credit-based connection.
 *
 * @param[in] connHandle        Connection handle associated with this connection.
 * @param[in] spsm              The SPSM (Simplified Protocol/Service Multiplexer) value. See the valid range @ref BLE_L2CAP_SPSM_RANGE.
 *
 * @retval MBA_RES_SUCCESS      Successfully issued a connection request.
 * @retval MBA_RES_OOM          Internal memory allocation failure occurred.
 * @retval MBA_RES_NO_RESOURCE  No transmit buffers available for sending connection request.
 */
uint16_t BLE_L2CAP_CbConnReq(uint16_t connHandle, uint16_t spsm);


/**
 * @brief Sends an L2CAP SDU (Service Data Unit) over a credit-based connection channel.
 *
 * @param[in] leL2capId         The L2CAP instance identifier.
 * @param[in] length            The length of the L2CAP SDU. See the maximum size definition @ref BLE_L2CAP_MAX_SDU_SIZE.
 * @param[in] p_payload         Pointer to the L2CAP SDU buffer.
 *
 * @retval MBA_RES_SUCCESS      Successfully sent an L2CAP SDU.
 * @retval MBA_RES_OOM          Internal memory allocation failure occurred.
 * @retval MBA_RES_NO_RESOURCE  No transmit buffers available for sending L2CAP data.
 * @retval MBA_RES_FAIL         Failed to send the SDU due to an L2CAP instance error.
 */
uint16_t BLE_L2CAP_CbSendSdu(uint8_t leL2capId, uint16_t length, uint8_t *p_payload);


/**
 * @brief Sends L2CAP flow control credits to the peer device.
 * @note  Credits should be returned to the peer device after receiving data to ensure the peer can continue sending data.
 *
 * @param[in] leL2capId         The L2CAP instance identifier.
 * @param[in] credits           The number of credits to send.
 *
 * @retval MBA_RES_SUCCESS      Successfully sent credits to the peer device.
 * @retval MBA_RES_OOM          Internal memory allocation failure occurred.
 * @retval MBA_RES_NO_RESOURCE  No transmit buffers available for sending L2cap data.
 * @retval MBA_RES_FAIL         Failed to send credits due to an L2CAP instance error.
 *
 */
uint16_t BLE_L2CAP_CbAddCredits(uint8_t leL2capId, uint16_t credits);


/**
 * @brief Issues a disconnect request for a credit-based connection channel.
 *
 * @par Events generated
 * @ref BLE_L2CAP_EVT_CB_DISC_IND is generated when a credit-based connection is disconnected.
 *
 * @param[in] leL2capId         The L2CAP instance identifier.
 *
 * @retval MBA_RES_SUCCESS      Successfully issued a disconnect request.
 * @retval MBA_RES_OOM          Internal memory allocation failure occurred.
 * @retval MBA_RES_NO_RESOURCE  No transmit buffers available for sending L2CAP disconnect request.
 * @retval MBA_RES_FAIL         Failed to send the disconnect request due to an L2CAP instance error.
 *
 */
uint16_t BLE_L2CAP_CbDiscReq(uint8_t leL2capId);


/**
 * @brief Registers an SPSM (Simplified Protocol/Service Multiplexer).
 * @note  This function must be called before establishing a credit-based channel.
 *
 * @param[in] spsm              The SPSM value. See the range @ref BLE_L2CAP_SPSM_RANGE.
 * @param[in] mtu               The Maximum Transmission Unit. See the range @ref BLE_L2CAP_MTU_SIZE or @ref BLE_L2CAP_PDU_SIZE.
 * @param[in] mps               The Maximum PDU (Protocol Data Unit) Payload Size. See the minimum size @ref BLE_L2CAP_MIN_MPS_SIZE.
 * @param[in] initCredits       The initial number of credits.
 * @param[in] permission        The permission setting for the SPSM. See @ref BLE_L2CAP_PERMISSION.
 *
 * @retval MBA_RES_SUCCESS      Successfully registered the SPSM.
 * @retval MBA_RES_INVALID_PARA Invalid parameter, such as an out-of-range MTU.
 * @retval MBA_RES_FAIL         Failed to register the SPSM.
 */
uint16_t BLE_L2CAP_CbRegisterSpsm(uint16_t spsm, uint16_t mtu, uint16_t mps, uint16_t initCredits, uint8_t permission);


/**
 * @brief Deregisters an SPSM (Simplified Protocol/Service Multiplexer).
 * @note  This function should be called to release resources associated with an unused registered SPSM.
 *
 * @param[in] spsm              The SPSM value.
 *
 * @retval MBA_RES_SUCCESS      Successfully deregistered the SPSM.
 * @retval MBA_RES_INVALID_PARA The specified SPSM is unknown or invalid.
 */
uint16_t BLE_L2CAP_CbDeregisterSpsm(uint16_t spsm);


/**
 * @brief Pauses or resumes authorization for a specific SPSM (Simplified Protocol/Service Multiplexer).
 * @note By default, all SPSMs are authorized. Use this API to pause authorization if required.
 *
 * @param[in] spsm              The SPSM value.
 * @param[in] enable            Set to true to pause authorization (unauthorized). Set to false to resume authorization (authorized).
 *
 * @retval MBA_RES_SUCCESS      Successfully configured the SPSM authorization.
 * @retval MBA_RES_INVALID_PARA The specified SPSM is unknown or invalid.
 */
uint16_t BLE_L2CAP_CbPauseAuthorization(uint16_t spsm, bool enable);

/** @} */ //BLE_L2CAP_FUNS

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif//BLE_L2CAP_H
