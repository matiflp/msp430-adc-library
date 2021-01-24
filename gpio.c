/*
 * gpio.c
 *
 *  Created on: 23 jul. 2020
 *      Author: Matías Lopez - Jesús López
 */
//*****************************************************************************
//
// gpio.c - Driver para manejar los pines de uC.
//
//*****************************************************************************

//*****************************************************************************
#include "gpio.h"

//*****************************************************************************
void GPIO_configPins(uint16_t* selectedPort, uint16_t* selectedPin)
{
    uint16_t port = *(selectedPort);
    uint8_t  pin  = *(selectedPin);

    switch (port)
        {
            case 1:
                *(selectedPin) = (0x0001 << pin);
                *(selectedPort) = 0x0200;
                break;
            case 2:
                *(selectedPin) = (0x0001 << pin);
                *(selectedPin) <<= 8;
                *(selectedPort) =  0x0200;
                break;
            case 3:
                *(selectedPin) = (0x0001 << pin);
                *(selectedPort) = 0x0220;
                break;
            case 4:
                *(selectedPin) = (0x0001 << pin);
                *(selectedPin) <<= 8;
                *(selectedPort) = 0x0220;
                break;
            case 5:
                *(selectedPin) = (0x0001 << pin);
                *(selectedPort) = 0x0240;
                break;
            case 6:
                *(selectedPin) = (0x0001 << pin);
                *(selectedPin) <<= 8;
                *(selectedPort) = 0x0240;
                break;
            case 7:
                *(selectedPin) = (0x0001 << pin);
                *(selectedPort) = 0x0260;
                break;
            case 8:
                *(selectedPin) = (0x0001 << pin);
                *(selectedPin) <<= 8;
                *(selectedPort) = 0x0260;
                break;
        }
}
//*****************************************************************************
void GPIO_powerOnSensor(const uint8_t vccPort, const uint8_t vccPin)
{
    uint16_t selectedPortVcc = vccPort;
    uint16_t selectedPinVcc  = vccPin;

    GPIO_configPins(&selectedPortVcc, &selectedPinVcc);
    GPIO_setHighOnPin(selectedPortVcc, selectedPinVcc);
}
//*****************************************************************************
void GPIO_powerOffSensor(const uint8_t vccPort, const uint8_t vccPin)
{
    uint16_t selectedPortVcc = vccPort;
    uint16_t selectedPinVcc  = vccPin;

    GPIO_configPins(&selectedPortVcc, &selectedPinVcc);
    GPIO_setLowOnPin(selectedPortVcc, selectedPinVcc);
}
