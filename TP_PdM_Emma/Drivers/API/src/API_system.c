/*
 * API_system.c
 *
 *  Created on: 23 abr. 2022
 *      Author: Win10
 */


#include "API_system.h"
#include "API_debounce.h"
#include "API_adc.h"

#define menosTiempo_PRESSED  (GPIOG->IDR & (1<<1) )  //-Tiempo
#define masTiempo_PRESSED  	 (GPIOG->IDR & (1<<0) )  //+Tiempo

typedef enum{
	s_rest,
	s_decreaseTime,
	s_increaseTime,
	s_alarm,
	s_Rx,
} debounceState_t;

static bool_t error = 0;
static uint8_t state = 0;
static uint16_t tiempoDisparo = 100;
debounceState_t mainState = s_rest;

void mainFSM_update()
{
	switch (mainState)
	{
		case s_rest:

				error = myADC_update();
				if(error==0)
				{
					state = debounceFSM_update();
					if(state==0) 		mainState = s_rest;
					else if(state==1) 	mainState = s_decreaseTime;
					else if(state==2)	mainState = s_increaseTime;
					else if(state==3)   mainState = s_Rx;
				}
				else mainState = s_alarm;
				break;

		case s_decreaseTime:

				decreaseTime();
				mainState = s_rest;
				break;

		case s_increaseTime:

				increaseTime();
				mainState = s_rest;
				break;

		case s_alarm:

				error = myADC_update();
				if(error==0) mainState = s_rest;
				break;

		case s_Rx:

				applyRx();
				mainState = s_rest;
				break;
	}
}

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

//Función: disminuye tiempo de Disparo de RX
//Entrada: ninguna
//Salida: ninguna
void decreaseTime()
{
	BSP_LED_On(LED1);
	if(tiempoDisparo>100) tiempoDisparo = tiempoDisparo-100;
	printf("Tiempo de disparo = %dms\r\n",tiempoDisparo);
	while(menosTiempo_PRESSED);
	BSP_LED_Off(LED1);
	HAL_Delay(100);
}

//Función: aumenta tiempo de Disparo de RX
//Entrada: ninguna
//Salida: ninguna
void increaseTime()
{
	BSP_LED_On(LED2);
	if(tiempoDisparo<3000) tiempoDisparo = tiempoDisparo+100;
	printf("Tiempo de disparo = %dms\r\n",tiempoDisparo);
	while(masTiempo_PRESSED);
	BSP_LED_Off(LED2);
	HAL_Delay(100);
}

//Función: ejecución de Disparo de RX, durante el tiempo configurado
//Entrada: ninguna
//Salida: ninguna
void applyRx()
{
	printf("Disparo ON\r\n");
	BSP_LED_On(LED3);
	HAL_Delay(tiempoDisparo);
	BSP_LED_Off(LED3);
	printf("Disparo OFF\r\n");
	while(BSP_PB_GetState(BUTTON_USER)); //espera a que suelte disparo
	HAL_Delay(200);
}
