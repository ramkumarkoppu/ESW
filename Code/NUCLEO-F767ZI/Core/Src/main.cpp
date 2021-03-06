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

#if defined( USE_PWM_TIMER_EXAMPLE )
#define PWM_CHANNELS	(1U)
#endif // USE_PWM_TIMER_EXAMPLE

UART_HandleTypeDef huart3;

#if defined( USE_PWM_TIMER_EXAMPLE )
TIM_HandleTypeDef hTimer2;
#endif //USE_PWM_TIMER_EXAMPLE

#if defined( USE_ADC_EXAMPLE )
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
#endif // USE_ADC_EXAMPLE

#if defined( USE_PWM_TIMER_EXAMPLE )
static std::uint32_t pulse_values[ PWM_CHANNELS ];
#endif // USE_PWM_TIMER_EXAMPLE

#if defined( USE_ADC_EXAMPLE )
std::uint16_t adcSamples[16];
#endif // USE_ADC_EXAMPLE

static std::int8_t button_press_cnt{3};

void Error_Handler( void );

#if defined( USE_PWM_TIMER_EXAMPLE )
static void TIM2_init( void );
#endif // USE_PWM_TIMER_EXAMPLE

#if defined( USE_ADC_EXAMPLE )
static void DMA2_init( void );
static void ADC1_init( void );
static void Button_init( void );
#endif // USE_ADC_EXAMPLE

static void SystemClock_Config( void );
static void UART3_Init( void );

int main( void )
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	// Initialize UART debug console.
	UART3_Init();

#if defined( USE_ADC_EXAMPLE )
	// User button init.
	Button_init();
#endif // USE_ADC_EXAMPLE

#if defined( USE_PWM_TIMER_EXAMPLE )
	TIM2_init();
#endif // USE_PWM_TIMER_EXAMPLE

#if defined( USE_PWM_TIMER_EXAMPLE )
	if ( HAL_TIM_PWM_Start_IT( &hTimer2, TIM_CHANNEL_2 ) != HAL_OK)
	{
		// Error in Timer Start.
		Error_Handler();
	}
#endif // USE_PWM_TIMER_EXAMPLE

#if defined( USE_ADC_EXAMPLE )
	DMA2_init();
	ADC1_init();
#endif // USE_ADC_EXAMPLE

	while(true)
	{
	}

	return 0;
}

#ifdef USE_PWM_TIMER_EXAMPLE
extern "C" void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	static bool rool_back{false};

	// Logic to update duty cycle on the fly goes here.
	if ( !rool_back )
	{
		if ( __HAL_TIM_GET_COMPARE( htim, TIM_CHANNEL_2 ) <= hTimer2.Init.Period )
		{
			pulse_values[0]++;
		}
		else if ( __HAL_TIM_GET_COMPARE( htim, TIM_CHANNEL_2 ) > hTimer2.Init.Period )
		{
			rool_back = true;
		}
	}

	if ( rool_back )
	{
		if ( __HAL_TIM_GET_COMPARE( htim, TIM_CHANNEL_2 ) > 0 )
		{
			pulse_values[0]--;
		}
		else if ( __HAL_TIM_GET_COMPARE( htim, TIM_CHANNEL_2 ) == 0 )
		{
			pulse_values[0] = 0;
			rool_back = false;
		}
	}

	__HAL_TIM_SET_COMPARE( htim, TIM_CHANNEL_2, pulse_values[0] );
}
#endif // USE_PWM_TIMER_EXAMPLE

/* User Button Press Callback Function. */
extern "C" void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin )
{
	// Handle Button debouncing
	if (button_press_cnt > 0)
	{
		button_press_cnt--;
	}

	if (button_press_cnt <= 0)
	{
		// Start the ADC conversion when User button is Pressed.
		if ( HAL_ADC_Start_DMA( &hadc1, (std::uint32_t *)adcSamples, 16 ) != HAL_OK )
		{
			// Error in ADC Start.
			Error_Handler();
		}
	}
}

#if defined( USE_ADC_EXAMPLE )
/* ADC DMA Stream ISR Callback Function. */
void HAL_ADC_ConvCpltCallback( ADC_HandleTypeDef* hadc )
{
	button_press_cnt = 3;
}
#endif // USE_ADC_EXAMPLE

void Error_Handler( void )
{
	for (;;);
}

static void SystemClock_Config( void )
{
	// Configure the Clock Source.
	RCC_OscInitTypeDef Osc_init{0};
	/* Configure PLL to generate 84MHz clock for SYSCLK using HSI as source. */

	// Configure the main internal regulator output voltage.
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG( PWR_REGULATOR_VOLTAGE_SCALE3 );
	__HAL_PWR_OVERDRIVE_DISABLE();

	Osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	Osc_init.HSIState = RCC_HSI_ON;
	Osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	Osc_init.PLL.PLLState = RCC_PLL_ON;
	Osc_init.PLL.PLLM = 8;
	Osc_init.PLL.PLLN = 168;
	Osc_init.PLL.PLLP = RCC_PLLP_DIV4;
	Osc_init.PLL.PLLQ = 4;
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
	Clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;	// for 84HHz HCLK.
	Clk_init.APB1CLKDivider = RCC_HCLK_DIV2;	// for 48HHz PCLK1.
	Clk_init.APB2CLKDivider = RCC_HCLK_DIV1;	// for 84HHz PCLK2.
	if ( HAL_RCC_ClockConfig( &Clk_init, FLASH_LATENCY_2 ) != HAL_OK )
	{
		// Error in Clock configuration.
		Error_Handler();
	}

	// Configure SysTick with new clock settings.
	HAL_SYSTICK_CLKSourceConfig( SYSTICK_CLKSOURCE_HCLK );
	HAL_SYSTICK_Config( ( HAL_RCC_GetHCLKFreq() / 1000 ) );
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

#if defined( USE_PWM_TIMER_EXAMPLE )
static void TIM2_init( void )
{
	hTimer2.Instance = TIM2;
	hTimer2.Init.Prescaler = 4;
	hTimer2.Init.CounterMode = TIM_COUNTERMODE_UP;
	hTimer2.Init.Period = 10000 - 1; // Generate update event at every 1 ms.
	if ( HAL_TIM_PWM_Init( &hTimer2 ) != HAL_OK )
	{
		// Error in initializing Timer.
		Error_Handler();
	}
	TIM_OC_InitTypeDef tim_OC_channels_config{0};
	tim_OC_channels_config.OCMode = TIM_OCMODE_PWM1;
	tim_OC_channels_config.OCPolarity = TIM_OCPOLARITY_HIGH;
	for (std::uint8_t chan_idx{0}; chan_idx < PWM_CHANNELS; chan_idx++)
	{
		// Compute initial duty cycle for each channel.
		switch(chan_idx)
		{
		case 0:
			pulse_values[chan_idx] = hTimer2.Init.Period * 0.0; // 0% Duty cycle.
			break;
		default:
			break;
		}

		tim_OC_channels_config.Pulse = pulse_values[chan_idx];

		if ( HAL_TIM_PWM_ConfigChannel( &hTimer2, &tim_OC_channels_config, ( TIM_CHANNEL_1 + ( chan_idx * 4) ) ) != HAL_OK)
		{
			// Error in Timer channel configuration.
			Error_Handler();
		}
	}
}
#endif // USE_PWM_TIMER_EXAMPLE

#if defined( USE_ADC_EXAMPLE )
static void DMA2_init( void )
{
	// Enable Clock for DMA2.
	__HAL_RCC_DMA2_CLK_ENABLE();

	// Configure NVIC for DMA2 Stream 4 interrupt.
	HAL_NVIC_SetPriority( DMA2_Stream4_IRQn, 0x0F, 0x0);
	HAL_NVIC_EnableIRQ( DMA2_Stream4_IRQn );
}

static void ADC1_init( void )
{
	hadc1.Instance = ADC1;
	 hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
	  hadc1.Init.ContinuousConvMode = ENABLE;
	  hadc1.Init.DiscontinuousConvMode = DISABLE;
	  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	  hadc1.Init.NbrOfConversion = 16;
	  hadc1.Init.DMAContinuousRequests = ENABLE;
	  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	  if ( HAL_ADC_Init( &hadc1 ) != HAL_OK )
	  {
		  // Error in ADC initialization.
		  Error_Handler();
	  }

	ADC_ChannelConfTypeDef adcConfig{0};
	adcConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
	adcConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	adcConfig.Rank = ADC_REGULAR_RANK_1;
	if ( HAL_ADC_ConfigChannel( &hadc1, &adcConfig ) != HAL_OK )
	{
		// Error in ADC channel configuration.
		Error_Handler();
	}
}

static void Button_init( void )
{
	GPIO_InitTypeDef user_Button_Pin_Config{0};
	user_Button_Pin_Config.Pin = GPIO_PIN_13;
	user_Button_Pin_Config.Mode = GPIO_MODE_IT_RISING;
	user_Button_Pin_Config.Pull = GPIO_PULLDOWN;
	user_Button_Pin_Config.Speed = GPIO_SPEED_FREQ_LOW;

	__HAL_RCC_GPIOC_CLK_ENABLE();
	HAL_GPIO_Init( GPIOC, &user_Button_Pin_Config );

	// Configure User Button interrupt.
	HAL_NVIC_SetPriority( EXTI15_10_IRQn, 15U, 0U );
	HAL_NVIC_EnableIRQ( EXTI15_10_IRQn );
}

#endif // USE_ADC_EXAMPLE
