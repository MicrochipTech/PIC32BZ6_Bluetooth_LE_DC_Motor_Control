/** "crmops" interface for RSA and GF(p) cryptographic computations
 *
 * Simpler functions to perform public key crypto operations. Included directly
 * in some interfaces (like crmbuf or OpenSSL engine). The functions
 * take input operands (large integers) and output operands
 * which will get the computed results.
 *
 * Operands have the "crm_op" type. The specific interfaces (like crmbuf) define
 * the "crm_op" type.
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

#ifndef RSA_HEADER_FILE
#define RSA_HEADER_FILE

#include <driver/security/cryptopk/core_api.h>
#include "driver/security/api_table.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/security/cryptopk/adapter_api.h"
#include "driver/security/cryptopk/impl.h"
#include <driver/security/cryptopk/inputslots.h>
#include <driver/security/cryptopk/version.h>

/** Make sure the application is compatible with CryptoPK API version **/
CRM_PK_API_ASSERT_COMPATIBLE(1, 0);

struct crm_pk_cmd_def;

/**
 * @addtogroup CRM_PK_CRMOPS_MOD
 *
 * @{
 */

/** Asynchronous (non-blocking) Primitive modular operation with 1 operand
 *
 * Start a primitive modular operation with 1 operand on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_async_finish_single()
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] cmd Command definition. Should be a primitive modular
 * operation with 1 operands. For example:
 *    ::CRM_PK_CMD_ODD_MOD_INV, ::CRM_PK_CMD_ODD_MOD_REDUCE,
 *    ::CRM_PK_CMD_EVEN_MOD_INV, ::CRM_PK_CMD_EVEN_MOD_REDUCE
 * @param[in] modulo Modulus operand. Must be odd if using ::CRM_PK_CMD_ODD_MOD_INV
 * or ::CRM_PK_CMD_ODD_MOD_REDUCE command and even when using ::CRM_PK_CMD_EVEN_MOD_INV
 * or ::CRM_PK_CMD_EVEN_MOD_REDUCE command
 * @param[in] b Operand of modular operation
 *
 * @return Acquired acceleration request for this operation
 */
static inline
struct crm_pk_dreq crm_async_mod_single_op_cmd_go(
      struct crm_pk_cnx *cnx,
      const struct crm_pk_cmd_def *cmd,
      const crm_op *modulo,
      const crm_op *b)
{
   struct crm_pk_dreq pkreq;
   struct crm_pk_inops_mod_single_op_cmd inputs;

   pkreq = CRM_PK_ACQUIRE_REQ(cnx, cmd);
   if (pkreq.status)
      return pkreq;

   // convert and transfer operands
   int sizes[] = {
      CRM_OP_SIZE(modulo),
      CRM_OP_SIZE(b),
   };
   pkreq.status = CRM_PK_LIST_GFP_INSLOTS(pkreq.req, sizes, (struct crm_pk_slot *)&inputs);
   if (pkreq.status)
      return pkreq;
   CRM_PK_OP2VMEM(modulo, inputs.n.addr);
   CRM_PK_OP2VMEM(b, inputs.b.addr);

   CRM_PK_RUN(pkreq.req);

   return pkreq;
}


/** Compute single operand modular operation
 *
 *  - result = b mod modulo for ::CRM_PK_CMD_ODD_MOD_REDUCE, ::CRM_PK_CMD_EVEN_MOD_REDUCE
 *  - result = 1 / b mod modulo for ::CRM_PK_CMD_ODD_MOD_INV, ::CRM_PK_CMD_EVEN_MOD_INV
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] cmd Command definition. Should be a primitive modular
 * operation with 1 operand. For example:
 *    ::CRM_PK_CMD_ODD_MOD_REDUCE, ::CRM_PK_CMD_ODD_MOD_INV,
 *    ::CRM_PK_CMD_EVEN_MOD_REDUCE, ::CRM_PK_CMD_EVEN_MOD_INV
 * @param[in] modulo Modulus operand. Must be odd if using ::CRM_PK_CMD_ODD_MOD_INV
 * or ::CRM_PK_CMD_ODD_MOD_REDUCE command and even when using ::CRM_PK_CMD_EVEN_MOD_INV
 * or ::CRM_PK_CMD_EVEN_MOD_REDUCE command
 * @param[in] b Operand
 * @param[out] result Result operand
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_PARAM
 * @return ::CRM_ERR_NOT_INVERTIBLE
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @remark It is up to the user to use the corresponding command w.r.t.
 * the parity of the modulus
 *
 * @see crm_async_mod_single_op_cmd_go() and crm_async_finish_single()
 * for an asynchronous version
 */
static inline
int crm_mod_single_op_cmd(
      struct crm_pk_cnx *cnx,
      const struct crm_pk_cmd_def *cmd,
      const crm_op *modulo,
      const crm_op *b,
      crm_op *result)
{
   struct crm_pk_dreq pkreq;
   int status;

   pkreq = crm_async_mod_single_op_cmd_go(cnx, cmd, modulo, b);
   if (pkreq.status)
      return pkreq.status;

   status = CRM_PK_WAIT(pkreq.req);
   crm_async_finish_single(pkreq.req, result);

   return status;
}

/** Asynchronous (non-blocking) Primitive modular operation with 2 operands
 *
 * Start a primitive modular operation with 2 operands on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_async_finish_single()
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] cmd Command definition. Should be a primitive modular
 * operation with 2 operands. For example:
 *    ::CRM_PK_CMD_MOD_ADD, ::CRM_PK_CMD_MOD_SUB,
 *    ::CRM_PK_CMD_ODD_MOD_MULT, ::CRM_PK_CMD_ODD_MOD_DIV
 * @param[in] modulo Modulus operand for the modular operantion
 * @param[in] a First operand of modular operation
 * @param[in] b Second operand of modular operation
 *
 * @return Acquired acceleration request for this operation
 *
 * @see crm_mod_primitive_cmd() for a synchronous version
 */
static inline
struct crm_pk_dreq crm_async_mod_cmd_go(
      struct crm_pk_cnx *cnx,
      const struct crm_pk_cmd_def *cmd,
      const crm_op *modulo,
      const crm_op *a,
      const crm_op *b)
{
   struct crm_pk_dreq pkreq;
   struct crm_pk_inops_mod_cmd inputs;

   pkreq = CRM_PK_ACQUIRE_REQ(cnx, cmd);
   if (pkreq.status)
      return pkreq;

   // convert and transfer operands
   int sizes[] = {
      CRM_OP_SIZE(modulo),
      CRM_OP_SIZE(a),
      CRM_OP_SIZE(b),
   };
   pkreq.status = CRM_PK_LIST_GFP_INSLOTS(pkreq.req, sizes, (struct crm_pk_slot *)&inputs);
   if (pkreq.status)
      return pkreq;
   CRM_PK_OP2VMEM(modulo, inputs.n.addr);
   CRM_PK_OP2VMEM(a, inputs.a.addr);
   CRM_PK_OP2VMEM(b, inputs.b.addr);

   CRM_PK_RUN(pkreq.req);

   return pkreq;
}


/** Primitive modular operation with 2 operands
 *
 * - result = a + b mod modulo for ::CRM_PK_CMD_MOD_ADD
 * - result = a - b mod modulo for ::CRM_PK_CMD_MOD_SUB
 * - result = a * b mod modulo for ::CRM_PK_CMD_ODD_MOD_MULT with odd modulus
 * - result = a / b mod modulo for ::CRM_PK_CMD_ODD_MOD_DIV with odd modulus
 *
 * Perform a modular addition or subtraction or
 * odd modular multiplication or odd modular division.
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] cmd Command definition. Should be a primitive modular
 * operation with 2 operands. See description
 * @param[in] modulo Modulus operand for the modular operantion
 * @param[in] a First operand of modular operation
 * @param[in] b Second operand of modular operation
 * @param[out] result Result operand of the modular operation
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_NOT_INVERTIBLE
 * @return ::CRM_ERR_INVALID_PARAM
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @see crm_async_mod_cmd_go() and crm_async_finish_single()
 * for an asynchronous version
 */
static inline
int crm_mod_primitive_cmd(
      struct crm_pk_cnx *cnx,
      const struct crm_pk_cmd_def *cmd,
      const crm_op *modulo,
      const crm_op *a,
      const crm_op *b,
      crm_op *result)
{
   struct crm_pk_dreq pkreq;
   int status;

   pkreq = crm_async_mod_cmd_go(cnx, cmd, modulo, a, b);
   if (pkreq.status)
      return pkreq.status;

   status = CRM_PK_WAIT(pkreq.req);
   crm_async_finish_single(pkreq.req, result);

   return status;
}


/** Asynchronous (non-blocking) mod inversion.
 *
 * Start a modular inversion on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_async_finish_single()
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] modulo Modulus operand
 * @param[in] b Operand to inverse
 *
 * @return Acquired acceleration request for this operation
 *
 * @see crm_async_finish_single(), crm_mod_inv()
 */
static inline
struct crm_pk_dreq crm_async_mod_inv_go(
      struct crm_pk_cnx *cnx,
      const crm_op *modulo,
      const crm_op *b)
{
   return crm_async_mod_single_op_cmd_go(cnx, CRM_PK_CMD_ODD_MOD_INV, modulo, b);
}


/** Compute modular inversion
 *
 *    result = 1/b mod modulo
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] modulo Modulus operand
 * @param[in] b Operand to inverse
 * @param[out] result Result operand of the modular inversion
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_NOT_INVERTIBLE
 * @return ::CRM_ERR_INVALID_PARAM
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @see crm_async_mod_inv_go() for an asynchronous verion
 */
static inline
int crm_mod_inv(
      struct crm_pk_cnx *cnx,
      const crm_op *modulo,
      const crm_op *b,
      crm_op *result)
{
   struct crm_pk_dreq pkreq;
   int status;

   pkreq = crm_async_mod_inv_go(cnx, modulo, b);
   if (pkreq.status)
      return pkreq.status;

   status = CRM_PK_WAIT(pkreq.req);

   crm_async_finish_single(pkreq.req, result);

   return status;
}


/** Asynchronous (non-blocking) modular exponentiation.
 *
 * Start a modular exponentiation on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_async_mod_exp_end()
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] input Base operand for modular exponentiation
 * @param[in] exp Exponent operand
 * @param[in] m Modulus operand
 *
 * @return Acquired acceleration request for this operation
 *
 * @see crm_mod_exp() for the synchronous version
 */
static inline
struct crm_pk_dreq crm_async_mod_exp_go(
      struct crm_pk_cnx *cnx,
      const crm_op *input,
      const crm_op *exp,
      const crm_op *m)
{
    return crm_async_mod_cmd_go(cnx, CRM_PK_CMD_MOD_EXP, m, input, exp);
}


/** Finish asynchronous (non-blocking) modular exponentiation.
 *
 * Get the output operand of the modular exponentiation and release
 * the accelerator.
 *
 * @pre The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[inout] req The previously acquired acceleration
 * request for this operation
 * @param[out] result Result operand
 *
 * @see crm_async_mod_exp_go() and crm_mod_exp()
 */
static inline
void crm_async_mod_exp_end(
      crm_pk_accel *req,
      crm_op *result)
{
   crm_async_finish_single(req, result);
}


/** Compute modular exponentiation.
 *
 *    result = input ^ exp mod m
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] input Base operand
 * @param[in] exp Exponent operand
 * @param[in] m Modulus operand
 * @param[out] result Result operand
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_PARAM
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @see crm_async_mod_exp_go(), crm_async_mod_exp_end()
 * for an asynchronous version
 */
static inline
int crm_mod_exp(
        struct crm_pk_cnx *cnx,
        const crm_op *input,
        const crm_op *exp,
        const crm_op *m,
        crm_op *result)
{
   struct crm_pk_dreq pkreq;
   int status;

   pkreq = crm_async_mod_exp_go(cnx, input, exp, m);
   if (pkreq.status)
      return pkreq.status;

   status = CRM_PK_WAIT(pkreq.req);
   crm_async_mod_exp_end(pkreq.req, result);
   return status;
}

/** @} */

/**
 * @addtogroup CRM_PK_CRMOPS_RSA
 *
 * @{
 */


/** Asynchronous (non-blocking) modular exponentiation with CRT.
 *
 * Start a modular exponentiation with CRT on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_async_crt_mod_exp_end()
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] in Input
 * @param[in] p Prime number p
 * @param[in] q Prime number q
 * @param[in] dp d mod (p-1), with d the private key
 * @param[in] dq d mod (q-1), with d the private key
 * @param[in] qinv q^(-1) mod p

 * @return Acquired acceleration request for this operation
 *
 * @see crm_async_crt_mod_exp_end()
 */
static inline
struct crm_pk_dreq crm_async_crt_mod_exp_go(
      struct crm_pk_cnx *cnx,
      const crm_op *in,
      const crm_op *p,
      const crm_op *q,
      const crm_op *dp,
      const crm_op *dq,
      const crm_op *qinv)
{

   struct crm_pk_dreq pkreq;
   struct crm_pk_inops_crt_mod_exp inputs;

   pkreq = CRM_PK_ACQUIRE_REQ(cnx, CRM_PK_CMD_MOD_EXP_CRT);
   if (pkreq.status)
      return pkreq;

   // convert and transfer operands
   int sizes[] = {
      CRM_OP_SIZE(p),
      CRM_OP_SIZE(q),
      CRM_OP_SIZE(in),
      CRM_OP_SIZE(dp),
      CRM_OP_SIZE(dq),
      CRM_OP_SIZE(qinv)
   };
   pkreq.status = CRM_PK_LIST_GFP_INSLOTS(pkreq.req, sizes, (struct crm_pk_slot *)&inputs);
   if (pkreq.status)
      return pkreq;
   CRM_PK_OP2VMEM(in, inputs.in.addr);
   CRM_PK_OP2VMEM(p, inputs.p.addr);
   CRM_PK_OP2VMEM(q, inputs.q.addr);
   CRM_PK_OP2VMEM(dp, inputs.dp.addr);
   CRM_PK_OP2VMEM(dq, inputs.dq.addr);
   CRM_PK_OP2VMEM(qinv, inputs.qinv.addr);

   CRM_PK_RUN(pkreq.req);

   return pkreq;
}


/** Finish asynchronous (non-blocking) modular exponentiation with CRT.
 *
 * Get the output operand of the modular exponentiation with CRT
 * and release the reserved resources.
 *
 * @pre The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[inout] req The previously acquired acceleration
 * request for this operation
 * @param[out] result
 *
 * @see crm_async_crt_mod_exp_go()
*/
static inline
void crm_async_crt_mod_exp_end(
      crm_pk_accel *req,
      crm_op *result)
{
   crm_async_finish_single(req, result);
}


/** Compute modular exponentiation with CRT
 *
 *  Compute (result = in ^ db mod m) with those steps:
 *
 *   vp = in ^ dp mod p
 *   vq = in ^ dq mod q
 *   u = (vp -vq) * qinv mod p
 *   result = vq + u * q
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] in Input
 * @param[in] p Prime number p
 * @param[in] q Prime number q
 * @param[in] dp d mod (p-1), with d the private key
 * @param[in] dq d mod (q-1), with d the private key
 * @param[in] qinv q^(-1) mod p
 * @param[out] result Result of modular exponentiation with CRT
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_PARAM
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @see crm_async_crt_mod_exp_go(), crm_async_crt_mod_exp_end()
 * for an asynchronous version
 */
static inline
int crm_crt_mod_exp(
        struct crm_pk_cnx *cnx,
        const crm_op *in,
        const crm_op *p,
        const crm_op *q,
        const crm_op *dp,
        const crm_op *dq,
        const crm_op *qinv,
        crm_op *result)
{
   struct crm_pk_dreq pkreq;
   int status;

   pkreq = crm_async_crt_mod_exp_go(cnx, in, p, q, dp, dq, qinv);
   if (pkreq.status)
      return pkreq.status;
   status = CRM_PK_WAIT(pkreq.req);
   crm_async_crt_mod_exp_end(pkreq.req, result);

   return status;
}


/** Asynchronous (non-blocking) RSA private key generation.
 *
 * Start an RSA private key generation on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_async_rsa_keygen_end()
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] p Prime value p
 * @param[in] q Prime value q
 * @param[in] public_expo Public exponent operand

 * @return Acquired acceleration request for this operation
 */
static inline
struct crm_pk_dreq crm_async_rsa_keygen_go(struct crm_pk_cnx *cnx,
   const crm_op *p, const crm_op *q, const crm_op *public_expo)
{
   struct crm_pk_dreq pkreq;
   struct crm_pk_inops_rsa_keygen inputs;

   pkreq = CRM_PK_ACQUIRE_REQ(cnx, CRM_PK_CMD_RSA_KEYGEN);
   if (pkreq.status)
      return pkreq;

   // convert and transfer operands
   int sizes[] = {
      CRM_OP_SIZE(p),
      CRM_OP_SIZE(q),
      CRM_OP_SIZE(public_expo)
   };
   pkreq.status = CRM_PK_LIST_GFP_INSLOTS(pkreq.req, sizes, (struct crm_pk_slot *)&inputs);
   if (pkreq.status)
      return pkreq;
   CRM_PK_OP2VMEM(p, inputs.p.addr);
   CRM_PK_OP2VMEM(q, inputs.q.addr);
   CRM_PK_OP2VMEM(public_expo, inputs.e.addr);

   CRM_PK_RUN(pkreq.req);

   return pkreq;
}


/** Finish asynchronous (non-blocking) RSA private key generation.
 *
 * Get the output operands of the RSA private key generation
 * and release the reserved resources.
 *
 * @pre The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[inout] req The previously acquired acceleration
 * request for this operation
 * @param[out] n Multiple of 2 primes p and q
 * @param[out] lambda_n Least common multiple of p-1 and q-1
 * @param[out] privkey Private key
*/
static inline
void crm_async_rsa_keygen_end(crm_pk_accel *req, crm_op *n, crm_op *lambda_n, crm_op *privkey)
{
    const char **outputs = CRM_PK_GET_OUTPUT_OPS(req);
    const int opsz = CRM_PK_GET_OPSIZE(req);

    CRM_PK_MEM2OP(outputs[0], opsz, n);
    CRM_PK_MEM2OP(outputs[1], opsz, lambda_n);
    CRM_PK_MEM2OP(outputs[2], opsz, privkey);

    CRM_PK_RELEASE_REQ(req);
}


/** Compute RSA private key and lambda_n from primes p and q.
 *
 * The private key is generated with the following steps:
 * 1. n = p * q
 * 2. lambda_n = lcm(p-1,q-1)
 * 3. d = e^-1 % lambda_n
 *
 * Where d is the private key (privkey).
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] p Prime value p
 * @param[in] q Prime value q
 * @param[in] public_expo Public exponent operand
 * @param[out] n Resulting n operand
 * @param[out] lambda_n Resulting lambda_n operand
 * @param[out] privkey Resulting rivate key operand
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_PARAM
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @see crm_async_rsa_keygen_go(), crm_async_rsa_keygen_end()
 * for an asynchronous version
 */
static inline

int crm_rsa_keygen(struct crm_pk_cnx *cnx,
     const crm_op *p, const crm_op *q, const crm_op *public_expo,
     crm_op *n, crm_op *lambda_n, crm_op *privkey)
{
   struct crm_pk_dreq pkreq;
   int status;

   pkreq = crm_async_rsa_keygen_go(cnx, p, q, public_expo);
   if (pkreq.status)
      return pkreq.status;

   status = CRM_PK_WAIT(pkreq.req);

   crm_async_rsa_keygen_end(pkreq.req, n, lambda_n, privkey);

   return status;
}


/** Asynchronous (non-blocking) RSA CRT private key parameters.
 *
 * Start a RSA CRT private key generation on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_async_rsa_crt_keyparams_end()
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] p Prime operand p
 * @param[in] q Prime operand q
 * @param[in] privkey Private key
 *
 * @return Acquired acceleration request for this operation
 *
 * @see crm_async_rsa_crt_keyparams_end() and crm_async_rsa_crt_keyparams()
*/
static inline
struct crm_pk_dreq crm_async_rsa_crt_keyparams_go(
   struct crm_pk_cnx *cnx, const crm_op *p, const crm_op *q,
   const crm_op *privkey)
{
   struct crm_pk_dreq pkreq;
   struct crm_pk_inops_rsa_crt_keyparams inputs;

   pkreq = CRM_PK_ACQUIRE_REQ(cnx, CRM_PK_CMD_RSA_CRT_KEYPARAMS);
   if (pkreq.status)
      return pkreq;

   // convert and transfer operands
   int sizes[] = {
      CRM_OP_SIZE(p),
      CRM_OP_SIZE(q),
      CRM_OP_SIZE(privkey)
   };
   pkreq.status = CRM_PK_LIST_GFP_INSLOTS(pkreq.req, sizes, (struct crm_pk_slot *)&inputs);
   if (pkreq.status)
      return pkreq;
   CRM_PK_OP2VMEM(p, inputs.p.addr);
   CRM_PK_OP2VMEM(q, inputs.q.addr);
   CRM_PK_OP2VMEM(privkey, inputs.privkey.addr);

   CRM_PK_RUN(pkreq.req);

   return pkreq;
}


/** Finish asynchronous (non-blocking) RSA CRT private key parameters.
 *
 * Get the output operands of the RSA CRT private key parameters
 * and release the reserved resources.
 *
 * @pre The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[inout] req The previously acquired acceleration
 * request for this operation
 * @param[out] dp d mod (p - 1)
 * @param[out] dq d mod (q - 1)
 * @param[out] qinv q ^ -1 mod p
 *
 * @see crm_async_rsa_crt_keyparams_go() and crm_rsa_crt_keyparams()
 */
static inline
void crm_async_rsa_crt_keyparams_end(crm_pk_accel *req,
                             crm_op *dp, crm_op *dq, crm_op *qinv)
{
    const char **outputs = CRM_PK_GET_OUTPUT_OPS(req);
    const int opsz = CRM_PK_GET_OPSIZE(req);

    CRM_PK_MEM2OP(outputs[0], opsz, dp);
    CRM_PK_MEM2OP(outputs[1], opsz, dq);
    CRM_PK_MEM2OP(outputs[2], opsz, qinv);

    CRM_PK_RELEASE_REQ(req);
}


/** Compute RSA CRT private key parameters.
 *
 * Computes the following parameters:
 *  dp = d mod (p - 1)
 *  dq = d mod (q - 1)
 *  qinv = q ^ -1 mod p
 * where d is the private key and the pair p and q are the secret primes used
 * to create the RSA private key.
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] p Prime value p
 * @param[in] q Prime value q
 * @param[in] privkey Private key operand
 * @param[out] dp d mod (p - 1)
 * @param[out] dq d mod (q - 1)
 * @param[out] qinv q ^ -1 mod p
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_NOT_INVERTIBLE
 * @return ::CRM_ERR_OUT_OF_RANGE
 * @return ::CRM_ERR_INVALID_PARAM
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @see crm_async_rsa_crt_keyparams_go(), crm_async_rsa_crt_keyparams_end()
 * for an asynchronous version
 */
static inline
int crm_rsa_crt_keyparams(struct crm_pk_cnx *cnx,
     const crm_op *p, const crm_op *q, const crm_op *privkey,
     crm_op *dp, crm_op *dq, crm_op *qinv)
{
   struct crm_pk_dreq pkreq;
   int status;

   pkreq = crm_async_rsa_crt_keyparams_go(cnx, p, q, privkey);
   if (pkreq.status)
      return pkreq.status;

   status = CRM_PK_WAIT(pkreq.req);

   crm_async_rsa_crt_keyparams_end(pkreq.req, dp, dq, qinv);

   return status;
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif
