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
RTC_HandleTypeDef RtcHandle;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
   /* System clock configuration */
  APP_SystemClockConfig();
  
  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize button */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);
  
  /* RTC initialization */
  RtcHandle.Instance = RTC;                         /* Select RTC */
  RtcHandle.Init.AsynchPrediv = RTC_AUTO_1_SECOND;  /* RTC asynchronous prescaler calculated automatically for one second time base */
  if (HAL_RTC_Init(&RtcHandle) != HAL_OK)
  {
  }
  
  /* Turn on the LED */
  BSP_LED_On(LED_GREEN);
  
  /* Wait for the user button to be pressed to start the main program */
  while (BSP_PB_GetState(BUTTON_KEY) == 1)
  {
  }
  
  /* Turn off the LED */
  BSP_LED_Off(LED_GREEN);
  
  /* Suspend the SysTick interrupt to prevent interrupt waking up the system */
  HAL_SuspendTick();
  
  /* Enter STOP mode */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  
  /* Resume the SysTick interrupt */
  HAL_ResumeTick();
  
  while (1)
  {
    BSP_LED_Toggle(LED_GREEN);
    HAL_Delay(500);
  }
}

/**
  * @brief  System clock configuration function
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};

  /* RCC Oscillator initialization */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI;
  oscinitstruct.HSIState        = RCC_HSI_ON;                                               /* Enable HSI */
  oscinitstruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz;                              /* Configure HSI output clock as 8MHz */
  oscinitstruct.HSEState        = RCC_HSE_OFF;                                              /* Disable HSE */
  oscinitstruct.LSEState        = RCC_LSE_OFF;                                              /* Disable LSI */
  oscinitstruct.LSIState        = RCC_LSI_ON;                                               /* Disable LSE */
  oscinitstruct.PLL.PLLState    = RCC_PLL_NONE;                                             /* Keep PLL configuration unchanged */
  if (HAL_RCC_OscConfig(&oscinitstruct) != HAL_OK)
  {
    while (1);
  }

  /*  Initialize CPU, AHB, APB bus clocks */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1); /* RCC system clock types */
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                                           /* SYSCLK source selection as HSI */
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                               /* AHB clock not divided */
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV1;                                                /* APB clock not divided */
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_1) != HAL_OK)
  {
    while (1);
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
