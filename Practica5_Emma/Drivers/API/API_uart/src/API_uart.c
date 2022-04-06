/*
 * API_uart.c
 *
 *  Created on: 5 abr. 2022
 *      Author: Win10
 */

#include "API_uart.h"

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/*
 	 Función: inicialización de la UART
 	 Entradas: ninguna
 	 Salida: booleando TRUE si se inicializó correctamente, FALSE si falló
*/
#define myBaudRate 9600
#define UARTn 3
bool_t uartinit()
{
	UartHandle.Instance        = USART1;
	UartHandle.Init.BaudRate   = myBaudRate;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_ODD;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&UartHandle) != HAL_OK)
	{
		/* Initialization Error */
		//Error_Handler();
		printf("Error en la inicializacion de la UART\n\r");
		return false;
	}
	printf("UART inicializada correctamente\n\r");
	printf("Parametros de configuracion:\n\r");
	printf("Instancia: USART%d\n\r",UARTn);
	printf("Baudrate: %d\n\r",myBaudRate);

	return true;
}

/*
	Función: envía un mensaje por la UART configurada, completo (hasta el caracter ‘\0’)
	Entradas: *pstring puntero de mensaje a enviar
	Salida: ninguna
*/
void uartsendString(uint8_t *pstring) {
	uint16_t size = (uint16_t) strlen((const char*) pstring);
	HAL_StatusTypeDef ret = HAL_UART_Transmit(&UartHandle, pstring, size, 0xFFFF);

	if (ret == HAL_ERROR)
	{
		printf("Error de transmision de la UART");
	}
}

/*
	Función: envía un mensaje por la UART configurada, limitado por tamaño
	Entradas 1: *pstring puntero de mensaje a enviar, size tamaño del mensaje a enviar
	Salida: ninguna
*/
void uartSendStringSize(uint8_t *pstring, uint16_t size)
{
	HAL_StatusTypeDef ret = HAL_UART_Transmit(&UartHandle, pstring, size, 0xFFF);

	if (ret == HAL_ERROR)
	{
		printf("Error de transmision de la UART");
	}
}


/*
	Función: recibe un mensaje por la UART configurada
	Entradas: *pstring mensaje a enviar, size tamaño del mensaje a enviar
	Salida: ninguna
*/
void uartReceiveStringSize(uint8_t *pstring, uint16_t size) {
	HAL_StatusTypeDef ret = HAL_UART_Receive(&UartHandle, pstring, size, 0xFFF);
	if (ret == HAL_ERROR)
	{
		printf("Error de recepcion de mensaje de la UART");
	}
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  // Place your implementation of fputc here
  // e.g. write a character to the USART3 and Loop until the end of transmission
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}
