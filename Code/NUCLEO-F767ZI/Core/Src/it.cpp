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

#if defined( USE_PWM_TIMER_EXAMPLE )
extern "C" void TIM2_IRQHandler( void )
{
	// Invoke callback function.
	HAL_TIM_IRQHandler( &hTimer2 );
}
#endif // USE_PWM_TIMER_EXAMPLE

#if defined( USE_ADC_EXAMPLE )
/* ADC DMA Stream ISR. */
extern "C" void DMA2_Stream4_IRQHandler( void )
{
	// Invoke Callback function.
	HAL_DMA_IRQHandler( &hdma_adc1 );
}
#endif // USE_ADC_EXAMPLE

/* User Button ISR. */
extern "C" void EXTI15_10_IRQHandler(void)
{
	// Invoke Callback function.
	HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_13 );
}
