/** AES counter-measures mask load
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
 * The following example shows typical sequence of function calls for
 * loading the counter-measure mask.
   @code
       CRM_CM_LOAD_MASK(ctx, value)
       CRM_CM_LOAD_MASK_WAIT(ctx)
   @endcode
 */

#ifndef CMMASK_API_FILE
#define CMMASK_API_FILE

#include <stddef.h>
#include "driver/security/cryptosym/internal.h"
#include "driver/security/api_table.h"


/** Loads random used in the AES counter-measures.
 *
 * Counter-measures are available for the AES, if enabled in HW.
 * This function initializes the user allocated object \p c with a new
 * counter-measures mask load operation context and reserves the HW resource.
 *
 * After the initialization of \p c, this function starts the load of the
 * counter-measure cryptographically secure random \p value.
 * The function will return immediately. No data will be received for the
 * load operation.
 *
 * The operation is considered successful if the status returned by
 * CRM_CM_LOAD_MASK_WAIT() or CRM_CM_LOAD_MASK_STATUS() is ::CRM_OK.
 *
 * @param[out] c counter-measures mask load operation context
 * @param[in] value counter-measures random value to be loaded
 * @return ::CRM_OK
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 * @return ::CRM_ERR_RETRY
 *
 * @remark - it is under the user responsibility to call it after system boot
 *           (not automatically called).
 * @remark - for more details see the technical report: "Secure and Efficient
 *           Masking of AES - A Mission Impossible?", June 2004)
 */
typedef int (*FUNC_CRM_CM_LOAD_MASK)(struct crmcmmask *c, uint32_t value);
#define CRM_CM_LOAD_MASK                                ((FUNC_CRM_CM_LOAD_MASK)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_CM_LOAD_MASK)))


/** Waits until the given AES counter-measures load operation has finished.
 *
 * This function returns when the counter-measures load operation was
 * successfully completed, or when an error has occurred that caused the
 * operation to terminate.
 *
 * The return value of this function is the operation status.
 *
 * After this call, all resources have been released and \p c cannot be used
 * again unless CRM_CM_LOAD_MASK() is used.
 *
 * @param[inout] c counter-measures mask load operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_DMA_FAILED
 *
 * @pre - CRM_CM_LOAD_MASK() function must be called first
 *
 * @see CRM_CM_LOAD_MASK_STATUS().
 *
 * @remark - this function is blocking until operation finishes.
 */
typedef int (*FUNC_CRM_CM_LOAD_MASK_WAIT)(struct crmcmmask *c);
#define CRM_CM_LOAD_MASK_WAIT                           ((FUNC_CRM_CM_LOAD_MASK_WAIT)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_CM_LOAD_MASK_WAIT)))


/** Returns the status of the given AES counter-measures load operation context.
 *
 * If the operation is still ongoing, return ::CRM_ERR_HW_PROCESSING.
 * In that case, the user can retry later.
 *
 * When this function returns with a code different than ::CRM_ERR_HW_PROCESSING,
 * the counter-measures mask load operation has ended and all resources used by
 * counter-measures mask load operation context \p c have been released. In this
 * case, \p c cannot be used for a new operation until CRM_CM_LOAD_MASK() is
 * called again.
 *
 * @param[inout] c counter-measures mask load operation context
 * @return ::CRM_OK
 * @return ::CRM_ERR_UNITIALIZED_OBJ
 * @return ::CRM_ERR_HW_PROCESSING
 * @return ::CRM_ERR_DMA_FAILED
 *
 * @pre - CRM_CM_LOAD_MASK() function must be called first
 */
typedef int (*FUNC_CRM_CM_LOAD_MASK_STATUS)(struct crmcmmask *c);
#define CRM_CM_LOAD_MASK_STATUS                         ((FUNC_CRM_CM_LOAD_MASK_STATUS)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_CM_LOAD_MASK_STATUS)))
#endif
