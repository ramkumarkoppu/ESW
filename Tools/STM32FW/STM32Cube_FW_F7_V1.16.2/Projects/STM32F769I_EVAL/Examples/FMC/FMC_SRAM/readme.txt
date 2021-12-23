    /**
  @page FMC_SRAM FMC SRAM memory basic functionalities use example

  @verbatim
  ******************************************************************************
  * @file    FMC/FMC_SRAM/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the FMC SRAM example.
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

How to configure the FMC controller to access the SRAM memory.

The SRAM is IS61WV102416BLL-10MLI.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 216 MHz.

The goal of this example is to explain the different steps to configure the FMC 
and make the SRAM device ready for access, without using the MSP layer.          

In this example, the SRAM device is configured and initialized explicitly 
following all initialization sequence steps. After initializing the device, user 
can perform read/write operations on it. A data buffer is written to the SRAM 
memory, then read back and checked to verify its correctness.

If the data is read correctly from SRAM, the LED1 is ON, otherwise the LED2 is ON.   
In case of HAL initialization issue, LED3 will be ON. 

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Memory, FMC, SRAM, Read, Write, Initialization, Access

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

 - FMC/FMC_SRAM/Inc/stm32f7xx_hal_conf.h        HAL Configuration file
 - FMC/FMC_SRAM/Inc/main.h                      Header for main.c module 
 - FMC/FMC_SRAM/Inc/stm32f7xx_it.h              Header for stm32f7xx_it.c
 - FMC/FMC_SRAM/Src/main.c                      Main program
 - FMC/FMC_SRAM/Src/stm32f7xx_hal_msp.c         HAL MSP module  
 - FMC/FMC_SRAM/Src/stm32f7xx_it.c              Interrupt handlers
 - FMC/FMC_SRAM/Src/system_stm32f7xx.c          STM32F7xx system clock configuration file 
    

@par Hardware and Software environment 

  - This example runs on STM32F767xx/STM32F769xx/STM32F777xx/STM32F779xx devices.
    
  - This example has been tested with STM32F769I-EVAL board and can be
    easily tailored to any other supported device and development board. 

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
