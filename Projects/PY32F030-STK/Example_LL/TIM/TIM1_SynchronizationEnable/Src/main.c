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
#include "py32f030xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigTIM1Trigger_Slave(void);
static void APP_ConfigTIM3Trigger_Master(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 配置系统时钟 */
  APP_SystemClockConfig();
  
  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);
  BSP_LED_On(LED_GREEN);
  
  /* 使能TIM1、TIM3时钟 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

  /* 配置TIM1为同步触发从模式 */
  APP_ConfigTIM1Trigger_Slave();

  /* 配置TIM3为同步触发主模式 */
  APP_ConfigTIM3Trigger_Master();
  
  /* 无限循环 */
  while (1)
  {

  }
}

/**
  * @brief  TIM1 同步触发模式配置函数
  * @param  无
  * @retval 无
  */
static void APP_ConfigTIM1Trigger_Slave(void)
{
  /* CK_INT 1分频 */
  LL_TIM_SetClockDivision(TIM1,LL_TIM_CLOCKDIVISION_DIV1);
  /* 向上计数模式 */
  LL_TIM_SetCounterMode(TIM1,LL_TIM_COUNTERMODE_UP);
  /* 重装载值1000 */
  LL_TIM_SetAutoReload(TIM1,1000-1);
  /* CK_CNT 预分频值：8000 */
  LL_TIM_SetPrescaler(TIM1,8000-1);
  /* 从模式触发 */
  LL_TIM_SetSlaveMode(TIM1,LL_TIM_SLAVEMODE_TRIGGER);
  /* 触发输入选择ITR2（TIM3） */
  LL_TIM_SetTriggerInput(TIM1,LL_TIM_TS_ITR2);
  
  /* 开启UPDATE中断 */
  LL_TIM_EnableIT_UPDATE(TIM1);
  /* 设置UPDATE中断NVIC优先级 */
  NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 1);
  /* 使能UPDATE中断NVIC IRQ */
  NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
  
}

/**
  * @brief  TIM1 更新中断回调函数
  * @param  无
  * @retval 无
  */
void APP_TIM1UpdateCallback(void)
{
  BSP_LED_Toggle(LED_GREEN);
}

/**
  * @brief  TIM3 同步触发模式配置函数
  * @param  无
  * @retval 无
  */
static void APP_ConfigTIM3Trigger_Master(void)
{
  /* CK_INT 1分频 */
  LL_TIM_SetClockDivision(TIM3,LL_TIM_CLOCKDIVISION_DIV1);
  /* 向上计数模式 */
  LL_TIM_SetCounterMode(TIM3,LL_TIM_COUNTERMODE_UP);
  /* 重装载值1000 */
  LL_TIM_SetAutoReload(TIM3,1000-1);
  /* CK_CNT 预分频值：8000 */
  LL_TIM_SetPrescaler(TIM3,8000-1);
  /* 设置触发输出为更新事件 */
  LL_TIM_SetTriggerOutput(TIM3,LL_TIM_TRGO_UPDATE);
  
  /* 使能TIM3计数器 */
  LL_TIM_EnableCounter(TIM3);
}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
static void APP_SystemClockConfig(void)
{
  /* 使能HSI */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* 设置 AHB 分频 */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* 配置HSISYS作为系统时钟源 */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* 设置 APB1 分频 */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);

  /* 更新系统时钟全局变量SystemCoreClock(也可以通过调用SystemCoreClockUpdate函数更新) */
  LL_SetSystemCoreClock(8000000);
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
