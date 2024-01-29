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
#include "py32f002xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void APP_SystemClockConfig(void);
void APP_ConfigEXTI(void);
void Enter_Sleep(void);
void GPIO_Config(void);
static void APP_LED_run(void);

/**
  * @brief  应用程序入口函数.
  * @param  无
  * @retval int
  */
int main(void)
{
  /* 配置系统时钟 */
  APP_SystemClockConfig();

   /*初始化LED*/
  BSP_LED_Init(LED_GREEN);
  /*关闭LED*/
  BSP_LED_Off(LED_GREEN);
  /*外部中断初始化*/
  APP_ConfigEXTI();
  
  /*LED亮*/
  BSP_LED_On(LED_GREEN);
  /*延时200ms*/
  LL_mDelay(200);
  /*LED灭*/
  BSP_LED_Off(LED_GREEN);;
  
  /*进入SLEEP模式*/
  Enter_Sleep();

  while (1)
  {
    APP_LED_run();
  }
}


/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
void APP_SystemClockConfig(void)
{
 /* HSI使能及初始化 */
  LL_RCC_HSI_Enable();
  LL_RCC_HSI_SetCalibFreq(LL_RCC_HSICALIBRATION_24MHz);
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }
  
  
  /* 设置AHB分频*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
   
  /* 配置HSISYS为系统时钟及初始化 */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }
  
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  
  /*设置APB1分频及初始化*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(24000000);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(24000000);
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void APP_ConfigEXTI(void)
{
   /*GPIOA时钟使能*/
   LL_IOP_GRP1_EnableClock (LL_IOP_GRP1_PERIPH_GPIOA);
  
   LL_GPIO_InitTypeDef GPIO_InitStruct;
   /*选择PA06引脚*/
   GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
   /*选择输入模式*/
   GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
   /*选择下拉*/
   GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
   /*GPIOA初始化*/
   LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   /*选择EXTI6做外部中断输入*/
   LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTA,LL_EXTI_CONFIG_LINE6);

   LL_EXTI_InitTypeDef EXTI_InitStruct;
   /*选择EXTI6*/
   EXTI_InitStruct.Line = LL_EXTI_LINE_6;
   /*使能*/
   EXTI_InitStruct.LineCommand = ENABLE;
   /*选择中断模式*/
   EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
   /*选择上升沿触发*/
   EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
   /*外部中断初始化*/
   LL_EXTI_Init(&EXTI_InitStruct);
   
   /*设置中断优先级*/
   NVIC_SetPriority(EXTI4_15_IRQn,1);
   /*使能中断*/
   NVIC_EnableIRQ(EXTI4_15_IRQn);
}

/**
  * @brief  进入SLEEP模式
  * @param  无
  * @retval 无
  */
void Enter_Sleep(void)
{
  /*使能PWR时钟*/
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  
  /*进入Sleep模式*/
  LL_LPM_EnableSleep();
  
  /*等待中断指令*/
  __WFI();
}
/**
  * @brief  LED运行配置
  * @param  无
  * @retval 无
  */
static void APP_LED_run(void)
{
  /*翻转LED灯*/
  BSP_LED_Toggle(LED_GREEN);
  /*延时200ms*/
  LL_mDelay(200);
  /*翻转LED灯*/
  BSP_LED_Toggle(LED_GREEN);
  /*延时200ms*/
  LL_mDelay(200);
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
