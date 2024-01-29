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
TIM_ClockConfigTypeDef sClockSourceConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief   应用程序入口函数
  * @retval  int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();
  
  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  TimHandle.Instance = TIM1;                                           /* 选择TIM1 */
  TimHandle.Init.Period            = 800 - 1;                          /* 自动重装载值 */
  TimHandle.Init.Prescaler         = 1 - 1;                            /* 预分频为1-1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* 时钟不分频 */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* 向上计数 */
  TimHandle.Init.RepetitionCounter = 1 - 1;                            /* 不重复计数 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* 自动重装载寄存器没有缓冲 */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                         /* TIM1初始化 */
  {
    APP_ErrorHandler();
  }

  sClockSourceConfig.ClockFilter = 0;                                  /* 无滤波 */
  sClockSourceConfig.ClockPolarity = 0;                                /* ETR不进行反向，高电平或者上升沿有效 */
  sClockSourceConfig.ClockPrescaler = TIM_ETRPRESCALER_DIV1;           /* 预分频器关闭 */
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_ETRMODE1;           /* 外部触发输入(ETRF) */
  HAL_TIM_ConfigClockSource(&TimHandle, &sClockSourceConfig);          /* 时钟配置 */

  if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)                     /* TIM1使能启动，并使能中断 */
  {
    APP_ErrorHandler();
  }

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
