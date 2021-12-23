/**
  @page LibJPEG_Encoding LibJPEG encoding example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    LibJPEG/LibJPEG_Encoding/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the LibJPEG encoding example.
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

This example demonstrates how to read BMP file from micro SD, encode it, save the jpeg file
in the SD card root then decode the jpeg file and display the final BMP image on the LCD.


The images must have the following properties:
 - named as "image.bmp"
 - 320*240 size

The image size can be modified by changing IMAGE_WIDTH and IMAGE_HEIGHT defines 
in "main.h" file to decode other resolution than 320x240.

Uncomment "SWAP_RB" define in "main.h" file to invert the display image colors.

The image transferring to the LCD_FRAME_BUFFER can be done with two ways; 
with CPU or with DMA2D. In main.h file, uncomment "USE_DMA2D" define for DMA2D   
transfer. Otherwise, transfer is made by CPU. 

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@note The STM32F7xx devices can reach a maximum clock frequency of 216MHz but as this application uses SDRAM,
      the system clock is limited to 200MHz. Indeed proper functioning of the SDRAM is only guaranteed 
      at a maximum system clock frequency of 200MHz.

@par Keywords

Display, Graphic, LibJPEG, Encoding, Flash memory, DMA2D, ARGB8888, LCD, RGB, BMP, JPG, SD Card

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

    - LibJPEG/LibJPEG_Encoding/Inc/main.h                      Main program header file
    - LibJPEG/LibJPEG_Encoding/Inc/stm32f7xx_it.h              Interrupt handlers header file
    - LibJPEG/LibJPEG_Encoding/Inc/stm32f7xx_hal_conf.h        HAL Configuration file 
    - LibJPEG/LibJPEG_Encoding/Inc/ffconf.h                    Configuration file for FatFs module.
    - LibJPEG/LibJPEG_Encoding/Inc/encode.h                    encoder header file
    - LibJPEG/LibJPEG_Encoding/Inc/decode.h                    decoder header file
    - LibJPEG/LibJPEG_Encoding/Inc/jmorecfg.h                  Lib JPEG configuration file (advanced configuration).
    - LibJPEG/LibJPEG_Encoding/Inc/jconfig.h                   Lib JPEG configuration file.
    - LibJPEG/LibJPEG_Encoding/Inc/jdata_conf.h                Write/Read methods definition   
    - LibJPEG/LibJPEG_Encoding/Src/sd_diskio.h                 SD diskio header file    
    - LibJPEG/LibJPEG_Encoding/Src/main.c                      Main program  
    - LibJPEG/LibJPEG_Encoding/Src/stm32f7xx_it.c              Interrupt handlers
    - LibJPEG/LibJPEG_Encoding/Src/system_stm32f7xx.c          STM32F7xx system clock configuration file
    - LibJPEG/LibJPEG_Encoding/Src/encode.c                    encoder file
    - LibJPEG/LibJPEG_Encoding/Src/decode.c                    decoder file
    - LibJPEG/LibJPEG_Encoding/Src/jdata_conf.c                Write/Read methods definition
    - LibJPEG/LibJPEG_Encoding/Src/sd_diskio.c                 SD diskio file


@par Hardware and Software environment

  - This example runs on STM32F756xx/STM32F746xx devices.
    
  - This example has been tested with STMicroelectronics STM327x6G-EVAL
    evaluation boards and can be easily tailored to any other supported device 
    and development board.
    
  - STM327x6G-EVAL Set-up
    - Connect a uSD Card to the MSD connector (CN16).

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
                                   
