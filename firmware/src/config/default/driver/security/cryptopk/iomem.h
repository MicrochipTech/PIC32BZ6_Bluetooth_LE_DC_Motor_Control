/** Memory operation functions
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
#ifndef IOMEM_HEADER_FILE
#define IOMEM_HEADER_FILE

/** Clear device memory
 *
 * @param[in] dst Memory to clear.
 * Will be zeroed after this call
 * @param[in] sz Number of bytes to clear
*/
void ioclrmem(void *dst, size_t sz);

/** Write src to device memory at dst.
 *
 * The write to device memory will always use write instructions at naturally
 * aligned addresses.
 *
 * @param[out] dst Destination of write operation.
 * Will be modified after this call
 * @param[in] src Source of write operation
 * @param[in] sz The number of bytes to write from src to dst
 */
void iowrmem(void *dst, const void *src, size_t sz);

/** Read from device memory at src into normal memory at dst.
 *
 * The read from device memory will always use read instructions at naturally
 * aligned addresses.
 *
 * @param[out] dst Destination of read operation.
 * Will be modified after this call
 * @param[in] src Source of read operation
 * @param[in] sz The number of bytes to read from src to dst
 */
void iordmem(void *dst, const void *src, size_t sz);

#endif
