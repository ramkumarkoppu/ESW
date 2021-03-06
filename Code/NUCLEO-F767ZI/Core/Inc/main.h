/*
 * MAIN.H
 *
 *  Created on: Dec 24, 2021
 *      Author: rkoppu
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f7xx_hal.h"

#ifdef USE_UART_EXAMPLE
void HAL_UART_RxCpltCallback( UART_HandleTypeDef *huart );
void HAL_UART_TxCpltCallback( UART_HandleTypeDef *huart );

extern UART_HandleTypeDef huart3;
#endif // USE_UART_EXAMPLE

#ifdef USE_BASIC_TIMER_EXAMPLE
extern TIM_HandleTypeDef hTimer6;
#endif // USE_BASIC_TIMER_EXAMPLE

#if defined( USE_INPUT_CAPTURE_TIMER_EXAMPLE ) || defined( USE_OUTPUT_CAPTURE_TIMER_EXAMPLE ) || defined( USE_PWM_TIMER_EXAMPLE )
extern TIM_HandleTypeDef hTimer2;
#endif // USE_INPUT_CAPTURE_TIMER_EXAMPLE or USE_OUTPUT_CAPTURE_TIMER_EXAMPLE or USE_PWM_TIMER_EXAMPLE

#if defined( USE_ADC_EXAMPLE )
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
#endif // USE_ADC_EXAMPLE

void Error_Handler( void );

#ifdef __cplusplus
}
#endif

#endif /* INC_MAIN_H_ */
