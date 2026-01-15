/** Input slots for operations
 *
 * @file
 */
/*
 * Copyright (c) 2018-2020 Silex Insight sa
 * Copyright (c) 2018-2020 Beerten Engineering
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
#ifndef INPUTSLOTS_HEADER_FILE
#define INPUTSLOTS_HEADER_FILE


/** Input slots for ::CRM_PK_CMD_ODD_MOD_INV & ::CRM_PK_CMD_ODD_MOD_REDUCE
 * & ::CRM_PK_CMD_MOD_SQRT & ::CRM_PK_CMD_EVEN_MOD_INV &
 * ::CRM_PK_CMD_ODD_MOD_REDUCE
 */
struct crm_pk_inops_mod_single_op_cmd {
   struct crm_pk_slot n; /**< Modulus **/
   struct crm_pk_slot b; /**< Value **/
};

/** Input slots for ::CRM_PK_CMD_MOD_ADD & ::CRM_PK_CMD_MOD_SUB
 * & ::CRM_PK_CMD_ODD_MOD_MULT & ::CRM_PK_CMD_ODD_MOD_DIV
 */
struct crm_pk_inops_mod_cmd {
   struct crm_pk_slot n; /**< Modulus **/
   struct crm_pk_slot a; /**< Operand A **/
   struct crm_pk_slot b; /**< Operand B **/
};

/** Input slots for ::CRM_PK_CMD_MULT */
struct crm_pk_inops_mult {
   struct crm_pk_slot a; /**< First scalar value **/
   struct crm_pk_slot b; /**< Second scalar value **/
};


/** Input slots for ::CRM_PK_CMD_MOD_EXP */
struct crm_pk_inops_mod_exp {
   struct crm_pk_slot m; /**< Modulus **/
   struct crm_pk_slot input; /**< Base **/
   struct crm_pk_slot exp; /**< Exponent **/
};


/** Input slots for ::CRM_PK_CMD_RSA_MOD_EXP_CM */
struct crm_pk_inops_rsa_mod_exp_cm {
   struct crm_pk_slot m; /**< Modulus **/
   struct crm_pk_slot lambda_n; /**< Lambda_n **/
   struct crm_pk_slot input; /**< Base **/
   struct crm_pk_slot exp; /**< Exponent **/
   struct crm_pk_slot blind; /**< Blinding factor **/
};


/** Input slots for ::CRM_PK_CMD_MOD_EXP_CRT */
struct crm_pk_inops_crt_mod_exp {
   struct crm_pk_slot p; /**< Prime number p **/
   struct crm_pk_slot q; /**< Prime number q **/
   struct crm_pk_slot in; /**< Input **/
   struct crm_pk_slot dp; /**< d mod (p-1), with d the private key **/
   struct crm_pk_slot dq; /**< d mod (q-1), with d the private key **/
   struct crm_pk_slot qinv; /**< q^(-1) mod p **/
};

/** Input slots for ::CRM_PK_CMD_RSA_KEYGEN */
struct crm_pk_inops_rsa_keygen {
   struct crm_pk_slot p; /**< Prime number p **/
   struct crm_pk_slot q; /**< Prime number q **/
   struct crm_pk_slot e; /**< Public exponent **/
};

/** Input slots for ::CRM_PK_CMD_RSA_CRT_KEYPARAMS */
struct crm_pk_inops_rsa_crt_keyparams {
   struct crm_pk_slot p; /**< Prime number p **/
   struct crm_pk_slot q; /**< Prime number q **/
   struct crm_pk_slot privkey; /**< Private key **/
};

/** Input slots for ::CRM_PK_CMD_SRP_USER_KEY_GEN */
struct crm_pk_inops_srp_user_keyparams {
   struct crm_pk_slot n; /**< Safe prime number **/
   struct crm_pk_slot g; /**< Generator of the multiplicative group **/
   struct crm_pk_slot a; /**< Random value **/
   struct crm_pk_slot b; /**< k * g^x + g^t with t random salt, k value derived by both sides (for example k = H(n, g)) **/
   struct crm_pk_slot x; /**< Hash of (s, p) with s a random salt and p the user password **/
   struct crm_pk_slot k; /**< Hash of (n, g) **/
   struct crm_pk_slot u; /**< Hash of (g^a, b) **/
};

/** Input slots for ::CRM_PK_CMD_ECKCDSA_SIGN */
struct crm_pk_inops_eckcdsa_sign {
   struct crm_pk_slot d; /**< Private key **/
   struct crm_pk_slot k; /**< Random value **/
   struct crm_pk_slot r; /**< First part of signature **/
   struct crm_pk_slot h; /**< Hash digest **/
};


/** Input slots for ::CRM_PK_CMD_MONTGOMERY_PTMUL */
struct crm_pk_inops_montgomery_mult {
   struct crm_pk_slot p; /**< Point P **/
   struct crm_pk_slot k; /**< Scalar **/
};


/** Input slots for ::CRM_PK_CMD_ECC_PT_ADD */
struct crm_pk_inops_ecp_add {
   struct crm_pk_slot p1x; /**< x-coordinate of point P1 **/
   struct crm_pk_slot p1y; /**< y-coordinate of point P1 **/
   struct crm_pk_slot p2x; /**< x-coordinate of point P2 **/
   struct crm_pk_slot p2y; /**< y-coordinate of point P2 **/
};


/** Input slots for ::CRM_PK_CMD_ECC_PTMUL */
struct crm_pk_inops_ecp_mult {
   struct crm_pk_slot k; /**< Scalar **/
   struct crm_pk_slot px; /**< x-coordinate of point P **/
   struct crm_pk_slot py; /**< y-coordinate of point P **/
};

/** Input slots for ::CRM_PK_CMD_ECC_PT_DOUBLE */
struct crm_pk_inops_ecp_double {
   struct crm_pk_slot px; /**< x-coordinate of point P **/
   struct crm_pk_slot py; /**< y-coordinate of point P **/
};


/** Input slots for ::CRM_PK_CMD_ECC_PTONCURVE */
struct crm_pk_inops_ec_ptoncurve {
   struct crm_pk_slot px; /**< x-coordinate of point P **/
   struct crm_pk_slot py; /**< y-coordinate of point P **/
};

/** Input slots for ::CRM_PK_CMD_ECC_PT_DECOMP */
struct crm_pk_inops_ec_pt_decompression {
   struct crm_pk_slot x; /**< x-coordinate of compressed point **/
};


/** Input slots for ::CRM_PK_CMD_ECDSA_VER &
 * ::CRM_PK_CMD_ECKCDSA_VER & ::CRM_PK_CMD_SM2_VER
 */
struct crm_pk_inops_ecdsa_verify {
   struct crm_pk_slot qx; /**< x-coordinate of public key **/
   struct crm_pk_slot qy; /**< y-coordinate of public key **/
   struct crm_pk_slot r; /**< First part of signature **/
   struct crm_pk_slot s; /**< Second part of signature **/
   struct crm_pk_slot h; /**< Hash digest **/
};


/** Input slots for ::CRM_PK_CMD_ECDSA_GEN & ::CRM_PK_CMD_SM2_GEN */
struct crm_pk_inops_ecdsa_generate {
   struct crm_pk_slot d; /**< Private key **/
   struct crm_pk_slot k; /**< Random value **/
   struct crm_pk_slot h; /**< Hash digest **/
};

/** Input slots for ::CRM_PK_CMD_SM2_EXCH */
struct crm_pk_inops_sm2_exchange {
   struct crm_pk_slot d; /**< Private key **/
   struct crm_pk_slot k; /**< Random value **/
   struct crm_pk_slot qx; /**< x-coordinate of public key **/
   struct crm_pk_slot qy; /**< y-coordinate of public key **/
   struct crm_pk_slot rbx; /**< x-coordinate of random value from B **/
   struct crm_pk_slot rby; /**< y-coordinate of random value from B **/
   struct crm_pk_slot cof; /**< Cofactor **/
   struct crm_pk_slot rax; /**< x-coordinate of random value from A **/
   struct crm_pk_slot w; /**< (log2(n)/2)-1, with n the curve order **/
};

/** Input slots for ::CRM_PK_CMD_ECKCDSA_PUBKEY_GEN */
struct crm_pk_inops_eckcdsa_generate {
   struct crm_pk_slot d; /**< Private key **/
};


/** Input slots for ::CRM_PK_CMD_EDDSA_PTMUL */
struct crm_pk_inops_eddsa_ptmult {
   struct crm_pk_dblslot r; /**< Scalar **/
};


/** Input slots for ::CRM_PK_CMD_EDDSA_SIGN */
struct crm_pk_inops_eddsa_sign {
   struct crm_pk_dblslot k; /**< Scalar with a size double of other operands **/
   struct crm_pk_dblslot r; /**< Signature part 1 **/
   struct crm_pk_slot s; /**< Signature part 2 **/
};



/** Input slots for ::CRM_PK_CMD_EDDSA_VER */
struct crm_pk_inops_eddsa_ver {
   struct crm_pk_dblslot k; /**< Scalar with a size double of other operands **/
   struct crm_pk_slot ay; /**< Encoded public key  **/
   struct crm_pk_slot sig_s; /**< Signature part 2 **/
   struct crm_pk_slot ry; /**< y-coordinate of r **/
};


/** Input slots for ::CRM_PK_CMD_MILLER_RABIN */
struct crm_pk_inops_miller_rabin {
   struct crm_pk_slot n; /**< Candidate prime value **/
   struct crm_pk_slot a; /**< Random value **/
};

/** Input slots for ::CRM_PK_CMD_DSA_SIGN */
struct crm_pk_inops_dsa_sign {
   struct crm_pk_slot p; /**< Prime modulus **/
   struct crm_pk_slot q; /**< Prime divisor of p-1 **/
   struct crm_pk_slot g; /**< Generator **/
   struct crm_pk_slot k; /**< Random value **/
   struct crm_pk_slot privkey; /**< Private key **/
   struct crm_pk_slot h; /**< Hash digest **/
};

/** Input slots for ::CRM_PK_CMD_DSA_VER */
struct crm_pk_inops_dsa_ver {
   struct crm_pk_slot p; /**< Prime modulus **/
   struct crm_pk_slot q; /**< Prime divisor of p-1 **/
   struct crm_pk_slot g; /**< Generator **/
   struct crm_pk_slot pubkey; /**< Public key **/
   struct crm_pk_slot r; /**< First part of signature **/
   struct crm_pk_slot s; /**< Second part of signature **/
   struct crm_pk_slot h; /**< Hash digest **/
};

/** Input slots for ::CRM_PK_CMD_SM9_EXP */
struct crm_pk_inops_sm9_exp {
   struct crm_pk_slot h; /**< exponent */
   struct crm_pk_slot t; /**< polynomial base */
   struct crm_pk_slot g[12]; /**< g in GT */
};

/** Input slots for ::CRM_PK_CMD_SM9_PMULG1 */
struct crm_pk_inops_sm9_pmulg1 {
   struct crm_pk_slot p1x0; /**< x-coordinate */
   struct crm_pk_slot p1y0; /**< y-coordinate */
   struct crm_pk_slot ke; /**< scalar */
   struct crm_pk_slot t; /**< polynomial base */
};

/** Input slots for ::CRM_PK_CMD_SM9_PMULG2 */
struct crm_pk_inops_sm9_pmulg2 {
   struct crm_pk_slot p2x0; /**< x-coordinate 0 */
   struct crm_pk_slot p2x1; /**< x-coordinate 1 */
   struct crm_pk_slot p2y0; /**< y-coordinate 0 */
   struct crm_pk_slot p2y1; /**< y-coordinate 1 */
   struct crm_pk_slot ke; /**< scalar */
   struct crm_pk_slot t; /**< polynomial base */
};

/** Input slots for ::CRM_PK_CMD_SM9_PAIR */
struct crm_pk_inops_sm9_pair {
   struct crm_pk_slot qx0; /**< Q x-coordinate 0 */
   struct crm_pk_slot qx1; /**< Q x-coordinate 1 */
   struct crm_pk_slot qy0; /**< Q y-coordinate 0 */
   struct crm_pk_slot qy1; /**< Q y-coordinate 1 */
   struct crm_pk_slot px0; /**< P x-coordinate */
   struct crm_pk_slot py0; /**< P y-coordinate */
   struct crm_pk_slot f; /**< frobenius constant */
   struct crm_pk_slot t; /**< polynomial base */
};

/** Input slots for ::CRM_PK_CMD_SM9_PRIVSIGKEYGEN */
struct crm_pk_inops_sm9_sigpkgen {
   struct crm_pk_slot p1x0; /**< x-coordinate */
   struct crm_pk_slot p1y0; /**< y-coordinate */
   struct crm_pk_slot h; /**< scalar */
   struct crm_pk_slot ks; /**< scalar */
   struct crm_pk_slot t; /**< polynomial base */
};

/** Input slots for ::CRM_PK_CMD_SM9_SIGNATUREGEN */
struct crm_pk_inops_sm9_signaturegen {
   struct crm_pk_slot dcrm0; /**< x-coordinate */
   struct crm_pk_slot dsy0; /**< y-coordinate */
   struct crm_pk_slot h; /**< scalar */
   struct crm_pk_slot r; /**< scalar */
   struct crm_pk_slot t; /**< polynomial base */
};

/** Input slots for ::CRM_PK_CMD_SM9_SIGNATUREVERIFY */
struct crm_pk_inops_sm9_signatureverify {
   struct crm_pk_slot h1; /**< scalar */
   struct crm_pk_slot p2x0; /**< x-coordinate */
   struct crm_pk_slot p2x1; /**< x-coordinate */
   struct crm_pk_slot p2y0; /**< y-coordinate */
   struct crm_pk_slot p2y1; /**< y-coordinate */
   struct crm_pk_slot ppubcrm0; /**< x-coordinate 0 */
   struct crm_pk_slot ppubcrm1; /**< x-coordinate 1 */
   struct crm_pk_slot ppubsy0; /**< y-coordinate 0 */
   struct crm_pk_slot ppubsy1; /**< y-coordinate 1 */
   struct crm_pk_slot crm0; /**< x-coordinate */
   struct crm_pk_slot sy0; /**< y-coordinate */
   struct crm_pk_slot h; /**< scalar */
   struct crm_pk_slot f; /**< frobenius constant */
   struct crm_pk_slot t; /**< polynomial base */
   struct crm_pk_slot g[12]; /**< input */
};

/** Input slots for ::CRM_PK_CMD_SM9_PRIVENCRKEYGEN */
struct crm_pk_inops_sm9_privencrkeygen {
   struct crm_pk_slot p2x0; /**< x-coordinate 0 */
   struct crm_pk_slot p2x1; /**< x-coordinate 1 */
   struct crm_pk_slot p2y0; /**< y-coordinate 0 */
   struct crm_pk_slot p2y1; /**< y-coordinate 1 */
   struct crm_pk_slot h; /**< scalar */
   struct crm_pk_slot ks; /**< scalar */
   struct crm_pk_slot t; /**< polynomial base */
};

/** Input slots for ::CRM_PK_CMD_SM9_SENDKEY */
struct crm_pk_inops_sm9_sendkey {
   struct crm_pk_slot p1x0; /**< x-coordinate */
   struct crm_pk_slot p1y0; /**< y-coordinate */
   struct crm_pk_slot ppubex0; /**< x-coordinate */
   struct crm_pk_slot ppubey0; /**< y-coordinate */
   struct crm_pk_slot h; /**< scalar */
   struct crm_pk_slot r; /**< scalar */
   struct crm_pk_slot t; /**< polynomial base */
};

/** Input slots for ::CRM_PK_CMD_SM9_REDUCEH */
struct crm_pk_inops_sm9_reduceh {
   struct crm_pk_slot h; /**< scalar */
   struct crm_pk_slot t; /**< polynomial base */
};

/** Input slots for ::CRM_PK_CMD_ECJPAKE_GENERATE_ZKP */
struct crm_pk_inops_ecjpake_generate_zkp {
   struct crm_pk_slot v; /**< Random input */
   struct crm_pk_slot x; /**< Exponent */
   struct crm_pk_slot h; /**< Hash digest */
};

/** Input slots for ::CRM_PK_CMD_ECJPAKE_VERIFY_ZKP */
struct crm_pk_inops_ecjpake_verify_zkp {
   struct crm_pk_slot xv; /**< Point V on the curve, x-coordinate */
   struct crm_pk_slot yv; /**< Point V on the curve, y-coordinate */
   struct crm_pk_slot xx; /**< Point X on the curve, x-coordinate */
   struct crm_pk_slot yx; /**< Point X on the curve, y-coordinate */
   struct crm_pk_slot r; /**< Proof */
   struct crm_pk_slot h; /**< Hash digest */
   struct crm_pk_slot xg2; /**< Point G on the curve, x-coordinate */
   struct crm_pk_slot yg2; /**< Point G on the curve, y-coordinate */
};

/** Input slots for ::CRM_PK_CMD_ECJPAKE_3PT_ADD */
struct crm_pk_inops_ecjpake_3pt_add {
   struct crm_pk_slot x2_1; /**< Point X2 on the curve, x-coordinate */
   struct crm_pk_slot x2_2; /**< Point X2 on the curve, y-coordinate */
   struct crm_pk_slot x3_1; /**< Point X3 on the curve, x-coordinate */
   struct crm_pk_slot x3_2; /**< Point X3 on the curve, y-coordinate */
   struct crm_pk_slot x1_1; /**< Point X1 on the curve, x-coordinate */
   struct crm_pk_slot x1_2; /**< Point X1 on the curve, y-coordinate */
};

/** Input slots for ::CRM_PK_CMD_ECJPAKE_GEN_STEP_2 */
struct crm_pk_inops_ecjpake_gen_step_2 {
   struct crm_pk_slot x4_1; /**< Point X4 on the curve, x-coordinate */
   struct crm_pk_slot x4_2; /**< Point X4 on the curve, y-coordinate */
   struct crm_pk_slot x3_1; /**< Point X3 on the curve, x-coordinate */
   struct crm_pk_slot x3_2; /**< Point X3 on the curve, y-coordinate */
   struct crm_pk_slot x2s;  /**< Random value * Password */
   struct crm_pk_slot x1_1; /**< Point X1 on the curve, x-coordinate */
   struct crm_pk_slot x1_2; /**< Point X1 on the curve, y-coordinate */
   struct crm_pk_slot s;    /**< Password */
};

/** Input slots for ::CRM_PK_CMD_ECJPAKE_GEN_SESS_KEY */
struct crm_pk_inops_ecjpake_gen_sess_key {
   struct crm_pk_slot x4_1; /**< Point X4 on the curve, x-coordinate */
   struct crm_pk_slot x4_2; /**< Point X4 on the curve, y-coordinate */
   struct crm_pk_slot b_1; /**< Point B on the curve, x-coordinate */
   struct crm_pk_slot b_2; /**< Point B on the curve, y-coordinate */
   struct crm_pk_slot x2; /**< Random value */
   struct crm_pk_slot x2s; /**< Random value * Password */
};

/** Inputs slots for ::CRM_PK_CMD_SRP_SERVER_PUBLIC_KEY_GEN */
struct crm_pk_inops_srp_server_public_key_gen {
   struct crm_pk_slot n; /**< Safe prime */
   struct crm_pk_slot g; /**< Generator */
   struct crm_pk_slot k; /**< Hash digest */
   struct crm_pk_slot v; /**< Exponentiated hash digest */
   struct crm_pk_slot b; /**< Random */
};

/** Inputs slots for ::CRM_PK_CMD_SRP_SERVER_SESSION_KEY_GEN */
struct crm_pk_inops_srp_server_session_key_gen {
   struct crm_pk_slot n; /**< Safe prime */
   struct crm_pk_slot a; /**< Random */
   struct crm_pk_slot u; /**< Hash digest */
   struct crm_pk_slot v; /**< Exponentiated hash digest */
   struct crm_pk_slot b; /**< Random */
};

/** Inputs slots for ::CRM_PK_CMD_CHECK_PARAM_AB */
struct crm_pk_inops_check_param_ab {
   struct crm_pk_slot p; /**< p parameter of curve */
   struct crm_pk_slot a; /**< a parameter of curve */
   struct crm_pk_slot b; /**< b parameter of curve */
};

/** Inputs slots for ::CRM_PK_CMD_CHECK_PARAM_N */
struct crm_pk_inops_check_param_n {
   struct crm_pk_slot p; /**< p parameter of curve */
   struct crm_pk_slot n; /**< n parameter of curve */
};

/** Inputs slots for ::CRM_PK_CMD_CHECK_XY */
struct crm_pk_inops_check_xy {
   struct crm_pk_slot p; /**< p parameter of curve */
   struct crm_pk_slot x; /**< x-coordinate */
   struct crm_pk_slot y; /**< y-coordinate */
};

#endif
