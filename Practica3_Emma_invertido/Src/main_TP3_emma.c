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
static delay_t delay1;
static delay_t delay2;
static delay_t delay3;

tick_t tON  = 200;
tick_t tOFF = 400;

void iniciaSecuencia1(void);
void iniciaSecuencia2(void);
void checkUserButton();

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

    /* Initialize BSP Led for LED2 */
    misLeds_Init();

    delayInit(&delay1, 1);
	delayInit(&delay2, tON+1);
	delayInit(&delay3, tOFF+1);

	while (1)
	{
		checkUserButton();

		if(delayRead(&delay1))
		{
			miToggleLed(1);
			if(delay1.duration==tON) 	delayWrite(&delay1,tOFF);
			else 						delayWrite(&delay1,tON);
		}
		if(delayRead(&delay2))
		{
			miToggleLed(2);
			if(delay2.duration==tON) 	delayWrite(&delay2,tOFF);
			else 						delayWrite(&delay2,tON);
		}
		if(delayRead(&delay3))
		{
			miToggleLed(3);
			if(delay3.duration==tON) 	delayWrite(&delay3,tOFF);
			else						delayWrite(&delay3,tON);
		}
	}
}


bool_t secuencia1 = 0;
bool_t secuencia2 = 0;

void iniciaSecuencia1(void)
{
	secuencia1 = 1;
	secuencia2 = 0;

	GPIOB->BSRR |= (1<<(16+0));
	GPIOB->BSRR |= (1<<(16+7));
	GPIOB->BSRR |= (1<<(16+1));
	GPIOB->BSRR |= (1<<(16+14));

	GPIOG->BSRR |= (1<<13);
	HAL_Delay(500);
	GPIOG->BSRR |= (1<<(16+13));

	delayInit(&delay1, 1);
	delayInit(&delay2, tON+1);
	delayInit(&delay3, tOFF+1);
}

void iniciaSecuencia2(void)
{
	secuencia2 = 1;
	secuencia1 = 0;

	GPIOB->BSRR |= (1<<(16+0));
	GPIOB->BSRR |= (1<<(16+7));
	GPIOB->BSRR |= (1<<(16+1));
	GPIOB->BSRR |= (1<<(16+14));

	GPIOG->BSRR |= (1<<13);
	HAL_Delay(500);
	GPIOG->BSRR |= (1<<(16+13));

	delayInit(&delay3, 1);
	delayInit(&delay2, tON+1);
	delayInit(&delay1, tOFF+1);
}

void checkUserButton()
{
	if( (GPIOA->IDR & (1<<0)) )
	{
		HAL_Delay(10);
		if( (GPIOA->IDR & (1<<0)) )
		{
			if ( secuencia1==0 ) iniciaSecuencia1();
		}
	}
	else if( !(GPIOA->IDR & (1<<0)) )
	{
		HAL_Delay(10);
		if( !(GPIOA->IDR & (1<<0)) )
		{
			if ( secuencia2==0 ) iniciaSecuencia2();
		}
	}
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
