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
/* Private variables ---------------------------------------------------------*/
uint8_t aTxBuffer[] = "UART Test";
uint8_t aRxBuffer[30];

uint8_t *TxBuff = NULL;
__IO uint16_t TxSize = 0;
__IO uint16_t TxCount = 0;

uint8_t *RxBuff = NULL;
__IO uint16_t RxSize = 0;
__IO uint16_t RxCount = 0;

__IO ITStatus UartReady = RESET;

/* Private function prototypes -----------------------------------------------*/
void APP_SystemClockConfig(void);
static void APP_ConfigUsart(USART_TypeDef *USARTx);
static void APP_UsartTransmit_IT(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);
static void APP_UsartReceive_IT(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);

/**
  * @brief  应用程序入口函数.
  * @param  无
  * @retval int
  */
int main(void)
{
  /* 配置系统时钟 */
  APP_SystemClockConfig();

  /* USART配置 */
  APP_ConfigUsart(USART1);
  
  /* 发送"UART Test"，并等待发送完成 */
  APP_UsartTransmit_IT(USART1, (uint8_t*)aTxBuffer, sizeof(aTxBuffer)-1);
  while (UartReady != SET)
  {
  }
  UartReady = RESET;

  while (1)
  {
    /* 接收数据 */
    APP_UsartReceive_IT(USART1, (uint8_t *)aRxBuffer, 12);
    while (UartReady != SET)
    {
    }
    UartReady = RESET;
    
    /* 发送数据 */
    APP_UsartTransmit_IT(USART1, (uint8_t*)aRxBuffer, 12);
    while (UartReady != SET)
    {
    }
    UartReady = RESET;
  }
}

/**
  * @brief  USART配置函数.
  * @param  USARTx：USART模块，USART1
  * @retval 无
  */
static void APP_ConfigUsart(USART_TypeDef *USARTx)
{
/*使能时钟、初始化引脚*/
  
  /*使能GPIOA时钟*/
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  /*使能USART1时钟*/
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1);
    
  /*GPIOA配置*/
  LL_GPIO_InitTypeDef GPIO_InitStruct;
  /*选择2号引脚*/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
  /*选择复用模式*/
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  /*选择输出速度*/
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  /*选择输出模式*/
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  /*选择上拉*/
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  /*复用为USART1功能*/
  GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
  /*GPIOA初始化*/
  LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
  /*选择3号引脚*/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
  /*复用为USART1功能*/
  GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
  /*GPIOA初始化*/
  LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
      
  /*设置USART1中断优先级*/
  NVIC_SetPriority(USART1_IRQn,0);
  /*使能USART1中断*/
  NVIC_EnableIRQ(USART1_IRQn);
    
 /*配置USART功能*/
  LL_USART_InitTypeDef USART_InitStruct;
  /*设置波特率*/
  USART_InitStruct.BaudRate = 9600;
  /*设置数据长度*/
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  /*停止位*/
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  /*设置校验位*/
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  /*USART初始化*/
  LL_USART_Init(USARTx, &USART_InitStruct);
  
  /*配置为全双工异步模式*/
  LL_USART_ConfigAsyncMode(USARTx);
  
  /*使能UART模块*/
  LL_USART_Enable(USARTx);
      
}

/**
  * @brief  USART发送函数.
  * @param  USARTx：USART模块，USART1
**           pData：发送缓冲区
**           Size：发送缓冲区大小
  * @retval 无
  */
static void APP_UsartTransmit_IT(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{
    TxBuff = pData;
    TxSize = Size;
    TxCount = Size;
    
    /*使能发送数据寄存器空中断*/
    LL_USART_EnableIT_TXE(USARTx); 
}

/**
  * @brief  USART接收函数.
  * @param  USARTx：USART模块，USART1
**           pData：发送缓冲区
**           Size：发送缓冲区大小
  * @retval 无
  */
static void APP_UsartReceive_IT(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{
    RxBuff = pData;
    RxSize = Size;
    RxCount = Size;
    
    /*使能接收奇偶校验错误中断*/
    LL_USART_EnableIT_PE(USARTx);
  
    /*使能接收错误中断*/
    LL_USART_EnableIT_ERROR(USARTx);
  
    /*使能接收数据寄存器非空中断*/
    LL_USART_EnableIT_RXNE(USARTx);
}

/**
  * @brief  USART中断处理函数.
  * @param  USARTx：USART模块，USART1
  * @retval 无
  */
void APP_UsartIRQCallback(USART_TypeDef *USARTx)
{
    /* 接收数据寄存器不为空 */
    uint32_t errorflags = (LL_USART_IsActiveFlag_PE(USARTx) | LL_USART_IsActiveFlag_FE(USARTx) |\
                           LL_USART_IsActiveFlag_ORE(USARTx) | LL_USART_IsActiveFlag_NE(USARTx));
    if (errorflags == RESET)
    {
        if ((LL_USART_IsActiveFlag_RXNE(USARTx) != RESET) && (LL_USART_IsEnabledIT_RXNE(USARTx) != RESET))
        {
            *RxBuff = LL_USART_ReceiveData8(USARTx);
             RxBuff++;
            if (--RxCount == 0U)
            {
                LL_USART_DisableIT_RXNE(USARTx);
                LL_USART_DisableIT_PE(USARTx);
                       LL_USART_DisableIT_ERROR(USARTx);
                
                UartReady = SET;
            }
            return;
        }
    }
    
    /* 接收错误 */ 
    if (errorflags != RESET)
    {
      Error_Handler();
    }
    
    /* 发送数据寄存器空 */ 
    if ((LL_USART_IsActiveFlag_TXE(USARTx) != RESET) && (LL_USART_IsEnabledIT_TXE(USARTx) != RESET))
      {
        LL_USART_TransmitData8(USARTx, *TxBuff);
        TxBuff++;
        if (--TxCount == 0U)
        { 
            LL_USART_DisableIT_TXE(USARTx);
            
            LL_USART_EnableIT_TC(USARTx);
        }
        return;
    }
    
    /* 发送完成 */
    if ((LL_USART_IsActiveFlag_TC(USARTx) != RESET) && (LL_USART_IsEnabledIT_TC(USARTx) != RESET))
    {
        LL_USART_DisableIT_TC(USARTx);
        UartReady = SET;
      
        return;
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
