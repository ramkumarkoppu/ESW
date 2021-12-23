/**
  @page CDC_RNDIS HTTP Server Application

  @verbatim
  ******************** (C) COPYRIGHT 2019 STMicroelectronics *******************
  * @file    USB_Device/CDC_RNDIS_Server/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the LwIP http server over USB.
  ******************************************************************************
  *
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @endverbatim

@par Application Description

This application guides STM32Cube HAL API users to run an http server application
(through LwIP TCP/IP) stack over USB interface.
The communication is achieved with a web browser application on a connected host PC.
The STM32 device is connected to a USB Host (ie. PC) and behaves as network device using
the CDC RNDIS interface protocol. From the host point of view, the STM32 is seen as an HTTP server
accessed through address 192.168.0.10.

The HTTP server implemented in the STM32 RNDIS application contains three html pages:
  + The first page (home page) is static, it gives information about STM32 device and USB CDC applications.
  + The second page controls the LED on the board (modify the LED toggling speed).
  + The third page is dynamically refreshed (every 1 s), it shows the current status of the push button (pressed/not pressed)

In order to configure correctly the USB Host, following setup must be followed:
  - Deactivate IPv6 and activate IPv4 mode
  - Setup static addresses as follows:
      - Address = 192.168.0.11
      - Network Mask = 255.255.255.0
      - Gateway = 192.168.0.1
  - Automatic DNS and Routing deactivated.
Then, through the internet browser, open the link address 192.168.0.10 and the home page of the STM32 device will be displayed.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

For more details about LwIP and HTTP, refer to UM1713 "STM32Cube interfacing with LwIP and applications"

@par Keywords

Connectivity, USB_Device, USB, RNDIS, HTTP server, CDC, LWIP, TCP/IP, GRUB, DHCP

@par Hardware and Software environment

  - This application runs on STM32F746xx devices.

  - This application has been tested with the following environments:
     - STM32746G-DISCOVERY board
     - Http clients: Firefox Mozilla (v24) or Microsoft Internet Explorer (v8 and later) or Google Chrome (v76)


  - STM32746G-DISCOVERY Set-up
    - Connect the DK board to remote PC (through a USB cable)


  - Remote PC Set-up
    - In most cases, it is sufficient to disable IPv6 from the setting tray and skip steps below.
    - Disable IPv6: Open /etc/default/grub with a text editor, and add "ipv6.disable=1" to GRUB_CMDLINE_LINUX variable
      and  apply the modified GRUB/GRUB2 settings by running sudo update-grub

    - set Linux IP address and mask to 192.168.0.11, 255.255.255.0, 192.168.0.1
      and Set IPv4 to manual mode with DHCP and routing disabled:
      use nmcli con show command to obtain your connection name then run the command:
      nmcli con mod "your connection name" ipv4.addresses "192.168.0.11/24,255.255.255.0" ipv4.gateway "192.168.0.1" ipv4.method "manual"

    - Set Windows 7/10 IP address and mask to 192.168.0.11, 255.255.255.0, 192.168.0.1 manually:
      open Control Panel \ Network and Internet \ Network Connections panel, and with right button click and select properties:
      double click on Internet Protocol version 4(TCP/IPv4) and select "use the following IP address":
      "IP address: 192.168.0.11" "Subnet mask: 255.255.255.0" "Default gateway: 192.168.0.1"

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Check that DK board is connected to a remote PC before running the application
 - Run the application


 */
