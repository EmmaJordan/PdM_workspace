/*
 * API_debounce.h
 *
 *  Created on: 29 mar. 2022
 *      Author: Win10
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

//#include "API_delay.h"
#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

typedef bool bool_t;



void debounceFSM_init();	// debe cargar el estado inicial o reiniciar en caso de error
void debounceFSM_update();	// debe leer las entradas, resolver la lógica de transición de
							// estados y actualizar las salidas (llamado periódico)
void buttonPressed();		// debe togglear el LED1
void buttonReleased();		// debe togglear el LED3

bool_t readKey();			//lectura del botón de usuario
void miToggleLed(uint8_t led);

#endif /* API_INC_API_DEBOUNCE_H_ */
