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
  * @brief   初始化全局MSP
  */
void HAL_MspInit(void)
{
}

/**
  * @brief   初始化LED相关MSP
  */
void HAL_LED_MspInit(LED_HandleTypeDef *hled)
{
  GPIO_InitTypeDef GPIO_Initure;
  
  /* 开启LED时钟 */
  __HAL_RCC_LED_CLK_ENABLE();
  /* 开启GPIOA时钟 */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  /* 开启GPIOB时钟 */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* 配置PB3、PB4、PB5为com1 2 3 */
  GPIO_Initure.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
  GPIO_Initure.Mode = GPIO_MODE_AF_PP;
  GPIO_Initure.Pull = GPIO_PULLUP;
  GPIO_Initure.Alternate = GPIO_AF6_LED  ;
  GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_Initure);

  /* 配置PA15为com0 */
  GPIO_Initure.Pin = GPIO_PIN_15;
  GPIO_Initure.Mode = GPIO_MODE_AF_PP;
  GPIO_Initure.Pull = GPIO_PULLUP;
  GPIO_Initure.Alternate = GPIO_AF6_LED;
  GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_Initure);

  /* 配置PA0、PA1、PA2、PA3、PA4、PA5、PA6为SEG B C D E F G DP */
  GPIO_Initure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
  GPIO_Initure.Mode = GPIO_MODE_AF_PP;
  GPIO_Initure.Pull = GPIO_PULLUP;
  GPIO_Initure.Alternate = GPIO_AF3_LED  ;
  GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_Initure);

  /* 配置PB8为SEG A */
  GPIO_Initure.Pin = GPIO_PIN_8;
  GPIO_Initure.Mode = GPIO_MODE_AF_PP;
  GPIO_Initure.Pull = GPIO_PULLUP;
  GPIO_Initure.Alternate = GPIO_AF3_LED  ;
  GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_Initure);

  /* 使能LED中断 */
  HAL_NVIC_SetPriority(LED_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(LED_IRQn);
  __HAL_LED_ENABLE_IT(hled, LED_CR_IE);
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
