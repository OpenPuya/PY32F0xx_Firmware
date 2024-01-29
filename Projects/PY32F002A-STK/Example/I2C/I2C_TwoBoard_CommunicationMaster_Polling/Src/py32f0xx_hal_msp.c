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

/**
  * @brief 初始化全局MSP
  */
void HAL_MspInit(void)
{
 BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
}

/**
  * @brief 初始化I2C相关MSP
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_SYSCFG_CLK_ENABLE();                              /*SYSCFG时钟使能*/
  __HAL_RCC_I2C_CLK_ENABLE();                                 /*I2C时钟使能*/
  __HAL_RCC_GPIOA_CLK_ENABLE();                               /*GPIOA时钟使能*/

  /**I2C GPIO Configuration
  PA3     ------> I2C1_SCL
  PA2     ------> I2C1_SDA
  */
  GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;                     /*开漏*/
  GPIO_InitStruct.Pull = GPIO_PULLUP;                         /*上拉*/
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_I2C;                   /*复用为I2C*/
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                     /*GPIO初始化*/
  /*复位I2C*/
  __HAL_RCC_I2C_FORCE_RESET();
  __HAL_RCC_I2C_RELEASE_RESET();

  /* I2C1 interrupt Init */
  HAL_NVIC_SetPriority(I2C1_IRQn, 0, 0);                     /*中断优先级设置*/
  HAL_NVIC_EnableIRQ(I2C1_IRQn);                              /*使能I2C中断*/
}

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
