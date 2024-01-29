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
#define STATE_OVER_THRESHOLD    0x00000001
#define STATE_WITHIN_THRESHOLD  0x00000002
#define STATE_UNDER_THRESHOLD   0x00000003

/* Private variables ---------------------------------------------------------*/
COMP_HandleTypeDef  hcomp1, hcomp2;
__IO uint32_t State = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_CompInit(void);
static void APP_InputVoltageLevelCheck(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();

  /* 初始化LED */  
  BSP_LED_Init(LED_GREEN);

  /* 配置比较器 */
  APP_CompInit();
  while (1)
  {
    APP_InputVoltageLevelCheck();                                        /* 输入电压检测 */
    if (State == STATE_OVER_THRESHOLD)
    {
      BSP_LED_Toggle(LED_GREEN);
      HAL_Delay(200);
    }
    else if (State == STATE_WITHIN_THRESHOLD)
    {
      BSP_LED_On(LED_GREEN);
    }
    else
    {
      BSP_LED_Off(LED_GREEN);
    }
  }
}

/**
  * @brief  比较器初始化
  * @param  无
  * @retval 无
  */
static void APP_CompInit(void)
{
  hcomp1.Instance             = COMP1;                                   /* 选择COMP1 */
  hcomp1.Init.InputMinus      = COMP_INPUT_MINUS_VREFINT;                /* 负输入为VREF(1.2V) */
  hcomp1.Init.InputPlus       = COMP_INPUT_PLUS_IO3;                     /* 正输入选择为PA1 */
  hcomp1.Init.OutputPol       = COMP_OUTPUTPOL_NONINVERTED;              /* COMP1极性选择为不反向 */
  hcomp1.Init.Mode            = COMP_POWERMODE_HIGHSPEED;                /* COMP1功耗模式选择为High speed模式 */
  hcomp1.Init.Hysteresis      = COMP_HYSTERESIS_DISABLE;                 /* 迟滞功能关闭 */
  hcomp1.Init.WindowMode      = COMP_WINDOWMODE_COMP1_INPUT_PLUS_COMMON; /* 窗口模式 */
  hcomp1.Init.TriggerMode     = COMP_TRIGGERMODE_IT_RISING_FALLING;      /* COMP1上升/下降沿中断 */
  /* COMP1初始化 */
  if (HAL_COMP_Init(&hcomp1) != HAL_OK)                                  
  {
    APP_ErrorHandler();
  }
  /* COMP1启动 */
  HAL_COMP_Start(&hcomp1);                                               

  hcomp2.Instance             = COMP2;                                   /* 选择COMP2 */
  hcomp2.Init.InputMinus      = COMP_INPUT_MINUS_1_4VREFINT;             /* 负输入为VREF(0.3V) */
  hcomp2.Init.InputPlus       = COMP_INPUT_PLUS_IO3;                     /* 正输入选择为PA3 */
  hcomp2.Init.OutputPol       = COMP_OUTPUTPOL_NONINVERTED;              /* COMP2极性选择为不反向 */
  hcomp2.Init.Mode            = COMP_POWERMODE_HIGHSPEED;                /* COMP2功耗模式选择为High speed模式 */
  hcomp2.Init.Hysteresis      = COMP_HYSTERESIS_DISABLE;                 /* 迟滞功能关闭 */
  hcomp2.Init.WindowMode      = COMP_WINDOWMODE_COMP1_INPUT_PLUS_COMMON; /* 窗口模式 */
  hcomp2.Init.TriggerMode     = COMP_TRIGGERMODE_IT_RISING_FALLING;      /* COMP2上升/下降沿中断 */
  /* COMP2初始化 */
  if (HAL_COMP_Init(&hcomp2) != HAL_OK)                                 
  {
    APP_ErrorHandler();
  }
  /* COMP2启动 */
  HAL_COMP_Start(&hcomp2);                                               
}

/**
  * @brief  电压比较函数
  * @param  无
  * @retval 无
  */
static void APP_InputVoltageLevelCheck(void)
{
  /* 检查COMP1和COMP2输出 */
  if (((HAL_COMP_GetOutputLevel(&hcomp1)) == COMP_OUTPUT_LEVEL_HIGH)
      && ((HAL_COMP_GetOutputLevel(&hcomp2)) == COMP_OUTPUT_LEVEL_HIGH))
  {
    State = STATE_OVER_THRESHOLD;
  }
  else if (((HAL_COMP_GetOutputLevel(&hcomp1)) == COMP_OUTPUT_LEVEL_LOW)
           && ((HAL_COMP_GetOutputLevel(&hcomp2)) == COMP_OUTPUT_LEVEL_HIGH))
  {
    State = STATE_WITHIN_THRESHOLD;   
  }
  else if (((HAL_COMP_GetOutputLevel(&hcomp1)) == COMP_OUTPUT_LEVEL_LOW)
           && ((HAL_COMP_GetOutputLevel(&hcomp2)) == COMP_OUTPUT_LEVEL_LOW))
  {
    State = STATE_UNDER_THRESHOLD;
  }
}

/**
  * @brief  比较器触发函数
  * @param  hcomp：COMP句柄
  * @retval 无
  */
void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp)
{
  APP_InputVoltageLevelCheck();
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
