/**
  ******************************************************************************
  * @file    py32f0xx_hal_msp.c
  * @author  MCU Application Team
  * @brief   This file provides code for the MSP Initialization
  *          and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
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
static DMA_HandleTypeDef  hdma_tim;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* External functions --------------------------------------------------------*/

/**
  * @brief 初始化全局MSP
  */
void HAL_MspInit(void)
{
}

/**
  * @brief 初始TIM相关MSP
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  __HAL_RCC_DMA_CLK_ENABLE();                                 /* DMA时钟使能 */
  __HAL_RCC_TIM1_CLK_ENABLE();                                /* TIM1时钟使能 */
  __HAL_RCC_SYSCFG_CLK_ENABLE();                              /* SYSCFG时钟使能 */
  HAL_SYSCFG_DMA_Req(0x10);                                   /* DMA1_MAP 选择TIM1_UP */

  hdma_tim.Instance = DMA1_Channel1;                          /* 选择DMA通道1 */
  hdma_tim.Init.Direction = DMA_MEMORY_TO_PERIPH;             /* 方向为从存储器到外设 */
  hdma_tim.Init.PeriphInc = DMA_PINC_DISABLE;                 /* 禁止外设地址增量 */
  hdma_tim.Init.MemInc = DMA_MINC_ENABLE;                     /* 使能存储器地址增量 */
  hdma_tim.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD ;   /* 外设数据宽度为8位 */
  hdma_tim.Init.MemDataAlignment = DMA_MDATAALIGN_WORD ;      /* 存储器数据宽度位8位 */
  hdma_tim.Init.Mode = DMA_NORMAL;                            /* 禁止循环模式 */
  hdma_tim.Init.Priority = DMA_PRIORITY_VERY_HIGH;            /* 通道优先级为很高 */
  HAL_NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 0, 0);       /* 设置中断优先级 */
  HAL_NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);               /* 使能TIM1中断 */

  __HAL_LINKDMA(htim, hdma[TIM_DMA_ID_UPDATE], hdma_tim);     /* DMA1关联TIM_UP事件 */
  HAL_DMA_Init(htim->hdma[TIM_DMA_ID_UPDATE]);                /* DMA初始化 */
  
  /*启动DMA*/
  HAL_DMA_Start(htim->hdma[TIM_DMA_ID_UPDATE], (uint32_t)&Arr_DMA, (uint32_t)&TIM1->ARR, 3);
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
