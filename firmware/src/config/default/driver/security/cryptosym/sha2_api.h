/** Cryptographic message hashing SHA-2.
 *
 * @file
 *
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
#ifndef CRMSYMCRYPT_SHA2_API_FILE
#define CRMSYMCRYPT_SHA2_API_FILE

#include "driver/security/api_table.h"

struct crmhash;

/** Hash algorithm SHA-2 224
 *
 * Has only 32 bit capacity against length extension attacks.
 */
#define CRMHASHALG_SHA2_224        ((const struct crmhashalg *)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRMHASHALG_SHA2_224)))


/** Hash algorithm SHA-2 256
 *
 * Has no resistance against length extension attacks.
 */
#define CRMHASHALG_SHA2_256        ((const struct crmhashalg *)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRMHASHALG_SHA2_256)))

/** Hash algorithm SHA-2 384
 *
 * Has 128 bit capacity against length extension attacks.
 */
#define CRMHASHALG_SHA2_384        ((const struct crmhashalg *)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRMHASHALG_SHA2_384)))

/** Hash algorithm SHA-2 512
 *
 * Has no resistance against length extension attacks.
 */
#define CRMHASHALG_SHA2_512        ((const struct crmhashalg *)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRMHASHALG_SHA2_512)))

/** Prepares a SHA256 hash operation context
 *
 * This function initializes the user allocated object \p c with a new hash
 * operation context and reserves the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the hashing functions.
 *
 * @param[out] c hash operation context
 * @param[in] csz size of the hash operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @remark - SHA256 digest size is 32 bytes
 */
typedef int (*FUNC_CRM_HASH_CREATE_SHA256)(struct crmhash *c, size_t csz);
#define CRM_HASH_CREATE_SHA256                          ((FUNC_CRM_HASH_CREATE_SHA256)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_HASH_CREATE_SHA256)))

/** Prepares a SHA384 hash operation context
 *
 * This function initializes the user allocated object \p c with a new hash
 * operation context and reserves the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the hashing functions.
 *
 * @param[out] c hash operation context
 * @param[in] csz size of the hash operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @remark - SHA384 digest size is 48 bytes
 */
typedef int (*FUNC_CRM_HASH_CREATE_SHA384)(struct crmhash *c, size_t csz);
#define CRM_HASH_CREATE_SHA384                          ((FUNC_CRM_HASH_CREATE_SHA384)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_HASH_CREATE_SHA384)))


/** Prepares a SHA512 hash operation context
 *
 * This function initializes the user allocated object \p c with a new hash
 * operation context and reserves the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the hashing
 * functions.
 *
 * @param[out] c hash operation context
 * @param[in] csz size of the hash operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @remark - SHA512 digest size is 64 bytes
 */
typedef int (*FUNC_CRM_HASH_CREATE_SHA512)(struct crmhash *c, size_t csz);
#define CRM_HASH_CREATE_SHA512                          ((FUNC_CRM_HASH_CREATE_SHA512)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_HASH_CREATE_SHA512)))


/** Prepares a SHA224 hash operation context
 *
 * This function initializes the user allocated object \p c with a new hash
 * operation context and reserves the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the hashing functions.
 *
 * @param[out] c hash operation context
 * @param[in] csz size of the hash operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @remark - SHA224 digest size is 28 bytes
 */
typedef int (*FUNC_CRM_HASH_CREATE_SHA224)(struct crmhash *c, size_t csz);
#define CRM_HASH_CREATE_SHA224                          ((FUNC_CRM_HASH_CREATE_SHA224)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_HASH_CREATE_SHA224)))


#endif
