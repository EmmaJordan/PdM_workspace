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

/*	Función: inicialización de conversor AD en un canal (A0 de placa Nucleo)
	Entrada: ninguna
	Salida: ninguna
	Nota: es una función pública porque se llama desde fuera del módulo (main) */
void myADC_init()
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
		printf("Error inicializacion ADC\r\n");
	}


	//##-2- Configure ADC regular channel ######################################
	sConfig.Channel      = ADC_CHANNEL_3;
	sConfig.Rank         = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	sConfig.Offset       = 0;

	if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
	{
		printf("Error configuracion ADC\r\n");
	}

	//##-3- Start the conversion process #######################################
	// Note: Considering IT occurring after each number of ADC conversions
	//       (IT by DMA end of transfer), select sampling time and ADC clock
	//       with sufficient duration to not create an overhead situation in
	//        IRQHandler.
	/*if(HAL_ADC_Start_DMA(&AdcHandle, (uint32_t*)&uhADCxConvertedValue, 1) != HAL_OK)
	{
		printf("Error inicializacion DMA\r\n");
	}*/
}

/*	Función: lectura del canal de ADC elegido en myADC_init(), en modo polling
 	siguiendo ejemplo ADC_RegularConversion_DMA de STM32Cube_FW_F4_V1.27.0
	Entrada: ninguna
	Salida: ninguna
	Nota: es una función pública porque se llama desde fuera del módulo (main) */
static uint32_t myADC_read()
{
	uint32_t valorLeidoADC;
	valorLeidoADC = HAL_ADC_GetValue(&AdcHandle);
	HAL_ADC_Start(&AdcHandle);
	HAL_ADC_PollForConversion(&AdcHandle,0xFFF);
	valorLeidoADC = HAL_ADC_GetValue(&AdcHandle);
	HAL_ADC_Stop(&AdcHandle);
	return valorLeidoADC;
}

#define MIN_LINEA 		200
#define MAX_LINEA 		240
#define AMPLITUD_LINEA 	250
#define ADC_RESOLUTION 	4095.0
static uint32_t lecturaADC = 0;
static uint8_t 	valorAnteriorADC =0;
static uint8_t 	valorADC = 0;
static bool_t error = 0;
/*	Función: actualización de lectura AD para mostrar Línea por terminal
	Entrada: ninguna
	Salida: error (0:ok, 1:bloqueo por problema de Línea)
	Nota: es una función privada porque se llama internamente en API_adc */
bool_t myADC_update()
{
	lecturaADC = ( myADC_read()+myADC_read()+myADC_read() ) / 3; 	//Promedio de 3 lecturas para disminuir oscilación
	valorADC   = ((float)lecturaADC/ADC_RESOLUTION)*AMPLITUD_LINEA;	//Escala Linea

	if(valorAnteriorADC != valorADC)
	{
		if(valorADC<MIN_LINEA)
		{
			printf("Tension de alimentacion insuficiente!\r\n");
			error = 1;
		}
		else if(valorADC>MAX_LINEA)
		{
			printf("Tension de alimentacion excedida!\r\n");
			error = 1;
		}
		else
		{
			printf("Linea = %dVca\r\n", valorADC);
			error = 0;
		}
	}
	valorAnteriorADC = valorADC; //Guarda valor anterior para evitar escrituras sucesivas iguales
	return error;
}

