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
uint32_t uwStep = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigTIM1Base(void);
static void APP_Config6StepPWMChannel(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 配置系统时钟 */
  APP_SystemClockConfig();
  
  /* 开启SysTick中断 */
  LL_SYSTICK_EnableIT();
  
  /* 使能TIM1、GPIO时钟 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA|LL_IOP_GRP1_PERIPH_GPIOB);
  
  /* 配置并开启TIM16StepPWM模式 */
  APP_ConfigTIM1Base();
  
  /*  无限循环  */
  while (1)
  {
  }
}

/**
  * @brief  配置TIM1 6StepPWM相关GPIO
  * @param  无
  * @retval 无
  */
static void APP_Config6StepPWMChannel(void)
{
  LL_GPIO_InitTypeDef TIM1CH1MapInit= {0};
  LL_TIM_OC_InitTypeDef TIM_OC_Initstruct ={0};

  /* 配置PA7/PA8/PA9/PA10为TIM1_CH1N/TIM1_CH1/TIM1_CH2/TIM1_CH3 */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_7|LL_GPIO_PIN_8|LL_GPIO_PIN_9|LL_GPIO_PIN_10;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2; 
  LL_GPIO_Init(GPIOA,&TIM1CH1MapInit);
  
  /* 配置PB0/PB1为TIM1_CH2N/TIM1_CH3N */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_0|LL_GPIO_PIN_1;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2; 
  LL_GPIO_Init(GPIOB,&TIM1CH1MapInit);
  
  /* 配置PWM通道 */
  TIM_OC_Initstruct.OCMode        = LL_TIM_OCMODE_PWM1;     /* 模式：PWM1 */
  TIM_OC_Initstruct.OCState       = LL_TIM_OCSTATE_ENABLE;  /* 通道开启 */
  TIM_OC_Initstruct.OCNState      = LL_TIM_OCSTATE_ENABLE;  /* 互补通道开启 */
  TIM_OC_Initstruct.OCPolarity    = LL_TIM_OCPOLARITY_HIGH; /* 有效极性：高电平 */
  TIM_OC_Initstruct.OCNPolarity   = LL_TIM_OCPOLARITY_HIGH; /* 互补通道有效极性：高电平 */
  TIM_OC_Initstruct.OCIdleState   = LL_TIM_OCIDLESTATE_LOW; /* 空闲状态：低电平 */
  TIM_OC_Initstruct.OCNIdleState  = LL_TIM_OCIDLESTATE_LOW; /* 互补通道空闲状态：低电平 */
  TIM_OC_Initstruct.CompareValue  = 50;                     /* 比较值：50 */
  /* 配置通道1 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH1,&TIM_OC_Initstruct);
  /* 配置通道2 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH2,&TIM_OC_Initstruct);
  /* 配置通道3 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH3,&TIM_OC_Initstruct);
  /* 关闭所有通道输出 */
  LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1|LL_TIM_CHANNEL_CH1N|
                                LL_TIM_CHANNEL_CH2|LL_TIM_CHANNEL_CH2N|
                                LL_TIM_CHANNEL_CH3|LL_TIM_CHANNEL_CH3N);
}

/**
  * @brief  TIM1 6StepPWM配置函数
  * @param  无
  * @retval 无
  */
static void APP_ConfigTIM1Base(void)
{
  /* 配置TIM1 */
  LL_TIM_InitTypeDef TIM1CountInit = {0};
 
  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;  /* 时钟不分频 */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;      /* 向上计数模式 */
  TIM1CountInit.Prescaler           = 24-1;                       /* 预分频值：24 */
  TIM1CountInit.Autoreload          = 100-1;                      /* 自动重装载值：100 */
  TIM1CountInit.RepetitionCounter   = 0;                          /* 重复计数值：0 */
  
  /* 初始化TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);
  
  /* 配置TIM16步PWM相关通道 */
  APP_Config6StepPWMChannel();
  
  /* 使能COM中断 */
  LL_TIM_EnableIT_COM(TIM1);
  /* 设置COM中断优先级 */
  NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn,1);
  /* 使能COM中断NVIC IRQ */
  NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
  
  /* 使能预装载功能 */
  LL_TIM_CC_EnablePreload(TIM1);
  
  /* 主输出使能 */
  LL_TIM_EnableAllOutputs(TIM1);

  /* 使能TIM1计数器 */
  LL_TIM_EnableCounter(TIM1);
}

/**
  * @brief  TIM1 COM中断回调函数
  * @param  无
  * @retval 无
  */
void APP_COMCallback(void)
{
  switch(uwStep)
  {
    /* 第1步配置（起始状态） */
    case 0:
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);   /* CH1 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3N);  /* CH3N: 1 */
      uwStep++;
      break;
    /* 第2步配置 */
    case 1:
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);   /* CH1 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2N);  /* CH2N: 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3N); /* CH3N: 0 */
      uwStep++;
      break;
    /* 第3步配置 */
    case 2:
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1);  /* CH1 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2N);  /* CH2N: 1 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3);   /* CH3 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3N); /* CH3N: 0 */
      uwStep++;
      break;
    /* 第4步配置 */
    case 3:
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1);  /* CH1 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1N);  /* CH1N: 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3);   /* CH3 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3N); /* CH3N: 0 */
      uwStep++;
      break;
    /* 第5步配置 */
    case 4:
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1);  /* CH1 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1N);  /* CH1N: 1 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2);   /* CH2 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3N); /* CH3N: 0 */
      uwStep++;
      break;
    /* 第6步配置 */
    case 5:
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1);  /* CH1 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2);   /* CH2 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3N);  /* CH3N: 1 */
      uwStep++;
      break;
    /* 第1步配置 */
    case 6:
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);   /* CH1 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3N);  /* CH3N: 1 */
      uwStep = 1;
      break;
  }
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
