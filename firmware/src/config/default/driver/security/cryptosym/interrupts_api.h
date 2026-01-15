/** Hardware interrupts
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
#ifndef INTERRUPTS_API_FILE
#define INTERRUPTS_API_FILE

#include <stddef.h>
#include "driver/security/cryptosym/internal.h"
#include "driver/security/api_table.h"

/** Prepares the hardware to use hardware interrupts.
 *
 * This function may be called only once, before any function that starts an
 * aead, blkcipher, or hash operation.
 *
 * @return ::CRM_OK
 *
 * @remark - hardware interrupts are not available for cmmask.
 */
typedef int (*FUNC_CRM_INTERRUPTS_ENABLE)(void);
#define CRM_INTERRUPTS_ENABLE                           ((FUNC_CRM_INTERRUPTS_ENABLE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_INTERRUPTS_ENABLE)))

/** Disables all hardware interrupts.
 *
 * This function may be called only when there is no ongoing hardware
 * processing.
 *
 * @return ::CRM_OK
 */
typedef int (*FUNC_CRM_INTERRUPTS_DISABLE)(void);
#define CRM_INTERRUPTS_DISABLE                          ((FUNC_CRM_INTERRUPTS_DISABLE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_INTERRUPTS_DISABLE)))
#endif
