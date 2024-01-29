/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
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
volatile uint16_t   aADCxConvertedData;
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef       OCConfig;
TIM_MasterConfigTypeDef sMasterConfig;
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Error_Handler(void);
void APP_ADCConfig(void);
void APP_Tim1Config(void);
/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();

  /* 初始化调试串口(printf使用) */
  BSP_USART_Config();

  /* 打印调试信息 */
  printf("print test");

  /* Tim1配置*/
  APP_Tim1Config();

  /* ADC配置*/
  APP_ADCConfig();


  /* 无限循环 */
  while (1)
  {
    
  }
}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
void APP_ADCConfig(void)
{
  __HAL_RCC_ADC_CLK_ENABLE();                                                     /* ADC时钟使能 */

  /* 先复位ADC值 */
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
  __HAL_RCC_ADC_CLK_ENABLE();                                 /* 使能ADC时钟 */

  AdcHandle.Instance = ADC1;
  if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)                          /* ADC校准 */
  {
    Error_Handler();
  }
  
  AdcHandle.Instance                   = ADC1;                                    /* ADC*/
  AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV1;                /* 模拟ADC时钟源为PCLK*/
  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;                      /* 转换分辨率12bit*/
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* 数据右对齐 */
  AdcHandle.Init.ScanConvMode          = ADC_SCAN_DIRECTION_BACKWARD;             /* 扫描序列方向：向下*/
  AdcHandle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;                     /* 转换结束标志*/
  AdcHandle.Init.LowPowerAutoWait      = ENABLE;                                  /* 等待转换模式开启 */
  AdcHandle.Init.ContinuousConvMode    = DISABLE;                                 /* 单次转换模式 */
  AdcHandle.Init.DiscontinuousConvMode = ENABLE;                                  /* 使能非连续模式 */
  AdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_TRGO;            /* 外部触发转换启动事件为TIM1_TRG0 */
  AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING;  /* 上升沿和下降沿进行外部驱动 */
  AdcHandle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* 当过载发生时，覆盖上一个值*/
  AdcHandle.Init.SamplingTimeCommon    = ADC_SAMPLETIME_239CYCLES_5;              /* 通道采样时间为239.5ADC时钟周期 */
  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)                                         /* ADC初始化*/
  {
    Error_Handler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                                 /* 设置是否排行, 想设置单通道采样,需配置ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_0;                                           /* 设置采样通道 */
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)                      /* 配置ADC通道 */
  {
    Error_Handler();
  }
 
  if (HAL_ADC_Start_IT(&AdcHandle) != HAL_OK)                                      /*ADC开启，并且开启中断*/
  {
    Error_Handler();
  }

}
/**
  * @brief  Timer1初始化
  * @param  无
  * @retval 无
  */
void APP_Tim1Config(void)
{
  __HAL_RCC_TIM1_CLK_ENABLE();                                        /*TIM1时钟使能*/
  TimHandle.Instance = TIM1;                                          /*TIM1*/
  TimHandle.Init.Period            = 8000 - 1;                        /*TIM1重装载值位8000-1*/
  TimHandle.Init.Prescaler         = 100 - 1;                         /*预分频为100-1*/
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;          /*时钟不分配*/
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;              /*向上计数*/
  TimHandle.Init.RepetitionCounter = 0;                               /*不重复*/
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  /*自动重装载寄存器没有缓冲*/
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                        /*初始化TIM1*/
  {
    Error_Handler();
  }
  /*配置TIM1为主机模式*/
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;                /*选择更新事件作为触发源*/
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;        /*主/从模式无作用*/
  HAL_TIMEx_MasterConfigSynchronization(&TimHandle, &sMasterConfig);  /*配置TIM1*/
  if (HAL_TIM_Base_Start(&TimHandle) != HAL_OK)                       /*TIM1时钟启动*/
  {
    Error_Handler();
  }
}

/**
  * @brief  ADC执行函数，获取当前的ADC值
  * @param  无
  * @retval 无
  */
 void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  aADCxConvertedData = hadc->Instance->DR;
  printf("ADC: %03x\n\r", aADCxConvertedData);

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
