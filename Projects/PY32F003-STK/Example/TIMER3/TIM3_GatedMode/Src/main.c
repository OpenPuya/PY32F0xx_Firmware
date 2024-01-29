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
TIM_SlaveConfigTypeDef   sSlaveConfig;
TIM_MasterConfigTypeDef sMasterConfig;
TIM_IC_InitTypeDef sConfig;

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

  TimHandle.Instance = TIM3;                                           /* 选择TIM3 */
  TimHandle.Init.Period            = 8000 - 1;                         /* 自动重装载值 */
  TimHandle.Init.Prescaler         = 1 - 1;                            /* 不预分频 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* 时钟不分频 */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* 向上计数 */
  TimHandle.Init.RepetitionCounter = 1 - 1;                            /* 不重复计数 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* 自动重装载寄存器没有缓冲 */
  if (HAL_TIM_IC_Init(&TimHandle) != HAL_OK)                           /* TIM3输入捕获初始化 */
  {
    APP_ErrorHandler();
  }
  
  /* TIM3_CH1输入配置 */
  sConfig.ICPrescaler = TIM_ICPSC_DIV1;                                /* 不分配 */
  sConfig.ICFilter = 0;                                                /* 不滤波 */
  sConfig.ICPolarity = TIM_ICPOLARITY_FALLING;                         /* 下降沿捕获 */
  sConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;                      /* CC1通道配置为输入,IC1映射在TI1上 */
  /* TIM3_CH1捕获配置 */
  if (HAL_TIM_IC_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  sSlaveConfig.SlaveMode        = TIM_SLAVEMODE_GATED;                 /* 从模式选择为复位模式 */
  sSlaveConfig.InputTrigger     = TIM_TS_TI1FP1;                       /* TIM3的触发选择为TIM1 */
  sSlaveConfig.TriggerPolarity  = TIM_TRIGGERPOLARITY_NONINVERTED;     /* 外部触发极性不反向 */
  sSlaveConfig.TriggerPrescaler = TIM_TRIGGERPRESCALER_DIV1;           /* 外部触发不分频 */
  sSlaveConfig.TriggerFilter    = 0;                                   /* 不滤波 */
  /* 配置TIM3为从模式，中断方式 */
  if (HAL_TIM_SlaveConfigSynchro_IT(&TimHandle, &sSlaveConfig) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  if (HAL_TIM_IC_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)          /* TIM3启动计数并使能产生中断 */
  {
    APP_ErrorHandler();
  }

  while (1)
  {
  }

}

/**
  * @brief   触发中断回调函数
  * @param   htim：TIM句柄
  * @retval  无
  */
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim)
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
