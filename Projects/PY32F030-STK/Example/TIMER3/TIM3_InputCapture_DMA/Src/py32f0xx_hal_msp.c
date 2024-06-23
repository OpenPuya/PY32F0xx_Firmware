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
static DMA_HandleTypeDef  hdma_tim;

/* Private function prototypes -----------------------------------------------*/
/* External functions --------------------------------------------------------*/

/**
  * @brief   Initialize TIM-related MSP
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef   GPIO_InitStruct = {0};
  /* Enable GPIOA clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  /* Enable DMA clock */
  __HAL_RCC_DMA_CLK_ENABLE();
  /* Enable TIM3 clock */
  __HAL_RCC_TIM3_CLK_ENABLE();
  /* Enable SYSCFG clock */
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  
  /* DMA1_MAP selects TIM3_CH1 */
  HAL_SYSCFG_DMA_Req(0x12);
  
  /* Initialize GPIOB4 as TIM3_CH1 */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  hdma_tim.Instance = DMA1_Channel1;                          /* Select DMA channel 1 */
  hdma_tim.Init.Direction = DMA_PERIPH_TO_MEMORY;             /* Direction from peripheral to memory */
  hdma_tim.Init.PeriphInc = DMA_PINC_DISABLE;                 /* Disable peripheral address increment */
  hdma_tim.Init.MemInc = DMA_MINC_DISABLE;                    /* Disable memory address increment */
  hdma_tim.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD ;   /* Peripheral data width is 8 bits */
  hdma_tim.Init.MemDataAlignment = DMA_MDATAALIGN_WORD ;      /* Memory data width is 8 bits */
  hdma_tim.Init.Mode = DMA_CIRCULAR;                          /* Circular mode */
  hdma_tim.Init.Priority = DMA_PRIORITY_VERY_HIGH;            /* Channel priority is very high */
  /* Link DMA with TIM_CC1 event */
  __HAL_LINKDMA(htim, hdma[TIM_DMA_ID_CC1], hdma_tim);
  /* Initialize DMA */
  HAL_DMA_Init(htim->hdma[TIM_DMA_ID_CC1]);
  
  /* Start DMA */
  HAL_DMA_Start(htim->hdma[TIM_DMA_ID_CC1], (uint32_t)&TIM3->CCR1, (uint32_t)&CC1_Capture, 1);
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
