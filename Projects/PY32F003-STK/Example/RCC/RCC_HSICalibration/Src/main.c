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
#include "hsi.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
uint32_t             StartCalibration = 0;
uint32_t __IO        Capture = 0;
uint32_t __IO        CaptureState = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_HSI_Calibration(void);
static void APP_SystemClockConfig(uint32_t HSICLKSource_set);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  HAL_RCC_MCOConfig(RCC_MCO2, RCC_MCO1SOURCE_HSI, RCC_MCODIV_8);

  HAL_Init();
  /* Initialize LED */  
  BSP_LED_Init(LED_GREEN);
  
  /* Initialize button */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
  
  /* Wait for button press */
  while (BSP_PB_GetState(BUTTON_USER))
  {
  }
  
  /* Turn on the LED */
  BSP_LED_On(LED_GREEN);
  
  /* 配置系统时钟为 HSI 24MHz. */
  APP_SystemClockConfig(RCC_HSICALIBRATION_24MHz);
  
  /* Calibrate the HSI */
  APP_HSI_Calibration();
  
  while (1)
  {
    HAL_Delay(100);
    /* Toggle LED */
    BSP_LED_Toggle(LED_GREEN);
  }
}

/**
  * @brief   TIM捕获中断执行函数
  * @param   无
  * @retval  无
  */
static void APP_HSI_Calibration(void)
{
  /* Enable Calibration */
  StartCalibration = 1;

  /* Initialize the GPIO and TIMx before calibration */
  HSI_MeasurementInit();

  /* Calculate the optimal calibration value of the HSI by dichotomisation and calibrate the HSI */
  HSI_Trimming();
}

/**
  * @brief   TIM捕获中断执行函数
  * @param   无
  * @retval  无
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

  static uint32_t IC1ReadValue1 = 0, IC1ReadValue2 = 0;

  if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_y)                        /* 通道选择判断 */
  {                                                                     
    /* 首次捕获执行 */                                                  
    if (CaptureState == CAPTURE_START)                                  
    {                                                                   
      IC1ReadValue1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_y);    /* 保存捕获值 */
      CaptureState = CAPTURE_ONGOING;                                    /* 切换捕获状态 */
    }                                                                   
    /* 非首次捕获执行 */                                                
    else if (CaptureState == CAPTURE_ONGOING)                           
    {                                                                   
      IC1ReadValue2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_y);   
                                                                        
      if (IC1ReadValue2 > IC1ReadValue1)                                 /* 本次捕获值>首次捕获值执行 */
      {                                                                 
        Capture = (IC1ReadValue2 - IC1ReadValue1);                      
      }                                                                 
      else if (IC1ReadValue2 < IC1ReadValue1)                            /* 本次捕获值<首次捕获值执行 */
      {
        Capture = ((0xFFFF - IC1ReadValue1) + IC1ReadValue2);
      }
      else
      {
        APP_ErrorHandler();
      }
      CaptureState = CAPTURE_COMPLETED;                                   /* 切换状态，捕获完成 */
    }
  }
}

/**
  * @brief   TIM周期中断执行函数
  * @param   无
  * @retval  无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  BSP_LED_Toggle(LED_GREEN);     /* GPIO翻转 */
}

/**
  * @brief   配置系统时钟
  * @param   HSICLKSource_SET：选择HSI时钟频率
  *            @arg @ref RCC_HSICALIBRATION_4MHz：4M时钟
  *            @arg @ref RCC_HSICALIBRATION_8MHz：8M时钟
  *            @arg @ref RCC_HSICALIBRATION_16MHz：16M时钟
  *            @arg @ref RCC_HSICALIBRATION_22p12MHz：22.12M时钟
  *            @arg @ref RCC_HSICALIBRATION_24MHz：24M时钟
  * @retval  无
  */
static void APP_SystemClockConfig(uint32_t HSICLKSource_SET)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /*配置HSI时钟*/
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                     /* 使能HSI */
  RCC_OscInitStruct.HSIDiv =    RCC_HSI_DIV1;                                  /* HSI预分频 */
  RCC_OscInitStruct.HSICalibrationValue = HSICLKSource_SET;                    /* 设置HSI输出时钟库会设置校准值 */
                                                                               
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)                         /* 配置时钟 */
  {
    APP_ErrorHandler();
  }

  /*初始化AHB,APB总线时钟*/
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                        /* 配置AHB时钟源 */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                            /* 设置AHB预分频 */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                             /* 设置APB1预分频 */
                                                                                
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)       /* 配置总线 */
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief   配置GPIO，GPIO作为TIM1捕获输入模式
  * @param   无
  * @retval  无
  */
void APP_GPIO_ConfigForCalibration(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIOA clock enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_4;                       /* Configure PIN */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                 /* Configure as alternate function */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;           /* Configure GPIO speed */
  GPIO_InitStruct.Pull  = GPIO_NOPULL;                    /* No Pull-up or Pull-down activation */
  GPIO_InitStruct.Alternate = GPIO_AF4_TIMx;              /* Select alternate function */
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                 /* Initialize GPIOA4 */
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
