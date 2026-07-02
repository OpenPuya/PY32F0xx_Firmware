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
#define  PULSE1_VALUE       (uint32_t)(400)      /* Capture Compare 1 Value  */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef              sPWMConfig;
TIM_BreakDeadTimeConfigTypeDef sBreakConfig;

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

  TimHandle.Instance = TIM1;                                                      /* Select TIM1 */
  TimHandle.Init.Period            = 800 - 1;                                     /* Auto-reload value */
  TimHandle.Init.Prescaler         = 1000 - 1;                                    /* Prescaler */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                      /* No clock division */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                          /* Up counting */
  TimHandle.Init.RepetitionCounter = 1 - 1;                                       /* No repetition counting */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;              /* Auto-reload register not buffered */
  if (HAL_TIM_PWM_Init(&TimHandle) != HAL_OK)                                     /* PWM initialization */
  {
    APP_ErrorHandler();
  }

  sPWMConfig.OCMode       = TIM_OCMODE_PWM1;                                      /* Configure as PWM1 */
  sPWMConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;                                  /* High level is active */
  sPWMConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                 /* High level is active */
  sPWMConfig.OCIdleState  = TIM_OCIDLESTATE_SET;                                  /* Output idle state 1 (OC1 output) */
  sPWMConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;                               /* Output idle state 1 (OC1N output) */
  sPWMConfig.OCFastMode   = TIM_OCFAST_DISABLE;                                   /* Disable fast mode */

  sPWMConfig.Pulse = PULSE1_VALUE;                                                /* Channel 1 duty cycle */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sPWMConfig, TIM_CHANNEL_1) != HAL_OK)/* Channel 1 configuration */
  {
    APP_ErrorHandler();
  }
  
  /* Brake and deadtime configuration */
  sBreakConfig.BreakState       = TIM_BREAK_ENABLE;                               /* Enable brake function */
  sBreakConfig.DeadTime         = 160;                                            /* Set deadtime */
  sBreakConfig.OffStateRunMode  = TIM_OSSR_ENABLE;                                /* Off-state selection in run mode OSSR=1 */
  sBreakConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;                                /* Off-state selection in IDLE mode OSSI=1 */
  sBreakConfig.LockLevel        = TIM_LOCKLEVEL_OFF;                              /* Lock level off */
  sBreakConfig.BreakPolarity    = TIM_BREAKPOLARITY_LOW;                          /* Brake input is active low */
  sBreakConfig.AutomaticOutput  = TIM_AUTOMATICOUTPUT_ENABLE;                     /* Enable automatic output */

  if (HAL_TIMEx_ConfigBreakDeadTime(&TimHandle, &sBreakConfig) != HAL_OK)         /* Configure brake and deadtime */
  {
    APP_ErrorHandler();
  }
  /* Output PWM on Channel 1 */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  /* Output PWM on Channel 1N */
  if (HAL_TIMEx_PWMN_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  while (1)
  {
  }
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
