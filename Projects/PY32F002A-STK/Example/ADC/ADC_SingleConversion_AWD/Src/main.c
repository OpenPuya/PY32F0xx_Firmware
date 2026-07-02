/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
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
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;
ADC_ChannelConfTypeDef sConfig;
ADC_AnalogWDGConfTypeDef      ADCAnalogWDGConfig;
uint32_t adc_value[2];
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void APP_ADCConfig(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  uint8_t i;
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();

  /* Configure ADC*/
  APP_ADCConfig();

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize UART */
  BSP_USART_Config();

  printf("print test");
  /* infinite loop */
  while (1)
  {
    HAL_ADC_Start(&hadc);                           /* Start ADC*/
    for (i = 0; i < 2; i++)
    {
      HAL_ADC_PollForConversion(&hadc, 10000);      /* Waiting for ADC conversion */
      adc_value[i] = HAL_ADC_GetValue(&hadc);       /* Get AD value  */
      printf("adc[%u]:%u\r\n", i, (unsigned int)adc_value[i]);
    }
  }
}

/**
  * @brief  ADC configuration function
  * @param  None
  * @retval None
  */
void APP_ADCConfig(void)
{
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
  __HAL_RCC_ADC_CLK_ENABLE();                                                /* Enable ADC clock */

  hadc.Instance = ADC1;
  if (HAL_ADCEx_Calibration_Start(&hadc) != HAL_OK)                          /* ADC calibration */
  {
    APP_ErrorHandler();
  }

  hadc.Instance                   = ADC1;                                    /* ADC*/
  hadc.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;                /* Setting the ADC clock source*/
  hadc.Init.Resolution            = ADC_RESOLUTION_12B;                      /* 12-bit resolution for converted data*/
  hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* Right-alignment for converted data */
  hadc.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;              /* Scan sequence direction: forward*/
  hadc.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;                     /* Single sampling*/
  hadc.Init.LowPowerAutoWait      = ENABLE;                                  /* Enable wait for conversion mode */
  hadc.Init.ContinuousConvMode    = DISABLE;                                 /* Single conversion mode */
  hadc.Init.DiscontinuousConvMode = DISABLE;                                 /* Disable discontinuous mode */
  hadc.Init.ExternalTrigConv      = ADC_SOFTWARE_START;                      /* Software triggering */
  hadc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;           /* No external trigger edge */
  hadc.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* When an overload occurs, overwrite the previous value*/
  hadc.Init.SamplingTimeCommon    = ADC_SAMPLETIME_239CYCLES_5;              /* Set sampling time */
  if (HAL_ADC_Init(&hadc) != HAL_OK)                                         /* ADC initialization*/
  {
    APP_ErrorHandler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*Set whether to sample */
  sConfig.Channel      = ADC_CHANNEL_0;                                      /*  Setting the sampling channel */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  Configuring ADC Channels */
  {
    APP_ErrorHandler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*Set whether to sample */
  sConfig.Channel      = ADC_CHANNEL_1;                                      /*  Setting the sampling channel */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  Configuring ADC Channels */
  {
    APP_ErrorHandler();
  }
  /* ADC Analogue Watchdog Initialisation */
  ADCAnalogWDGConfig.WatchdogMode = ADC_ANALOGWATCHDOG_ALL_REG;              /* All channels */
  ADCAnalogWDGConfig.HighThreshold = 0X1FF;                                  /* Setting the high threshold */
  ADCAnalogWDGConfig.LowThreshold = 0;                                       /* Setting the low threshold */
  ADCAnalogWDGConfig.ITMode = ENABLE;                                        /* Enable Interrupt  */

  if (HAL_ADC_AnalogWDGConfig(&hadc, &ADCAnalogWDGConfig) != HAL_OK)         /* ADC analogue watchdog configuration */
  {
    APP_ErrorHandler();
  }
  HAL_NVIC_SetPriority(ADC_COMP_IRQn, 0, 0);                                      /* Setting the ADC interrupt priority */
  HAL_NVIC_EnableIRQ(ADC_COMP_IRQn);                                              /* Setting ADC kernel interruptsv */
}

/**
  * @brief  Analog watchdog interrupt callback function
  * @param  AdcHandle: ADC handle
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
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
