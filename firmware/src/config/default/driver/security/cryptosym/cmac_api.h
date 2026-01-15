/** Message Authentication Code AES CMAC.
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
 * The following examples show typical sequences of function calls for
 * generating a mac.
   @code
   1. One-shot operation MAC generation
          CRM_MAC_CREATE_AESCMAC(ctx, ...)
          CRM_MAC_FEED(ctx, ...)
          CRM_MAC_GENERATE(ctx)
          CRM_MAC_WAIT(ctx)
   @endcode
 */

#ifndef CMAC_API_FILE
#define CMAC_API_FILE

#include <stddef.h>
#include "driver/security/cryptosym/internal.h"
#include "driver/security/cryptosym/mac_api.h"
#include "driver/security/api_table.h"

/** Prepares an AES CMAC generation.
 *
 * This function initializes the user allocated object \p c with a new AES CMAC
 * operation context needed to run the CMAC generation.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the CMAC functions.
 *
 * @param[out] c CMAC operation context
 * @param[in] key key used for the CMAC generation operation,
 *                expected size 16, 24 or 32 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
  *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 */
typedef int (*FUNC_CRM_MAC_CREATE_AESCMAC)(struct crmmac *c, const struct crmkeyref *key);
#define CRM_MAC_CREATE_AESCMAC                          ((FUNC_CRM_MAC_CREATE_AESCMAC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_MAC_CREATE_AESCMAC)))
#endif
