/** True Random Number Generator (TRNG)
 *
 * @file
 *
 * The TRNG uses the hardware to generate random number with a high
 * level of entropy. It's intended to feed entropy into a DRBG.
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
#ifndef TRNG_API_H
#define TRNG_API_H

#include <stdint.h>
#include <stddef.h>
#include "driver/security/cryptosym/trnginternal.h"
#include "driver/security/api_table.h"

/** Configuration parameters for the TRNG */
struct crm_trng_config {
    /** FIFO level below which the module leaves the idle state to refill the FIFO
     * 
     * In numbers of 128-bit blocks.
     * 
     * Set to 0 to use default.
     */
    unsigned int wakeup_level;
    
    /** Number of clock cycles to wait before sampling data from the noise source
     * 
     * Set to 0 to use default.
     */
    unsigned int init_wait;
    
    /** Number of clock cycles to wait before stopping the rings after the FIFO is full.
     * 
     * Set to 0 to use default.
     */
    unsigned int off_time_delay;
    
    /** Clock divider for the frequency at which the outputs of the rings are sampled.
     * 
     * Set to 0 to sample at APB interface clock frequency.
     */
    unsigned int sample_clock_div;
};

/** TRNG initialization
 *
 * @param[inout] ctx TRNG context to be used in other operations
 * @param[in] config pointer to optional configuration. NULL to use default.
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_INCOMPATIBLE_HW
 */
typedef int (*FUNC_CRM_TRNG_INIT)(struct crm_trng *ctx, const struct crm_trng_config *config);
#define CRM_TRNG_INIT                              ((FUNC_CRM_TRNG_INIT)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_TRNG_INIT)))

/** Get random bytes
 *
 * When this function returns ::CRM_OK, \p size random bytes have been
 * written to the \p dst memory location. If not enough random bytes are
 * available, the function does not write any data to \p dst and returns
 * ::CRM_ERR_INSUFFICIENT.
 *
 * @param[inout] ctx TRNG context to be used in other operations
 * @param[out] dst Destination in memory to copy \p size bytes to
 * @param[in] size length in bytes
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_INSUFFICIENT
 * @return ::CRM_ERR_HARDWARE_FAILURE
 */
typedef int (*FUNC_CRM_TRNG_GET)(struct crm_trng *ctx, char *dst, size_t size);
#define CRM_TRNG_GET                                    ((FUNC_CRM_TRNG_GET)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_TRNG_GET)))

#endif
