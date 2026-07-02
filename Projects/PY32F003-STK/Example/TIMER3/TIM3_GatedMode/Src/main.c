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
TIM_HandleTypeDef    TimHandle;
TIM_SlaveConfigTypeDef   sSlaveConfig;
TIM_MasterConfigTypeDef sMasterConfig;
TIM_IC_InitTypeDef sConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief   Main program.
  * @retval  int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  TimHandle.Instance = TIM3;                                           /* Select TIM3 */
  TimHandle.Init.Period            = 8000 - 1;                         /* Auto-reload value */
  TimHandle.Init.Prescaler         = 1 - 1;                            /* No prescaler */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* No clock division */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* Up counting */
  TimHandle.Init.RepetitionCounter = 1 - 1;                            /* No repetition counting */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* Auto-reload register not buffered */
  if (HAL_TIM_IC_Init(&TimHandle) != HAL_OK)                           /* TIM3 input capture initialization */
  {
    APP_ErrorHandler();
  }
  
  /* TIM3_CH1 input configuration */
  sConfig.ICPrescaler = TIM_ICPSC_DIV1;                                /* No prescaler */
  sConfig.ICFilter = 0;                                                /* No filter */
  sConfig.ICPolarity = TIM_ICPOLARITY_FALLING;                         /* Capture on falling edge */
  sConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;                      /* Configure CC1 channel as input*/
  /* TIM3_CH1 capture configuration */
  if (HAL_TIM_IC_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  sSlaveConfig.SlaveMode        = TIM_SLAVEMODE_GATED;                 /* Slave mode selected as gated mode */
  sSlaveConfig.InputTrigger     = TIM_TS_TI1FP1;                       /* Trigger selection for TIM3 is TIM1 */
  sSlaveConfig.TriggerPolarity  = TIM_TRIGGERPOLARITY_NONINVERTED;     /* External trigger polarity is non-inverted */
  sSlaveConfig.TriggerPrescaler = TIM_TRIGGERPRESCALER_DIV1;           /* External trigger is not prescaled */
  sSlaveConfig.TriggerFilter    = 0;                                   /* No filter */
  /* Configure TIM3 as slave mode, enable interrupts */
  if (HAL_TIM_SlaveConfigSynchro_IT(&TimHandle, &sSlaveConfig) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  if (HAL_TIM_IC_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)          /* Start counting and enable interrupt generation for TIM3 */
  {
    APP_ErrorHandler();
  }

  while (1)
  {
  }

}

/**
  * @brief   Trigger interrupt callback function
  * @param   htim：TIM handle
  * @retval  None
  */
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim)
{
  BSP_LED_Toggle(LED_GREEN);

}

/**
  * @brief   This function is executed in case of error occurrence.
  * @param   None
  * @retval  None
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
