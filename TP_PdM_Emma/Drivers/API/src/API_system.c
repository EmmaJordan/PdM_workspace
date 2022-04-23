/*
 * API_system.c
 *
 *  Created on: 23 abr. 2022
 *      Author: Win10
 */


#include "API_system.h"

// Entrada: Ninguna
// Salida: Ninguna
// Función: Inicialización de las entradas del Sistema
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

// Entrada: Ninguna
// Salida: Ninguna
// Función: Inicialización de las salidas del Sistema
void outputsInit()
{
	/* Initialize BSP Led for LED1 */
	BSP_LED_Init(LED1);
	/* Initialize BSP Led for LED2 */
	BSP_LED_Init(LED2);
	/* Initialize BSP Led for LED1 */
	BSP_LED_Init(LED3);
	/* Initialize Buzzer */
	RCC->AHB1ENR   |=  (1<<4); //Habilita puerto E <-- para PE2 (buzzer) y PE4 (Rx)
	GPIOE->MODER   &=~ (1<<(pinBuzzer*2+1));
	GPIOE->MODER   |=  (1<<pinBuzzer*2);
	GPIOE->OTYPER  &=~ (1<<pinBuzzer);
	GPIOE->OSPEEDR &=~ (3<<pinBuzzer*3);
	GPIOE->PUPDR   &=~ (3<<pinBuzzer*3);
	/* Initialize Disparo Rx */
	GPIOE->MODER   &=~ (1<<(pinRx*2+1));
	GPIOE->MODER   |=  (1<<pinRx*2);
	GPIOE->OTYPER  &=~ (1<<pinRx);
	GPIOE->OSPEEDR &=~ (3<<pinRx*3);
	GPIOE->PUPDR   &=~ (3<<pinRx*3);
}
