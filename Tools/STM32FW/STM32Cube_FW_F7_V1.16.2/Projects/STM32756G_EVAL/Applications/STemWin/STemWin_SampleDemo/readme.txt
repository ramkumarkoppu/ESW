/**
  @page STemWin_SampleDemo Readme file
 
  @verbatim
  ******************************************************************************
  * @file    STemWin/STemWin_SampleDemo/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of STemWin Sample Demo application.  
  ******************************************************************************
  *
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @endverbatim

@par Application Description

This application shows how to implement a sample demonstration example allowing 
to show some of the STemWin Library capabilities.

The list of modules to be used is configured into the file Demo/GUIDEMO.h

At the first run, after power OFF/ON, a touch screen calibration is needed: in
order to this, user is just requested to follow the displayed instructions.
Then all the demo modules are run sequentially. Throughout the demonstration, a
control frame window is displayed at the bottom right of the touch screen: it
includes a progress bar and two control buttons (Next + Halt) allowing to skip
or pause the currently running module.

LEDs 1 to 4 are continuously toggling to indicate that the Demo runs properly.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@note Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select the RTC clock source; in this 
      case the Backup domain will be reset in order to modify the RTC Clock source, as consequence RTC  
      registers (including the backup registers) and RCC_BDCR register are set to their reset values.
	   
@note The STM32F7xx devices can reach a maximum clock frequency of 216MHz but as this application uses SDRAM,
      the system clock is limited to 200MHz. Indeed proper functioning of the SDRAM is only guaranteed 
      at a maximum system clock frequency of 200MHz.

     
@par Keywords

Display, Graphic, STemWin, HelloWorld, LCD, GUI, Demonstration, Touch screen

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

  - STemWin/STemWin_SampleDemo/STemWin/Target/GUIConf.h                        Header for GUIConf.c
  - STemWin/STemWin_SampleDemo/STemWin/Target/LCDConf.h                        Header for LCDConf*.c
  - STemWin/STemWin_SampleDemo/Core/Inc/rtc.h                                  Header for rtc.c
  - STemWin/STemWin_SampleDemo/Core/Inc/calibration.h                          Header for calibration.c
  - STemWin/STemWin_SampleDemo/Core/Inc/main.h                                 Main program header file
  - STemWin/STemWin_SampleDemo/Core/Inc/stm32f7xx_hal_conf.h                   Library Configuration file
  - STemWin/STemWin_SampleDemo/Core/Inc/stm32f7xx_it.h                         Interrupt handlers header file
  - STemWin/STemWin_SampleDemo/Core/Src/rtc.c                                  Main file to configure RTC clock
  - STemWin/STemWin_SampleDemo/Core/Src/calibration.c                          Main file to calibrate TS
  - STemWin/STemWin_SampleDemo/STemWin/Target/GUIConf.c                        Display controller initialization file
  - STemWin/STemWin_SampleDemo/STemWin/Target/LCDConf_STM327x6G_EVAL_MB1063.c  Configuration file for the GUI library (MB1063 LCD)
  - STemWin/STemWin_SampleDemo/Core/Src/main.c                                 Main program file
  - STemWin/STemWin_SampleDemo/Core/Src/stm32f7xx_it.c                         STM32F7xx Interrupt handlers
  - STemWin/STemWin_SampleDemo/Core/Src/system_stm32f7xx.c                     STM32F7xx system file
  - STemWin/STemWin_SampleDemo/STemWin/App/GUIDEMO.c                           All the sources files provided for SEGGER DEMO
  - STemWin/STemWin_SampleDemo/STemWin/App/GUIDEMO.h                           DEMO modules configuration file


@par Hardware and Software environment 

  - This application runs on STM32F756xx/STM32F746xx devices.
    
  - This application has been tested with STMicroelectronics STM327x6G_EVAL
    (STM32F7x6 Devices) evaluation boards and can be easily 
    tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the application
 

 */
