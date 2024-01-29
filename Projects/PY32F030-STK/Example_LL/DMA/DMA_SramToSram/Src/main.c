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
#define BUFFER_SIZE              32

/* Private variables ---------------------------------------------------------*/
uint32_t aSRC_Const_Buffer[BUFFER_SIZE];       /* 数据传输源buffer */
uint32_t aDST_Buffer[BUFFER_SIZE];             /* 数据传输目标buffer */
__IO uint32_t transferCompleteDetected=0;      /* 当传输完成时，该位置1 */
__IO uint32_t transferErrorDetected=0;         /* 当传输出错时，该位置1 */
__IO uint32_t transferFailedDetected=0;        /* 当传输数据有误时，该位置1 */

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_DmaConfig(void);
static void APP_SystemClockConfig(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 配置系统时钟 */
  APP_SystemClockConfig();

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  /* 给DMA 源buffer初始化数据 */
  for(uint8_t i=0; i<BUFFER_SIZE; i++)
  {
    aSRC_Const_Buffer[i]=i;
  }

  /* 配置DMA */
  APP_DmaConfig();

  while (1)
  {   
    /* DMA传输完成，但数据不正确 */
    if(transferFailedDetected == 1 && transferCompleteDetected == 1 )
    {
      while(1)
      {
        BSP_LED_Toggle(LED_GREEN);
        LL_mDelay(500);
      }
    }

    /* DMA传输完成，并且数据正确 */
    if(transferFailedDetected == 0 && transferCompleteDetected == 1 )
    {
      BSP_LED_On(LED_GREEN);
      while(1)
      {
      }
    }

    /* DMA传输出错 */
    if(transferErrorDetected == 1 )
    {
      BSP_LED_On(LED_GREEN);
      while(1)
      {
        BSP_LED_Toggle(LED_GREEN);
        LL_mDelay(500);
      }
    } 
  }
}

/**
  * @brief  DMA配置函数
  * @param  无
  * @retval 无
  */
static void APP_DmaConfig(void)
{
  LL_DMA_InitTypeDef dma_initstruct;

  /* 使能DMA时钟 */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

  /* 配置DMA功能参数 */
  dma_initstruct.PeriphOrM2MSrcAddress  = (uint32_t)&aSRC_Const_Buffer;           /* 源地址设置 */
  dma_initstruct.MemoryOrM2MDstAddress  = (uint32_t)&aDST_Buffer;                 /* 目标地址设置 */
  dma_initstruct.Direction              = LL_DMA_DIRECTION_MEMORY_TO_MEMORY;      /* M2M 模式 */
  dma_initstruct.Mode                   = LL_DMA_MODE_NORMAL;                     /* DMA循环模式关闭 */
  dma_initstruct.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_INCREMENT;                /* 外设地址增量模式使能 */
  dma_initstruct.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;                /* 存储器地址增量模式使能 */
  dma_initstruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_WORD;                 /* 外设数据宽度为32位 */
  dma_initstruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_WORD;                 /* 存储器数据宽度为32位 */
  dma_initstruct.NbData                 = BUFFER_SIZE;
  dma_initstruct.Priority               = LL_DMA_PRIORITY_HIGH;                   /* 通道优先级为高 */
  /* 初始化DMA */
  if (LL_DMA_Init(DMA1, LL_DMA_CHANNEL_1, &dma_initstruct) != SUCCESS)
  {
    APP_ErrorHandler();
  }

  /* 使能中断 */
  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
  LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_1);
  NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);

  /* 使能DMA */
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
}

/**
  * @brief  DMA传输完成回调函数
  * @param  无
  * @retval 无
  */
void APP_TransferCompleteCallback(void)
{
  for(uint16_t i=0 ; i<BUFFER_SIZE; i++)
  {
    if(aDST_Buffer[i] != aSRC_Const_Buffer[i])
    {
      transferFailedDetected=1;
      break;
    }
  }
  transferCompleteDetected=1;
}

/**
  * @brief  DMA传输出错回调函数
  * @param  无
  * @retval 无
  */
void APP_TransferErrorCallback(void)
{
  transferErrorDetected = 1;
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
void APP_ErrorHandler(void)
{
  while(1)
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
