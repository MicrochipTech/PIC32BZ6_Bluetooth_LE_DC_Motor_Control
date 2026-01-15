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
  BLE Ctrl Service Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_ctrl_svc.c

  Summary:
    This file contains the BLE Ctrl Service functions for application user.

  Description:
    This file contains the BLE Ctrl Service functions for application user.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stddef.h>
#include "gatt.h"
#include "ble_util/byte_stream.h"
#include "ble_cms/ble_ctrl_svc.h"


// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
/* Little Endian. */
#define UUID_CTRL_PRIMARY_SVC_LE         0x01, 0xCB    /* Service UUID */

#define UUID_CTRL_CHARACTERISTIC_0_LE         0x02, 0xCB    /* Characteristic 0 UUID */
#define UUID_CTRL_CHARACTERISTIC_1_LE         0x03, 0xCB    /* Characteristic 1 UUID */

// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************

/* Primary Service Declaration */
static const uint8_t s_ctrlSvcUuid[] = {UUID_CTRL_PRIMARY_SVC_LE};
static const uint16_t s_ctrlSvcUuidLen = sizeof(s_ctrlSvcUuid);

/* Ctrl Characteristic 0 Characteristic */
static const uint8_t s_ctrlChar0[] = {ATT_PROP_READ|ATT_PROP_WRITE_REQ, UINT16_TO_BYTES(CTRL_HDL_CHARVAL_0), UUID_CTRL_CHARACTERISTIC_0_LE};    /* Read */ /* Write with response */
static const uint16_t s_ctrlChar0Len = sizeof(s_ctrlChar0);

/* Ctrl Characteristic 0 Characteristic Value */
static const uint8_t s_ctrlUuidChar0[] = {UUID_CTRL_CHARACTERISTIC_0_LE};
static uint8_t s_ctrlChar0Val[4] = {0x0};    /* Default Value */
static uint16_t s_ctrlChar0ValLen = sizeof(s_ctrlChar0Val);

/* Ctrl Characteristic 1 Characteristic */
static const uint8_t s_ctrlChar1[] = {ATT_PROP_READ|ATT_PROP_WRITE_CMD|ATT_PROP_NOTIFY, UINT16_TO_BYTES(CTRL_HDL_CHARVAL_1), UUID_CTRL_CHARACTERISTIC_1_LE};    /* Read */ /* Write without response */ /* Notify */
static const uint16_t s_ctrlChar1Len = sizeof(s_ctrlChar1);

/* Ctrl Characteristic 1 Characteristic Value */
static const uint8_t s_ctrlUuidChar1[] = {UUID_CTRL_CHARACTERISTIC_1_LE};
static uint8_t s_ctrlChar1Val[128] = {0x0};    /* Default Value */
uint16_t s_ctrlChar1ValLen = sizeof(s_ctrlChar1Val);

/* Ctrl Characteristic 1 Client Characteristic Configuration Descriptor */
static uint8_t s_ctrlCccChar1[] = {UINT16_TO_BYTES(0x0000)};
static const uint16_t s_ctrlCccChar1Len = sizeof(s_ctrlCccChar1);

/* Attribute list for Ctrl service */
static GATTS_Attribute_T s_ctrlList[] = {
    /* Service Declaration */
    {
        (uint8_t *) g_gattUuidPrimSvc,
        (uint8_t *) s_ctrlSvcUuid,
        (uint16_t *) & s_ctrlSvcUuidLen,
        sizeof (s_ctrlSvcUuid),
        0,
        PERMISSION_READ
    },
    /* Characteristic 0 Declaration */
    {
        (uint8_t *) g_gattUuidChar,
        (uint8_t *) s_ctrlChar0,
        (uint16_t *) & s_ctrlChar0Len,
        sizeof (s_ctrlChar0),
        0,
        PERMISSION_READ
    },
    /* Characteristic 0 Value */
    {
        (uint8_t *) s_ctrlUuidChar0,
        (uint8_t *) s_ctrlChar0Val,
        (uint16_t *) & s_ctrlChar0ValLen,
        sizeof(s_ctrlChar0Val),
        0,    
        PERMISSION_READ|PERMISSION_WRITE    
    },
    /* Characteristic 1 Declaration */
    {
        (uint8_t *) g_gattUuidChar,
        (uint8_t *) s_ctrlChar1,
        (uint16_t *) & s_ctrlChar1Len,
        sizeof (s_ctrlChar1),
        0,
        PERMISSION_READ
    },
    /* Characteristic 1 Value */
    {
        (uint8_t *) s_ctrlUuidChar1,
        (uint8_t *) s_ctrlChar1Val,
        (uint16_t *) & s_ctrlChar1ValLen,
        sizeof(s_ctrlChar1Val),
        SETTING_MANUAL_WRITE_RSP|SETTING_VARIABLE_LEN,    /* Manual Write Response */ /* Variable Length */
        PERMISSION_READ|PERMISSION_WRITE    
    },
    /* Client Characteristic Configuration Descriptor */
    {
        (uint8_t *) g_descUuidCcc,
        (uint8_t *) s_ctrlCccChar1,
        (uint16_t *) & s_ctrlCccChar1Len,
        sizeof (s_ctrlCccChar1),
        SETTING_MANUAL_WRITE_RSP|SETTING_CCCD,    /* Manual Write Response */
        PERMISSION_READ|PERMISSION_WRITE    
    },
};

static const GATTS_CccdSetting_T s_ctrlCccdSetting[] = 
{
    {CTRL_HDL_CCCD_1, NOTIFICATION},
};

/* Ctrl Service structure */
static GATTS_Service_T s_ctrlSvc = 
{
    NULL,
    (GATTS_Attribute_T *) s_ctrlList,
    (GATTS_CccdSetting_T const *)s_ctrlCccdSetting,
    CTRL_START_HDL,
    CTRL_END_HDL,
    1
};

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

uint16_t BLE_MobileCtrl_Add(void)
{
    return GATTS_AddService(&s_ctrlSvc, (CTRL_END_HDL - CTRL_START_HDL + 1));
}
