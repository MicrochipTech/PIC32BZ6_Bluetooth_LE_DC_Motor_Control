/** CryptoPK status codes
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
#ifndef CRM_PK_STATUSCODES_HEADER_FILE
#define CRM_PK_STATUSCODES_HEADER_FILE

#include "driver/security/api_table.h"

/**
 * @addtogroup CRM_PK_STATUS
 *
 * @{
 */

/** The function or operation succeeded */
#define CRM_OK  0

/** The function or operation was given an invalid parameter */
#define CRM_ERR_INVALID_PARAM 1

/** Unknown error */
#define CRM_ERR_UNKNOWN_ERROR 2

/** The operation is still executing */
#define CRM_ERR_BUSY 3

/** The input operand is not a quadratic residue */
#define CRM_ERR_NOT_QUADRATIC_RESIDUE 4

/** The input value for Rabin-Miller test is a composite value */
#define CRM_ERR_COMPOSITE_VALUE 5

/** Inversion of non-invertible value */
#define CRM_ERR_NOT_INVERTIBLE 6

/** The signature is not valid
 *
 * This error can happen during signature generation
 * and signature verification
 */
#define CRM_ERR_INVALID_SIGNATURE 7

/** The functionality or operation is not supported */
#define CRM_ERR_NOT_IMPLEMENTED 8

/** The output operand is a point at infinity */
#define CRM_ERR_POINT_AT_INFINITY 9

/** The input value is outside the expected range */
#define CRM_ERR_OUT_OF_RANGE 10

/** The modulus has an unexpected value
 *
 * This error happens when the modulus is zero or
 * even when odd modulus is expected
 */
#define CRM_ERR_INVALID_MODULUS 11

/** The input point is not on the defined elliptic curve */
#define CRM_ERR_POINT_NOT_ON_CURVE 12

/** The input operand is too large */
#define CRM_ERR_OPERAND_TOO_LARGE 13

/** A platform specific error */
#define CRM_ERR_PLATFORM_ERROR 14

/** The evaluation period for the product expired */
#define CRM_ERR_EXPIRED 15

/** The hardware is still in IK mode
 *
 * This error happens when a normal operation
 * is started and the hardware is still in IK mode.
 * Run command ::CRM_PK_CMD_IK_EXIT to exit the IK
 * mode and to run normal operations again
*/
#define CRM_ERR_IK_MODE 16

/** The parameters of the elliptic curve are not valid. */
#define CRM_ERR_INVALID_CURVE_PARAM 17

/** Return a brief text string describing the given status code.
 *
 * @param[in] code Value of status code
 * @return Text string describing the status code
*/
typedef const char *(*FUNC_CRM_DESCRIBE_STATUSCODE)(int code);
#define CRM_DESCRIBE_STATUSCODE         ((FUNC_CRM_DESCRIBE_STATUSCODE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_DESCRIBE_STATUSCODE)))

/** @} */

#endif
