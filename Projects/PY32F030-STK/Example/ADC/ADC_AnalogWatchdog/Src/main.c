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
ADC_HandleTypeDef             AdcHandle;
ADC_ChannelConfTypeDef        sConfig;
ADC_AnalogWDGConfTypeDef      ADCAnalogWDGConfig;
uint32_t adc_value[2];

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
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
    HAL_Delay(500);
  }
}

/**
  * @brief  ADC configuration function
  * @param  None
  * @retval None
  */
static void APP_AdcInit(void)
{
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();                                         /* Reset ADC */
  __HAL_RCC_ADC_CLK_ENABLE();                                            /* Enable ADC clock */

  AdcHandle.Instance = ADC1;
  
  /* ADC calibration */
  if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)                 
  {
    APP_ErrorHandler();
  }
 
  AdcHandle.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;              /* Set ADC clock */
  AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;                        /* 12-bit resolution for converted data */
  AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;                        /* Right-alignment for converted data */
  AdcHandle.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;              /* Scan sequence direction: forward  */
  AdcHandle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                     /* Single sampling */
  AdcHandle.Init.LowPowerAutoWait = ENABLE;                              /* Enable wait for conversion mode */
  AdcHandle.Init.ContinuousConvMode = DISABLE;                           /* Single conversion mode */
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;                        /* Disable discontinuous mode */
  AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                  /* Software triggering */
  AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;   /* No external trigger edge */
  AdcHandle.Init.DMAContinuousRequests = DISABLE;                        /* Disable DMA */
  AdcHandle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                     /* Overrun handling: overwrite previous value */
  AdcHandle.Init.SamplingTimeCommon=ADC_SAMPLETIME_13CYCLES_5;           /* Set sampling time */

  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)                                /* Initialize ADC */
  {
    APP_ErrorHandler();
  }

  sConfig.Channel = ADC_CHANNEL_0;                                       /* ADC channel selection */
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;                                /* Set the rank for the ADC channel order */
  /* Configure ADC channels */
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)             
  {
    APP_ErrorHandler();
  }

  sConfig.Channel = ADC_CHANNEL_1;                                       /* ADC channel selection */
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;                                /* Set the rank for the ADC channel order */
  /* Configure ADC channels */
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)             
  {
    APP_ErrorHandler();
  }

  /* Initialize ADC analog watchdog */
  ADCAnalogWDGConfig.WatchdogMode = ADC_ANALOGWATCHDOG_ALL_REG;            /* All channels */
  ADCAnalogWDGConfig.HighThreshold = 0X1FF;                                /* Set upper threshold */
  ADCAnalogWDGConfig.LowThreshold = 0;                                     /* Set lower threshold */
  ADCAnalogWDGConfig.ITMode = ENABLE;                                      /* Enable interrupt */
  /* ADC analog watchdog configuration */
  if (HAL_ADC_AnalogWDGConfig(&AdcHandle, &ADCAnalogWDGConfig) != HAL_OK)  
  {
    APP_ErrorHandler();
  }
  HAL_NVIC_SetPriority(ADC_COMP_IRQn, 0, 0);                               /*  Set ADC interrupt priority */
  HAL_NVIC_EnableIRQ(ADC_COMP_IRQn);                                       /*  Enable ADC interrupt */
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
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line)  */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
