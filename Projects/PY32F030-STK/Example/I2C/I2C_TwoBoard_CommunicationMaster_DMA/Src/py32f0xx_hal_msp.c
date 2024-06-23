/**
  ******************************************************************************
  * @file    py32f0xx_hal_msp.c
  * @author  MCU Application Team
  * @brief   This file provides code for the MSP Initialization
  *          and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static DMA_HandleTypeDef HdmaCh1;
static DMA_HandleTypeDef HdmaCh2;

/* Private function prototypes -----------------------------------------------*/
/* External functions --------------------------------------------------------*/

/**
  * @brief Initialize global MSP
  */
void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}

/**
  * @brief Initialize I2C MSP
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_SYSCFG_CLK_ENABLE();                              /* Enable SYSCFG clock */
  __HAL_RCC_DMA_CLK_ENABLE();                                 /* Enable DMA clock */
  __HAL_RCC_I2C_CLK_ENABLE();                                 /* Enable I2C clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();                               /* Enable GPIOA clock */

  /**I2C GPIO Configuration
  PA9     ------> I2C1_SCL
  PA10     ------> I2C1_SDA
  */
  GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;                     /* Open-drain mode */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                         /* Pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF6_I2C;                   /* Alternate as I2C */
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                     /* Initialize GPIO */
  /* Reset I2C */
  __HAL_RCC_I2C_FORCE_RESET();
  __HAL_RCC_I2C_RELEASE_RESET();

  /* I2C1 interrupt initialization */
  HAL_NVIC_SetPriority(I2C1_IRQn, 0, 0);                     /* Set interrupt priority */
  HAL_NVIC_EnableIRQ(I2C1_IRQn);                              /* Enable I2C interrupt */

  /* Configure DMA request mapping */
  HAL_SYSCFG_DMA_Req(9);                                      /* Set DMA1_MAP to IIC_TX */
  HAL_SYSCFG_DMA_Req(0xA00);                                  /* Set DMA2_MAP to IIC_RX */

  /* Configure DMA */
  /* Configure DMA handle for transmission */
  HdmaCh1.Instance                 = DMA1_Channel1;           /* Select DMA channel 1 */
  HdmaCh1.Init.Direction           = DMA_MEMORY_TO_PERIPH;    /* Memory to peripheral direction */
  HdmaCh1.Init.PeriphInc           = DMA_PINC_DISABLE;        /* Disable peripheral address increment */
  HdmaCh1.Init.MemInc              = DMA_MINC_ENABLE;         /* Enable memory address increment */
  HdmaCh1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;     /* Peripheral data width is 8 bits */
  HdmaCh1.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;     /* Memory data width is 8 bits */
  HdmaCh1.Init.Mode                = DMA_NORMAL;              /* Disable circular mode */
  HdmaCh1.Init.Priority            = DMA_PRIORITY_VERY_HIGH;  /* Channel priority is very high */

  HAL_DMA_Init(&HdmaCh1);                                     /* Initialize DMA channel 1 */
  __HAL_LINKDMA(hi2c, hdmatx, HdmaCh1);                       /* Link DMA1 with IIC_TX */

  /* Configure DMA handle for reception */
  HdmaCh2.Instance                 = DMA1_Channel2;           /* Select DMA channel 1 */
  HdmaCh2.Init.Direction           = DMA_PERIPH_TO_MEMORY;    /* Direction : peripheral to memory */
  HdmaCh2.Init.PeriphInc           = DMA_PINC_DISABLE;        /* Disable peripheral address increment */
  HdmaCh2.Init.MemInc              = DMA_MINC_ENABLE;         /* Enable memory address increment */
  HdmaCh2.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;     /* Peripheral data width is 8 bits */
  HdmaCh2.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;     /* Memory data width is 8 bits */
  HdmaCh2.Init.Mode                = DMA_NORMAL;              /* Disable circular mode */
  HdmaCh2.Init.Priority            = DMA_PRIORITY_HIGH;       /* Channel priority is high */

  HAL_DMA_Init(&HdmaCh2);                                     /* Initialize DMA channel 1 */
  __HAL_LINKDMA(hi2c, hdmarx, HdmaCh2);                       /* Link DMA1 with IIC_RX */

  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 1);             /* Set interrupt priority */
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);                     /* Enable DMA channel 1 interrupt */

  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 1);           /* Set interrupt priority */
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);                   /* Enable DMA channel 2 and 3 interrupt */
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
