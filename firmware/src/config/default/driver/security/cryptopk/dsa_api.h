/** "crmops" interface for DSA cryptographic computations
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

#ifndef DSA_HEADER_FILE
#define DSA_HEADER_FILE

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
CRM_PK_API_ASSERT_COMPATIBLE(1, 1);

struct crm_pk_cmd_def;

/**
 * @addtogroup CRM_PK_CRMOPS_DSA
 *
 * @{
 */

/** Asynchronous (non-blocking) DSA signature generation
 *
 * Start an DSA signature generation on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call crm_async_finish_pair()
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] p Prime modulus p
 * @param[in] q Prime divisor of p-1
 * @param[in] g Generator of order q mod p
 * @param[in] k Random value
 * @param[in] privkey Private key
 * @param[in] h Hash digest of message reduced by means of
 * Secure Hash Algorithm specified in FIPS 180-3
 *
 * @return Acquired acceleration request for this operation
 *
 * @see crm_dsa_sign() for a synchronous version
 */
static inline
struct crm_pk_dreq crm_async_dsa_sign_go(struct crm_pk_cnx *cnx,
   const crm_op *p, const crm_op *q, const crm_op *g, const crm_op *k,
   const crm_op *privkey, const crm_op *h)
{
   struct crm_pk_dreq pkreq;
   struct crm_pk_inops_dsa_sign inputs;

   pkreq = CRM_PK_ACQUIRE_REQ(cnx, CRM_PK_CMD_DSA_SIGN);
   if (pkreq.status)
      return pkreq;

   // convert and transfer operands
   int sizes[] = {
      CRM_OP_SIZE(p),
      CRM_OP_SIZE(q),
      CRM_OP_SIZE(g),
      CRM_OP_SIZE(k),
      CRM_OP_SIZE(privkey),
      CRM_OP_SIZE(h),
   };
   pkreq.status = CRM_PK_LIST_GFP_INSLOTS(pkreq.req, sizes, (struct crm_pk_slot *)&inputs);
   if (pkreq.status)
      return pkreq;
   CRM_PK_OP2VMEM(p, inputs.p.addr);
   CRM_PK_OP2VMEM(q, inputs.q.addr);
   CRM_PK_OP2VMEM(g, inputs.g.addr);
   CRM_PK_OP2VMEM(k, inputs.k.addr);
   CRM_PK_OP2VMEM(privkey, inputs.privkey.addr);
   CRM_PK_OP2VMEM(h, inputs.h.addr);

   CRM_PK_RUN(pkreq.req);

   return pkreq;
}


/** DSA signature generation
 *
 * Computes the following:
 *    1. X = g ^ k mod p
 *    2. r = X mod q
 *    3. if r == 0 the return ::CRM_ERR_INVALID_SIGNATURE
 *    4. else w = k ^ (-1) mod q
 *    5. s = w * (h + x * r) mod q
 *    6. if s == 0 then return ::CRM_ERR_INVALID_SIGNATURE
 *    7. (r,s) is the signature
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] p Prime modulus p
 * @param[in] q Prime divisor of p-1
 * @param[in] g Generator of order q mod p
 * @param[in] k Random value
 * @param[in] privkey Private key
 * @param[in] h Hash digest of message reduced by means of
 * Secure Hash Algorithm specified in FIPS 180-3
 * @param[out] r First part of signature
 * @param[out] s Second part of signature
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_NOT_INVERTIBLE
 * @return ::CRM_ERR_INVALID_SIGNATURE
 * @return ::CRM_ERR_INVALID_PARAM
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @see crm_async_dsa_sign_go() for an asynchronous version
 */
int crm_dsa_sign(struct crm_pk_cnx *cnx,
   const crm_op *p, const crm_op *q, const crm_op *g, const crm_op *k,
   const crm_op *privkey, const crm_op *h, crm_op *r, crm_op *s)
{
   struct crm_pk_dreq pkreq;
   int status;

   pkreq = crm_async_dsa_sign_go(cnx, p, q, g, k, privkey, h);
   if (pkreq.status)
      return pkreq.status;

   status = CRM_PK_WAIT(pkreq.req);

   crm_async_finish_pair(pkreq.req, r, s);

   return status;
}


/** Asynchronous (non-blocking) DSA signature verification
 *
 * Start an DSA signature verification on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call CRM_PK_RELEASE_REQ()
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] p Prime modulus p
 * @param[in] q Prime divisor of p-1
 * @param[in] g Generator of order q mod p
 * @param[in] pubkey Public key
 * @param[in] h Hash digest of message reduced by means of
 * Secure Hash Algorithm specified in FIPS 180-3
 * @param[in] r First part of the signature to verify
 * @param[in] s Second part of the signature to verify
 *
 * @return Acquired acceleration request for this operation
 *
 * @see crm_dsa_ver() for a synchronous version
 */
static inline
struct crm_pk_dreq crm_async_dsa_ver_go(struct crm_pk_cnx *cnx,
   const crm_op *p, const crm_op *q, const crm_op *g, const crm_op *pubkey,
   const crm_op *h, const crm_op *r, const crm_op *s)
{
   struct crm_pk_dreq pkreq;
   struct crm_pk_inops_dsa_ver inputs;

   pkreq = CRM_PK_ACQUIRE_REQ(cnx, CRM_PK_CMD_DSA_VER);
   if (pkreq.status)
      return pkreq;

   // convert and transfer operands
   int sizes[] = {
      CRM_OP_SIZE(p),
      CRM_OP_SIZE(q),
      CRM_OP_SIZE(g),
      CRM_OP_SIZE(pubkey),
      CRM_OP_SIZE(h),
      CRM_OP_SIZE(r),
      CRM_OP_SIZE(s),
   };
   pkreq.status = CRM_PK_LIST_GFP_INSLOTS(pkreq.req, sizes, (struct crm_pk_slot *)&inputs);
   if (pkreq.status)
      return pkreq;
   CRM_PK_OP2VMEM(p, inputs.p.addr);
   CRM_PK_OP2VMEM(q, inputs.q.addr);
   CRM_PK_OP2VMEM(g, inputs.g.addr);
   CRM_PK_OP2VMEM(pubkey, inputs.pubkey.addr);
   CRM_PK_OP2VMEM(h, inputs.h.addr);
   CRM_PK_OP2VMEM(r, inputs.r.addr);
   CRM_PK_OP2VMEM(s, inputs.s.addr);

   CRM_PK_RUN(pkreq.req);

   return pkreq;
}


/** DSA signature verification
 *
 * Checks if a signature is valid:
 *    1. w = s ^ (-1) mod q
 *    2. u1 = h * w mod q
 *    3. u2 = r * w mod q
 *    4. X = g ^ (u1) * y ^ (u2) mod p
 *    5. v = X mod q
 *    6. if v == r then signature is valid (::CRM_OK)
 *    7. else return ::CRM_ERR_INVALID_SIGNATURE
 *
 * Before launching the operation, verify the domain D(p,q,g)
 * by checking:
 *    1. 2^1023 < p < 2^1024 \b or 2^2047 < p < 2^2048
 *    2. 2^159 < q < 2^160 \b or 2^223 < q < 2^224 \b or 2^255 < q < 2^256
 *    3. 1 < g < p
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] p Prime modulus p
 * @param[in] q Prime divisor of p-1
 * @param[in] g Generator of order q mod p
 * @param[in] pubkey Public key
 * @param[in] h Hash digest of message reduced by means of
 * Secure Hash Algorithm specified in FIPS 180-3
 * @param[in] r First part of the signature to verify
 * @param[in] s Second part of the signature to verify
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_NOT_INVERTIBLE
 * @return ::CRM_ERR_INVALID_SIGNATURE
 * @return ::CRM_ERR_OUT_OF_RANGE
 * @return ::CRM_ERR_INVALID_PARAM
 * @return ::CRM_ERR_UNKNOWN_ERROR
 * @return ::CRM_ERR_BUSY
 * @return ::CRM_ERR_NOT_IMPLEMENTED
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_PLATFORM_ERROR
 * @return ::CRM_ERR_EXPIRED
 *
 * @see crm_async_dsa_ver_go() for an asynchronous version
 */
int crm_dsa_ver(struct crm_pk_cnx *cnx,
   const crm_op *p, const crm_op *q, const crm_op *g, const crm_op *pubkey,
   const crm_op *h, const crm_op *r, const crm_op *s)
{
   struct crm_pk_dreq pkreq;
   int status;

   pkreq = crm_async_dsa_ver_go(cnx, p, q, g, pubkey, h, r, s);
   if (pkreq.status)
      return pkreq.status;

   status = CRM_PK_WAIT(pkreq.req);

   CRM_PK_RELEASE_REQ(pkreq.req);

   return status;
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif
