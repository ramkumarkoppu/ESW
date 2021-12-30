/*
 * main.cpp
 *
 *  Created on: Dec 24, 2021
 *      Author: rkoppu
 */
#include <cstdint>
#include <cstring>
#include "main.h"

UART_HandleTypeDef huart3;

static char recv_data[64];
std::uint8_t cnt{0};

static void SystemClock_Config( void );
static void UART3_Init( void );
static void Error_Handler( void );
static inline char convert_to_Upper(char c);

int main( void )
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Configure the UART for debug console */
	UART3_Init();

#ifdef USE_UART_EXAMPLE
	const char *pMsg = "Hello, how are you?\r";
	if ( HAL_UART_Transmit( &huart3, (const std::uint8_t *)pMsg, std::strlen(pMsg), HAL_MAX_DELAY ) != HAL_OK )
	{
		// Error in Transmission.
		Error_Handler();
	}

	HAL_UART_Receive_IT(&huart3, (std::uint8_t *)&recv_data[cnt], 1);
#endif // USE_UART_EXAMPLE

	while(true)
	{

	}

	return 0;
}

#ifdef USE_UART_EXAMPLE
/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if ( (recv_data[cnt] != '\r') && (cnt < ( sizeof(recv_data) / sizeof(recv_data[0]))) )
	{
		cnt++;
		HAL_UART_Receive_IT(&huart3, (std::uint8_t *)&recv_data[cnt], 1);
	}
	else
	{
		for (std::uint8_t i{0}; i < cnt; i++)
		{
			recv_data[i] = convert_to_Upper( recv_data[i] );
		}
		cnt++;
		recv_data[cnt] = '\n';

		if ( HAL_UART_Transmit_IT( &huart3, (const std::uint8_t *)recv_data, cnt) != HAL_OK )
		{
			// Error in Transmission.
			Error_Handler();
		}
	}
}

/**
  * @brief  Tx Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

}

#endif // USE_UART_EXAMPLE

static void SystemClock_Config( void )
{

}

/* USART3 Initialization Function */
static void UART3_Init( void )
{
	/* UART High level initilization */
	huart3.Instance = USART3;

	huart3.Init.BaudRate = 115200U;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;

	huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	if (HAL_UART_Init(&huart3) != HAL_OK)
	{
		// Initialization Error.
		Error_Handler();
	}
}

#ifdef USE_UART_EXAMPLE
static inline char convert_to_Upper(char c)
{
	char retVal{c};

	if ( (c >= 'a') && (c <= 'z') )
	{
		retVal -= ('a' - 'A');
	}

	return retVal;
}
#endif // USE_UART_EXAMPLE

static void Error_Handler( void )
{
	for (;;);
}
