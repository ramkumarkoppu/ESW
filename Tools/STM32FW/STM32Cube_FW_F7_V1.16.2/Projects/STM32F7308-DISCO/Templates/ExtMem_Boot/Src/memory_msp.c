/**
  ******************************************************************************
  * @file    Templates/ExtMem_Boot/Src/memory_msp.c
  * @author  MCD Application Team
  * @brief   External memory code execution MSP module.
  ******************************************************************************
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
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "memory.h"
#include "memory_msp.h"

/** @addtogroup MEMORY
  * @{
  */

/** @defgroup MEMORY
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup MEMORY_MSP_Private_Functions
  * @{
  */
  
#if (CODE_AREA == USE_QSPI) || (CODE_AREA == USE_SPI_NOR)
/**
  * @brief QSPI MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - NVIC configuration for QSPI interrupt
  * @retval None
  */
void QSPI_MspInit(void)
{
  GPIO_InitTypeDef gpio_init_structure;  

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable the QuadSPI memory interface clock */
  __HAL_RCC_QSPI_CLK_ENABLE();
  /* Reset the QuadSPI memory interface */
  __HAL_RCC_QSPI_FORCE_RESET();
  __HAL_RCC_QSPI_RELEASE_RESET();
  /* Enable GPIO clocks */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*##-2- Configure peripheral GPIO ##########################################*/
  /* QSPI CS GPIO pin configuration  */
  gpio_init_structure.Pin       = GPIO_PIN_6;
  gpio_init_structure.Alternate = GPIO_AF10_QUADSPI;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &gpio_init_structure);

  /* QSPI CLK GPIO pin configuration  */
  gpio_init_structure.Pin       = GPIO_PIN_2;
  gpio_init_structure.Alternate = GPIO_AF9_QUADSPI;
  gpio_init_structure.Pull      = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &gpio_init_structure);

  /* QSPI D0 GPIO pin configuration  */
  gpio_init_structure.Pin       = GPIO_PIN_9;
  HAL_GPIO_Init(GPIOC, &gpio_init_structure);
#if (CODE_AREA == USE_QSPI)
  /* QSPI D1 GPIO pin configuration  */
  gpio_init_structure.Pin       = GPIO_PIN_10;
  HAL_GPIO_Init(GPIOC, &gpio_init_structure);
  /* QSPI D2 GPIO pin configuration  */
  gpio_init_structure.Pin       = GPIO_PIN_2;
  HAL_GPIO_Init(GPIOE, &gpio_init_structure);
  /* QSPI D3 GPIO pin configuration  */
  gpio_init_structure.Pin       = GPIO_PIN_13;
  HAL_GPIO_Init(GPIOD, &gpio_init_structure);
#endif
}
#endif

#if (DATA_AREA == USE_EXTERNAL_PSRAM) || (CODE_AREA == USE_EXTERNAL_PSRAM)
/**
  * @brief  Initializes PSRAM MSP.
  * @retval None
  */
void PSRAM_MspInit(void)
{  
  GPIO_InitTypeDef gpio_init_structure;  

  /* Enable FMC clock */
  __HAL_RCC_FMC_CLK_ENABLE();

  /* Enable GPIOs clock */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /* Common GPIO configuration */
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF12_FMC;

  /* GPIOD configuration: GPIO_PIN_7 is  FMC_NE1 , GPIO_PIN_11 ans GPIO_PIN_12 are PSRAM_A16 and PSRAM_A17 */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7 | GPIO_PIN_8 |\
                              GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOD, &gpio_init_structure);
  
  /* GPIOE configuration */  
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |\
                              GPIO_PIN_12 |GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &gpio_init_structure);
  
  /* GPIOF configuration */  
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |\
                              GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15; 
  HAL_GPIO_Init(GPIOF, &gpio_init_structure);

  /* GPIOG configuration */  
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |\
                              GPIO_PIN_5; 
  HAL_GPIO_Init(GPIOG, &gpio_init_structure);

}
#endif /*(DATA_AREA == USE_EXTERNAL_PSRAM) || (CODE_AREA == USE_EXTERNAL_PSRAM)*/

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


