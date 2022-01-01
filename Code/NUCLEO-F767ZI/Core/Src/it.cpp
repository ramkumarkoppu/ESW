/*
 * it.cpp
 *
 *  Created on: Dec 24, 2021
 *      Author: rkoppu
 */
#include "main.h"

/* This function handles System tick timer. */
extern "C" void SysTick_Handler( void )
{
	HAL_IncTick();
	// Invoke callback if it exists.
	HAL_SYSTICK_IRQHandler();
}

#ifdef USE_UART_EXAMPLE
/* This function handles USART3. */
extern "C" void USART3_IRQHandler( void )
{
	// Invoke callback if it exists.
	HAL_UART_IRQHandler( &huart3 );
}
#endif // USE_UART_EXAMPLE




