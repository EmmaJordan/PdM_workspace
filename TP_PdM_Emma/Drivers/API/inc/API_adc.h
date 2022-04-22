/*
 * API_adc.h
 *
 *  Created on: 22 abr. 2022
 *      Author: Win10
 */

#ifndef API_INC_API_ADC_H_
#define API_INC_API_ADC_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
#include <stm32f4xx_hal_adc.h>		//agregado Emma

void iniciaADC();
uint32_t myADCread();
void lecturakV_Update();

#endif /* API_INC_API_ADC_H_ */
