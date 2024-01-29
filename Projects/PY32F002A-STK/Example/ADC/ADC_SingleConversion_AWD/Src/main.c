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
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;
ADC_ChannelConfTypeDef sConfig;
ADC_AnalogWDGConfTypeDef      ADCAnalogWDGConfig;
uint32_t adc_value[2];
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Error_Handler(void);
void APP_ADCConfig(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  uint8_t i;
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();

  /* ADC配置*/
  APP_ADCConfig();

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  /* 初始化调试串口(printf使用) */
  BSP_USART_Config();

  /* 打印调试信息 */
  printf("print test");
  /* 无限循环 */
  while (1)
  {
    HAL_ADC_Start(&hadc);                           /* ADC开启*/
    for (i = 0; i < 2; i++)
    {
      HAL_ADC_PollForConversion(&hadc, 10000);      /* 等待ADC转换 */
      adc_value[i] = HAL_ADC_GetValue(&hadc);       /* 获取AD值  */
      printf("adc[%d]:%d\r\n", i, adc_value[i]);
    }
  }
}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
void APP_ADCConfig(void)
{
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
  __HAL_RCC_ADC_CLK_ENABLE();                                                /* 使能ADC时钟 */

  hadc.Instance = ADC1;
  if (HAL_ADCEx_Calibration_Start(&hadc) != HAL_OK)                          /* ADC校准 */
  {
    Error_Handler();
  }

  hadc.Instance                   = ADC1;                                    /* ADC*/
  hadc.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV32;               /* 模拟ADC时钟源为PCLK*/
  hadc.Init.Resolution            = ADC_RESOLUTION_12B;                      /* 转换分辨率12bit*/
  hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* 数据右对齐 */
  hadc.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;              /* 扫描序列方向：向上(从通道0到通道11)*/
  hadc.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;                     /* ADC_EOC_SINGLE_CONV:单次采样 ; ADC_EOC_SEQ_CONV:序列采样*/
  hadc.Init.LowPowerAutoWait      = ENABLE;                                  /* ENABLE=读取ADC值后,开始下一次转换 ; DISABLE=直接转换 */
  hadc.Init.ContinuousConvMode    = DISABLE;                                 /* 单次转换模式 */
  hadc.Init.DiscontinuousConvMode = DISABLE;                                 /* 不使能非连续模式 */
  hadc.Init.ExternalTrigConv      = ADC_SOFTWARE_START;                      /* 软件触发 */
  hadc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;           /* 触发边沿无 */
  hadc.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* ADC_OVR_DATA_OVERWRITTEN=过载时覆盖,ADC_OVR_DATA_PRESERVED=保留旧值*/
  hadc.Init.SamplingTimeCommon    = ADC_SAMPLETIME_41CYCLES_5;               /* 通道采样时间为41.5ADC时钟周期 */
  if (HAL_ADC_Init(&hadc) != HAL_OK)                                         /* ADC初始化*/
  {
    Error_Handler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*设置是否排行, 想设置单通道采样,需配置ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_0;                                      /* 设置采样通道 */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  配置ADC通道 */
  {
    Error_Handler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*设置是否排行, 想设置单通道采样,需配置ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_1;                                      /* 设置采样通道 */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  配置ADC通道 */
  {
    Error_Handler();
  }
  /* ADC 模拟看门狗初始化 */
  ADCAnalogWDGConfig.WatchdogMode = ADC_ANALOGWATCHDOG_ALL_REG;              /* 所有通道=ADC_ANALOGWATCHDOG_ALL_REG ;   单通道=ADC_ANALOGWATCHDOG_SINGLE_REG; */
  ADCAnalogWDGConfig.HighThreshold = 0X1FF;                                  /* 设置上阈值*/
  ADCAnalogWDGConfig.LowThreshold = 0;                                       /* 设置下阈值*/
  ADCAnalogWDGConfig.ITMode = ENABLE;                                        /* ENABLE=使能中断, DISABLE=禁止中断  */

  if (HAL_ADC_AnalogWDGConfig(&hadc, &ADCAnalogWDGConfig) != HAL_OK)         /* ADC模拟看门狗配置*/
  {
    Error_Handler();
  }
  HAL_NVIC_SetPriority(ADC_COMP_IRQn, 0, 0);                                      /* 设置ADC中断优先级*/
  HAL_NVIC_EnableIRQ(ADC_COMP_IRQn);                                              /* 设置ADC内核中断*/
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
