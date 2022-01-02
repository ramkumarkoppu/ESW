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

#ifdef USE_UART_EXAMPLE
UART_HandleTypeDef huart3;
//static char recv_data[64];
//std::uint8_t cnt{0};
#endif // USE_UART_EXAMPLE

#ifdef USE_BASIC_TIMER_EXAMPLE
TIM_HandleTypeDef hTimer6;
#endif // USE_BASIC_TIMER_EXAMPLE

#ifdef USE_INPUT_CAPTURE_TIMER_EXAMPLE
TIM_HandleTypeDef hTimer2;
static volatile std::uint32_t TIM_cnts[2];
std::uint8_t capture_idx;
bool capture_completed;
#endif // USE_INPUT_CAPTURE_TIMER_EXAMPLE

#ifdef USE_BASIC_TIMER_EXAMPLE
static void TIM6_init( void );
static void LED_init( void );
#endif // USE_BASIC_TIMER_EXAMPLE

#ifdef USE_INPUT_CAPTURE_TIMER_EXAMPLE
static void TIM2_init( void );
static void SystemClock_Config( void );
static void LSE_config( void );
static void displayUserSigInfo( void );
#endif // USE_INPUT_CAPTURE_TIMER_EXAMPLE

#if defined( USE_HSE_EXAMPLE ) || defined( USE_PLL_EXAMPLE )
static void SystemClock_Config( void );
static void displayClkInfo( void );
#endif

#if defined( USE_HSE_EXAMPLE ) || defined( USE_PLL_EXAMPLE ) || defined( USE_UART_EXAMPLE )
static void UART3_Init( void );
#endif // USE_HSE_EXAMPLE or USE_PLL_EXAMPLE or USE_UART_EXAMPLE

static void Error_Handler( void );
#ifdef USE_UART_EXAMPLE
//static inline char convert_to_Upper( char c );
#endif // USE_UART_EXAMPLE

int main( void )
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

#if defined( USE_HSE_EXAMPLE ) || defined( USE_PLL_EXAMPLE )
	// Print current settings of clocks.
	displayClkInfo();

	/* Configure the system clock */
	SystemClock_Config();
#endif // USE_HSE_EXAMPLE or USE_PLL_EXAMPLE

#ifdef USE_UART_EXAMPLE
#if 0
	const char *pMsg = "Hello, how are you?\r";
	if ( HAL_UART_Transmit( &huart3, (const std::uint8_t *)pMsg, std::strlen(pMsg), HAL_MAX_DELAY ) != HAL_OK )
	{
		// Error in Transmission.
		Error_Handler();
	}

	HAL_UART_Receive_IT(&huart3, (std::uint8_t *)&recv_data[cnt], 1);
#endif
#endif // USE_UART_EXAMPLE

#ifdef USE_INPUT_CAPTURE_TIMER_EXAMPLE
	SystemClock_Config();
#endif // USE_INPUT_CAPTURE_TIMER_EXAMPLE

#if defined( USE_HSE_EXAMPLE ) || defined( USE_PLL_EXAMPLE )
	// Print current settings of clocks.
	displayClkInfo();
#endif // USE_HSE_EXAMPLE or USE_PLL_EXAMPLE

#ifdef USE_BASIC_TIMER_EXAMPLE
	// Initialize the Timer.
	TIM6_init();
	// Initialize the LED.
	LED_init();
	// Set initial state to low.
	HAL_GPIO_WritePin( GPIOB, GPIO_PIN_7, GPIO_PIN_RESET );
	// Start the Timer.
	HAL_TIM_Base_Start_IT( &hTimer6 );
#endif // USE_BASIC_TIMER_EXAMPLE

#ifdef USE_INPUT_CAPTURE_TIMER_EXAMPLE
	TIM2_init();
	LSE_config();
	HAL_TIM_IC_Start_IT( &hTimer2, TIM_CHANNEL_1 );
#endif // USE_INPUT_CAPTURE_TIMER_EXAMPLE

	while(true)
	{
		if (capture_completed)
		{
			displayUserSigInfo();
			capture_completed = false;
		}
	}

	return 0;
}

#ifdef USE_UART_EXAMPLE
/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
#if 0
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

#endif

#endif // USE_UART_EXAMPLE

#ifdef USE_BASIC_TIMER_EXAMPLE
extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// Toggle LED only if Timer 6 update flag is received.
	HAL_GPIO_TogglePin( GPIOB, GPIO_PIN_7 );
}
#endif // USE_BASIC_TIMER_EXAMPLE

#if defined( USE_HSE_EXAMPLE ) || defined( USE_PLL_EXAMPLE )
#if 0
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

#ifdef USE_PLL_EXAMPLE
	// Configure the Clock Source.
	RCC_OscInitTypeDef Osc_init{0};
//	Osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
//	Osc_init.HSIState = RCC_HSI_ON;
//	Osc_init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
//	Osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;
//	Osc_init.PLL.PLLState = RCC_PLL_ON;
	/* Configure PLL to generate 50MHz clock for SYSCLK. */
//	Osc_init.PLL.PLLM = 16;
//	Osc_init.PLL.PLLN = 100;
//	Osc_init.PLL.PLLP = RCC_PLLP_DIV2;
	/* End of 50Mhz specific configuration */
	/* Configure PLL to generate 84MHz clock for SYSCLK. */
//	Osc_init.PLL.PLLM = 16;
//	Osc_init.PLL.PLLN = 168;
//	Osc_init.PLL.PLLP = RCC_PLLP_DIV2;
	/* End of 84Mhz specific configuration */
	/* Configure PLL to generate 120MHz clock for SYSCLK. */
//	Osc_init.PLL.PLLM = 16;
//	Osc_init.PLL.PLLN = 240;
//	Osc_init.PLL.PLLP = RCC_PLLP_DIV2;
	/* End of 120Mhz specific configuration */
	/* Configure PLL to generate 216MHz clock for SYSCLK using HSE as source. */

	// This configuration requires Power Scale 1 and Over drive ON.
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG( PWR_REGULATOR_VOLTAGE_SCALE1 );
	__HAL_PWR_OVERDRIVE_ENABLE();

	Osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	Osc_init.HSEState = RCC_HSE_BYPASS;
	Osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	Osc_init.PLL.PLLState = RCC_PLL_ON;
	Osc_init.PLL.PLLM = 4;
	Osc_init.PLL.PLLN = 216;
	Osc_init.PLL.PLLP = RCC_PLLP_DIV2;
	/* End of 120Mhz specific configuration */
	Osc_init.PLL.PLLQ = 2;
	Osc_init.PLL.PLLR = 2;
	if ( HAL_RCC_OscConfig(&Osc_init) != HAL_OK )
	{
		// Error in Oscillator or PLL configuration.
		Error_Handler();
	}

	// Configure the various clocks.
	RCC_ClkInitTypeDef Clk_init{0};
	Clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	Clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	//Clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1; // for 50, 84 and 120Mhz configurations.
	//Clk_init.APB1CLKDivider = RCC_HCLK_DIV2;	// for 50 and 84 configurations.
	//Clk_init.APB1CLKDivider = RCC_HCLK_DIV4;	// for 128HHz configuration.
	//Clk_init.APB2CLKDivider = RCC_HCLK_DIV2;	// for 50, 84 and 128MHz configurations.
	std::uint32_t flash_latency{FLASH_LATENCY_0};
	//flash_latency = FLASH_LATENCY_1; // for 50MHz configuration.
	//flash_latency = FLASH_LATENCY_2; // for 84MHz configuration.
	// for 216MHz configuration.
	Clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
	Clk_init.APB1CLKDivider = RCC_HCLK_DIV4;	// for 54HHz PCLK1.
	Clk_init.APB2CLKDivider = RCC_HCLK_DIV2;	// for 108HHz PCLK2.
//	flash_latency = FLASH_LATENCY_4; // for 120MHz configuration.
	flash_latency = FLASH_LATENCY_7; // for 216MHz configuration.
	if ( HAL_RCC_ClockConfig( &Clk_init, flash_latency ) != HAL_OK )
	{
		// Error in Clock configuration.
		Error_Handler();
	}

	// Disable HSI
	__HAL_RCC_HSI_DISABLE();

	// Configure SysTick with new clock settings.
	HAL_SYSTICK_CLKSourceConfig( SYSTICK_CLKSOURCE_HCLK );
	HAL_SYSTICK_Config( ( HAL_RCC_GetHCLKFreq() / 1000 ) );
#endif // USE_PLL_EXAMPLE
}
#endif
#endif // USE_HSE_EXAMPLE or USE_PLL_EXAMPLE

#if defined( USE_HSE_EXAMPLE ) || defined( USE_PLL_EXAMPLE ) || defined( USE_UART_EXAMPLE )
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
#endif // USE_HSE_EXAMPLE or USE_PLL_EXAMPLE or USE_UART_EXAMPLE

#ifdef USE_UART_EXAMPLE
#if 0
static inline char convert_to_Upper( char c )
{
	char retVal{c};

	if ( (c >= 'a') && (c <= 'z') )
	{
		retVal -= ('a' - 'A');
	}

	return retVal;
}
#endif
#endif // USE_UART_EXAMPLE

static void Error_Handler( void )
{
	for (;;);
}

#if defined( USE_HSE_EXAMPLE ) || defined( USE_PLL_EXAMPLE )
static void displayClkInfo( void )
{
	char msg[1024];

	/* Configure the UART for debug console */
	UART3_Init();

	std::sprintf (msg, "SYSCLK:%luMHz, HCLK:%luMHz, PCLK1:%luMHz, PCLK2:%luMHz\r\n",
			( HAL_RCC_GetSysClockFreq() / 1000000 ), ( HAL_RCC_GetHCLKFreq() / 1000000 ), ( HAL_RCC_GetPCLK1Freq() / 1000000 ), ( HAL_RCC_GetPCLK2Freq() / 1000000 ) );

	HAL_UART_Transmit( &huart3, (const std::uint8_t *)msg, std::strlen(msg), HAL_MAX_DELAY );
}
#endif // USE_HSE_EXAMPLE or USE_PLL_EXAMPLE

#ifdef USE_BASIC_TIMER_EXAMPLE
static void TIM6_init( void )
{
	/* Configure basic timer to generate timer update event for every 100us. */
	hTimer6.Instance = TIM6;
	hTimer6.Init.CounterMode = TIM_COUNTERMODE_UP;
	hTimer6.Init.Prescaler = 16;
	hTimer6.Init.Period = 100 - 1;
	if ( HAL_TIM_Base_Init( &hTimer6 ) != HAL_OK )
	{
		// Error in Timer Configuration.
		Error_Handler();
	}
}

static void LED_init( void )
{
	/* Blue User LED is connected to GPIOB pin 7. */
	GPIO_InitTypeDef LED_pin_config{0};
	LED_pin_config.Pin = GPIO_PIN_7;
	LED_pin_config.Mode = GPIO_MODE_OUTPUT_PP;
	LED_pin_config.Speed = GPIO_SPEED_FREQ_LOW;
	LED_pin_config.Pull = GPIO_NOPULL;
	// Enable clock for GPIOB.
	__HAL_RCC_GPIOB_CLK_ENABLE();
	HAL_GPIO_Init( GPIOB, &LED_pin_config );
}
#endif // USE_BASIC_TIMER_EXAMPLE

#ifdef USE_INPUT_CAPTURE_TIMER_EXAMPLE
static void TIM2_init( void )
{
	hTimer2.Instance = TIM2;
	hTimer2.Init.CounterMode = TIM_COUNTERMODE_UP;
	hTimer2.Init.Prescaler = 1; // Run timer at 25MHz.
	hTimer2.Init.Period = 0xFFFFFFFFU;
	if ( HAL_TIM_IC_Init( &hTimer2 ) != HAL_OK )
	{
		// Error in Timer initialization.
		Error_Handler();
	}

	TIM_IC_InitTypeDef tim2_ic_config{0};
	tim2_ic_config.ICFilter = 0;
	tim2_ic_config.ICPolarity = TIM_ICPOLARITY_RISING;
	tim2_ic_config.ICSelection = TIM_ICSELECTION_DIRECTTI;
	tim2_ic_config.ICPrescaler = TIM_ICPSC_DIV1;
	if ( HAL_TIM_IC_ConfigChannel( &hTimer2, &tim2_ic_config, TIM_CHANNEL_1 ) != HAL_OK )
	{
		// Error in Timer input channel configuration.
		Error_Handler();
	}
}

static void SystemClock_Config( void )
{
	// Configure the Clock Source.
	RCC_OscInitTypeDef Osc_init{0};

	/* Configure PLL to generate 50MHz clock for SYSCLK using HSE as source. */

	// This configuration requires Power Scale 1 and Over drive OFF.
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG( PWR_REGULATOR_VOLTAGE_SCALE1 );
	__HAL_PWR_OVERDRIVE_DISABLE();

	Osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	Osc_init.HSEState = RCC_HSE_BYPASS;
	Osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	Osc_init.PLL.PLLState = RCC_PLL_ON;
	Osc_init.PLL.PLLM = 4;
	Osc_init.PLL.PLLN = 50;
	Osc_init.PLL.PLLP = RCC_PLLP_DIV2;
	/* End of 120Mhz specific configuration */
	Osc_init.PLL.PLLQ = 2;
	Osc_init.PLL.PLLR = 2;

	if ( HAL_RCC_OscConfig(&Osc_init) != HAL_OK )
	{
		// Error in Oscillator or PLL configuration.
		Error_Handler();
	}

	// Configure the various clocks.
	RCC_ClkInitTypeDef Clk_init{0};
	Clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	Clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	std::uint32_t flash_latency{FLASH_LATENCY_1};
	Clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;	// for 50HHz HCLK.
	Clk_init.APB1CLKDivider = RCC_HCLK_DIV1;	// for 50HHz PCLK1.
	Clk_init.APB2CLKDivider = RCC_HCLK_DIV1;	// for 50HHz PCLK2.
	if ( HAL_RCC_ClockConfig( &Clk_init, flash_latency ) != HAL_OK )
	{
		// Error in Clock configuration.
		Error_Handler();
	}

	// Disable HSI
	__HAL_RCC_HSI_DISABLE();

	// Configure SysTick with new clock settings.
	HAL_SYSTICK_CLKSourceConfig( SYSTICK_CLKSOURCE_HCLK );
	HAL_SYSTICK_Config( ( HAL_RCC_GetHCLKFreq() / 1000 ) );
}

static void LSE_config( void )
{
	/* Configure the Oscillator. */
	RCC_OscInitTypeDef Osc_init{0};

	Osc_init.OscillatorType = RCC_OSCILLATORTYPE_LSE;
	Osc_init.LSEState = RCC_LSE_ON;

	if ( HAL_RCC_OscConfig(&Osc_init) != HAL_OK )
	{
		// Error in Oscillator configuration.
		Error_Handler();
	}

	// Route LSE to MCO1 (PA8).
	HAL_RCC_MCOConfig( RCC_MCO1, RCC_MCO1SOURCE_LSE, RCC_MCODIV_1 );
}

extern "C" void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if ( !capture_completed )
	{
		if ( !capture_idx )
		{
			TIM_cnts[0] = __HAL_TIM_GET_COMPARE( htim, TIM_CHANNEL_1 );
			capture_idx = 1;
		}
		else
		{
			TIM_cnts[1] = __HAL_TIM_GET_COMPARE( htim, TIM_CHANNEL_1 );
			capture_completed = true;
			capture_idx = 0;
		}
	}
}

static void displayUserSigInfo( void )
{
	std::uint32_t elapsed_tim_cnts{0};
	double user_sig_time_period{0};
	double user_sig_freq{0};
	std::uint32_t tim_freq{0};
	double tim_resolution{0};

	if ( TIM_cnts[1] >= TIM_cnts[0] )
	{
		elapsed_tim_cnts = TIM_cnts[1] - TIM_cnts[0];
	}
	else
	{
		elapsed_tim_cnts = ( hTimer2.Init.Period - TIM_cnts[0] ) + TIM_cnts[1];
	}

	// Because The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC + 1).
	tim_freq = HAL_RCC_GetPCLK1Freq() / ( hTimer2.Init.Prescaler + 1 );
	tim_resolution = 1.0 / tim_freq;
	user_sig_time_period = elapsed_tim_cnts * tim_resolution;
	// Transform from User signal time domain to Frequency domain.
	user_sig_freq = 1.0 / user_sig_time_period;

	char msg[1024];

	/* Configure the UART for debug console */
	UART3_Init();

	std::sprintf (msg, "%.3lfKhz\r\n", ( user_sig_freq / 1000 ) );
	HAL_UART_Transmit( &huart3, (const std::uint8_t *)msg, std::strlen(msg), HAL_MAX_DELAY );
}
#endif // USE_INPUT_CAPTURE_TIMER_EXAMPLE
