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
TIM_HandleTypeDef    TimHandle1,TimHandle3;
TIM_SlaveConfigTypeDef   sSlaveConfig;
TIM_MasterConfigTypeDef sMasterConfig;
TIM_OC_InitTypeDef sConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);

/**
  * @brief   Main program
  * @retval  int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* System clock configuration */
  APP_SystemClockConfig(); 
  
  /* Initialize USART */
  BSP_USART_Config();
  
  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);  
  
  TimHandle3.Instance               = TIM3;                             /* Select TIM3 */
  TimHandle3.Init.Period            = 8000 - 1;                         /* Auto-reload value */
  TimHandle3.Init.Prescaler         = 1000 - 1;                         /* prescale */
  TimHandle3.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* Up counting mode */
  TimHandle3.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* No clock division */
  TimHandle3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* Auto-reload register not buffered */
  /* TIM3 initialization */
  if (HAL_TIM_Base_Init(&TimHandle3) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  TimHandle1.Instance               = TIM1;                              /* Select TIM1 */
  TimHandle1.Init.Period            = 4000 - 1;                          /* Auto-reload value */
  TimHandle1.Init.Prescaler         = 1000 - 1;                          /* prescale */
  TimHandle1.Init.CounterMode       = TIM_COUNTERMODE_UP;                /* Up counting mode */
  TimHandle1.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;            /* No clock division */
  TimHandle1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;    /* Auto-reload register not buffered */
  TimHandle1.Init.RepetitionCounter = 1 - 1;                             /* No repetition counter */
  /* TIM1 initialization */
  if (HAL_TIM_Base_Init(&TimHandle1) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;                 /* Master clock generates TRGO signal on update event */
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;         /* Master/slave mode disabled */
  /* Configure TIM1 as master mode */
  HAL_TIMEx_MasterConfigSynchronization(&TimHandle1, &sMasterConfig);

  sSlaveConfig.SlaveMode        = TIM_SLAVEMODE_RESET;                 /* Slave mode selected as reset mode */
  sSlaveConfig.InputTrigger     = TIM_TS_ITR0;                         /* Trigger selection for TIM3 is TIM1 */
  sSlaveConfig.TriggerPolarity  = TIM_TRIGGERPOLARITY_NONINVERTED;     /* External trigger polarity not inverted */
  sSlaveConfig.TriggerPrescaler = TIM_TRIGGERPRESCALER_DIV1;           /* External trigger not divided */
  sSlaveConfig.TriggerFilter    = 0;                                   /* No filter */
  /* Configure TIM3 as slave mode */
  if (HAL_TIM_SlaveConfigSynchro(&TimHandle3, &sSlaveConfig) != HAL_OK)
  {
    APP_ErrorHandler();
  }
    
  /* Start counting for TIM1 */
  if (HAL_TIM_Base_Start(&TimHandle1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Start counting and enable interrupt generation for TIM3 */
  if (HAL_TIM_Base_Start(&TimHandle3) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Infinite loop */
  while (1)
  {
    printf("TIM3 CNT = %u\r\n",(unsigned int)__HAL_TIM_GET_COUNTER(&TimHandle3));
  }

}

/**
  * @brief   System clock configuration function
  * @param   None
  * @retval  None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI \
                                   | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;  /* Configure HSE, HSI, LSI, LSE */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                             /* Enable HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                             /* HSI not divided */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz;                     /* HSI calibration frequency: 8MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                                            /* Disable HSE */
  /* RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz; */                                  /* HSE frequency range: 16~32MHz */
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                                            /* Disable LSI */
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;                                            /* Disable LSE */
  /* RCC_OscInitStruct.LSEDriver = RCC_LSEDRIVE_MEDIUM; */                             /* Default LSE drive capability */
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_OFF;                                        /* Disable PLL */
  /* RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI; */                           /* Select HSI as PLL source */
  /* Configure oscillators */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;/* Configure SYSCLK, HCLK, PCLK */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                                        /* Set system clock source as HSI */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                            /* AHBNo clock division */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                                             /* APBNo clock division */
  /* Configure clock source */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief   This function is executed in case of error occurrence.
  * @param   None
  * @retval  None
  */
void APP_ErrorHandler(void)
{
  /* Infinite loop */
  while (1)
  {
  }
}
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
