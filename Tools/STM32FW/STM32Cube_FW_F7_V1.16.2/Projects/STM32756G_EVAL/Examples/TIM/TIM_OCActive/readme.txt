/**
  @page TIM_OCActive TIM_OCActive example
  
  @verbatim
  ******************************************************************************
  * @file    TIM/TIM_OCActive/readme.txt 
  * @author  MCD Application Team
  * @brief   This example shows how to configure the Timer to generate four 
  *          delayed signals.
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

Configuration of the TIM peripheral in Output Compare Active mode 
(when the counter matches the capture/compare register, the corresponding output 
pin is set to its active state).

  The TIM1 frequency is set to SystemCoreClock, and the objective is
  to get TIM1 counter clock at 10 kHz so the Prescaler is computed as following:
     - Prescaler = (TIM1CLK /TIM1 counter clock) - 1
   
  SystemCoreClock is set to 216 MHz for STM32F7xx Devices.

  The TIM1 CCR1 register value is equal to 10000:
  TIM1_CH1 delay = CCR1_Val/TIM1 counter clock  = 1s
  so the TIM1 Channel 1 generates a signal with a delay equal to 1s.

  The TIM1 CCR2 register value is equal to 5000:
  TIM1_CH2 delay = CCR2_Val/TIM1 counter clock = 500 ms
  so the TIM1 Channel 2 generates a signal with a delay equal to 500 ms.

  The TIM1 CCR3 register value is equal to 2500:
  TIM1_CH3 delay = CCR3_Val/TIM1 counter clock = 250 ms
  so the TIM1 Channel 3 generates a signal with a delay equal to 250 ms.

  The TIM1 CCR4 register value is equal to 1250:
  TIM1_CH4 delay = CCR4_Val/TIM1 counter clock = 125 ms
  so the TIM1 Channel 4 generates a signal with a delay equal to 125 ms.

  The delay correspond to the time difference between PB.02 rising edge and
  TIM1_CHx signal rising edges.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Timers, Output, Compare, Active, Signals, 

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

  - TIM/TIM_OCActive/Inc/stm32f7xx_hal_conf.h    HAL configuration file
  - TIM/TIM_OCActive/Inc/stm32f7xx_it.h          Interrupt handlers header file
  - TIM/TIM_OCActive/Inc/main.h                  Header for main.c module  
  - TIM/TIM_OCActive/Src/stm32f7xx_it.c          Interrupt handlers
  - TIM/TIM_OCActive/Src/main.c                  Main program
  - TIM/TIM_OCActive/Src/stm32f7xx_hal_msp.c     HAL MSP file
  - TIM/TIM_OCActive/Src/system_stm32f7xx.c      STM32F7xx system source file


@par Hardware and Software environment

  - This example runs on STM32756xx devices.
    
  - This example has been tested with STMicroelectronics STM327x6G-EVAL revB 
    board and can be easily tailored to any other supported device 
    and development board.      

  - STM327x6G-EVAL revB Set-up
   Connect the following pins to an oscilloscope to monitor the different waveforms:
      - Use PB.02 (Reference)
      - PA.08: (TIM1_CH1) ((pin 52 in CN6 connector))
      - PA.09: (TIM1_CH2) ((pin 43 in CN6 connector))
      - PA.10: (TIM1_CH3) ((pin 44 in CN6 connector))
      - PA.11: (TIM1_CH4) ((pin 41 in CN6 connector))

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
 
 
You should see these waveforms on oscilloscope :

 CH1                                                            ________________
 _______________________________________________________________|
           <---------------------- 1sec------------------------->
           
 CH2                                   __________________________________________
 ______________________________________|
           <------------500ms--------->
 
 CH3                        _____________________________________________________
 ___________________________|
           <----250ms------->
 
 CH4                  ____________________________________________________________
 _____________________|
           <--125ms--->

 TRIG      ______________________________________________________________________
 __________|



 */
