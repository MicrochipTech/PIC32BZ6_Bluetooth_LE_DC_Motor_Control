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
  Middleware AES Source File

  Company:
    Microchip Technology Inc.

  File Name:
    mw_aes.c

  Summary:
    Implements AES encryption/decryption functions for use in applications.

  Description:
    This source file provides a set of functions to handle AES (Advanced
    Encryption Standard) encryption and decryption processes, facilitating
    secure data handling in application-level code. It abstracts the complexity
    of cryptographic operations, offering a user-friendly interface for
    integrating AES into various software solutions.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "device.h"
#include "driver/security/cryptosym/keyref_api.h"
#include "driver/security/cryptopk/statuscodes_api.h"
#include "driver/security/cryptosym/aead_api.h"

#include "mba_error_defs.h"
#include "mw_aes.h"

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************
/** 
 * @brief Initializes AES CBC block cipher decryption.
 *
 * @param[out] p_ctx               Pointer to the AES context structure.
 * @param[in] p_aesKey             Pointer to the 16-byte encryption key.
 * @param[in] p_iv                 Pointer to the 16-byte initialization vector (IV).
 *
 * @retval MBA_RES_SUCCESS         Initialize successfully.
 * @retval MBA_RES_FAIL            Initialization failed.
 */
uint16_t MW_AES_CbcDecryptInit(MW_AES_Ctx_T * p_ctx, uint8_t *p_aesKey, uint8_t *p_iv)
{
    uint16_t result;

    CRYPTO_CLK_ENABLE();
    
    p_ctx->aesKeyRef=CRM_KEYREF_LOAD_MATERIAL(16, (char *)p_aesKey);
    if (CRM_OK!=CRM_BLKCIPHER_CREATE_AESCBC_DEC(&p_ctx->aesBlkCipher, &p_ctx->aesKeyRef, (char *)p_iv))
    {
        result = MBA_RES_FAIL;
    }
    else
    {
        result = MBA_RES_SUCCESS;
    }
    
    CRYPTO_CLK_DISABLE();

    return result;

}


/**
 * @brief Decrypts a block of data using AES CBC mode.
 *
 * @param[in] p_ctx                Pointer to the AES context structure.
 * @param[in] length               The length of the data to be decrypted.
 * @param[out] p_plainText         Pointer to the buffer where the decrypted data will be stored.
 * @param[in] p_cipherText         Pointer to the buffer containing the data to be decrypted.
 *
 * @retval MBA_RES_SUCCESS         Decryption successful.
 * @retval MBA_RES_FAIL            Decryption failed.
 */
uint16_t MW_AES_AesCbcDecrypt(MW_AES_Ctx_T * p_ctx, uint16_t length, uint8_t *p_plainText, uint8_t *p_cipherText)
{
    int32_t s;

    CRYPTO_CLK_ENABLE();

    s = CRM_BLKCIPHER_CRYPT(&p_ctx->aesBlkCipher, (char *)p_cipherText, length, (char *)p_plainText);
    if (s == CRM_OK)
    {
        s = CRM_BLKCIPHER_SAVE_STATE(&p_ctx->aesBlkCipher);
    }
    if (s == CRM_OK)
    {
    s = CRM_BLKCIPHER_WAIT(&p_ctx->aesBlkCipher);
    }
    if (s == CRM_OK)
    {
    s = CRM_BLKCIPHER_RESUME_STATE(&p_ctx->aesBlkCipher);
    }

    CRYPTO_CLK_DISABLE();


    if (s != CRM_OK)
    {
        return MBA_RES_FAIL;
    }

    return MBA_RES_SUCCESS;
}


/**
 * @brief Initializes AES ECB block cipher encryption.
 *
 * @param[out] p_ctx               Pointer to the AES context structure.
 * @param[in] p_aesKey             Pointer to the 16-byte encryption key.
 *
 * @retval MBA_RES_SUCCESS         Initialization successful.
 * @retval MBA_RES_FAIL            Initialization failed.
 */
uint16_t MW_AES_EcbEncryptInit(MW_AES_Ctx_T * p_ctx, uint8_t *p_aesKey)
{
    uint16_t result;

    CRYPTO_CLK_ENABLE();
    
    p_ctx->aesKeyRef=CRM_KEYREF_LOAD_MATERIAL(16, (char *)p_aesKey);
    if (CRM_OK!=CRM_BLKCIPHER_CREATE_AESECB_ENC(&p_ctx->aesBlkCipher, &p_ctx->aesKeyRef))
    {
        result = MBA_RES_FAIL;
    }
    else
    {
        result = MBA_RES_SUCCESS;
    }
    
    CRYPTO_CLK_DISABLE();

    return result;

}


/**
 * @brief Encrypts a block of data using AES ECB mode.
 *
 * @param[in] p_ctx                Pointer to the AES context structure.
 * @param[in] length               The length of the data to be encrypted.
 * @param[out] p_cipherText        Pointer to the buffer where the encrypted data will be stored.
 * @param[in] p_plainText          Pointer to the buffer containing the data to be encrypted.
 *
 * @retval MBA_RES_SUCCESS         Encryption successful.
 * @retval MBA_RES_FAIL            Encryption failed.
 */
uint16_t MW_AES_AesEcbEncrypt(MW_AES_Ctx_T * p_ctx, uint16_t length, uint8_t *p_cipherText, uint8_t *p_plainText)
{
    int32_t s;

    CRYPTO_CLK_ENABLE();

    s = CRM_BLKCIPHER_CRYPT(&p_ctx->aesBlkCipher, (char *)p_plainText, length, (char *)p_cipherText);
    if (s == CRM_OK)
    {
        s = CRM_BLKCIPHER_RUN(&p_ctx->aesBlkCipher);
    }
    if (s == CRM_OK)
    {
        s = CRM_BLKCIPHER_WAIT(&p_ctx->aesBlkCipher);
    }

    CRYPTO_CLK_DISABLE();


    if (s != CRM_OK)
    {
        return MBA_RES_FAIL;
    }

    return MBA_RES_SUCCESS;
}

/**
 * @brief Initializes AES CCM encryption.
 *
 * @param[out] p_ctx               Pointer to the AES context structure.
 * @param[in] p_aesKey             Pointer to the 16-byte encryption key.
 * @param[in] p_nonce              Pointer to the nonce used for encryption.
 * @param[in] nonceSz              The size of p_nonce, between 7 and 13 bytes.
 * @param[in] tagSz                The tag size used for encryption, must be a value in {4, 6, 8, 10, 12, 14, 16}.
 * @param[in] p_aad                Pointer to the additional authentication data.
 * @param[in] aadSz                The size of p_aad, can be 0 if p_aad is NULL.
 * @param[in] dataSz               The size of the data to be encrypted.
 *
 * @retval MBA_RES_SUCCESS         Initialization successful.
 * @retval MBA_RES_FAIL            Initialization failed.
 */
uint16_t MW_AES_CcmEncryptInit(MW_AES_Ctx_T * p_ctx, uint8_t *p_aesKey, uint8_t *p_nonce, uint8_t nonceSz, uint8_t tagSz, uint8_t *p_aad, uint16_t aadSz, uint16_t dataSz)
{
    int32_t s;

    CRYPTO_CLK_ENABLE();
    
    p_ctx->aesKeyRef=CRM_KEYREF_LOAD_MATERIAL(16, (char *)p_aesKey);
    s = CRM_AEAD_CREATE_AESCCM_ENC(&p_ctx->aeadCtx, &p_ctx->aesKeyRef, (char *)p_nonce, nonceSz, tagSz, aadSz, dataSz);

    if (s == CRM_OK)
    {
        s = CRM_AEAD_FEED_AAD(&p_ctx->aeadCtx, (const char *)p_aad, aadSz);
    }
    
    
    CRYPTO_CLK_DISABLE();

    if (s != CRM_OK)
    {
        return MBA_RES_FAIL;
    }

    p_ctx->aeadSize = dataSz;
    
    return MBA_RES_SUCCESS;
}


/**
 * @brief Encrypts data using AES CCM mode.
 *
 * @param[in] p_ctx                Pointer to the AES context structure.
 * @param[in] length               The length of the data to be encrypted. 
 *                                 Must be a multiple of 16 bytes, except for the last data fragment.
 * @param[in] p_plainText          Pointer to the buffer containing the data to be encrypted.
 * @param[out] p_cipherText        Pointer to the buffer where the encrypted data will be stored.
 * @param[out] p_tag               Pointer to the buffer where the authentication tag will be stored.
 *                                 Only valid if p_plainText is the last data fragment.
 *
 * @retval MBA_RES_SUCCESS         Encryption successful.
 * @retval MBA_RES_FAIL            Encryption failed.
 */
uint16_t MW_AES_AesCcmEncrypt(MW_AES_Ctx_T * p_ctx, uint16_t length, uint8_t *p_plainText, uint8_t *p_cipherText, uint8_t *p_tag)
{
    int32_t s;

    CRYPTO_CLK_ENABLE();


    
    s = CRM_AEAD_CRYPT(&p_ctx->aeadCtx, (char *)p_plainText, length, (char *)p_cipherText);

    if (s == CRM_OK)
    {
        if (p_ctx->aeadCtx.dataintotalsz < p_ctx->aeadSize)
        {
            s = CRM_AEAD_SAVE_STATE(&p_ctx->aeadCtx);

            if (s == CRM_OK)
            {
                s = CRM_AEAD_WAIT(&p_ctx->aeadCtx);
            }

            if (s == CRM_OK)
            {
                s = CRM_AEAD_RESUME_STATE(&p_ctx->aeadCtx);
            }
        }
        else
        {
            s = CRM_AEAD_PRODUCE_TAG(&p_ctx->aeadCtx, (char *)p_tag);
            
            if (s == CRM_OK)
            {
                s = CRM_AEAD_WAIT(&p_ctx->aeadCtx);
            }

        }
    }


    CRYPTO_CLK_DISABLE();


    if (s != CRM_OK)
    {
        return MBA_RES_FAIL;
    }

    return MBA_RES_SUCCESS;
}

/**
 * @brief Initializes AES CCM decryption.
 *
 * @param[out] p_ctx               Pointer to the AES context structure.
 * @param[in] p_aesKey             Pointer to the 16-byte encryption key.
 * @param[in] p_nonce              Pointer to the nonce used for encryption.
 * @param[in] nonceSz              The size of p_nonce, between 7 and 13 bytes.
 * @param[in] tagSz                The tag size used for encryption, must be a value in {4, 6, 8, 10, 12, 14, 16}.
 * @param[in] p_aad                Pointer to the additional authentication data.
 * @param[in] aadSz                The size of p_aad, can be 0 if p_aad is NULL.
 * @param[in] dataSz               The size of the data to be decrypted.
 *
 * @retval MBA_RES_SUCCESS         Initialization successful.
 * @retval MBA_RES_FAIL            Initialization failed.
 */
uint16_t MW_AES_CcmDecryptInit(MW_AES_Ctx_T * p_ctx, uint8_t *p_aesKey, uint8_t *p_nonce, uint8_t nonceSz, uint8_t tagSz, uint8_t *p_aad, uint16_t aadSz, uint16_t dataSz)
{
    int32_t s;

    CRYPTO_CLK_ENABLE();
    
    p_ctx->aesKeyRef=CRM_KEYREF_LOAD_MATERIAL(16, (char *)p_aesKey);
    s = CRM_AEAD_CREATE_AESCCM_DEC(&p_ctx->aeadCtx, &p_ctx->aesKeyRef, (char *)p_nonce, nonceSz, tagSz, aadSz, dataSz);

    if (s == CRM_OK)
    {
        s = CRM_AEAD_FEED_AAD(&p_ctx->aeadCtx, (const char *)p_aad, aadSz);
    }
    
    
    CRYPTO_CLK_DISABLE();

    if (s != CRM_OK)
    {
        return MBA_RES_FAIL;
    }

    p_ctx->aeadSize = dataSz;
    
    return MBA_RES_SUCCESS;
}

/**
 * @brief Decrypts data using AES CCM mode.
 *
 * @param[in] p_ctx                Pointer to the AES context structure.
 * @param[in] length               The length of the data to be decrypted. 
 *                                 Must be a multiple of 16 bytes, except for the last data fragment.
 * @param[in] p_cipherText         Pointer to the buffer containing the data to be decrypted.
 * @param[in] p_tag                Pointer to the buffer containing the authentication tag.
 *                                 Only be used if p_cipherText is the last data fragment.
 * @param[out] p_plainText         Pointer to the buffer where the decrypted data will be stored.
 *
 * @retval MBA_RES_SUCCESS         Encryption successful.
 * @retval MBA_RES_FAIL            Encryption failed.
 */
uint16_t MW_AES_AesCcmDecrypt(MW_AES_Ctx_T * p_ctx, uint16_t length, uint8_t *p_cipherText, uint8_t *p_tag, uint8_t *p_plainText)
{
    int32_t s;

    CRYPTO_CLK_ENABLE();

    s = CRM_AEAD_CRYPT(&p_ctx->aeadCtx, (char *)p_cipherText, length, (char *)p_plainText);

    if (s == CRM_OK)
    {
        if (p_ctx->aeadCtx.dataintotalsz < p_ctx->aeadSize)
        {
            s = CRM_AEAD_SAVE_STATE(&p_ctx->aeadCtx);

            if (s == CRM_OK)
            {
                s = CRM_AEAD_WAIT(&p_ctx->aeadCtx);
            }

            if (s == CRM_OK)
            {
                s = CRM_AEAD_RESUME_STATE(&p_ctx->aeadCtx);
            }
        }
        else
        {
            s = CRM_AEAD_VERIFY_TAG(&p_ctx->aeadCtx, (char *)p_tag);
            
            if (s == CRM_OK)
            {
                s = CRM_AEAD_WAIT(&p_ctx->aeadCtx);
            }

        }
    }


    CRYPTO_CLK_DISABLE();


    if (s != CRM_OK)
    {
        return MBA_RES_FAIL;
    }

    return MBA_RES_SUCCESS;
}

