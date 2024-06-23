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
/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigLPTIMOneShot(void);
static void APP_uDelay(uint32_t nus);
static void APP_LPTIMClockconf(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{  
  /* Configure system clock */
  APP_SystemClockConfig();

  /* Enable LPTIM and PWR clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPTIM1);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  
  /* Initialize LED and button */  
  BSP_LED_Init(LED3);
  BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
  
  /* Configure LPTIM clock source as LSI */
  APP_LPTIMClockconf();
  
  /* Configure and enable LPTIM */
  APP_ConfigLPTIMOneShot();
  
  /* Turn on LED */
  BSP_LED_On(LED3);
  
  /* Wait for button press */
  while(BSP_PB_GetState(BUTTON_USER) != 0)
  {}
  
  /* Turn off LED */
  BSP_LED_Off(LED3);
    
  while (1)
  {
    /* Enable low power run mode */
    LL_PWR_EnableLowPowerRunMode();
    /* Disable LPTIM */
    LL_LPTIM_Disable(LPTIM1);
    /* Enable LPTIM */
    LL_LPTIM_Enable(LPTIM1);
    
    /* Delay for 120us */
    APP_uDelay(120);

    /* Start LPTIM in one-shot mode */
    LL_LPTIM_StartCounter(LPTIM1,LL_LPTIM_OPERATING_MODE_ONESHOT);

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    LL_LPM_EnableDeepSleep();
    
    /* Request Wait For Interrupt */
    __WFI();
  }
}

/**
  * @brief  LPTIM clock configuration
  * @param  None
  * @retval None
  */
static void APP_LPTIMClockconf(void)
{
  /* Enable LSI */
  LL_RCC_LSI_Enable();
  
  /* Wait for LSI to be ready */
  while(LL_RCC_LSI_IsReady() == 0)
  {}
    
  /* Configure LSI as LPTIM clock source */
  LL_RCC_SetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE_LSI);
}

/**
  * @brief  Configure LPTIM in one-shot mode
  * @param  None
  * @retval None
  */
static void APP_ConfigLPTIMOneShot(void)
{
  /* Configure LPTIM */
  /* LPTIM prescaler: divide by 128 */
  LL_LPTIM_SetPrescaler(LPTIM1,LL_LPTIM_PRESCALER_DIV128);
  
  /* Update ARR at the end of LPTIM counting period */
  LL_LPTIM_SetUpdateMode(LPTIM1,LL_LPTIM_UPDATE_MODE_ENDOFPERIOD);
  
  /* Enable ARR interrupt */
  LL_LPTIM_EnableIT_ARRM(LPTIM1);
  
  /* Enable NVIC interrupt request */
  NVIC_EnableIRQ(LPTIM1_IRQn);
  NVIC_SetPriority(LPTIM1_IRQn,0);
  
  /* Enable LPTIM */
  LL_LPTIM_Enable(LPTIM1);
  
  /* Configure auto-reload value: 51 */
  LL_LPTIM_SetAutoReload(LPTIM1,51);
}

/**
  * @brief  LPTIM ARR interrupt callback function
  * @param  None
  * @retval None
  */
void APP_LPTIMCallback(void)
{
  /*Toggle LED*/
  BSP_LED_Toggle(LED3);
}

/**
  * @brief  Microsecond delay function
  * @param  nus ：delay value
  * @retval None
  */
static void APP_uDelay(uint32_t nus)
{
  __IO uint32_t Delay =1+ nus * (SystemCoreClock / 24U) / 1000000U;
  do
  {
    __NOP();
  }
  while(Delay--);
}

/**
  * @brief  System clock configuration function
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  /* Enable HSI */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* Set AHB prescaler */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Configure HSISYS as system clock source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* Set APB1 prescaler */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);
  
  /* Update system clock global variable SystemCoreClock (can also be updated by calling SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(8000000);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  /* Infinite loop */
  while(1)
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
