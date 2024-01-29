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
#define  PULSE1_VALUE       (uint32_t)(400)      /* Capture Compare 1 Value  */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef              sPWMConfig;
TIM_BreakDeadTimeConfigTypeDef sBreakConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();

  TimHandle.Instance = TIM1;                                                      /* 选择TIM1 */
  TimHandle.Init.Period            = 800 - 1;                                     /* 自动重装载值 */
  TimHandle.Init.Prescaler         = 1000 - 1;                                    /* 预分频为1000-1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                      /* 时钟不分频 */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                          /* 向上计数 */
  TimHandle.Init.RepetitionCounter = 1 - 1;                                       /* 不重复计数 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;              /* 自动重装载寄存器没有缓冲 */
  if (HAL_TIM_PWM_Init(&TimHandle) != HAL_OK)                                     /* PWM初始化 */
  {
    APP_ErrorHandler();
  }

  sPWMConfig.OCMode       = TIM_OCMODE_PWM1;                                      /* 配置为PWM1 */
  sPWMConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;                                  /* 高电平有效 */
  sPWMConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                 /* 高电平有效 */
  sPWMConfig.OCIdleState  = TIM_OCIDLESTATE_SET;                                  /* 输出空闲状态1(OC1输出) */
  sPWMConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;                               /* 输出空闲状态1(OC1N输出) */
  sPWMConfig.OCFastMode   = TIM_OCFAST_DISABLE;                                   /* 关闭快速使能 */

  sPWMConfig.Pulse = PULSE1_VALUE;                                                /* 通道1占空比 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sPWMConfig, TIM_CHANNEL_1) != HAL_OK)/* 通道1配置 */
  {
    APP_ErrorHandler();
  }
  
  /* 设置刹车和死区相关配置 */
  sBreakConfig.BreakState       = TIM_BREAK_ENABLE;                               /* 刹车功能使能 */
  sBreakConfig.DeadTime         = 160;                                            /* 设置死区时间 */
  sBreakConfig.OffStateRunMode  = TIM_OSSR_ENABLE;                                /* 运行模式下关闭状态选择 OSSR=1 */
  sBreakConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;                                /* 空闲状态下关闭状态选择 OSSI=1 */
  sBreakConfig.LockLevel        = TIM_LOCKLEVEL_OFF;                              /* 锁定关闭 */
  sBreakConfig.BreakPolarity    = TIM_BREAKPOLARITY_LOW;                          /* 刹车输入高电平有效 */
  sBreakConfig.AutomaticOutput  = TIM_AUTOMATICOUTPUT_ENABLE;                     /* 自动输出使能 */

  if (HAL_TIMEx_ConfigBreakDeadTime(&TimHandle, &sBreakConfig) != HAL_OK)         /* 刹车和死区状况配置 */
  {
    APP_ErrorHandler();
  }
  /* 通道1输出PWM */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  /* 通道1N输出PWM */
  if (HAL_TIMEx_PWMN_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  while (1)
  {
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
