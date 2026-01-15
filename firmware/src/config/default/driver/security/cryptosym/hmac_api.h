/** Cryptographic HMAC(Keyed-Hash Message Authentication Code).
 *
 * The "create operation" functions are specific to HMAC. For the rest,
 * the HMAC computation is done by using the following MAC API functions:
 * CRM_MAC_FEED(), CRM_MAC_GENERATE(), CRM_MAC_STATUS() and CRM_MAC_WAIT().
 * The current implementation of HMAC does not support context-saving.
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
 /* Examples:
 * The following example shows typical sequence of function calls for computing
 * the HMAC of a message.
   @code
       CRM_MAC_CREATE_HMAC_SHA256(ctx, key)
       CRM_MAC_FEED(ctx, 'chunk 1')
       CRM_MAC_FEED(ctx, 'chunk 2')
       CRM_MAC_GENERATE(ctx)
       CRM_MAC_WAIT(ctx)
   @endcode
 */

#ifndef HMAC_API_FILE
#define HMAC_API_FILE

#include <stddef.h>
#include "driver/security/cryptosym/internal.h"
#include "driver/security/api_table.h"

struct crmmac;

/** Prepares a HMAC SHA256 MAC operation
 *
 * This function initializes the user allocated object \p c with a new MAC
 * operation context and reserves the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the hashing functions (except the ones that are specific to
 * context-saving).
 *
 * @param[out] c MAC operation context
 * @param[in] hmackey HMAC key
 * @param[in] ksz size, in bytes, of the HMAC key, can be any size
 * @return ::CRM_OK
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 */
typedef int (*FUNC_CRM_MAC_CREATE_HMAC_SHA256)(struct crmmac *c, struct crmkeyref *keyref);
#define CRM_MAC_CREATE_HMAC_SHA2_256                      ((FUNC_CRM_MAC_CREATE_HMAC_SHA256)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_MAC_CREATE_HMAC_SHA2_256)))


/** Prepares a HMAC SHA384 MAC operation
 *
 * This function initializes the user allocated object \p c with a new MAC
 * operation context and reserves the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the hashing functions (except the ones that are specific to
 * context-saving).
 *
 * @param[out] c MAC operation context
 * @param[in] hmackey HMAC key
 * @param[in] ksz size, in bytes, of the HMAC key, can be any size
 * @return ::CRM_OK
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @remark - \p hmackey buffer should not be changed until the operation is
 *              completed.
 */
typedef int (*FUNC_CRM_MAC_CREATE_HMAC_SHA384)(struct crmmac *c, struct crmkeyref *keyref);
#define CRM_MAC_CREATE_HMAC_SHA2_384                      ((FUNC_CRM_MAC_CREATE_HMAC_SHA384)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_MAC_CREATE_HMAC_SHA2_384)))


/** Prepares a HMAC SHA512 MAC operation
 *
 * This function initializes the user allocated object \p c with a new MAC
 * operation context and reserves the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the hashing functions (except the ones that are specific to
 * context-saving).
 *
 * @param[out] c MAC operation context
 * @param[in] hmackey HMAC key
 * @param[in] ksz size, in bytes, of the HMAC key, can be any size
 * @return ::CRM_OK
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @remark - \p hmackey buffer should not be changed until the operation is
 *              completed.
 */
typedef int (*FUNC_CRM_MAC_CREATE_HMAC_SHA2_512)(struct crmmac *c, struct crmkeyref *keyref);
#define CRM_MAC_CREATE_HMAC_SHA2_512                      ((FUNC_CRM_MAC_CREATE_HMAC_SHA2_512)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_MAC_CREATE_HMAC_SHA2_512)))


/** Prepares a HMAC SHA1 MAC operation
 *
 * This function initializes the user allocated object \p c with a new MAC
 * operation context and reserves the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the hashing functions (except the ones that are specific to
 * context-saving).
 *
 * @param[out] c MAC operation context
 * @param[in] hmackey HMAC key
 * @param[in] ksz size, in bytes, of the HMAC key, can be any size
 * @return ::CRM_OK
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @remark - \p hmackey buffer should not be changed until the operation is
 *              completed.
 */
typedef int (*FUNC_CRM_MAC_CREATE_HMAC_SHA1)(struct crmmac *c, struct crmkeyref *keyref);
#define CRM_MAC_CREATE_HMAC_SHA1                        ((FUNC_CRM_MAC_CREATE_HMAC_SHA1)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_MAC_CREATE_HMAC_SHA1)))


/** Prepares a HMAC SHA224 MAC operation
 *
 * This function initializes the user allocated object \p c with a new MAC
 * operation context and reserves the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the hashing functions (except the ones that are specific to
 * context-saving).
 *
 * @param[out] c MAC operation context
 * @param[in] hmackey HMAC key
 * @param[in] ksz size, in bytes, of the HMAC key, can be any size

 * @return ::CRM_OK
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @remark - \p hmackey buffer should not be changed until the operation is
 *              completed.
 */
typedef int (*FUNC_CRM_MAC_CREATE_HMAC_SHA224)(struct crmmac *c, struct crmkeyref *keyref);
#define CRM_MAC_CREATE_HMAC_SHA2_224                      ((FUNC_CRM_MAC_CREATE_HMAC_SHA224)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_MAC_CREATE_HMAC_SHA2_224)))

#endif
