/** Semantic version numbers of the CryptoPK API.
 *
 * The version numbering used here adheres to the concepts outlined in
 * https://semver.org/.
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

#ifndef CRM_PK_VERSION_HEADER_FILE
#define CRM_PK_VERSION_HEADER_FILE


/** Major version number of the CryptoPK API
 *
 * Changes made to the API with the same major version number remain
 * backwards compatible. Applications should check at compile time that
 * current major version number matches the one they were made for.
 */
#define CRM_PK_API_MAJOR 1


/** Minor version number of the CryptoPK API
 *
 * New features added while maintaining backwards compatibility increment
 * the minor version number. Applications should check that the minor
 * version number is equal or larger than the minor version number
 * they were written for.
 */
#define CRM_PK_API_MINOR 4


/** Check application has compatible version numbers.
 *
 * Non-zero if the API is compatible and zero if incompatible.
 * The application is compatible if the major number does matches
 * the library major number and the application minor number is equal or
 * smaller than the library minor number.
 */
#define CRM_PK_API_IS_COMPATIBLE(appmajor, appminor) \
    (((appmajor) == CRM_PK_API_MAJOR)\
    && ((appminor) <= CRM_PK_API_MINOR))


/** Assert that the application is compatible with the library
 *
 * If the application is not compatible, this macro will cause a compile
 * time error.
 */
#define CRM_PK_API_ASSERT_COMPATIBLE(appmajor, appminor) \
    typedef char crm_pk_api_check_app_semver_fail[ \
    (CRM_PK_API_IS_COMPATIBLE(appmajor, appminor)) ? 1 : -1]

#endif
