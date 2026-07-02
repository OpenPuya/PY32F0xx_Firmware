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
#include "py32f003xx_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle1, TimHandle3;
TIM_SlaveConfigTypeDef   sSlaveConfig;
TIM_MasterConfigTypeDef sMasterConfig;
TIM_OC_InitTypeDef sConfig;

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
  
  /* Initialize USART */
  BSP_USART_Config();
  
  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  TimHandle3.Instance               = TIM3;                             /* Select TIM3 */
  TimHandle3.Init.Period            = 8000 - 1;                         /* Auto-reload value */
  TimHandle3.Init.Prescaler         = 1 - 1;                            /* prescale */
  TimHandle3.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* Up counting */
  TimHandle3.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* No clock division */
  TimHandle3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* Auto-reload register not buffered */
  if (HAL_TIM_Base_Init(&TimHandle3) != HAL_OK)                         /* Initialize TIM3 */
  {
    APP_ErrorHandler();
  }

  TimHandle1.Instance               = TIM1;                             /* Select TIM1 */
  TimHandle1.Init.Period            = 80 - 1;                           /* Auto-reload value */
  TimHandle1.Init.Prescaler         = 1 - 1;                            /* prescale */
  TimHandle1.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* Up counting */
  TimHandle1.Init.ClockDivision     =  TIM_CLOCKDIVISION_DIV1;          /* No clock division */
  TimHandle1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* Auto-reload register not buffered */
  TimHandle1.Init.RepetitionCounter = 1 - 1;                            /* No repetition counting */
  if (HAL_TIM_Base_Init(&TimHandle1) != HAL_OK)                         /* Initialize TIM1 */
  {
    APP_ErrorHandler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;                 /* Master clock generates TRGO signal on update event */
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;         /* Master/slave mode disabled */
  /* Configure TIM1 as master mode */
  HAL_TIMEx_MasterConfigSynchronization(&TimHandle1, &sMasterConfig);  

  sSlaveConfig.SlaveMode        = TIM_SLAVEMODE_RESET;                 /* Slave mode selected as gated mode */
  sSlaveConfig.InputTrigger     = TIM_TS_ITR0;                         /* Trigger selection for TIM3 is TIM1 */
  sSlaveConfig.TriggerPolarity  = TIM_TRIGGERPOLARITY_NONINVERTED;     /* External trigger polarity is non-inverted */
  sSlaveConfig.TriggerPrescaler = TIM_TRIGGERPRESCALER_DIV1;           /* External trigger is not prescaled */
  sSlaveConfig.TriggerFilter    = 0;                                   /* No filter */
  /* Configure TIM3 as slave mode */
  if (HAL_TIM_SlaveConfigSynchro(&TimHandle3, &sSlaveConfig) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  if (HAL_TIM_Base_Start(&TimHandle1) != HAL_OK)                        /* Start counting for TIM1 */
  {
    APP_ErrorHandler();
  }
  if (HAL_TIM_Base_Start(&TimHandle3) != HAL_OK)                        /* Start TIM3 counting */
  {
    APP_ErrorHandler();
  }

  while (1)
  {
    printf("TIM3 CNT:%u\r\n", (unsigned int)__HAL_TIM_GET_COUNTER(&TimHandle3));
  }

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
