/**
  @page LTDC_Paint LTDC Paint application
  
  @verbatim
  ******************************************************************************
  * @file    Display/LTDC_Paint/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the LTDC Paint application.
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

 This application describes how to configure LCD touch screen and attribute 
 an action related to configured touch zone and how to save BMP picture in USB Disk.
 
 At the beginning of the main program the HAL_Init() function is called to reset 
 all the peripherals, initialize the Flash interface and the systick.
 Then the SystemClock_Config() function is used to configure the system
 clock (SYSCLK) to run at 200 MHz.  

 After LCD and touch screen initialization, touchscreen calibration is requested
 for better accuracy for MB1046 only, then, menu is displayed on the screen. 
 
 The menu contains palette of colors, clear icon, save icon, different kinds 
 of draw sizes, the current selected size, selected color and working rectangle. 

 Select one of proposed colors and select the size of brush to draw 
 inside the working rectangle.
 
 Clear the working window by pressing the clear icon or/and save the picture 
 in USB Mass Stroage by pressing the save icon.

                                          LCD Menu
               ____________________________________________________________
          /   |______|---------------------------------------------------- |
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
palette   |   |______||               Working Rectangle                   ||
   of   __|   |______||                                                   ||
 Colors   |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||___________________________________________________|| 
          \   |______|__________________ _________        __               | 
              |clear |  choose the brush|   Save  |      |__|         O    | 
              |______|________size______|_USBDisk_|__selected color__size__|


  - LED1 is on to indicate the end of saving operation and a message is displayed 
    on LCD to indicate the beginning and the end of the saving operation.
  - LED3 is ON when any error occurs.

Note: After save operation, the touch positions are not cleared from STMPE811 FIFO 
      and the next touch in any positions of the LCD screen leads second save 
      operation.
      This limitation is only relative to ampire 480x272 LCD device.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@note The STM32F7xx devices can reach a maximum clock frequency of 216MHz but as this application uses SDRAM,
      the system clock is limited to 200MHz. Indeed proper functioning of the SDRAM is only guaranteed 
      at a maximum system clock frequency of 200MHz.

@par Keywords

Display, Graphic, LTDC, Pictures, USB, BMP, Background, Foreground, Layers, Touchscreen, Calibration

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

    - Display/LTDC_Paint/Inc/main.h                 Main configuration file
    - Display/LTDC_Paint/Inc/stm32f7xx_it.h         Interrupt handlers header file
    - Display/LTDC_Paint/Inc/stm32f7xx_hal_conf.h   HAL Configuration file 
    - Display/LTDC_Paint/Inc/ffconf.h               FAT file system module configuration file
    - Display/LTDC_Paint/Inc/usbh_conf.h            Configuration file for USB module
    - Display/LTDC_Paint/Inc/color.h                Image used for LTDC Validation
    - Display/LTDC_Paint/Inc/color2.h               Image used to display colored pens
    - Display/LTDC_Paint/Inc/save.h                 Image used to display save icon
    - Display/LTDC_Paint/Src/usbh_diskio.h          USB host diskio header file
    - Display/LTDC_Paint/Src/main.c                 Main program 
    - Display/LTDC_Paint/Src/stm32f7xx_it.c         Interrupt handlers
    - Display/LTDC_Paint/Src/usbh_conf.c            Main function to configure USB
    - Display/LTDC_Paint/Src/ts_calibration.c       Main function used to calibrate TS
    - Display/LTDC_Paint/Src/system_stm32f7xx.c     STM32F7xx system clock configuration file
    - Display/LTDC_Paint/Src/usbh_diskio.c          USB host diskio file


@par Hardware and Software environment

  - This application runs on STM32F756xx/STM32F746xx devices.

  - This application has been tested with STM327x6G-EVAL evaluation board 
    and can be easily tailored to any other supported device and development board.

  - STM327x6G-EVAL Set-up
    - Plug the USB key into the STM327x6G-EVAL board through 'USB micro A-Male 
      to A-Female' cable (HS mode: connector CN8).
    - Ensure that JP24 is in position 2-3 to use LED1.
    - Ensure that JP23 is in position 2-3 to use LED3. 


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the application


 */
                                   