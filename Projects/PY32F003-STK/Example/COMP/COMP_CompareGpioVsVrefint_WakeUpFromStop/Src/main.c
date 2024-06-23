/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
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
COMP_HandleTypeDef hcomp1;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_RccInit(void);
static void APP_CompInit(void);
static void APP_CompIt(void);
static void APP_LedRun(void);

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

  /* 关闭systick中断 */
  HAL_SuspendTick();

  /* 时钟设置初始化 */
  APP_RccInit();

  /* COMP初始化 */
  APP_CompInit();

  /* 中断使能 */
  APP_CompIt();
  
  /* COMP启动 */
  HAL_COMP_Start(&hcomp1);

  BSP_LED_On(LED_GREEN);

  /* 等待按键按下 */
  while (BSP_PB_GetState(BUTTON_USER) != 0)
  {
  }

  BSP_LED_Off(LED_GREEN);

  /* 进入STOP模式 */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

  /* 恢复systick中断 */
  HAL_ResumeTick();
  HAL_Delay(1000);
  while (1)
  {
    APP_LedRun();
  }
}

/**
  * @brief  时钟初始化
  * @param  无
  * @retval 无
  */
static void APP_RccInit(void)
{
  RCC_OscInitTypeDef RCCCONF       = {0};
  RCC_PeriphCLKInitTypeDef COMPRCC = {0};

  RCCCONF.OscillatorType = RCC_OSCILLATORTYPE_LSI;        /* RCC使用内部LSI */
  RCCCONF.LSIState = RCC_LSI_ON;                          /* 开启LSI */

  COMPRCC.PeriphClockSelection = RCC_PERIPHCLK_COMP1;     /* RCC扩展外设时钟为RTC */
  COMPRCC.Comp1ClockSelection = RCC_COMP1CLKSOURCE_LSC;   /* 外设独立时钟源选择LSC */

  HAL_RCC_OscConfig(&RCCCONF);                            /* 时钟初始化 */
  HAL_RCCEx_PeriphCLKConfig(&COMPRCC);                    /* RCC扩展外设时钟初始化 */
}

/**
  * @brief  比较器初始化
  * @param  无
  * @retval 无
  */
static void APP_CompInit(void)
{
  __HAL_RCC_COMP1_CLK_ENABLE();                              /* 使能COMP1时钟 */

  hcomp1.Instance = COMP1;                                   /* COMP1 */

  hcomp1.Init.InputPlus = COMP_INPUT_PLUS_IO3;               /* 正端输入: PA1 */
  hcomp1.Init.InputMinus = COMP_INPUT_MINUS_VREFINT;         /* 负端输入: VREFINT */
  hcomp1.Init.OutputPol = COMP_OUTPUTPOL_NONINVERTED;        /* 输出不反向 */
  hcomp1.Init.Mode = COMP_POWERMODE_MEDIUMSPEED;             /* 功耗低速 */
  hcomp1.Init.Hysteresis = COMP_HYSTERESIS_ENABLE;           /* 延迟使能 */
  hcomp1.Init.WindowMode = COMP_WINDOWMODE_DISABLE;          /* 窗口模式关闭 */
  hcomp1.Init.TriggerMode = COMP_TRIGGERMODE_IT_FALLING;     /* 下降沿触发 */
  hcomp1.Init.DigitalFilter = 0;                         
  HAL_COMP_Init(&hcomp1);
}

/**
  * @brief  比较器中断
  * @param  无
  * @retval 无
  */
static void APP_CompIt(void)
{
  /* COMP中断使能 */
  HAL_NVIC_EnableIRQ(ADC_COMP_IRQn);
  HAL_NVIC_SetPriority(ADC_COMP_IRQn, 0x01, 0);
}

/**
  * @brief  LED翻转
  * @param  无
  * @retval 无
  */
static void APP_LedRun(void)
{
  BSP_LED_Toggle(LED_GREEN);
  HAL_Delay(200);
  BSP_LED_Toggle(LED_GREEN);
  HAL_Delay(200);
}

/**
  * @brief  比较器中断回调函数
  * @param  无
  * @retval 无
  */
void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp)
{
  BSP_LED_On(LED_GREEN);
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
