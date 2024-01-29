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
uint32_t TIM1DataBuff[] = {2,200,3,300,4,400,5,500,6,600,7,700,8,800,9,900};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigTIM1Base(void);
static void APP_ConfigPWMChannel(void);
static void APP_ConfigDMABurst(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 配置系统时钟 */
  APP_SystemClockConfig();
  
  /* 使能TIM1、GPIO、DMA、SYSCFG时钟 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  
  /* 配置TIM1 PWM通道 */
  APP_ConfigPWMChannel();
  
  /* 配置DMA通道 */
  APP_ConfigDMABurst();
  
  /* 配置并开启TIM1 DMA Burst模式 */
  APP_ConfigTIM1Base();
  
  while (1)
  {
  }
}

/**
  * @brief  配置TIM1 PWM模式以及相关GPIO
  * @param  无
  * @retval 无
  */
static void APP_ConfigPWMChannel(void)
{
  LL_GPIO_InitTypeDef TIM1CH1MapInit= {0};
  LL_TIM_OC_InitTypeDef TIM_OC_Initstruct ={0};

  /* 配置PA3为TIM1_CH1 */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_3;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_13; 
  LL_GPIO_Init(GPIOA,&TIM1CH1MapInit);

  /* 配置PWM通道 */
  TIM_OC_Initstruct.OCMode        = LL_TIM_OCMODE_PWM1;     /* 通道模式：PWM1 */
  TIM_OC_Initstruct.OCState       = LL_TIM_OCSTATE_ENABLE;  /* 通道状态：开启 */
  TIM_OC_Initstruct.OCPolarity    = LL_TIM_OCPOLARITY_HIGH; /* 通道有效极性：高电平 */
  TIM_OC_Initstruct.OCIdleState   = LL_TIM_OCIDLESTATE_LOW; /* 通道空闲极性：低电平 */

  /* 通道1比较值:100 */
  TIM_OC_Initstruct.CompareValue  = 100;
  /* 配置通道1 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH1,&TIM_OC_Initstruct);
}

/**
  * @brief  配置DMA Burst传输
  * @param  无
  * @retval 无
  */
static void APP_ConfigDMABurst(void)
{
  
  LL_DMA_InitTypeDef DMA_TIM1DMABurst ={0};
  
  /* 配置DMA通道1 */
  DMA_TIM1DMABurst.PeriphOrM2MSrcAddress  = (uint32_t)&(TIM1->DMAR);           /* 目标地址 */
  DMA_TIM1DMABurst.MemoryOrM2MDstAddress  = (uint32_t)TIM1DataBuff;            /* 源地址 */
  DMA_TIM1DMABurst.Direction              = LL_DMA_DIRECTION_MEMORY_TO_PERIPH; /* 传输方向：存储器到内存 */
  DMA_TIM1DMABurst.Mode                   = LL_DMA_MODE_NORMAL;                /* 普通模式 */
  DMA_TIM1DMABurst.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT;         /* 禁用外设地址增量 */
  DMA_TIM1DMABurst.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;           /* 启用内存地址增量 */
  DMA_TIM1DMABurst.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_WORD;            /* 数据大小字对齐 */
  DMA_TIM1DMABurst.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_WORD;            /* 数据大小字对齐 */
  DMA_TIM1DMABurst.Priority               = LL_DMA_PRIORITY_MEDIUM;            /* 通道优先级：中等 */
  DMA_TIM1DMABurst.NbData                 = 16;                                /* 数据量：16 */
  /* 初始化DMA通道1 */
  LL_DMA_Init(DMA1,LL_DMA_CHANNEL_1,&DMA_TIM1DMABurst);
  
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
  * @brief  配置TIM base
  * @param  无
  * @retval 无
  */
static void APP_ConfigTIM1Base(void)
{
  /* 配置TIM1 */
  LL_TIM_InitTypeDef TIM1CountInit = {0};
 
  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1; /* 时钟不分频 */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;     /* 向上计数模式 */
  TIM1CountInit.Prescaler           = 24-1;                      /* 预分频值：24 */
  TIM1CountInit.Autoreload          = 1000-1;                    /* 自动重装载值：1000 */
  TIM1CountInit.RepetitionCounter   = 1;                         /* 重复计数值：1 */
  
  /* 初始化TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit); 
  
  /* 开启更新事件DMA请求 */
  LL_TIM_EnableDMAReq_UPDATE(TIM1);
  
  /* 开启DMA突发传输 */
  LL_TIM_ConfigDMABurst(TIM1,LL_TIM_DMABURST_BASEADDR_RCR,LL_TIM_DMABURST_LENGTH_2TRANSFERS);
  
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
