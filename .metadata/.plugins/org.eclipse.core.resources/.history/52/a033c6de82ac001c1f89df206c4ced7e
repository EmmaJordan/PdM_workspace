/*
 * API_delay.c
 *
 *  Created on: Mar 20, 2022
 *      Author: amilcar Rincon
 */

#include "../Inc/API_delay.h"



 // Funcion que inicializa los parametros internos del delay.

void delayInit (delay_t * delay, tick_t duration){  // se verifica que el puntero sea valido y que la duracion sea positiva y mayor a cero.
	if ((delay != NULL) && (duration >0)){
		delay-> duration = duration;
		delay-> running = false;
	}
}

// Funcion Bool que indica si ya transcurrio el tiempo del delay.

bool_t delayRead(delay_t * delay){

	bool timeReached =false;

	if (delay != NULL){
		if(delay-> running){   // si el delay esta corriendo calcula si ya paso el tiempo del delay.
			if ((HAL_GetTick() - delay-> startTime)>= delay->duration){ // si ya paso el tiempo guarda el timestamp actual.
				timeReached=true;
				delay->startTime = HAL_GetTick();
			}
		}
		else { // si el delay esta detenido, lo reanuda y guarda el timestamp actual
			delay->startTime=HAL_GetTick();
			delay->running = true;
		}
	}
	return timeReached;
}

//Funcion que cambia la duracion del delay, sin importar si esta corriendo o no.

void delayWrite (delay_t * delay, tick_t duration){   // se verifica que el puntero sea valido y que la duracion sea positiva y mayor a cero.
	if ((delay!=NULL)&& (duration>0)){
		delay ->duration = duration;
	}
}
