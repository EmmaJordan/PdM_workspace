/*
 * API_debounce.c
 *
 *  Created on: 29 mar. 2022
 *      Author: Win10
 */

#include "API_delay.h"
#include "API_debounce.h"


#define BUTTON_Disparo_PRESSED  	(GPIOC->IDR & (1<<13) )  //CESE
#define BUTTON_menosTiempo_PRESSED  (GPIOG->IDR & (1<<0)  )  //-Tiempo
#define BUTTON_masTiempo_PRESSED  	(GPIOG->IDR & (1<<1)  )  //+Tiempo
//Privada
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

#define TIME_ANTIREBOTE 40
static delay_t delayAntiRebote;
static debounceState_t actualState;
static bool_t PrivateGlobalVariable;

//Función: cambia estado de LED1
//Entrada: ninguna
//Salida: ninguna
void buttonPressed()
{
	//BSP_LED_Toggle(LED1);
	printf("Flanco de subida detectado\r\n");
}

//Función: cambia estado de LED3
//Entrada: ninguna
//Salida: ninguna
void buttonReleased()
{
	//BSP_LED_Toggle(LED3);
	printf("Flanco de bajada detectado\r\n");
}



//Función: lee las entradas, resuelve la lógica de transición de datos, actualiza las salidas
//Entrada: ninguna
//Salida: ninguna
//Nota: es una función pública porque se llama desde fuera del módulo (main)
static bool_t flancoDescendente = 0;
void debounceFSM_update()
{
	if ( BUTTON_menosTiempo_PRESSED )
	{
		BSP_LED_Toggle(LED1);
	}
	if ( BUTTON_masTiempo_PRESSED )
	{
		BSP_LED_Toggle(LED2);
	}
	if ( BUTTON_Disparo_PRESSED )
	{
		BSP_LED_Toggle(LED3);
	}
	/*switch (actualState)
	{
		case BUTTON_UP:

					if ( BUTTON_Disparo_PRESSED )
					{
						actualState = BUTTON_FALLING;
					}
					break;

		case BUTTON_FALLING:

					if( delayRead(&delayAntiRebote) )
					{
						if ( BUTTON_Disparo_PRESSED )
						{
							buttonPressed();
							flancoDescendente = 1;
							actualState = BUTTON_DOWN;
						}
						else
						{
							actualState = BUTTON_UP;
						}
					}
					break;

		case BUTTON_DOWN:

					if ( !BUTTON_Disparo_PRESSED )
					{
						actualState = BUTTON_RAISING;
					}
					break;

		case BUTTON_RAISING:

					if( delayRead(&delayAntiRebote) )
					{
						if ( !BUTTON_Disparo_PRESSED )
						{
							buttonReleased();
							actualState = BUTTON_UP;
						}
						else
						{
							actualState = BUTTON_DOWN;
						}
					}
					break;
		default:
					break;
	}*/
}

//Función: carga el estado inicial
//Entrada: ninguna
//Salida:  ninguna
//Nota: es una función pública porque se llama desde fuera del módulo (main)
void debounceFSM_init()
{
	delayInit(&delayAntiRebote, TIME_ANTIREBOTE);
	actualState = BUTTON_UP;
}

//Función: lectura del botón de usuario
//Entrada: ninguna
//Salida: booleano que avisa si se presionó (TRUE) o no (FALSE) el botón
bool_t readKey()
{
	PrivateGlobalVariable  = 0;
	if( flancoDescendente )
	{
		flancoDescendente = 0;
		PrivateGlobalVariable = 1;
	}
	return PrivateGlobalVariable;
}



int miLed1 = 0;
int miLed2 = 7;
int miLed2bis = 13;
int miLed3 = 1;
int miLed3bis = 14; //para que sea compatible con placa Nucleo CESE

uint8_t ON_1 = 0;
uint8_t ON_2 = 0;
uint8_t ON_3 = 0;

// Entrada: Número de led
// Salida: Ninguna
// Función: Cambio de estado de led de entrada
/*void miToggleLed(uint8_t led)
{
	if (led == 1)
	{
		if(ON_1==0)
		{
			ON_1=1;
			GPIOB->BSRR |= (1<<miLed1);
		}
		else if(ON_1==1)
		{
			ON_1=0;
			GPIOB->BSRR |= (1<<(16+miLed1));
		}
	}
	else if (led == 2) //led verde
	{
		if(ON_2==0)
		{
			ON_2=1;
			GPIOB->BSRR |= (1<<miLed2);
		}
		else if(ON_2==1)
		{
			ON_2=0;
			GPIOB->BSRR |= (1<<(16+miLed2));
		}
	}
	else if (led == 3) //led rojo
	{
		if(ON_3==0)
		{
			ON_3=1;
			GPIOB->BSRR |= (1<<miLed3);
			GPIOB->BSRR |= (1<<miLed3bis);
		}
		else if(ON_3==1)
		{
			ON_3=0;
			GPIOB->BSRR |= (1<<(16+miLed3));
			GPIOB->BSRR |= (1<<(16+miLed3bis));
		}
	}
}*/

