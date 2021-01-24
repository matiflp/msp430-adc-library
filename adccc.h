/**
  * @file     adc.h
  * @brief    Driver para manejar el ADC del micro.
  * @date     Created on: 14 dic. 2019
  * @authors  Matías López - Jesús López
  * @version  1.0
  */
//*****************************************************************************
//
// adc.h - Driver para manejar el ADC del micro.
//
//*****************************************************************************

#ifndef ADCCC_H_
#define ADCCC_H_

//*****************************************************************************
//                              Include
//*****************************************************************************
#include "driverlib.h"
#include "delay.h"
#include "gpio.h"

//*****************************************************************************
//                              Funciones Prototipos
//*****************************************************************************
//*****************************************************************************
//! \brief Habilita el \b ADC para recibir el valor a convertir por un pin
//!        externo.
//!
//! \details \b Descripción \n
//!          Habilita el pin ADC de entrada que corresponda para realizar una
//!          conversion. Esto lo realiza seteando el bit \b ADCPCTLx en el
//!          registro \b SYSCFG2.
//!
//! \param adcInput Variable que indica que entrada de donde se queiere obtener
//!                 una conversion.
//!
//! \return \c void
//!
//! \attention Modifica el bit del registro \b SYSCFG2.
//*****************************************************************************
static inline void ADC_initPin(const uint16_t adcInput);

//*****************************************************************************
//! \brief Configura el ADC para realizar la función requerida.
//!
//! \details \b Descripción \n
//!          Primero se desabilita el \b ADC mediante el bit \b ADCENC del
//!          registro \b ADCCTL0 para así poder modificar los bits de control ya
//!          que sin esto no seria posible. Luego se define el número de ciclos
//!          \b ADCCLK mediante los bits \b ADCSHT_2 (se utiliza como reloj de
//!          conversión y también para generar el período de muestreo cuando se
//!          selecciona el modo de muestreo de pulso), y se setea el bit \b ADCON.
//!          En el registro \b ADCCTL1 se selecciona la fuente de la señal de
//!          muestreo,y en \b ADCCTL2 se elige la resolucion de la conversion
//!          además de habilitar la interrupción de conversion completa. Además,
//!          en \b ADMCTL0 se selecciona el canal de entrada \b ADC correspondiente
//!          para realizar la conversion deseada. Por ejemplo, para seleccionar
//!          la referencia de voltaje de 1.5v se debe seleccionar el canal 13.
//!          Todos los canales diponibles se puede ve en la tabla
//!          <em> "Table 6-12. ADC Channel Connections"</em> en la
//!          página 47 del <em>"MSP430FR413x mixed-signal microcontrollers"</em>.
//!          Por último, se selecciona dos niveles de voltajes para definir los
//!          límites superior e inferior de la conversión.
//!
//! \param adcInput Variable que indica que entrada es necesaria para realizar
//!                 una configuración.
//!
//! \return \c void
//!
//! \attention Modifica los bits del registro \b ADCCTLx, \b ADCIE y \b ADCMCTL0.
//*****************************************************************************
static void ADC_initPort(const uint8_t adcInput);

//*****************************************************************************
//! \brief Da comienzo a la conversion.
//!
//! \details \b Descripción \n
//!          Se activa el \b ADC mediante el bit \b ADCENC del registro
//!          \b ADCCTL0. Ya finalizada la configuración se inicia la
//!          conversión mediante el bit \b ADCSC y se resetea automáticamente.
//!
//! \return \c void
//!
//! \atenttion Modifica los bits del registro \b ADCCTL0.
//*****************************************************************************
static inline void ADC_start(void);

//*****************************************************************************
//! \brief Habilita la referencia interna de 1.5V.
//!
//! \details \b Descripción \n
//!          Se escribe \b 0A5h para desbloquear los registros \b PMM de control.
//!          Luego se habilita la referencia interna en el registro \b PMMCTL2
//!           y se espera que este disponible para ser usada.
//!
//! \return \c void
//!
//! \attention Modifica los bits de los registros \b PMMCTLx.
//*****************************************************************************
static void ADC_initVref(void);

//*****************************************************************************
//! \brief Deshabilita la referencia interna para ahorrar energia.
//!
//! \details \b Descripción \n
//!          Deshabilita la referencia interna para ahorrar energía resetenado
//!          el bit \b INTREFEN en el registro \b PMMCTL2. Por ultimo se bloquea
//!          los registro PMM.
//!
//! \return \c void
//!
//! \atenttion Modifica los bits de los registros \b PMMCTLx.
//*****************************************************************************
static inline void ADC_stopVref(void);

//*****************************************************************************
//! \brief Detiene el ADC.
//!
//! \details \b Descripción \n
//!          Detiene el ADC una vez que no se lo utilice para ahorrar energía
//!          resetenado el bit \b ADCON en conjunto con el bit \b ADCENC en el
//!          registro \b ADCCTL0.
//!
//! \return \c void
//!
//! \atenttion Modifica los bits del registro \b ADCCTL0.
//*****************************************************************************
static inline void ADC_stop(void);

//*****************************************************************************
//! \brief Función que permite obtener el voltaje de bangap.
//!
//! \details \b Descripción \n
//!          Obtiene la referencia interna de 1.5V que, al ser un valor
//!          constante, permitira obtener el voltaje de la bateria de manera
//!          de hacer un control de su voltaje.
//!
//! \return \c La conversion de la referencia interna.
//*****************************************************************************
uint16_t ADC_getVref(void);

//*****************************************************************************
//! \brief Función que permite tomar una medida de una entrada analógica.
//!
//! \details \b Descripción \n
//!          Realiza la secuencia de configuración para tomar una medida.
//!
//! \param adcPin Pin deseado de donde se desea obtener el valor de conversion.
//! \param vccPort Puerto elegido para alimentar el sensor mediante un pin.
//! \param vccPin Pin elegido para alimentar el sensor.
//! \param dPort Puerto de donde se selecciona el pin de datos.
//! \param dPin Pin de datos.
//!
//! \return \c La conversion obtenida.
//*****************************************************************************
uint16_t ADC_takeMeasure(const uint8_t adcPin, const uint8_t vccPort,
                         const uint8_t vccPin, const uint8_t dPort,
                         const uint8_t dPin);

#endif /* ADCCC_H_ */
