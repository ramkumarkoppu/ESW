/**
  @page STemWin_HelloWorld Readme file
 
  @verbatim
  ******************************************************************************
  * @file    STemWin/STemWin_HelloWorld/readme.txt 
  * @author  MCD Application Team
  * @brief   
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

Simple "Hello World" example based on STemWin.

The application allows also to run the different Segger samples that can be
downloaded from here:
http://www.segger.com/emwin-samples.html
To do this, user has only to replace the file "Basic_HelloWorld.c" into the
project workspace by the downloaded one.

Note that the following user files may need to be updated:
  LCDConf.c
  GUIConf.c
(if for example more GUI allocated memory is needed)

LED5 and LED6 are toggling continuously as a background task to indicate that the application is running successfully.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.      

@par Keywords

Display, Graphic, STemWin, HelloWorld, LCD, GUI

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

  - STemWin/STemWin_HelloWorld/Inc/GUIConf.h                        Header for GUIConf.c
  - STemWin/STemWin_HelloWorld/Inc/LCDConf.h                        Header for LCDConf*.c
  - STemWin/STemWin_HelloWorld/Inc/main.h                           Main program header file
  - STemWin/STemWin_HelloWorld/Inc/stm32f7xx_hal_conf.h             Library Configuration file
  - STemWin/STemWin_HelloWorld/Inc/stm32f7xx_it.h                   Interrupt handlers header file
  - STemWin/STemWin_HelloWorld/Src/BASIC_HelloWorld.c               Simple demo drawing "Hello world"
  - STemWin/STemWin_HelloWorld/Src/GUIConf.c                        Display controller initialization
  - STemWin/STemWin_HelloWorld/Src/LCDConf.c                        Configuration file for the GUI library
  - STemWin/STemWin_HelloWorld/Src/main.c                           Main program file
  - STemWin/STemWin_HelloWorld/Src/stm32f7xx_it.c                   STM32F7xx Interrupt handlers
  - STemWin/STemWin_HelloWorld/Src/system_stm32f7xx.c               STM32F7xx system file
 
 
@par Hardware and Software environment  

  - This application runs on STM32F723xx devices.
    
  - This application has been tested with STMicroelectronics STM32F723E_DISCOVERY
    boards RevC and can be easily tailored to any other supported device and 
    development board.


@par How to use it ? 

In order to make the program work, you must do the following :
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the application
  

 */
