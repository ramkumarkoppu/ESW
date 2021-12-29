/*
 * msp.cpp
 *
 *  Created on: Dec 24, 2021
 *      Author: rkoppu
 */
#include "main.h"

/* Low level Processor specific initialization */
extern "C" void HAL_MspInit(void)
{
	// Set the priority grouping of the processor.
	HAL_NVIC_SetPriorityGrouping( NVIC_PRIORITYGROUP_4 );

	// Enable the required system exceptions (Usage, bus and memory fault exceptions).
	SCB->SHCSR |= ( (1U << 18U) | (1U << 17U) | (1U << 16U) );

	// Configure the priority of the system exceptions.
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
}

/* UART Low level initilization */
extern "C" void HAL_UART_MspInit(UART_HandleTypeDef *huart)
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
	HAL_GPIO_Init(GPIOD, &USART3_gpio_config);

	// Enable the IRQ and set up the priority (NVIC settings)
	HAL_NVIC_SetPriority(USART3_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(USART3_IRQn);
}



