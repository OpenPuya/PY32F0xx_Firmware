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
#define APP_GPIO_TOGGLE()  {GPIOB->BSRR = u32High;\
                            GPIOB->BSRR = u32Low; \
                            GPIOB->BSRR = u32High;\
                            GPIOB->BSRR = u32Low; \
                            GPIOB->BSRR = u32High;\
                            GPIOB->BSRR = u32Low; \
                            GPIOB->BSRR = u32High;\
                            GPIOB->BSRR = u32Low; \
                            GPIOB->BSRR = u32High;\
                            GPIOB->BSRR = u32Low;}

/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_GpioInit(void);
static void APP_SystemClockConfig(void);

/**
  * @brief  应用程序入口函数.
  * @param  无
  * @retval int
  */
int main(void)
{
  /* PB5 */
  uint32_t u32High = 0x00000020;
  uint32_t u32Low  = 0x00200000;
  
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();      
  
  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);
  
  /* 初始化GPIO */
  APP_GpioInit();                                 
  
  /* 配置系统时钟 */
  APP_SystemClockConfig();                         
  
  while (1)
  {
    /* LED 翻转输出约12MHz */
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
  }
}

/**
  * @brief  GPIO初始化
  * @param  无
  * @retval 无
  */
static void APP_GpioInit()
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  __HAL_RCC_GPIOB_CLK_ENABLE();                          /* GPIOB时钟使能 */

  /* 初始化GPIOB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* 使能上拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     /* GPIO速度 */
  /* GPIO初始化 */
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);                
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

  /* 配置时钟源HSI */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                                       /* 开启HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                                       /* 不分频 */
  /* RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_4MHz; */                         /* 配置HSI输出时钟为4MHz */
  /* RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz; */                         /* 配置HSI输出时钟为8MHz */
  /* RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_16MHz; */                        /* 配置HSI输出时钟为16MHz */
  /* RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_22p12MHz; */                     /* 配置HSI输出时钟为22.12MHz */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_24MHz;                              /* 配置HSI输出时钟为24MHz */

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)                                           /* 初始化RCC振荡器 */
  {
    APP_ErrorHandler();
  }

  /* 初始化CPU,AHB,APB总线时钟 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;  /* RCC系统时钟类型 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                                          /* SYSCLK的源选择为HSI */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                              /* APH时钟不分频 */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                                               /* APB时钟不分频 */

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)                         /* 初始化RCC系统时钟(FLASH_LATENCY_0=24M以下;FLASH_LATENCY_1=48M) */
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
