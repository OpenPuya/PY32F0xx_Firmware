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
TIM_HandleTypeDef    TimHandle1, TimHandle3;
TIM_SlaveConfigTypeDef   sSlaveConfig;
TIM_MasterConfigTypeDef sMasterConfig;
TIM_OC_InitTypeDef sConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);

/**
  * @brief   应用程序入口函数
  * @retval  int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();
  
  /* 系统时钟配置 */
  APP_SystemClockConfig(); 
  
  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  TimHandle3.Instance = TIM3;                                           /* 选择TIM3 */
  TimHandle3.Init.Period            = 1000 - 1;                         /* 自动重装载值 */
  TimHandle3.Init.Prescaler         = 1 - 1;                            /* 不预分频 */
  TimHandle3.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* 时钟不分频 */
  TimHandle3.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* 向上计数 */
  TimHandle3.Init.RepetitionCounter = 1 - 1;                            /* 不重复计数 */
  TimHandle3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* 自动重装载寄存器没有缓冲 */
  /* TIM3初始化 */
  if (HAL_TIM_Base_Init(&TimHandle3) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  TimHandle1.Instance = TIM1;                                               /* 选择TIM1 */
  TimHandle1.Init.Prescaler = 1 - 1;                                        /* 不预分频 */
  TimHandle1.Init.CounterMode = TIM_COUNTERMODE_UP;                         /* 向上计数 */
  TimHandle1.Init.Period = 8000 - 1;                                        /* 自动重装载值 */
  TimHandle1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                   /* 时钟不分频 */
  TimHandle1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;       /* 自动重装载寄存器没有缓冲 */
  /* TIM1初始化 */
  if (HAL_TIM_Base_Init(&TimHandle1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  sConfig.OCMode       = TIM_OCMODE_TOGGLE;                            /* 输出配置为翻转模式 */
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;                          /* OC通道输出高电平有效 */
  sConfig.OCFastMode   = TIM_OCFAST_DISABLE;                           /* 输出快速使能关闭 */
  sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                         /* OCN通道输出高电平有效 */
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;                       /* 空闲状态OC1N输出低电平 */
  sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;                        /* 空闲状态OC1输出低电平 */
  sConfig.Pulse        = 4000;
  /*OC通道配置*/
  if (HAL_TIM_OC_ConfigChannel(&TimHandle1, &sConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_OC1REF;                 /* 主时钟OC1REF被用于作为触发输出 */
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;         /* 主从模式关闭 */
  /* TIM1配置为主模式 */
  HAL_TIMEx_MasterConfigSynchronization(&TimHandle1, &sMasterConfig);

  sSlaveConfig.SlaveMode        = TIM_SLAVEMODE_GATED;                 /* 从模式选择为门控模式 */
  sSlaveConfig.InputTrigger     = TIM_TS_ITR0;                         /* TIM3的触发选择为TIM1 */
  sSlaveConfig.TriggerPolarity  = TIM_TRIGGERPOLARITY_NONINVERTED;     /* 外部触发极性不反向 */
  sSlaveConfig.TriggerPrescaler = TIM_TRIGGERPRESCALER_DIV1;           /* 外部触发不分频 */
  sSlaveConfig.TriggerFilter    = 0;                                   /* 不滤波 */
  /* TIM3配置为从模式 */
  if (HAL_TIM_SlaveConfigSynchro(&TimHandle3, &sSlaveConfig) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* TIM1启动计数 */
  if (HAL_TIM_OC_Start(&TimHandle1, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* TIM3启动计数并使能产生更新中断 */
  if (HAL_TIM_Base_Start_IT(&TimHandle3) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* 无限循环 */
  while (1)
  {
  }

}

/**
  * @brief   更新中断回调函数
  * @param   htim：TIM句柄
  * @retval  无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  BSP_LED_Toggle(LED_GREEN);
}

/**
  * @brief   系统时钟配置函数
  * @param   无
  * @retval  无
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI \
                                   | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;  /* 配置HSE、HSI、LSI、LSE */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                             /* 开启HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                             /* HSI不分频 */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz;                     /* HSI校准频率8MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                                            /* 关闭HSE */
  /* RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz; */                                  /* HSE频率范围16~32MHz */
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                                            /* 关闭LSI */
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;                                            /* 关闭LSE */
  /* RCC_OscInitStruct.LSEDriver = RCC_LSEDRIVE_MEDIUM; */                             /* 默认LSE驱动能力 */
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_OFF;                                        /* 关闭PLL */
  /* RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_NONE; */                          /* PLL无时钟源 */
  /* 配置振荡器 */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;/* 配置SYSCLK、HCLK、PCLK */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                                        /* 配置系统时钟为HSI */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                            /* AHB时钟不分频 */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                                             /* APB时钟不分频 */
  /* 配置时钟源 */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief   错误执行函数
  * @param   无
  * @retval  无
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
