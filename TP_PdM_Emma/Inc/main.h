/**
  ******************************************************************************
  * @file    UART/UART_Printf/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#define PLACA_NUCLEO

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
#include <stm32f4xx_hal_adc.h>		//agregado Emma
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor USARTx/UARTx instance used and associated
   resources */
/* Definition for USARTx clock resources */

#ifdef PLACA_NUCLEO
	#define USARTx                           USART3
	#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
	#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
	#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

	#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
	#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

	/* Definition for USARTx Pins */
	#define USARTx_TX_PIN                    GPIO_PIN_8
	#define USARTx_TX_GPIO_PORT              GPIOD
	#define USARTx_TX_AF                     GPIO_AF7_USART3
	#define USARTx_RX_PIN                    GPIO_PIN_9
	#define USARTx_RX_GPIO_PORT              GPIOD
	#define USARTx_RX_AF                     GPIO_AF7_USART3
#else
	#define USARTx                           USART1
	#define USARTx_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE();
	#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
	#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

	#define USARTx_FORCE_RESET()             __HAL_RCC_USART1_FORCE_RESET()
	#define USARTx_RELEASE_RESET()           __HAL_RCC_USART1_RELEASE_RESET()

	/* Definition for USARTx Pins */
	#define USARTx_TX_PIN                    GPIO_PIN_9
	#define USARTx_TX_GPIO_PORT              GPIOA
	#define USARTx_TX_AF                     GPIO_AF7_USART1
	#define USARTx_RX_PIN                    GPIO_PIN_10
	#define USARTx_RX_GPIO_PORT              GPIOA
	#define USARTx_RX_AF                     GPIO_AF7_USART1
#endif

/* Definition for ADCx clock resources */
#ifdef PLACA_NUCLEO
	#define ADCx                            ADC1
	#define ADCx_CLK_ENABLE()               __HAL_RCC_ADC1_CLK_ENABLE()
	#define DMAx_CLK_ENABLE()               __HAL_RCC_DMA2_CLK_ENABLE()
	#define ADCx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()

	#define ADCx_FORCE_RESET()              __HAL_RCC_ADC_FORCE_RESET()
	#define ADCx_RELEASE_RESET()            __HAL_RCC_ADC_RELEASE_RESET()

	/* Definition for ADCx Channel Pin */
	#define ADCx_CHANNEL_PIN                GPIO_PIN_3
	#define ADCx_CHANNEL_GPIO_PORT          GPIOA

	/* Definition for ADCx's Channel */
	#define ADCx_CHANNEL                    ADC_CHANNEL_3

	/* Definition for ADCx's DMA */
	#define ADCx_DMA_CHANNEL                DMA_CHANNEL_0
	#define ADCx_DMA_STREAM                 DMA2_Stream0

	/* Definition for ADCx's NVIC */
	#define ADCx_DMA_IRQn                   DMA2_Stream0_IRQn
	#define ADCx_DMA_IRQHandler             DMA2_Stream0_IRQHandler
#else
	#define ADCx                            ADC1
	#define ADCx_CLK_ENABLE()               __HAL_RCC_ADC1_CLK_ENABLE()
	#define DMAx_CLK_ENABLE()               __HAL_RCC_DMA2_CLK_ENABLE()
	#define ADCx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()

	#define ADCx_FORCE_RESET()              __HAL_RCC_ADC_FORCE_RESET()
	#define ADCx_RELEASE_RESET()            __HAL_RCC_ADC_RELEASE_RESET()

	/* Definition for ADCx Channel Pin */
	#define ADCx_CHANNEL_PIN                GPIO_PIN_0
	#define ADCx_CHANNEL_GPIO_PORT          GPIOC

	/* Definition for ADCx's Channel */
	#define ADCx_CHANNEL                    ADC_CHANNEL_10

	/* Definition for ADCx's DMA */
	#define ADCx_DMA_CHANNEL                DMA_CHANNEL_0
	#define ADCx_DMA_STREAM                 DMA2_Stream0

	/* Definition for ADCx's NVIC */
	#define ADCx_DMA_IRQn                   DMA2_Stream0_IRQn
	#define ADCx_DMA_IRQHandler             DMA2_Stream0_IRQHandler
#endif
void inputsInit();

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
