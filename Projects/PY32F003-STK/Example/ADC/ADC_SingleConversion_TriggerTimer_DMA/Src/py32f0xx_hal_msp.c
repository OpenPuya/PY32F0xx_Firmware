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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
DMA_HandleTypeDef HdmaCh1;
extern uint32_t   aADCxConvertedData;

/* Private function prototypes -----------------------------------------------*/
/* External functions --------------------------------------------------------*/

/**
  * @brief 初始化全局MSP
  */
void HAL_MspInit(void)
{
}

/**
  * @brief 初始化ADC相关MSP
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef          GPIO_InitStruct;
  __HAL_RCC_SYSCFG_CLK_ENABLE();                              /* SYSCFG时钟使能 */
  __HAL_RCC_DMA_CLK_ENABLE();                                 /* DMA时钟使能 */
  __HAL_RCC_GPIOA_CLK_ENABLE();                               /* 使能GPIOA时钟 */
  __HAL_RCC_ADC_CLK_ENABLE();                                 /* 使能ADC时钟 */

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_SYSCFG_DMA_Req(0);                                      /* DMA1_MAP选择为ADC */

  HdmaCh1.Instance                 = DMA1_Channel1;           /* 选择DMA通道1 */
  HdmaCh1.Init.Direction           = DMA_PERIPH_TO_MEMORY;    /* 方向为从外设到存储器 */
  HdmaCh1.Init.PeriphInc           = DMA_PINC_DISABLE;        /* 禁止外设地址增量 */
  HdmaCh1.Init.MemInc              = DMA_MINC_DISABLE;        /* 使能存储器地址增量 */
  HdmaCh1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD; /* 外设数据宽度为16位 */
  HdmaCh1.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD; /* 存储器数据宽度位16位 */
  HdmaCh1.Init.Mode                = DMA_CIRCULAR;            /* 循环模式 */
  HdmaCh1.Init.Priority            = DMA_PRIORITY_VERY_HIGH;  /* 通道优先级为很高 */

  HAL_DMA_DeInit(&HdmaCh1);                                   /* DMA反初始化 */
  HAL_DMA_Init(&HdmaCh1);                                     /* 初始化DMA通道1 */
  __HAL_LINKDMA(hadc, DMA_Handle, HdmaCh1);                   /* 连接DMA句柄 */
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
