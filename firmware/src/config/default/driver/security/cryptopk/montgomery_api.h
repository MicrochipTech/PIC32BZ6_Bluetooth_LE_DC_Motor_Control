/** Simpler functions for base Montgomery elliptic curve operations
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

#ifndef MONTGOMERY_HEADER_FILE
#define MONTGOMERY_HEADER_FILE

#include "driver/security/api_table.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Size in bytes of a point on X25519 curve */
#define CRM_X25519_PT_SZ 32

/** Size in bytes of a point on X448 curve */
#define CRM_X448_PT_SZ 56

/**
 * @addtogroup CRM_PK_MONT
 *
 * @{
 */

/** An X25519 point */
struct crm_x25519_pt {
    /** Bytes array representation of a X25519 point **/
    char bytes[CRM_X25519_PT_SZ];
};

/** An X448 point */
struct crm_x448_pt {
    /** Bytes array representation of a X448 point  **/
    char bytes[CRM_X448_PT_SZ];
};


/** Montgomery point multiplication (X25519)
 *
 * Compute r = pt * k
 *
 * The operands must be decoded and clamped as defined in specifications
 * for X25519 and X448.
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] k Scalar
 * @param[in] pt Point on the X25519 curve
 * @param[out] r Multiplication result of k and pt
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
 * @see CRM_ASYNC_X25519_PTMULT_GO() and CRM_ASYNC_X25519_PTMULT_END()
 * for an asynchronous version
 */
typedef int (*FUNC_CRM_X25519_PTMULT)(struct crm_pk_cnx *cnx, const struct crm_x25519_pt *k, const struct crm_x25519_pt *pt, struct crm_x25519_pt *r);
#define CRM_X25519_PTMULT         ((FUNC_CRM_X25519_PTMULT)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_X25519_PTMULT)))

/** Asynchronous Montgomery point multiplication (X25519)
 *
 * Start a montgomery point multiplication on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call CRM_ASYNC_X25519_PTMULT_END()
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] k Scalar
 * @param[in] pt Point on the X25519 curve
 *
 * @return Acquired acceleration request for this operation
 *
 * @see CRM_ASYNC_X25519_PTMULT_END() and CRM_X25519_PTMULT()
 */
typedef struct crm_pk_dreq (*FUNC_CRM_ASYNC_X25519_PTMULT_GO)(struct crm_pk_cnx *cnx, const struct crm_x25519_pt *k, const struct crm_x25519_pt *pt);
#define CRM_ASYNC_X25519_PTMULT_GO         ((FUNC_CRM_ASYNC_X25519_PTMULT_GO)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_ASYNC_X25519_PTMULT_GO)))

/** Collect the result of asynchronous Montgomery point multiplication (X25519)
 *
 * Get the output operand of the Montgomery point multiplication
 * and release accelerator.
 *
 * @remark The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[inout] req The previously acquired acceleration
 * request for this operation
 * @param[out] r Multiplication result of k and pt
 *
 * @see CRM_ASYNC_X25519_PTMULT_GO() and crm_async_x25519_ptmult()
 */
typedef void (*FUNC_CRM_ASYNC_X25519_PTMULT_END)(crm_pk_accel *req, struct crm_x25519_pt *r);
#define CRM_ASYNC_X25519_PTMULT_END         ((FUNC_CRM_ASYNC_X25519_PTMULT_END)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_ASYNC_X25519_PTMULT_END)))


/** Montgomery point multiplication (X448)
 *
 * Compute r = pt * k
 *
 * The operands must be decoded and clamped as defined in specifications
 * for X25519 and X448.
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] k Scalar
 * @param[in] pt Point on the X448 curve
 * @param[out] r Multiplication result of k and pt
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
 * @see CRM_ASYNC_X448_PTMULT_GO() and CRM_ASYNC_X448_PTMULT_END()
 * for an asynchronous version
 */
typedef int (*FUNC_CRM_X448_PTMULT)(struct crm_pk_cnx *cnx, const struct crm_x448_pt *k, const struct crm_x448_pt *pt, struct crm_x448_pt *r);
#define CRM_X448_PTMULT         ((FUNC_CRM_X448_PTMULT)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_X448_PTMULT)))

/** Asynchronous Montgomery point multiplication (X448)
 *
 * Start a montgomery point multiplication on the accelerator
 * and return immediately.
 *
 * @remark When the operation finishes on the accelerator,
 * call CRM_ASYNC_X448_PTMULT_END()
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] k Scalar
 * @param[in] pt Point on the X448 curve
 *
 * @return Acquired acceleration request for this operation
 *
 * @see CRM_ASYNC_X448_PTMULT_END() and CRM_X448_PTMULT()
 */
typedef struct crm_pk_dreq (*FUNC_CRM_ASYNC_X448_PTMULT_GO)(struct crm_pk_cnx *cnx, const struct crm_x448_pt *k, const struct crm_x448_pt *pt);
#define CRM_ASYNC_X448_PTMULT_GO         ((FUNC_CRM_ASYNC_X448_PTMULT_GO)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_ASYNC_X448_PTMULT_GO)))

/** Collect the result of asynchronous Montgomery point multiplication (X448)
 *
 * Get the output operand of the Montgomery point multiplication
 * and release the reserved resources.
 *
 * @remark The operation on the accelerator must be finished before
 * calling this function.
 *
 * @param[inout] req The previously acquired acceleration
 * request for this operation
 * @param[out] r Multiplication result of k and pt
 *
 * @see CRM_ASYNC_X448_PTMULT_GO() and crm_async_x448_ptmult()
 */
typedef void (*FUNC_CRM_ASYNC_X448_PTMULT_END)(crm_pk_accel *req, struct crm_x448_pt *r);
#define CRM_ASYNC_X448_PTMULT_END         ((FUNC_CRM_ASYNC_X448_PTMULT_END)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_ASYNC_X448_PTMULT_END)))


/**  @} */

#ifdef __cplusplus
}
#endif

#endif
