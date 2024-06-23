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

/* Private function prototypes -----------------------------------------------*/
/* External functions --------------------------------------------------------*/

/**
  * @brief Initialize global MSP
  */
void HAL_MspInit(void)
{
}

/**
  * @brief Initialize ADC-related
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef          GPIO_InitStruct={0};

  __HAL_RCC_SYSCFG_CLK_ENABLE();                              /* Enable SYSCFG clock */
  __HAL_RCC_DMA_CLK_ENABLE();                                 /* Enable DMA clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();                               /* Enable GPIOA clock */
 
  /* ------------------------------- */
  /* Configure ADC channel as PA0   */
  /* ------------------------------- */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_SYSCFG_DMA_Req(0);                                      /* Set DMA1 mapping to ADC */
  /* ---------------------- */
  /* DMA configuration      */
  /* ---------------------- */
  HdmaCh1.Instance                 = DMA1_Channel1;           /* Select DMA channel 1 */
  HdmaCh1.Init.Direction           = DMA_PERIPH_TO_MEMORY;    /* Direction: peripheral to memory */
  HdmaCh1.Init.PeriphInc           = DMA_PINC_DISABLE;        /* Disable peripheral address increment */
  HdmaCh1.Init.MemInc              = DMA_MINC_DISABLE;        /* Disable memory address increment */
  HdmaCh1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;     /* Peripheral data width: 32-bit */
  HdmaCh1.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;     /* Memory data width: 32-bit */
  HdmaCh1.Init.Mode                = DMA_CIRCULAR;            /* Circular mode */
  HdmaCh1.Init.Priority            = DMA_PRIORITY_VERY_HIGH;  /* Channel priority: very high */

  HAL_DMA_DeInit(&HdmaCh1);                                   /* Deinitialize DMA channel 1 */
  HAL_DMA_Init(&HdmaCh1);                                     /* Initialize DMA channel 1 */
  __HAL_LINKDMA(hadc, DMA_Handle, HdmaCh1);                   /* Link DMA handle to ADC */
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
