/** Authenticated encryption with associated data(AEAD).
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
// DOM-IGNORE-END/*
 /* Examples:
 * The following examples show typical sequences of function calls for
 * encryption and decryption a message.
   @code
   1. One-shot operation
      a. Encryption
         CRM_AEAD_CREATE_AESGCM_ENC(ctx, ...)
         CRM_AEAD_FEED_AAD(ctx, aad, aadsz)
         CRM_AEAD_CRYPT(ctx, datain, datainz, dataout)
         CRM_AEAD_PRODUCE_TAG(ctx, tag)
         CRM_AEAD_WAIT(ctx)
      b. Decryption
         CRM_AEAD_CREATE_AESGCM_DEC(ctx, ...)
         CRM_AEAD_FEED_AAD(ctx, aad, aadsz)
         CRM_AEAD_CRYPT(ctx, datain, datainz, dataout)
         CRM_AEAD_VERIFY_TAG(ctx, tag)
         CRM_AEAD_WAIT(ctx)
   2. Context-saving operation
         a. Encryption
         First round:
            CRM_AEAD_CREATE_AESGCM_ENC(ctx)
            CRM_AEAD_FEED_AAD(ctx, aad, aadsz)
            CRM_AEAD_CRYPT(ctx, 'first chunk')
            CRM_AEAD_SAVE_STATE(ctx)
            CRM_AEAD_WAIT(ctx)
         Intermediary rounds:
            CRM_AEAD_RESUME_STATE(ctx)
            CRM_AEAD_CRYPT(ctx, 'n-th chunk')
            CRM_AEAD_SAVE_STATE(ctx)
            CRM_AEAD_WAIT(ctx)
         Last round:
            CRM_AEAD_RESUME_STATE(ctx)
            CRM_AEAD_CRYPT(ctx, 'last chunk')
            CRM_AEAD_PRODUCE_TAG(ctx, tag)
            CRM_AEAD_WAIT(ctx)
         b. Decryption
         First round:
            CRM_AEAD_CREATE_AESGCM_DEC(ctx)
            CRM_AEAD_FEED_AAD(ctx, aad, aadsz)
            CRM_AEAD_CRYPT(ctx, 'first chunk')
            CRM_AEAD_SAVE_STATE(ctx)
            CRM_AEAD_WAIT(ctx)
         Intermediary rounds:
            CRM_AEAD_RESUME_STATE(ctx)
            CRM_AEAD_CRYPT(ctx, 'n-th chunk')
            CRM_AEAD_SAVE_STATE(ctx)
            CRM_AEAD_WAIT(ctx)
         Last round:
            CRM_AEAD_RESUME_STATE(ctx)
            CRM_AEAD_CRYPT(ctx, 'last chunk')
            CRM_AEAD_VERIFY_TAG(ctx, tag)
            CRM_AEAD_WAIT(ctx)
   @endcode
 */

#ifndef AEAD_API_FILE
#define AEAD_API_FILE

#include <stddef.h>
#include "driver/security/cryptosym/internal.h"
#include "driver/security/api_table.h"

/** Initialization vector (IV) size, in bytes, for GCM encryption/decryption */
#define CRM_GCM_IV_SZ 12u

/** Size, in bytes, of GCM authentication tag */
#define CRM_GCM_TAG_SZ 16u

/** Maximum size, in bytes, of CCM authentication tag */
#define CRM_CCM_MAX_TAG_SZ 16u


/** Prepares an AES GCM AEAD encryption operation.
 *
 * This function initializes the user allocated object \p c with a new AEAD
 * encryption operation context needed to run the AES GCM operation and
 * reserves the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the AEAD functions.
 *
 * @param[out] c AEAD operation context
 * @param[in] key key used for the AEAD operation, expected size
 *                16, 24 or 32 bytes
 * @param[in] iv initialization vector, size must be 12 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 *
 * @remark - \p key and \p iv buffers should not be changed until the operation
 *           is completed.
 * @remark - GMAC is supported by using GCM with plaintext with size 0.
 * @remark - GCM and GMAC support AAD split in multiple chunks, using context
 *           saving.
 */
typedef int (*FUNC_CRM_AEAD_CREATE_AESGCM_ENC)(struct crmaead *c, const struct crmkeyref *key, const char *iv);
#define CRM_AEAD_CREATE_AESGCM_ENC         ((FUNC_CRM_AEAD_CREATE_AESGCM_ENC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_AEAD_CREATE_AESGCM_ENC)))


/** Prepares an AES GCM AEAD decryption operation.
 *
 * This function initializes the user allocated object \p c with a new AEAD
 * decryption operation context needed to run the AES GCM operation and
 * reserves the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the AEAD functions.
 *
 * @param[out] c AEAD operation context
 * @param[in] key key used for the AEAD operation, expected size
 *                16, 24 or 32 bytes
 * @param[in] iv initialization vector, size must be 12 bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 *
 * @remark - \p key and \p iv buffers should not be changed until the operation
 *           is completed.
 * @remark - GMAC is supported by using GCM with ciphertext with size 0.
 * @remark - GCM and GMAC support AAD split in multiple chunks, using context
 *           saving.
 */
typedef int (*FUNC_CRM_AEAD_CREATE_AESGCM_DEC)(struct crmaead *c, const struct crmkeyref *key, const char *iv);
#define CRM_AEAD_CREATE_AESGCM_DEC                      ((FUNC_CRM_AEAD_CREATE_AESGCM_DEC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_AEAD_CREATE_AESGCM_DEC)))


/** Prepares an AES CCM AEAD encryption operation.
 *
 * This function initializes the user allocated object \p c with a new AEAD
 * encryption operation context needed to run the AES GCM operation and
 * reserves the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the AEAD functions.
 *
 * @param[out] c AEAD operation context
 * @param[in] key key used for the AEAD operation, expected size
 *                16, 24 or 32 bytes
 * @param[in] noncesz size, in bytes, of the nonce, between 7 and 13 bytes
 * @param[in] nonce nonce used for the AEAD operation, with size \p noncesz
 * @param[in] tagsz size, in bytes, of the tag used for the AEAD operation,
 *            must be a value in {4, 6, 8, 10, 12, 14, 16}
 * @param[in] aadsz size, in bytes, of the additional authenticated data(AAD)
 * @param[in] datasz size, in bytes, of the data to be processed
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 *
 * @remark - the same aadsz and datasz must be provided to crm_aead_encrypt()
 *           or crm_aead_decrypt() functions.
 * @remark - \p key and \p nonce buffers should not be changed until the
 *           operation is completed.
 * @remark - CCM DOES NOT support AAD split in multiple chunks
 */
typedef int (*FUNC_CRM_AEAD_CREATE_AESCCM_ENC)(struct crmaead *c, const struct crmkeyref *key, const char *nonce, size_t noncesz, size_t tagsz, size_t aadsz, size_t datasz);
#define CRM_AEAD_CREATE_AESCCM_ENC                      ((FUNC_CRM_AEAD_CREATE_AESCCM_ENC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_AEAD_CREATE_AESCCM_ENC)))


/** Prepares an AES CCM AEAD decryption operation.
 *
 * This function initializes the user allocated object \p c with a new AEAD
 * decryption operation context needed to run the AES GCM operation and
 * reserves the HW resource.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the AEAD functions.
 *
 * @param[out] c AEAD operation context
 * @param[in] key key used for the AEAD operation, expected size
 *                16, 24 or 32 bytes
 * @param[in] noncesz size, in bytes, of the nonce, between 7 and 13 bytes
 * @param[in] nonce nonce used for the AEAD operation, with size \p noncesz
 * @param[in] tagsz size, in bytes, of the tag used for the AEAD operation,
 *            must be a value in {4, 6, 8, 10, 12, 14, 16}
 * @param[in] aadsz size, in bytes, of the additional authenticated data(AAD)
 * @param[in] datasz size, in bytes, of the data to be processed
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @pre - key reference provided by \p key must be initialized using
 *        CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID()
 *
 * @remark - the same aadsz and datasz must be provided to crm_aead_encrypt()
 *           or crm_aead_decrypt() functions.
 * @remark - \p key and \p nonce buffers should not be changed until the
 *           operation is completed.
 * @remark - CCM DOES NOT support AAD split in multiple chunks
 */
typedef int (*FUNC_CRM_AEAD_CREATE_AESCCM_DEC)(struct crmaead *c, const struct crmkeyref *key, const char *nonce, size_t noncesz, size_t tagsz, size_t aadsz, size_t datasz);
#define CRM_AEAD_CREATE_AESCCM_DEC                      ((FUNC_CRM_AEAD_CREATE_AESCCM_DEC)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_AEAD_CREATE_AESCCM_DEC)))


/** Adds AAD chunks
 *
 * This function is used for adding AAD buffer given by \p aad. The function
 * will return immediately.
 *
 * @param[inout] c AEAD operation context
 * @param[in] aad additional authentication data(AAD), with size \p aadsz
 * @param[in] aadsz size, in bytes, of the additional authenticated data(AAD),
 *                  can be 0 if \p aad is empty
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_TOO_BIG
 *
 * @pre - one of the crm_aead_create_*() functions must be called first
 *
 * @remark - the additional authentication data can be empty(\p aadsz = 0)
 * @remark - \p aad buffer should not be changed until the operation is
 *           completed.
 */
typedef int (*FUNC_CRM_AEAD_FEED_AAD)(struct crmaead *c, const char *aad, size_t aadsz);
#define CRM_AEAD_FEED_AAD                               ((FUNC_CRM_AEAD_FEED_AAD)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_AEAD_FEED_AAD)))


/** Adds data to be encrypted or decrypted.
 *
 * This function is used for adding data to be processed. The function will
 * return immediately.
 *
 * The result of the operation will be transfered to \p dataout after the
 * operation is successfully completed.
 *
 * For context saving, \p datain size(\p datainsz) must be a multiple of 16
 * bytes for AES GCM and CCM and a multiple of 64 bytes for ChaCha20Poly1305,
 * except the last buffer.
 *
 * @param[inout] c AEAD operation context
 * @param[in] datain data to be encrypted or decryoted, with size \p datainsz
 * @param[in] datainsz size, in bytes, of the data to be encrypted or decrypted
 * @param[out] dataout encrypted or decrypted data, must have \p datainsz bytes
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_TOO_BIG
 *
 * @pre - one of the crm_aead_create_*() functions must be called first
 *
 * @remark - \p datain buffer should not be changed until the operation is
 *           completed.
 */
typedef int (*FUNC_CRM_AEAD_CRYPT)(struct crmaead *c, const char *datain, size_t datainsz, char *dataout);
#define CRM_AEAD_CRYPT                                  ((FUNC_CRM_AEAD_CRYPT)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_AEAD_CRYPT)))


/** Starts an AEAD encryption and tag computation.
 *
 * The function will return immediately.
 *
 * The computed tag will be transfered to \p tag only after the operation is
 * successfully completed.
 *
 * The user shall check operation status with crm_aead_status() or CRM_AEAD_WAIT().
 *
 * @param[inout] c AEAD operation context
 * @param[out] tag authentication tag
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_TOO_BIG
 *
 * @pre - one of the CRM_AEAD_FEED_AAD() or CRM_AEAD_CRYPT() functions must be
 *        called first
 *
 * @remark - if used with context saving(last chunk), the fed data size for
 *         the last chunk can not be 0
 */
typedef int (*FUNC_CRM_AEAD_PRODUCE_TAG)(struct crmaead *c, char *tagout);
#define CRM_AEAD_PRODUCE_TAG                            ((FUNC_CRM_AEAD_PRODUCE_TAG)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_AEAD_PRODUCE_TAG)))


/** Starts an AEAD decryption and tag validation.
 *
 * The function will return immediately.
 *
 * The user shall check operation status with crm_aead_status() or CRM_AEAD_WAIT().
 *
 * @param[inout] c AEAD operation context
 * @param[in] tag authentication tag
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_TOO_BIG
 *
 * @pre - one of the CRM_AEAD_FEED_AAD() or CRM_AEAD_CRYPT() functions must be
 *        called first
 *
 * @remark - \p tag buffer should not be changed until the operation is
 *           completed.
 * @remark - if used with context saving(last chunk), the fed data size for
 *         the last chunk can not be 0
 */
typedef int (*FUNC_CRM_AEAD_VERIFY_TAG)(struct crmaead *c, const char *tagin);
#define CRM_AEAD_VERIFY_TAG                             ((FUNC_CRM_AEAD_VERIFY_TAG)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_AEAD_VERIFY_TAG)))


/** Resumes AEAD operation in context-saving.
 *
 * This function shall be called when using context-saving to load the state
 * that was previously saved by crm_aead_save_state() in the crmaead
 * operation context \p c. It must be called with the same crmaead operation
 * context \p c that was used with crm_aead_save_state(). It will reserve
 * all hardware resources required to run the partial AEAD operation.
 * Previously used mode and direction are already stored in crmaead \p c.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the AEAD functions, except the crm_aead_create_*()
 * functions.
 *
 * @param[inout] c AEAD operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_CONTEXT_SAVING_NOT_SUPPORTED
 * @return ::CRM_ERR_INVALID_KEYREF
 * @return ::CRM_ERR_INVALID_KEY_SZ
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @pre - crm_aead_create_aes*() and crm_aead_save_state() functions
 *        must be called before, for first part of the message.
 * @pre - must be called for each part of the message(besides first), before
 *        CRM_AEAD_CRYPT() or crm_aead_save_state().
 *
 * @remark - the user must not change the key until all parts of the message to
 *           be encrypted/decrypted are processed.
 */
typedef int (*FUNC_CRM_AEAD_RESUME_STATE)(struct crmaead *c);
#define CRM_AEAD_RESUME_STATE                           ((FUNC_CRM_AEAD_RESUME_STATE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_AEAD_RESUME_STATE)))


/** Starts a partial AEAD operation.
 *
 * This function is used to start a partial encryption or decryption of
 * \p datain. The function will return immediately.
 *
 * The partial result will be transfered to \p dataout only after the operation
 * is successfully completed. The user shall check operation status with
 * crm_aead_status() or CRM_AEAD_WAIT().
 *
 * @param[inout] c AEAD operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_CONTEXT_SAVING_NOT_SUPPORTED
 * @return ::CRM_ERR_WRONG_SIZE_GRANULARITY
 *
 * @pre - CRM_AEAD_CRYPT() should be called first.
 *
 * @remark - the user must not change the key until all parts of the message to
 *           be encrypted/decrypted are processed.
 * @remark - when in context saving, the sizes of the chunks fed must be
 *           multiple of 16 bytes, besides the last chunk that can be any size,
 *           but not 0
 */
typedef int (*FUNC_CRM_AEAD_SAVE_STATE)(struct crmaead *c);
#define CRM_AEAD_SAVE_STATE                             ((FUNC_CRM_AEAD_SAVE_STATE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_AEAD_SAVE_STATE)))


/** Waits until the given AEAD operation has finished
 *
 * This function returns when the AEAD operation was successfully completed,
 * or when an error has occurred that caused the operation to terminate.
 *
 * The return value of this function is the operation status.
 *
 * After this call, all resources have been released and \p c cannot be used
 * again unless crm_aead_create_*() is used.
 *
 * making \p c unusable for a new operation without calling, first, one of the
 * crm_aead_create_*() functions.
 *
 * @param[inout] c AEAD operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_DMA_FAILED
 * @return ::CRM_ERR_INVALID_TAG
 *
 * @pre - crm_aead_encrypt or crm_aead_decrypt() function must be called first
 *
 * @see crm_aead_status().
 *
 * @remark - this function is blocking until operation finishes.
 */
typedef int (*FUNC_CRM_AEAD_WAIT)(struct crmaead *c);
#define CRM_AEAD_WAIT                                   ((FUNC_CRM_AEAD_WAIT)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_AEAD_WAIT)))


/** Returns the AEAD operation status.
 *
 * If the operation is still ongoing, return ::CRM_ERR_HW_PROCESSING.
 * In that case, the user can retry later.
 *
 * When this function returns with a code different than ::CRM_ERR_HW_PROCESSING,
 * the AEAD operation has ended and all resources used by the AEAD operation
 * context \p c have been released. In this case, \p c cannot be used for a new
 * operation until one of the crm_aead_create_*() functions is called again.
 *
 * @param[inout] c AEAD operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_HW_PROCESSING
 * @return ::CRM_ERR_DMA_FAILED
 * @return ::CRM_ERR_INVALID_TAG
 *
 * @pre - crm_aead_encrypt or crm_aead_decrypt() function must be called first
 *
 * @remark -  if authentication fails during decryption, ::CRM_ERR_INVALID_TAG
 *            will be returned. In this case, the decrypted text is not valid
 *            and shall not be used.
 */
typedef int (*FUNC_CRM_AEAD_STATUS)(struct crmaead *c);
#define CRM_AEAD_STATUS                                 ((FUNC_CRM_AEAD_STATUS)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_AEAD_STATUS)))
#endif
