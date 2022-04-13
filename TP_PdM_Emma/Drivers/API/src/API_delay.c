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


int miLD1 = 0;
int miLD2 = 7;
int miLD2bis = 13;
int miLD3 = 1;
int miLD3bis = 14;

// Entrada: Ninguna
// Salida: Ninguna
// Función: Inicialización de los leds de mi placa (diferente a Nucleo)
void inputsInit()
{
	RCC->AHB1ENR |= (1<<0); //Habilita puerto A <-- para user Button PA0 (EMMA)
	RCC->AHB1ENR |= (1<<1); //Habilita puerto B <-- para leds externos
	RCC->AHB1ENR |= (1<<2); //Habilita puerto C <-- para user Button PC13 (CESE)
	RCC->AHB1ENR |= (1<<6); //Habilita puerto G <-- para leds 3 y 4 (PG13 y PG14)

	GPIOA->MODER   &=~ (3<<0);   			//00 --> entrada
	GPIOA->PUPDR   &=~ (1<<0);				//10 --> pull down
	GPIOA->PUPDR   |=  (1<<1);

	GPIOC->MODER   &=~ (3<<0);   			//00 --> entrada
	GPIOC->PUPDR   &=~ (1<<0);				//10 --> pull down
	GPIOC->PUPDR   |=  (1<<1);

	GPIOB->MODER   &=~ (1<<(miLD1*2+1));
	GPIOB->MODER   |=  (1<<miLD1*2);
	GPIOB->OTYPER  &=~ (1<<miLD1);
	GPIOB->OSPEEDR &=~ (3<<miLD1*3);
	GPIOB->PUPDR   &=~ (3<<miLD1*3);

	GPIOB->MODER   &=~ (1<<(miLD2*2+1));
	GPIOB->MODER   |=  (1<<miLD2*2);
	GPIOB->OTYPER  &=~ (1<<miLD2);
	GPIOB->OSPEEDR &=~ (3<<miLD2*2);
	GPIOB->PUPDR   &=~ (3<<miLD2*2);

	GPIOG->MODER   &=~ (1<<(miLD2bis*2+1));
	GPIOG->MODER   |=  (1<<miLD2bis*2);
	GPIOG->OTYPER  &=~ (1<<miLD2bis);
	GPIOG->OSPEEDR &=~ (3<<miLD2bis*2);
	GPIOG->PUPDR   &=~ (3<<miLD2bis*2);

	GPIOB->MODER   &=~ (1<<(miLD3*2+1));
	GPIOB->MODER   |=  (1<<miLD3*2);
	GPIOB->OTYPER  &=~ (1<<miLD3);
	GPIOB->OSPEEDR &=~ (3<<miLD3*2);
	GPIOB->PUPDR   &=~ (3<<miLD3*2);

	GPIOB->MODER   &=~ (1<<(miLD3bis*2+1));
	GPIOB->MODER   |=  (1<<miLD3bis*2);
	GPIOB->OTYPER  &=~ (1<<miLD3bis);
	GPIOB->OSPEEDR &=~ (3<<miLD3bis*2);
	GPIOB->PUPDR   &=~ (3<<miLD3bis*2);
}



