/** Cryptographic message hashing SHA-1.
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
#ifndef CRMSYMCRYPT_SHA1_API_FILE
#define CRMSYMCRYPT_SHA1_API_FILE

#include "driver/security/api_table.h"

struct crmhash;


/** Hash algorithm SHA-1 (Secure Hash Algorithm 1)
 *
 * Deprecated algorithm. NIST formally deprecated use of SHA-1 in 2011
 * and disallowed its use for digital signatures in 2013. SHA-3 or SHA-2
 * are recommended instead.
 */
#define CRMHASHALG_SHA1        ((const struct crmhashalg *)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRMHASHALG_SHA1)))


/** Prepares a SHA1 hash operation context
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
 * @remark - SHA1 digest size is 20 bytes
 */
typedef int (*FUNC_CRM_HASH_CREATE_SHA1)(struct crmhash *c, size_t csz);
#define CRM_HASH_CREATE_SHA1                            ((FUNC_CRM_HASH_CREATE_SHA1)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_HASH_CREATE_SHA1)))

#endif
