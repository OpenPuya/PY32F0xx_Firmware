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
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef   sConfig1,sConfig2,sConfig3;
TIM_BreakDeadTimeConfigTypeDef sBreakConfig;
uint32_t temp;
__IO uint32_t uwStep = 0;

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
  
  /* TIM计数器配置 */
  TimHandle.Instance               = TIM1;                            /* 选择TIM1 */
  TimHandle.Init.Period            = 1000 - 1;                        /* 自动重载值：1000 */
  TimHandle.Init.Prescaler         = 1 - 1;                           /* 预分频器不分频 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;          /* 时钟不分频 */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;              /* 向上计数 */
  TimHandle.Init.RepetitionCounter = 1 - 1;                           /* 重复计数值：1 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  /* 禁用自动重载预装载 */
  /* 初始化TIM1 */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* PWM通道配置 */
  sConfig1.OCMode       = TIM_OCMODE_TIMING;                          /* 通道模式：冻结 */
  sConfig1.OCPolarity   = TIM_OCPOLARITY_HIGH;                        /* 通道有效极性：高电平 */
  sConfig1.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                       /* 互补通道有效极性：高电平 */
  sConfig1.OCIdleState  = TIM_OCNIDLESTATE_RESET;                     /* 通道空闲状态：低电平 */
  sConfig1.OCNIdleState = TIM_OCNIDLESTATE_RESET;                     /* 互补通道空闲状态：低电平 */
  sConfig1.OCFastMode   = TIM_OCFAST_DISABLE;                         /* 禁用快速模式 */
  /*配置通道1比较值500*/
  sConfig1.Pulse        = 500 - 1;
  /* 配置TIM1_CH1 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  sConfig2 = sConfig1;
  /*配置通道2比较值250*/
  sConfig2.Pulse        = 250 - 1;
  /* 配置TIM1_CH2 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig2, TIM_CHANNEL_2) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  sConfig3 = sConfig1;
  /* 配置通道3比较值125 */
  sConfig3.Pulse        = 125 - 1;
  /* 配置TIM1_CH3 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* 刹车和死区相关配置 */
  sBreakConfig.BreakState       = TIM_BREAK_ENABLE;                      /* 使能刹车 */
  sBreakConfig.DeadTime         = 1;                                     /* 死区时间 */
  sBreakConfig.OffStateRunMode  = TIM_OSSR_ENABLE;                       /* 运行模式下关闭状态：开启输出 */
  sBreakConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;                       /* 空闲模式下关闭状态：开启输出 */
  sBreakConfig.LockLevel        = TIM_LOCKLEVEL_OFF;                     /* 关闭锁定 */
  sBreakConfig.BreakPolarity    = TIM_BREAKPOLARITY_HIGH;                /* 刹车有效极性：高电平 */
  sBreakConfig.AutomaticOutput  = TIM_AUTOMATICOUTPUT_ENABLE;            /* 开启自动输出 */
  /* 配置刹车和死区 */
  if (HAL_TIMEx_ConfigBreakDeadTime(&TimHandle, &sBreakConfig) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  /* 配置换向事件：软件方式 */
  HAL_TIMEx_ConfigCommutEvent_IT(&TimHandle, TIM_TS_NONE, TIM_COMMUTATION_SOFTWARE);
  
  /* 开启所有通道 */
  if (HAL_TIM_OC_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  if (HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  if (HAL_TIM_OC_Start(&TimHandle, TIM_CHANNEL_2) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  if (HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_2) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  if (HAL_TIM_OC_Start(&TimHandle, TIM_CHANNEL_3) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  if (HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_3) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* 无限循环 */
  while (1)
  {
  }
}

/**
  * @brief   换向中断回调函数
  * @param   htim：TIM句柄
  * @retval  无
  */
void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim)
{
  if (uwStep == 0)
  {
    /* 第一步配置 */

    /* 通道1配置为PWM1 */
    sConfig1.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1);
    
    /* 开启CH1 */
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);
    /* 关闭CH1N */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_1);

    /* 通道3配置为PWM1 */
    sConfig3.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3);
    
    /* 开启CH3N */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_3);
    /* 关闭CH3 */
    HAL_TIM_PWM_Stop(&TimHandle, TIM_CHANNEL_3);

    /* 关闭CH2 */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_2);
    /* 关闭CH2N */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_2);
    
    uwStep = 1;
  }

  else if (uwStep == 1)
  {
    /* 第二步配置 */
    
    /* 通道2配置为PWM1 */
    sConfig2.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig2, TIM_CHANNEL_2);
    
    /* 开启CH2N */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_2);
    
    /* 关闭CH3N */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_3);

    uwStep++;
  }

  else if (uwStep == 2)
  {
    /* 第三步配置 */
    
    /* 通道3配置为PWM1 */
    sConfig3.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3);
    
    /* 开启CH3 */ 
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_3);
    
    /* 关闭CH1 */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_1);

    uwStep++;
  }

  else if (uwStep == 3)
  {
    /* 第四步配置 */
    
    /* 关闭CH2N */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_2);
    
    /* 通道1配置为PWM1 */
    sConfig1.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1);
    
    /* 开启CH1N */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_1);
    
    uwStep++;
  }
  else if (uwStep == 4)
  {
    /* 第五步配置 */
    
    /* 关闭CH3 */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_3);

    /* 通道2配置为PWM1 */
    sConfig2.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig2, TIM_CHANNEL_2);
    
    /* 开启CH2 */
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_2);

    uwStep++;
  }

  else if (uwStep == 5)
  {
    /* 第六步配置 */
    
    /* 通道3配置为PWM1 */
    sConfig3.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3);
    
    /* 开启CH3N */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_3);

    /* 关闭CH1N */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_1);

    uwStep++;
  }

  else
  {
    /* 第一步配置 */
    
    /* 通道1配置为PWM1 */
    sConfig1.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1);
    
    /* 开启CH1 */
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);
    
    /* 关闭CH2 */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_2);

    uwStep = 1;
  }
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
