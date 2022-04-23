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

// Entrada: Ninguna
// Salida: Ninguna
// Función: Inicialización de los leds de mi placa (diferente a Nucleo)
void inputsInit()
{
	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	/* Initialize Button for -Time & +Time */
	RCC->AHB1ENR |= (1<<6); //Habilita puerto G

	//PG0 -Time
	GPIOG->MODER &=~ (3<<0);   			//00 --> entrada
	GPIOG->PUPDR &=~ (1<<0);			//10 --> pull down
	GPIOG->PUPDR |=  (1<<1);

	//PG1 +Time
	GPIOG->MODER &=~ (3<<2);   			//00 --> entrada
	GPIOG->PUPDR &=~ (1<<2);			//10 --> pull down
	GPIOG->PUPDR |=  (1<<3);
}

#define pinBuzzer 2
void outputsInit()
{
	/* Initialize BSP Led for LED1 */
	BSP_LED_Init(LED1);
	/* Initialize BSP Led for LED2 */
	BSP_LED_Init(LED2);
	/* Initialize BSP Led for LED1 */
	BSP_LED_Init(LED3);
	/* Initialize Buzzer */
	RCC->AHB1ENR   |=  (1<<4); //Habilita puerto E <-- para PE2 (buzzer)
	GPIOE->MODER   &=~ (1<<(pinBuzzer*2+1));
	GPIOE->MODER   |=  (1<<pinBuzzer*2);
	GPIOE->OTYPER  &=~ (1<<pinBuzzer);
	GPIOE->OSPEEDR &=~ (3<<pinBuzzer*3);
	GPIOE->PUPDR   &=~ (3<<pinBuzzer*3);
}


