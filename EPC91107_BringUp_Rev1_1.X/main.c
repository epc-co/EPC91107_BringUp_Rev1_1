/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/tmr1.h"
#include "mcc_generated_files/adc/adc1.h"
#include "mcc_generated_files/pwm_hs/pwm.h"
#include "mcc_generated_files/system/pins.h"

// Define Global Variables:
// Time scale: 5 ns/tick (based on a 200 MHz)
int PWMperiod = 1428;    // 140.056kHz - Note that changing the period will require adjusting PhaseDelay
int DutyCycle = 1071;    // 25%: 357, 50%: 714, 75%: 1071, 100%: 1500
int PhaseDelay = 476;    // 120 degrees of 140.056kHz
int DTHigh = 3;          // 15 ns
int DTLow = 3;           // 15 ns

/* Create a pointer of type TMR_INTERFACE and assign it to the address of the Timer1 TIMER_INTERFACE struct.
This enables us to get access the portable API interface, which ensures that it's easy to change the peripheral instance the timer runs on. */
const struct TIMER_INTERFACE *Timer = &Timer1;

// This function could be used to toggle GPIOs for the low freq. bridge
void Timer_Callback_1ms(void) 
{
    //Add instructions here
}

int main(void)
{
    SYSTEM_Initialize();
    Timer->TimeoutCallbackRegister(Timer_Callback_1ms);
    
    PWM_PeriodSet(1,PWMperiod);
    PWM_PeriodSet(2,PWMperiod);
    PWM_PeriodSet(3,PWMperiod);
    
    PWM_TriggerCompareValueSet(1,PhaseDelay);
    PWM_TriggerCompareValueSet(2,PhaseDelay);
    
    PWM_DutyCycleSet(1,DutyCycle);
    PWM_DutyCycleSet(2,DutyCycle);
    PWM_DutyCycleSet(3,DutyCycle);
    
    PWM_DeadTimeLowSet(1,DTLow);
    PWM_DeadTimeLowSet(2,DTLow);
    PWM_DeadTimeLowSet(3,DTLow);
    
    PWM_DeadTimeHighSet(1,DTHigh);
    PWM_DeadTimeHighSet(2,DTHigh);
    PWM_DeadTimeHighSet(3,DTHigh);

    while(1)
    {
        //PWM_Enable();
        PG1CONLbits.ON = 1; // Set to 0 for 0% duty cycle              
        PG2CONLbits.ON = 1; // Set to 0 for 0% duty cycle              
        PG3CONLbits.ON = 1; // Set to 0 for 0% duty cycle 
    }    
}