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
#include "py32f0xx_hal_flash.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
TIM_IC_InitTypeDef sICConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  TimHandle.Instance = TIM1;                                                     /* Select TIM1 */
  TimHandle.Init.Period            = 12800 - 1;                                  /* Auto-reload value */
  TimHandle.Init.Prescaler         = 1000 - 1;                                   /* Prescaler */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                     /* No clock division */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                         /* Up counting */
  TimHandle.Init.RepetitionCounter = 1 - 1;                                      /* No repetition counting */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;             /* Auto-reload register not buffered */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                                   /* Initialize TIM1 */
  {
    APP_ErrorHandler();
  }
  sICConfig.ICPolarity  = TIM_ICPOLARITY_RISING;                                 /* Rising edge capture */
  sICConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;                              /* Configure CC1 channel as input */
  sICConfig.ICPrescaler = TIM_ICPSC_DIV1;                                        /* No input prescaler */
  sICConfig.ICFilter    = 0;                                                     /* No filter on input */
  if (HAL_TIM_IC_ConfigChannel(&TimHandle, &sICConfig, TIM_CHANNEL_1) != HAL_OK) /* Configure input capture for channel 1 */
  {
    APP_ErrorHandler();
  }
  if (HAL_TIM_IC_Start_IT(&TimHandle, TIM_CHANNEL_1) != HAL_OK)                  /* Start input capture for channel 1 */
  {
    APP_ErrorHandler();
  }
  while (1)
  {
  }
}

/**
  * @brief  Input Capture callback in non blocking mode
  * @param  htim：TIM handle
  * @retval None
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  BSP_LED_Toggle(LED_GREEN);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  /* infinite loop */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line)  */
  /* infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
