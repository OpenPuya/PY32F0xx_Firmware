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
RTC_HandleTypeDef RTCinit;
RTC_TimeTypeDef RTCtime;
RTC_AlarmTypeDef RTC_AlarmStruct;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_RtcInit(void);
static void APP_RtcSetAlarm(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* Enable LSI clock */
  APP_SystemClockConfig();
  
  /* Configure UART */
  DEBUG_USART_Config();
  
  /* RTC initialization */
  APP_RtcInit();
  
  /* Turn on LED */
  BSP_LED_On(LED_GREEN);
  
  /* Wait for button press */
  while (BSP_PB_GetState(BUTTON_USER) != 0)
  {
  }
  
  /* Get current RTC time in binary format */
  HAL_RTC_GetTime(&RTCinit,&RTCtime,RTC_FORMAT_BIN);
  
  /* Configure the time of the first alarm in binary format */
  RTC_AlarmStruct.AlarmTime = RTCtime;
  RTC_AlarmStruct.AlarmTime.Seconds += 1;
  HAL_RTC_SetAlarm_IT(&RTCinit, &RTC_AlarmStruct, RTC_FORMAT_BIN);
  
   /* Turn off LED */
  BSP_LED_Off(LED_GREEN);
  while (1)
  {
    /* Enter STOP mode */
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
    
    /* Set RTC alarm */
    APP_RtcSetAlarm();
  }
}

/**
  * @brief  RTC initialization function, sets RTC to January 1, 2022, Saturday, 00:00:00
  * @param  None
  * @retval None
  */
static void APP_RtcInit(void)
{
  RTC_TimeTypeDef Timeinit = {0};
  RCC_PeriphCLKInitTypeDef RTCLCKconfig = {0};
  
  /* Enable access to the backup domain (RTC settings are stored in the backup domain) */
  HAL_PWR_EnableBkUpAccess();
  
  /*Enable RTC clock*/
  __HAL_RCC_RTCAPB_CLK_ENABLE();                        /* Enable RTC module APB clock */
  __HAL_RCC_RTC_ENABLE();                               /* Enable RTC clock */
  
  /* RCC peripheral clock initialization */
  RTCLCKconfig.PeriphClockSelection = RCC_PERIPHCLK_RTC;/* RCC peripheral clock selection as RTC */
  RTCLCKconfig.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;/* RTC source selection as LSI */
  HAL_RCCEx_PeriphCLKConfig(&RTCLCKconfig);

  /* RTC initialization */
  RTCinit.Instance = RTC;                               /* Select RTC */
  RTCinit.Init.AsynchPrediv = RTC_AUTO_1_SECOND;        /* Automatic calculation of RTC's 1-second time base */
  RTCinit.Init.OutPut = RTC_OUTPUTSOURCE_NONE;          /* No output on the TAMPER pin */
  /*2022-1-1-00:00:00*/
  RTCinit.DateToUpdate.Year = 22;                       /* Year 22 */
  RTCinit.DateToUpdate.Month = RTC_MONTH_JANUARY;       /* January  */
  RTCinit.DateToUpdate.Date = 1;                        /* 1st day */
  RTCinit.DateToUpdate.WeekDay = RTC_WEEKDAY_SATURDAY;  /* Saturday  */
  Timeinit.Hours = 0x00;                                /* 0 hours */
  Timeinit.Minutes = 0x00;                              /* 0 minutes */
  Timeinit.Seconds = 0x00;                              /* 0 seconds */
  
  /* RTC deinitialization */
  HAL_RTC_DeInit(&RTCinit);
  
  /* RTC initialization */
  HAL_RTC_Init(&RTCinit);
  
  /* Set RTC current time in binary format */
  HAL_RTC_SetTime(&RTCinit, &Timeinit, RTC_FORMAT_BIN);
}

/**
  * @brief  Set RTC alarm
  * @param  None
  * @retval None
  */
static void APP_RtcSetAlarm(void)
{
  /* Get current alarm time in binary format */
  HAL_RTC_GetAlarm(&RTCinit, &RTC_AlarmStruct, RTC_FORMAT_BIN);
  
  /* Update alarm time in binary format */
  RTC_AlarmStruct.AlarmTime.Seconds += 1;
  HAL_RTC_SetAlarm_IT(&RTCinit, &RTC_AlarmStruct, RTC_FORMAT_BIN);
}

/**
  * @brief  RTC alarm event callback function, LED turns on when exiting low-power mode
  * @param  hrtc：RTC handle
  * @retval None
  */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Toggle LED */
  BSP_LED_Toggle(LED_GREEN);
  
  /* Print the current alarm time */
  printf("%02d:%02d:%02d\r\n", RTC_AlarmStruct.AlarmTime.Hours , RTC_AlarmStruct.AlarmTime.Minutes, RTC_AlarmStruct.AlarmTime.Seconds);
}

/**
  * @brief  System clock configuration function
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  
  /* Configure clock source HSE/HSI/LSE/LSI */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                                      /* Enable HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                                      /* No HSI division */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz;                              /* Configure HSI output clock as 8MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                                                     /* Disable HSE */
  /* RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz; */                                           /* HSE frequency range 16M~32M */
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;                                                      /* Enable LSI */
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;                                                     /* Disable LSE */
  /* RCC_OscInitStruct.LSEDriver = RCC_LSEDRIVE_MEDIUM; */                                      /* LSE default driving capability */
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_OFF;                                                 /* Disable PLL */
  /*RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;*/                                      /* Select HSI as PLL source */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
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
