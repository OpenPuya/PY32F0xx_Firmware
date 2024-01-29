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
static void APP_ConfigTIM1Encoder(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 使能TIM1、GPIOA时钟 */
  LL_APB1_GRP2_EnableClock(RCC_APBENR2_TIM1EN);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* 配置系统时钟 */
  APP_SystemClockConfig();
  
  /* 初始化LED、USART */
  BSP_LED_Init(LED3);
  BSP_USART_Config();
  
  /* 配置并开启TIM1编码器模式 */
  APP_ConfigTIM1Encoder();
  
  while (1)
  {
  }
}

/**
  * @brief  配置TIM编码器模式
  * @param  无
  * @retval 无
  */
static void APP_ConfigTIM1Encoder(void)
{
  LL_TIM_InitTypeDef TIM1CountInit = {0};
  LL_TIM_ENCODER_InitTypeDef TIM1EncoderInit = {0};
  LL_GPIO_InitTypeDef TIM1ChannelInit = {0};

  TIM1CountInit.Prescaler           = 1-1;    /* 不分频 */
  TIM1CountInit.Autoreload          = 1000-1; /* 自动重装载值：1000 */
  TIM1CountInit.RepetitionCounter   = 0;      /* 重复计数值：0 */
  
  /* 初始化TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);
  
  /* 开启CH1和CH2捕获中断 */
  LL_TIM_EnableIT_CC1(TIM1);
  LL_TIM_EnableIT_CC2(TIM1);
  NVIC_EnableIRQ(TIM1_CC_IRQn);
  
  /* 配置Encoder */
  LL_TIM_SetEncoderMode(TIM1,LL_TIM_ENCODERMODE_X4_TI12);

  TIM1EncoderInit.EncoderMode     = LL_TIM_ENCODERMODE_X4_TI12;   /* 编码器模式：模式3  */
  TIM1EncoderInit.IC1Polarity     = LL_TIM_IC_POLARITY_BOTHEDGE;  /* 输入捕获1有效边沿：双边沿 */
  TIM1EncoderInit.IC1ActiveInput  = LL_TIM_ACTIVEINPUT_DIRECTTI;  /* 输入捕获1有效输入：TI1 */
  TIM1EncoderInit.IC1Filter       = LL_TIM_IC_FILTER_FDIV1;       /* 输入捕获1滤波值：无滤波 */
  TIM1EncoderInit.IC1Prescaler    = LL_TIM_ICPSC_DIV1;            /* 输入捕获1预分频值：1 */
  TIM1EncoderInit.IC2Polarity     = LL_TIM_IC_POLARITY_BOTHEDGE;  /* 输入捕获2有效边沿：双边沿 */
  TIM1EncoderInit.IC2ActiveInput  = LL_TIM_ACTIVEINPUT_DIRECTTI;  /* 输入捕获2有效输入：TI2 */
  TIM1EncoderInit.IC2Filter       = LL_TIM_IC_FILTER_FDIV1;       /* 输入捕获2滤波值：无滤波 */
  TIM1EncoderInit.IC2Prescaler    = LL_TIM_ICPSC_DIV1;            /* 输入捕获2预分频值：1 */
  
  /* 初始化Encoder配置 */
  LL_TIM_ENCODER_Init(TIM1,&TIM1EncoderInit);
  
  /* TI1和TI2映射到PA8和PA9 */
  TIM1ChannelInit.Pin       = LL_GPIO_PIN_8 | LL_GPIO_PIN_9;
  TIM1ChannelInit.Mode      = LL_GPIO_MODE_ALTERNATE;
  TIM1ChannelInit.Alternate = LL_GPIO_AF_2;
  LL_GPIO_Init(GPIOA,&TIM1ChannelInit);
  
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
  * @brief  捕获回调函数
  * @param  无
  * @retval 无
  */
void APP_CCCallback(void)
{
  printf("Count:%d\r\n",LL_TIM_GetCounter(TIM1));
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
