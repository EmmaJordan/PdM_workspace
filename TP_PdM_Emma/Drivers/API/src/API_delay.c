/*
 * API_delay.c
 *
 *  Created on: 22 mar. 2022
 *      Author: Win10
 */

#include "API_delay.h"

// Entrada: Puntero al delay y su duración en ms
// Salida: Ninguna
// Función: Inicializa los parámetros internos del delay
void delayInit( delay_t * delay, tick_t duration )
{
	if((delay != NULL) && (duration > 0))			// Verifica que el puntero sea valido y que la duracion sea un valor positivo
	{
		delay->startTime = 0;
		delay->duration = duration;
		delay->running = false;						// Inicializa el delay detenido
	}
}

// Entrada: Puntero al delay
// Salida: Bool que indica si ya transcurrió el tiempo del delay o no.
// Función: Comprueba si ya transcurrio el tiempo del delay
bool_t delayRead( delay_t * delay )
{
	if((delay != NULL) && (delay > 0))			// Verifica que el puntero sea válido y que la duración sea un valor positivo
	{
		if(delay->running)
		{
			if(HAL_GetTick() >= (delay->startTime + delay->duration))
			{
				delay->running = false;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			delay->startTime = HAL_GetTick();
			delay->running   = true;
			return false;
		}
	}
	else
	{
		return false;
	}
}

// Entrada: Puntero al delay y su duraciónen ms
// Salida: Ninguna
// Función: Cambia la duración del delay, sin importar si está corriendo o no
void delayWrite( delay_t * delay, tick_t duration )
{
	if((delay != NULL) && (duration > 0))			// Verifica que el puntero sea válido y que la duración sea un valor positivo
	{
		delay->duration = duration;
	}
}

// Entrada: Puntero al delay y su duraciónen ms
// Salida: Ninguna
// Función: Cambia la duración del delay, sin importar si está corriendo o no
tick_t delayGetDuration( delay_t * delay )
{
	return delay->duration;
}



