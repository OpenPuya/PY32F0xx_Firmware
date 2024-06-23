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
#include "hsi.h"

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
uint32_t             StartCalibration = 0;
uint32_t __IO        Capture = 0;
uint32_t __IO        CaptureState = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_HSI_Calibration(void);
static void APP_SystemClockConfig(uint32_t HSICLKSource_set);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_8);

  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* Initialize LED */  
  BSP_LED_Init(LED_GREEN);
  
  /* Initialize button */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
  
  /* Wait for button press */
  while (BSP_PB_GetState(BUTTON_USER))
  {
  }
  
  /* Turn on the LED */
  BSP_LED_On(LED_GREEN);
  
  /* The system clock is configured as HSI 24MHz. */
  APP_SystemClockConfig(RCC_HSICALIBRATION_24MHz);
  
  /* Calibrate the HSI */
  APP_HSI_Calibration();
  
  while (1)
  {
    HAL_Delay(100);
    /* Toggle LED */
    BSP_LED_Toggle(LED_GREEN);
  }
}

/**
  * @brief   TIM capture interrupt execution function
  * @param   None
  * @retval  None
  */
static void APP_HSI_Calibration(void)
{
  /* Enable Calibration */
  StartCalibration = 1;

  /* Initialize the GPIO and TIMx before calibration */
  HSI_MeasurementInit();

  /* Calculate the optimal calibration value of the HSI by dichotomisation and calibrate the HSI */
  HSI_Trimming();
}

/**
  * @brief   Input Capture callback in non blocking mode
  * @param   htim: TIM IC handle
  * @retval  None
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

  static uint32_t IC1ReadValue1 = 0, IC1ReadValue2 = 0;

  if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_y)                         /* Channel selection check */
  {
    /* First capture execution */
    if (CaptureState == CAPTURE_START)
    {
      IC1ReadValue1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_y);     /* Save capture value */
      CaptureState = CAPTURE_ONGOING;                                     /* Switch capture state */
    }
    /* Subsequent captures execution */
    else if (CaptureState == CAPTURE_ONGOING)
    {
      IC1ReadValue2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_y);

      if (IC1ReadValue2 > IC1ReadValue1)                                  /* If current capture value > first capture value */
      {
        Capture = (IC1ReadValue2 - IC1ReadValue1);
      }
      else if (IC1ReadValue2 < IC1ReadValue1)                             /* If current capture value < first capture value */
      {
        Capture = ((0xFFFF - IC1ReadValue1) + IC1ReadValue2);
      }
      else
      {
        APP_ErrorHandler();
      }
 
      CaptureState = CAPTURE_COMPLETED;                                    /* Switch state, capture completed */
    }
  }
}

/**
  * @brief   Period elapsed callback in non blocking mode 
  * @param   htim: TIM handle
  * @retval  None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  BSP_LED_Toggle(LED_GREEN);    /* Toggle GPIO state */
}

/**
  * @brief   Configure system clock
  * @param   HSICLKSource_SET：HSI clock frequency selection
  *            @arg @ref RCC_HSICALIBRATION_4MHz：4Mclock
  *            @arg @ref RCC_HSICALIBRATION_8MHz：8Mclock
  *            @arg @ref RCC_HSICALIBRATION_16MHz：16Mclock
  *            @arg @ref RCC_HSICALIBRATION_22p12MHz：22.12Mclock
  *            @arg @ref RCC_HSICALIBRATION_24MHz：24Mclock
  * @retval  None
  */
static void APP_SystemClockConfig(uint32_t HSICLKSource_SET)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Configure HSI clock */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                      /* Enable HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                      /* HSI prescaler */
  RCC_OscInitStruct.HSICalibrationValue = HSICLKSource_SET;                     /* Set HSI output clock calibration value */
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_OFF;                                 /* Disable PLL */
  /*RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;*/                      /* Select HSI as PLL source */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)                          /* Configure clock */
  {
    APP_ErrorHandler();
  }

  /* Initialize AHB, APB bus clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                         /* Configure AHB clock source */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                             /* Set AHB prescaler */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                              /* Set APB1 prescaler */

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)        /* Configure bus clocks */
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief   Configure GPIO as TIM1 input capture mode
  * @param   None
  * @retval  None
  */
void APP_GPIO_ConfigForCalibration(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIOA clock enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_4;                       /* Configure PIN */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                 /* Configure as alternate function */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;           /* Configure GPIO speed */
  GPIO_InitStruct.Pull  = GPIO_NOPULL;                    /* No Pull-up or Pull-down activation */
  GPIO_InitStruct.Alternate = GPIO_AF4_TIMx;              /* Select alternate function */
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                 /* Initialize GPIOA4 */
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
