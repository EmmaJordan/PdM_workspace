/*
 * API_adc.h
 *
 *  Created on: 9 abr. 2022
 *      Author: Win10
 */

#ifndef API_INC_API_ADC_H_
#define API_INC_API_ADC_H_

#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

typedef bool bool_t;

/**
 * Inicializa la configuracion de la UART indicando:
 * - paridad
 * - bits de parada
 * - bits de datos
 * - COM usado
 * - baud rate
 */
bool_t ADCinit();


#endif /* API_INC_API_ADC_H_ */
