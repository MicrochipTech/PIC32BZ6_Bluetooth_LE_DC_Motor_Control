/** Status/error codes of crmsymcrypt functions
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
#ifndef STATUSCODES_API_FILE
#define STATUSCODES_API_FILE

/** The function or operation succeeded */
#define CRM_OK 0

/** Waiting on the hardware to process this operation */
#define CRM_ERR_HW_PROCESSING -1

/** No hardware available for a new operation. Retry later. */
#define CRM_ERR_RETRY -2

/** No compatible hardware for this operation.
 *
 * This error occurs if the dedicated hardware to execute the operation is not
 * present, or hardware is present and operation not supported by it.
 */
#define CRM_ERR_INCOMPATIBLE_HW -3

/** Invalid authentication tag in authenticated decryption */
#define CRM_ERR_INVALID_TAG -16

/** Hardware DMA error
 *
 * Fatal error that should never happen. Can be caused by invalid or
 * wrong addresses, RAM corruption, a hardware or software bug or system
 * corruption.
 */
#define CRM_ERR_DMA_FAILED -32

/** Fatal error, trying to call a function with an uninitialized object
 *
 * For example calling crm_aead_decrypt() with an crmaead object which
 * has not been created yet with crm_aead_create_*() function.
 */
#define CRM_ERR_UNITIALIZED_OBJ -33

/** Fatal error, trying to call an AEAD or block cipher create function with an
 * uninitialized or invalid key reference.
 *
 * Examples: calling crm_blkcipher_create_aesecb() with a key reference which
 * has not been initialized yet with crm_keyref_load_material() or crm_keyref_load_by_id()
 * function, crm_keyref_load_material() was called with key NULL or size 0, or
 * crm_keyref_load_by_id() was called with an invalid index ID.
 */
#define CRM_ERR_INVALID_KEYREF -34

/** Fatal error, trying to create instance with not enough memory */
#define CRM_ERR_ALLOCATION_TOO_SMALL -35

/** Input or output buffer size too large */
#define CRM_ERR_TOO_BIG -64

/** Input or output buffer size too small */
#define CRM_ERR_TOO_SMALL -65

/** The given key size is not supported by the algorithm or the hardware */
#define CRM_ERR_INVALID_KEY_SZ -66

/** Input tag size is invalid */
#define CRM_ERR_INVALID_TAG_SIZE -67

/** Input nonce size is invalid */
#define CRM_ERR_INVALID_NONCE_SIZE -68

/** Too many feeds were inputed */
#define CRM_ERR_FEED_COUNT_EXCEEDED -69

/** Input data size granularity is incorrect */
#define CRM_ERR_WRONG_SIZE_GRANULARITY -70

/** Attempt to use HW keys with a mode that does not support HW keys */
#define CRM_ERR_HW_KEY_NOT_SUPPORTED -71

/** Attempt to use a mode or engine that does not support context saving */
#define CRM_ERR_CONTEXT_SAVING_NOT_SUPPORTED -72

/** Attempt to feed AAD after input data was fed */
#define CRM_ERR_FEED_AFTER_DATA -73


/** Hardware cannot work anymore.
 *
 * To recover, reset the hardware.
 */
#define CRM_ERR_RESET_NEEDED -82

#endif
