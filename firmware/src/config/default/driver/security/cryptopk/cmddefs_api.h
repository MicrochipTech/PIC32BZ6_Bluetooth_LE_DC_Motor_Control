/** Asymmetric cryptographic command definitions
 *
 * @file
 */
/*
 * Copyright (c) 2018-2020 Silex Insight sa
 * Copyright (c) 2014-2020 Beerten Engineering scs
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
#ifndef CMDDEFS_HEADER_FILE
#define CMDDEFS_HEADER_FILE

#include <stdint.h>
#include "driver/security/api_table.h"

#ifdef __cplusplus
extern "C" {
#endif

struct crm_pk_cmd_def;

typedef const struct crm_pk_cmd_def * const CRM_CMD_PTR;

/**
 * @addtogroup CRM_PK_CMDS
 *
 * @{
 */

/** Modular addition of operands A and B */
#define CRM_PK_CMD_MOD_ADD                  ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_MOD_ADD))

/** Modular substraction of operands A and B */
#define CRM_PK_CMD_MOD_SUB                  ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_MOD_SUB))

/** Modular multiplication of operands A and B with odd modulo */
#define CRM_PK_CMD_ODD_MOD_MULT             ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_ODD_MOD_MULT))

/** Modular inversion of an operand with even modulo */
#define CRM_PK_CMD_EVEN_MOD_INV             ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_EVEN_MOD_INV))

/** Modular inversion of an operand with even modulo */
#define CRM_PK_CMD_EVEN_MOD_REDUCE          ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_EVEN_MOD_REDUCE))

/** Modular reduction of an operand with odd modulo */
#define CRM_PK_CMD_ODD_MOD_REDUCE           ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_ODD_MOD_REDUCE))

/** Modular division of operands A and B with odd modulo */
#define CRM_PK_CMD_ODD_MOD_DIV              ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_ODD_MOD_DIV))

/** Modular inversion of an operand with odd modulo */
#define CRM_PK_CMD_ODD_MOD_INV              ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_ODD_MOD_INV))

/** Modular square root **/
#define CRM_PK_CMD_MOD_SQRT                 ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_MOD_SQRT))

/** Multiplication **/
#define CRM_PK_CMD_MULT                     ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_MULT))

/** Modular exponentiation operation */
#define CRM_PK_CMD_MOD_EXP                  ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_MOD_EXP))

/** Diffie Hellman modular exponentiation operation with countermeasures
 *
 * The modulus must be a prime number.
 */
#define CRM_PK_CMD_DH_MOD_EXP_CM            ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_DH_MOD_EXP_CM))

/** RSA modular exponentiation operation with countermeasures*/
#define CRM_PK_CMD_RSA_MOD_EXP_CM           ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_RSA_MOD_EXP_CM))

/** Modular exponentiation operation (for RSA) with Chinese Remainder Theorem */
#define CRM_PK_CMD_MOD_EXP_CRT              ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_MOD_EXP_CRT))

/** Modular exponentiation operation (for RSA) with Chinese Remainder Theorem
 *
 * With blinding factor for countermeasures.
 */
#define CRM_PK_CMD_MOD_EXP_CRT_CM           ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_MOD_EXP_CRT_CM))

/** RSA private key including lambda(n) computation from primes
 *
 * Lambda(n) is also called the Carmichael's totient function or
 * Carmichael function.
 */
#define CRM_PK_CMD_RSA_KEYGEN               ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_RSA_KEYGEN))

/** RSA CRT private key parameters computation */
#define CRM_PK_CMD_RSA_CRT_KEYPARAMS        ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_RSA_CRT_KEYPARAMS))

/** Montgomery point multiplication for X25519 and X448
 *
 * All operands for this command use a little endian representation.
 * Operands should be decoded and clamped as defined in specifications
 * for X25519 and X448.
 */
#define CRM_PK_CMD_MONTGOMERY_PTMUL         ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_MONTGOMERY_PTMUL))

/** Elliptic curve ECDSA signature verification operation */
#define CRM_PK_CMD_ECDSA_VER                ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_ECDSA_VER))

/** Elliptic curve ECDSA signature generation operation */
#define CRM_PK_CMD_ECDSA_GEN                ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_ECDSA_GEN))

/** Elliptic curve point addition operation */
#define CRM_PK_CMD_ECC_PT_ADD               ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_ECC_PT_ADD))

/** Elliptic curve point multiplication operation */
#define CRM_PK_CMD_ECC_PTMUL                ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_ECC_PTMUL))

/** Elliptic curve point multiplication operation with countermeasures */
#define CRM_PK_CMD_ECC_PTMUL_CM             ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_ECC_PTMUL_CM))

/** Elliptic curve point decompression operation */
#define CRM_PK_CMD_ECC_PT_DECOMP            ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_ECC_PT_DECOMP))

/** Elliptic curve check parameters a & b */
#define CRM_PK_CMD_CHECK_PARAM_AB           ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_CHECK_PARAM_AB))

/** Elliptic curve check parameter n != p */
#define CRM_PK_CMD_CHECK_PARAM_N            ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_CHECK_PARAM_N))

/** Elliptic curve check x,y point < p */
#define CRM_PK_CMD_CHECK_XY                 ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_CHECK_XY))

/** Elliptic curve point doubling */
#define CRM_PK_CMD_ECC_PT_DOUBLE            ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_ECC_PT_DOUBLE))

/** Elliptic curve point on curve check */
#define CRM_PK_CMD_ECC_PTONCURVE            ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_ECC_PTONCURVE))

/** EDDSA point multiplication operation
 *
 * All operands for this command use a little endian representation.
 * Operands should be decoded and clamped as defined in specifications
 * for ED25519.
 */
#define CRM_PK_CMD_EDDSA_PTMUL              ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_EDDSA_PTMUL))

/** EDDSA 2nd part of signature operation
 *
 * All operands for this command use a little endian representation.
 * Operands should be decoded and clamped as defined in specifications
 * for ED25519.
 */
#define CRM_PK_CMD_EDDSA_SIGN               ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_EDDSA_SIGN))

/** EDDSA signature verification operation
 *
 * All operands for this command use a little endian representation.
 * Operands should be decoded and clamped as defined in specifications
 * for ED25519.
 */
#define CRM_PK_CMD_EDDSA_VER                ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_EDDSA_VER))

/** DSA signature generation */
#define CRM_PK_CMD_DSA_SIGN                 ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_DSA_SIGN))

/** DSA signature verification */
#define CRM_PK_CMD_DSA_VER                  ((CRM_CMD_PTR)**(uint32_t **)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CMD_DSA_VER))

/** @} */

#ifdef __cplusplus
}
#endif

#endif
