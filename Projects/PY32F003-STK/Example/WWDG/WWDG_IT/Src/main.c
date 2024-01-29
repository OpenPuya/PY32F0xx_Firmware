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
WWDG_HandleTypeDef   WwdgHandle;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  应用程序入口函数.
  * @param  无
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();                                       

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  /* WWDG模块初始化 */
  WwdgHandle.Instance = WWDG;                        /* 选择WWDG */
  WwdgHandle.Init.Prescaler = WWDG_PRESCALER_8;      /* 选择8分频 */
  WwdgHandle.Init.Window    = 127;                   /* 7位窗口值为0x40~0x7f */
  WwdgHandle.Init.Counter   = 127;                   /* 计数器值(7位) */
  WwdgHandle.Init.EWIMode   = WWDG_EWI_ENABLE;       /* 使能提前唤醒中断 */
  /* WWDG初始化 */
  if (HAL_WWDG_Init(&WwdgHandle) != HAL_OK)          
  {
    APP_ErrorHandler();
  }
  /* 喂狗 */
  if (HAL_WWDG_Refresh(&WwdgHandle) != HAL_OK)       
  {
    APP_ErrorHandler();
  }

  while (1)
  {
    /* 等待500ms */
    HAL_Delay(500);
    
    /* 翻转LED */
    BSP_LED_Toggle(LED_GREEN);                
  }
}

/**
  * @brief  WWDG提前唤醒函数
  * @param  hwwdg：WWDG句柄
  * @retval 无
  */
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
  /* 喂狗 */
  if (HAL_WWDG_Refresh(hwwdg) != HAL_OK)     
  {
    APP_ErrorHandler();
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
