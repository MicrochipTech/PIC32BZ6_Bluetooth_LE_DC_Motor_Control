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
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for for controlling the DC Motor.

  Description:
    This file contains the source code for controlling the DC Motor with PWM.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "motor_control.h"
#include "definitions.h"


static motorState_t motorState = MOTOR_OFF;
static motorDirection_t motorDirection = MOTOR_FORWARD;
uint32_t pwmPeriod = 400;
uint32_t lastSpeed = 50;



void Motor_Start()
{
    motorState = MOTOR_ON;
    /* Start PWM*/
    Motor_SetSpeed(lastSpeed);
    TCC1_PWMStart();
}

void Motor_Stop()
{
    motorState = MOTOR_OFF;
    TCC1_PWMStop();
    // braking (should brake for 0.1 seconds before issuing start again))
    GPIO_PinClear(GPIO_PIN_RD0);
    GPIO_PinClear(GPIO_PIN_RB12);
}

void Motor_SetSpeed(uint32_t percentage)
{
    uint32_t newDuty = pwmPeriod*percentage;
    newDuty/=100;
    if (!TCC1_PWM24bitDutySet(TCC1_CHANNEL1, newDuty))
    {
        //SYS_CONSOLE_MESSAGE("Failed to update motor speed\r\n");
    }
    else
    {
        //SYS_CONSOLE_PRINT("Set new duty percentage %d %d\r\n", percentage, newDuty);
    }
    lastSpeed = percentage;
}

void Motor_SetDirection(motorDirection_t direction)
{
    if (direction == MOTOR_FORWARD)
    {
        motorDirection = MOTOR_FORWARD;
        GPIO_PinSet(GPIO_PIN_RB12);  
        GPIO_PinClear(GPIO_PIN_RD0);          
    }
    else
    {
        motorDirection = MOTOR_REVERSE;
        GPIO_PinSet(GPIO_PIN_RD0);  
        GPIO_PinClear(GPIO_PIN_RB12);                  
    }
}

void Motor_Toggle()
{
    // motor toggling only if sensor is not tripped.
    if (motorState == MOTOR_OFF)
    {
        // toggle direction each time motor is turned on
        if (motorDirection == MOTOR_FORWARD)
        {
            Motor_SetDirection(MOTOR_REVERSE);
        }
        else
        {
            Motor_SetDirection(MOTOR_FORWARD);
        }
        Motor_Start();
    }
    else
    {
        // only toggle direction when turning on
        Motor_Stop();
    }
    //SYS_CONSOLE_PRINT("Toggling motor New State:%d New direction:%d\r\n", motorState, motorDirection);
    
}
/* *****************************************************************************
 End of File
 */
