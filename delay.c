/*
 * delay.c
 *
 *  Created on: 30 oct. 2019
 *      Authors: Matías López - Jesús López
 */
//*****************************************************************************
//
// delay.c - Driver para delays.
//
//*****************************************************************************

#include "delay.h"
/*****************************************************************************/
void delay_us(const uint16_t us)
{
    TA0CTL = TACLR;
    TA0CCR0 = us;
    TA0CCTL0 |= CCIE;
    TA0EX0 = TAIDEX_3;
    TA0CTL = TASSEL_2 + ID_1 + MC_1;
    __bis_SR_register(LPM3_bits + GIE);
}
/*****************************************************************************/
void delay_ms(const uint16_t ms)
{
    TA0CTL = TACLR;
    TA0CCR0 = ms;
    TA0CCTL0 |= CCIE;
    TA0EX0 = TAIDEX_3;
    TA0CTL = TASSEL_1 + ID_3 + MC_1;
    __bis_SR_register(LPM3_bits + GIE);
}
//***************************************************************************************************************
// Timer A0 interrupt service routine --> Timer1_A3 CC0
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
    TA0CTL = MC_0;
    TA0CCR0 = 0;
    TA0CTL &= ~TAIFG;
    TA0EX0 = TAIDEX_0;
    __bic_SR_register_on_exit(LPM3_bits + GIE);
}
