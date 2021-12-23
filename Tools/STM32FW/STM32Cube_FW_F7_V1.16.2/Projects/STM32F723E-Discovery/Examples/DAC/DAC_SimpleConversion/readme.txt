/**
  @page DAC_SimpleConversion DAC Simple Conversion example
  
  @verbatim
  ******************************************************************************
  * @file    DAC/DAC_SimpleConversion/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the DAC Simple Conversion example.
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

How to use the DAC peripheral to do a simple conversion.

The DAC peripheral is used to perform a simple conversion in 8 bits right alignment 
of 0xFF value, the result of the conversion can be seen by connecting PA4(DAC channel1) to an oscilloscope.
The observed value is 3.3V.
      

STM32F723E-DISCOVERY board's LEDs can be used to monitor the process status:
  - LED5 is ON and example is stopped (using infinite loop)
  when there is an error during process.

@par Keywords

Analog, DAC, Conversion, Voltage output, Oscilloscope

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

  - DAC/DAC_Simple_Conversion/Inc/stm32f7xx_hal_conf.h    HAL configuration file
  - DAC/DAC_Simple_Conversion/Inc/stm32f7xx_it.h          DMA interrupt handlers header file
  - DAC/DAC_Simple_Conversion/Inc/main.h                  Header for main.c module  
  - DAC/DAC_Simple_Conversion/Src/stm32f7xx_it.c          DMA interrupt handlers
  - DAC/DAC_Simple_Conversion/Src/main.c                  Main program
  - DAC/DAC_Simple_Conversion/Src/stm32f7xx_hal_msp.c     HAL MSP file
  - DAC/DAC_Simple_Conversion/Src/system_stm32f7xx.c      STM32F7xx system source file
  

@par Hardware and Software environment  
  - This example runs on STM32F722xx/STM32F723xx/STM32F732xx/STM32F733xx devices.
    
  - This example has been tested with STM32F723E-DISCOVERY board and can be
    easily tailored to any other supported device and development board.

  - STM32F723E-DISCOVERY Set-up 	
    
      - Connect PA4 (DAC Channel1) on eval board connector (pin 2 in CN15) to an oscilloscope.
      

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
  

 */

