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
/* Private function prototypes -----------------------------------------------*/
/* External functions --------------------------------------------------------*/

/**
  * @brief 初始化全局MSP
  */
void HAL_MspInit(void)
{

}

/**
  * @brief 初始化COMP相关MSP
  */
void HAL_COMP_MspInit(COMP_HandleTypeDef *hcomp)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();                 /* 使能GPIOA时钟 */
  __HAL_RCC_COMP1_CLK_ENABLE();                 /* 使能COMP1时钟 */
  __HAL_RCC_COMP2_CLK_ENABLE();                 /* 使能COMP2时钟 */

  /* GPIO PA1配置为模拟输入 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;            /* 模拟模式 */
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;               /* 下拉 */
  HAL_GPIO_Init(GPIOA,  &GPIO_InitStruct);            /* GPIO初始化 */

  /* GPIO PA6配置为输出 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;             /* 输出 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;               /* 下拉 */
  GPIO_InitStruct.Alternate = GPIO_AF7_COMP1;         /* 复用为COMP1_OUT */
  HAL_GPIO_Init(GPIOA,  &GPIO_InitStruct);            /* 初始化GPIO */

  HAL_NVIC_EnableIRQ(ADC_COMP_IRQn);            /* 使能COMP中断 */
  HAL_NVIC_SetPriority(ADC_COMP_IRQn, 1, 1);
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
