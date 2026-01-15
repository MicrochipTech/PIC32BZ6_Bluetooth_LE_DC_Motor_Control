/** Common functions used for generation a MAC (message authentication code).
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
#ifndef MAC_API_FILE
#define MAC_API_FILE

#include <stddef.h>
#include "driver/security/cryptosym/internal.h"
#include "driver/security/api_table.h"


/** Feeds data to be used for MAC generation.
 *
 * The function will return immediately.
 *
 * In order to start the operation CRM_MAC_GENERATE() must be called.
 *
 * @param[inout] c MAC operation context
 * @param[in] datain data to be processed, with size \p sz
 * @param[in] sz size, in bytes, of data to be processed
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_TOO_BIG
 * @return ::CRM_ERR_FEED_COUNT_EXCEEDED
 *
 * @pre - crm_mac_create_*() function must be called first
 *
 * @remark - this function can be called even if data size, \p sz, is 0.
 * @remark - this function can be called multiple times to feed multiple chunks
 *           scattered in memory.
 */
typedef int (*FUNC_CRM_MAC_FEED)(struct crmmac *c, const char *datain, size_t sz);
#define CRM_MAC_FEED                                    ((FUNC_CRM_MAC_FEED)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_MAC_FEED)))


/** Starts MAC generation operation.
 *
 * This function is used to start MAC generation.
 * The function will return immediately.
 *
 * The result will be transfered only after the operation is successfully
 * completed. The user shall check operation status with CRM_MAC_STATUS()
 * or CRM_MAC_WAIT().
 *
 * @param[inout] c MAC operation context
 * @param[out] mac generated MAC
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_TOO_SMALL
 *
 * @pre - CRM_MAC_FEED() function must be called first
 *
 * @remark - if used with context saving(last chunk), the fed data size for
 *         the last chunk can not be 0
 */
typedef int (*FUNC_CRM_MAC_GENERATE)(struct crmmac *c, char *mac);
#define CRM_MAC_GENERATE                                ((FUNC_CRM_MAC_GENERATE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_MAC_GENERATE)))


/** Resumes MAC operation in context-saving.
 *
 * This function shall be called when using context-saving to load the state
 * that was previously saved by CRM_MAC_SAVE_STATE() in the crmmac operation
 * context \p c. It must be called with the same crmmac operation context \p c
 * that was used with CRM_MAC_SAVE_STATE(). It will reserve all hardware
 * resources required to run the partial MAC operation.
 *
 * After successful execution of this function, the context \p c can be passed
 * to any of the block cipher functions, except the crm_mac_create_*()
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
 * @pre - crm_mac_create_*() and CRM_MAC_SAVE_STATE() functions
 *        must be called before, for first part of the message.
 * @pre - must be called for each part of the message(besides first), before
 *        crm_mac_crypt() or CRM_MAC_SAVE_STATE().
 *
 * @remark - the user must not change the key until all parts of the message to
 *           be encrypted/decrypted are processed.
 */
typedef int (*FUNC_CRM_MAC_RESUME_STATE)(struct crmmac *c);
#define CRM_MAC_RESUME_STATE                            ((FUNC_CRM_MAC_RESUME_STATE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_MAC_RESUME_STATE)))


/** Starts a partial MAC operation.
 *
 * This function is used to start a partial MAC operation on data fed using
 * CRM_MAC_FEED().
 * The function will return immediately.
 *
 * The partial result will be transfered only after the operation is
 * successfully completed. The user shall check operation status with
 * CRM_MAC_STATUS() or CRM_MAC_WAIT().
 *
 * @param[inout] c block cipher operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_CONTEXT_SAVING_NOT_SUPPORTED
 * @return ::CRM_ERR_TOO_SMALL
 * @return ::CRM_ERR_WRONG_SIZE_GRANULARITY
 *
 * @pre - crm_mac_crypt() should be called first.
 *
 * @remark - the user must not change the key until all parts of the message to
 *           be encrypted/decrypted are processed.
 */
typedef int (*FUNC_CRM_MAC_SAVE_STATE)(struct crmmac *c);
#define CRM_MAC_SAVE_STATE                              ((FUNC_CRM_MAC_SAVE_STATE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_MAC_SAVE_STATE)))


/** Waits until the given MAC generation operation has finished
 *
 * This function returns when the MAC generation operation was successfully
 * completed, or when an error has occurred that caused the operation to
 * terminate. The return value of this function is the operation status.
 *
 * After this call, all resources have been released and \p c cannot be used
 * again unless crm_mac_create_*() is used.
 *
 * @param[inout] c MAC generation operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_DMA_FAILED
 * @return ::CRM_ERR_INVALID_TAG
 *
 * @see CRM_MAC_STATUS().
 *
 * @remark - this function is blocking until operation finishes.
 */
typedef int (*FUNC_CRM_MAC_WAIT)(struct crmmac *c);
#define CRM_MAC_WAIT                                    ((FUNC_CRM_MAC_WAIT)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_MAC_WAIT)))


/** Returns the MAC generation operation status.
 *
 * If the operation is still ongoing, return ::CRM_ERR_HW_PROCESSING.
 * In that case, the user can retry later.
 *
 * When this function returns with a code different than ::CRM_ERR_HW_PROCESSING,
 * the MAC generation operation has ended and all resources used by MAC generation
 * operation context \p c have been released. In this case, \p c cannot be used
 * for a new operation until one of the crm_mac_create_*() functions is
 * called again.
 *
 * @param[inout] c MAC operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_HW_PROCESSING
 * @return ::CRM_ERR_DMA_FAILED
 * @return ::CRM_ERR_INVALID_TAG
 *
 * @pre - CRM_MAC_FEED() and CRM_MAC_GENERATE() functions must be called first
 */
typedef int (*FUNC_CRM_MAC_STATUS)(struct crmmac *c);
#define CRM_MAC_STATUS                                  ((FUNC_CRM_MAC_STATUS)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_MAC_STATUS)))
#endif
