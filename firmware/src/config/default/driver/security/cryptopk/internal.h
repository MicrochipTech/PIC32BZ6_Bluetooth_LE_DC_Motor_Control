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

#ifndef INTERNAL_HEADER_FILE_PK
#define INTERNAL_HEADER_FILE_PK

#include <stdint.h>

struct crm_pk_cmd_def;

struct crm_regs
{
   char *base;
};

struct crm_pk_accel
{
   struct crm_regs regs;
   char *cryptoram;
   int slot_sz;
   int op_size;
   const struct crm_pk_cmd_def *cmd;
   struct crm_pk_cnx *cnx;
   const char *outputops[12];
   void *userctxt;
   int ik_mode;
};

#define NUM_PK_INST     1

struct crm_pk_cnx {
   struct crm_pk_accel instances[NUM_PK_INST];
   struct crm_pk_capabilities caps;
};

int crm_pk_open_extra(struct crm_pk_cnx *cnx, struct crm_pk_config *cfg);

void crm_pk_wrreg(struct crm_regs *regs, uint32_t addr, uint32_t v);

uint32_t crm_pk_rdreg(struct crm_regs *regs, uint32_t addr);

#endif
