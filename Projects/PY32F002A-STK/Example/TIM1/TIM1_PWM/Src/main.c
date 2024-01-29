/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
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
#define  PERIOD_VALUE       (uint32_t)(50 - 1)
#define  PULSE1_VALUE       10
#define  PULSE2_VALUE       20
#define  PULSE3_VALUE       30
#define  PULSE4_VALUE       40
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef sConfig;

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Error_Handler(void);
static void APP_TIM1_INIT(void);
static void APP_TIM1_PWM(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();
  
  APP_TIM1_INIT();

  APP_TIM1_PWM();

  /* 通道1开始输出PWM */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)                  
  {
    Error_Handler();
  }

  /* 通道2开始输出PWM */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_2) != HAL_OK)                  
  {
    Error_Handler();
  }

  /* 通道3开始输出PWM */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_3) != HAL_OK)                  
  {
    Error_Handler();
  }

  /* 通道4开始输出PWM */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_4) != HAL_OK)                  
  {
    Error_Handler();
  }

  /* 无限循环 */
  while (1)
  {


  }
}
/**
  * @brief  TIM1初始化函数
  * @param  无
  * @retval 无
  */
static void APP_TIM1_INIT(void)
{
  /* 选择TIM1 */
  TimHandle.Instance = TIM1;                                                  
  
  /* 自动重装载值 */
  TimHandle.Init.Period            = 50;                                     

  /* 预分频为800-1 */
  TimHandle.Init.Prescaler         = 800 - 1;                                 

  /* 时钟不分频 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                  

  /* 向上计数*/
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                      

  /* 不重复计数 */
  TimHandle.Init.RepetitionCounter = 1 - 1;                                   

  /* 自动重装载寄存器没有缓冲 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;          

  /* 基础时钟初始化 */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                                
  {
    Error_Handler();
  }

}
/**
  * @brief  TIM1 PWM配置
  * @param  无
  * @retval 无
  */
static void APP_TIM1_PWM(void)
{
  /*输出配置为翻转模式 */
  sConfig.OCMode       = TIM_OCMODE_PWM1;                                     

  /*OC通道输出高电平有效 */
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;                                 

  /*输出快速使能关闭 */
  sConfig.OCFastMode   = TIM_OCFAST_DISABLE;                                  

  /*OCN通道输出高电平有效 */
  sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                

  /*空闲状态OC1N输出低电平 */
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;                              

  /*空闲状态OC1输出低电平*/
  sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;                               

  /*CC1值为10，占空比=10/50=20%*/
  sConfig.Pulse = PULSE1_VALUE;                                              

  /* 通道1配置 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  /* CC2值为20,占空比=20/50=40% */
  sConfig.Pulse = PULSE2_VALUE;                                               

  /* 通道2配置 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }

  /*CC3值为30,占空比=30/50=60%*/
  sConfig.Pulse = PULSE3_VALUE;                                              

  /* 通道3配置 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_3) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }

  /* CC4值为40,占空比=40/50=80% */
  sConfig.Pulse = PULSE4_VALUE;                                               

  /*通道4配置 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void Error_Handler(void)
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

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
