/*
 * port_config.h
 *
 *  Created on: 23 jul. 2020
 *      Author: Jes�s
 */
//*****************************************************************************
//
// gpio.h - Driver para manejar los pines de uC.
//
//*****************************************************************************

#ifndef GPIO_H_
#define GPIO_H_
//*****************************************************************************
//                              Include
//*****************************************************************************
#include "driverlib.h"

//*****************************************************************************
//                              Configuraci�n de Pines
//*****************************************************************************
//*****************************************************************************
//! @name Configuraci�n de pines:
//! \brief Definiciones de Pins dispuesta de manera tal que no es necesario
//!        modificar nada aca, solamente en la funci�n que utiliza estos defines.
//! @{
//*****************************************************************************

//*****************************************************************************
//! \details Coloca un pin como salida.
//*****************************************************************************
#define GPIO_setPinAsOutput(baseAddress, selectedPin)               HWREG16(baseAddress + OFS_PADIR) |= selectedPin;

//*****************************************************************************
//! \details Coloca un pin de salida en alto.
//*****************************************************************************
#define GPIO_setHighOnPin(baseAddress, selectedPin)                 HWREG16(baseAddress + OFS_PADIR) |=  selectedPin;   \
                                                                    HWREG16(baseAddress + OFS_PAREN) &= ~selectedPin;   \
                                                                    HWREG16(baseAddress + OFS_PAOUT) |=  selectedPin;
//*****************************************************************************
//! \details Coloca un pin de salida en bajo.
//*****************************************************************************
#define GPIO_setLowOnPin(baseAddress, selectedPin)                  HWREG16(baseAddress + OFS_PADIR) |=  selectedPin;   \
                                                                    HWREG16(baseAddress + OFS_PAREN) &= ~selectedPin;   \
                                                                    HWREG16(baseAddress + OFS_PAOUT) &= ~selectedPin;
//*****************************************************************************
//! \details Coloca un pin como entrada.
//*****************************************************************************
#define GPIO_setPinAsInput(baseAddress, selectedPin)                HWREG16(baseAddress + OFS_PADIR) &= ~selectedPin;

//*****************************************************************************
//! \details Obtiene el estado de un pin de entrada.
//*****************************************************************************
#define GPIO_getInputPinValue(baseAddress, selectedPin)             HWREG16(baseAddress + OFS_PAIN) & (selectedPin)

//*****************************************************************************
//! \details Establece una resistencia de Pullup en un pin de entrada.
//*****************************************************************************
#define GPIO_setPinWithPullDownResistor(baseAddress, selectedPin)   HWREG16(baseAddress + OFS_PADIR) &= ~selectedPin;   \
                                                                    HWREG16(baseAddress + OFS_PAREN) |= selectedPin;    \
                                                                    HWREG16(baseAddress + OFS_PAOUT) &= ~selectedPin;
//*****************************************************************************
//! \details Establece una resistencia de Pulldown en un pin de entrada.
//*****************************************************************************
#define GPIO_setPinWithPullUpResistor(baseAddress, selectedPin)     HWREG16(baseAddress + OFS_PADIR) &= ~selectedPin;   \
                                                                    HWREG16(baseAddress + OFS_PAREN) |= selectedPin;    \
                                                                    HWREG16(baseAddress + OFS_PAOUT) |= selectedPin;
//*****************************************************************************
//! \details Establece la funci�n primaria de un determinado pin.
//*****************************************************************************
#define GPIO_setPinPrimaryFunction(baseAddress, selectedPin)        HWREG16(baseAddress + OFS_PASEL0) |= selectedPin;  \
                                                                    HWREG16(baseAddress + OFS_PASEL1) &= ~selectedPin;
//*****************************************************************************
//! \details Establece la funci�n secundaria de un determinado pin.
//*****************************************************************************
#define GPIO_setPinSecondFunction(baseAddress, selectedPin)         HWREG16(baseAddress + OFS_PASEL0) &= ~selectedPin;  \
                                                                    HWREG16(baseAddress + OFS_PASEL1) |= selectedPin;
//*****************************************************************************
//! \details Establece la funci�n terciaria de un determinado pin.
//*****************************************************************************
#define GPIO_setPinTertiaryFunction(baseAddress, selectedPin)       HWREG16(baseAddress + OFS_PASEL0) |= selectedPin;  \
                                                                    HWREG16(baseAddress + OFS_PASEL1) |= selectedPin;

//*****************************************************************************
//! \details El pin de modo configuraci�n es colocado como entrada.
//*****************************************************************************
#define GPIO_configurationMode                                      { P2DIR &= ~BIT7; P2REN &= ~BIT7;}

//*****************************************************************************
//! \details Estado del pin de modo configuraci�n.
//*****************************************************************************
#define GPIO_configurationPin                                       P2IN & BIT7

//*****************************************************************************
//! @}
//*****************************************************************************

//*****************************************************************************
//                              Funciones Prototipos
//*****************************************************************************
//*****************************************************************************
//! \brief Configure los pines seleccionados por el usuario para realizar la
//!        distintas operaci�nes que lo requieran.
//!
//! \details \b Descripci�n \n
//!          Funci�n que recibe dos punteros como argumentos que se utilizar�n
//!          para realizar la configuraci�n de los pines seg�n la elecci�n del
//!          usuario. Para realizar la configuraci�n se utiliza un \c switch(),
//!          y si se tratase de un puerto impar solamente se desplaza el pin
//!          hacia la izquierda de acuerdo a la elecci�n del usuario y se pasa
//!          la direcci�n base del puerto que corresponda, por ejemplo, para
//!          los puertos 1 y 2 que corresponden al \b PA se le asigna la
//!          direcci�n base \b 0x0200. Si el puerto elegido es par, adem�s de
//!          lo realizado para un puerto impar, se realiza un desplazamiento al
//!          registro parte alta que es el que corresponde para los puertos
//!          pares.
//!
//! \param *selectedPort Puntero que define el puerto seleccionado.
//! \param *selectedPin Puntero que define el pin elegido en el puerto deseado.
//!
//! \return \c void.
//*****************************************************************************
void GPIO_configPins(uint16_t*, uint16_t*);

//*****************************************************************************
//! \brief Funci�n para encender un sensor.
//!
//! \details \b Descripci�n \n
//!          Realiza el encendido de un sensor a trav�s de una llave electr�nica
//!          controlada por un pin, el cual es indicado en uno de los
//!          par�metros recibidos, adem�s del puerto correspondiente.
//!
//! \param vccPort Puerto de donde se obtiene el pin de alimentaci�n.
//! \param vccPin Pin de alimentaci�n.
//!
//! \return \c void.
//*****************************************************************************
void GPIO_powerOnSensor(const uint8_t vccPort, const uint8_t vccPin);

//*****************************************************************************
//! \brief Funci�n para apagar un sensor.
//!
//! \details \b Descripci�n \n
//!          Realiza el apagado de un sensor a trav�s de una llave electr�nica
//!          controlada por un pin, el cual es indicado en uno de los
//!          par�metros recibidos, adem�s del puerto correspondiente.
//!
//! \param vccPort Puerto de donde se obtiene el pin de alimentaci�n.
//! \param vccPin Pin de alimentaci�n.
//!
//! \return \c void.
//*****************************************************************************
void GPIO_powerOffSensor(const uint8_t vccPort, const uint8_t vccPin);

#endif /* GPIO_H_ */
