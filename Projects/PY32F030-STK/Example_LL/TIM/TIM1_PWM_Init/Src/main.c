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
static void APP_ConfigTIM1Base(void);
static void APP_ConfigPWMChannel(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 配置系统时钟 */
  APP_SystemClockConfig();
  
  /* 使能TIM1、GPIO时钟 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  
  /* 配置TIM1 PWM通道和PWM模式 */
  APP_ConfigPWMChannel();
  
  /* 配置并开启TIM1 PWM2模式 */
  APP_ConfigTIM1Base();
  
  while (1)
  {
  }
}

/**
  * @brief  配置TIM1 PWM相关GPIO
  * @param  无
  * @retval 无
  */
static void APP_ConfigPWMChannel(void)
{
  LL_GPIO_InitTypeDef TIM1CH1MapInit= {0};
  LL_TIM_OC_InitTypeDef TIM_OC_Initstruct ={0};

  /* 配置PA8/PA9/PA10为TIM1_CH1N/TIM1_CH1/TIM1_CH2/TIM1_CH3*/
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_8|LL_GPIO_PIN_9|LL_GPIO_PIN_10;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2; 
  LL_GPIO_Init(GPIOA,&TIM1CH1MapInit);
  
  TIM_OC_Initstruct.OCMode        = LL_TIM_OCMODE_PWM2;     /* 模式：PWM1 */
  TIM_OC_Initstruct.OCState       = LL_TIM_OCSTATE_ENABLE;  /* 通道开启 */
  TIM_OC_Initstruct.OCPolarity    = LL_TIM_OCPOLARITY_HIGH; /* 有效极性：高电平 */
  TIM_OC_Initstruct.OCIdleState   = LL_TIM_OCIDLESTATE_LOW; /* 空闲状态：低电平 */
  /* 通道1比较值:250 */
  TIM_OC_Initstruct.CompareValue  = 250;
  /* 配置通道1 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH1,&TIM_OC_Initstruct);
  /* 通道2比较值:500 */
  TIM_OC_Initstruct.CompareValue  = 500;
  /* 配置通道2 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH2,&TIM_OC_Initstruct);
  /* 通道3比较值:750 */
  TIM_OC_Initstruct.CompareValue  = 750;
  /* 配置通道3 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH3,&TIM_OC_Initstruct);
}

/**
  * @brief  配置TIM base
  * @param  无
  * @retval 无
  */
static void APP_ConfigTIM1Base(void)
{
  /* 配置TIM1 */
  LL_TIM_InitTypeDef TIM1CountInit = {0};
 
  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;   /* 时钟不分频 */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;       /* 向上计数模式 */
  TIM1CountInit.Prescaler           = 2400-1;                      /* 预分频值：2400 */
  TIM1CountInit.Autoreload          = 1000-1;                      /* 自动重装载值：1000 */
  TIM1CountInit.RepetitionCounter   = 0;                           /* 重复计数值：0 */
  
  /* 初始化TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);
  
  /* 主输出使能 */
  LL_TIM_EnableAllOutputs(TIM1);

  /* 使能TIM1计数器 */
  LL_TIM_EnableCounter(TIM1);
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
  LL_RCC_HSI_SetCalibFreq(LL_RCC_HSICALIBRATION_24MHz);
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
  LL_Init1msTick(24000000);
  
  /* 更新系统时钟全局变量SystemCoreClock(也可以通过调用SystemCoreClockUpdate函数更新) */
  LL_SetSystemCoreClock(24000000);
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void APP_ErrorHandler(void)
{
  /* 无限循环 */
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
