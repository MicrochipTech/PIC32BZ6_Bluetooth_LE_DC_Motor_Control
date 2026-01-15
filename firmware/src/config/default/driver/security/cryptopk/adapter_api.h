/** "crmops" interface to read & write operands from/to memory
 *
 * @file
 */
/*
 * Copyright (c) 2018-2020 Silex Insight sa
 * Copyright (c) 2018-2020 Beerten Engineering scs
 * SPDX-License-Identifier: BSD-3-Clause
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

#ifndef ADAPTER_HEADER_FILE
#define ADAPTER_HEADER_FILE

#include <stdint.h>
#include "driver/security/api_table.h"

/** Write the operand into memory filling 'sz' bytes, 0-pading if needed
 *  in little endian format
 *
 * @param[in] op Operand written to memory. Data should have a
 * size smaller or equal to 'sz'
 * @param[in] mem Memory address to write the operand to
 * @param[in] sz Size in bytes of the operand
 */
typedef void (*FUNC_CRM_PK_OP2MEM_LE)(const crm_op *op, char *mem, int sz);
#define CRM_PK_OP2MEM_LE         ((FUNC_CRM_PK_OP2MEM_LE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_OP2MEM_LE)))

/** Write the operand into memory filling 'sz' bytes, 0-pading if needed
 *  in big endian format
 *
 * @param[in] op Operand written to memory. Data should have a
 * size smaller or equal to 'sz'
 * @param[in] mem Memory address to write the operand to
 * @param[in] sz Size in bytes of the operand
 */
typedef void (*FUNC_CRM_PK_OP2MEM_BE)(const crm_op *op, char *mem, int sz);
#define CRM_PK_OP2MEM_BE         ((FUNC_CRM_PK_OP2MEM_BE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_OP2MEM_BE)))

/** Write the operand into memory filling 'sz' bytes, 0-pading if needed
 *
 * @param[in] op Operand written to memory. Data should have
 * a size smaller or equal to 'sz'
 * @param[in] mem Memory address to write the operand to
 * @param[in] sz Size in bytes of the operand
 */
typedef void (*FUNC_CRM_PK_OP2MEM)(const crm_op *op, char *mem, int sz);
#define CRM_PK_OP2MEM         ((FUNC_CRM_PK_OP2MEM)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_OP2MEM)))

/** Write the operand into memory which has the exact size needed
 *  in little endian format
 *
 * @param[in] op Operand written to memory
 * @param[in] mem Memory address to write the operand to
 */
typedef void (*FUNC_CRM_PK_OP2VMEM_LE)(const crm_op *op, char *mem);
#define CRM_PK_OP2VMEM_LE         ((FUNC_CRM_PK_OP2VMEM_LE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_OP2VMEM_LE)))

/** Write the operand into memory which has the exact size needed
 *  in big endian format
 *
 * @param[in] op Operand written to memory
 * @param[in] mem Memory address to write the operand to
 */
typedef void (*FUNC_CRM_PK_OP2VMEM_BE)(const crm_op *op, char *mem);
#define CRM_PK_OP2VMEM_BE         ((FUNC_CRM_PK_OP2VMEM_BE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_OP2VMEM_BE)))

/** Write the operand into memory which has the exact size needed
 *
 * @param[in] op Operand written to memory. Data should be in big endian
 * @param[in] mem Memory address to write the operand to
 */
typedef void (*FUNC_CRM_PK_OP2VMEM)(const crm_op *op, char *mem);
#define CRM_PK_OP2VMEM         ((FUNC_CRM_PK_OP2VMEM)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_OP2VMEM)))

/** Convert raw little endian bytes format to operand
 *
 * @param[in] mem Memory address to read the operand from
 * @param[in] sz Size in bytes of the memory to read
 * @param[out] op Operand in which the raw little endian bytes are written.
 * Its size should be bigger or equal to 'sz'
 */
typedef void (*FUNC_CRM_PK_MEM2OP_LE)(const char *mem, int sz, crm_op *op);
#define CRM_PK_MEM2OP_LE         ((FUNC_CRM_PK_MEM2OP_LE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_MEM2OP_LE)))

/** Convert raw big endian bytes format to operand
 *
 * @param[in] mem Memory address to read the operand from
 * @param[in] sz Size in bytes of the memory to read
 * @param[out] op Operand in which the raw little endian bytes are written.
 * Its size should be bigger or equal to 'sz'
 */
typedef void (*FUNC_CRM_PK_MEM2OP_BE)(const char *mem, int sz, crm_op *op);
#define CRM_PK_MEM2OP_BE         ((FUNC_CRM_PK_MEM2OP_BE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_MEM2OP_BE)))

/** Convert raw bytes to operand
 *
 * @param[in] mem Memory address to read the operand from
 * @param[in] sz Size in bytes of the memory to read.
 * @param[out] op Operand in which the raw little endian bytes are written.
 * Its size should be bigger or equal to 'sz'
 */
typedef void (*FUNC_CRM_PK_MEM2OP)(const char *mem, int sz, crm_op *op);
#define CRM_PK_MEM2OP         ((FUNC_CRM_PK_MEM2OP)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_MEM2OP)))


/** Return the size in bytes of the operand.
 *
 * @param[in] op Operand
 * @return Operand size in bytes
 */
typedef int (*FUNC_CRM_OP_SIZE)(const crm_op *op);
#define CRM_OP_SIZE         ((FUNC_CRM_OP_SIZE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_OP_SIZE)))

#endif
