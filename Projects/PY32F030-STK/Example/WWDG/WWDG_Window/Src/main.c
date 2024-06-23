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
#define WINDOW_IN                                   /* Feed the watchdog within the window time */
/* #define WINDOW_UPPER */                          /* Feed the watchdog outside the upper limit of the window time */
/* #define WINDOW_LOWER */                          /* Feed the watchdog outside the lower limit of the window time  */

/* Private variables ---------------------------------------------------------*/
WWDG_HandleTypeDef   WwdgHandle;

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint32_t APP_TimeoutCalculation(uint32_t timevalue);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  uint32_t delay = 0;

  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();  
  
  /* Initialize button */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
  
  /* Initialize LED */
  BSP_LED_Init(LED_GREEN); 

  if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET)
  {
    /* Turn on LED */
    BSP_LED_On(LED_GREEN);

    /* Wait for 4s */
    HAL_Delay(4000);
    
    /* Turn off LED */
    BSP_LED_Off(LED_GREEN);

    /* Wait for 500ms */
    HAL_Delay(500);

    /* Clear reset flags */
    __HAL_RCC_CLEAR_RESET_FLAGS();
  }
  else
  {
    /* Turn off LED */
    BSP_LED_Off(LED_GREEN);
  }

  /* Initialize WWDG module */
  WwdgHandle.Instance = WWDG;                                                             /* Select WWDG */
  WwdgHandle.Init.Prescaler = WWDG_PRESCALER_8;                                           /* Select prescaler 8 */
  WwdgHandle.Init.Window    = 0x50;                                                       /* 7-bit window value 0x40~0x7f  */
  WwdgHandle.Init.Counter   = 0x7F;                                                       /* Counter value (7-bit) */
  WwdgHandle.Init.EWIMode   = WWDG_EWI_DISABLE;                                           /* Disable early wake-up interrupt */
  /* WWDG initialization */
  if (HAL_WWDG_Init(&WwdgHandle) != HAL_OK)                                               
  {
    APP_ErrorHandler();
  }

#if defined(WINDOW_IN)
  delay = APP_TimeoutCalculation((WwdgHandle.Init.Counter - WwdgHandle.Init.Window) + 1) + 1;   /* Within the window time */
#elif defined(WINDOW_UPPER)
  delay = APP_TimeoutCalculation((WwdgHandle.Init.Counter - WwdgHandle.Init.Window)-5 ) + 1;    /* Outside the upper limit of the window time */
#else 
  delay = APP_TimeoutCalculation((WwdgHandle.Init.Counter - 0x3f) +5) + 1;                      /* Outside the lower limit of the window time */
#endif

  /* Infinite loop */
  while (1)
  {
    /* Toggle LED */
    BSP_LED_Toggle(LED_GREEN);

    /* Insert the calculated delay */
    HAL_Delay(delay);

    /* Refresh the watchdog counter */
    if (HAL_WWDG_Refresh(&WwdgHandle) != HAL_OK)
    {
      APP_ErrorHandler();
    }
  }
}

/**
  * @brief  Timeout calculation function
  * @param  timevalue：Time value
  * @retval int
  */
static uint32_t APP_TimeoutCalculation(uint32_t timevalue)
{
  uint32_t timeoutvalue = 0;
  uint32_t pclk1 = 0;
  uint32_t wdgtb = 0;
  /* Get the value of PCLK1 */
  pclk1 = HAL_RCC_GetPCLK1Freq();
  /* Get the prescaler value */
  wdgtb = (1 << ((WwdgHandle.Init.Prescaler) >> 7)); /* 2^WDGTB[1:0] */
  /* Calculate the timeout value */
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
  BSP_LED_Off(LED_GREEN);

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
