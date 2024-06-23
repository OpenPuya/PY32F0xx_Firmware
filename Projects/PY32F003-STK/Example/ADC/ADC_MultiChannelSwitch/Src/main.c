/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
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
volatile uint32_t             aADCxConvertedData;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_AdcConfig(void);
static uint32_t APP_ADCConvert(uint32_t Channel);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 复位所有外设，初始化SysTick */
  HAL_Init();    
  
  /* 初始化 ADC */
  APP_AdcConfig();  
  
  /* 初始化 UART */
  DEBUG_USART_Config();  
  
  printf("test start..\r\n");
  while (1)
  {   
    aADCxConvertedData = APP_ADCConvert(ADC_CHANNEL_5);
    /* 打印通道5 的值 */
    printf("Channe5 value:%u \r\n",(unsigned int)aADCxConvertedData);
    
    aADCxConvertedData = APP_ADCConvert(ADC_CHANNEL_4);
    /* 打印通道4 的值 */
    printf("Channe4 value:%u \r\n",(unsigned int)aADCxConvertedData);
    HAL_Delay(1000);
  }
}

/**
  * @brief  ADC 转换函数
  * @param  Channel: 待转换的通道 
  * @retval ADC 转换值
  */
static uint32_t APP_ADCConvert(uint32_t Channel)
{
  uint16_t adcvalue = 0;
  
  /* 清除所有通道 */
  WRITE_REG(ADC1->CHSELR,0);
  
  /* 配置选择的通道 */
  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                             
  sConfig.Channel      = Channel;                                      
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)                      
  {
    APP_ErrorHandler();
  }
  
  /* 开始转换 */
  HAL_ADC_Start(&AdcHandle);  
  
  /* 轮询等待ADC转换结束 */
  HAL_ADC_PollForConversion(&AdcHandle, 1000000);        
  
  /* 读取ADC转换值 */
  adcvalue = HAL_ADC_GetValue(&AdcHandle);     
  
  /* 清除所有通道 */
  WRITE_REG(ADC1->CHSELR,0);
  
  return (uint32_t)adcvalue;
}

/**
  * @brief  ADC配置函数
  * @param  无
  * @retval 无
  */
static void APP_AdcConfig(void)
{

  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
  __HAL_RCC_ADC_CLK_ENABLE();

  /* ADC句柄为ADC1 */
  AdcHandle.Instance = ADC1;
  /* ADC校准 */
  if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)                 
  {
    APP_ErrorHandler();
  }    

  AdcHandle.Instance = ADC1;
  AdcHandle.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;              /* 设置ADC时钟 */
  AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;                        /* 转换分辨率12bit */
  AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;                        /* 数据右对齐 */
  AdcHandle.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;              /* 设置ADC转换方向, 向上 */
  AdcHandle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                     /* ADC_EOC_SINGLE_CONV:单次采样 ; ADC_EOC_SEQ_CONV:序列采样 */
  AdcHandle.Init.LowPowerAutoWait = ENABLE;                              /* 等待转换模式开启 */
  AdcHandle.Init.ContinuousConvMode = DISABLE;                           /* 单次转换模式 */
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;                        /* 不使能非连续模式 */
  AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                  /* 软件触发 */
  AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;   /* 触发边沿无 */
  AdcHandle.Init.DMAContinuousRequests = DISABLE;                        /* DMA不使能 */
  AdcHandle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                     /* 当过载发生时，覆盖上一个值 */
  AdcHandle.Init.SamplingTimeCommon = ADC_SAMPLETIME_41CYCLES_5;         /* 设置采样周期41.5个ADC时钟 */
  /* ADC初始化 */
  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)                                
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
