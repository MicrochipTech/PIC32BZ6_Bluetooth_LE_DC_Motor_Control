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
  BLE Connection Middleware Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_conn.c

  Summary:
    Implements BLE device connections and handles related events for BLE Device Manager.

  Description:
    This source file provides the functions and data structures used by the BLE 
    Device Manager for handling BLE connections. It is intended for internal 
    use within the BLE Device Manager module and should not be included 
    directly by application code.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "osal/osal_freertos_extend.h"
#include "ble_dm.h"
#include "ble_dm_conn.h"
#include "ble_dm_info.h"
#include "ble_dm_internal.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

typedef enum BLE_DM_CONN_State_T
{
    BLE_DM_CONN_STATE_IDLE = 0x00,                          // Default state (Disconnected).
    BLE_DM_CONN_STATE_CONNECTED                             // Connected state.
} BLE_DM_CONN_State_T;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/* Structure to hold connection update database information. */
typedef struct BLE_DM_ConnUpdateDb_T
{
    uint16_t                    connHandle;                         // The connection handle.
    BLE_DM_CONN_State_T         state;                              // Connection state.
    bool                        isProcedureInitiator;               // Indicates if the update procedure is initiated by this module or remotely.
} BLE_DM_ConnUpdateDb_T;


/* Structure to control BLE connection related operations. */
typedef struct BLE_DM_ConnCtrl_T
{
    BLE_DM_ConnUpdateDb_T       updateDb[BLE_GAP_MAX_LINK_NBR];     // Connection update instances for each link.
    BLE_DM_ConnConfig_T         userConnConfig;                     // User-defined connection configuration.
    bool                        autoReplyUpdate;                    // Flag to automatically accept connection parameter update requests from peer.
} BLE_DM_ConnCtrl_T;

// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************

static BLE_DM_ConnCtrl_T *      sp_dmConnCtrl;                      // Pointer to BLE_DM_ConnCtrl_T structure.

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************
/**
 * @brief Initializes the connection update database.
 * 
 * @param[in] p_conn Pointer to the connection update database structure.
 */
static void ble_dm_ConnInitUpdateDb(BLE_DM_ConnUpdateDb_T *p_conn)
{
    (void)memset((uint8_t *)p_conn, 0, sizeof(BLE_DM_ConnUpdateDb_T));
}

/**
 * @brief Retrieves a free connection instance from the connection update database.
 * 
 * @retval Pointer to the free connection instance, or NULL if none are available.
 */
static BLE_DM_ConnUpdateDb_T *ble_dm_GetFreeConn(void)
{
    uint8_t i;

    for (i=0; i<BLE_GAP_MAX_LINK_NBR; i++)
    {
        if (sp_dmConnCtrl->updateDb[i].state == BLE_DM_CONN_STATE_IDLE)
        {
            sp_dmConnCtrl->updateDb[i].state = BLE_DM_CONN_STATE_CONNECTED;
            return &sp_dmConnCtrl->updateDb[i];
        }
    }
    return NULL;
}


/**
 * @brief Finds a connection instance by its handle.
 * 
 * @param[in] connHandle The connection handle to search for.
 * 
 * @retval Pointer to the connection instance, or NULL if not found.
 */
static BLE_DM_ConnUpdateDb_T *ble_dm_ConnFindConnByHandle(uint16_t connHandle)
{
    uint8_t i;

    for (i=0; i<BLE_GAP_MAX_LINK_NBR; i++)
    {
        if ((sp_dmConnCtrl->updateDb[i].state == BLE_DM_CONN_STATE_CONNECTED) && (sp_dmConnCtrl->updateDb[i].connHandle == connHandle))
        {
            return &sp_dmConnCtrl->updateDb[i];
        }
    }
    return NULL;
}


/**
 * @brief Initializes the BLE Device Manager connection submodule.
 * 
 * @retval true if initialization is successful, false otherwise.
 */
bool BLE_DM_ConnInit(void)
{
    uint8_t i;

    if (sp_dmConnCtrl == NULL)
    {
        sp_dmConnCtrl = OSAL_Malloc(sizeof(BLE_DM_ConnCtrl_T));

        if (sp_dmConnCtrl == NULL)
        {
            return false;
        }
    }

    (void)memset(sp_dmConnCtrl, 0x00, sizeof(BLE_DM_ConnCtrl_T));

    for (i=0; i<BLE_GAP_MAX_LINK_NBR; i++)
    {
        ble_dm_ConnInitUpdateDb(&sp_dmConnCtrl->updateDb[i]);
    }

    return true;
}


/**
 * @brief Processes the GAP connected event.
 * 
 * @param[in] p_event Pointer to the GAP event structure.
 */
static void ble_dm_ConnProcGapConnected(BLE_GAP_Event_T *p_event)
{
    if ((p_event->eventField.evtConnect.status == GAP_STATUS_SUCCESS))
    {
        BLE_DM_ConnUpdateDb_T *p_conn;
    
        /* Find free connection instance */
        p_conn = ble_dm_GetFreeConn();

        if (p_conn != NULL)
        {
            p_conn->connHandle = p_event->eventField.evtConnect.connHandle;
        }
    }
}


/**
 * @brief Processes the GAP disconnected event.
 * 
 * @param[in] p_event Pointer to the GAP event structure.
 */
static void ble_dm_ConnProcGapDisconnected(BLE_GAP_Event_T *p_event)
{
    BLE_DM_ConnUpdateDb_T *p_conn;

    p_conn = ble_dm_ConnFindConnByHandle(p_event->eventField.evtDisconnect.connHandle);

    if (p_conn != NULL)
    {
        ble_dm_ConnInitUpdateDb(p_conn);
    }
}


/**
 * @brief Processes the GAP connection parameter update event.
 * 
 * @param[in] p_event Pointer to the GAP event structure.
 */
static void ble_dm_ConnProcGapConnParamUpdate(BLE_GAP_Event_T *p_event)
{
    BLE_DM_ConnUpdateDb_T *p_conn;

    p_conn = ble_dm_ConnFindConnByHandle(p_event->eventField.evtConnParamUpdate.connHandle);

    if (p_conn != NULL)
    {
        if (p_conn->isProcedureInitiator)
        {
            BLE_DM_Event_T  dmEvt;

            if (p_event->eventField.evtConnParamUpdate.status == 0U)
            {
                dmEvt.eventId = BLE_DM_EVT_CONN_UPDATE_SUCCESS;
            }
            else
            {
                dmEvt.eventId = BLE_DM_EVT_CONN_UPDATE_FAIL;
            }

            dmEvt.connHandle = p_event->eventField.evtConnParamUpdate.connHandle;
            BLE_DM_ConveyEvent(&dmEvt);
            p_conn->isProcedureInitiator = false;
        }
    }
}


/**
 * @brief Check if the remote device's connection update parameters are acceptable.
 *
 * This function checks if the given connection parameters are within the acceptable range as per
 * the Bluetooth specification and user-defined preferences.
 *
 * @param[in] minInterval   Minimum allowed connection interval.
 * @param[in] maxInterval   Maximum allowed connection interval.
 * @param[in] latency       Peripheral latency for the connection in number of connection events.
 * @param[in] timeout       Supervision timeout for the LE link.
 * 
 * @retval true if the parameters are acceptable, false otherwise.
 */
static bool ble_dm_ConnCheckRemoteUpdateParams(uint16_t minInterval, uint16_t maxInterval, uint16_t latency, uint16_t timeout)
{
    uint16_t minRequireTimeout;

    /* Check if value in Spec. suggested range. */
    if ((minInterval<BLE_GAP_CP_MIN_CONN_INTVAL_MIN) || (minInterval>BLE_GAP_CP_MIN_CONN_INTVAL_MAX) ||
        (maxInterval<BLE_GAP_CP_MAX_CONN_INTVAL_MIN) || (maxInterval>BLE_GAP_CP_MAX_CONN_INTVAL_MAX) ||
        (latency>BLE_GAP_CP_LATENCY_MAX) ||
        (timeout<BLE_GAP_CP_CONN_SUPV_TIMEOUT_MIN) || (timeout>BLE_GAP_CP_CONN_SUPV_TIMEOUT_MAX) ||
        (minInterval>maxInterval))
    {
        return false;
    }

    /* Check if parameters cause timeout */
    minRequireTimeout = (maxInterval*(1U+latency))*2U;    // Uint: 1.25 ms
    if ((timeout*8U) < minRequireTimeout)                // Compare with uint: 1.25 ms
    {
        return false;
    }

    /* Check if parameters are in user preferred range */
    if ((sp_dmConnCtrl->userConnConfig.maxAcceptConnInterval < minInterval) || (sp_dmConnCtrl->userConnConfig.minAcceptConnInterval > maxInterval) ||
        (sp_dmConnCtrl->userConnConfig.maxAcceptPeripheralLatency < latency) || (sp_dmConnCtrl->userConnConfig.minAcceptPeripheralLatency > latency))
    {
        return false;
    }

    return true;
}


/**
 * @brief Process GAP Remote Connection Update Request.
 *
 * This function processes the remote connection update request event. It checks if the connection parameters
 * requested by the remote device are valid and either accepts the request with the provided parameters or
 * rejects it if the parameters are not acceptable.
 *
 * @param[in] p_event Pointer to the BLE GAP event structure.
 */
static void ble_dm_ConnProcGapRemoteConnUpdateReq(BLE_GAP_Event_T *p_event)
{
    BLE_GAP_ConnParams_T    connParams;
    bool                    paramsValid;

    if (sp_dmConnCtrl->autoReplyUpdate)
    {
        paramsValid = ble_dm_ConnCheckRemoteUpdateParams(p_event->eventField.evtRemoteConnParamReq.intervalMin, p_event->eventField.evtRemoteConnParamReq.intervalMax,
                                                         p_event->eventField.evtRemoteConnParamReq.latency, p_event->eventField.evtRemoteConnParamReq.timeout);

        if (paramsValid)
        {
            connParams.intervalMin = p_event->eventField.evtRemoteConnParamReq.intervalMin;
            connParams.intervalMax = p_event->eventField.evtRemoteConnParamReq.intervalMax;
            connParams.latency = p_event->eventField.evtRemoteConnParamReq.latency;
            connParams.supervisionTimeout = p_event->eventField.evtRemoteConnParamReq.timeout;
            (void)BLE_GAP_RemoteConnParamsReqReply(p_event->eventField.evtRemoteConnParamReq.connHandle, &connParams);
        }
        else
        {
            (void)BLE_GAP_RemoteConnParamsReqNegativeReply(p_event->eventField.evtRemoteConnParamReq.connHandle, GAP_STATUS_UNACCEPTABLE_CONNECTION_PARAMETERS);
        }
    }
}


/**
 * @brief Handles BLE GAP events.
 * 
 * @param[in] p_event Pointer to the GAP event structure.
 */
static void ble_dm_ConnStackEvtBleGapHandler(BLE_GAP_Event_T *p_event)
{
    switch (p_event->eventId)
    {
        case BLE_GAP_EVT_CONNECTED:
        {
            ble_dm_ConnProcGapConnected(p_event);
        }
        break;

        case BLE_GAP_EVT_DISCONNECTED:
        {
            ble_dm_ConnProcGapDisconnected(p_event);
        }
        break;

        case BLE_GAP_EVT_CONN_PARAM_UPDATE:
        {
            ble_dm_ConnProcGapConnParamUpdate(p_event);
        }
        break;

        case BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST:
        {
            ble_dm_ConnProcGapRemoteConnUpdateReq(p_event);
        }
        break;

        default:
        {
            //Do nothing
        }
        break;
    }
}


/**
 * @brief Processes the L2CAP connection parameter update request event.
 * 
 * @param[in] p_event Pointer to the L2CAP event structure.
 */
static void ble_dm_ConnProcL2capCpUpdateReq(BLE_L2CAP_Event_T *p_event)
{
    BLE_DM_ConnUpdateDb_T *p_conn;

    p_conn = ble_dm_ConnFindConnByHandle(p_event->eventField.evtConnParamUpdateReq.connHandle);

    if (p_conn != NULL)
    {
        bool paramsValid;

        if (sp_dmConnCtrl->autoReplyUpdate)
        {
            paramsValid = ble_dm_ConnCheckRemoteUpdateParams(p_event->eventField.evtConnParamUpdateReq.intervalMin, p_event->eventField.evtConnParamUpdateReq.intervalMax,
                                                             p_event->eventField.evtConnParamUpdateReq.latency, p_event->eventField.evtConnParamUpdateReq.timeout);
            if (paramsValid)
            {
                /* Accept request. Send L2CAP response and send LL conn. update request. */
                BLE_GAP_ConnParams_T paras;

                (void)BLE_L2CAP_ConnParamUpdateRsp(p_event->eventField.evtConnParamUpdateReq.connHandle, BLE_L2CAP_CONN_PARAMS_ACCEPT);

                paras.intervalMin = p_event->eventField.evtConnParamUpdateReq.intervalMin;
                paras.intervalMax = p_event->eventField.evtConnParamUpdateReq.intervalMax;
                paras.latency = p_event->eventField.evtConnParamUpdateReq.latency;
                paras.supervisionTimeout = p_event->eventField.evtConnParamUpdateReq.timeout;
                (void)BLE_GAP_UpdateConnParam(p_event->eventField.evtConnParamUpdateReq.connHandle, &paras);
            }
            else
            {
                /* Reject request. Send L2CAP response. */
                (void)BLE_L2CAP_ConnParamUpdateRsp(p_event->eventField.evtConnParamUpdateReq.connHandle, BLE_L2CAP_CONN_PARAMS_REJECT);
            }
        }
    }
}


/**
 * @brief Processes the L2CAP connection parameter update response event.
 * 
 * @param[in] p_event Pointer to the L2CAP event structure.
 */
static void ble_dm_ConnProcL2capCpUpdateResp(BLE_L2CAP_Event_T *p_event)
{
    BLE_DM_ConnUpdateDb_T *p_conn;

    p_conn = ble_dm_ConnFindConnByHandle(p_event->eventField.evtConnParamUpdateRsp.connHandle);

    if (p_conn != NULL)
    {
        if ((p_event->eventField.evtConnParamUpdateRsp.result != MBA_RES_SUCCESS) && (p_conn->isProcedureInitiator))
        {
            BLE_DM_Event_T  dmEvt;

            dmEvt.eventId = BLE_DM_EVT_CONN_UPDATE_FAIL;
            dmEvt.connHandle = p_event->eventField.evtConnParamUpdateRsp.connHandle;
            BLE_DM_ConveyEvent(&dmEvt);
            p_conn->isProcedureInitiator = false;
        }
    }
}


/**
 * @brief Handles BLE L2CAP events.
 * 
 * @param[in] p_event Pointer to the L2CAP event structure.
 */
static void ble_dm_ConnStackEvtBleL2capHandler(BLE_L2CAP_Event_T *p_event)
{
    switch (p_event->eventId)
    {
        case BLE_L2CAP_EVT_CONN_PARA_UPD_REQ:
        {
            ble_dm_ConnProcL2capCpUpdateReq(p_event);
        }
        break;

        case BLE_L2CAP_EVT_CONN_PARA_UPD_RSP:
        {
            ble_dm_ConnProcL2capCpUpdateResp(p_event);
        }
        break;

        default:
        {
            //Do nothing
        }
        break;
    }
}


/**
 * @brief Main entry function for BLE Device Manager connection-related events.
 * 
 * @param[in] p_stackEvent Pointer to the stack event structure.
 */
void BLE_DM_Conn(STACK_Event_T *p_stackEvent)
{
    switch (p_stackEvent->groupId)
    {
        case STACK_GRP_BLE_GAP:
        {
            ble_dm_ConnStackEvtBleGapHandler((BLE_GAP_Event_T *)p_stackEvent->p_event);
        }
        break;

        case STACK_GRP_BLE_L2CAP:
        {
            ble_dm_ConnStackEvtBleL2capHandler((BLE_L2CAP_Event_T *)p_stackEvent->p_event);
        }
        break;

        default:
        {
            //Do nothing
        }
        break;
    }
}


/**
 * @brief Configures the connection parameters.
 * 
 * @param[in] p_config Pointer to the connection configuration structure.
 * 
 * @retval MBA_RES_SUCCESS on success, MBA_RES_INVALID_PARA on invalid parameters.
 */
uint16_t BLE_DM_ConnConfig(BLE_DM_ConnConfig_T *p_config)
{
    if (p_config->autoReplyUpdateRequest==true)
    {
        if ((p_config->maxAcceptConnInterval < p_config->minAcceptConnInterval) ||
            (p_config->maxAcceptPeripheralLatency < p_config->minAcceptPeripheralLatency) ||
            (p_config->minAcceptConnInterval < BLE_GAP_CP_MIN_CONN_INTVAL_MIN) ||
            (p_config->maxAcceptConnInterval > BLE_GAP_CP_MAX_CONN_INTVAL_MAX) ||
            (p_config->maxAcceptPeripheralLatency > BLE_GAP_CP_LATENCY_MAX))
        {
            sp_dmConnCtrl->autoReplyUpdate = false;
            return MBA_RES_INVALID_PARA;
        }
        else
        {
            sp_dmConnCtrl->autoReplyUpdate = true;
            sp_dmConnCtrl->userConnConfig.minAcceptConnInterval = p_config->minAcceptConnInterval;
            sp_dmConnCtrl->userConnConfig.maxAcceptConnInterval = p_config->maxAcceptConnInterval;
            sp_dmConnCtrl->userConnConfig.minAcceptPeripheralLatency = p_config->minAcceptPeripheralLatency;
            sp_dmConnCtrl->userConnConfig.maxAcceptPeripheralLatency = p_config->maxAcceptPeripheralLatency;
            sp_dmConnCtrl->userConnConfig.autoReplyUpdateRequest = p_config->autoReplyUpdateRequest;
            return MBA_RES_SUCCESS;
        }
    }
    else
    {
        sp_dmConnCtrl->autoReplyUpdate = false;
        return MBA_RES_SUCCESS;
    }
}


/**
 * @brief Updates the connection parameters.
 * 
 * @param[in] connHandle The connection handle.
 * @param[in] p_params Pointer to the connection parameter update structure.
 * 
 * @retval MBA_RES_SUCCESS on success, MBA_RES_INVALID_PARA on invalid parameters.
 */
uint16_t BLE_DM_ConnectionParameterUpdate(uint16_t connHandle, BLE_DM_ConnParamUpdate_T *p_params)
{
    BLE_DM_ConnUpdateDb_T *p_conn;
    BLE_DM_InfoConn_T *p_infoConn;
    uint16_t error;

    p_conn = ble_dm_ConnFindConnByHandle(connHandle);
    p_infoConn = BLE_DM_InfoGetConnByHandle(connHandle);

    if ((p_conn != NULL) && (p_infoConn != NULL))
    {
        BLE_GAP_ConnParams_T connParams;

        connParams.intervalMin = p_params->intervalMin;
        connParams.intervalMax = p_params->intervalMax;
        connParams.latency = p_params->latency;
        connParams.supervisionTimeout = p_params->timeout;
        /* minCeLength/maxCeLength is controlled by controller */
        error = BLE_GAP_UpdateConnParam(connHandle, &connParams);

        if ((error == MBA_RES_UNSUPPORT_REMOTE_FEATURE) && (p_infoConn->role == BLE_GAP_ROLE_PERIPHERAL))
        {
            error = BLE_L2CAP_ConnParamUpdateReq(connHandle, p_params->intervalMin, p_params->intervalMax, p_params->latency, p_params->timeout);
        }

        if (error == MBA_RES_SUCCESS)
        {
            p_conn->isProcedureInitiator = true;
        }
    }
    else
    {
        error = MBA_RES_INVALID_PARA;
    }
    return error;
}