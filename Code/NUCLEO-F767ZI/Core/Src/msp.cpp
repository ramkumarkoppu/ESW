/*
 * msp.cpp
 *
 *  Created on: Dec 24, 2021
 *      Author: rkoppu
 */
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

#if defined( USE_HSE_EXAMPLE ) || defined( USE_PLL_EXAMPLE ) || defined( USE_UART_EXAMPLE )
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
#endif // USE_HSE_EXAMPLE or USE_PLL_EXAMPLE or USE_UART_EXAMPLE

#ifdef USE_BASIC_TIMER_EXAMPLE
extern "C" void HAL_TIM_Base_MspInit( TIM_HandleTypeDef *htim )
{
	// Enable the clock for the TIM6.
	__HAL_RCC_TIM6_CLK_ENABLE();

	// Enable TIM6 IRQ.
	HAL_NVIC_SetPriority( TIM6_DAC_IRQn, 15, 0 );
	HAL_NVIC_EnableIRQ( TIM6_DAC_IRQn );
#endif // USE_BASIC_TIMER_EXAMPLE

#ifdef USE_INPUT_CAPTURE_TIMER_EXAMPLE
extern "C" void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
	// Enable the clock for the TIM2.
	__HAL_RCC_TIM2_CLK_ENABLE();

	// Configure GPIO pin PA0 as Timer 2 input channel.
	GPIO_InitTypeDef tim2_ch1_gpio{0};
	tim2_ch1_gpio.Pin = GPIO_PIN_0;
	tim2_ch1_gpio.Mode = GPIO_MODE_AF_PP;
	tim2_ch1_gpio.Alternate = GPIO_AF1_TIM2;
	// Enable the Clock for GPIOA.
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init( GPIOA, &tim2_ch1_gpio );

	// Enable TIM2 IRQ.
	HAL_NVIC_SetPriority( TIM2_IRQn, 15, 0 );
	HAL_NVIC_EnableIRQ( TIM2_IRQn );
}
#endif // USE_INPUT_CAPTURE_TIMER_EXAMPLE



