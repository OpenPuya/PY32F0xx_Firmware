/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
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
#include "py32f030xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
#define I2C_ADDRESS        0xA0     /* 本机\从机地址 */
#define I2C_SPEEDCLOCK     400000   /* 通讯速度400K */
#define I2C_STATE_READY    0        /* 就绪状态 */
#define I2C_STATE_BUSY_TX  1        /* 发送状态 */
#define I2C_STATE_BUSY_RX  2        /* 接收状态 */

#define I2C_MEMADD_SIZE_8BIT            0x00000001U /* 从机内部地址大小为8位 */
#define I2C_MEMADD_SIZE_16BIT           0x00000010U /* 从机内部地址大小为16位 */

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t aTxBuffer[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
uint8_t aRxBuffer[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

uint8_t         *pBuffPtr   = NULL;
__IO uint16_t   XferCount   = 0;
__IO uint32_t   Devaddress  = 0;
__IO uint32_t   State       = I2C_STATE_READY;

/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigI2cMaster(void);
static void APP_MasterTransmit_DMA_MEM(uint16_t DevAddress, uint16_t MemAddress,
  uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
static void APP_MasterReceive_DMA_MEM(uint16_t DevAddress, uint16_t MemAddress,
  uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
static void APP_CheckEndOfTransfer(void);
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength);
static void APP_LedBlinking(void);

/**
  * @brief  应用程序入口函数.
  * @param  无
  * @retval int
  */
int main(void)
{
  /* 配置系统时钟 */
  APP_SystemClockConfig();
  
  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  /* 初始化按键BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);
  
  /* 配置I2C */
  APP_ConfigI2cMaster();

  /*等待按键按下*/
  while(BSP_PB_GetState(BUTTON_KEY) == 1);
  
  /* 主机发送数据 */
  APP_MasterTransmit_DMA_MEM(I2C_ADDRESS, 0x00, I2C_MEMADD_SIZE_16BIT, (uint8_t *)aTxBuffer, sizeof(aTxBuffer));
  
  /* 等待主机发送数据完成 */
  while (State != I2C_STATE_READY);
  
  /* 延时100ms */
  LL_mDelay(100);
  
  /* 主机接收数据 */  
  APP_MasterReceive_DMA_MEM(I2C_ADDRESS, 0x00, I2C_MEMADD_SIZE_16BIT, (uint8_t *)aRxBuffer, sizeof(aRxBuffer));
  
  /* 等待主机接收数据完成 */
  while (State != I2C_STATE_READY);
  
  /* 检查接收到的数据 */
  APP_CheckEndOfTransfer();
  
  while (1)
  {
  }
}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
static void APP_SystemClockConfig(void)
{
  /* 使能HSI */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* 设置 AHB 分频*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* 配置HSISYS作为系统时钟源 */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* 设置 APB1 分频*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);

  /* 更新系统时钟全局变量SystemCoreClock(也可以通过调用SystemCoreClockUpdate函数更新) */
  LL_SetSystemCoreClock(8000000);
}

/**
  * @brief  I2C配置函数
  * @param  无
  * @retval 无
  */
static void APP_ConfigI2cMaster(void)
{
  /* 使能 GPIOA 的外设时钟 */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* 启用 I2C1 的外设时钟 */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
  
  /* 使能DMA时钟 */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
  
  /* 使能SYSCFG时钟 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);

  /* 将 SCL 引脚配置为：可选功能、高速、开漏、上拉 */
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* 将 SDA 引脚配置为：可选功能、高速、开漏、上拉 */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  /* 复位I2C */
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C1);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C1);
  
  /* 使能I2C的NVIC中断 */
  NVIC_SetPriority(I2C1_IRQn, 0);
  NVIC_EnableIRQ(I2C1_IRQn);
  
  /* 配置DMA请求映像 */
  LL_SYSCFG_SetDMARemap_CH1(LL_SYSCFG_DMA_MAP_I2C_TX);
  LL_SYSCFG_SetDMARemap_CH2(LL_SYSCFG_DMA_MAP_I2C_RX);
  
  /* DMA通道1初始化 */
  LL_DMA_InitTypeDef DMA_InitStruct;
  DMA_InitStruct.PeriphOrM2MSrcAddress  = 0x00000000U;
  DMA_InitStruct.MemoryOrM2MDstAddress  = 0x00000000U;
  DMA_InitStruct.Direction              = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  DMA_InitStruct.Mode                   = LL_DMA_MODE_NORMAL;
  DMA_InitStruct.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT;
  DMA_InitStruct.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;
  DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_InitStruct.NbData                 = 0x00000000U;
  DMA_InitStruct.Priority               = LL_DMA_PRIORITY_VERYHIGH;
  LL_DMA_Init(DMA1, LL_DMA_CHANNEL_1, &DMA_InitStruct);
  
  /* DMA通道2初始化 */
  DMA_InitStruct.PeriphOrM2MSrcAddress  = 0x00000000U;
  DMA_InitStruct.MemoryOrM2MDstAddress  = 0x00000000U;
  DMA_InitStruct.Direction              = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
  DMA_InitStruct.Mode                   = LL_DMA_MODE_NORMAL;
  DMA_InitStruct.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT;
  DMA_InitStruct.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;
  DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_InitStruct.NbData                 = 0x00000000U;
  DMA_InitStruct.Priority               = LL_DMA_PRIORITY_HIGH;
  LL_DMA_Init(DMA1, LL_DMA_CHANNEL_2, &DMA_InitStruct);
  
  /* 使能DMA的NVIC中断 */
  NVIC_SetPriority(DMA1_Channel1_IRQn, 1);
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  
  NVIC_SetPriority(DMA1_Channel2_3_IRQn, 1);
  NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
  
  /* I2C初始化 */
  LL_I2C_InitTypeDef I2C_InitStruct;
  I2C_InitStruct.ClockSpeed      = I2C_SPEEDCLOCK;
  I2C_InitStruct.DutyCycle       = LL_I2C_DUTYCYCLE_16_9;
  I2C_InitStruct.OwnAddress1     = I2C_ADDRESS;
  I2C_InitStruct.TypeAcknowledge = LL_I2C_NACK;
  LL_I2C_Init(I2C1, &I2C_InitStruct);
  
  /* 启用时钟拉伸 */
  /* 复位值是启用时钟延长 */
  /* LL_I2C_EnableClockStretching(I2C1); */
  
  /* 启用广播呼叫 */
  /* 复位值为禁用广播呼叫 */
  /* LL_I2C_EnableGeneralCall(I2C1); */
}

/**
  * @brief  I2C发送函数
  * @param  DevAddress：从机地址
  * @param  MemAddress：从机内部地址
  * @param  MemAddSize：从机内部地址大小
  * @param  pData：要发送数据指针
  * @param  Size：要发送数据大小
  * @retval 无
  */
static void APP_MasterTransmit_DMA_MEM(uint16_t DevAddress, uint16_t MemAddress,
  uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
  /* 清pos */
  LL_I2C_DisableBitPOS(I2C1);
  
  /* 将从机地址、要发送数据、数据大小、状态赋给全局变量 */
  pBuffPtr    = pData;
  XferCount   = Size;
  Devaddress  = DevAddress;
  State       = I2C_STATE_BUSY_TX;
  
  /* 使能DMA传输中断 */
  LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
  
  LL_DMA_ClearFlag_GI1(DMA1);
  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, Size);
  uint32_t dataRegAddr = LL_I2C_DMA_GetRegAddr(I2C1);
  LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)pData, dataRegAddr, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
  
  LL_DMA_DisableIT_HT(DMA1, LL_DMA_CHANNEL_1);
  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
  LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_1);
  
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
  
  /* 产生起始位 */
  LL_I2C_GenerateStartCondition(I2C1);
  while(LL_I2C_IsActiveFlag_SB(I2C1) != 1);
  
  /* 发送从机地址 */
  LL_I2C_TransmitData8(I2C1, (Devaddress & (uint8_t)(~0x01)));
  while(LL_I2C_IsActiveFlag_ADDR(I2C1) != 1);
  LL_I2C_ClearFlag_ADDR(I2C1);
  
  /* 发送从机内部地址 */
  while(LL_I2C_IsActiveFlag_TXE(I2C1) != 1);
  if (MemAddSize == I2C_MEMADD_SIZE_8BIT)
  {
    LL_I2C_TransmitData8(I2C1, (MemAddress & 0xFF));
  }
  else
  {
    LL_I2C_TransmitData8(I2C1, ((MemAddress & 0xFF00) >> 8));
    while(LL_I2C_IsActiveFlag_TXE(I2C1) != 1);
    
    LL_I2C_TransmitData8(I2C1, (MemAddress & 0xFF));
  }
  while(LL_I2C_IsActiveFlag_TXE(I2C1) != 1);
  
  /* 使能I2C的ERR中断 */
  LL_I2C_EnableIT_ERR(I2C1);
  
  /* 使能DMA请求 */
  LL_I2C_EnableDMAReq_TX(I2C1);
}

/**
  * @brief  I2C接收函数
  * @param  DevAddress：从机地址
  * @param  MemAddress：从机内部地址
  * @param  MemAddSize：从机内部地址大小
  * @param  pData：要接收数据指针
  * @param  Size：要接收数据大小
  * @retval 无
  */
static void APP_MasterReceive_DMA_MEM(uint16_t DevAddress, uint16_t MemAddress,
  uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
  /* 清pos */
  LL_I2C_DisableBitPOS(I2C1);
  
  /* 将从机地址、要发送数据、数据大小赋给全局变量 */
  pBuffPtr    = pData;
  XferCount   = Size;
  Devaddress  = DevAddress;
  State       = I2C_STATE_BUSY_RX;
  
  /* 使能DMA传输中断 */
  LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
  
  LL_DMA_ClearFlag_GI2(DMA1);
  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, Size);
  uint32_t dataRegAddr = LL_I2C_DMA_GetRegAddr(I2C1);
  LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_2, dataRegAddr, (uint32_t)pData, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
  
  LL_DMA_DisableIT_HT(DMA1, LL_DMA_CHANNEL_2);
  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
  LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_2);
  
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
  
  /* 使能应答 */
  LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
  
  /* 产生起始位 */
  LL_I2C_GenerateStartCondition(I2C1);
  while(LL_I2C_IsActiveFlag_SB(I2C1) != 1);
  
  /* 发送从机地址(写) */
  LL_I2C_TransmitData8(I2C1, (Devaddress & (uint8_t)(~0x01)));
  while(LL_I2C_IsActiveFlag_ADDR(I2C1) != 1);
  LL_I2C_ClearFlag_ADDR(I2C1);
  
  /* 发送从机内部地址 */
  while(LL_I2C_IsActiveFlag_TXE(I2C1) != 1);
  if (MemAddSize == I2C_MEMADD_SIZE_8BIT)
  {
    LL_I2C_TransmitData8(I2C1, (MemAddress & 0xFF));
  }
  else
  {
    LL_I2C_TransmitData8(I2C1, ((MemAddress & 0xFF00) >> 8));
    while(LL_I2C_IsActiveFlag_TXE(I2C1) != 1);
    
    LL_I2C_TransmitData8(I2C1, (MemAddress & 0xFF));
  }
  while(LL_I2C_IsActiveFlag_TXE(I2C1) != 1);
  
  /* 重新产生起始位 */
  LL_I2C_GenerateStartCondition(I2C1);
  while(LL_I2C_IsActiveFlag_SB(I2C1) != 1);
  
  /* 发送从机地址(读) */
  LL_I2C_TransmitData8(I2C1, (Devaddress | 0x1));
  while(LL_I2C_IsActiveFlag_ADDR(I2C1) != 1);
  LL_I2C_ClearFlag_ADDR(I2C1);
  
  if (XferCount == 1U)
  {
    LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
  }
  else
  {
    LL_I2C_EnableLastDMA(I2C1);
  }

  /* 使能I2C的ERR中断 */
  LL_I2C_EnableIT_ERR(I2C1);
  
  /* 使能DMA请求 */
  LL_I2C_EnableDMAReq_RX(I2C1);
}

/**
  * @brief  I2C中断回调函数
  * @param  无
  * @retval 无
  */
void APP_MasterI2cIRQCallback(void)
{
  
  /* 主机发送方向 */
  if (LL_I2C_GetTransferDirection(I2C1) == LL_I2C_DIRECTION_WRITE)
  {
    /* 如果DMA发送正在进行，则不检查BTF 标志 */
    if (LL_I2C_IsEnabledDMAReq_TX(I2C1) != 1)
    {
      /* BTF标志位置位 */
      if ((LL_I2C_IsActiveFlag_BTF(I2C1) == 1) && (LL_I2C_IsEnabledIT_EVT(I2C1) == 1))
      {
        if (XferCount == 0U)
        {
          LL_I2C_DisableIT_EVT(I2C1);
          LL_I2C_DisableIT_ERR(I2C1);
          
          LL_I2C_GenerateStopCondition(I2C1);
          State = I2C_STATE_READY;
        }
      }
    }
  }
  /* 主机接收方向 */
  else
  {
  }
}

/**
  * @brief  DMA中断回调函数
  * @param  无
  * @retval 无
  */
void APP_DmaIRQCallback(void)
{
  /* 发送完成处理 */
  if (State == I2C_STATE_BUSY_TX)
  {
    if ((LL_DMA_IsActiveFlag_TC1(DMA1) == 1) && (LL_DMA_IsEnabledIT_TC(DMA1, LL_DMA_CHANNEL_1) == 1))
    {
      /* 关传输完成中断 */
      LL_DMA_DisableIT_TC(DMA1, LL_DMA_CHANNEL_1);
      LL_DMA_DisableIT_TE(DMA1, LL_DMA_CHANNEL_1);
      
      /* 清传输完成标志位 */
      LL_DMA_ClearFlag_TC1(DMA1);
      
      /* 屏蔽I2C的EVT和ERR中断 */
      LL_I2C_DisableIT_EVT(I2C1);
      LL_I2C_DisableIT_ERR(I2C1);
      
      /* 屏蔽I2C的DMA请求 */
      LL_I2C_DisableDMAReq_TX(I2C1);
      
      XferCount = 0U;
      
      /* 使能I2C的EVT和ERR中断 */
      LL_I2C_EnableIT_EVT(I2C1);
      LL_I2C_EnableIT_ERR(I2C1);
    }
  }
  /* 接收完成处理 */
  else
  {
    if ((LL_DMA_IsActiveFlag_TC2(DMA1) == 1) && (LL_DMA_IsEnabledIT_TC(DMA1, LL_DMA_CHANNEL_2) == 1))
    {
      /* 关传输完成中断 */
      LL_DMA_DisableIT_TC(DMA1, LL_DMA_CHANNEL_2);
      LL_DMA_DisableIT_TE(DMA1, LL_DMA_CHANNEL_2);
      
      /* 清传输完成标志位 */
      LL_DMA_ClearFlag_TC2(DMA1);
      
      /* 屏蔽I2C的EVT和ERR中断 */
      LL_I2C_DisableIT_EVT(I2C1);
      LL_I2C_DisableIT_ERR(I2C1);
      
      /* 传输完成时I2C处理 */
      if (XferCount == (uint16_t)1)
      {
        LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
      }
      LL_I2C_GenerateStopCondition(I2C1);
      LL_I2C_DisableLastDMA(I2C1);
      LL_I2C_DisableDMAReq_RX(I2C1);
      XferCount = 0U;
      State = I2C_STATE_READY;
    }
  }
}

/**
  * @brief  校验数据函数
  * @param  无
  * @retval 无
  */
static void APP_CheckEndOfTransfer(void)
{
  /* 比较发送数据和接收数据 */
  if(APP_Buffercmp8((uint8_t*)aTxBuffer, (uint8_t*)aRxBuffer, sizeof(aRxBuffer)))
  {
    /* 错误处理 */
    APP_LedBlinking();
  }
  else
  {
    /* 如果数据接收到，则打开 LED */
    BSP_LED_On(LED_GREEN);
  }
}

/**
  * @brief  字符比较函数
  * @param  pBuffer1：待比较缓冲区1
  * @param  pBuffer2：待比较缓冲区2
  * @param  BufferLength：待比较字符的个数
  * @retval 0：比较值相同；1：比较值不同
  */
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}

/**
  * @brief  LED灯闪烁
  * @param  无
  * @retval 无
  */
static void APP_LedBlinking(void)
{
  while (1)
  {
    BSP_LED_Toggle(LED_GREEN);
    LL_mDelay(500);
  }
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void APP_ErrorHandler(void)
{
  /* 无限循环 */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  输出产生断言错误的源文件名及行号
  * @param  file：源文件名指针
  * @param  line：发生断言错误的行号
  * @retval 无
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* 用户可以根据需要添加自己的打印信息,
     例如: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* 无限循环 */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
