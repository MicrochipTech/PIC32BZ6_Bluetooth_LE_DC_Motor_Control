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
  Application BLE Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_ble_handler.c

  Summary:
    This file contains the Application BLE functions for this project.

  Description:
    This file contains the Application BLE functions for this project.
 *******************************************************************************/



// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include <stdint.h>
#include "configuration.h"
#include "system/console/sys_console.h"
#include "osal/osal_freertos_extend.h"
#include "app_ble.h"
#include "app_ble_handler.h"
#include "ble_cms/ble_ctrl_svc.h"
#include "peripheral/tcc/plib_tcc1.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

#define APP_BLE_NUM_ADDR_IN_DEV_NAME    2    /**< The number of bytes of device address included in the device name. */



// BLE Advertising Data Types
#define AD_TYPE_FLAGS              0x01
#define AD_TYPE_COMPLETE_NAME      0x09
#define AD_TYPE_SHORT_NAME         0x08
#define AD_TYPE_MANUFACTURER_DATA  0xFF
#define AD_TYPE_UUID16_COMPLETE    0x03
#define AD_TYPE_UUID128_COMPLETE   0x07


// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************
APP_Database_T                  g_appDb;
APP_ConnList                    g_appConnList[APP_BLE_MAX_LINK_NUMBER];
uint8_t                         g_enableUartMode;
uint8_t                         g_bleConnLinkNum;

// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************
static APP_BLE_ConnList_T       s_bleConnList[APP_BLE_MAX_LINK_NUMBER];
static APP_BLE_ConnList_T       *sp_currentBleLink = NULL; /**< This pointer means the last one connected BLE link. */
static uint8_t                  s_currBleConnIdx;

// Function to parse BLE advertising data
void parse_ble_adv_data(uint8_t *data, uint8_t len) {
    uint8_t index = 0;
    //SYS_CONSOLE_HANDLE myConsoleHandle;
    //myConsoleHandle = SYS_CONSOLE_HandleGet(SYS_CONSOLE_INDEX_0);

    while (index < len) {
        uint8_t field_len = data[index]; // First byte is length
        if (field_len == 0 || index + field_len >= len) {
            break; // Stop if length is invalid
        }

        uint8_t field_type = data[index + 1]; // Second byte is type
        uint8_t *field_value = &data[index + 2]; // Value starts after length and type

        ////SYS_CONSOLE_PRINT("Type: 0x%02X, Length: %d, Data: ", field_type, field_len - 1);

        switch (field_type) {
            case AD_TYPE_COMPLETE_NAME:
            case AD_TYPE_SHORT_NAME:
                //SYS_CONSOLE_MESSAGE("Device Name: ");
                for (int i = 0; i <field_len-1; i++)
                {
                    //SYS_CONSOLE_Print(myConsoleHandle, "%c", *field_value);
                    field_value+=1;
                }
                //SYS_CONSOLE_MESSAGE("\r\n");
                break;
            case AD_TYPE_UUID16_COMPLETE:
                //SYS_CONSOLE_PRINT("UUID16: 0x%02X%02X\r\n", field_value[1], field_value[0]);
                break;
            case AD_TYPE_UUID128_COMPLETE:
                ////SYS_CONSOLE_MESSAGE("UUID128: ");
                //for (int i = field_len - 2; i >= 0; i--) {
                //    //SYS_CONSOLE_PRINT("%02X", field_value[i]);
                //}
                break;
            case AD_TYPE_MANUFACTURER_DATA:
                ////SYS_CONSOLE_MESSAGE("Manufacturer Data: ");
                //for (int i = 0; i < field_len - 1; i++) {
                //    //SYS_CONSOLE_PRINT("%02X ", field_value[i]);
                //}
                break;
            default:
                ////SYS_CONSOLE_MESSAGE("Unknown");
                break;
        }
        index += field_len + 1; // Move to the next field
    }
}


// Function to parse BLE advertising data
uint16_t parse_UUID16(uint8_t *data, uint8_t len) {
    uint8_t index = 0;
    uint16_t uuid = 0;

    while (index < len) {
        uint8_t field_len = data[index]; // First byte is length
        if (field_len == 0 || index + field_len >= len) {
            break; // Stop if length is invalid
        }

        uint8_t field_type = data[index + 1]; // Second byte is type
        uint8_t *field_value = &data[index + 2]; // Value starts after length and type

        ////SYS_CONSOLE_PRINT("Type: 0x%02X, Length: %d, Data: ", field_type, field_len - 1);

        switch (field_type) {
            case AD_TYPE_UUID16_COMPLETE:
                uuid = (field_value[1] << 8) + field_value[0];
                return uuid;
            default:
                ////SYS_CONSOLE_MESSAGE("Unknown field type in scan data \r\n");
                break;
        }
        index += field_len + 1; // Move to the next field
    }
    return uuid;
}

// Function to parse BLE advertising data
bool check_local_name(uint8_t *data, uint8_t len, const char* pName) {
    uint8_t index = 0;

    while (index < len) {
        uint8_t field_len = data[index]; // First byte is length
        if (field_len == 0 || index + field_len >= len) {
            break; // Stop if length is invalid
        }

        uint8_t field_type = data[index + 1]; // Second byte is type
        uint8_t *field_value = &data[index + 2]; // Value starts after length and type

        ////SYS_CONSOLE_PRINT("Type: 0x%02X, Length: %d, Data: ", field_type, field_len - 1);

        switch (field_type) {
            case AD_TYPE_COMPLETE_NAME:
            case AD_TYPE_SHORT_NAME:
                //SYS_CONSOLE_MESSAGE("Device Name: ");
                if (strncmp((const char *)field_value, pName, strlen(pName)) == 0)
                    return true;
                //SYS_CONSOLE_MESSAGE("\r\n");
                break;
            default:
                ////SYS_CONSOLE_MESSAGE("Unknown field type in scan data \r\n");
                break;
        }
        index += field_len + 1; // Move to the next field
    }
    return false;
}


// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************
static void APP_ClearConnListByConnHandle(uint16_t connHandle)
{
    uint8_t i;

    for (i = 0; i < APP_BLE_MAX_LINK_NUMBER; i++)
    {
        if (s_bleConnList[i].connData.handle == connHandle)
        {
            memset((uint8_t *)(&s_bleConnList[i]), 0, sizeof(APP_BLE_ConnList_T));
            s_bleConnList[i].linkState = APP_BLE_STATE_STANDBY;
        }
    }
}

static APP_BLE_ConnList_T *APP_GetScanConnList(void)
{
    uint8_t i;

    //First find the state of APP_BLE_STATE_CONNECTING
    for (i = 0; i < APP_BLE_MAX_LINK_NUMBER; i++)
    {
        if (s_bleConnList[i].linkState == APP_BLE_STATE_CONNECTING)
        {
            s_currBleConnIdx = i;
            return (&s_bleConnList[i]);
        }
    }

    for (i = 0; i < APP_BLE_MAX_LINK_NUMBER; i++)
    {
        if (s_bleConnList[i].linkState == APP_BLE_STATE_STANDBY)
        {
            s_currBleConnIdx = i;
            return (&s_bleConnList[i]);
        }
    }
    
    return NULL;
}

uint8_t APP_GetConnLinkNum(void)
{
    uint8_t index, num = 0;

    for (index = 0; index < APP_BLE_MAX_LINK_NUMBER; index++)
    {
        if (s_bleConnList[index].linkState >= APP_BLE_STATE_CONNECTED)
        {
            num+=1;
        }
    }

    return num;
}

APP_BLE_ConnList_T *APP_GetFreeConnList(void)
{
    uint8_t i;

    for (i = 0; i < APP_BLE_MAX_LINK_NUMBER; i++)
    {
        if (s_bleConnList[i].connData.handle == 0)
        {
            s_currBleConnIdx = i;
            return (&s_bleConnList[i]);
        }
    }
    return NULL;
}

APP_BLE_ConnList_T *APP_GetConnInfoForPeripheral()
{
    uint8_t i;

    for (i = 0; i < APP_BLE_MAX_LINK_NUMBER; i++)
    {
        if ((s_bleConnList[i].linkState >= APP_BLE_STATE_CONNECTED) && (s_bleConnList[i].connData.role == BLE_GAP_ROLE_PERIPHERAL))
        {
            ////SYS_CONSOLE_MESSAGE("Found peripheral connection\r\n");
            return (&s_bleConnList[i]);
        }
    }
    return NULL;
}

APP_BLE_ConnList_T *APP_GetConnInfoByConnHandle(uint16_t connHandle)
{
    uint8_t i;

    for (i = 0; i < APP_BLE_MAX_LINK_NUMBER; i++)
    {
        if (s_bleConnList[i].connData.handle == connHandle)
        {
            return (&s_bleConnList[i]);
        }
    }
    return NULL;
}

uint16_t APP_GetConnHandleByIndex(uint8_t index)
{
    if (index < BLE_GAP_MAX_LINK_NBR)
    {
        if ((s_bleConnList[index].connData.handle != 0) && (s_bleConnList[index].linkState != APP_BLE_STATE_STANDBY))
            return s_bleConnList[index].connData.handle;
    }

    return 0xFFFF;
}
bool notificationsEnabled = false;

uint16_t APP_StartAdvertising()
{
    APP_BLE_ConnList_T   *p_bleConnList_t = APP_GetFreeConnList();            
    if (p_bleConnList_t == NULL)
        return 0xFFFF;

    // Start Advertisement
    uint16_t result = BLE_GAP_SetAdvEnable(true, 0);

    if (result == MBA_RES_SUCCESS)
    {
        APP_SetBleStateByLink(p_bleConnList_t, APP_BLE_STATE_ADVERTISING);
    }
    return MBA_RES_SUCCESS;
}
// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************
void APP_BleGapEvtHandler(BLE_GAP_Event_T *p_event)
{
    APP_BLE_ConnList_T *p_bleConn = NULL;
    switch(p_event->eventId)
    {
        case BLE_GAP_EVT_CONNECTED:
        {
            SYS_CONSOLE_PRINT("Connection handle %d role %d\r\n", p_event->eventField.evtConnect.connHandle, p_event->eventField.evtConnect.role);
             if (p_event->eventField.evtConnect.role == BLE_GAP_ROLE_CENTRAL)
                p_bleConn = APP_GetScanConnList();
            else
            {
                p_bleConn = APP_GetBleLinkByStates(APP_BLE_STATE_ADVERTISING, APP_BLE_STATE_ADVERTISING);
                notificationsEnabled = false;
            }
            
            if (p_bleConn)
            {
                //GATTS_UpdateBondingInfo(p_event->eventField.evtConnect.connHandle, NULL, 0, NULL);    //TODO: Have to handle bonded case

                /* Update the connection parameter */
                p_bleConn->linkState                        = APP_BLE_STATE_CONNECTED;
                p_bleConn->connData.role                    = p_event->eventField.evtConnect.role;        // 0x00: Central, 0x01:Peripheral
                p_bleConn->connData.handle                  = p_event->eventField.evtConnect.connHandle;
                p_bleConn->connData.connInterval            = p_event->eventField.evtConnect.interval;
                p_bleConn->connData.connLatency             = p_event->eventField.evtConnect.latency;
                p_bleConn->connData.supervisionTimeout      = p_event->eventField.evtConnect.supervisionTimeout;

                /* Save Remote Device Address */
                p_bleConn->connData.remoteAddr.addrType = p_event->eventField.evtConnect.remoteAddr.addrType;
                memcpy((uint8_t *)p_bleConn->connData.remoteAddr.addr, (uint8_t *)p_event->eventField.evtConnect.remoteAddr.addr, GAP_MAX_BD_ADDRESS_LEN);

                p_bleConn->secuData.smpInitiator.addrType = p_event->eventField.evtConnect.remoteAddr.addrType;
                memcpy((uint8_t *)p_bleConn->secuData.smpInitiator.addr, (uint8_t *)p_event->eventField.evtConnect.remoteAddr.addr, GAP_MAX_BD_ADDRESS_LEN);

                sp_currentBleLink = p_bleConn;
            }
        }
        break;

        case BLE_GAP_EVT_DISCONNECTED:
        {
            APP_BLE_ConnList_T *p_bleConn = APP_GetConnInfoByConnHandle(p_event->eventField.evtDisconnect.connHandle);
            if (p_bleConn->connData.role == BLE_GAP_ROLE_PERIPHERAL)
            {
                notificationsEnabled = false;
                ////SYS_CONSOLE_MESSAGE("Restarting advertising\r\n");
                // Restart Advertisement when peripheral disconnected
                APP_StartAdvertising();
            }
            SYS_CONSOLE_PRINT("Connection handle %d\r\n", p_event->eventField.evtDisconnect.connHandle);
            // Clear connection list
            APP_ClearConnListByConnHandle(p_event->eventField.evtDisconnect.connHandle);


            //APP_LED_AlwaysOn(APP_LED_TYPE_NULL, APP_LED_TYPE_NULL);
            if (g_bleConnLinkNum > 0)
                g_bleConnLinkNum--; //Don't move it because the two functions below need to reference.
        }
        break;

        case BLE_GAP_EVT_CONN_PARAM_UPDATE:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_ENCRYPT_STATUS:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_ADV_REPORT:
        {
            uint16_t UUID = parse_UUID16(p_event->eventField.evtAdvReport.advData, p_event->eventField.evtAdvReport.length);
            // door remote with correct service (Use specific name for demo purposes)?
            if (UUID == 0xCD01 && check_local_name(p_event->eventField.evtAdvReport.advData, p_event->eventField.evtAdvReport.length, "door_remote") )
            {
                //SYS_CONSOLE_MESSAGE("Found Peer Node\r\n");
                BLE_GAP_CreateConnParams_T createConnParam_t;
                createConnParam_t.scanInterval = 0x3C; // 37.5 ms
                createConnParam_t.scanWindow = 0x1E; // 18.75 ms
                createConnParam_t.filterPolicy = BLE_GAP_SCAN_FP_ACCEPT_ALL;
                createConnParam_t.peerAddr.addrType = p_event->eventField.evtAdvReport.addr.addrType;
                memcpy(createConnParam_t.peerAddr.addr, p_event->eventField.evtAdvReport.addr.addr, GAP_MAX_BD_ADDRESS_LEN);
                createConnParam_t.connParams.intervalMin = 6; // 6 = max 7.5ms
                createConnParam_t.connParams.intervalMax = 6;
                createConnParam_t.connParams.latency = 0;
                createConnParam_t.connParams.supervisionTimeout = 0x48;
                //SYS_CONSOLE_MESSAGE("Initiating Connection\r\n");
                BLE_GAP_CreateConnection(&createConnParam_t);                
            }
            ////SYS_CONSOLE_MESSAGE("ADV_REPORT\r\n");
            //parse_ble_adv_data(p_event->eventField.evtAdvReport.advData, p_event->eventField.evtAdvReport.length);
        }
        break;

        case BLE_GAP_EVT_ENC_INFO_REQUEST:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_EXT_ADV_REPORT:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_ADV_TIMEOUT:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_TX_BUF_AVAILABLE:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_DEVICE_NAME_CHANGED:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_AUTH_PAYLOAD_TIMEOUT:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_PHY_UPDATE:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_SCAN_REQ_RECEIVED:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_DIRECT_ADV_REPORT:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_PERI_ADV_SYNC_EST:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_PERI_ADV_REPORT:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_PERI_ADV_SYNC_LOST:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_ADV_SET_TERMINATED:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_SCAN_TIMEOUT:
        {
            /* TODO: implement your application code.*/
            //SYS_CONSOLE_MESSAGE("Scan Completed \r\n");
            // Start Advertisement
            //BLE_GAP_SetAdvEnable(0x01, 0x00);
            //SERCOM0_USART_Write((uint8_t *)"Advertising\r\n",13);
        }
        break;

        case BLE_GAP_EVT_TRANSMIT_POWER_REPORTING:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_ADV_COMPL:
        {
            /* TODO: implement your application code.*/

        }
        break;

        case BLE_GAP_EVT_PATH_LOSS_THRESHOLD:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_FEATURE_EXCHANGE_COMPL:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_GAP_EVT_SUBRATE_CHANGE:
        {
            /* TODO: implement your application code.*/
        }
        break;

        default:
        break;
    }
}

void APP_BleL2capEvtHandler(BLE_L2CAP_Event_T *p_event)
{
    switch(p_event->eventId)
    {
        case BLE_L2CAP_EVT_CONN_PARA_UPD_REQ:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_L2CAP_EVT_CONN_PARA_UPD_RSP:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_L2CAP_EVT_CB_CONN_IND:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_L2CAP_EVT_CB_CONN_FAIL_IND:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_L2CAP_EVT_CB_SDU_IND:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_L2CAP_EVT_CB_ADD_CREDITS_IND:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_L2CAP_EVT_CB_DISC_IND:
        {
            /* TODO: implement your application code.*/
        }
        break;

        default:
        break;
    }
}

extern void Motor_Start();
extern void Motor_Stop();
extern void Motor_Toggle();
extern void Motor_SetSpeed(uint8_t percentage);
extern uint16_t s_ctrlChar1ValLen;

void sendNotificationMessage(const char* buffer, uint32_t len)
{
    if (!notificationsEnabled)
    {
        return;
    }
    APP_BLE_ConnList_T *p_bleConn = APP_GetConnInfoForPeripheral();
    if (p_bleConn == NULL)
    {
        //SYS_CONSOLE_MESSAGE("Peripheral not found\r\n");
        return;
    }
    
    // limit to size of characteristic
    if (len > s_ctrlChar1ValLen) len = s_ctrlChar1ValLen;
    GATTS_HandleValueParams_T  hvParams;

    hvParams.charHandle = (uint16_t)CTRL_HDL_CHARVAL_1;
    hvParams.charLength = len;
    memcpy(hvParams.charValue, buffer, len);
    hvParams.sendType = ATT_HANDLE_VALUE_NTF;
    ////SYS_CONSOLE_PRINT("Sending notification on handle %d\r\n", p_bleConn->connData.handle);
    uint16_t result = GATTS_SendHandleValue(p_bleConn->connData.handle, &hvParams);
    if (result == MBA_RES_SUCCESS)
    {
        ////SYS_CONSOLE_MESSAGE("message sent \r\n");
    }
    else
    {
        ////SYS_CONSOLE_PRINT("Send error on handle %d %d\r\n",p_bleConn->connData.handle, result);
    }
}

void APP_GattEvtHandler(GATT_Event_T *p_event)
{
    ////SYS_CONSOLE_PRINT("GATT Event %d\r\n", p_event->eventId);
    switch(p_event->eventId)
    {
        case GATTC_EVT_ERROR_RESP:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTC_EVT_DISC_PRIM_SERV_RESP:
        {
#if 0
            /* TODO: implement your application code.*/
            uint8_t i = 0;
            for(i=0; i<no_of_links;i++)
                if(conn_hdl[i] == p_event->eventField.onDiscPrimServResp.connHandle)
                    conn_hdl_role[i] = BLE_ROLE_CLIENT;
#endif
        }
        break;

        case GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP:
        {
#if 0
            /* TODO: implement your application code.*/
            uint8_t i = 0;
            for(i=0; i<no_of_links;i++)
                if(conn_hdl[i] == p_event->eventField.onDiscPrimServByUuidResp.connHandle)
                    conn_hdl_role[i] = BLE_ROLE_CLIENT;
#endif
        }
        break;

        case GATTC_EVT_DISC_CHAR_RESP:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTC_EVT_DISC_DESC_RESP:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTC_EVT_READ_USING_UUID_RESP:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTC_EVT_READ_RESP:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTC_EVT_WRITE_RESP:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTC_EVT_HV_NOTIFY:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTC_EVT_HV_INDICATE:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTS_EVT_READ:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTS_EVT_WRITE:
        {
            if (p_event->eventField.onWrite.attrHandle == CTRL_HDL_CHARVAL_0)
            {
                ////SYS_CONSOLE_PRINT("GATTS_EVT_WRITE 0x%02x 0x%02x\r\n", p_event->eventField.onWrite.writeValue[2], p_event->eventField.onWrite.writeValue[3]);
                if (p_event->eventField.onWrite.writeValue[2] == 0x10) // motor on/off
                {
                    if (p_event->eventField.onWrite.writeValue[3] == 1)
                    {
                        Motor_Toggle();
                    }
                }
                else if (p_event->eventField.onWrite.writeValue[2] == 0x11) // motor speed
                {
                    uint8_t speed = p_event->eventField.onWrite.writeValue[3];
                    // 0-100%
                    if (speed > 100) speed = 100;
                    Motor_SetSpeed(speed);
                }
                // send response
                GATTS_SendWriteRespParams_T response;
                response.attrHandle = p_event->eventField.onWrite.attrHandle;
                response.responseType = ATT_WRITE_RSP;
                if (GATTS_SendWriteResponse(p_event->eventField.onWrite.connHandle, &response) == MBA_RES_SUCCESS)
                {
                }
            }
            else if (p_event->eventField.onWrite.attrHandle == CTRL_HDL_CCCD_1) // enable notifications
            {
                ////SYS_CONSOLE_MESSAGE("GOT Notifications enable\r\n");
                notificationsEnabled = true;
                // send response
                GATTS_SendWriteRespParams_T response;
                response.attrHandle = p_event->eventField.onWrite.attrHandle;
                response.responseType = ATT_WRITE_RSP;
                if (GATTS_SendWriteResponse(p_event->eventField.onWrite.connHandle, &response) == MBA_RES_SUCCESS)
                {
                }
            }
            /* TODO: implement your application code.*/
        }
        break;

        case GATTS_EVT_HV_CONFIRM:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case ATT_EVT_TIMEOUT:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case ATT_EVT_UPDATE_MTU:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTC_EVT_DISC_CHAR_BY_UUID_RESP:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTS_EVT_SERVICE_CHANGE:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTS_EVT_CLIENT_FEATURE_CHANGE:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTS_EVT_CLIENT_CCCDLIST_CHANGE:
        {
            /* TODO: implement your application code.*/
            OSAL_Free(p_event->eventField.onClientCccdListChange.p_cccdList);
        }
        break;

        case GATTC_EVT_PROTOCOL_AVAILABLE:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case GATTS_EVT_PROTOCOL_AVAILABLE:
        {
            /* TODO: implement your application code.*/
        }
        break;


        default:
        break;
    }
}

void APP_BleSmpEvtHandler(BLE_SMP_Event_T *p_event)
{
    switch(p_event->eventId)
    {
        case BLE_SMP_EVT_PAIRING_COMPLETE:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_SMP_EVT_SECURITY_REQUEST:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_SMP_EVT_NUMERIC_COMPARISON_CONFIRM_REQUEST:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_SMP_EVT_INPUT_PASSKEY_REQUEST:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_SMP_EVT_NOTIFY_KEYS:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_SMP_EVT_PAIRING_REQUEST:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_SMP_EVT_INPUT_OOB_DATA_REQUEST:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_SMP_EVT_INPUT_SC_OOB_DATA_REQUEST:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_SMP_EVT_KEYPRESS:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_SMP_EVT_GEN_SC_OOB_DATA_DONE:
        {
            /* TODO: implement your application code.*/
        }
        break;

        default:
        break;
    }
}

void APP_DmEvtHandler(BLE_DM_Event_T *p_event)
{
    switch(p_event->eventId)
    {
        case BLE_DM_EVT_DISCONNECTED:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_DM_EVT_CONNECTED:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_DM_EVT_SECURITY_START:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_DM_EVT_SECURITY_SUCCESS:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_DM_EVT_SECURITY_FAIL:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_DM_EVT_PAIRED_DEVICE_FULL:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_DM_EVT_PAIRED_DEVICE_UPDATED:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_DM_EVT_CONN_UPDATE_SUCCESS:
        {
            /* TODO: implement your application code.*/
        }
        break;

        case BLE_DM_EVT_CONN_UPDATE_FAIL:
        {
            /* TODO: implement your application code.*/
        }
        break;

        default:
        break;
    }
}

static void APP_HexToAscii(uint8_t byteNum, uint8_t *p_hex, uint8_t *p_ascii)
{
    uint8_t i, j, c;
    uint8_t digitNum = byteNum * 2;

    if (p_hex == NULL || p_ascii == NULL)
        return;

    for (i = 0; i < digitNum; i++)
    {
        j = i / 2;
        c = p_hex[j] & 0x0F;

        if (c >= 0x00 && c <= 0x09)
        {
            p_ascii[digitNum - i - 1] = c + 0x30;
        }
        else if (c >= 0x0A && c <= 0x0F)
        {
            p_ascii[digitNum - i - 1] = c - 0x0A + 'A';
        }

        p_hex[j] /= 16;
    }
}

void APP_UpdateLocalName(uint8_t devNameLen, uint8_t *p_devName)
{
    uint8_t localName[GAP_MAX_DEVICE_NAME_LEN] = {0};
    uint8_t localNameLen = 0;

    if (p_devName == NULL || devNameLen == 0)
    {
        BLE_GAP_Addr_T addrPara;
        uint8_t addrAscii[APP_BLE_NUM_ADDR_IN_DEV_NAME * 2];
        uint8_t digitNum = APP_BLE_NUM_ADDR_IN_DEV_NAME * 2;

        localName[localNameLen++] = 'B';
        localName[localNameLen++] = 'L';
        localName[localNameLen++] = 'E';
        localName[localNameLen++] = '_';
        localName[localNameLen++] = 'U';
        localName[localNameLen++] = 'A';
        localName[localNameLen++] = 'R';
        localName[localNameLen++] = 'T';
        localName[localNameLen++] = '_';

        BLE_GAP_GetDeviceAddr(&addrPara);

        APP_HexToAscii(APP_BLE_NUM_ADDR_IN_DEV_NAME, addrPara.addr, addrAscii);

        memcpy(&localName[localNameLen], &addrAscii[0], digitNum);

        localNameLen += digitNum;

        BLE_GAP_SetDeviceName(localNameLen, localName);
    }
    else
    {
        BLE_GAP_SetDeviceName(devNameLen, p_devName);
    }
}

uint8_t APP_GetBleRole(void)
{
    return (sp_currentBleLink->connData.role);
}

APP_BLE_LinkState_T APP_GetBleStateByLink(APP_BLE_ConnList_T *p_bleConnList_t)
{
    if (p_bleConnList_t == NULL)
        return (sp_currentBleLink->linkState);
    else
        return (p_bleConnList_t->linkState);
}

void APP_SetBleStateByLink(APP_BLE_ConnList_T *p_bleConnList_t, APP_BLE_LinkState_T state)
{
    if (p_bleConnList_t == NULL)
        sp_currentBleLink->linkState = state;
    else
        p_bleConnList_t->linkState = state;
}

uint8_t APP_GetBleRoleByLink(APP_BLE_ConnList_T *p_bleConnList_t)
{
    if (p_bleConnList_t == NULL)
        return (sp_currentBleLink->connData.role);
    else
        return (p_bleConnList_t->connData.role);
}

bool APP_IsBleMultiRole(void)
{
    uint8_t i;
    uint8_t gapCentralRole = 0;
    uint8_t gapPeripheralRole = 0;

    for (i = 0; i < APP_BLE_MAX_LINK_NUMBER; i++)
    {
        if (s_bleConnList[i].connData.handle == 0)
            continue;
        
        if (s_bleConnList[i].connData.role == BLE_GAP_ROLE_CENTRAL)
        {
            gapCentralRole++;
        }
        else
        {
            gapPeripheralRole++;
        }

        if (gapCentralRole && gapPeripheralRole)
        {
            return true;
        }
    }

    return false;
}


APP_BLE_ConnList_T *APP_GetLastOneConnectedBleLink(void)
{
    uint8_t i, idx = 0xFF;
    uint16_t lastOne = 0;

    for (i = 0; i < APP_BLE_MAX_LINK_NUMBER; i++)
    {
        if ((s_bleConnList[i].connData.handle != 0) && (s_bleConnList[i].connData.handle > lastOne))
        {
            lastOne = s_bleConnList[i].connData.handle;
            idx = i;
        }
    }

    if ((lastOne) && (idx < APP_BLE_MAX_LINK_NUMBER))
        return &(s_bleConnList[idx]);
    else
        return NULL;
}

APP_BLE_ConnList_T *APP_GetBleLinkByStates(APP_BLE_LinkState_T start, APP_BLE_LinkState_T end)
{
    uint8_t i;

    while (end >= start)
    {
        i = 0;
        
        for (i = 0; i < APP_BLE_MAX_LINK_NUMBER; i++)
        {
            if (s_bleConnList[i].linkState == start)
                return (&s_bleConnList[i]);
        }
        
        start+=1;
    }
    
    return NULL;
}

uint8_t APP_SetCurrentBleLink(APP_BLE_ConnList_T *p_bleConnList_t)
{
    /*if (p_bleConnList_t == NULL)
        return APP_RES_INVALID_PARA;
    else*/
        sp_currentBleLink = p_bleConnList_t;

    return MBA_RES_SUCCESS;
}

uint16_t APP_GetCurrentConnHandle(void)
{
    if (sp_currentBleLink->linkState == APP_BLE_STATE_CONNECTED)
    {
        return sp_currentBleLink->connData.handle;
    }
    else
    {
        return 0;
    }
}

void APP_InitConnList(void)
{
    uint8_t i;

    sp_currentBleLink = &s_bleConnList[0];
    s_currBleConnIdx = APP_BLE_UNKNOWN_ID;
    g_bleConnLinkNum = 0;

    for (i = 0; i < APP_BLE_MAX_LINK_NUMBER; i++)
    {
        memset((uint8_t *)(&s_bleConnList[i]), 0, sizeof(APP_BLE_ConnList_T));
        s_bleConnList[i].linkState = APP_BLE_STATE_STANDBY;
    }

}


