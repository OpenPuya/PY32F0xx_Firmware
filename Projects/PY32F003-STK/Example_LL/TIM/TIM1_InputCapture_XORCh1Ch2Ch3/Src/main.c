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
#include "py32f003xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigTIM1XOR(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 使能TIM1时钟 */
  LL_APB1_GRP2_EnableClock(RCC_APBENR2_TIM1EN);

  /* 配置系统时钟 */
  APP_SystemClockConfig();
  
  /* 初始化LED、按键 */
  BSP_LED_Init(LED3);
  BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
  
  /* 等待按键按下 */
  while(BSP_PB_GetState(BUTTON_USER) != 0)
  {
  }
    
  /* 配置并开启TIM1 XOR模式 */
  APP_ConfigTIM1XOR();
  
  while (1)
  {
  }
}

/**
  * @brief  配置TIM1 XOR模式
  * @param  无
  * @retval 无
  */
static void APP_ConfigTIM1XOR(void)
{
  LL_TIM_InitTypeDef TIM1CountInit = {0};
  LL_GPIO_InitTypeDef TIM1ChannelInit = {0};
  
  /* 配置TIM1 */
  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;  /* 时钟不分频 */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;      /* 向上计数模式 */
  TIM1CountInit.Prescaler           = 8000-1;                     /* 预分频值：8000 */
  TIM1CountInit.Autoreload          = 1000-1;                     /* 自动重装载值：1000 */
  TIM1CountInit.RepetitionCounter   = 0;                          /* 重复计数值：0 */
  
  /* 初始化TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);
  
  /* 使能CC中断 */
  LL_TIM_EnableIT_CC1(TIM1);
  NVIC_EnableIRQ(TIM1_CC_IRQn);
  
  /* 使能XOR输入 */
  LL_TIM_IC_EnableXORCombination(TIM1);
  
  /* 配置CH1、CH2、CH3为输入模式 */
  LL_TIM_IC_SetActiveInput(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_ACTIVEINPUT_DIRECTTI);
  LL_TIM_IC_SetActiveInput(TIM1,LL_TIM_CHANNEL_CH2,LL_TIM_ACTIVEINPUT_DIRECTTI);
  LL_TIM_IC_SetActiveInput(TIM1,LL_TIM_CHANNEL_CH3,LL_TIM_ACTIVEINPUT_DIRECTTI);
  
  /* 映射CH1、CH2、CH3到AP3、AP13、PA0 */
  TIM1ChannelInit.Pin       = LL_GPIO_PIN_3 | LL_GPIO_PIN_13 | LL_GPIO_PIN_0;
  TIM1ChannelInit.Pull      = LL_GPIO_PULL_UP;
  TIM1ChannelInit.Mode      = LL_GPIO_MODE_ALTERNATE;
  TIM1ChannelInit.Alternate = LL_GPIO_AF_13;
  LL_GPIO_Init(GPIOA,&TIM1ChannelInit);
  
  /* 使能CH1、CH2、CH3 */
  LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);
  LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2);
  LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3);

  /* 使能TIM1计数器 */
  LL_TIM_EnableCounter(TIM1);
  
}

/**
  * @brief  TIM1 CH1捕获中断回调函数
  * @param  无
  * @retval 无
  */
void APP_CCCallback(void)
{
  /* 翻转LED */
  BSP_LED_Toggle(LED3);
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
  while(1)
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
