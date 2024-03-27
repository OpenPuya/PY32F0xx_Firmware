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
  * @brief   Initialize global MSP
  */
void HAL_MspInit(void)
{
}

/**
  * @brief   Initialize TIM-related MSP
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  /* Enable DMA clock */
  __HAL_RCC_DMA_CLK_ENABLE();
  /* Enable TIM1 clock */
  __HAL_RCC_TIM1_CLK_ENABLE();
  /* Enable SYSCFG clock */
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  /* Select TIM1_UP as DMA1 mapping */
  HAL_SYSCFG_DMA_Req(0x10);

  hdma_tim.Instance = DMA1_Channel1;                          /* Select DMA channel 1 */
  hdma_tim.Init.Direction = DMA_MEMORY_TO_PERIPH;             /* Set direction from memory to peripheral */
  hdma_tim.Init.PeriphInc = DMA_PINC_DISABLE;                 /* Disable peripheral address increment */
  hdma_tim.Init.MemInc = DMA_MINC_ENABLE;                     /* Enable memory address increment */
  hdma_tim.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD ;   /* Set peripheral data width to 8 bits */
  hdma_tim.Init.MemDataAlignment = DMA_MDATAALIGN_WORD ;      /* Set memory data width to 8 bits */
  hdma_tim.Init.Mode = DMA_NORMAL;                            /* Disable circular mode */
  hdma_tim.Init.Priority = DMA_PRIORITY_VERY_HIGH;            /* Set channel priority to very high */
  HAL_NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 0, 0);       /* Set interrupt priority */
  HAL_NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);               /* Enable TIM1 interrupt */

  /* Link DMA1 with TIM_UP event */
  __HAL_LINKDMA(htim, hdma[TIM_DMA_ID_UPDATE], hdma_tim);
  /* Initialize DMA */
  HAL_DMA_Init(htim->hdma[TIM_DMA_ID_UPDATE]);
}
