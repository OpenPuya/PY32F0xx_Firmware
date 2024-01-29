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
#include "py32f002xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
#define I2C_ADDRESS        0xA0     /* 本机\从机地址 */
#define I2C_SPEEDCLOCK     100000   /* 通讯速度100K */
#define I2C_STATE_READY    0        /* 就绪状态 */
#define I2C_STATE_BUSY_TX  1        /* 发送状态 */
#define I2C_STATE_BUSY_RX  2        /* 接收状态 */

/* Private variables ---------------------------------------------------------*/
uint8_t aTxBuffer[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
uint8_t aRxBuffer[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

uint8_t         *pBuffPtr   = NULL;
__IO uint16_t   XferCount   = 0;
__IO uint32_t   State       = I2C_STATE_READY;
/* Private function prototypes -----------------------------------------------*/
void APP_SystemClockConfig(void);
static void APP_ConfigI2cSlave(void);
static void APP_SlaveTransmit_IT(uint8_t *pData, uint16_t Size);
static void APP_SlaveReceive_IT(uint8_t *pData, uint16_t Size);
/**
  * @brief  应用程序入口函数.
  * @param  无
  * @retval int
  */
int main(void)
{
  /* 配置系统时钟 */
  APP_SystemClockConfig();

 /* 配置I2C */
  APP_ConfigI2cSlave();
  
  /* 从机接收数据 */
  APP_SlaveReceive_IT((uint8_t *)aRxBuffer, sizeof(aRxBuffer));
  
  /* 等待从机接收数据完成 */
  while (State != I2C_STATE_READY);
  
  /* 从机发送数据 */
  APP_SlaveTransmit_IT((uint8_t *)aTxBuffer, sizeof(aTxBuffer));
  
  /* 等待从机发送数据完成 */
  while (State != I2C_STATE_READY);
  
  while (1)
  {

  }
}


/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
void APP_SystemClockConfig(void)
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
static void APP_ConfigI2cSlave(void)
{
    /* 使能 GPIOA 的外设时钟 */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* 启用 I2C1 的外设时钟 */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

  /* 将 SCL 引脚配置为：可选功能、高速、开漏、上拉 */
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_12;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* 将 SDA 引脚配置为：可选功能、高速、开漏、上拉 */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_12;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  /* 复位I2C */
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C1);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C1);
  
  /* 使能NVIC中断 */
  NVIC_SetPriority(I2C1_IRQn, 0);
  NVIC_EnableIRQ(I2C1_IRQn);
  
  /* I2C初始化 */
  LL_I2C_InitTypeDef I2C_InitStruct;
  I2C_InitStruct.ClockSpeed      = I2C_SPEEDCLOCK;
  I2C_InitStruct.DutyCycle       = LL_I2C_DUTYCYCLE_16_9;
  I2C_InitStruct.OwnAddress1     = I2C_ADDRESS;
  I2C_InitStruct.TypeAcknowledge = LL_I2C_NACK;
  LL_I2C_Init(I2C1, &I2C_InitStruct);
  
  /* 启用时钟拉伸 */
  /* 复位值是启用时钟延长 */
  /*LL_I2C_EnableClockStretching(I2C1);*/
  
  /* 启用广播呼叫 */
  /* 复位值为禁用广播呼叫 */
  /*LL_I2C_EnableGeneralCall(I2C1);*/
}

/**
  * @brief  I2C发送函数
  * @param  DevAddress：从机地址；
**          pData：要发送数据指针；
**          Size：要发送数据大小
  * @retval 无
  */
static void APP_SlaveTransmit_IT(uint8_t *pData, uint16_t Size)
{
 /* 清pos */
  LL_I2C_DisableBitPOS(I2C1);
  
  /*要发送数据、数据大小、状态赋给全局变量 */
  pBuffPtr    = pData;
  XferCount   = Size;
  State       = I2C_STATE_BUSY_TX;
  
  /* 使能应答 */
  LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
  
  /* 使能中断 */
  LL_I2C_EnableIT_EVT(I2C1);
  LL_I2C_EnableIT_BUF(I2C1);
  LL_I2C_EnableIT_ERR(I2C1);
}
/**
  * @brief  I2C接收函数
  * @param  DevAddress：从机地址；
**          pData：要发送数据指针；
**          Size：要发送数据大小
  * @retval 无
  */
static void APP_SlaveReceive_IT(uint8_t *pData, uint16_t Size)
{
  /* 清pos */
  LL_I2C_DisableBitPOS(I2C1);
  
  /* 要发送数据、数据大小赋给全局变量 */
  pBuffPtr    = pData;
  XferCount   = Size;
  State       = I2C_STATE_BUSY_RX;
  
  /* 使能应答 */
  LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
  
  /* 使能中断 */
  LL_I2C_EnableIT_EVT(I2C1);
  LL_I2C_EnableIT_BUF(I2C1);
  LL_I2C_EnableIT_ERR(I2C1);
}

/**
  * @brief  I2C中断回调函数
  * @param  无
  * @retval 无
  */
void APP_SlaveIRQCallback(void)
{
  /* ADDR标志位置位 */
  if ((LL_I2C_IsActiveFlag_ADDR(I2C1) == 1) && (LL_I2C_IsEnabledIT_EVT(I2C1) == 1))
  {
    LL_I2C_ClearFlag_ADDR(I2C1);
  }
  /* STOPF 标志位置位 */
  else if (LL_I2C_IsActiveFlag_STOP(I2C1) == 1)
  {
    LL_I2C_DisableIT_EVT(I2C1);
    LL_I2C_DisableIT_BUF(I2C1);
    LL_I2C_DisableIT_ERR(I2C1);
    
    LL_I2C_ClearFlag_STOP(I2C1);
    
    LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
    
    /* 数据未全部接收，接收数据失败 */
    if (XferCount != 0U)
    {
      if ((LL_I2C_IsActiveFlag_BTF(I2C1) == 1))
      {
        *pBuffPtr = LL_I2C_ReceiveData8(I2C1);
        pBuffPtr++;
        XferCount--;
      }
      
      if ((LL_I2C_IsActiveFlag_RXNE(I2C1) == 1))
      {
        *pBuffPtr = LL_I2C_ReceiveData8(I2C1);
        pBuffPtr++;
        XferCount--;
      }
      if (XferCount != 0U)
      {
        /* 数据接收失败处理 */
      }
    }
    
    if (State == I2C_STATE_BUSY_RX)
    {
       State = I2C_STATE_READY;
    }
  }
  /* 从机发送 */
  else if (State == I2C_STATE_BUSY_TX)
  {
    /* TXE标志位置位，BTF标志位未置位 */
    if ((LL_I2C_IsActiveFlag_TXE(I2C1) == 1) && (LL_I2C_IsEnabledIT_BUF(I2C1) == 1) && (LL_I2C_IsActiveFlag_BTF(I2C1) == 0))
    {
      if (XferCount != 0)
      {
        LL_I2C_TransmitData8(I2C1, *pBuffPtr);
        pBuffPtr++;
        XferCount--;
      }
    }
    /* BTF标志位置位 */
    else if ((LL_I2C_IsActiveFlag_BTF(I2C1) == 1) && (LL_I2C_IsEnabledIT_EVT(I2C1) == 1))
    {
      if (XferCount != 0)
      {
        LL_I2C_TransmitData8(I2C1, *pBuffPtr);
        pBuffPtr++;
        XferCount--;
      }
    }
  }
  /* 从机接收 */
  else
  {
    /* RXNE标志位置位，BTF标志位未置位 */
    if ((LL_I2C_IsActiveFlag_RXNE(I2C1) == 1) && (LL_I2C_IsEnabledIT_BUF(I2C1) == 1) && (LL_I2C_IsActiveFlag_BTF(I2C1) == 0))
    {
      if (XferCount != 0U)
      {
        *pBuffPtr = LL_I2C_ReceiveData8(I2C1);
        pBuffPtr++;
        XferCount--;
      }
    }
    /* BTF标志位置位 */
    else if ((LL_I2C_IsActiveFlag_BTF(I2C1) == 1) && (LL_I2C_IsEnabledIT_EVT(I2C1) == 1))
    {
      if (XferCount != 0U)
      {
        *pBuffPtr = LL_I2C_ReceiveData8(I2C1);
        pBuffPtr++;
        XferCount--;
      }
    }
  }
}
/**
  * @brief  I2C主机接收完最后一字节后，向从机发送NACK，从机NACK中断回调函数
  * @param  无
  * @retval 无
  */
void APP_SlaveIRQCallback_NACK(void)
{
  if ((LL_I2C_IsActiveFlag_AF(I2C1) == 1) && (LL_I2C_IsEnabledIT_ERR(I2C1) == 1))
  {
    if ((XferCount == 0) && (State == I2C_STATE_BUSY_TX))
    {
      LL_I2C_DisableIT_EVT(I2C1);
      LL_I2C_DisableIT_BUF(I2C1);
      LL_I2C_DisableIT_ERR(I2C1);
      
      LL_I2C_ClearFlag_AF(I2C1);
      
      LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
      
      State = I2C_STATE_READY;
    }
  }
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void Error_Handler(void)
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

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
