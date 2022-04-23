/*
 * API_debounce.h
 *
 *  Created on: 29 mar. 2022
 *      Author: Win10
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#define BUTTON_menosTiempo_PRESSED  (GPIOG->IDR & (1<<1)  )  //-Tiempo
#define BUTTON_masTiempo_PRESSED  	(GPIOG->IDR & (1<<0)  )  //+Tiempo

typedef bool bool_t;

void debounceFSM_init();	// debe cargar el estado inicial o reiniciar en caso de error
uint8_t debounceFSM_update();	// control de todas las máquinas de estado de pulsadores

void debounceB1_update();	// control máquina de estados menos Tiempo
void debounceB2_update();   // control máquina de estados mas Tiempo
void debounceB3_update();	// debe leer las entradas, resolver la lógica de transición de
							// estados y actualizar las salidas (llamado periódico)
void buttonB1Pressed();		// boton menos Tiempo presionado
void buttonB2Pressed();		// boton más Tiempo presionado
void buttonB3Pressed();		// boton Disparo presionado

void decreaseTime();		// función para decrementar Tiempo Disparo
void increaseTime();		// función para incrementar Tiempo Disparo
void applyRx();				// función para activar etapa de Disparo

bool_t readKey();			//lectura del botón de usuario
//void miToggleLed(uint8_t led);

#endif /* API_INC_API_DEBOUNCE_H_ */
