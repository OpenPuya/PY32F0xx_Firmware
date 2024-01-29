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
/* Private function prototypes -----------------------------------------------*/
/* External functions --------------------------------------------------------*/

/**
  * @brief 初始化全局MSP
  */
void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}

/**
  * @brief 初始化COMP相关MSP
  */
void HAL_COMP_MspInit(COMP_HandleTypeDef *hcomp)
{
  __HAL_RCC_GPIOA_CLK_ENABLE();                 /* 使能GPIOA时钟 */
  __HAL_RCC_COMP1_CLK_ENABLE();                 /* 使能COMP1时钟 */
  __HAL_RCC_COMP2_CLK_ENABLE();                 /* 使能COMP2时钟 */
  /* GPIOPA1配置为模拟输入 */
  GPIO_InitTypeDef COMPINPUT;                   
  COMPINPUT.Pin = GPIO_PIN_1;                    
  COMPINPUT.Mode = GPIO_MODE_ANALOG;            /* 模拟模式 */
  COMPINPUT.Speed = GPIO_SPEED_FREQ_HIGH;       
  COMPINPUT.Pull = GPIO_PULLDOWN;               /* 下拉 */
  HAL_GPIO_Init(GPIOA,  &COMPINPUT);            /* GPIO初始化 */
  
  /* GPIOPA6配置为输出 */
  COMPINPUT.Pin = GPIO_PIN_6|GPIO_PIN_7;                   
  COMPINPUT.Mode = GPIO_MODE_AF_PP;             /* 输出 */
  COMPINPUT.Speed = GPIO_SPEED_FREQ_HIGH;
  COMPINPUT.Pull = GPIO_PULLDOWN;               /* 下拉 */
  COMPINPUT.Alternate = GPIO_AF7_COMP1;         /* 复用为COM1_OUT */
  HAL_GPIO_Init(GPIOA,  &COMPINPUT);            /* 初始化GPIO */
  HAL_NVIC_EnableIRQ(ADC_COMP_IRQn);            /* 使能COMP中断 */
  HAL_NVIC_SetPriority(ADC_COMP_IRQn, 1, 1); 
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
