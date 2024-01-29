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
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);

/**
  * @brief   应用程序入口函数
  * @retval  int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();

  /* 初始化用户按键 */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
  
  /* 配置PA08引脚为MCO功能，输出系统时钟 */
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
  
  /* 等待按键按下使能HSE */
  while (BSP_PB_GetState(BUTTON_KEY) == 1)
  {
  }

  /* 配置系统时钟为HSE，PCLK不分频，HCLK二分频 */
  APP_SystemClockConfig();

  /* 无限循环 */
  while (1)
  {
  }
}

/**
  * @brief   系统时钟配置函数
  * @param   无
  * @retval  无
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;                                   /* 选择RCC振荡器为HSE */
  /* RCC_OscInitStruct.HSIState = RCC_HSI_ON; */                                               /* 开启HSI */
  /* RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV4; */                                               /* 4分频 */
  /* RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz; */                       /* 配置HSI输出时钟为8MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;                                                     /* 开启HSE */
  RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz;                                                /* HSE晶振工作频率16M~32M */
  /* RCC_OscInitStruct.LSIState = RCC_LSI_OFF; */                                              /* 关闭LSI */
  /* RCC_OscInitStruct.LSEState = RCC_LSE_OFF; */                                              /* 关闭LSE */
  /* RCC_OscInitStruct.LSEDriver = RCC_ECSCR_LSE_DRIVER_1; */                                  /* LSE默认驱动能力 */
  /* RCC_OscInitStruct.PLL.PLLState = RCC_PLL_OFF; */                                          /* 关闭PLL */
  /* RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE; */                                   /* 选择PLL源为HSE */
  /* 初始化RCC振荡器 */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* 初始化CPU,AHB,APB总线时钟 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;/* RCC系统时钟类型 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;                                        /* SYSCLK的源选择为HSE */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                            /* APH时钟不分频 */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;                                             /* APB时钟2分频 */
  /* 初始化RCC系统时钟(FLASH_LATENCY_0=24M以下;FLASH_LATENCY_1=48M) */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief   错误执行函数
  * @param   无
  * @retval  无
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
