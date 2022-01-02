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

#ifdef USE_INPUT_CAPTURE_TIMER_EXAMPLE
extern TIM_HandleTypeDef hTimer2;
#endif // USE_INPUT_CAPTURE_TIMER_EXAMPLE

#ifdef __cplusplus
}
#endif

#endif /* INC_MAIN_H_ */
