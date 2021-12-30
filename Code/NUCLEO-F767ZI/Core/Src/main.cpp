/*
 * main.cpp
 *
 *  Created on: Dec 24, 2021
 *      Author: rkoppu
 */
#include <cstdint>
#include <cstring>
#include <cstdio>
#include "main.h"

UART_HandleTypeDef huart3;
#ifdef USE_UART_EXAMPLE
static char recv_data[64];
std::uint8_t cnt{0};
#endif // USE_UART_EXAMPLE

static void SystemClock_Config( void );
static void displayClkInfo( void );
static void UART3_Init( void );
static void Error_Handler( void );
#ifdef USE_UART_EXAMPLE
static inline char convert_to_Upper( char c );
#endif // USE_UART_EXAMPLE

int main( void )
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

#ifdef USE_HSE_EXAMPLE
	// Print current settings of clocks.
	displayClkInfo();
#endif // USE_HSE_EXAMPLE

	/* Configure the system clock */
	SystemClock_Config();

#ifdef USE_UART_EXAMPLE
	const char *pMsg = "Hello, how are you?\r";
	if ( HAL_UART_Transmit( &huart3, (const std::uint8_t *)pMsg, std::strlen(pMsg), HAL_MAX_DELAY ) != HAL_OK )
	{
		// Error in Transmission.
		Error_Handler();
	}

	HAL_UART_Receive_IT(&huart3, (std::uint8_t *)&recv_data[cnt], 1);
#endif // USE_UART_EXAMPLE

	// Print current settings of clocks.
	displayClkInfo();

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
void HAL_UART_RxCpltCallback( UART_HandleTypeDef *huart )
{
	if ( (recv_data[cnt] != '\r') && (cnt < ( sizeof(recv_data) / sizeof(recv_data[0]))) )
	{
		cnt++;
		HAL_UART_Receive_IT( &huart3, (std::uint8_t *)&recv_data[cnt], 1 );
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
void HAL_UART_TxCpltCallback( UART_HandleTypeDef *huart )
{

}

#endif // USE_UART_EXAMPLE

static void SystemClock_Config( void )
{
#ifdef USE_HSE_EXAMPLE
	// Configure the Clock Source.
	RCC_OscInitTypeDef Osc_init{0};
	Osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	Osc_init.HSEState = RCC_HSE_BYPASS;
	if ( HAL_RCC_OscConfig(&Osc_init) != HAL_OK )
	{
		// Error in Oscillator configuration.
		Error_Handler();
	}

	// Configure the various clocks.
	RCC_ClkInitTypeDef Clk_init{0};
	Clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	Clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	Clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2;
	Clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
	Clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
	if ( HAL_RCC_ClockConfig( &Clk_init, FLASH_LATENCY_0 ) != HAL_OK )
	{
		// Error in Clock configuration.
		Error_Handler();
	}

	// Disable HSI
	__HAL_RCC_HSI_DISABLE();

	// Configure SysTick with new clock settings.
	HAL_SYSTICK_CLKSourceConfig( SYSTICK_CLKSOURCE_HCLK );
	HAL_SYSTICK_Config( ( HAL_RCC_GetHCLKFreq() / 1000 ) );
#endif // USE_HSE_EXAMPLE
}

/* USART3 Initialization Function */
static void UART3_Init( void )
{
	std::memset( &huart3, 0, sizeof(huart3) );
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

	if (HAL_UART_Init( &huart3 ) != HAL_OK)
	{
		// Initialization Error.
		Error_Handler();
	}
}

#ifdef USE_UART_EXAMPLE
static inline char convert_to_Upper( char c )
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

static void displayClkInfo( void )
{
	char msg[1024];

	/* Configure the UART for debug console */
	UART3_Init();

	std::sprintf (msg, "SYSCLK:%luMHZ\r\n", ( HAL_RCC_GetSysClockFreq() / 1000000 ) );
	HAL_UART_Transmit( &huart3, (const std::uint8_t *)msg, std::strlen(msg), HAL_MAX_DELAY );
	std::sprintf( msg, "HCLK:%luMHZ\r\n", ( HAL_RCC_GetHCLKFreq() / 1000000 ) );
	HAL_UART_Transmit( &huart3, (const std::uint8_t *)msg, std::strlen(msg), HAL_MAX_DELAY );
	std::sprintf( msg, "PCLK1:%luMHZ\r\n", ( HAL_RCC_GetPCLK1Freq() / 1000000 ) );
	HAL_UART_Transmit( &huart3, (const std::uint8_t *)msg, std::strlen(msg), HAL_MAX_DELAY );
	std::sprintf( msg, "PCLK2:%luMHZ\r\n", ( HAL_RCC_GetPCLK2Freq() / 1000000 ) );
	HAL_UART_Transmit( &huart3, (const std::uint8_t *)msg, std::strlen(msg), HAL_MAX_DELAY );
}

