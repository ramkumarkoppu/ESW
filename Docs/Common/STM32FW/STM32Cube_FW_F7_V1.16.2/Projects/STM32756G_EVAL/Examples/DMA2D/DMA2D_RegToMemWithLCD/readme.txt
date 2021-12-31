/**
  @page DMA2D_RegToMemWithLCD DMA2D Register to Memory with LCD example
  
  @verbatim
  ******************************************************************************
  * @file    DMA2D/DMA2D_RegToMemWithLCD/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the DMA2D Register to Memory with LCD example.
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

@par Example Description

How to configure DMA2D peripheral in Register-to-memory transfer mode and
display the result on the LCD.
  
  The register to Memory mode of the DMA2D is used to copy a fixed color in format ARGB4444 (16 bpp).
  The fixed color value used is 0xF0FF. It is copied from register to a SRAM memory area aBufferResult[]
  of 100x100 pixels in same format ARGB4444 which is filled by the DMA2D with fixed pattern ARGB4444 0xF0FF.
  The LTDC is then used to display the aBufferResult[] which is a 100x100 ARGB4444 fixed color image on LCD.
  
  At the beginning of the main program the HAL_Init() function is called to reset 
  all the peripherals, initialize the Flash interface and the systick.
  Then the SystemClock_Config() function is used to configure the system
  clock (SYSCLK) to run at 216 MHz.
 
  The Register_to_Memory transfer mode, is used to fill a user defined area by a 
  fixed color.
 
  After DMA2D configuration, the data transfer is performed and then the LCD is 
  configured to display color zone created after this transfer on LCD. 
  (more details about LCD configuration in LCD examples)

  @note 
  => Output offset is the number of pixel to be skipped after each transferred line

  how to calculate the size of the transferred data ? 
  => selected color mode gives the number of bits per pixel and we have 
     (ARGB4444 => 16bits/pixel) the number of pixel per line and the number of line, 
     therefore :
    
     data_size = (bits per pixel) X (pixel per line + output offset) X (number of line) 
    
STM327x6G-EVAL board revB's LEDs can be used to monitor the transfer status:
 - LED1 is ON when the DMA2D transfer is complete.
 - LED2 is ON when there is a DMA2D transfer error.
 - LED3 is ON when there is an error in LTDC transfer/Init process.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Display, Graphic, DMA2D, LCD, ARGB4444, Blending, Register to memory, LTDC, Pixel

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

    - DMA2D/DMA2D_RegToMemWithLCD/Inc/main.h                Main configuration file
    - DMA2D/DMA2D_RegToMemWithLCD/Inc/stm32f7xx_it.h        Interrupt handlers header file
    - DMA2D/DMA2D_RegToMemWithLCD/Inc/stm32f7xx_hal_conf.h  HAL configuration file 
    - DMA2D/DMA2D_RegToMemWithLCD/Src/main.c                Main program  
    - DMA2D/DMA2D_RegToMemWithLCD/Src/stm32f7xx_it.c        Interrupt handlers
    - DMA2D/DMA2D_RegToMemWithLCD/Src/stm32f7xx_hal_msp.c   HAL MSP module    
    - DMA2D/DMA2D_RegToMemWithLCD/Src/system_stm32f7xx.c    STM32F7xx system clock configuration file


@par Hardware and Software environment  

  - This example runs on STM32F756xx/STM32F746xx devices.
  
  - This example has been tested with STM327x6G-EVAL board revBs and can be easily 
    tailored to any other supported device and development board. 

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
  

 */
                                   