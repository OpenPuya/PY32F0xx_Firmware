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
COMP_HandleTypeDef  hcomp1;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();                                                           

  /* 初始化按键 */  
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
  
  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  hcomp1.Instance = COMP1;                                              /* 选择COMP1 */
  hcomp1.Init.InputMinus      = COMP_INPUT_MINUS_VREFINT;               /* 负输入为VREF(1.2V) */
  hcomp1.Init.InputPlus       = COMP_INPUT_PLUS_IO3;                    /* 正输入选择为PA1 */
  hcomp1.Init.OutputPol       = COMP_OUTPUTPOL_NONINVERTED;             /* COMP1极性选择为不反向 */
  hcomp1.Init.Mode            = COMP_POWERMODE_HIGHSPEED;               /* COMP1功耗模式选择为High speed模式 */
  hcomp1.Init.Hysteresis      = COMP_HYSTERESIS_DISABLE;                /* 迟滞功能关闭 */
  hcomp1.Init.WindowMode      = COMP_WINDOWMODE_DISABLE;                /* 窗口模式关闭 */
  hcomp1.Init.TriggerMode     = COMP_TRIGGERMODE_IT_RISING_FALLING;     /* COMP1上升/下降沿触发 */
  /* COMP1初始化 */
  if (HAL_COMP_Init(&hcomp1) != HAL_OK)                                 
  {
    APP_ErrorHandler();
  }
  /* COMP1启动 */
  HAL_COMP_Start(&hcomp1);                                              

  while (1)
  {
  }
}

/**
  * @brief  比较器中断回调函数
  * @param  hcomp：COMP句柄
  * @retval 无
  */
void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp)
{
  BSP_LED_Toggle(LED_GREEN);
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
