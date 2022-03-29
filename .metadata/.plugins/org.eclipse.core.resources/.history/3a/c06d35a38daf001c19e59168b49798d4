 /**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/main.c
  * @author  MCD Application Team
  * @brief   This example shows how to retarget the C library printf function
  *          to the UART.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_delay.h"
/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup UART_Printf
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

#define Led_1    0
#define Led_2    7
#define Led_3 	 1
#define Led_3bis 14

#define TIME_ANTIREBOTE 40

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

debounceState_t actualState;
delay_t delayAntiRebote;

void debounceFSM_init();	// debe cargar el estado inicial o reiniciar en caso de error
void debounceFSM_update();	// debe leer las entradas, resolver la lógica de transición de
							// estados y actualizar las salidas (llamado periódico)
void buttonPressed();		// debe togglear el LED1
void buttonReleased();		// debe togglear el LED3


int main(void)
{
   /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user
         can eventually implement his proper time base source (a general purpose
         timer for example or other time source), keeping in mind that Time base
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
    HAL_Init();

    /* Configure the system clock to 180 MHz */
    SystemClock_Config();

    /* Initialize Inputs */
    inputsInit();


    tick_t  timeAntiRebote = TIME_ANTIREBOTE;
    delayInit(&delayAntiRebote, timeAntiRebote);

    debounceFSM_init();

	while (1)
	{
		debounceFSM_update();
	}
}



#define BUTTON_PRESSED  (GPIOA->IDR & (1<<0) ) //EMMA
//#define BUTTON_PRESSED  (GPIOC->IDR & (1<<13) ) //CESE

//Función: lee las entradas, resuelve la lógica de transición de datos, actualiza las salidas
//Entrada: ninguna
//Salida: ninguna
void debounceFSM_update()
{
	switch (actualState)
	{
		case BUTTON_UP:

					if (BUTTON_PRESSED)
					{
						actualState = BUTTON_FALLING;
					}
					break;

		case BUTTON_FALLING:

					if( delayRead(&delayAntiRebote) )
					{
						HAL_Delay(40);
						if (BUTTON_PRESSED)
						{
							buttonPressed();
							actualState = BUTTON_DOWN;
						}
						else
						{
							actualState = BUTTON_UP;
						}
					}
					break;

		case BUTTON_DOWN:

					if (!BUTTON_PRESSED)
					{
						actualState = BUTTON_RAISING;
					}
					break;

		case BUTTON_RAISING:

					if( delayRead(&delayAntiRebote) )
					{
						if (!BUTTON_PRESSED)
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
	}
}

//Función: carga el estado inicial
//Entrada: ninguna
//Salida:  ninguna
void debounceFSM_init()
{
	actualState = BUTTON_UP;
}

//Función: cambia estado de LED1
//Entrada: ninguna
//Salida: ninguna
void buttonPressed()
{
	miToggleLed(1);
}

//Función: cambia estado de LED3
//Entrada: ninguna
//Salida: ninguna
void buttonReleased()
{
	miToggleLed(3);
}




/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/*
 * uint8_t ON_OFF = 0;
uint8_t start = 0;
uint32_t tickstart = 0;
void mi_Delay_NO_bloqueante(uint32_t Delay)
{
	uint32_t wait = Delay;
	if (wait < HAL_MAX_DELAY)
	{
		wait += (uint32_t)(uwTickFreq);
	}


	//TOMA INSTANTE MS INICIAL
	if(start==0)
	{
		start = 1;
		tickstart = HAL_GetTick(); //devuelve uwTick actual
	}
	else if(start==1)
	{
		if((HAL_GetTick() - tickstart) == wait)
		{
			start = 0;
			if(ON_OFF==0)
			{
				ON_OFF=1;
				GPIOG->BSRR |= (1<<ledVERDE);
				GPIOG->BSRR |= (1<<(16+ledROJO));
			}
			else if(ON_OFF==1)
			{
				ON_OFF=0;
				GPIOG->BSRR |= (1<<ledROJO);
				GPIOG->BSRR |= (1<<(16+ledVERDE));
			}
		}
	}
}
 * */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
