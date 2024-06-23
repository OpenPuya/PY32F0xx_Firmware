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
#include "py32f030xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
#define WINDOW_IN                                   /* Feed the watchdog within the window time */
/* #define WINDOW_UPPER */                          /* Feed the watchdog outside the upper limit of the window time */
/* #define WINDOW_LOWER */                          /* Feed the watchdog outside the lower limit of the window time */

/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_WwdgConfig(void);
static uint32_t APP_TimeoutCalculation(uint32_t timevalue);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  uint32_t delay = 0;

  /* Enable PWR clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
 
  /* Initialize clock, configure system clock as HSI */
  APP_SystemClockConfig();

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  if (LL_RCC_IsActiveFlag_WWDGRST() != RESET)
  {
    /* Turn on the LED */
    BSP_LED_On(LED_GREEN);

    /* Wait for 4 seconds */
    LL_mDelay(4000);

    /* Turn off the LED */
    BSP_LED_Off(LED_GREEN);

    /* Wait for 500ms */
    LL_mDelay(500);

    /* Clear reset status flags */
    LL_RCC_ClearResetFlags();
  }
  else
  {
    /* Turn off the LED */
    BSP_LED_Off(LED_GREEN);
  }

  /* IWDG configuration */
  APP_WwdgConfig();

#if defined(WINDOW_IN)
  delay = APP_TimeoutCalculation((0x7F - 0x50) + 1) + 1;                      /* Feed the watchdog within the window time */
#elif defined(WINDOW_UPPER)
  delay = APP_TimeoutCalculation((0x7F - 0x50) - 5) + 1;                      /* Feed the watchdog outside the upper limit of the window time */
#else 
  delay = APP_TimeoutCalculation((0x7F - 0x3f) + 5) + 1;                      /* Feed the watchdog outside the lower limit of the window time */
#endif

  while (1)
  {
    BSP_LED_Toggle(LED_GREEN);

    /* Delay time */
    LL_mDelay(delay);

    /* Feed watchdog */
    LL_WWDG_SetCounter(WWDG, 0x7F);
  }
}

/**
  * @brief  System clock configuration function
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  /* Enable and initialize HSI */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* Set AHB prescaler */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Configure HSISYS as system clock and initialize it */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  /* Set APB1 prescaler and initialize it */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);
  /* Update system clock global variable SystemCoreClock (can also be updated by calling SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(8000000);
}

/**
  * @brief  WWDG configuration function
  * @param  None
  * @retval None
  */
static void APP_WwdgConfig(void)
{
  /* Enable WWDG clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_WWDG);

  /* Set counter value */
  LL_WWDG_SetCounter(WWDG, 0x7F);
  
  /* Set prescaler */
  LL_WWDG_SetPrescaler(WWDG, LL_WWDG_PRESCALER_8);
  
  /* Set window value */
  LL_WWDG_SetWindow(WWDG, 0x50);
  
  /* Enable WWDG */
  LL_WWDG_Enable(WWDG);
}

/**
  * @brief  Timeout calculation function
  * @param  timevalue：Time value
  * @retval int
  */
static uint32_t APP_TimeoutCalculation(uint32_t timevalue)
{
  uint32_t timeoutvalue = 0;
  LL_RCC_ClocksTypeDef RCC_Clocks = {0};
  uint32_t pclk1 = 0;
  uint32_t wdgtb = 0;

  /* Get HCLK frequency */
  LL_RCC_GetSystemClocksFreq(&RCC_Clocks);
  pclk1 = RCC_Clocks.PCLK1_Frequency;

  /* Get prescaler */
  wdgtb = (1 << ((LL_WWDG_PRESCALER_8) >> 7)); /* 2^WDGTB[1:0] */

  /* Calculate timeout value */
  timeoutvalue = ((4096 * wdgtb * timevalue) / (pclk1 / 1000));

  return timeoutvalue;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
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
