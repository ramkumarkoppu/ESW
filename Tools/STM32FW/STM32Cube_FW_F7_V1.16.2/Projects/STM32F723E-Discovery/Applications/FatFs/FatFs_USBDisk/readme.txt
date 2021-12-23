/**
  @page FatFs_USBDisk   FatFs with USB disk drive application
 
  @verbatim
  ******************************************************************************
  * @file    FatFs/FatFs_USBDisk/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the FatFs with USB disk drive application
  ******************************************************************************
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

How to use STM32Cube firmware with FatFs middleware component as a generic FAT
file system module and STM32 USB On-The-Go (OTG) host library, in both Full
Speed (FS) and High Speed (HS) modes. This example develops an application
exploiting FatFs features, with USB disk drive configuration.

At the beginning of the main program the HAL_Init() function is called to reset all the peripherals,
initialize the Flash interface and the systick. The user is provided with the SystemClock_Config()
function to configure the system clock (SYSCLK) to run at 216 MHz. The Full Speed (FS) USB module uses
internally a 48-MHz clock which is coming from the main PLL..
In the High Speed (HS) mode the USB clock (60 MHz) is driven by the ULPI.
           
The application is based on writing a text file to a drive, and it's performed 
using FatFs APIs to access the FAT volume as described in the following steps: 

 - Link the USB Host disk I/O driver;
 - Register the file system object (mount) to the FatFs module for the USB drive;
 - Create and Open new text file object with write access;
 - Write data to the text file;
 - Close the open text file;
 - Unlink the USB Host disk I/O driver.
 
It is worth noting that the application manages any error occurred during the 
access to FAT volume, when using FatFs APIs. Otherwise, user can check if the
written text file is available on the USB disk.

It is possible to fine tune needed FatFs features by modifying defines values 
in FatFs configuration file �ffconf.h� available under the project includes 
directory, in a way to fit the application requirements. 

STM32F723E-DISCOVERY's LEDs can be used to monitor the application status:
  - LED6 is ON when the application runs successfully.
  - LED5 is ON when any error occurs.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

For more details about FatFs implementation on STM32Cube, please refer to UM1721 "Developing Applications 
on STM32Cube with FatFs".

@par Keywords

Connectivity, FatFS, USB_Host, FAT, File system 

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
 
  - FatFs/FatFs_USBDisk/Inc/stm32f7xx_hal_conf.h    HAL configuration file
  - FatFs/FatFs_USBDisk/Inc/stm32f7xx_it.h          Interrupt handlers header file
  - FatFs/FatFs_USBDisk/Inc/main.h                  Main program header file
  - FatFs/FatFs_USBDisk/Inc/ffconf.h                FAT file system module configuration file   
  - FatFs/FatFs_USBDisk/Inc/usbh_diskio.h           USB host diskio header file
  - FatFs/FatFs_USBDisk/Inc/usb_conf.h              USB host low level configuration file
  - FatFs/FatFs_USBDisk/Src/stm32f7xx_it.c          Interrupt handlers
  - FatFs/FatFs_USBDisk/Src/main.c                  Main program
  - FatFs/FatFs_USBDisk/Src/system_stm32f7xx.c      STM32F7xx system clock configuration file
  - FatFs/FatFs_USBDisk/Src/usbh_diskio.c           USB host diskio file
  - FatFs/FatFs_USBDisk/Src/usb_conf.c              USB host low level configuration functions
         
 
@par Hardware and Software environment

  - This application runs on STM32F723xx devices.
    
  - This application has been tested with STMicroelectronics STM32F723E-Discovery 
    boards and can be easily tailored to any other supported device.

  - STM32F723E-Discovery Set-up
    - Plug the USB key into the STM32F723E-Discovery board through 'USB micro A-Male 
      to A-Female' cable to the connector:
      - CN19: to use USB High Speed (HS) 
      - CN18: to use USB Full Speed (FS)     

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - In the workspace toolbar select the project configuration:
   - STM32F723E-Discovery_USBH-HS: to configure the project for STM32F7xx devices using USB OTG HS peripheral
   - STM32F723E-Discovery_USBH-FS: to configure the project for STM32F7xx devices using USB OTG FS peripheral

 - Run the application


 */

