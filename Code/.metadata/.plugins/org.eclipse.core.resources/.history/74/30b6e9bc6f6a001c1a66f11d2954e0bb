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
#endif // USE_UART_EXAMPLE

extern UART_HandleTypeDef huart3;

#ifdef __cplusplus
}
#endif

#endif /* INC_MAIN_H_ */
