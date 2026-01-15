/** "crmops" interface to finalise acceleration requests
 * and get the output operands
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

#ifndef CRMOPS_IMPL_HEADER_FILE
#define CRMOPS_IMPL_HEADER_FILE

#include <driver/security/cryptopk/version.h>

/** Make sure the application is compatible with CryptoPK API version **/
CRM_PK_API_ASSERT_COMPATIBLE(1, 0);

/** Finish an operation with one result operands
 *
 * Write the single result in the result operand
 * and release the reserved resources.
 *
 * @pre The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[in] pkhw The acceleration request where an
 * operation with 1 output operands has finished
 * @param[out] result Result operand of a single output operand operation
 */
static inline
void crm_async_finish_single(crm_pk_accel *pkhw, crm_op *result)
{
   const char **outputs = CRM_PK_GET_OUTPUT_OPS(pkhw);
   const int opsz = CRM_PK_GET_OPSIZE(pkhw);

   CRM_PK_MEM2OP(outputs[0], opsz, result);

   CRM_PK_RELEASE_REQ(pkhw);
}

/** Finish an operation with two result operands
 *
 * Write the two results in the result operand
 * and release the reserved resources.
 *
 * @pre The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[in] pkhw The acceleration request where the
 * operation with 2 output operands has finished
 * @param[out] r1 First result operand of the operation
 * @param[out] r2 Second result operand of the operation
 */
static inline
void crm_async_finish_pair(crm_pk_accel *pkhw, crm_op *r1, crm_op *r2)
{
   const char **outputs = CRM_PK_GET_OUTPUT_OPS(pkhw);
   const int opsz = CRM_PK_GET_OPSIZE(pkhw);

   CRM_PK_MEM2OP(outputs[0], opsz, r1);
   CRM_PK_MEM2OP(outputs[1], opsz, r2);

   CRM_PK_RELEASE_REQ(pkhw);
}

/** Finish an operation with four result operands
 *
 * Write the four results in the result operand buffers
 * and release the reserved resources.
 *
 * @pre The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[in] pkhw The acceleration request where the
 * operation with 4 resulting operands has finished
 * @param[out] r1 First result operand of the operation
 * @param[out] r2 Second result operand of the operation
 * @param[out] r3 Third result operand of the operation
 * @param[out] r4 Fourth result operand of the operation
 */
static inline
void crm_async_finish_quad(crm_pk_accel *pkhw, crm_op *r1, crm_op *r2, crm_op *r3, crm_op *r4)
{
   const char **outputs = CRM_PK_GET_OUTPUT_OPS(pkhw);
   const int opsz = CRM_PK_GET_OPSIZE(pkhw);

   CRM_PK_MEM2OP(outputs[0], opsz, r1);
   CRM_PK_MEM2OP(outputs[1], opsz, r2);
   CRM_PK_MEM2OP(outputs[2], opsz, r3);
   CRM_PK_MEM2OP(outputs[3], opsz, r4);

   CRM_PK_RELEASE_REQ(pkhw);
}

/** Finish an operation with any number of result operands
 *
 * Write results in the result operand buffer
 * and release the reserved resources.
 *
 * @pre The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[in] pkhw The acceleration request where the
 * operation with 'count' resulting operands has finished
 * @param[out] results Buffer of result operands of the operation
 * @param[in] count The number of result operands
 */
static inline
void crm_async_finish_any(crm_pk_accel *pkhw, crm_op **results, int count)
{
   const char **outputs = CRM_PK_GET_OUTPUT_OPS(pkhw);
   const int opsz = CRM_PK_GET_OPSIZE(pkhw);

   for (int i=0; i < count; i++)
      CRM_PK_MEM2OP(outputs[i], opsz, results[i]);
   CRM_PK_RELEASE_REQ(pkhw);
}
#endif
