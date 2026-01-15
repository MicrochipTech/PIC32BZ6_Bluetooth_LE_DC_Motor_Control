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

/*******************************************************************************
  Middleware Assert Header File

  Company:
    Microchip Technology Inc.

  File Name:
    mw_assert.h

  Summary:
    Defines the middleware assertion functionality.

  Description:
    This header file declares the assertion macros and functions used by
    middleware components to validate assumptions during runtime. If an
    assertion fails, it can aid in identifying incorrect program behavior
    early in the development cycle.
 *******************************************************************************/

/**
 * @addtogroup BLE_MW BLE Middleware
 * @{
 */

/**
 * @defgroup MW_ASSERT Assertion macros
 * @brief Provides assertion macros for middleware validation.
 * @{
 */

#ifndef MW_ASSERT_H
#define MW_ASSERT_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
/**
 * @brief Asserts that a condition is true at compile time.
 *
 * This macro implements a static assertion mechanism that checks a condition
 * during compilation. If the condition is false, it will cause a compile-time
 * error due to the negative size array declaration. This is useful for
 * enforcing constraints that can be verified during compilation rather than at
 * runtime.
 *
 * @param[in] check The compile-time condition that should be true.
 *
 * Example usage:
 * @code
 *     MW_ASSERT(sizeof(int) == 4);
 * @endcode
 */
#define  MW_ASSERT(check)     extern char assertion[(check) ? 1 : -1]

/** @} */

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif //MW_ASSERT_H