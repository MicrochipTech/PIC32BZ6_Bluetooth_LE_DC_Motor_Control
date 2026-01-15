/** Common simple block cipher modes.
 *
 * All block cipher modes here perform simple encryption and decryption
 * without any authentication.
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
 * encryption and decryption of a message.
   @code
   1. One-shot operation
      a. Encryption
          crm_blkcipher_create_aescbc_enc(ctx, ...)
          CRM_BLKCIPHER_CRYPT(ctx, ...)
          CRM_BLKCIPHER_RUN(ctx)
          CRM_BLKCIPHER_WAIT(ctx)
      b. Decryption
          crm_blkcipher_create_aescbc_dec(ctx, ...)
          CRM_BLKCIPHER_CRYPT(ctx, ...)
          CRM_BLKCIPHER_RUN(ctx)
          CRM_BLKCIPHER_WAIT(ctx)
   2. Context-saving operation
      a. Encryption
          First round:
              crm_blkcipher_create_aescbc_enc(ctx)
              CRM_BLKCIPHER_CRYPT(ctx, 'first chunk')
              crm_blkcipher_save_state(ctx)
              CRM_BLKCIPHER_WAIT(ctx)
          Intermediary rounds:
              crm_blkcipher_resume_state(ctx)
              CRM_BLKCIPHER_CRYPT(ctx, 'n-th chunk')
              crm_blkcipher_save_state(ctx)
              CRM_BLKCIPHER_WAIT(ctx)
          Last round:
              crm_blkcipher_resume_state(ctx)
              CRM_BLKCIPHER_CRYPT(ctx, 'last chunk')
              CRM_BLKCIPHER_RUN(ctx)
              CRM_BLKCIPHER_WAIT(ctx)
      b. Decryption
          First round:
              crm_blkcipher_create_aescbc_dec(ctx)
              CRM_BLKCIPHER_CRYPT(ctx, 'first chunk')
              crm_blkcipher_save_state(ctx)
              CRM_BLKCIPHER_WAIT(ctx)
          Intermediary rounds:
              crm_blkcipher_resume_state(ctx)
              CRM_BLKCIPHER_CRYPT(ctx, 'n-th chunk')
              crm_blkcipher_save_state(ctx)
              CRM_BLKCIPHER_WAIT(ctx)
          Last round:
              crm_blkcipher_resume_state(ctx)
              CRM_BLKCIPHER_CRYPT(ctx, 'last chunk')
              CRM_BLKCIPHER_RUN(ctx)
              CRM_BLKCIPHER_WAIT(ctx)
   @endcode
 */

#ifndef BLKCIPHER_API_FILE
#define BLKCIPHER_API_FILE

#include <stddef.h>
#include "driver/security/cryptosym/internal.h"
#include "driver/security/api_table.h"


/** Prepares an AES XTS block cipher encryption.
 *
 * This function initializes the user allocated object \p c with a new block
 * cipher operation context needed to run the AES XTS encryption and reserves
 * the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions.
 *
 * @param[out] c block cipher operation context
 * @param[in] key1 first key used for the block cipher operation. expected size
 *                 16, 24 or 32 bytes, must be equal to \p key2 size
 * @param[in] key2 second key used for the block cipher operation, expected
 *                 size 16, 24 or 32 bytes, must be equal to \p key1 size
 * @param[in] iv initialization vector, size must be 16 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_HW_KEY_NOT_SUPPORTED
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
  *
 * @pre - key references provided by \p key1 and \p key2 must be initialized
 *        using CRM_KEYREF_LOAD_MATERIAL().
 */
typedef int (*FUNC_CRM_BLKCIPHER_CREATE_AESXTS_ENC)(struct crmblkcipher *c, const struct crmkeyref *key1, const struct crmkeyref *key2, const char *iv);
#define CRM_BLKCIPHER_CREATE_AESXTS_ENC                 ((FUNC_CRM_BLKCIPHER_CREATE_AESXTS_ENC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_CREATE_AESXTS_ENC)))


/** Prepares an AES XTS block cipher decryption
 *
 * This function initializes the user allocated object \p c with a new block
 * cipher operation context needed to run the AES XTS decryption and reserves
 * the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions.
 *
 * @param[out] c block cipher operation context
 * @param[in] key1 first key used for the block cipher operation. expected size
 *                 16, 24 or 32 bytes, must be equal to \p key2 size
 * @param[in] key2 second key used for the block cipher operation, expected
 *                 size 16, 24 or 32 bytes, must be equal to \p key1 size
 * @param[in] iv initialization vector, size must be 16 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_HW_KEY_NOT_SUPPORTED
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
  *
 * @pre - key references provided by \p key1 and \p key2 must be initialized
 *        using CRM_KEYREF_LOAD_MATERIAL().
 */
typedef int (*FUNC_CRM_BLKCIPHER_CREATE_AESXTS_DEC)(struct crmblkcipher *c, const struct crmkeyref *key1, const struct crmkeyref *key2, const char *iv);
#define CRM_BLKCIPHER_CREATE_AESXTS_DEC                 ((FUNC_CRM_BLKCIPHER_CREATE_AESXTS_DEC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_CREATE_AESXTS_DEC)))


/** Prepares an AES CTR block cipher encryption.
 *
 * This function initializes the user allocated object \p c with a new block
 * cipher operation context needed to run the AES CTR encryption and reserves
 * the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions.
 *
 * @param[out] c block cipher operation context
 * @param[in] key key used for the block cipher operation, expected size
 *                16, 24 or 32 bytes
 * @param[in] iv initialization vector, size must be 16 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
  *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 */
typedef int (*FUNC_CRM_BLKCIPHER_CREATE_AESCTR_ENC)(struct crmblkcipher *c, const struct crmkeyref *key, const char *iv);
#define CRM_BLKCIPHER_CREATE_AESCTR_ENC                 ((FUNC_CRM_BLKCIPHER_CREATE_AESCTR_ENC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_CREATE_AESCTR_ENC)))


/** Prepares an AES CTR block cipher decryption
 *
 * This function initializes the user allocated object \p c with a new block
 * cipher operation context needed to run the AES CTR decryption and reserves
 * the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions.
 *
 * @param[out] c block cipher operation context
 * @param[in] key key used for the block cipher operation, expected size
 *            16, 24 or 32 bytes
 * @param[in] iv initialization vector, size must be 16 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
  *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 */
typedef int (*FUNC_CRM_BLKCIPHER_CREATE_AESCTR_DEC)(struct crmblkcipher *c, const struct crmkeyref *key, const char *iv);
#define CRM_BLKCIPHER_CREATE_AESCTR_DEC                 ((FUNC_CRM_BLKCIPHER_CREATE_AESCTR_DEC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_CREATE_AESCTR_DEC)))


/** Prepares an AES ECB block cipher encryption.
 *
 * This function initializes the user allocated object \p c with a new block
 * cipher operation context needed to run the AES ECB encryption and reserves
 * the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions.
 *
 * @param[out] c block cipher operation context
 * @param[in] key key used for the block cipher operation, expected size is
 *                16, 24 or 32 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
  *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 *
 * @remark - AES ECB does not support context saving.
 */
typedef int (*FUNC_CRM_BLKCIPHER_CREATE_AESECB_ENC)(struct crmblkcipher *c, const struct crmkeyref *key);
#define CRM_BLKCIPHER_CREATE_AESECB_ENC                 ((FUNC_CRM_BLKCIPHER_CREATE_AESECB_ENC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_CREATE_AESECB_ENC)))


/** Prepares an AES ECB block cipher decryption
 *
 * This function initializes the user allocated object \p c with a new block
 * cipher operation context needed to run the AES ECB decryption and reserves
 * the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions.
 *
 * @param[out] c block cipher operation context
 * @param[in] key key used for the block cipher operation, expected size
 *                16, 24 or 32 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
  *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 *
 * @remark - AES ECB does not support context saving.
 */
typedef int (*FUNC_CRM_BLKCIPHER_CREATE_AESECB_DEC)(struct crmblkcipher *c, const struct crmkeyref *key);
#define CRM_BLKCIPHER_CREATE_AESECB_DEC                 ((FUNC_CRM_BLKCIPHER_CREATE_AESECB_DEC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_CREATE_AESECB_DEC)))


/** Prepares an AES CBC block cipher encryption.
 *
 * This function initializes the user allocated object \p c with a new block
 * cipher operation context needed to run the AES CBC encryption and reserves
 * the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions.
 *
 * @param[out] c block cipher operation context
 * @param[in] key key used for the block cipher operation, expected size
                  16, 24 or 32 bytes
 * @param[in] iv initialization vector, size must be 16 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
  *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 */
typedef int (*FUNC_CRM_BLKCIPHER_CREATE_AESCBC_ENC)(struct crmblkcipher *c, const struct crmkeyref *key, const char *iv);
#define CRM_BLKCIPHER_CREATE_AESCBC_ENC                 ((FUNC_CRM_BLKCIPHER_CREATE_AESCBC_ENC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_CREATE_AESCBC_ENC)))


/** Prepares an AES CBC block cipher decryption
 *
 * This function initializes the user allocated object \p c with a new block
 * cipher operation context needed to run the AES CBC decryption and reserves
 * the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions.
 *
 * @param[out] c block cipher operation context
 * @param[in] key key used for the block cipher operation, expected size
 *                16, 24 or 32 bytes
 * @param[in] iv initialization vector, size must be 16 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
  *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 */
typedef int (*FUNC_CRM_BLKCIPHER_CREATE_AESCBC_DEC)(struct crmblkcipher *c, const struct crmkeyref *key, const char *iv);
#define CRM_BLKCIPHER_CREATE_AESCBC_DEC                 ((FUNC_CRM_BLKCIPHER_CREATE_AESCBC_DEC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_CREATE_AESCBC_DEC)))


/** Prepares an AES CFB block cipher encryption.
 *
 * This function initializes the user allocated object \p c with a new block
 * cipher operation context needed to run the AES CFB encryption and reserves
 * the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions.
 *
 * @param[out] c block cipher operation context
 * @param[in] key key used for the block cipher operation, expected size
 *                16, 24 or 32 bytes
 * @param[in] iv initialization vector, size must be 16 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
  *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 */
typedef int (*FUNC_CRM_BLKCIPHER_CREATE_AESCFB_ENC)(struct crmblkcipher *c, const struct crmkeyref *key, const char *iv);
#define CRM_BLKCIPHER_CREATE_AESCFB_ENC                 ((FUNC_CRM_BLKCIPHER_CREATE_AESCFB_ENC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_CREATE_AESCFB_ENC)))


/** Prepares an AES CFB block cipher decryption
 *
 * This function initializes the user allocated object \p c with a new block
 * cipher operation context needed to run the AES CFB decryption and reserves
 * the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions.
 *
 * @param[out] c block cipher operation context
 * @param[in] key key used for the block cipher operation, expected size
 *                16, 24 or 32 bytes
 * @param[in] iv initialization vector, size must be 16 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
  *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 */
typedef int (*FUNC_CRM_BLKCIPHER_CREATE_AESCFB_DEC)(struct crmblkcipher *c, const struct crmkeyref *key, const char *iv);
#define CRM_BLKCIPHER_CREATE_AESCFB_DEC                 ((FUNC_CRM_BLKCIPHER_CREATE_AESCFB_DEC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_CREATE_AESCFB_DEC)))


/** Prepares an AES OFB block cipher encryption.
 *
 * This function initializes the user allocated object \p c with a new block
 * cipher operation context needed to run the AES OFB encryption and reserves
 * the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions.
 *
 * @param[out] c block cipher operation context
 * @param[in] key key used for the block cipher operation, expected size
 *                16, 24 or 32 bytes
 * @param[in] iv initialization vector, size must be 16 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
  *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 */
typedef int (*FUNC_CRM_BLKCIPHER_CREATE_AESOFB_ENC)(struct crmblkcipher *c, const struct crmkeyref *key, const char *iv);
#define CRM_BLKCIPHER_CREATE_AESOFB_ENC                 ((FUNC_CRM_BLKCIPHER_CREATE_AESOFB_ENC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_CREATE_AESOFB_ENC)))


/** Prepares an AES OFB block cipher decryption
 *
 * This function initializes the user allocated object \p c with a new block
 * cipher operation context needed to run the AES OFB decryption and reserves
 * the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions.
 *
 * @param[out] c block cipher operation context
 * @param[in] key key used for the block cipher operation, expected size
 *                16, 24 or 32 bytes
 * @param[in] iv initialization vector, size must be 16 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
  *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 */
typedef int (*FUNC_CRM_BLKCIPHER_CREATE_AESOFB_DEC)(struct crmblkcipher *c, const struct crmkeyref *key, const char *iv);
#define CRM_BLKCIPHER_CREATE_AESOFB_DEC                 ((FUNC_CRM_BLKCIPHER_CREATE_AESOFB_DEC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_CREATE_AESOFB_DEC)))


/** Adds data to be encrypted/decrypted.
 *
 * The function will return immediately.
 *
 * In order to start the operation CRM_BLKCIPHER_RUN() must be called.
 *
 * \p sz must ensure the following restrictions based on the mode used:
 *  Algorithm | \p sz        | Remarks
 *  --------: | :----------: | :-----------
 *        ECB | N * 16 bytes | N > 0
 *        CBC | N * 16 bytes | N > 0
 *        CFB | N * 16 bytes | N > 0
 *        OFB | N * 16 bytes | N > 0
 *        XTS | >= 16 bytes  | none
 *        CTR | > 0 bytes    | none
 *
 * The restrictions above are applicable ONLY for the last chunk of the data
 * to be processed when doing a partial operation. \p sz must be a multiple of
 * block size(16 bytes) when doing a partial operation(besides last chunk).
 *
 * @param[inout] c block cipher operation context
 * @param[in] datain data to be encrypted or decrypted, with size \p sz
 * @param[in] sz size, in bytes, of data to be decrypted
 * @param[out] dataout encrypted or decrypted data, must have \p sz bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_TOO_BIG
 *
 * @pre - one of the crm_blkcipher_create_*() functions must be called first
 */
typedef int (*FUNC_CRM_BLKCIPHER_CRYPT)(struct crmblkcipher *c, const char *datain, size_t sz, char *dataout);
#define CRM_BLKCIPHER_CRYPT                             ((FUNC_CRM_BLKCIPHER_CRYPT)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_CRYPT)))


/** Starts a block cipher operation.
 *
 * This function is used to start an encryption or a decryption based on what
 * create function was used, crm_blkcipher_create_*_enc() or
 * crm_blkcipher_create_*_dec(). The function will return immediately.
 *
 * The result will be transfered only after the operation is successfully
 * completed. The user shall check operation status with crm_blkcipher_status()
 * or CRM_BLKCIPHER_WAIT().
 *
 * @param[inout] c block cipher operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_TOO_SMALL
 * @return ::CRM_ERR_WRONG_SIZE_GRANULARITY
 *
 * @pre - CRM_BLKCIPHER_CRYPT() function must be called first
 */
typedef int (*FUNC_CRM_BLKCIPHER_RUN)(struct crmblkcipher *c);
#define CRM_BLKCIPHER_RUN                               ((FUNC_CRM_BLKCIPHER_RUN)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_RUN)))


/** Resumes AES operation in context-saving.
 *
 * This function shall be called when using context-saving to load the state
 * that was previously saved by crm_blkcipher_save_state() in the crmblkcipher
 * operation context \p c. It must be called with the same crmblkcipher operation
 * context \p c that was used with crm_crmblkcipher_save_state(). It will reserve
 * all hardware resources required to run the partial AES operation.
 * Previously used mode and direction are already stored in crmblkcipher \p c.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions, except the crm_blkcipher_create_*()
 * functions.
 *
 * @param[inout] c block cipher operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_CONTEXT_SAVING_NOT_SUPPORTED
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @pre - crm_blkcipher_create_aes*() and crm_blkcipher_save_state() functions
 *        must be called before, for first part of the message.
 * @pre - must be called for each part of the message(besides first), before
 *        crm_blkchiper_crypt() or crm_blkcipher_save_state().
 *
 * @remark - the user must not change the key until all parts of the message to
 *           be encrypted/decrypted are processed.
 * @remark - AES ECB does not support context saving.
 */
typedef int (*FUNC_CRM_BLKCIPHER_RESUME_STATE)(struct crmblkcipher *c);
#define CRM_BLKCIPHER_RESUME_STATE                      ((FUNC_CRM_BLKCIPHER_RESUME_STATE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_RESUME_STATE)))


/** Starts a partial block cipher operation.
 *
 * This function is used to start a partial encryption or decryption of
 * \p datain. The function will return immediately.
 *
 * The partial result will be transfered to \p dataout only after the operation
 * is successfully completed. The user shall check operation status with
 * crm_blkcipher_status() or CRM_BLKCIPHER_WAIT().
 *
 * @param[inout] c block cipher operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_CONTEXT_SAVING_NOT_SUPPORTED
 *
 * @pre - CRM_BLKCIPHER_CRYPT() should be called first.
 *
 * @remark - the user must not change the key until all parts of the message to
 *           be encrypted/decrypted are processed.
 */
typedef int (*FUNC_CRM_BLKCIPHER_SAVE_STATE)(struct crmblkcipher *c);
#define CRM_BLKCIPHER_SAVE_STATE                        ((FUNC_CRM_BLKCIPHER_SAVE_STATE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_SAVE_STATE)))


/** Waits until the given block cipher operation has finished
 *
 * This function returns when the block cipher operation was successfully
 * completed, or when an error has occurred that caused the operation to
 * terminate. The return value of this function is the operation status.
 *
 * After this call, all resources have been released and \p c cannot be used
 * again unless crm_blkcipher_create_*() is used.
 *
 * @param[inout] c block cipher operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_DMA_FAILED
 *
 * @see crm_blkcipher_status().
 *
 * @remark - this function is blocking until operation finishes.
 */
typedef int (*FUNC_CRM_BLKCIPHER_WAIT)(struct crmblkcipher *c);
#define CRM_BLKCIPHER_WAIT                              ((FUNC_CRM_BLKCIPHER_WAIT)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_WAIT)))


/** Returns the block cipher operation status.
 *
 * If the operation is still ongoing, return ::CRM_ERR_HW_PROCESSING.
 * In that case, the user can retry later.
 *
 * When this function returns with a code different than ::CRM_ERR_HW_PROCESSING,
 * the block cipher operation has ended and all resources used by block cipher
 * operation context \p c have been released. In this case, \p c cannot be used
 * for a new operation until one of the crm_blkcipher_create_*() functions is
 * called again.
 *
 * @param[inout] c block cipher operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_HW_PROCESSING
 * @return ::CRM_ERR_DMA_FAILED
 *
 * @pre - CRM_BLKCIPHER_CRYPT and CRM_BLKCIPHER_RUN() functions must be called
 *        first
 */
typedef int (*FUNC_CRM_BLKCIPHER_STATUS)(struct crmblkcipher *c);
#define CRM_BLKCIPHER_STATUS                            ((FUNC_CRM_BLKCIPHER_STATUS)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_BLKCIPHER_STATUS)))
#endif
