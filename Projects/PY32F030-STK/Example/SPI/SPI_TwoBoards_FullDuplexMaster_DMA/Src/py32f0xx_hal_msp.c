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
  * @brief 初始化SPI的MSP
  */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  /* SPI1 初始化 */
  if (hspi->Instance == SPI1)
  {
    __HAL_RCC_GPIOB_CLK_ENABLE();                   /* GPIOB时钟使能 */
    __HAL_RCC_GPIOA_CLK_ENABLE();                   /* GPIOA时钟使能 */
    __HAL_RCC_SYSCFG_CLK_ENABLE();                  /* 使能SYSCFG时钟 */
    __HAL_RCC_SPI1_CLK_ENABLE();                    /* SPI1时钟使能 */
    __HAL_RCC_DMA_CLK_ENABLE();                     /* DMA时钟使能 */
    HAL_SYSCFG_DMA_Req(1);                          /* SPI1_TX DMA_CH1 */
    HAL_SYSCFG_DMA_Req(0x200);                      /* SPI1_RX DMA_CH2 */
    /*
      PB3-SCK  (AF0)
      PB4-MISO(AF0)
      PB5-MOSI(AF0)
      PA15-NSS(AF0)
    */
    /*SCK*/
    GPIO_InitStruct.Pin       = GPIO_PIN_3;
    if (hspi->Init.CLKPolarity == SPI_POLARITY_LOW)
    {
      GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    }
    else
    {
      GPIO_InitStruct.Pull = GPIO_PULLUP;
    }
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF0_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* SPI NSS*/
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF0_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


    /*GPIO配置为SPI：MISO/MOSI*/
    GPIO_InitStruct.Pin       = GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF0_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    /*中断配置*/
    HAL_NVIC_SetPriority(SPI1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(SPI1_IRQn);
    /*DMA_CH1配置*/
    HdmaCh1.Instance                 = DMA1_Channel1;
    HdmaCh1.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    HdmaCh1.Init.PeriphInc           = DMA_PINC_DISABLE;
    HdmaCh1.Init.MemInc              = DMA_MINC_ENABLE;
    if (hspi->Init.DataSize <= SPI_DATASIZE_8BIT)
    {
      HdmaCh1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
      HdmaCh1.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    }
    else
    {
      HdmaCh1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
      HdmaCh1.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
    }
    HdmaCh1.Init.Mode                = DMA_NORMAL;
    HdmaCh1.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
    /*DMA初始化*/
    HAL_DMA_Init(&HdmaCh1);
    /*DMA句柄关联到SPI句柄*/
    __HAL_LINKDMA(hspi, hdmatx, HdmaCh1);

    /*DMA_CH2配置*/
    HdmaCh2.Instance                 = DMA1_Channel2;
    HdmaCh2.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    HdmaCh2.Init.PeriphInc           = DMA_PINC_DISABLE;
    HdmaCh2.Init.MemInc              = DMA_MINC_ENABLE;
    if (hspi->Init.DataSize <= SPI_DATASIZE_8BIT)
    {
      HdmaCh2.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
      HdmaCh2.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    }
    else
    {
      HdmaCh2.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
      HdmaCh2.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
    }
    HdmaCh2.Init.Mode                = DMA_NORMAL;
    HdmaCh2.Init.Priority            = DMA_PRIORITY_LOW;
    /*DMA初始化*/
    HAL_DMA_Init(&HdmaCh2);
    /*DMA句柄关联到SPI句柄*/
    __HAL_LINKDMA(hspi, hdmarx, HdmaCh2);
    /*DMA中断设置*/
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
    HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
  }
  else if (hspi->Instance == SPI2)
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();                   /* GPIOA时钟使能 */
    __HAL_RCC_GPIOB_CLK_ENABLE();                   /* GPIOB时钟使能 */
    __HAL_RCC_SYSCFG_CLK_ENABLE();                  /* 使能SYSCFG时钟 */
    __HAL_RCC_SPI2_CLK_ENABLE();                    /* SPI2时钟使能 */
    HAL_SYSCFG_DMA_Req(3);                          /* SPI2_TX DMA_CH1 */
    HAL_SYSCFG_DMA_Req(0x00);                       /* SPI2_RX DMA_CH2 */
    /*GPIO配置为SPI：SCK/MISO/MOSI*/
    /*
      PA0-SCK  (AF0)
      PA3-MISO(AF0)
      PB7-MOSI(AF1)
      PB8-NSS  (AF1)
    */
    /*GPIO配置为SPI：SCK*/
    GPIO_InitStruct.Pin       = GPIO_PIN_0;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    if (hspi->Init.CLKPolarity == SPI_POLARITY_LOW)
    {
      GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    }
    else
    {
      GPIO_InitStruct.Pull = GPIO_PULLUP;
    }
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF0_SPI2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*GPIO配置为SPI：MOSI/NSS*/
    GPIO_InitStruct.Pin       = GPIO_PIN_7 | GPIO_PIN_8;
    GPIO_InitStruct.Alternate = GPIO_AF1_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin       = GPIO_PIN_3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(SPI2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(SPI2_IRQn);
    /*DMA_CH1配置*/
    HdmaCh1.Instance                 = DMA1_Channel1;
    HdmaCh1.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    HdmaCh1.Init.PeriphInc           = DMA_PINC_DISABLE;

    HdmaCh1.Init.MemInc              = DMA_MINC_ENABLE;
    if (hspi->Init.DataSize <= SPI_DATASIZE_8BIT)
    {
      HdmaCh1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
      HdmaCh1.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    }
    else
    {
      HdmaCh1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
      HdmaCh1.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
    }
    HdmaCh1.Init.Mode                = DMA_NORMAL;
    HdmaCh1.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
    /*DMA初始化*/
    HAL_DMA_Init(&HdmaCh1);
    /*DMA句柄关联到SPI句柄*/
    __HAL_LINKDMA(hspi, hdmatx, HdmaCh1);

    /*DMA_CH2配置*/
    HdmaCh2.Instance                 = DMA1_Channel2;
    HdmaCh2.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    HdmaCh2.Init.PeriphInc           = DMA_PINC_DISABLE;
    HdmaCh2.Init.MemInc              = DMA_MINC_ENABLE;
    if (hspi->Init.DataSize <= SPI_DATASIZE_8BIT)
    {
      HdmaCh2.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
      HdmaCh2.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    }
    else
    {
      HdmaCh2.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
      HdmaCh2.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
    }
    HdmaCh2.Init.Mode                = DMA_NORMAL;
    HdmaCh2.Init.Priority            = DMA_PRIORITY_HIGH;
    /*DMA初始化*/
    HAL_DMA_Init(&HdmaCh2);
    /*DMA句柄关联到SPI句柄*/
    __HAL_LINKDMA(hspi, hdmarx, HdmaCh2);
    /*DMA中断设置*/
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
    HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
  }
}

/**
  * @brief 反初始化I2C的MSP
  */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
  if (hspi->Instance == SPI1)
  {
    /* 复位SPI外设 */
    __HAL_RCC_SPI1_FORCE_RESET();
    __HAL_RCC_SPI1_RELEASE_RESET();

    /* 关闭外设和GPIO时钟 */
    /* 取消配置SPI SCK*/
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_15);

    HAL_NVIC_DisableIRQ(SPI1_IRQn);

    HAL_DMA_DeInit(&HdmaCh1);
    HAL_NVIC_DisableIRQ(DMA1_Channel1_IRQn);

  }
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
