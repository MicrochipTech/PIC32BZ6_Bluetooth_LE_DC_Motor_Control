/*******************************************************************************
  Quadrature Encoder Interface (QEI) Peripheral Library (PLIB)

  Company:
    Microchip Technology Inc.

  File Name:
    plib_qei.c

  Summary:
    QEI Source File

  Description:
    None

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
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
#include "device.h"
#include "plib_qei.h"
#include "interrupts.h"

// *****************************************************************************

// *****************************************************************************
// Section: QEI Implementation
// *****************************************************************************
// *****************************************************************************


void QEI_Initialize (void)
{


    /* QEICON register  */
    /*  CCM    = 0 */
    /*  GATEN  = 0 */
    /*  CNTPOL = 0 */
    /*  INTDIV = 0 */
    /*  IMV    = 0  */
    /*  PIMOD  = 1  */
    /*  QEISIDL = 0 */
    QEI_REGS->QEI_QEICON = 0x400;

    /* QEIIOC register  */
    /*  QEAPOL    = 0 */
    /*  QEBPOL  = 0 */
    /*  IDXPOL = 0 */
    /*  HOMPOL = 0 */
    /*  SWPAB    = 0  */
    /*  OUTFNC  = 0  */
    /*  QFDIV   = 0   */
    /*  FLTREN  = 1   */
    QEI_REGS->QEI_QEIIOC = 0x4000;

    QEI_REGS->QEI_QEIICC = 200U;
    QEI_REGS->QEI_QEICMPL = 1U;

    /* QEISTAT register  */
    /*  IDXIEN    = false */
    /*  HOMIEN  = false */
    /*  VELOVIEN = false */
    /*  POSOVIEN = false */
    /*  PCIIEN    = false  */
    /*  PCLEQIEN  = false    */
    /*  PCHEQIEN = false     */
    QEI_REGS->QEI_QEISTAT = 0x0;
}


void QEI_Start(void)
{
    /* Enable QEI channel */
    QEI_REGS->QEI_QEICONSET = QEI_QEICON_ON_Msk;
}

void QEI_Stop(void)
{
    /* Disable QEI channel */
    QEI_REGS->QEI_QEICONCLR = QEI_QEICON_ON_Msk;
}

uint32_t QEI_PulseIntervalGet(void)
{
    return QEI_REGS->QEI_INTHLD;
}

void QEI_PositionWindowSet(uint32_t high_threshold, uint32_t low_threshold)
{
    QEI_REGS->QEI_QEIICC   = high_threshold;
    QEI_REGS->QEI_QEICMPL  = low_threshold;
}

void QEI_PositionCountSet(uint32_t position_count)
{
    QEI_REGS->QEI_POSCNT = position_count;
}

void QEI_VelocityCountSet(uint32_t velocity_count)
{
    QEI_REGS->QEI_VELCNT = velocity_count;
}


