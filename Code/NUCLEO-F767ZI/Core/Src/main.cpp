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

	const char *pMsg = "Hello, how are you?\r";
	if ( HAL_UART_Transmit( &huart3, (const std::uint8_t *)pMsg, std::strlen(pMsg), HAL_MAX_DELAY ) != HAL_OK )
	{
		// Error in Transmission.
		Error_Handler();
	}

	char recv_data[64]{0};
	std::uint8_t cnt{0};
	for ( ; cnt < ( sizeof(recv_data) / sizeof(recv_data[0]) ); cnt++)
	{
		if ( HAL_UART_Receive(&huart3, (std::uint8_t *)&recv_data[cnt], 1, HAL_MAX_DELAY) != HAL_OK )
		{
			// Error in Reception.
			Error_Handler();
		}
		else
		{
			recv_data[cnt] = convert_to_Upper( recv_data[cnt] );
		}

		if (recv_data[cnt] == '\r')
		{
			break;
		}
	}
	cnt++;
	recv_data[cnt] = '\n';

	if ( HAL_UART_Transmit( &huart3, (const std::uint8_t *)recv_data, cnt, HAL_MAX_DELAY ) != HAL_OK )
	{
		// Error in Transmission.
		Error_Handler();
	}

	while(true)
	{

	}

	return 0;
}

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

static inline char convert_to_Upper(char c)
{
	char retVal{c};

	if ( (c >= 'a') && (c <= 'z') )
	{
		retVal -= ('a' - 'A');
	}

	return retVal;
}

static void Error_Handler( void )
{
	for (;;);
}