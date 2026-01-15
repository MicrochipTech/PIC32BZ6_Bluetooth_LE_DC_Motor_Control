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
  Middleware AES Header File

  Company:
    Microchip Technology Inc.

  File Name:
    mw_aes.h

  Summary:
    Provides an interface for the Advanced Encryption Standard (AES) functionality
    within the BLE middleware.

  Description:
    This header file exposes the AES cryptographic functions that are part of the
    BLE middleware, enabling the application user to perform encryption and decryption
    operations in compliance with the AES standard.
 *******************************************************************************/
#ifndef MW_AES_H
#define MW_AES_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "driver/security/cryptosym/blkcipher_api.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/**
 * @addtogroup BLE_MW BLE Middleware
 * @{
 */

/**
 * @defgroup MW_AES Advanced Encryption Standard (AES)
 * 
 * @brief Provides AES cryptographic functions for BLE applications.
 * @note This section declares the API for the AES component of the BLE middleware.
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup MW_AES_STRUCTS Structures
 * @{
 */

/** @brief Structure for maintaining AES encryption context. */
typedef struct MW_AES_Ctx_T
{
    struct crmblkcipher aesBlkCipher;                                /**< Block cipher context for AES operations. */
    struct crmkeyref    aesKeyRef;                                   /**< Reference to the AES key for encryption or decryption. */
    struct crmaead      aeadCtx;                                     /**< Cipher context for AEAD operations. */
    uint16_t            aeadSize;                                    /**< Data size for AEAD operations. */
} MW_AES_Ctx_T;


/** @} */ //MW_AES_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup MW_AES_FUNS Functions
 * @{
 */

/** @brief Initializes AES CBC block cipher decryption.
 *
 * @param[out] p_ctx               Pointer to the AES context structure. See @ref MW_AES_Ctx_T.
 * @param[in] p_aesKey             Pointer to the 16-byte encryption key.
 * @param[in] p_iv                 Pointer to the 16-byte initialization vector (IV).
 *
 * @retval MBA_RES_SUCCESS         Initialization successful.
 * @retval MBA_RES_FAIL            Initialization failed.
 */
uint16_t MW_AES_CbcDecryptInit(MW_AES_Ctx_T * p_ctx, uint8_t *p_aesKey, uint8_t *p_iv);


/**
 * @brief Decrypts a block of data using AES CBC mode.
 *
 * @param[in] p_ctx                Pointer to the AES context structure. See @ref MW_AES_Ctx_T.
 * @param[in] length               The length of the data to be decrypted.
 * @param[out] p_plainText         Pointer to the buffer where the decrypted data will be stored.
 * @param[in] p_cipherText         Pointer to the buffer containing the data to be decrypted.
 *
 * @retval MBA_RES_SUCCESS         Decryption successful.
 * @retval MBA_RES_FAIL            Decryption failed.
 */
uint16_t MW_AES_AesCbcDecrypt(MW_AES_Ctx_T * p_ctx, uint16_t length, uint8_t *p_plainText, uint8_t *p_cipherText);


/**
 * @brief Initializes AES ECB block cipher encryption.
 *
 * @param[out] p_ctx               Pointer to the AES context structure. See @ref MW_AES_Ctx_T.
 * @param[in] p_aesKey             Pointer to the 16-byte encryption key.
 *
 * @retval MBA_RES_SUCCESS         Initialization successful.
 * @retval MBA_RES_FAIL            Initialization failed.
 */
uint16_t MW_AES_EcbEncryptInit(MW_AES_Ctx_T * p_ctx, uint8_t *p_aesKey);


/**
 * @brief Encrypts a block of data using AES ECB mode.
 *
 * @param[in] p_ctx                Pointer to the AES context structure. See @ref MW_AES_Ctx_T.
 * @param[in] length               The length of the data to be encrypted.
 * @param[out] p_cipherText        Pointer to the buffer where the encrypted data will be stored.
 * @param[in] p_plainText          Pointer to the buffer containing the data to be encrypted.
 *
 * @retval MBA_RES_SUCCESS         Encryption successful.
 * @retval MBA_RES_FAIL            Encryption failed.
 */
uint16_t MW_AES_AesEcbEncrypt(MW_AES_Ctx_T * p_ctx, uint16_t length, uint8_t *p_cipherText, uint8_t *p_plainText);

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
uint16_t MW_AES_CcmEncryptInit(MW_AES_Ctx_T * p_ctx, uint8_t *p_aesKey, uint8_t *p_nonce, uint8_t nonceSz, uint8_t tagSz, uint8_t *p_aad, uint16_t aadSz, uint16_t dataSz);

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
uint16_t MW_AES_AesCcmEncrypt(MW_AES_Ctx_T * p_ctx, uint16_t length, uint8_t *p_plainText, uint8_t *p_cipherText, uint8_t *p_tag);

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
uint16_t MW_AES_CcmDecryptInit(MW_AES_Ctx_T * p_ctx, uint8_t *p_aesKey, uint8_t *p_nonce, uint8_t nonceSz, uint8_t tagSz, uint8_t *p_aad, uint16_t aadSz, uint16_t dataSz);


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
uint16_t MW_AES_AesCcmDecrypt(MW_AES_Ctx_T * p_ctx, uint16_t length, uint8_t *p_cipherText, uint8_t *p_tag, uint8_t *p_plainText);


/** @} */ //MW_AES_FUNS

/** @} */

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif //MW_AES_H
