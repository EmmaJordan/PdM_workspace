/*
 * API_debounce.c
 *
 *  Created on: 29 mar. 2022
 *      Author: Win10
 */

#include "API_delay.h"
#include "API_debounce.h"

#define TIME_ANTIREBOTE 40


//Privada
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;


static delay_t delayAntiReboteB1;
static delay_t delayAntiReboteB2;
static delay_t delayAntiReboteB3;

static debounceState_t actualB1State;
static debounceState_t actualB2State;
static debounceState_t actualB3State;

static uint8_t changeState = 0;

/*	Función: lee las entradas, resuelve la lógica de transición de datos, actualiza las salidas
	Entrada: ninguna
	Salida: ninguna
	Nota: es una función pública porque se llama desde fuera del módulo (main) */
uint8_t debounceFSM_update()
{
	changeState = 0;
	debounceB1_update();
	debounceB2_update();
	debounceB3_update();
	return changeState;
}

void debounceB1_update()
{
	switch (actualB1State)
	{
		case BUTTON_UP:

					if ( BUTTON_menosTiempo_PRESSED )
					{
						actualB1State = BUTTON_FALLING;
					}
					break;

		case BUTTON_FALLING:

					if( delayRead(&delayAntiReboteB1) )
					{
						if (BUTTON_menosTiempo_PRESSED )
						{
							actualB1State = BUTTON_DOWN;
							changeState = 1;
						}
						else
						{
							actualB1State = BUTTON_UP;
						}
					}
					break;

		case BUTTON_DOWN:

					if ( !BUTTON_menosTiempo_PRESSED )
					{
						actualB1State = BUTTON_RAISING;
					}
					break;

		case BUTTON_RAISING:

					if( delayRead(&delayAntiReboteB1) )
					{
						if ( !BUTTON_menosTiempo_PRESSED )
						{
							actualB1State = BUTTON_UP;
						}
						else
						{
							actualB1State = BUTTON_DOWN;
						}
					}
					break;
		default:
					break;
	}
}

void debounceB2_update()
{
	switch (actualB2State)
	{
		case BUTTON_UP:

					if ( BUTTON_masTiempo_PRESSED )
					{
						actualB2State = BUTTON_FALLING;
					}
					break;

		case BUTTON_FALLING:

					if( delayRead(&delayAntiReboteB2) )
					{
						if (BUTTON_masTiempo_PRESSED )
						{
							actualB2State = BUTTON_DOWN;
							changeState = 2;
						}
						else
						{
							actualB2State = BUTTON_UP;
						}
					}
					break;

		case BUTTON_DOWN:

					if ( !BUTTON_masTiempo_PRESSED )
					{
						actualB2State = BUTTON_RAISING;
					}
					break;

		case BUTTON_RAISING:

					if( delayRead(&delayAntiReboteB2) )
					{
						if ( !BUTTON_masTiempo_PRESSED )
						{
							actualB2State = BUTTON_UP;
						}
						else
						{
							actualB2State = BUTTON_DOWN;
						}
					}
					break;
		default:
					break;
	}
}

void debounceB3_update()
{
	switch (actualB3State)
		{
			case BUTTON_UP:

						if ( BSP_PB_GetState(BUTTON_USER) )
						{
							actualB3State = BUTTON_FALLING;
						}
						break;

			case BUTTON_FALLING:

						if( delayRead(&delayAntiReboteB3) )
						{
							if (BSP_PB_GetState(BUTTON_USER) )
							{
								actualB3State = BUTTON_DOWN;
								changeState = 3;
							}
							else
							{
								actualB3State = BUTTON_UP;
							}
						}
						break;

			case BUTTON_DOWN:

						if ( !BSP_PB_GetState(BUTTON_USER) )
						{
							actualB3State = BUTTON_RAISING;
						}
						break;

			case BUTTON_RAISING:

						if( delayRead(&delayAntiReboteB3) )
						{
							if ( !BSP_PB_GetState(BUTTON_USER) )
							{
								actualB3State = BUTTON_UP;
							}
							else
							{
								actualB3State = BUTTON_DOWN;
							}
						}
						break;
			default:
						break;
		}
}

//Función: carga el estado inicial
//Entrada: ninguna
//Salida:  ninguna
//Nota: es una función pública porque se llama desde fuera del módulo (main)
void debounceFSM_init()
{
	delayInit(&delayAntiReboteB1, TIME_ANTIREBOTE);
	delayInit(&delayAntiReboteB2, TIME_ANTIREBOTE);
	delayInit(&delayAntiReboteB3, TIME_ANTIREBOTE);
	actualB1State = BUTTON_UP;
	actualB2State = BUTTON_UP;
	actualB3State = BUTTON_UP;
}

