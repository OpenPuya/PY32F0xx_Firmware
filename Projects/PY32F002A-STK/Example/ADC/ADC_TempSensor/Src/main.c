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
/* Please Check the HighTemperature and NormalTemperaute value */
#define HAL_ADC_TSCAL1                  (*(uint32_t *)(0x1fff0f14))  /*!< Temperature Scale1 */
#define HAL_ADC_TSCAL2                  (*(uint32_t *)(0x1fff0f18))  /*!< Temperature Scale2 */
#define Vcc_Power     3.3l                                            /* VCC power supply voltage, modify according to actual situation  */
#define TScal1        (float)((HAL_ADC_TSCAL1) * 3.3 / Vcc_Power)     /* Voltage corresponding to calibration value */
#define TScal2        (float)((HAL_ADC_TSCAL2) * 3.3 / Vcc_Power)     /* Voltage corresponding to calibration value  */
#define TStem1        30l                                             /* 30 ℃ */

/* #define HighTemp_85 */
#define HighTemp_105

#define TStem2_85        85   
#define TStem2_105       105  
#define Temp_k_85        ((float)(TStem2_85-TStem1)/(float)(TScal2-TScal1))
#define Temp_k_105       ((float)(TStem2_105-TStem1)/(float)(TScal2-TScal1))

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef        AdcHandle;
uint16_t                 aADCxConvertedData;
__IO uint16_t            hADCxConvertedData_Temperature_DegreeCelsius = 0;
TIM_HandleTypeDef        TimHandle;
TIM_MasterConfigTypeDef  sMasterConfig;

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_AdcConfig(void);

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
  
  /* Initialize UART */
  BSP_USART_Config();                                                  
  
  /* Configure ADC */
  APP_AdcConfig();
  
  /* ADC Calibrate */ 
  if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
    
  /* ADC Start */
  HAL_ADC_Start(&AdcHandle);

  while(1)
  {
   /* Poll For ADC Conversion */
    if(HAL_ADC_PollForConversion(&AdcHandle, 2000) == HAL_OK)
    {
      /* Get ADC Value */
      aADCxConvertedData = HAL_ADC_GetValue(&AdcHandle); 
       
/* Please Check the High Temperature Value accord the datasheet */
#if defined(HighTemp_85)                              
      hADCxConvertedData_Temperature_DegreeCelsius =(int16_t)(Temp_k_85 * aADCxConvertedData - Temp_k_85 * TScal1 + TStem1);
#else
      hADCxConvertedData_Temperature_DegreeCelsius =(int16_t)(Temp_k_105 * aADCxConvertedData - Temp_k_105 * TScal1 + TStem1);
#endif

      printf("Temperature: %d\r\n",(int)hADCxConvertedData_Temperature_DegreeCelsius);

    }
    HAL_Delay(1000);
  }   
}

/**
  * @brief  ADC configuration function
  * @param  None
  * @retval None
  */
static void APP_AdcConfig(void)
{
  ADC_ChannelConfTypeDef   sConfig={0};  
  
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();                                                  /* Reset ADC */
  __HAL_RCC_ADC_CLK_ENABLE();                                                     /* Enable ADC clock */

  AdcHandle.Instance = ADC1;

  /* ADC calibration */
  if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)                          
  {
    APP_ErrorHandler();
  }
                                                 
  AdcHandle.Instance                   = ADC1;                                    /* ADC1 */
  AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;                /* Set ADC clock */
  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;                      /* 12-bit resolution for converted data */
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* Right-alignment for converted data */
  AdcHandle.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;              /* Scan sequence direction: forward */
  AdcHandle.Init.EOCSelection          = ADC_EOC_SEQ_CONV;                        /* Conversion completion flag */
  AdcHandle.Init.LowPowerAutoWait      = ENABLE;                                  /* Enable wait for conversion mode */
  AdcHandle.Init.ContinuousConvMode    = DISABLE;                                 /* Single conversion mode */
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;                                 /* Disable discontinuous mode */
  AdcHandle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;                      /* Software triggering */
  AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;           /* No external trigger edge */
  AdcHandle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* When an overload occurs, overwrite the previous value */
  AdcHandle.Init.SamplingTimeCommon    = ADC_SAMPLETIME_239CYCLES_5;              /* Channel sampling time is 239.5 ADC clock cycles */
  /* ADC initialization */
  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)                                         
  {
    APP_ErrorHandler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                                 /* Set the rank for the ADC channel order */
  sConfig.Channel      = ADC_CHANNEL_TEMPSENSOR;                                  /* ADC channel selection */
  /* Configure ADC channels */
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)                      
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
