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
TIM_OnePulse_InitTypeDef sConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();
  
  /* 系统时钟配置 */
  APP_SystemClockConfig(); 
  
  /* 初始化按键 */
  BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
  
  /* 等待按键按下 */
  while(BSP_PB_GetState(BUTTON_USER) == GPIO_PIN_SET)
  {
  }
  
  TimHandle.Instance = TIM1;                                           /* 选择TIM1 */
  TimHandle.Init.Period            = 0xffff;                           /* 自动重装载值 */
  TimHandle.Init.Prescaler         = 1 - 1;                            /* 不分频 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* 时钟不分频 */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* 向上计数 */
  TimHandle.Init.RepetitionCounter = 1 - 1;                            /* 不重复计数 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* 自动重装载寄存器没有缓冲 */
  /*TIM1单脉冲初始化*/
  if (HAL_TIM_OnePulse_Init(&TimHandle, TIM_OPMODE_SINGLE) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  sConfig.OCMode       = TIM_OCMODE_PWM2;                              /* PWM模式2 */
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;                          /* OC输出高电平有效 */
  sConfig.Pulse        = 16383;                                        /* 宽度 */
  sConfig.ICPolarity   = TIM_ICPOLARITY_RISING;                        /* IC1捕获信号不反向 */
  sConfig.ICSelection  = TIM_ICSELECTION_DIRECTTI;                     /* CC1 通道被配置为输入IC1映射在TI1上 */
  sConfig.ICFilter     = 0;                                            /* 不滤波 */
  sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                         /* OCN输出高电平有效 */
  sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;                        /* 输出空闲状态1（OC1输出） */
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;                       /* 输出空闲状态1（OC1N输出） */
  /*配置TIM1 单脉冲通道参数配置*/
  if (HAL_TIM_OnePulse_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1, TIM_CHANNEL_2) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*配置TIM1 单脉冲启动*/
  if (HAL_TIM_OnePulse_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  while (1)
  {
  }
}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* 配置时钟源HSE/HSI/LSE/LSI */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                                       /* 开启HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                                       /* 不分频 */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_16MHz;                              /* 配置HSI输出时钟为16MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                                                      /* 关闭HSE */
  RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz;                                                  /* HSE晶振工作频率16M~32M */
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                                                      /* 关闭LSI */

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)                                           /* 初始化RCC振荡器 */
  {
    APP_ErrorHandler();
  }

  /* 初始化CPU,AHB,APB总线时钟 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* RCC系统时钟类型 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                                         /* SYSCLK的源选择为PLL */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                             /* APH时钟不分频 */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                                              /* APB时钟不分频 */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)                        /* 初始化RCC系统时钟(FLASH_LATENCY_0=24M以下;FLASH_LATENCY_1=48M) */
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
