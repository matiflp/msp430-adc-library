/*
 * adc.c
 *
 *  Created on: 14 dic. 2019
 *      Author: Matías López - Jesús López
 */
//*****************************************************************************
//
// adc.c - Driver para manejar el ADC del micro.
//
//*****************************************************************************

#include "adccc.h"
//*****************************************************************************
static inline void ADC_initPin(const uint16_t adcInput)
{
    // Configure ADC Ax pin
    SYSCFG2 |= adcInput;
}
//*****************************************************************************
static void ADC_initPort(const uint8_t adcInput)
{
    // Configure ADC10
    ADCCTL0 &= ~ADCENC;                     // Disable ADC
    ADCCTL0 = ADCSHT_2 | ADCON;             // ADCON, S&H=16 ADC clks
    ADCCTL1 = ADCSHP;                       // ADCCLK = MODOSC; sampling timer
    ADCCTL2 = ADCRES;                       // 10-bit conversion results
    ADCMCTL0 = adcInput | ADCSREF_0;        // Ax ADC input select; Vref=AVCC
    ADCIE = ADCIE0;                         // Enable ADC conv complete interrupt
}
//*****************************************************************************
static inline void ADC_start(void)
{
    ADCCTL0 |= ADCENC | ADCSC;              // Sampling and conversion start
    __bis_SR_register(LPM3_bits | GIE);     // Enter LPM0, ADC_ISR will force exit
}
//*****************************************************************************
static void ADC_initVref(void)
{
    // Configure reference module located in the PMM
    PMMCTL0_H = PMMPW_H;                    // Unlock the PMM registers
    PMMCTL2 |= INTREFEN;                    // Enable internal reference
    delay_us(60);                           // Poll till internal reference settles
    //while(!(PMMCTL2 & REFGENRDY));        // Poll till internal reference settles
}
//*****************************************************************************
static inline void ADC_stopVref(void)
{
    PMMCTL2 &= ~INTREFEN;                    // For low power
    PMMCTL0_H &= ~PMMPW_H;                   // Unlock the PMM registers
}
//*****************************************************************************
static inline void ADC_stop(void)
{
    ADCCTL0 &= ~(ADCENC | ADCON);
}
//*****************************************************************************
uint16_t ADC_getVref(void)
{
    // VREF - Configura el ADC
    ADC_initPort(ADCINCH_13);

    // VREF - Habilita la referencia interna
    ADC_initVref();

    // VREF - Inicia la conversion
    ADC_start();

    // VREF - Detiene el ADC
    ADC_stop();

    // VREF - Detiene la Referencia Interna
    ADC_stopVref();

    return(ADCMEM0);
}
//*****************************************************************************
uint16_t ADC_takeMeasure(const uint8_t adcPin, const uint8_t vccPort,
                         const uint8_t vccPin, const uint8_t dPort,
                         const uint8_t dPin)
{
    uint16_t adcInput;

    // Alimantación
    GPIO_powerOnSensor(vccPort, vccPin);
    delay_ms(5);

    // Inicializa Pin ADC
    adcInput = 0x0001 << adcPin;
    ADC_initPin(adcInput);

    // Configura el ADC
    ADC_initPort(adcPin);

    // Inicia la conversion
    ADC_start();

    // Detiene el ADC
    ADC_stop();

    // Apago el sensor
    GPIO_powerOffSensor(vccPort, vccPin);
    GPIO_powerOffSensor(dPort, dPin);

    return (ADCMEM0);
}
//****************************************************************************************************************************************************
// ADC interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC_VECTOR))) ADC_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(ADCIV, ADCIV_ADCIFG))
    {
        case ADCIV_NONE:
            break;
        case ADCIV_ADCOVIFG:
            break;
        case ADCIV_ADCTOVIFG:
            break;
        case ADCIV_ADCHIIFG:
            break;
        case ADCIV_ADCLOIFG:
            break;
        case ADCIV_ADCINIFG:
            break;
        case ADCIV_ADCIFG:
            ADCIFG &= ~ADCIFG0;
            __bic_SR_register_on_exit(LPM3_bits + GIE);   // Exit from LPM
            break;
        default:
            break;
    }
}
