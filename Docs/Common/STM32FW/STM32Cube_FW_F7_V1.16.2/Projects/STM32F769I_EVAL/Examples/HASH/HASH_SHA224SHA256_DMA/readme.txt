/**
  @page HASH_SHA224SHA256_DMA  HASH digest calculation using SHA224 and SHA256 example
  
  @verbatim
  ******************************************************************************
  * @file    HASH/HASH_SHA224SHA256_DMA/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the digest calculation using HMAC SHA1 and HMAC MD5 Example.
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

How to use the HASH peripheral to hash data with SHA224 and SHA256 algorithms.

In this example, DMA is used to transfer data from internal RAM to HASH peripheral.
The SHA224 message digest length is 28 bytes  and the SHA256 message digest length 
is 32 bytes.

The expected HASH digests (for SHA224 and SHA256) are already computed using an online
HASH tool. Those values are compared to those computed by the HASH peripheral.
In case there is a mismatch the red LED is turned ON.
In case the SHA224 digest is computed correctly the green LED (LED1) is turned ON.
In case the SHA256 digest is computed correctly the blue LED (LED4) is turned ON.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

System, Security, HASH, SHA256, SHA224, digest, DMA

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

  - HASH/HASH_SHA224SHA256_DMA/Inc/stm32f7xx_hal_conf.h    HAL configuration file
  - HASH/HASH_SHA224SHA256_DMA/Inc/stm32f7xx_it.h          Interrupt handlers header file
  - HASH/HASH_SHA224SHA256_DMA/Inc/main.h						 Header for main.c module  
  - HASH/HASH_SHA224SHA256_DMA/Src/stm32f7xx_it.c          Interrupt handlers
  - HASH/HASH_SHA224SHA256_DMA/Src/main.c						 Main program
  - HASH/HASH_SHA224SHA256_DMA/Src/stm32f7xx_hal_msp.c     HAL MSP module
  - HASH/HASH_SHA224SHA256_DMA/Src/system_stm32f7xx.c      STM32F7xx system source file


@par Hardware and Software environment

  - This example runs on STM32F777xx/STM32F779xx devices.
  
  - This example has been tested with STM32F779I_EVAL board and can be
    easily tailored to any other supported device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example 



 */
 