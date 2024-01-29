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
/* Private variables ---------------------------------------------------------*/
uint8_t aTxBuffer[] = "UART Test";
uint8_t aRxBuffer[30];

uint8_t *TxBuff = NULL;
__IO uint16_t TxCount = 0;

uint8_t *RxBuff = NULL;
__IO uint16_t RxCount = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigUsart(USART_TypeDef *USARTx);
static void APP_UsartTransmit(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);
static void APP_UsartReceive(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);

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
  APP_UsartTransmit(USART1, (uint8_t*)aTxBuffer, sizeof(aTxBuffer)-1);

  while (1)
  {
    /* 接收数据 */
    APP_UsartReceive(USART1, (uint8_t *)aRxBuffer, 12);
    
    /* 发送数据 */
    APP_UsartTransmit(USART1, (uint8_t*)aRxBuffer, 12);
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
  * @brief  USART配置函数
  * @param  USARTx：USART模块，可以是USART1、USART2
  * @retval 无
  */
static void APP_ConfigUsart(USART_TypeDef *USARTx)
{
  /*使能时钟、初始化引脚*/
  if (USARTx == USART1) 
  {
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
  }
  else if (USARTx == USART2)
  {
    /*使能GPIOA时钟*/
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    /*使能USART1时钟*/
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
    
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
    /*复用为USART2功能*/
    GPIO_InitStruct.Alternate = LL_GPIO_AF4_USART2;
    /*GPIOA初始化*/
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    /*选择3号引脚*/
    GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
    /*复用为USART2功能*/
    GPIO_InitStruct.Alternate = LL_GPIO_AF4_USART2;
    /*GPIOA初始化*/
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
  }
  
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
  * @brief  USART发送函数
  * @param  USARTx：USART模块，可以是USART1、USART2
  * @param  pData：发送缓冲区
  * @param  Size：发送缓冲区大小
  * @retval 无
  */
static void APP_UsartTransmit(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{
  TxBuff = pData;
  TxCount = Size;
  
  /*发送数据*/
  while (TxCount > 0)
  {
    /* 等待TXE标志位置位 */
    while(LL_USART_IsActiveFlag_TXE(USARTx) != 1);
    /* 发送数据 */
    LL_USART_TransmitData8(USARTx, *TxBuff);
    TxBuff++;
    TxCount--;
  }
  
  /*等待TC标志位置位*/
  while(LL_USART_IsActiveFlag_TC(USARTx) != 1);
}

/**
  * @brief  USART接收函数
  * @param  USARTx：USART模块，可以是USART1、USART2
  * @param  pData：接收缓冲区
  * @param  Size：接收缓冲区大小
  * @retval 无
  */
static void APP_UsartReceive(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{
  RxBuff = pData;
  RxCount = Size;
  
  /*接收数据*/
  while (RxCount > 0)
  {
    /* 等待RXNE标志位置位 */
    while(LL_USART_IsActiveFlag_RXNE(USARTx) != 1);
    /* 接收数据 */
    *RxBuff = LL_USART_ReceiveData8(USARTx);
    RxBuff++;
    RxCount--;
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
