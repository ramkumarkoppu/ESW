/**
  @page FreeRTOS_DelayUntil FreeRTOS Delay Until example
 
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    FreeRTOS/FreeRTOS_DelayUntil/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the FreeRTOS Delay Until example.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @endverbatim

@par Application Description

This directory contains a set of source files that implement thread delaying using 
osDelayUntil function.

This example creates a thread that waits for 200ms starting from a reference absolute time "PreviousWakeTime"
using osDelayUntil then toggle LED1.

the result is that the thread execution frequency is ensured to be every 200ms 
independently from the time that the thread treatment takes

osDelayUntil function differs from osDelay() in one important aspect:  osDelay () will
cause a thread to block for the specified time in ms from the time osDelay () is
called.  It is therefore difficult to use osDelay () by itself to generate a fixed
execution frequency as the time between a thread starting to execute and that thread
calling osDelay () may not be fixed [the thread may take a different path though the
code between calls, or may get interrupted or preempted a different number of times
each time it executes].

Whereas osDelay () specifies a wake time relative to the time at which the function
is called, osDelayUntil () specifies the absolute (exact) time at which it wishes to
unblock.
PreviousWakeTime must be initialised with the current time prior to its first use 
(PreviousWakeTime = osKernelSysTick ) 

LED1 must blink every 200ms   


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in HAL time base ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the HAL time base interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the HAL time base interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the HAL time base is always set to 1 millisecond
      to have correct HAL operation.
	  
@note The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set according to 
      the OS resources memory requirements of the application with +10% margin and rounded to the 
	  upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications 
on STM32Cube with RTOS".

@par Keywords

RTOS, FreeRTOS, Threading, Delay

@Note�If the user code size exceeds the DTCM-RAM size or starts from internal cacheable memories (SRAM1 and SRAM2),that is shared between several processors,
 �����then it is highly recommended to enable the CPU cache and maintain its coherence at application level.
������The address and the size of cacheable buffers (shared between CPU and other masters)  must be properly updated to be aligned to cache line size (32 bytes).

@Note It is recommended to enable the cache and maintain its coherence, but depending on the use case
����� It is also possible to configure the MPU as "Write through", to guarantee the write access coherence.
������In that case, the MPU must be configured as Cacheable/Bufferable/Not Shareable.
������Even though the user must manage the cache coherence for read accesses.
������Please refer to the AN4838 �Managing memory protection unit (MPU) in STM32 MCUs�
������Please refer to the AN4839 �Level 1 cache on STM32F7 Series�

@par Directory contents

    - FreeRTOS/FreeRTOS_DelayUntil/Inc/main.h                Main program header file
    - FreeRTOS/FreeRTOS_DelayUntil/Inc/stm32f7xx_hal_conf.h  HAL Library Configuration file
    - FreeRTOS/FreeRTOS_DelayUntil/Inc/stm32f7xx_it.h        Interrupt handlers header file
    - FreeRTOS/FreeRTOS_DelayUntil/Inc/FreeRTOSConfig.h      FreeRTOS Configuration file
    - FreeRTOS/FreeRTOS_DelayUntil/Src/main.c                Main program
    - FreeRTOS/FreeRTOS_DelayUntil/Src/stm32f7xx_it.c        Interrupt handlers


@par Hardware and Software environment

  - This application runs on STM32F746xx devices.
    
  - This example has been tested with STM32746G-DISCOVERY evaluation board and can be
    easily tailored to any other supported device and development board.

  - STM32746G-DISCOVERY Set-up
    - None

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
  

 */
