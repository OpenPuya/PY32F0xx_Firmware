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
RTC_HandleTypeDef RtcHandle;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 复位所有外设，初始化flash接口和systick.*/
  HAL_Init();
  
  /* 系统时钟配置 */
  APP_SystemClockConfig();
  
  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  /* 初始化按键BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);
  
  /* RTC初始化 */
  RtcHandle.Instance = RTC;                         /* 选择RTC */
  RtcHandle.Init.AsynchPrediv = RTC_AUTO_1_SECOND;  /* RTC一秒时基自动计算 */
  if (HAL_RTC_Init(&RtcHandle) != HAL_OK)
  {
  }
  
  /* 点亮小灯 */
  BSP_LED_On(LED_GREEN);
  
  /* 等待用户按键按下，主机程序开始运行 */
  while (BSP_PB_GetState(BUTTON_KEY) == 1)
  {
  }
  
  /* 关闭小灯 */
  BSP_LED_Off(LED_GREEN);
  
  /* 关闭systick中断，否则会中断唤醒 */
  HAL_SuspendTick();
  
  /* 进入STOP模式 */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  
  /* 打开systick中断 */
  HAL_ResumeTick();
  
  while (1)
  {
    BSP_LED_Toggle(LED_GREEN);
    HAL_Delay(500);
  }
}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
static void APP_SystemClockConfig(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};
  
  /* RCC振荡器初始化 */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI;
  oscinitstruct.HSIState        = RCC_HSI_ON;                                               /* 开启HSI */
  oscinitstruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz;                              /* 配置HSI输出时钟为8MHz */
  oscinitstruct.HSEState        = RCC_HSE_OFF;                                              /* 关闭HSE */
  oscinitstruct.LSIState        = RCC_LSI_ON;                                               /* 关闭LSE */
  if (HAL_RCC_OscConfig(&oscinitstruct) != HAL_OK)
  {
    while (1)
    {
    }
  }

  /* 初始化CPU,AHB,APB总线时钟 */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1); /* RCC系统时钟类型 */
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                                           /* SYSCLK的源选择为HSI */
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                               /* APH时钟不分频 */
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV1;                                                /* APB时钟不分频 */
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_1) != HAL_OK)
  {
    while (1)
    {
    }
  }
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
