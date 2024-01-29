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
ADC_HandleTypeDef             AdcHandle;
ADC_ChannelConfTypeDef        sConfig;
uint32_t   aADCxConvertedData = 1;
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef       OCConfig;
TIM_MasterConfigTypeDef sMasterConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_TimerInit(void);
static void APP_AdcConfig(void);

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
  
  /* 初始化USART */
  DEBUG_USART_Config();                                                           
  
  /* 初始化Timer */
  APP_TimerInit();      
  
  /* 配置ADC */
  APP_AdcConfig();                                                                
  
  while (1)
  {
    /* DMA通道1传输完成 */
    if (__HAL_DMA_GET_FLAG(DMA1, DMA_ISR_TCIF1))                                  
    {
      /* 清DMA通道1传输完成标志 */
      __HAL_DMA_CLEAR_FLAG(DMA1, DMA_IFCR_CTCIF1);                                
      printf("ADC: %d \r\n", aADCxConvertedData);
    }
  }
}

/**
  * @brief  ADC配置函数
  * @param  无
  * @retval 无
  */
static void APP_AdcConfig(void)
{
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();                                                  /* 复位ADC */
  __HAL_RCC_ADC_CLK_ENABLE();                                                     /* ADC时钟使能 */

  AdcHandle.Instance = ADC1;

  /* ADC校准 */
  if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)                          
  {
    APP_ErrorHandler();
  }
  
  AdcHandle.Instance                   = ADC1;                                    /* ADC1 */
  AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV1;                /* 设置ADC时钟 */
  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;                      /* 转换分辨率12bit */
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* 数据右对齐 */
  AdcHandle.Init.ScanConvMode          = ADC_SCAN_DIRECTION_BACKWARD;             /* 扫描序列方向：向下 */
  AdcHandle.Init.LowPowerAutoWait      = ENABLE;                                  /* 等待转换模式开启 */
  AdcHandle.Init.ContinuousConvMode    = DISABLE;                                 /* 单次转换模式 */
  AdcHandle.Init.DiscontinuousConvMode = ENABLE;                                  /* 使能非连续模式 */
  AdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_TRGO;            /* 外部触发转换启动事件为TIM1_TRGO */
  AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING;  /* 触发边沿上升沿和下降沿 */
  AdcHandle.Init.DMAContinuousRequests = ENABLE;                                  /* DMA循环模式选择 */
  AdcHandle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* 当过载发生时，覆盖上一个值 */
  AdcHandle.Init.SamplingTimeCommon    = ADC_SAMPLETIME_28CYCLES_5;               /* 通道采样时间为28.5ADC时钟周期 */
  /* ADC初始化 */
  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;
  sConfig.Channel      = ADC_CHANNEL_0;
  /* 通道0配置 */
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)                     
  {
    APP_ErrorHandler();
  }
  /* ADC开启 */
  if (HAL_ADC_Start_DMA(&AdcHandle, &aADCxConvertedData, 1) != HAL_OK)            
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  TIM配置函数
  * @param  无
  * @retval 无
  */
static void APP_TimerInit(void)
{
  __HAL_RCC_TIM1_CLK_ENABLE();                                        /* TIM1时钟使能 */
  TimHandle.Instance = TIM1;                                          /* TIM1 */
  TimHandle.Init.Period            = 8000 - 1;                        /* TIM1重装载值位8000-1 */
  TimHandle.Init.Prescaler         = 1000 - 1;                        /* 预分频为1000-1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;          /* 时钟不分频 */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;              /* 向上计数 */
  TimHandle.Init.RepetitionCounter = 0;                               /* 不重复 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  /* 自动重装载寄存器没有缓冲 */
  /* 初始化TIM1 */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                        
  {
    APP_ErrorHandler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;                /* 选择更新事件作为触发源 */
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;        /* 主/从模式无作用 */
  HAL_TIMEx_MasterConfigSynchronization(&TimHandle, &sMasterConfig);  /* 配置TIM1 */
  /* TIM1时钟启动 */
  if (HAL_TIM_Base_Start(&TimHandle) != HAL_OK)                       
  {
    APP_ErrorHandler();
  }
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
