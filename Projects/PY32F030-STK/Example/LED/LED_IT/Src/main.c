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
const uint8_t dispArr[] = {LED_DISP_0, LED_DISP_1, LED_DISP_2, LED_DISP_3, LED_DISP_4, \
                           LED_DISP_5, LED_DISP_6, LED_DISP_7, LED_DISP_8, LED_DISP_9};
uint8_t dispNum = 0;
LED_HandleTypeDef hled;
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief   应用程序入口函数
  * @retval  int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();
  
  /* LED初始化 */
  hled.Instance = LED;
  hled.Init.ComNum = 4 - 1;               /* 4个COM口均打开 */
  hled.Init.ComDrive = LED_COMDRIVE_LOW;  /* LED 非COM输出 */
  hled.Init.Prescaler = 10 - 1;           /* Fpclk/(PR+1) */
  hled.Init.LightTime = 0xF0;             /* 每个LED被点亮的时间  */
  hled.Init.DeadTime = 0x10;              /* 两个LED切换的间歇时间,间歇时间不能为零 */
  HAL_LED_Init(&hled);

  /* 无限循环 */
  while (1)
  {
    dispNum++;
    if (dispNum == 10)
    {
      dispNum = 0;
    }
    HAL_Delay(1000);
  }
}

/**
  * @brief   LED中断回调执行函数
  * @param   无
  * @retval  无
  */
void HAL_LED_LightCpltCallback(LED_HandleTypeDef *hled)
{
  static uint32_t oldValue = 0xFF;

  if (oldValue != dispNum)
  {
    oldValue = dispNum;
    HAL_LED_SetComDisplay(hled, LED_COM0, dispArr[(dispNum) % 10]);
    HAL_LED_SetComDisplay(hled, LED_COM1, dispArr[(dispNum + 1) % 10]);
    HAL_LED_SetComDisplay(hled, LED_COM2, dispArr[(dispNum + 2) % 10]);
    HAL_LED_SetComDisplay(hled, LED_COM3, dispArr[(dispNum + 3) % 10]);
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
