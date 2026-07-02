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
ADC_HandleTypeDef AdcHandle;
ADC_AnalogWDGConfTypeDef      ADCAnalogWDGConfig;
uint32_t adc_value[3];

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_AdcInit(void);

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

  /* Initialize system clock */
  APP_SystemClockConfig();                          
  
  /* Initialize ADC */
  APP_AdcInit();    

  /* Initialize UART */
  DEBUG_USART_Config();                              

  while (1)
  {
    /* Enable ADC */
    HAL_ADC_Start(&AdcHandle);                       
    for (uint8_t i = 0; i < 2; i++)
    {
      /* Waiting for ADC conversion */
      HAL_ADC_PollForConversion(&AdcHandle, 10000); 
      /* Get ADC value */
      adc_value[i] = HAL_ADC_GetValue(&AdcHandle);   
      printf("adc[%u]:%u\r\n", i, (unsigned int)adc_value[i]);
    }
  }
}

/**
  * @brief  Configure system clock
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Configure HSI, HSE, LSI clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                      /* Enable HSI */
#if defined(RCC_HSIDIV_SUPPORT)
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                      /* HSI prescaler */
#endif
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz;              /* Set HSI output clock as 8MHz, the library will set the calibration value */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                                     /* Disable HSE */
  RCC_OscInitStruct.HSEFreq =  RCC_HSE_16_32MHz;                                /* HSE frequency range 16M~32M */
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                                     /* Disable LSI */

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Initialize AHB, and APB bus clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSISYS;                        /* SYSCLK source is HSISYS */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                            /* Setting the AHB prescaler */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                             /* Setting the APB1 prescaler */

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  ADC Initialisation
  * @param  None
  * @retval None
  */
static void APP_AdcInit(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
  __HAL_RCC_ADC_CLK_ENABLE();

  AdcHandle.Instance = ADC1;
  /* ADC calibration */
  if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)                  
  {
    APP_ErrorHandler();
  }

  AdcHandle.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;              /* Set ADC clock */
  AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;                         /* 12-bit resolution for converted data */
  AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;                         /* Right-alignment for converted data */
  AdcHandle.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;               /* Scan sequence direction: forward */
  AdcHandle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                      /* Single sampling */
  AdcHandle.Init.LowPowerAutoWait = ENABLE;                               /* Enable wait for conversion mode */
  AdcHandle.Init.ContinuousConvMode = DISABLE;                            /* Single conversion mode */
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;                         /* Disable discontinuous mode */
  AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                   /* Software triggering */
  AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;    /* No external trigger edge */
  AdcHandle.Init.DMAContinuousRequests = DISABLE;                         /* Disable DMA */
  AdcHandle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                      /* Overrun handling: overwrite previous value */
  AdcHandle.Init.SamplingTimeCommon=ADC_SAMPLETIME_239CYCLES_5;            /* Set sampling time */
  /* Initialize ADC */
  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)                                 
  {
    APP_ErrorHandler();
  }

  sConfig.Channel = ADC_CHANNEL_0;                                        /* ADC channel selection */
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;                                 /* Set the rank for the ADC channel order */
  /* Configure ADC channels */
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)              
  {
    APP_ErrorHandler();
  }

  sConfig.Channel = ADC_CHANNEL_1;                                        /* ADC channel selection */
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;                                 /* Set the rank for the ADC channel order */
  /* Configure ADC channels */
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)              
  {
    APP_ErrorHandler();
  }

  /* Initialize ADC analog watchdog */
  ADCAnalogWDGConfig.WatchdogMode = ADC_ANALOGWATCHDOG_ALL_REG;           /* All channels */
  /* ADCAnalogWDGConfig.Channel = ADC_CHANNEL_2; */                       /* Configuring the ADC Analogue Watchdog Channel */
  ADCAnalogWDGConfig.HighThreshold = 0X1FF;                               /* Set upper threshold */
  ADCAnalogWDGConfig.LowThreshold = 0;                                    /* Set lower threshold */
  ADCAnalogWDGConfig.ITMode = ENABLE;                                     /* Enable interrupt */
  /* ADC analog watchdog configuration */
  if (HAL_ADC_AnalogWDGConfig(&AdcHandle, &ADCAnalogWDGConfig) != HAL_OK) 
  {
    APP_ErrorHandler();
  }
  HAL_NVIC_SetPriority(ADC_COMP_IRQn, 0, 0);                              /* Set ADC interrupt priority */
  HAL_NVIC_EnableIRQ(ADC_COMP_IRQn);                                      /* Enable ADC interrupt */
}

/**
  * @brief  Analog watchdog interrupt callback function
  * @param  AdcHandle：ADC handle
  * @retval None
  */
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* AdcHandle)
{
  BSP_LED_On(LED_GREEN);
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
