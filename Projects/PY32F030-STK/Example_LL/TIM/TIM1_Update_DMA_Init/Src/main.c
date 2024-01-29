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
uint32_t TIM1ReloadCounter[9] = {900-1,800-1,700-1,600-1,500-1,400-1,300-1,200-1,100-1};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigTIM1Count(void);
static void APP_ConfigDMATIM1Reload(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 使能TIM1、DMA、SYSCFG时钟 */
  LL_APB1_GRP2_EnableClock(RCC_APBENR2_TIM1EN);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  
  /* 配置系统时钟 */
  APP_SystemClockConfig();
  
  /* 初始化LED */
  BSP_LED_Init(LED3);
  
  /* 配置并开启DMA */
  APP_ConfigDMATIM1Reload();
  
  /* 配置并开启TIM1计数模式 */
  APP_ConfigTIM1Count();
  
  while (1)
  {
  }
}

/**
  * @brief  配置TIM计数模式
  * @param  无
  * @retval 无
  */
static void APP_ConfigTIM1Count(void)
{
  /* 配置TIM1 */
  LL_TIM_InitTypeDef TIM1CountInit = {0};
  
  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1; /* 时钟不分频 */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;     /* 向上计数模式 */
  TIM1CountInit.Prescaler           = 8000-1;                    /* 预分频值：8000 */
  TIM1CountInit.Autoreload          = 1000-1;                    /* 自动重装载值：1000 */
  TIM1CountInit.RepetitionCounter   = 0;                         /* 重复计数值：0 */
  
  /* 初始化TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);
  
  /* 使能UPDATE中断 */
  LL_TIM_EnableIT_UPDATE(TIM1);
  
  /* 使能更新中断DMA请求 */
  LL_TIM_EnableDMAReq_UPDATE(TIM1);
  
  /* 使能TIM1计数器 */
  LL_TIM_EnableCounter(TIM1);
  
  /* 开启UPDATE中断请求 */
  NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
  NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn,0);
}

/**
  * @brief  配置DMA传输
  * @param  无
  * @retval 无
  */
static void APP_ConfigDMATIM1Reload(void)
{
  
  LL_DMA_InitTypeDef DMA_TIM1Reload ={0};
  
  /* 配置DMA通道1 */
  DMA_TIM1Reload.PeriphOrM2MSrcAddress  = (uint32_t)&(TIM1->ARR);
  DMA_TIM1Reload.MemoryOrM2MDstAddress  = (uint32_t)TIM1ReloadCounter;
  DMA_TIM1Reload.Direction              = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  DMA_TIM1Reload.Mode                   = LL_DMA_MODE_NORMAL;
  DMA_TIM1Reload.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT;
  DMA_TIM1Reload.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;
  DMA_TIM1Reload.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_WORD;
  DMA_TIM1Reload.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_WORD;
  DMA_TIM1Reload.NbData                 = 9;
  DMA_TIM1Reload.Priority               = LL_DMA_PRIORITY_MEDIUM;
  
  /* 初始化DMA通道1 */
  LL_DMA_Init(DMA1,LL_DMA_CHANNEL_1,&DMA_TIM1Reload);
  
  /* 将TIM1更新中断映射到通道1 */
  LL_SYSCFG_SetDMARemap_CH1(LL_SYSCFG_DMA_MAP_TIM1_UP);
  
  /* 使能DMA传输完成中断 */
  LL_DMA_EnableIT_TC(DMA1,LL_DMA_CHANNEL_1);
  
  /* 使能DMA通道1 */
  LL_DMA_EnableChannel(DMA1,LL_DMA_CHANNEL_1);
  
  /* 使能DMA通道1中断请求 */
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  NVIC_SetPriority(DMA1_Channel1_IRQn,0);
}

/**
  * @brief  TIM更新中断回调函数
  * @param  无
  * @retval 无
  */
void APP_UpdateCallback(void)
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
