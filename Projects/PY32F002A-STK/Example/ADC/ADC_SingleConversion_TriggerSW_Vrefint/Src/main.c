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
ADC_HandleTypeDef             hadc;
ADC_ChannelConfTypeDef        sConfig;
uint32_t                      adc_value;
uint16_t                      T_VCC;
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void APP_ADCConfig(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  APP_ADCConfig();

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize UART */
  BSP_USART_Config();

  /* infinite loop */
  while (1)
  {
    HAL_ADC_Start(&hadc);                             /* Start ADC */
    HAL_ADC_PollForConversion(&hadc, 1000000);        /* Wait for ADC conversion to complete */
    adc_value = HAL_ADC_GetValue(&hadc);              /* Get ADC value */
   
    T_VCC = (4095 * 1200) / adc_value;               
    printf("VCC : %d mV\r\n", T_VCC);
    HAL_Delay(500); 
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

 
  hadc.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;                /* Setting the ADC Clock*/
  hadc.Init.Resolution            = ADC_RESOLUTION_12B;                      /* 12-bit resolution for converted data*/
  hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* Right-alignment for converted data */
  hadc.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;              /* Scan sequence direction: forward*/
  hadc.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;                     /* Single sampling*/
  hadc.Init.LowPowerAutoWait      = ENABLE;                                  /* Enable wait for conversion mode */
  hadc.Init.ContinuousConvMode    = DISABLE;                                 /* Single conversion mode */
  hadc.Init.DiscontinuousConvMode = DISABLE;                                 /* Disable discontinuous mode */
  hadc.Init.ExternalTrigConv      = ADC_SOFTWARE_START;                      /* Software triggering */
  hadc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;           /* No external trigger edge */
  hadc.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* When an overload occurs, overwrite the previous value */
  hadc.Init.SamplingTimeCommon    = ADC_SAMPLETIME_239CYCLES_5;              /* Set sampling time */
  if (HAL_ADC_Init(&hadc) != HAL_OK)                                         /* ADC initialization*/
  {
    APP_ErrorHandler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                             /* Set whether to sample */
  sConfig.Channel      = ADC_CHANNEL_VREFINT;                                 /*  Setting the sampling channel */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                       /* Configuring ADC Channels */
  {
    APP_ErrorHandler();
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
