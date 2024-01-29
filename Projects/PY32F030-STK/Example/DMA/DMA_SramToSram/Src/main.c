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

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
DMA_HandleTypeDef     DmaHandle;
uint32_t aSRC_Const_Buffer[BUFFER_SIZE];       /* 数据传输源buffer */
uint32_t aDST_Buffer[BUFFER_SIZE];             /* 数据传输目标buffer */
__IO uint32_t transferCompleteDetected=0;      /* 当传输完成时，该位置1 */
__IO uint32_t transferErrorDetected=0;         /* 当传输出错时，该位置1 */
__IO uint32_t transferFailedDetected=0;        /* 当传输数据有误时，该位置1 */

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_DmaConfig(void);
static void APP_TransferComplete(DMA_HandleTypeDef *DmaHandle);
static void APP_TransferError(DMA_HandleTypeDef *DmaHandle);


/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);
  
  /* 给DMA 源buffer初始化数据*/
  for (uint8_t i = 0; i < BUFFER_SIZE; i++)
  {
    aSRC_Const_Buffer[i] = i;
  }

  /* 配置DMA */
  APP_DmaConfig();

  /* 使能DMA，并使能DMA中断 */
  if (HAL_DMA_Start_IT(&DmaHandle, (uint32_t)&aSRC_Const_Buffer, (uint32_t)&aDST_Buffer, BUFFER_SIZE) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  while (1)
  {
    /* DMA传输完成，但数据不正确 */
    if(transferFailedDetected == 1 && transferCompleteDetected == 1 )
    {
      while(1)
      {
        BSP_LED_Toggle(LED_GREEN);
        HAL_Delay(500);
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
        HAL_Delay(500);
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
  __HAL_RCC_DMA_CLK_ENABLE();                               /*使能DMA时钟*/

  DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;          /* M2M 模式 */
  DmaHandle.Init.PeriphInc = DMA_PINC_ENABLE;               /* 外设地址增量模式使能 */
  DmaHandle.Init.MemInc = DMA_MINC_ENABLE;                  /* 存储器地址增量模式使能 */
  DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD; /* 外设数据宽度为32位 */
  DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;    /* 存储器数据宽度为32位 */
  DmaHandle.Init.Mode = DMA_NORMAL;                         /* DMA循环模式关闭 */
  DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;              /* 通道优先级为高 */

  DmaHandle.Instance = DMA1_Channel1;                       /* 选择DMA通道1 */
  /* DMA初始化 */
  if (HAL_DMA_Init(&DmaHandle) != HAL_OK)                   
  {
    APP_ErrorHandler();
  }

  /* 选择错误传输和正确传输后，调用的回调函数 */
  HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_CPLT_CB_ID, APP_TransferComplete);
  HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_ERROR_CB_ID, APP_TransferError);
  /* DMA通道1中断使能 */
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

/**
  * @brief  DMA传输完成函数
  * @param  DmaHandle：DMA句柄
  * @retval 无
  */
static void APP_TransferComplete(DMA_HandleTypeDef *DmaHandle)
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
  * @brief  DMA传输出错函数
  * @param  DmaHandle：DMA句柄
  * @retval 无
  */
static void APP_TransferError(DMA_HandleTypeDef *DmaHandle)
{
  transferErrorDetected = 1;
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void APP_ErrorHandler(void)
{
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
