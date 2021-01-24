#include "adccc.h"

int main(void)
{
    // Variables locales
    volatile uint16_t adcResult = 0;                            // Guarda la conversion de los sensores en crudo.
    volatile float vSup = 0.0;
    volatile float vBat = 0.0;
    volatile float ec5 = 0.0;
    volatile float mpx5700 = 0.0;

    // WATCHDOG -----------------------------------------------------------------------------------------------------------------------------------------------
    WDT_A_hold(WDT_A_BASE);

    // Desabilita el modo de alta impedancia habilitando la configuración establecida previamente.
    PM5CTL0 &= ~LOCKLPM5;

    // VREF -----------------------------------------------------------------------------------------------------------------------------------------------
    // VREF - Obtengo el valor de referencia de 1.5.
    adcResult = ADC_getVref();

    // VREF - Calculo de la tension de alimentación
    vSup = (1.5 * 1023) / adcResult;

    // BATERIA --------------------------------------------------------------------------------------------------------------------------------------------
    // BATERIA - Obtengo la conversion de la bateria.
    adcResult = ADC_takeMeasure(ADCINCH_4, 4, 7, 1, 4);

    // BATERIA - Calculo del voltaje de la bateria.
    vBat = (((adcResult * vSup) / 1023) * ((8200 + 2200) / 2200)) + 0.9;  // 8.2 k y 2.2k son los valores del divisor resistivo y 0.9v es la caida en los transistores.

    // EC5 -------------------------------------------------------------------------------------------------------------------------------------------
    // EC5 - Realiza una medicion
    adcResult = ADC_takeMeasure(ADCINCH_9, 4, 0, 8, 1);

    // EC5 - Calculo de la tension del sensor.
    ec5 = (adcResult * vSup) / 1023;    // Con este valor se calcula la humedad. No se calcula aqui porque es necesario calibrar el sensor en base al suelo donde se coloca.

    // MPX5700 -------------------------------------------------------------------------------------------------------------------------------------------
    // MPX5700 - Realiza una medición
    adcResult = ADC_takeMeasure(ADCINCH_5, 5, 6, 1, 5);

    mpx5700 = ((adcResult - 41.37) / (972.28 - 41.37)) * 700; // Este es un sensor de 5v, por lo tanto se coloca un divisor resistivo para llevarlo a 3.3v y no dañar el MCU.
                                                              // De ahi salen los valores de offset para obtener un valor correcto en la medicion.

    while(1);
}
