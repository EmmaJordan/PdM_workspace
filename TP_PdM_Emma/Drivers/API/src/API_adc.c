/*
 * API_adc.c
 *
 *  Created on: 22 abr. 2022
 *      Author: Win10
 */


#include "API_adc.h"

/* ADC handler declaration */
ADC_HandleTypeDef    AdcHandle;

/* Variable used to get converted value */
__IO uint16_t uhADCxConvertedValue = 0;

void iniciaADC()
{
	ADC_ChannelConfTypeDef sConfig;

	//##-1- Configure the ADC peripheral #######################################
	AdcHandle.Instance                   = ADC1;
	AdcHandle.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV2;
	AdcHandle.Init.Resolution            = ADC_RESOLUTION12b;
	AdcHandle.Init.ScanConvMode          = DISABLE;                       // Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1)
	AdcHandle.Init.ContinuousConvMode    = ENABLE;                        // Continuous mode disabled to have only 1 conversion at each conversion trig
	AdcHandle.Init.DiscontinuousConvMode = DISABLE;                       // Parameter discarded because sequencer is disabled
	AdcHandle.Init.NbrOfDiscConversion   = 0;
	AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;        // Conversion start trigged at each external event
	AdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;
	AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
	AdcHandle.Init.NbrOfConversion       = 1;
	AdcHandle.Init.DMAContinuousRequests = ENABLE;
	AdcHandle.Init.EOCSelection          = DISABLE;

	if (HAL_ADC_Init(&AdcHandle) != HAL_OK)
	{
		// ADC initialization Error
		//Error_Handler();
	}

	//printf("HAL_ADC_Init OK\r\n");

	//##-2- Configure ADC regular channel ######################################
	sConfig.Channel      = ADC_CHANNEL_3;
	sConfig.Rank         = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	sConfig.Offset       = 0;

	if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
	{
		//Channel Configuration Error
		//Error_Handler();
	}

	//printf("HAL_ADC_ConfigChannel OK\r\n");

	//##-3- Start the conversion process #######################################
	// Note: Considering IT occurring after each number of ADC conversions
	//       (IT by DMA end of transfer), select sampling time and ADC clock
	//       with sufficient duration to not create an overhead situation in
	//        IRQHandler.
	//if(HAL_ADC_Start_DMA(&AdcHandle, (uint32_t*)&uhADCxConvertedValue, 1) != HAL_OK)
	//{
		 //Start Conversation Error
		//Error_Handler();
	//}
	//printf("HAL_ADC_Start_DMA OK\r\n");
}

uint32_t myADCread()
{
	uint32_t valorLeidoADC;
	valorLeidoADC = HAL_ADC_GetValue(&AdcHandle);
	HAL_ADC_Start(&AdcHandle);
	HAL_ADC_PollForConversion(&AdcHandle,0xFFF);
	valorLeidoADC = HAL_ADC_GetValue(&AdcHandle);
	HAL_ADC_Stop(&AdcHandle);
	return valorLeidoADC;
}
