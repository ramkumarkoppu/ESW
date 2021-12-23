/**
  @page MSC_RTOS USB Host Mass Storage (MSC) RTOS application
  
  @verbatim
  ******************** (C) COPYRIGHT 2018 STMicroelectronics *******************
  * @file    USB_Host/MSC_RTOS/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the USB Host MSC RTOS application.
  ******************************************************************************
  *
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @endverbatim

@par Application Description

This application is a part of the USB Host Library package using STM32Cube firmware. It describes how to use
USB host application based on the Mass Storage Class (MSC) on the STM32F730xx devices in RTOS mode
configuration.

In this application, the code is executed from QSPI external memory while data are in internal
SRAM memory.

This is a typical application on how to use the STM32F730xx USB OTG Host peripheral to operate with an USB 
flash disk using the Bulk Only Transfer (BOT) and Small Computer System Interface (SCSI) transparent
commands combined with a file system FatFs (Middleware component).

At the beginning of the main program the HAL_Init() function is called to reset all the peripherals,
initialize the Flash interface and the systick. The user is provided with the SystemClock_Config()
function to configure the system clock (SYSCLK) to run at 216 MHz. The Full Speed (FS) USB module uses
internally a 48-MHz clock which is coming from the main PLL.

When the application is started, the connected USB flash disk device is detected in MSC mode and gets 
initialized. The STM32 MCU behaves as a MSC Host, it enumerates the device and extracts VID, PID, 
manufacturer name, Serial no and product name information and displays it on the LCD screen. 
This application is based on read/write file and explore the USB flash disk content. It creates a normal
priority thread, that executes a MSC routine.

A menu is displayed and the user can select any operation from the menu using the Touch Screen:
 - "File Operations" operation writes a small text file (less to 1 KB) on the USB flash disk.
 - "Explorer Disk" operation explores the USB flash disk content and displays it on the LCD screen.
    User has to press the Key button to display the whole USB flash disk content (recursion level 2).
 - "Re-Enumerate" operation performs a new Enumeration of the device.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in HAL time base ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the HAL time base interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the HAL time base interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the HAL time base is always set to 1 millisecond
      to have correct HAL operation.
	  
@note The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set according 
      to the OS resources memory requirements of the application with +10% margin and rounded to 
	  the upper Kbyte boundary.

      
For more details about the STM32Cube USB Host library, please refer to UM1720  
"STM32Cube USB Host library".


@par USB Library Configuration

To select the appropriate USB Core to work with, user must add the following macro defines within the
compiler preprocessor (already done in the preconfigured projects provided with this application):
      - "USE_USB_HS" when using USB High Speed (HS) Core
      - "USE_USB_FS" when using USB Full Speed (FS) Core

It is possible to fine tune needed USB Host features by modifying defines values in USBH configuration
file �usbh_conf.h� available under the project includes directory, in a way to fit the application
requirements, such as:
  - Level of debug: USBH_DEBUG_LEVEL
                  0: No debug messages
                  1: Only User messages are shown
                  2: User and Error messages are shown
                  3: All messages and internal debug messages are shown
   By default debug messages are displayed on the debugger IO terminal; to redirect the Library
   messages on the LCD screen, lcd_log.c driver need to be added to the application sources.

Since this is an RTOS based application, built around FreeRTOS and CMSIS-OS wrapping layer common APIs,
the RTOS is enabled by setting, #define USBH_USE_OS      1

@par Keywords

Connectivity, USB_Host, USB, MSC, Mass Storage, Full Speed, High Speed, BOT, SCSI, Removable drive, FatFs,
File system, Write, Read, Format, FreeRTOS

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

  - USB_Host/MSC_RTOS/Src/main.c                       Main program
  - USB_Host/MSC_RTOS/Src/usbh_diskio_dma.c            FatFS usbh diskio driver implementation
  - USB_Host/MSC_RTOS/Src/system_STM32f7xx.c           STM32F7xx system clock configuration file
  - USB_Host/MSC_RTOS/Src/STM32f7xx_it.c               Interrupt handlers
  - USB_Host/MSC_RTOS/Src/stm32f7xx_hal_timebase_tim.c HAL TIM base functions
  - USB_Host/MSC_RTOS/Src/menu.c                       MSC State Machine
  - USB_Host/MSC_RTOS/Src/usbh_conf.c                  General low level driver configuration
  - USB_Host/MSC_RTOS/Src/explorer.c                   Explore the USB flash disk content
  - USB_Host/MSC_RTOS/Src/file_operations.c            Write/read file on the disk
  - USB_Host/MSC_RTOS/Src/ts_calibration.c             touchscreen calibration functions
  - USB_Host/MSC_RTOS/Inc/main.h                       Main program header file
  - USB_Host/MSC_RTOS/Inc/usbh_diskio_dma.h            FatFS usbh diskio driver header file
  - USB_Host/MSC_RTOS/Inc/STM32f7xx_it.h               Interrupt handlers header file
  - USB_Host/MSC_RTOS/Inc/lcd_log_conf.h               LCD log configuration file
  - USB_Host/MSC_RTOS/Inc/STM32f7xx_hal_conf.h         HAL configuration file
  - USB_Host/MSC_RTOS/Inc/usbh_conf.h                  USB Host driver Configuration file
  - USB_Host/MSC_RTOS/Inc/ffconf.h                     FatFs Module Configuration file
  - USB_Host/MSC_RTOS/Inc/FreeRTOSConfig.h             FreeRTOS configuration file

@par Hardware and Software environment

  - This application runs on STM32F730xx devices.
    
  - This application has been tested with STMicroelectronics STM32F7308-DISCO
    boards and can be easily tailored to any other supported device 
    and development board.

  - STM32F7308-DISCO Set-up
    - Plug the USB key into the STM32F7308-DISCO board through 'USB micro A-Male 
      to A-Female' cable to the connector:
      - CN18: to use USB Full Speed (FS)
      - CN19 : to use USB High Speed (HS) 

@par How to use it ?

In order to make the program work, you must do the following:

  1. Select required configuration in memory.h in Templates\ExtMem_Boot\Inc.
  2. Program the internal Flash with the ExtMem_Boot (see below).
  3. Program the external QSPI memory with this application (see below).
  4. Start debugging user application or reset for free running.

In order to load the ExtMem_Boot code :
   - Open your preferred toolchain :
      - Open the Project
      - Rebuild all files
      - Load project image

In order to load this application to the external memory:
   - Open your preferred toolchain
      - Open the Project
      - In the workspace toolbar select the project configuration:
        - STM32FF7308-DISCO_USBH-HS: to configure the project for STM32F730xx devices using USB OTG HS peripheral
        - STM32FF7308-DISCO_USBH-FS: to configure the project for STM32F730xx devices using USB OTG FS peripheral
      - Rebuild all files:
      - Run & debug the program:
      - For an XiP configuration (eXecute in Place from QSPI):
          - Using EWARM or MDK-ARM : Load project image from the IDE: Project->Debug
          - Using SW4STM32 :
            - Open the STM32CubeProgrammer tool
            - Select the QSPI external flash loader "MX25L512G_STM32F7308-DISCO"
            - From Erasing & Programming menu, browse and open the output binary file relative to your application
            - Load the file into the external QSPI flash using "Start Programming" at the address APPLICATION_ADDRESS (0x90000000)

 

 */
