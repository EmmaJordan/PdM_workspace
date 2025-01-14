/*
 * API_delay.c
 *
 *  Created on: 22 mar. 2022
 *      Author: Win10
 */

#include "API_delay.h"

int miLed1 = 0;
int miLed2 = 7;
int miLed2bis = 13;
int miLed3 = 1;
int miLed3bis = 14; //para que sea compatible con placa Nucleo CESE

uint8_t ON_1 = 0;
uint8_t ON_2 = 0;
uint8_t ON_3 = 0;


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

// Entrada: Número de led
// Salida: Ninguna
// Función: Cambio de estado de led de entrada
void miToggleLed(uint8_t led)
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
}

// Entrada: Ninguna
// Salida: Ninguna
// Función: Inicialización de los leds de mi placa (diferente a Nucleo)
void misLeds_Init()
{
	RCC->AHB1ENR |= (1<<0); //Habilita puerto A <-- para user Button PA0
	RCC->AHB1ENR |= (1<<1); //Habilita puerto B <-- para leds externos
	RCC->AHB1ENR |= (1<<6); //Habilita puerto G <-- para leds 3 y 4 (PG13 y PG14)

	GPIOA->MODER   &=~ (3<<0);   			//00 --> entrada
	GPIOA->PUPDR   &=~ (1<<0);				//10 --> pull down
	GPIOA->PUPDR   |=  (1<<1);

	GPIOB->MODER   &=~ (1<<(miLed1*2+1));
	GPIOB->MODER   |=  (1<<miLed1*2);
	GPIOB->OTYPER  &=~ (1<<miLed1);
	GPIOB->OSPEEDR &=~ (3<<miLed1*3);
	GPIOB->PUPDR   &=~ (3<<miLed1*3);

	GPIOB->MODER   &=~ (1<<(miLed2*2+1));
	GPIOB->MODER   |=  (1<<miLed2*2);
	GPIOB->OTYPER  &=~ (1<<miLed2);
	GPIOB->OSPEEDR &=~ (3<<miLed2*2);
	GPIOB->PUPDR   &=~ (3<<miLed2*2);

	GPIOG->MODER   &=~ (1<<(miLed2bis*2+1));
	GPIOG->MODER   |=  (1<<miLed2bis*2);
	GPIOG->OTYPER  &=~ (1<<miLed2bis);
	GPIOG->OSPEEDR &=~ (3<<miLed2bis*2);
	GPIOG->PUPDR   &=~ (3<<miLed2bis*2);

	GPIOB->MODER   &=~ (1<<(miLed3*2+1));
	GPIOB->MODER   |=  (1<<miLed3*2);
	GPIOB->OTYPER  &=~ (1<<miLed3);
	GPIOB->OSPEEDR &=~ (3<<miLed3*2);
	GPIOB->PUPDR   &=~ (3<<miLed3*2);

	GPIOB->MODER   &=~ (1<<(miLed3bis*2+1));
	GPIOB->MODER   |=  (1<<miLed3bis*2);
	GPIOB->OTYPER  &=~ (1<<miLed3bis);
	GPIOB->OSPEEDR &=~ (3<<miLed3bis*2);
	GPIOB->PUPDR   &=~ (3<<miLed3bis*2);
}



