/*
 * API_system.h
 *
 *  Created on: 23 abr. 2022
 *      Author: Win10
 */

#ifndef API_INC_API_SYSTEM_H_
#define API_INC_API_SYSTEM_H_

#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#define pinBuzzer 2
#define pinRx 4

void inputsInit();
void outputsInit();

#endif /* API_INC_API_SYSTEM_H_ */
