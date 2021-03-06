/*
 * msp.cpp
 *
 *  Created on: Dec 24, 2021
 *      Author: rkoppu
 */
#include <cstring>
#include "main.h"

/* Low level Processor specific initialization */
extern "C" void HAL_MspInit( void )
{
	// Set the priority grouping of the processor.
	HAL_NVIC_SetPriorityGrouping( NVIC_PRIORITYGROUP_4 );

	// Enable the required system exceptions (Usage, bus and memory fault exceptions).
	SCB->SHCSR |= ( (1U << 18U) | (1U << 17U) | (1U << 16U) );

	// Configure the priority of the system exceptions.
	HAL_NVIC_SetPriority( UsageFault_IRQn, 0, 0 );
	HAL_NVIC_SetPriority( BusFault_IRQn, 0, 0 );
	HAL_NVIC_SetPriority( MemoryManagement_IRQn, 0, 0 );
}

/* UART Low level initilization */
extern "C" void HAL_UART_MspInit( UART_HandleTypeDef *huart )
{
	GPIO_InitTypeDef USART3_gpio_config{0};

	// Enable the clock for USART3 peripheral.
	__HAL_RCC_USART3_CLK_ENABLE();

	// Enable the clock for GPIOD peripheral.
	__HAL_RCC_GPIOD_CLK_ENABLE();

	// Do the GPIO multiplexing. PD8 is USART3 Tx and PD9 is USART3 Rx.
	USART3_gpio_config.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	USART3_gpio_config.Mode = GPIO_MODE_AF_PP;
	USART3_gpio_config.Pull = GPIO_PULLUP;
	USART3_gpio_config.Speed = GPIO_SPEED_FREQ_LOW;
	USART3_gpio_config.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init( GPIOD, &USART3_gpio_config );

	// Enable the IRQ and set up the priority (NVIC settings)
	HAL_NVIC_SetPriority( USART3_IRQn, 0x0F, 0 );
	HAL_NVIC_EnableIRQ( USART3_IRQn );
}

#if defined( USE_PWM_TIMER_EXAMPLE )
extern "C" void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	/* Enable Clock for TIM2. */
	__HAL_RCC_TIM2_CLK_ENABLE();

	/* Configure GPIO pins PB3 (TIM2-CH2) as Timer 2 output channel. */
	GPIO_InitTypeDef tim2_ch_gpios{0};

	tim2_ch_gpios.Mode = GPIO_MODE_AF_PP;
	tim2_ch_gpios.Alternate = GPIO_AF1_TIM2;
	tim2_ch_gpios.Pin = GPIO_PIN_3;
	// Enable the clock for GPIOB.
	__HAL_RCC_GPIOB_CLK_ENABLE();
	HAL_GPIO_Init( GPIOB, &tim2_ch_gpios );

	/* Configure NVIC for TIM2 interrupt. */
	HAL_NVIC_SetPriority( TIM2_IRQn, 15, 0 );
	HAL_NVIC_EnableIRQ( TIM2_IRQn );
}
#endif // USE_PWM_TIMER_EXAMPLE

#if defined( USE_ADC_EXAMPLE )
extern "C" void HAL_ADC_MspInit( ADC_HandleTypeDef* hadc )
{
	if ( hadc->Instance == ADC1 )
	{
		// Enable Clock for ADC1.
		__HAL_RCC_ADC1_CLK_ENABLE();

		hdma_adc1.Instance = DMA2_Stream4;
	    hdma_adc1.Init.Channel = DMA_CHANNEL_0;
	    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
	    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
	    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
	    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	    hdma_adc1.Init.Mode = DMA_NORMAL;
	    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
	    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	    hdma_adc1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	    hdma_adc1.Init.MemBurst = DMA_MBURST_SINGLE;
	    hdma_adc1.Init.PeriphBurst = DMA_PBURST_SINGLE;

		if ( HAL_DMA_Init( &hdma_adc1 ) != HAL_OK )
		{
			// Error in DMA configuration for ADC1.
			Error_Handler();
		}

		__HAL_LINKDMA( hadc, DMA_Handle, hdma_adc1 );
	}
}
#endif // USE_ADC_EXAMPLE
