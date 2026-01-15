/** "crmops" interface for EC J-PAKE computations.
 *
 * Simpler functions to perform public key crypto operations. Included directly
 * in some interfaces (like crmbuf or OpenSSL engine). The functions
 * take input operands (large integers) and output operands
 * which will receive the computed results.
 *
 * Operands have the "crm_op" type. The specific interfaces (like crmbuf) define
 * the "crm_op" type.
 *
 * @file
 */
/*
 * Copyright (c) 2020 Silex Insight sa
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
#ifndef ECJPAKE_HEADER_FILE
#define ECJPAKE_HEADER_FILE

#include "driver/security/cryptopk/core_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/security/cryptopk/inputslots.h"
#include "driver/security/cryptopk/iomem.h"
#include "driver/security/cryptopk/ec_curves_api.h"
#include "driver/security/cryptopk/adapter_api.h"
#include "driver/security/cryptopk/impl.h"
#include "driver/security/cryptopk/version.h"

/** Make sure the application is compatible with CryptoPK API version **/
CRM_PK_API_ASSERT_COMPATIBLE(1, 3);

struct crm_pk_ecurve;

/**
 * @addtogroup CRM_PK_CRMOPS_ECJPAKE
 *
 * @{
 */

/** Curve generator point for crm_ecjpake_verify_zkp() or crm_ecjpake_verify_zkp_go() */
#ifndef CRM_PT_CURVE_GENERATOR
#define CRM_PT_CURVE_GENERATOR NULL
#endif

/** Affine point parameter group
 *
 * This structure is used for point values which are stored in
 * two consecutive locations (x and y).
*/
struct crm_pk_point {
   crm_op *x; /**< x-coordinate */
   crm_op *y; /**< y-coordinate */
};

/** Asynchronous EC J-PAKE proof generation
 *
 * Start a EC J-PAKE proof generation operation on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_async_generate_zkp_end()
 *
 * @param[in] curve Elliptic curve on which to perform the operation.
 * @param[in] v Random input (< n)
 * @param[in] x Exponent
 * @param[in] h Hash digest
 *
 * Truncation or padding should be done by user application
 *
 * @return Acquired acceleration request for this operation
 */
static inline
struct crm_pk_dreq crm_ecjpake_generate_zkp_go(
   const struct crm_pk_ecurve *curve,
   const crm_op *v,
   const crm_op *x,
   const crm_op *h)
{
   struct crm_pk_dreq pkreq;
   struct crm_pk_inops_ecjpake_generate_zkp inputs;

   pkreq = CRM_PK_ACQUIRE_REQ(curve->cnx, CRM_PK_CMD_ECJPAKE_GENERATE_ZKP);
   if (pkreq.status)
      return pkreq;

   pkreq.status = CRM_PK_LIST_ECC_INSLOTS(pkreq.req, curve, 0, (struct crm_pk_slot *)&inputs);
   if (pkreq.status)
      return pkreq;

   int opsz = CRM_PK_GET_OPSIZE(pkreq.req);

   CRM_PK_OP2MEM(v, inputs.v.addr, opsz);
   CRM_PK_OP2MEM(x, inputs.x.addr, opsz);
   CRM_PK_OP2MEM(h, inputs.h.addr, opsz);

   CRM_PK_RUN(pkreq.req);

   return pkreq;
}

/** Finish asynchronous (non-blocking) EC J-PAKE proof generation.
 *
 * Get the output operands of the EC J-PAKE proof generation
 * and release the reserved resources.
 *
 * @pre The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[inout] req The previously acquired acceleration
 * request for this operation
 * @param[out] r The resulting value
 */
static inline
void crm_ecjpake_generate_zkp_end(
   crm_pk_accel *req,
   crm_op *r)
{
   crm_async_finish_single(req, r);
}

/** Perform an EC J-PAKE proof generation
 *
 * The proof generation has the following steps:
 *   1. r = (v - (x * h)) % n [where n is the modulus, a curve parameter]
 *
 * @param[in] curve Elliptic curve on which to perform the operation.
 * @param[in] v Random input (< n)
 * @param[in] x Exponent
 * @param[in] h Hash digest
 *
 * Truncation or padding should be done by user application
 * @param[out] r The result
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_OUT_OF_RANGE
 * @return ::CRM_ERR_POINT_NOT_ON_CURVE
 * @return ::CRM_ERR_NOT_INVERTIBLE
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @see crm_async_ecjpake_generate_zkp_go(), crm_async_ecjpake_generate_zkp_end() for
 * an asynchronous version
 */
static inline
int crm_ecjpake_generate_zkp(
   const struct crm_pk_ecurve *curve,
   const crm_op *v,
   const crm_op *x,
   const crm_op *h,
   crm_op *r
   )
{
   uint32_t status;
   struct crm_pk_dreq pkreq;

   pkreq = crm_ecjpake_generate_zkp_go(curve, v, x, h);
   if (pkreq.status)
      return pkreq.status;

   status = CRM_PK_WAIT(pkreq.req);

   crm_ecjpake_generate_zkp_end(pkreq.req, r);

   return status;
}

/** Asynchronous EC J-PAKE proof verification
 *
 * Start an EC J-PAKE proof verification operation on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_ecjpake_verify_zkp_end()
 *
 * @param[in] curve Elliptic curve on which to perform the operation.
 * @param[in] v Point on the curve
 * @param[in] x Point on the curve
 * @param[in] r Proof to be verified
 * @param[in] h Hash digest
 * @param[in] g Point on the curve (Optional, pass CRM_PT_CURVE_GENERATOR to use
 *              the curve generator point)
 *
 * Truncation or padding should be done by user application
 *
 * @return Acquired acceleration request for this operation
 */
static inline
struct crm_pk_dreq crm_ecjpake_verify_zkp_go(
   const struct crm_pk_ecurve *curve,
   const struct crm_pk_point *v,
   const struct crm_pk_point *x,
   const crm_op *r,
   const crm_op *h,
   const struct crm_pk_point *g)
{
   struct crm_pk_dreq pkreq;
   struct crm_pk_inops_ecjpake_verify_zkp inputs;

   pkreq = CRM_PK_ACQUIRE_REQ(curve->cnx, CRM_PK_CMD_ECJPAKE_VERIFY_ZKP);
   if (pkreq.status)
      return pkreq;

   pkreq.status = CRM_PK_LIST_ECC_INSLOTS(pkreq.req, curve, 0, (struct crm_pk_slot *)&inputs);
   if (pkreq.status)
      return pkreq;

   int opsz = CRM_PK_GET_OPSIZE(pkreq.req);

   crm_pk_op2mem(v->x, inputs.xv.addr, opsz);
   crm_pk_op2mem(v->y, inputs.yv.addr, opsz);
   crm_pk_op2mem(x->x, inputs.xx.addr, opsz);
   crm_pk_op2mem(x->y, inputs.yx.addr, opsz);
   crm_pk_op2mem(r, inputs.r.addr, opsz);
   crm_pk_op2mem(h, inputs.h.addr, opsz);

   if (g != CRM_PT_CURVE_GENERATOR) {
      crm_pk_op2mem(g->x, inputs.xg2.addr, opsz);
      crm_pk_op2mem(g->y, inputs.yg2.addr, opsz);
   } else {
      crm_pk_write_curve_gen(pkreq.req, curve, inputs.xg2, inputs.yg2);
   }

   CRM_PK_RUN(pkreq.req);

   return pkreq;
}

/** Finish asynchronous (non-blocking) EC J-PAKE proof verification.
 *
 * Finishes the EC J-PAKE proof verification
 * and releases the reserved resources.
 *
 * @pre The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[inout] req The previously acquired acceleration
 * request for this operation
 */
static inline
void crm_ecjpake_verify_zkp_end(
   crm_pk_accel *req
   )
{
   crm_pk_release_req(req);
}

/** Synchronous EC J-PAKE proof verification
 *
 * Start an EC J-PAKE proof verification operation on the accelerator
 * and return immediately.
 *
 * The proof verification has the following steps:
 *   1. ( (G * r) + (X * h) ) ?= V
 *
 * In case of a comparison failure CRM_ERR_INVALID_SIGNATURE shall
 * be returned.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_ecjpake_verify_zkp_end()
 *
 * @param[in] curve Elliptic curve on which to perform the operation.
 * @param[in] v Point on the curve
 * @param[in] x Point on the curve
 * @param[in] r Proof to be verified
 * @param[in] h Hash digest
 * @param[in] g Point on the curve (Optional, pass CRM_PT_CURVE_GENERATOR to use
 *              the curve generator point)
 *
 * Truncation or padding should be done by user application
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_SIGNATURE
 * @return ::CRM_ERR_OUT_OF_RANGE
 * @return ::CRM_ERR_POINT_NOT_ON_CURVE
 * @return ::CRM_ERR_NOT_INVERTIBLE
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @see crm_async_ecjpake_verify_zkp_go(), crm_async_ecjpake_verify_zkp_end() for
 * an asynchronous version
 */
static inline
int crm_ecjpake_verify_zkp(
   const struct crm_pk_ecurve *curve,
   const struct crm_pk_point *v,
   const struct crm_pk_point *x,
   const crm_op *r,
   const crm_op *h,
   const struct crm_pk_point *g
   )
{
   uint32_t status;
   struct crm_pk_dreq pkreq;

   pkreq = crm_ecjpake_verify_zkp_go(curve, v, x, r, h, g);
   if (pkreq.status)
      return pkreq.status;

   status = crm_pk_wait(pkreq.req);

   crm_ecjpake_verify_zkp_end(pkreq.req);

   return status;
}

/** Asynchronous EC J-PAKE 3 point addition
 *
 * Start a EC J-PAKE 3 point addition operation on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_ecjpake_3pt_add_end()
 *
 * @param[in] curve Elliptic curve on which to perform the operation.
 * @param[in] a Point on the curve
 * @param[in] b Point on the curve
 * @param[in] c Point on the curve
 *
 * Truncation or padding should be done by user application
 *
 * @return Acquired acceleration request for this operation
 *
 */
static inline
struct crm_pk_dreq crm_ecjpake_3pt_add_go(
   const struct crm_pk_ecurve *curve,
   const struct crm_pk_point *a,
   const struct crm_pk_point *b,
   const struct crm_pk_point *c)
{
   struct crm_pk_dreq pkreq;
   struct crm_pk_inops_ecjpake_3pt_add inputs;

   pkreq = crm_pk_acquire_req(curve->cnx, CRM_PK_CMD_ECJPAKE_3PT_ADD);
   if (pkreq.status)
      return pkreq;

   pkreq.status = crm_pk_list_ecc_inslots(pkreq.req, curve, 0, (struct crm_pk_slot *)&inputs);
   if (pkreq.status)
      return pkreq;

   int opsz = crm_pk_get_opsize(pkreq.req);

   crm_pk_op2mem(b->x, inputs.x2_1.addr, opsz);
   crm_pk_op2mem(b->y, inputs.x2_2.addr, opsz);
   crm_pk_op2mem(c->x, inputs.x3_1.addr, opsz);
   crm_pk_op2mem(c->y, inputs.x3_2.addr, opsz);
   crm_pk_op2mem(a->x, inputs.x1_1.addr, opsz);
   crm_pk_op2mem(a->y, inputs.x1_2.addr, opsz);

   crm_pk_run(pkreq.req);

   return pkreq;
}

/** Finish asynchronous (non-blocking) EC J-PAKE 3 point addition.
 *
 * Finishes the EC J-PAKE 3 point addition
 * and releases the reserved resources.
 *
 * @pre The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[inout] req The previously acquired acceleration
 * request for this operation
 * @param[out] gb The addition result
 */
static inline
void crm_ecjpake_3pt_add_end(
   crm_pk_accel *req,
   struct crm_pk_point *gb
   )
{
   crm_async_finish_pair(req, gb->x, gb->y);
}

/** Synchronous EC J-PAKE 3 point addition
 *
 * Start a EC J-PAKE 3 point addition operation on the accelerator
 * and return immediately.
 *
 * The 3 point addition operation has the following steps:
 *   1. gb = a + b + c
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_ecjpake_3pt_add_end()
 *
 * @param[in] curve Elliptic curve on which to perform the operation.
 * @param[in] a Point on the curve
 * @param[in] b Point on the curve
 * @param[in] c Point on the curve
 * @param[out] gb The addition result
 *
 * Truncation or padding should be done by user application
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_SIGNATURE
 * @return ::CRM_ERR_OUT_OF_RANGE
 * @return ::CRM_ERR_POINT_NOT_ON_CURVE
 * @return ::CRM_ERR_NOT_INVERTIBLE
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @see crm_async_ecjpake_verify_zkp_go(), crm_async_ecjpake_verify_zkp_end() for
 * an asynchronous version
 */
static inline
int crm_ecjpake_3pt_add(
   const struct crm_pk_ecurve *curve,
   const struct crm_pk_point *a,
   const struct crm_pk_point *b,
   const struct crm_pk_point *c,
   struct crm_pk_point *gb
   )
{
   uint32_t status;
   struct crm_pk_dreq pkreq;

   pkreq = crm_ecjpake_3pt_add_go(curve, a,b,c);
   if (pkreq.status)
      return pkreq.status;

   status = crm_pk_wait(pkreq.req);

   crm_ecjpake_3pt_add_end(pkreq.req, gb);

   return status;
}

/** Asynchronous EC J-PAKE session key generation
 *
 * Start a EC J-PAKE session key generation operation on
 * the accelerator and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_ecjpake_gen_sess_key_end()
 *
 * @param[in] curve Elliptic curve on which to perform the operation.
 * @param[in] x4 Point on the curve
 * @param[in] b Point on the curve
 * @param[in] x2 Generated random number
 * @param[in] x2s (x2 * s) % n [s = password, n = modulus]
 *
 * Truncation or padding should be done by user application
 *
 * @return Acquired acceleration request for this operation
 */
static inline
struct crm_pk_dreq crm_ecjpake_gen_sess_key_go(
   const struct crm_pk_ecurve *curve,
   const struct crm_pk_point *x4,
   const struct crm_pk_point *b,
   const crm_op *x2,
   const crm_op *x2s)
{
   struct crm_pk_dreq pkreq;
   struct crm_pk_inops_ecjpake_gen_sess_key inputs;

   pkreq = crm_pk_acquire_req(curve->cnx, CRM_PK_CMD_ECJPAKE_GEN_SESS_KEY);
   if (pkreq.status)
      return pkreq;

   pkreq.status = crm_pk_list_ecc_inslots(pkreq.req, curve, 0, (struct crm_pk_slot *)&inputs);
   if (pkreq.status)
      return pkreq;

   int opsz = crm_pk_get_opsize(pkreq.req);

   crm_pk_op2mem(x4->x, inputs.x4_1.addr, opsz);
   crm_pk_op2mem(x4->y, inputs.x4_2.addr, opsz);
   crm_pk_op2mem(b->x, inputs.b_1.addr, opsz);
   crm_pk_op2mem(b->y, inputs.b_2.addr, opsz);
   crm_pk_op2mem(x2, inputs.x2.addr, opsz);
   crm_pk_op2mem(x2s, inputs.x2s.addr, opsz);

   crm_pk_run(pkreq.req);

   return pkreq;
}

/** Finish asynchronous (non-blocking) EC J-PAKE session key generation
 *
 * Finishes the EC J-PAKE session key generation operation
 * and releases the reserved resources.
 *
 * @pre The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[inout] req The previously acquired acceleration
 * request for this operation
 * @param[out] t The result
 */
static inline
void crm_ecjpake_gen_sess_key_end(
   crm_pk_accel *req,
   struct crm_pk_point *t)
{
   crm_async_finish_pair(req, t->x, t->y);
}

/** Synchronous EC J-PAKE session key generation
 *
 * Start a EC J-PAKE session key generation operation on the accelerator
 * and return immediately.
 *
 * The session key generation has the following steps:
 *   1. T = (b - (x4 * x2s)) * x2
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_ecjpake_gen_sess_key_end()
 *
 * @param[in] curve Elliptic curve on which to perform the operation.
 * @param[in] x4 Point on the curve
 * @param[in] b Point on the curve
 * @param[in] x2 Generated random number
 * @param[in] x2s x2 * password
 * @param[out] t result
 *
 * Truncation or padding should be done by user application
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_SIGNATURE
 * @return ::CRM_ERR_OUT_OF_RANGE
 * @return ::CRM_ERR_POINT_NOT_ON_CURVE
 * @return ::CRM_ERR_NOT_INVERTIBLE
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @see crm_async_ecjpake_gen_sess_key_go(), crm_async_ecjpake_gen_sess_key_end() for
 * an asynchronous version
 */
static inline
int crm_ecjpake_gen_sess_key(
   const struct crm_pk_ecurve *curve,
   const struct crm_pk_point *x4,
   const struct crm_pk_point *b,
   const crm_op *x2,
   const crm_op *x2s,
   struct crm_pk_point *t
   )
{
   uint32_t status;
   struct crm_pk_dreq pkreq;

   pkreq = crm_ecjpake_gen_sess_key_go(curve, x4, b, x2, x2s);
   if (pkreq.status)
      return pkreq.status;

   status = crm_pk_wait(pkreq.req);

   crm_ecjpake_gen_sess_key_end(pkreq.req, t);

   return status;
}

/** Asynchronous EC J-PAKE step 2 calculation
 *
 * Start an EC J-PAKE step 2 calculation operation on
 * the accelerator and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_ecjpake_gen_step_2_end()
 *
 * @param[in] curve Elliptic curve on which to perform the operation.
 * @param[in] x4 Point on the curve
 * @param[in] x3 Point on the curve
 * @param[in] x1 Point on the curve
 * @param[in] x2s (x2 * s) % n [x2 = random, s = password, n = modulus]
 * @param[in] s password
 *
 * Truncation or padding should be done by user application
 *
 * @return Acquired acceleration request for this operation
 */
static inline
struct crm_pk_dreq crm_ecjpake_gen_step_2_go(
   const struct crm_pk_ecurve *curve,
   const struct crm_pk_point *x4,
   const struct crm_pk_point *x3,
   const struct crm_pk_point *x1,
   const crm_op *x2s,
   const crm_op *s)
{
   struct crm_pk_dreq pkreq;
   struct crm_pk_inops_ecjpake_gen_step_2 inputs;

   pkreq = crm_pk_acquire_req(curve->cnx, CRM_PK_CMD_ECJPAKE_GEN_STEP_2);
   if (pkreq.status)
      return pkreq;

   pkreq.status = crm_pk_list_ecc_inslots(pkreq.req, curve, 0, (struct crm_pk_slot *)&inputs);
   if (pkreq.status)
      return pkreq;

   int opsz = crm_pk_get_opsize(pkreq.req);

   crm_pk_op2mem(x4->x, inputs.x4_1.addr, opsz);
   crm_pk_op2mem(x4->y, inputs.x4_2.addr, opsz);
   crm_pk_op2mem(x3->x, inputs.x3_1.addr, opsz);
   crm_pk_op2mem(x3->y, inputs.x3_2.addr, opsz);
   crm_pk_op2mem(x1->x, inputs.x1_1.addr, opsz);
   crm_pk_op2mem(x1->y, inputs.x1_2.addr, opsz);
   crm_pk_op2mem(x2s, inputs.x2s.addr, opsz);
   crm_pk_op2mem(s, inputs.s.addr, opsz);

   crm_pk_run(pkreq.req);

   return pkreq;
}

/** Finish an asynchronous (non-blocking) EC J-PAKE step 2 calculation
 *
 * Finishes the EC J-PAKE step 2 calculation operation
 * and releases the reserved resources.
 *
 * @pre The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[inout] req The previously acquired acceleration
 * request for this operation
 * @param[out] a Point on the curve
 * @param[out] x2s Generated random * password
 * @param[out] ga Point on the curve
 */
static inline
void crm_ecjpake_gen_step_2_end(
   crm_pk_accel *req,
   struct crm_pk_point *a,
   crm_op *x2s,
   struct crm_pk_point *ga)
{
   crm_op *results[5] = { a->x, a->y, x2s, ga->x, ga->y };

   crm_async_finish_any(req, results, 5);
}

/** Synchronous EC J-PAKE step 2 calculation
 *
 * Start an EC J-PAKE step 2 calculation operation on the accelerator
 * and return immediately.
 *
 * The step 2 calculation has the following steps:
 *   1. ga = x1 + x3 + x4
 *   2. rx2s = (x2s * s) % curve.n
 *   3. a = ga * rx2s
 *
 * @param[in] curve Elliptic curve on which to perform the operation.
 * @param[in] x4 Point on the curve
 * @param[in] x3 Point on the curve
 * @param[in] x1 Point on the curve
 * @param[in] x2s Generated random * password
 * @param[in] s Password
 * @param[out] a Point on the curve
 * @param[out] rx2s Generated random * password
 * @param[out] ga Point on the curve
 *
 * Truncation or padding should be done by user application
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_INVALID_SIGNATURE
 * @return ::CRM_ERR_OUT_OF_RANGE
 * @return ::CRM_ERR_POINT_NOT_ON_CURVE
 * @return ::CRM_ERR_NOT_INVERTIBLE
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @see crm_async_ecjpake_gen_step_2_go(), crm_async_ecjpake_gen_step_2_end() for
 * an asynchronous version
 */
static inline
int crm_ecjpake_gen_step_2(
   const struct crm_pk_ecurve *curve,
   const struct crm_pk_point *x4,
   const struct crm_pk_point *x3,
   const struct crm_pk_point *x1,
   const crm_op *x2s,
   const crm_op *s,
   struct crm_pk_point *a,
   crm_op *rx2s,
   struct crm_pk_point *ga
   )
{
   uint32_t status;
   struct crm_pk_dreq pkreq;

   pkreq = crm_ecjpake_gen_step_2_go(curve, x4, x3, x1, x2s, s);
   if (pkreq.status)
      return pkreq.status;

   status = crm_pk_wait(pkreq.req);

   crm_ecjpake_gen_step_2_end(pkreq.req, a, rx2s, ga);

   return status;
}

/** @} */
#ifdef __cplusplus
}
#endif

#endif
