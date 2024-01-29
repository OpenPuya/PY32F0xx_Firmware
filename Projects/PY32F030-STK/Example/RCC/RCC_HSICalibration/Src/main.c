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
#include "hsi.h"

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
TIM_IC_InitTypeDef     sICConfig;

/* Private function prototypes -----------------------------------------------*/
void APP_ErrorHandler(void);
void HSI_CALIBRATION(uint32_t HSICLKSource_SET);

uint32_t  StartCalibration = 0;

uint32_t  __IO Capture = 0;
uint32_t  __IO CaptureState = 0;

/* HSI Rough VALUE */
extern uint32_t HSI_Rough_Value ;
extern uint32_t HSI_Fine_Value ;

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  HAL_RCC_MCOConfig(0, RCC_MCO1SOURCE_HSI, RCC_MCODIV_8);

  HAL_Init();
  HSI_CALIBRATION(RCC_HSICALIBRATION_24MHz);

  while (1);
}

/**
  * @brief   TIM捕获中断执行函数
  * @param   无
  * @retval  无
  */
void HSI_CALIBRATION(uint32_t HSICLKSource_SET)
{
  uint32_t HSI_Calibration_value = 0;

  /* Enable Calibration */
  StartCalibration = 1;

  /* Get frequency values before calibration */
  HSI_MeasurementInit(HSICLKSource_SET);

  HSI_Rough_Value = Hsi_Rough_Trimming();       /* 高4位校准值 */
  HSI_Fine_Value = Hsi_Fine_Trimming();         /* 低4位校准值 */

  HSI_Calibration_value = ((HSI_Rough_Value << 9) & 0x1E00) | (HSI_Fine_Value & 0x1FF);
  MODIFY_REG(RCC->ICSCR, RCC_ICSCR_HSI_TRIM, (HSI_Calibration_value) << RCC_ICSCR_HSI_TRIM_Pos);
}

/**
  * @brief   TIM捕获中断执行函数
  * @param   无
  * @retval  无
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

  static uint32_t IC1ReadValue1 = 0, IC1ReadValue2 = 0;

  if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_y)                         /* 通道选择判断 */
  {
    /* 首次捕获执行 */
    if (CaptureState == CAPTURE_START)
    {
      IC1ReadValue1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_y);     /* 保存捕获值 */
      CaptureState = CAPTURE_ONGOING;                                     /* 切换捕获状态 */
    }
    /* 非首次捕获执行 */
    else if (CaptureState == CAPTURE_ONGOING)
    {
      IC1ReadValue2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_y);

      if (IC1ReadValue2 > IC1ReadValue1)                                  /* 本次捕获值>首次捕获值执行 */
      {
        Capture = (IC1ReadValue2 - IC1ReadValue1);
      }
      else if (IC1ReadValue2 < IC1ReadValue1)                             /* 本次捕获值<首次捕获值执行 */
      {
        Capture = ((0xFFFF - IC1ReadValue1) + IC1ReadValue2);
      }
      else
      {
        APP_ErrorHandler();
      }
 
      CaptureState = CAPTURE_COMPLETED;                                    /* 切换状态，捕获完成 */
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
  BSP_LED_Toggle(LED_GREEN);    /* GPIO翻转 */
}

/**
  * @brief   配置系统时钟
  * @param   HSICLKSource_SET：选择HSI时钟频率
  *            @arg @ref RCC_HSICALIBRATION_8MHz：8M时钟
  *            @arg @ref RCC_HSICALIBRATION_16MHz：16M时钟
  *            @arg @ref RCC_HSICALIBRATION_22p12MHz：22.12M时钟
  *            @arg @ref RCC_HSICALIBRATION_24MHz：24M时钟
  * @retval  无
  */
void SystemClock_Config(uint32_t HSICLKSource_SET)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* 配置HSI时钟 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                      /* 使能HSI */
  RCC_OscInitStruct.HSIDiv =    RCC_HSI_DIV1;                                   /* HSI预分频 */
  RCC_OscInitStruct.HSICalibrationValue = HSICLKSource_SET;                     /* 设置HSI输出时钟库会设置校准值 */

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)                          /* 配置时钟 */
  {
    APP_ErrorHandler();
  }

  /* 初始化AHB,APB总线时钟 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                         /* 配置AHB时钟源 */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                             /* 设置AHB预分频 */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                              /* 设置APB1预分频 */

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)        /* 配置总线 */
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief   配置GPIO，GPIO作为TIM1捕获输入模式
  * @param   无
  * @retval  无
  */
void GPIO_ConfigForCalibration(void)
{
  GPIO_InitTypeDef gpio_init;

  /* GPIOA clock enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  gpio_init.Pin = GPIO_PIN_4;                       /* 配置PIN */
  gpio_init.Mode = GPIO_MODE_AF_PP;                 /* 配置为复用功能 */
  gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;           /* 配置GPIO速度 */
  gpio_init.Pull  = GPIO_NOPULL;                    /* 配合GPIO上下拉 */
  gpio_init.Alternate = GPIO_AF4_TIMx;              /* 选择复用功能 */
  HAL_GPIO_Init(GPIOA, &gpio_init);                 /* 初始化GPIOA4 */
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
