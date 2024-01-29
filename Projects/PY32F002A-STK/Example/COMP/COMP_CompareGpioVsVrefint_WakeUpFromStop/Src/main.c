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
COMP_HandleTypeDef COMPINIT;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
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
  
  /* 系统时钟配置 */
  APP_SystemClockConfig(); 

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  /* 初始化按键BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  /* 关闭systick中断 */
  HAL_SuspendTick();

  /* 时钟设置初始化 */
  APP_RccInit();

  /* 初始化COMP */
  APP_CompInit();
 
  /* 使能中断 */
  APP_CompIt();
 
  /* 启动COMP */
  HAL_COMP_Start(&COMPINIT);
  
  BSP_LED_On(LED_GREEN);

  /* 等待按键按下 */
  while(BSP_PB_GetState(BUTTON_USER) != 0)
  {
  }
  BSP_LED_Off(LED_GREEN);

  /* 进入STOP模式 */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);  

  /* 恢复systick中断 */
  HAL_ResumeTick();

  HAL_Delay(1000);
  while(1)
  {
    APP_LedRun();
  }
}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* 振荡器配置 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI; /* 选择振荡器HSE,HSI,LSI */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                          /* 开启HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                          /* HSI 1分频 */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz;  /* 配置HSI时钟8MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                         /* 关闭HSE */
  /*RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz;*/
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                         /* 关闭LSI */

  /* 配置振荡器 */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* 时钟源配置 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* 选择配置时钟 HCLK,SYSCLK,PCLK1 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI; /* 选择HSI作为系统时钟 */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;     /* AHB时钟 1分频 */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;      /* APB时钟 1分频 */
  /* 配置时钟源 */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  比较器时钟切换函数
  * @param  无
  * @retval 无
  */
static void APP_RccInit(void)
{                    
  RCC_OscInitTypeDef RCCCONF;
  RCC_PeriphCLKInitTypeDef COMPRCC;
  
  RCCCONF.OscillatorType = RCC_OSCILLATORTYPE_LSI;        /* RCC使用内部LSI */
  RCCCONF.LSIState = RCC_LSI_ON;                          /* 开启LSI */
  
  COMPRCC.PeriphClockSelection = RCC_PERIPHCLK_COMP1;     /* 外设选择COMP1 */
  COMPRCC.Comp1ClockSelection = RCC_COMP1CLKSOURCE_LSC;   /* 外设独立时钟源选择LSC */

  HAL_RCC_OscConfig(&RCCCONF);                            /* 时钟初始化 */
  HAL_RCCEx_PeriphCLKConfig(&COMPRCC);                    /* RCC扩展外设时钟初始化 */
}

/**
  * @brief  比较器初始化函数
  * @param  无
  * @retval 无
  */
static void APP_CompInit(void)
{
  __HAL_RCC_COMP1_CLK_ENABLE();                           /* 使能COMP1时钟 */
  COMP_InitTypeDef COMPCONF={0};
  COMPINIT.Instance = COMP1;                              /* COMP1 */
  COMPCONF.Mode = COMP_POWERMODE_HIGHSPEED;               /* COMP1功耗选择为High speed */
  COMPCONF.InputPlus = COMP_INPUT_PLUS_IO3;               /* 正极引脚为PA1 */
  COMPCONF.InputMinus = COMP_INPUT_MINUS_VREFINT;         /* 负极选择为VREFINT */
  COMPCONF.TriggerMode = COMP_TRIGGERMODE_IT_FALLING;     /* 触发方式为下降沿中断触发 */
  COMPCONF.Hysteresis = COMP_HYSTERESIS_ENABLE;           /* 迟滞功能开启 */
  COMPINIT.Init = COMPCONF;                           
  
  HAL_COMP_Init(&COMPINIT);
}

/**
  * @brief  比较器中断使能函数
  * @param  无
  * @retval 无
  */
static void APP_CompIt(void)
{
  /*COMP中断使能*/
  HAL_NVIC_EnableIRQ(ADC_COMP_IRQn);
  HAL_NVIC_SetPriority(ADC_COMP_IRQn, 0x01, 0);
}

/**
  * @brief  LED翻转函数
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
  * @param  hcomp：比较器句柄
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
