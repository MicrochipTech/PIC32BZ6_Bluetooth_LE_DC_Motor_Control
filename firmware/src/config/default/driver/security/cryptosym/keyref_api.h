/** Common function definitions for keys.
 *
 * @file
 * Copyright (c) 2019-2020 Silex Insight. All Rights reserved. 
 */

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END
#ifndef KEYREF_API_FILE
#define KEYREF_API_FILE

#include "driver/security/cryptosym/internal.h"
#include "driver/security/api_table.h"


/** Returns a reference to a key whose key material is in user memory.
 *
 * This function loads the user provided key data and returns an initialized
 * crmkeyref object.
 *
 * The returned object can be passed to any of the crm_aead_create_*() or
 * crm_blkcipher_create_*() functions.
 *
 * @param[in] keysz size of the key to be loaded
 * @param[in] keymaterial key to be loaded with size \p keysz
 * @return crmkeyref initialized object with provided inputs
 *
 * @remark - \p keymaterial buffer should not be changed until the operation
 *           is completed.
 */
typedef struct crmkeyref (*FUNC_CRM_KEYREF_LOAD_MATERIAL)(size_t keysz, const char *keymaterial);
#define CRM_KEYREF_LOAD_MATERIAL                        ((FUNC_CRM_KEYREF_LOAD_MATERIAL)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_KEYREF_LOAD_MATERIAL)))


/** Returns a reference to a key selected by an index.
 *
 * This function initializes a crmkeyref object to use predefined hardware keys.
 * Currently, predefined hardware keys can be used with AES(BA411) and
 * SM4(BA419).
 *
 * The returned object can be passed to any of the crm_aead_create_*() or
 * crm_blkcipher_create_*() functions.
 *
 * @param[in] keyindex index of the hardware key, must be 0 or 1.
 * @return crmkeyref initialized object with configuration of the hardware key
 *         index provided
 */
typedef struct crmkeyref (*FUNC_CRM_KEYREF_LOAD_BY_ID)(size_t keyindex);
#define CRM_KEYREF_LOAD_BY_ID                           ((FUNC_CRM_KEYREF_LOAD_BY_ID)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_KEYREF_LOAD_BY_ID)))
#endif
