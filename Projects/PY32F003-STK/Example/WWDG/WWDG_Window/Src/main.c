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
#define WINDOW_IN                                   /* 窗口时间内喂狗 */
/* #define WINDOW_UPPER */                          /* 窗口时间上限外喂狗 */
/* #define WINDOW_LOWER */                          /* 窗口时间下限外喂狗 */


/* Private variables ---------------------------------------------------------*/
WWDG_HandleTypeDef   WwdgHandle;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint32_t APP_TimeoutCalculation(uint32_t timevalue);

/**
  * @brief  应用程序入口函数.
  * @param  无
  * @retval int
  */
int main(void)
{
  uint32_t delay;

  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET)
  {
    /* LED 亮 */
    BSP_LED_On(LED_GREEN);

    /* 等待4s */
    HAL_Delay(4000);

    /* LED 灭 */
    BSP_LED_Off(LED_GREEN);

    /* 等待500ms */
    HAL_Delay(500);

    /* 清除复位状态标志位 */
    __HAL_RCC_CLEAR_RESET_FLAGS();
  }
  else
  {
    /* LED 灭 */
    BSP_LED_Off(LED_GREEN);
  }

  /* WWDG模块初始化 */
  WwdgHandle.Instance = WWDG;                                           /* 选择WWDG */
  WwdgHandle.Init.Prescaler = WWDG_PRESCALER_8;                         /* 选择8分频 */
  WwdgHandle.Init.Window    = 0x50;                                     /* 7位窗口值为0x40~0x50 */
  WwdgHandle.Init.Counter   = 0x7F;                                     /* 计数器值(7位) */
  WwdgHandle.Init.EWIMode   = WWDG_EWI_DISABLE;                         /* 关闭提前唤醒中断 */
  if (HAL_WWDG_Init(&WwdgHandle) != HAL_OK)                             /* WWDG初始化 */
  {
    APP_ErrorHandler();
  }

#if defined(WINDOW_IN)
  delay = APP_TimeoutCalculation((WwdgHandle.Init.Counter - WwdgHandle.Init.Window) + 1) + 1;   /* 窗口时间内 */
#elif defined(WINDOW_UPPER)
  delay = APP_TimeoutCalculation((WwdgHandle.Init.Counter - WwdgHandle.Init.Window)-5 ) + 1;    /* 窗口时间上限外 */
#else 
  delay = APP_TimeoutCalculation((WwdgHandle.Init.Counter - 0x3f) +5) + 1;                      /* 窗口时间下线外 */
#endif

  /* 无限循环 */
  while (1)
  {
    BSP_LED_Toggle(LED_GREEN);

    /* 插入上面计算好的延时 */
    HAL_Delay(delay);

    /* 更新看门狗计数器 */
    if (HAL_WWDG_Refresh(&WwdgHandle) != HAL_OK)
    {
      APP_ErrorHandler();
    }
  }
}

/**
  * @brief  计算超时时间函数
  * @param  timeout：时间
  * @retval int
  */
static uint32_t APP_TimeoutCalculation(uint32_t timevalue)
{
  uint32_t timeoutvalue = 0;
  uint32_t pclk1 = 0;
  uint32_t wdgtb = 0;
  /* 获取PCLK的值 */
  pclk1 = HAL_RCC_GetPCLK1Freq();
  /* 获取分频值 */
  wdgtb = (1 << ((WwdgHandle.Init.Prescaler) >> 7)); /* 2^WDGTB[1:0] */
  /* 计算超时时间 */
  timeoutvalue = ((4096 * wdgtb * timevalue) / (pclk1 / 1000));
  return timeoutvalue;
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
