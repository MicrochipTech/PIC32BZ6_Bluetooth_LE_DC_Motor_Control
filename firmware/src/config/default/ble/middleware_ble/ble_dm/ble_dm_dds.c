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
  Device Information Middleware Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_dds.c

  Summary:
    Implements the internal data storage mechanisms for the BLE Device Manager.

  Description:
    This source file provides the necessary functions to handle data storage
    operations required by the BLE Device Manager. It is intended for internal
    use within the BLE software stack and is not part of the public API.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <string.h>
#include "osal/osal_freertos.h"
#include "ble_util/mw_aes.h"
#include "ble_dm_dds.h"
#include "pds.h"


// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
/* Enumeration of BLE PDS item IDs.*/
typedef enum BLE_DM_PdsBleItem_T{
    PDS_BLE_ITEM_ID_1 = (PDS_MODULE_BT_OFFSET),         // PDS item ID 1.
    PDS_BLE_ITEM_ID_2,                                  // PDS item ID 2.
    PDS_BLE_ITEM_ID_3,                                  // PDS item ID 3.
    PDS_BLE_ITEM_ID_4,                                  // PDS item ID 4.
    PDS_BLE_ITEM_ID_5,                                  // PDS item ID 5.
    PDS_BLE_ITEM_ID_6,                                  // PDS item ID 6.
    PDS_BLE_ITEM_ID_7,                                  // PDS item ID 7.
    PDS_BLE_ITEM_ID_8,                                  // PDS item ID 8.


    PDS_BLE_ITEM_EXT_ID_1,                              // PDS extended item ID 1.
    PDS_BLE_ITEM_EXT_ID_2,                              // PDS extended item ID 2.
    PDS_BLE_ITEM_EXT_ID_3,                              // PDS extended item ID 3.
    PDS_BLE_ITEM_EXT_ID_4,                              // PDS extended item ID 4.
    PDS_BLE_ITEM_EXT_ID_5,                              // PDS extended item ID 5.
    PDS_BLE_ITEM_EXT_ID_6,                              // PDS extended item ID 6.
    PDS_BLE_ITEM_EXT_ID_7,                              // PDS extended item ID 7.
    PDS_BLE_ITEM_EXT_ID_8                               // PDS extended item ID 8.
}BLE_DM_PdsBleItem_T;

#define BLE_DM_DDS_FILE_MAIN_ITEM_START       PDS_BLE_ITEM_ID_1     // Start ID for main item in DDS.
#define BLE_DM_DDS_FILE_EXT_ITEM_START        PDS_BLE_ITEM_EXT_ID_1 // Start ID for extended item in DDS.

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/* Structure to store main paired device information.*/
typedef struct BLE_DM_MainPairedDevInfo_T
{
    BLE_GAP_Addr_T                  remoteAddr;                    // Paired device bluetooth address.
    uint8_t                         remoteIrk[16];                 // Paired device BLE identity resolving key.
    uint8_t                         rv[8];                         // Paired device BLE rand value
    uint8_t                         ediv[2];                       // Paired device BLE encrypted diversifier.
    uint8_t                         ltk[16];                       // Paired device BLE Link key.
    uint8_t                         lesc:1;                        // Paired device using LE secure connection.
    uint8_t                         auth:1;                        // Paired device using authenticated pairing method.
    uint8_t                         encryptKeySize:6;              // Paired device BLE encrpytion key size.
}BLE_DM_MainPairedDevInfo_T;


/* Structure to store extended paired device information.*/
typedef struct BLE_DM_ExtPairedDevInfo_T
{
    BLE_GAP_Addr_T                  localAddr;                     // Local device bluetooth address.
    uint8_t                         localIrk[16];                  // Local device BLE identity resolving key.
    uint8_t                         reserved[9];                   // Reserved space for future use.
}BLE_DM_ExtPairedDevInfo_T;

// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************

static BLE_DM_MainPairedDevInfo_T       s_mainPairedInfo;
static BLE_DM_ExtPairedDevInfo_T        s_extPairedInfo;


PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_1, (uint16_t)sizeof(BLE_DM_MainPairedDevInfo_T), &s_mainPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_2, (uint16_t)sizeof(BLE_DM_MainPairedDevInfo_T), &s_mainPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_3, (uint16_t)sizeof(BLE_DM_MainPairedDevInfo_T), &s_mainPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_4, (uint16_t)sizeof(BLE_DM_MainPairedDevInfo_T), &s_mainPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_5, (uint16_t)sizeof(BLE_DM_MainPairedDevInfo_T), &s_mainPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_6, (uint16_t)sizeof(BLE_DM_MainPairedDevInfo_T), &s_mainPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_7, (uint16_t)sizeof(BLE_DM_MainPairedDevInfo_T), &s_mainPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_8, (uint16_t)sizeof(BLE_DM_MainPairedDevInfo_T), &s_mainPairedInfo,FILE_INTEGRITY_CONTROL_MARK);

PDS_DECLARE_FILE(PDS_BLE_ITEM_EXT_ID_1, (uint16_t)sizeof(BLE_DM_ExtPairedDevInfo_T), &s_extPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_EXT_ID_2, (uint16_t)sizeof(BLE_DM_ExtPairedDevInfo_T), &s_extPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_EXT_ID_3, (uint16_t)sizeof(BLE_DM_ExtPairedDevInfo_T), &s_extPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_EXT_ID_4, (uint16_t)sizeof(BLE_DM_ExtPairedDevInfo_T), &s_extPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_EXT_ID_5, (uint16_t)sizeof(BLE_DM_ExtPairedDevInfo_T), &s_extPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_EXT_ID_6, (uint16_t)sizeof(BLE_DM_ExtPairedDevInfo_T), &s_extPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_EXT_ID_7, (uint16_t)sizeof(BLE_DM_ExtPairedDevInfo_T), &s_extPairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_EXT_ID_8, (uint16_t)sizeof(BLE_DM_ExtPairedDevInfo_T), &s_extPairedInfo,FILE_INTEGRITY_CONTROL_MARK);


static BLE_DM_DdsWriteCompleteCb_T s_dmDdsCb;

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************
/**
 * @brief Checks if the given address can be resolved using the provided IRK.
 *
 * @param[in] p_remoteIrk Pointer to the IRK used for resolving the address.
 * @param[in] p_remoteAddr Pointer to the address to be resolved.
 * 
 * @retval true if the address can be resolved, false otherwise.
 */
static bool ble_dm_DdsCheckResolveAddress(uint8_t *p_remoteIrk, uint8_t *p_remoteAddr)
{
    uint8_t data[16], temp[16];
    uint8_t i;
    MW_AES_Ctx_T ctx;

    /* convert irk as aes key */
    for(i=0U; i<16U; i++)
    {
        temp[i]=p_remoteIrk[15U-i];
    }

    if (MW_AES_EcbEncryptInit(&ctx, temp) != MBA_RES_SUCCESS)
    {
        return false;
    }

    /* get prand from address */
    (void)memset(&data[0], 0, 13);
    for(i=0U; i<3U; i++)
    {
        data[13U+i]=p_remoteAddr[5U-i];
    }

    /* calculate localHash value */
    if(MW_AES_AesEcbEncrypt(&ctx, 16, temp, data) != MBA_RES_SUCCESS)
    {
        return false;
    }

    /* extract hash value from address */
    for(i=0U; i<3U; i++)
    {
        data[i]=p_remoteAddr[2U-i];
    }

    /* compare localHash with hash from address */
    return (memcmp(temp + 13, data, 3) == 0);
}

/**
 * @brief Retrieve paired device information.
 * 
 * @param[in] devId             Device ID of the paired device.
 * @param[out] p_pairedDevInfo  Pointer to the structure where paired device information will be stored.
 * 
 * @retval MBA_RES_SUCCESS on success.
 * @retval MBA_RES_INVALID_PARA if the device ID is invalid.
 * @retval MBA_RES_FAIL on failure.
 */
uint16_t BLE_DM_DdsGetPairedDevice(uint8_t devId, BLE_DM_PairedDevInfo_T * p_pairedDevInfo)
{
    if (devId >= BLE_DM_MAX_PAIRED_DEVICE_NUM
        || PDS_IsAbleToRestore((uint16_t)BLE_DM_DDS_FILE_MAIN_ITEM_START + devId) == false)
    {
        return MBA_RES_INVALID_PARA;
    }

    if (PDS_Restore((uint16_t)BLE_DM_DDS_FILE_MAIN_ITEM_START + devId))
    {
        if (PDS_IsAbleToRestore((uint16_t)BLE_DM_DDS_FILE_EXT_ITEM_START + devId) == true)
        {
            if (PDS_Restore((uint16_t)BLE_DM_DDS_FILE_EXT_ITEM_START + devId) == false)
            {
                return MBA_RES_FAIL;
            }

            (void)memcpy(&p_pairedDevInfo->localAddr, &s_extPairedInfo.localAddr, offsetof(BLE_DM_ExtPairedDevInfo_T, reserved));
        }
        else
        {
            (void)memset(&p_pairedDevInfo->localAddr, 0x00, offsetof(BLE_DM_ExtPairedDevInfo_T, reserved));
        }

        (void)memcpy(&p_pairedDevInfo->remoteAddr, &s_mainPairedInfo.remoteAddr, offsetof(BLE_DM_PairedDevInfo_T, localAddr));
        (void)memcpy(p_pairedDevInfo->rv, s_mainPairedInfo.rv, sizeof(BLE_DM_MainPairedDevInfo_T) - offsetof(BLE_DM_MainPairedDevInfo_T, rv));

        return MBA_RES_SUCCESS;
    }
    else
    {
        return MBA_RES_FAIL;
    }
}

/**
 * @brief Set paired device information.
 * 
 * @param[in] devId Device ID of the paired device.
 * @param[in] p_pairedDevInfo Pointer to the structure containing the paired device information to be set.
 * 
 * @retval MBA_RES_SUCCESS on success.
 * @retval MBA_RES_INVALID_PARA if the device ID is invalid.
 * @retval MBA_RES_FAIL on failure.
 */
uint16_t BLE_DM_DdsSetPairedDevice(uint8_t devId, BLE_DM_PairedDevInfo_T *p_pairedDevInfo)
{
    if (devId >= BLE_DM_MAX_PAIRED_DEVICE_NUM)
    {
        return MBA_RES_INVALID_PARA;
    }

    (void)memcpy(&s_extPairedInfo.localAddr, &p_pairedDevInfo->localAddr, offsetof(BLE_DM_ExtPairedDevInfo_T, reserved));

    if (PDS_Store((uint16_t)BLE_DM_DDS_FILE_EXT_ITEM_START + devId))
    {
        (void)memcpy(&s_mainPairedInfo.remoteAddr, &p_pairedDevInfo->remoteAddr, offsetof(BLE_DM_PairedDevInfo_T, localAddr));
        (void)memcpy(s_mainPairedInfo.rv, p_pairedDevInfo->rv, sizeof(BLE_DM_MainPairedDevInfo_T) - offsetof(BLE_DM_MainPairedDevInfo_T, rv));

        if (PDS_Store((uint16_t)BLE_DM_DDS_FILE_MAIN_ITEM_START + devId))
        {
            return MBA_RES_SUCCESS;
        }
        else
        {
            return MBA_RES_FAIL;
        }
    }
    else
    {
        return MBA_RES_FAIL;
    }
}


/**
 * @brief Get the first free device ID.
 * 
 * @retval The first free device ID.
 */
uint8_t BLE_DM_DdsGetFreeDeviceId(void)
{
    uint8_t devId;

    for (devId = 0; devId < BLE_DM_MAX_PAIRED_DEVICE_NUM; devId++)
    {
        if (!PDS_IsAbleToRestore((uint16_t)BLE_DM_DDS_FILE_MAIN_ITEM_START + devId))
        {
            break;
        }
    }

    return devId;
}


/**
 * @brief Retrieve the device ID for a given Bluetooth address.
 * 
 * @param[in] p_bdAddr Pointer to the Bluetooth address structure.
 * 
 * @retval Device ID on success, or BLE_DM_MAX_PAIRED_DEVICE_NUM if the address is non-resolvable or on failure.
 */
uint8_t BLE_DM_DdsGetDeviceId(BLE_GAP_Addr_T *p_bdAddr)
{
    uint8_t devId;
    BLE_GAP_Addr_T addr;
    uint16_t result;

    /* check if non-resolvable private address? */
    if (p_bdAddr->addrType == BLE_GAP_ADDR_TYPE_RANDOM_NON_RESOLVABLE)
    {
        return BLE_DM_MAX_PAIRED_DEVICE_NUM;
    }

    result = BLE_GAP_GetDeviceAddr(&addr);

    if (result!= MBA_RES_SUCCESS)
    {
        return BLE_DM_MAX_PAIRED_DEVICE_NUM;
    }
    
    for (devId = 0; devId < BLE_DM_MAX_PAIRED_DEVICE_NUM; devId++)
    {
        if (PDS_IsAbleToRestore((uint16_t)BLE_DM_DDS_FILE_MAIN_ITEM_START + devId))
        {
            if (PDS_Restore((uint16_t)BLE_DM_DDS_FILE_MAIN_ITEM_START + devId))
            {
                if (PDS_IsAbleToRestore((uint16_t)BLE_DM_DDS_FILE_EXT_ITEM_START + devId))
                {
                    if (PDS_Restore((uint16_t)BLE_DM_DDS_FILE_EXT_ITEM_START + devId))
                    {
                        if (memcmp(&s_extPairedInfo.localAddr, &addr, (uint16_t)sizeof(BLE_GAP_Addr_T)) != 0)
                        {
                            continue;
                        }
                    }
                    else
                    {
                        continue;
                    }
                }

                if (p_bdAddr->addrType == BLE_GAP_ADDR_TYPE_RANDOM_RESOLVABLE)
                {
                    if (ble_dm_DdsCheckResolveAddress(s_mainPairedInfo.remoteIrk, p_bdAddr->addr)==true)
                    {
                        break;
                    }
                }
                else
                {
                    if (memcmp(p_bdAddr->addr, s_mainPairedInfo.remoteAddr.addr, GAP_MAX_BD_ADDRESS_LEN) == 0)
                    {
                        break;
                    }
                }
            }
        }
    }

    return devId;
}


/**
 * @brief Delete paired device information for a given device ID.
 * 
 * @param[in] devId Device ID of the paired device to be deleted.
 * 
 * @retval MBA_RES_SUCCESS on success.
 * @retval MBA_RES_INVALID_PARA if the device ID is invalid.
 * @retval MBA_RES_FAIL on failure.
 */
uint16_t BLE_DM_DdsDeletePairedDevice(uint8_t devId)
{
    if (devId >= BLE_DM_MAX_PAIRED_DEVICE_NUM)
    {
        return MBA_RES_INVALID_PARA;
    }

    if (PDS_Delete((uint16_t)BLE_DM_DDS_FILE_MAIN_ITEM_START + devId) == PDS_SUCCESS)
    {
        return MBA_RES_SUCCESS;
    }
    else
	{
        return MBA_RES_FAIL;
	}
}


/**
 * @brief Delete all paired device information.
 * 
 * @retval MBA_RES_SUCCESS on success.
 * @retval MBA_RES_FAIL on failure.
 */
uint16_t BLE_DM_DdsDeleteAllPairedDevice(void)
{
    uint8_t devId;

    for (devId = 0; devId < BLE_DM_MAX_PAIRED_DEVICE_NUM; devId++)
    {
        if (PDS_Delete((uint16_t)BLE_DM_DDS_FILE_MAIN_ITEM_START + devId) != PDS_SUCCESS)
		{
            return MBA_RES_FAIL;
		}
    }

    return MBA_RES_SUCCESS;
}


/**
 * @brief Check if a device ID is valid and able to be restored.
 * 
 * @param[in] devId Device ID to be checked.
 * 
 * @retval true if the device ID is valid and able to be restored, false otherwise.
 */
bool BLE_DM_DdsChkDeviceId(uint8_t devId)
{
    return PDS_IsAbleToRestore((uint16_t)BLE_DM_DDS_FILE_MAIN_ITEM_START + devId);
}


/**
 * @brief Callback function for write complete event.
 * 
 * @param[in] memoryId Memory ID of the PDS item that was written.
 */
static void ble_dm_DdsWriteCompleteCallback(PDS_MemId_t memoryId)
{
    if ((memoryId >= (uint16_t)PDS_BLE_ITEM_ID_1) && (memoryId <= (uint16_t)PDS_BLE_ITEM_ID_8))
    {
        if (s_dmDdsCb!=NULL)
        {
            s_dmDdsCb(memoryId-(uint16_t)PDS_BLE_ITEM_ID_1);
        }
    }
}


/**
 * @brief Initialize the Device Manager Device Data Storage submodule.
 * 
 * @param[in] cb Callback function to be called on write complete event.
 */
void BLE_DM_DdsInit(BLE_DM_DdsWriteCompleteCb_T cb)
{
    s_dmDdsCb=cb;
    PDS_RegisterWriteCompleteCallback(ble_dm_DdsWriteCompleteCallback);
}
