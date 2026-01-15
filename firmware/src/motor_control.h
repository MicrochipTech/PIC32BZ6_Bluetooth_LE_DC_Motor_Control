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

/*******************************************************************************
 Brushed DC Motor Control interface

  Company:
    Microchip Technology Inc.

  File Name:
    motor_control.c

  Summary:
    This header file provides prototypes and definitions for controlling 
    the DC Motor.

  Description:
    This header file provides function prototypes and data type definitions for
    controlling the DC Motor with PWM.
 *******************************************************************************/
#ifndef _MOTOR_CONTROL_H
#define _MOTOR_CONTROL_H
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"


typedef enum {
    MOTOR_OFF = 0,
    MOTOR_ON
} motorState_t;

typedef enum {
    MOTOR_FORWARD,
    MOTOR_REVERSE
} motorDirection_t;

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

void Motor_Start();
void Motor_Stop();
void Motor_SetSpeed(uint32_t percentage);
void Motor_SetDirection(motorDirection_t direction);
void Motor_Toggle();

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MOTOR_CONTROL_H */

/*******************************************************************************
 End of File
 */
