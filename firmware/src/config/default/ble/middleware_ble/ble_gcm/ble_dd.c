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
  BLE Database Discovery Middleware Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dd.c

  Summary:
    Implements BLE Database Discovery functions and handles related events for the application layer.

  Description:
    This source file provides the necessary functions to perform BLE Database Discovery
    and manage associated events within the application context. The "BLE_DD_Init" function
    must be invoked within the "APP_Initialize" function to properly set up this module.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include "osal/osal_freertos_extend.h"
#include "mba_error_defs.h"
#include "ble_gap.h"
#include "gatt.h"
#include "ble_util/byte_stream.h"
#include "ble_dd.h"


// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
#define DISC_CHAR_UUID2_RSP_LENGTH                  0x07        // Length for UUID of 2 bytes
#define DISC_CHAR_UUID16_RSP_LENGTH                 0x15        // Length for UUID of 16 bytes

/* BLE Device Discovery States. */
typedef enum BLE_DD_State_T
{
    BLE_DD_STATE_IDLE = 0x00U,                                  // Device is not connected (idle state)
    BLE_DD_STATE_CONNECTED                                      // Device is connected. */
} BLE_DD_State_T;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/* Structure for representing a single service discovery instance. */
typedef struct BLE_DD_DiscInstance_T
{
    uint16_t                svcStartHandle;                     // Start handle of the service being discovered.
    uint16_t                svcEndHandle;                       // End handle of the service being discovered.
    bool                    isSvcFound;                         // Flag indicating whether the service was found during discovery.
    uint8_t                 queuedReqByProtocol;                // Number of queued requests due to ATT protocol being busy.
    uint8_t                 queuedReqBySecurity;                // Number of queued requests due to ATT security requirements.
} BLE_DD_DiscInstance_T;


/* Structure for representing a connection instance for the database discovery process. */
typedef struct BLE_DD_Conn_T
{
    BLE_DD_DiscInstance_T   *p_discInstance;                    // Pointer to the service discovery instance.
    BLE_DD_CharInfo_T       *p_charInfoList;                    // Pointer to the list of characteristic information for the service being discovered.
    uint16_t                connHandle;                         // Handle identifying the connection.
    uint8_t                 connIndex;                          // Index of this connection within the connection database.
    uint8_t                 gapRole;                            // GAP role associated with this connection.
    uint8_t                 discSvcIndex;                       // Index of the service currently being discovered.
    bool                    isDiscovering;                      // Indicates if the discovery process is active for this connection.
    bool                    disableDiscovery;                   // If true, discovery is disabled for this connection, assuming characteristics are already known.
    BLE_DD_State_T          state;                              // Current state of the connection in the discovery process.
} BLE_DD_Conn_T;


/* Database for the database discovery module, holding all active connections and services to be discovered. */
typedef struct BLE_DD_Ctrl_T
{
    BLE_DD_Conn_T *         conn[BLE_GAP_MAX_LINK_NBR];         // Array of pointers to connection instances, indexed by connection handle. 
    BLE_DD_DiscSvc_T        services[BLE_DD_MAX_DISC_SVC_NUM];  // Array of services that are registered for discovery.
    uint8_t                 numOfService;                       // The total number of services registered for discovery.
} BLE_DD_Ctrl_T;

// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************
static BLE_DD_EventCb_T            s_ddEventCb;                 // Callback function for database discovery events.
static BLE_DD_Ctrl_T *             sp_ddCtrl;                   // Pointer to the database discovery module's structure.

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************
/**
 * @brief Frees a BLE device discovery connection object.
 *
 * This function releases the resources associated with a BLE device discovery
 * connection object, including the discovery instance and the connection entry.
 *
 * @param[in] p_conn Pointer to the BLE_DD_Conn_T structure to be freed.
 */
static void ble_dd_FreeConn(BLE_DD_Conn_T *p_conn)
{
    uint8_t i;

    if (p_conn->p_discInstance != NULL)
    {
        OSAL_Free(p_conn->p_discInstance);
    }

    for (i=0; i<BLE_GAP_MAX_LINK_NBR; i++)
    {
        if (sp_ddCtrl->conn[i] == p_conn)
        {
            OSAL_Free(sp_ddCtrl->conn[i]);
            sp_ddCtrl->conn[i] = NULL;
        
            break;
        }
    }
}


/**
 * @brief Retrieves a free connection object for device discovery.
 *
 * This function searches for an available connection object and initializes it
 * if found. It allocates memory for the connection object and sets the connection
 * index.
 *
 * @retval Pointer to the initialized BLE_DD_Conn_T structure, or NULL if no free
 *         connection object is available.
 */
static BLE_DD_Conn_T *ble_dd_GetFreeConn(void)
{
    uint8_t i;

    for (i=0; i<BLE_GAP_MAX_LINK_NBR; i++)
    {
        if (sp_ddCtrl->conn[i] == NULL)
        {
            sp_ddCtrl->conn[i] = OSAL_Malloc(sizeof(BLE_DD_Conn_T));
            if (sp_ddCtrl->conn[i] != NULL)
            {
                (void)memset((uint8_t *)sp_ddCtrl->conn[i], 0, sizeof(BLE_DD_Conn_T));
                sp_ddCtrl->conn[i]->connIndex = i;
            }
            return sp_ddCtrl->conn[i];
        }
    }
    return NULL;
}


/**
 * @brief Finds a connection object by its handle.
 *
 * This function searches for a connection object that matches the given connection
 * handle.
 *
 * @param[in] connHandle The handle of the connection to find.
 * 
 * @retval Pointer to the BLE_DD_Conn_T structure if found, or NULL otherwise.
 */
static BLE_DD_Conn_T *ble_dd_FindConnByHandle(uint16_t connHandle)
{
    uint8_t i;

    for (i=0; i<BLE_GAP_MAX_LINK_NBR; i++)
    {
        if ((sp_ddCtrl->conn[i]!= NULL) && (sp_ddCtrl->conn[i]->connHandle == connHandle))
        {
            sp_ddCtrl->conn[i]->connIndex = i;
            return sp_ddCtrl->conn[i];
        }
    }
    return NULL;
}


/**
 * @brief Sends a discovery complete event for a connection.
 *
 * This function notifies the application that service discovery is complete for
 * the specified connection.
 *
 * @param[in] p_conn Pointer to the BLE_DD_Conn_T structure representing the connection.
 */
static void ble_dd_SendDiscCompleteEvent(BLE_DD_Conn_T *p_conn)
{
    if (s_ddEventCb != NULL)
    {
        BLE_DD_Event_T ddEvent;

        ddEvent.eventId = BLE_DD_EVT_DISC_COMPLETE;
        ddEvent.eventField.evtDiscResult.connHandle = p_conn->connHandle;
        s_ddEventCb(&ddEvent);
    }
}


/**
 * @brief Starts service discovery on a connection.
 *
 * This function initiates service discovery for the specified connection by
 * sending a GATT discover primary service by UUID request.
 *
 * @param[in] p_conn Pointer to the BLE_DD_Conn_T structure representing the connection.
 */
static void ble_dd_ServiceDiscovery(BLE_DD_Conn_T *p_conn)
{
    GATTC_DiscoverPrimaryServiceParams_T discParams;

    p_conn->p_charInfoList = sp_ddCtrl->services[p_conn->discSvcIndex].p_charList[p_conn->connIndex].p_charInfo;
    (void)memset((uint8_t *)p_conn->p_charInfoList, 0, sizeof(BLE_DD_CharInfo_T)*sp_ddCtrl->services[p_conn->discSvcIndex].discCharsNum);
    (void)memset((uint8_t *)p_conn->p_discInstance, 0, sizeof(BLE_DD_DiscInstance_T));

    discParams.startHandle = 0x0001;
    discParams.endHandle = 0xFFFF;
    discParams.valueLength = sp_ddCtrl->services[p_conn->discSvcIndex].svcUuid.uuidLength;
    (void)memcpy(discParams.value ,sp_ddCtrl->services[p_conn->discSvcIndex].svcUuid.uuid, sp_ddCtrl->services[p_conn->discSvcIndex].svcUuid.uuidLength);
    if (GATTC_DiscoverPrimaryServiceByUUID(p_conn->connHandle, &discParams) == MBA_RES_BUSY)
    {
        p_conn->p_discInstance->queuedReqByProtocol = ATT_FIND_BY_TYPE_VALUE_REQ;
    }
}


/**
 * @brief Continues to the next service discovery on a connection.
 *
 * This function moves to the next service discovery if available, or completes
 * the discovery process if all services have been discovered.
 *
 * @param[in] p_conn Pointer to the BLE_DD_Conn_T structure representing the connection.
 */
static void ble_dd_NextServiceDiscovery(BLE_DD_Conn_T *p_conn)
{
    p_conn->discSvcIndex++;
    if (p_conn->discSvcIndex < sp_ddCtrl->numOfService)
    {
        ble_dd_ServiceDiscovery(p_conn);
    }
    else
    {
        p_conn->isDiscovering = false;
        ble_dd_SendDiscCompleteEvent(p_conn);
    }
}


/**
 * @brief Starts descriptor discovery for characteristics on a connection.
 *
 * This function initiates descriptor discovery for all characteristics of the
 * current service being discovered on the connection.
 *
 * @param[in] p_conn Pointer to the BLE_DD_Conn_T structure representing the connection.
 * 
 * @retval MBA_RES_SUCCESS if descriptor discovery is not needed or initiated successfully.
 * @retval MBA_RES_FAIL if descriptor discovery could not be started.
 */
static uint16_t ble_dd_DescriptorDiscovery(BLE_DD_Conn_T *p_conn)
{
    BLE_DD_DiscChar_T   **p_discChar;
    uint16_t            result = MBA_RES_SUCCESS;
    uint8_t             idx;

    p_discChar = sp_ddCtrl->services[p_conn->discSvcIndex].p_discChars;

    for (idx=0; idx<sp_ddCtrl->services[p_conn->discSvcIndex].discCharsNum; idx++, p_discChar++)
    {
        /* Check if there's descriptor to discover */
        if (((*p_discChar)->settings & CHAR_SET_DESCRIPTOR)!= 0U)
        {
            if (GATTC_DiscoverAllDescriptors(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle , p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
            {
                p_conn->p_discInstance->queuedReqByProtocol = ATT_FIND_INFORMATION_REQ;
            }
            result = MBA_RES_FAIL;
            break;
        }
    }

    return result;
}


/**
 * @brief Processes the characteristic discovery response.
 *
 * This function processes the response received from a characteristic discovery
 * request and updates the characteristic information list.
 *
 * @param[in] p_conn    Pointer to the BLE_DD_Conn_T structure representing the connection.
 * @param[in] p_event   Pointer to the GATT_Event_T structure containing the discovery response.
 */
static void ble_dd_ProcCharDiscResp(BLE_DD_Conn_T *p_conn, GATT_Event_T *p_event)
{
    BLE_DD_DiscChar_T   **p_discChar;
    uint16_t            procIdx = 0;
    uint8_t             uuidLength, idx;
    uint8_t             *p_uuid;

    /* ATT has error checking. There should be only these 2 cases. */
    if (p_event->eventField.onDiscCharResp.attrPairLength == (uint8_t)DISC_CHAR_UUID16_RSP_LENGTH)
    {
        uuidLength = ATT_UUID_LENGTH_16;
    }
    else
    {
        uuidLength = ATT_UUID_LENGTH_2;
    }

    /* Process each characteristic declaration in response */
    while (procIdx < p_event->eventField.onDiscCharResp.attrDataLength)
    {
        p_uuid = &p_event->eventField.onDiscCharResp.attrData[procIdx+5U];

        /* Process each discover characteristic with each characteristic declaration */
        for (idx=0, p_discChar = sp_ddCtrl->services[p_conn->discSvcIndex].p_discChars; idx<sp_ddCtrl->services[p_conn->discSvcIndex].discCharsNum; idx++, p_discChar++)
        {
            if (((*p_discChar)->settings & CHAR_SET_DESCRIPTOR) == 0U)
            {
                if (((*p_discChar)->p_uuid->uuidLength == uuidLength) && (memcmp((*p_discChar)->p_uuid->uuid, p_uuid, uuidLength) == 0))
                {
                    BUF_LE_TO_U16(&p_conn->p_charInfoList[idx].attrHandle, &p_event->eventField.onDiscCharResp.attrData[procIdx]);
                    /* Characteristic found, record handle. */
                    BUF_LE_TO_U16(&p_conn->p_charInfoList[idx].charHandle, &p_event->eventField.onDiscCharResp.attrData[procIdx+3U]);
                    p_conn->p_charInfoList[idx].property = p_event->eventField.onDiscCharResp.attrData[procIdx+2U];
                }
            }
        }
        procIdx += p_event->eventField.onDiscCharResp.attrPairLength;
    }
}


/**
 * @brief Processes the descriptor discovery response.
 *
 * This function processes the response received from a descriptor discovery
 * request and updates the characteristic information list with descriptor handles.
 *
 * @param[in] p_conn    Pointer to the BLE_DD_Conn_T structure representing the connection.
 * @param[in] p_event   Pointer to the GATT_Event_T structure containing the discovery response.
 */
static void ble_dd_ProcDescDiscResp(BLE_DD_Conn_T *p_conn, GATT_Event_T *p_event)
{
    BLE_DD_DiscChar_T   **p_discChar;
    uint16_t            procIdx = 0;
    uint16_t            uuidLength, idx;
    uint8_t             *p_uuid;

    /* GATT has filtering. The format of information data should only be 0x01 (16-bit UUID). */
    uuidLength = ATT_UUID_LENGTH_2;

    /* Process each handle-uuid pair in response */
    while (procIdx < p_event->eventField.onDiscDescResp.infoDataLength)
    {
        p_uuid = &p_event->eventField.onDiscDescResp.infoData[procIdx+2U];

        /* Process each discover characteristic with each characteristic declaration */
        for (idx=0, p_discChar = sp_ddCtrl->services[p_conn->discSvcIndex].p_discChars; idx<sp_ddCtrl->services[p_conn->discSvcIndex].discCharsNum; idx++, p_discChar++)
        {
            if ((((*p_discChar)->settings & CHAR_SET_DESCRIPTOR) != 0U) && (p_conn->p_charInfoList[idx].charHandle == 0U))
            {
                if (((*p_discChar)->p_uuid->uuidLength == uuidLength) && (memcmp((*p_discChar)->p_uuid->uuid, p_uuid, uuidLength) == 0))
                {
                    /* Characteristic descriptor found, record handle. */
                    BUF_LE_TO_U16(&p_conn->p_charInfoList[idx].charHandle, &p_event->eventField.onDiscDescResp.infoData[procIdx]);
                    break;
                }
            }
        }
        procIdx += (2U+ uuidLength);
    }
}


/**
 * @brief Handles BLE GAP events for device discovery.
 *
 * This function processes BLE GAP events relevant to device discovery, such as
 * connection and disconnection events, and initiates service discovery if appropriate.
 *
 * @param[in] p_config  Pointer to the BLE_DD_Config_T structure containing configuration options.
 * @param[in] p_event   Pointer to the BLE_GAP_Event_T structure containing the GAP event.
 */
static void ble_dd_StackEvtBleGapHandler(BLE_DD_Config_T *p_config, BLE_GAP_Event_T *p_event)
{
    switch (p_event->eventId)
    {
        case BLE_GAP_EVT_CONNECTED:
        {
            if ((p_event->eventField.evtConnect.status == GAP_STATUS_SUCCESS))
            {
                BLE_DD_Conn_T   *p_conn;
                uint8_t         i;

                /* Find free connection instance */
                p_conn = ble_dd_GetFreeConn();

                if (p_conn != NULL)
                {
                    BLE_DD_Event_T ddEvent;

                    p_conn->connHandle = p_event->eventField.evtConnect.connHandle;
                    p_conn->discSvcIndex = 0;
                    p_conn->gapRole = p_event->eventField.evtConnect.role;
                    p_conn->p_discInstance = OSAL_Malloc(sizeof(BLE_DD_DiscInstance_T));

                    for (i=0; i<sp_ddCtrl->numOfService; i++)
                    {
                        sp_ddCtrl->services[i].p_charList[p_conn->connIndex].connHandle = p_event->eventField.evtConnect.connHandle;
                    }

                    if (p_conn->p_discInstance != NULL)
                    {
                        (void)memset((uint8_t *)p_conn->p_discInstance, 0, sizeof(BLE_DD_DiscInstance_T));

                        if (p_config->disableConnectedDisc == 0U)
                        {
                            if (((p_config->initDiscInCentral==1U) && (p_conn->gapRole == BLE_GAP_ROLE_CENTRAL)) ||
                                ((p_config->initDiscInPeripheral==1U) && (p_conn->gapRole == BLE_GAP_ROLE_PERIPHERAL)))
                            {
                                if (p_config->waitForSecurity == 0U)
                                {
                                    p_conn->isDiscovering = true;
                                    ble_dd_ServiceDiscovery(p_conn);
                                }
                            }
                        }
                        else
                        {
                            p_config->disableConnectedDisc = 0;
                            p_conn->disableDiscovery = true;
                        }
                    }

                    ddEvent.eventId = BLE_DD_EVT_CONNECTED;
                    ddEvent.eventField.evtConnect.connHandle = p_conn->connHandle;
                    s_ddEventCb(&ddEvent);                
                }
            }
        }
        break;

        case BLE_GAP_EVT_DISCONNECTED:
        {
            BLE_DD_Conn_T *p_conn;

            /* Find connection instance */
            p_conn = ble_dd_FindConnByHandle(p_event->eventField.evtDisconnect.connHandle);
            if (p_conn != NULL)
            {
                BLE_DD_Event_T ddEvent;

                ble_dd_FreeConn(p_conn);
                ddEvent.eventId = BLE_DD_EVT_DISCONNECTED;
                ddEvent.eventField.evtDisconnect.connHandle = p_event->eventField.evtDisconnect.connHandle;
                s_ddEventCb(&ddEvent);
            }
        }
        break;

        case BLE_GAP_EVT_ENCRYPT_STATUS:
        {
            if (p_event->eventField.evtEncryptStatus.status == GAP_STATUS_SUCCESS)
            {
                BLE_DD_Conn_T *p_conn;

                /* Find connection instance */
                p_conn = ble_dd_FindConnByHandle(p_event->eventField.evtEncryptStatus.connHandle);

                if (p_conn != NULL)
                {
                    if ((p_conn->p_discInstance != NULL) && (p_conn->p_discInstance->queuedReqBySecurity!=0U))
                    {
                        if (p_conn->p_discInstance->queuedReqBySecurity == ATT_FIND_BY_TYPE_VALUE_REQ)
                        {
                            ble_dd_ServiceDiscovery(p_conn);
                        }
                        else if (p_conn->p_discInstance->queuedReqBySecurity == ATT_READ_BY_TYPE_REQ)
                        {
                            if (GATTC_DiscoverAllCharacteristics(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle, p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
                            {
                                p_conn->p_discInstance->queuedReqByProtocol = ATT_READ_BY_TYPE_REQ;
                            }
                        }
                        else if (p_conn->p_discInstance->queuedReqBySecurity == ATT_FIND_INFORMATION_REQ)
                        {
                            if (GATTC_DiscoverAllDescriptors(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle , p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
                            {
                                p_conn->p_discInstance->queuedReqByProtocol = ATT_FIND_INFORMATION_REQ;
                            }
                        }
                        else
                        {
                            //Shall not enter here
                        }
                        p_conn->p_discInstance->queuedReqBySecurity = 0;
                    }
                    else
                    {
                        if ((p_config->waitForSecurity == 1U) && (sp_ddCtrl->numOfService > 0U) && (p_conn->p_discInstance != NULL) && (p_conn->disableDiscovery == false))
                        {
                            if (((p_config->initDiscInCentral==1U) && (p_conn->gapRole == BLE_GAP_ROLE_CENTRAL)) ||
                                ((p_config->initDiscInPeripheral==1U) && (p_conn->gapRole == BLE_GAP_ROLE_PERIPHERAL)))
                            {
                                p_conn->isDiscovering = true;
                                ble_dd_ServiceDiscovery(p_conn);
                            }
                        }
                    }
                }
            }
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
 * @brief Handles BLE GATT client events for device discovery.
 *
 * This function processes BLE GATT client events relevant to device discovery,
 * such as service, characteristic, and descriptor discovery responses.
 *
 * @param[in] p_event Pointer to the GATT_Event_T structure containing the GATT client event.
 */
static void ble_dd_StackEvtBleGattcHandler(GATT_Event_T *p_event)
{
    switch (p_event->eventId)
    {
        case GATTC_EVT_ERROR_RESP:
        {
            BLE_DD_Conn_T *p_conn;

            p_conn = ble_dd_FindConnByHandle(p_event->eventField.onError.connHandle);

            if (p_conn != NULL)
            {
                /* Ignore responses when dd is not discovering */
                if (p_conn->isDiscovering == false)
                {
                    return;
                }

                /* Require security permission to access characteristics. Inform application and pause the discovery. */
                if ((p_event->eventField.onError.errCode == ATT_ERR_INSUF_ENC) || (p_event->eventField.onError.errCode == ATT_ERR_INSUF_AUTHN))
                {
                    p_conn->p_discInstance->queuedReqBySecurity = p_event->eventField.onError.reqOpcode;
                    if (s_ddEventCb != NULL)
                    {
                        BLE_DD_Event_T ddEvent;

                        ddEvent.eventId = BLE_DD_EVT_SEC_REQUIRED;
                        ddEvent.eventField.evtDiscResult.connHandle = p_conn->connHandle;
                        s_ddEventCb(&ddEvent);
                    }
                    return;
                }

                if (p_event->eventField.onError.reqOpcode == ATT_FIND_BY_TYPE_VALUE_REQ)
                {
                    if (p_conn->p_discInstance->isSvcFound==true)
                    {
                        /* Service found. Send characteristic discovery */
                        if (GATTC_DiscoverAllCharacteristics(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle, p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
                        {
                            p_conn->p_discInstance->queuedReqByProtocol = ATT_READ_BY_TYPE_REQ;
                        }
                    }
                    else
                    {
                        /* Move to next service discovery if exists */
                        ble_dd_NextServiceDiscovery(p_conn);
                    }
                }
                else if (p_event->eventField.onError.reqOpcode == ATT_READ_BY_TYPE_REQ)
                {
                    uint16_t result;

                    /* Characteristic discovery finish. Check if there's descriptor to discover. */
                    result = ble_dd_DescriptorDiscovery(p_conn);

                    /* No descriptor need to discover. Discovery of one service is finished. */
                    if (result == MBA_RES_SUCCESS)
                    {
                        /* Move to next service discovery if exists */
                        ble_dd_NextServiceDiscovery(p_conn);
                    }
                }
                else if (p_event->eventField.onError.reqOpcode == ATT_FIND_INFORMATION_REQ)
                {
                    /* Move to next service discovery if exists */
                    ble_dd_NextServiceDiscovery(p_conn);
                }
                else
                {
					//Shall not enter here
                }
            }
        }
        break;

        case GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP:
        {
            BLE_DD_Conn_T *p_conn;

            p_conn = ble_dd_FindConnByHandle(p_event->eventField.onDiscPrimServByUuidResp.connHandle);

            /* Ignore responses when dd is not discovering */
            if (p_conn->isDiscovering == false)
            {
                return;
            }

            if (p_conn != NULL)
            {
                BUF_LE_TO_U16(&p_conn->p_discInstance->svcStartHandle, &p_event->eventField.onDiscPrimServByUuidResp.handleInfo[0]);
                BUF_LE_TO_U16(&p_conn->p_discInstance->svcEndHandle, &p_event->eventField.onDiscPrimServByUuidResp.handleInfo[2]);
                if (sp_ddCtrl->services[p_conn->discSvcIndex].p_discInfo != NULL)
                {
                    sp_ddCtrl->services[p_conn->discSvcIndex].p_discInfo->svcStartHandle = p_conn->p_discInstance->svcStartHandle;
                    sp_ddCtrl->services[p_conn->discSvcIndex].p_discInfo->svcEndHandle = p_conn->p_discInstance->svcEndHandle;
                }
                p_conn->p_discInstance->isSvcFound = true;

                if (p_event->eventField.onDiscPrimServByUuidResp.procedureStatus == GATT_PROCEDURE_STATUS_FINISH)
                {
                    /* Send characteristic discovery directly if procedure is finished */
                    if (GATTC_DiscoverAllCharacteristics(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle, p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
                    {
                        p_conn->p_discInstance->queuedReqByProtocol = ATT_READ_BY_TYPE_REQ;
                    }
                }
            }
        }
        break;

        case GATTC_EVT_DISC_CHAR_RESP:
        {
            BLE_DD_Conn_T *p_conn;

            p_conn = ble_dd_FindConnByHandle(p_event->eventField.onDiscPrimServByUuidResp.connHandle);

            /* Ignore responses when dd is not discovering */
            if (p_conn->isDiscovering == false)
            {
                return;
            }

            if (p_conn != NULL)
            {
                ble_dd_ProcCharDiscResp(p_conn, p_event);

                /* Move to descriptor discovery or next service discovery when procedure finish. */
                if (p_event->eventField.onDiscCharResp.procedureStatus == GATT_PROCEDURE_STATUS_FINISH)
                {
                    uint16_t result;

                    /* Characteristic discovery finish. Check if there's descriptor to discover. */
                    result = ble_dd_DescriptorDiscovery(p_conn);

                    if (result == MBA_RES_SUCCESS)
                    {
                        /* Move to next service discovery if exists */
                        ble_dd_NextServiceDiscovery(p_conn);
                    }
                }
            }
        }
        break;

        case GATTC_EVT_DISC_DESC_RESP:
        {
            BLE_DD_Conn_T *p_conn;

            p_conn = ble_dd_FindConnByHandle(p_event->eventField.onDiscDescResp.connHandle);

            /* Ignore responses when dd is not discovering */
            if (p_conn->isDiscovering == false)
            {
                return;
            }

            if (p_conn != NULL)
            {
                if (p_event->eventField.onDiscDescResp.infoDataLength != 0U)
                {
                    ble_dd_ProcDescDiscResp(p_conn, p_event);
                }

                /* Move to next service discovery when procedure finish. */
                if (p_event->eventField.onDiscDescResp.procedureStatus == GATT_PROCEDURE_STATUS_FINISH)
                {
                    /* Move to next service discovery if exists */
                    ble_dd_NextServiceDiscovery(p_conn);
                }
            }
        }
        break;

        case GATTC_EVT_PROTOCOL_AVAILABLE:
        {
            BLE_DD_Conn_T *p_conn;

            p_conn = ble_dd_FindConnByHandle(p_event->eventField.onClientProtocolAvailable.connHandle);

            /* Ignore responses when dd is not discovering */
            if (p_conn->isDiscovering == false)
            {
                return;
            }

            if (p_conn != NULL)
            {
                if (p_conn->p_discInstance->queuedReqByProtocol == ATT_FIND_BY_TYPE_VALUE_REQ)
                {
                    p_conn->p_discInstance->queuedReqByProtocol = 0;
                    ble_dd_ServiceDiscovery(p_conn);
                }
                else if (p_conn->p_discInstance->queuedReqByProtocol == ATT_READ_BY_TYPE_REQ)
                {
                    p_conn->p_discInstance->queuedReqByProtocol = 0;
                    if (GATTC_DiscoverAllCharacteristics(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle, p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
                    {
                        p_conn->p_discInstance->queuedReqByProtocol = ATT_READ_BY_TYPE_REQ;
                    }
                }
                else if (p_conn->p_discInstance->queuedReqByProtocol == ATT_FIND_INFORMATION_REQ)
                {
                    p_conn->p_discInstance->queuedReqByProtocol = 0;
                    if (GATTC_DiscoverAllDescriptors(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle , p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
                    {
                        p_conn->p_discInstance->queuedReqByProtocol = ATT_FIND_INFORMATION_REQ;
                    }
                }
                else
                {
					//Shall not enter here
                }
            }
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
 * @brief Initializes the BLE device discovery module.
 *
 * This function allocates and initializes the structure for the BLE
 * device discovery module.
 *
 * @retval true if initialization is successful, false otherwise.
 */
bool BLE_DD_Init(void)
{
    uint8_t i;
    
    if (sp_ddCtrl == NULL)
    {
        sp_ddCtrl = OSAL_Malloc(sizeof(BLE_DD_Ctrl_T));

        if (sp_ddCtrl == NULL)
        {
            return false;
        }
    }
    else
    {
        for (i=0; i<BLE_GAP_MAX_LINK_NBR; i++)
        {
            if (sp_ddCtrl->conn[i] != NULL)
            {
                ble_dd_FreeConn(sp_ddCtrl->conn[i]);
            }
        }
    }

    (void)memset((uint8_t *)sp_ddCtrl, 0, sizeof(BLE_DD_Ctrl_T));


    return true;
}


/**
 * @brief Registers an event callback for the BLE device discovery module.
 *
 * This function sets the event callback function that will be called when
 * device discovery events occur.
 *
 * @param[in] eventCb The callback function to register.
 */
void BLE_DD_EventRegister(BLE_DD_EventCb_T eventCb)
{
    s_ddEventCb = eventCb;
}


/**
 * @brief Registers a service for discovery.
 *
 * This function adds a service to the list of services to be discovered on a
 * BLE connection.
 *
 * @param[in] p_discSvc Pointer to the BLE_DD_DiscSvc_T structure representing the service to register.
 * 
 * @retval MBA_RES_SUCCESS if the service is registered successfully
 * @retval MBA_RES_FAIL otherwise.
 */
uint16_t BLE_DD_ServiceDiscoveryRegister(BLE_DD_DiscSvc_T *p_discSvc)
{
    if (sp_ddCtrl->numOfService < BLE_DD_MAX_DISC_SVC_NUM)
    {
        (void)memcpy((uint8_t *)&sp_ddCtrl->services[sp_ddCtrl->numOfService], (uint8_t *)p_discSvc, sizeof(BLE_DD_DiscSvc_T));
        sp_ddCtrl->numOfService += 1U;
        return MBA_RES_SUCCESS;
    }
    else
    {
        return MBA_RES_FAIL;
    }
}


/**
 * @brief Handles BLE stack events for the device discovery module.
 *
 * This function processes stack events and dispatches them to the appropriate
 * GAP or GATT handler functions.
 *
 * @param[in] p_config Pointer to the BLE_DD_Config_T structure containing configuration options.
 * @param[in] p_stackEvent Pointer to the STACK_Event_T structure containing the stack event.
 */
void BLE_DD_BleEventHandler(BLE_DD_Config_T *p_config, STACK_Event_T *p_stackEvent)
{
    switch (p_stackEvent->groupId)
    {
        case STACK_GRP_BLE_GAP:
        {
            if (p_config != NULL)
            {
                ble_dd_StackEvtBleGapHandler(p_config, (BLE_GAP_Event_T *)p_stackEvent->p_event);
            }
        }
        break;

        case STACK_GRP_GATT:
        {
            ble_dd_StackEvtBleGattcHandler((GATT_Event_T *)p_stackEvent->p_event);
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
 * @brief Restarts service discovery for a specific connection.
 *
 * This function re-initiates service discovery for a given connection handle.
 *
 * @param[in] connHandle The handle of the connection for which to restart service discovery.
 * 
 * @retval MBA_RES_SUCCESS if service discovery is restarted successfully.
 * @retval MBA_RES_OOM if memory allocation fails.
 * @retval MBA_RES_INVALID_PARA if the connection handle is invalid.
 */
uint16_t BLE_DD_RestartServicesDiscovery(uint16_t connHandle)
{
    BLE_DD_Conn_T *p_conn;

    p_conn = ble_dd_FindConnByHandle(connHandle);

    if (p_conn != NULL)
    {
        if (p_conn->p_discInstance != NULL)
        {
            (void)memset((uint8_t *)p_conn->p_discInstance, 0, sizeof(BLE_DD_DiscInstance_T));
            p_conn->discSvcIndex = 0;
            p_conn->isDiscovering = true;
            ble_dd_ServiceDiscovery(p_conn);
            return MBA_RES_SUCCESS;
        }
        else
        {
            return MBA_RES_OOM;
        }
    }
    else
    {
        return MBA_RES_INVALID_PARA;
    }
}

