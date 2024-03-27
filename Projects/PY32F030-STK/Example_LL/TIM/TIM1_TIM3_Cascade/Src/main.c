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
static void APP_ConfigTIM1Slave(void);
static void APP_ConfigTIM3Master(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Enable TIM1 and TIM3 clocks */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

  /* Configure system clock */
  APP_SystemClockConfig();
  
  /* Initialize LED, USART */
  BSP_LED_Init(LED3);
  BSP_USART_Config();
  
  /* Enable TIM1 */
  APP_ConfigTIM1Slave();
  
  /* Enable TIM3 */
  APP_ConfigTIM3Master();
  
  /*  Infinite loop  */
  while (1)
  {
    printf("TIM1Count:%u\r\n",(unsigned int)LL_TIM_GetCounter(TIM1));
    LL_mDelay(1000);
  }
}

/**
  * @brief  Configure TIM3 as Master
  * @param  None
  * @retval None
  */
static void APP_ConfigTIM3Master(void)
{
  /* Prescaler value: 8000 */
  LL_TIM_SetPrescaler(TIM3,8000-1);
  
  /* Counting mode: Up counting */
  LL_TIM_SetCounterMode(TIM3,LL_TIM_COUNTERMODE_UP);
  
  /* Auto-reload value : 1000-1 */
  LL_TIM_SetAutoReload(TIM3,1000-1);
  
  /* No clock division */
  LL_TIM_SetClockDivision(TIM3,LL_TIM_CLOCKDIVISION_DIV1);
  
  /* Set trigger output as UPDATE event */
  LL_TIM_SetTriggerOutput(TIM3,LL_TIM_TRGO_UPDATE);
  
  /* Enable TIM3 counter */
  LL_TIM_EnableCounter(TIM3);
}

/**
  * @brief  Configure TIM1 as Slave
  * @param  None
  * @retval None
  */
static void APP_ConfigTIM1Slave(void)
{
  /* Counting mode: Up counting */
  LL_TIM_SetCounterMode(TIM1,LL_TIM_COUNTERMODE_UP);
  
  /* Autoreload value: 10 */
  LL_TIM_SetAutoReload(TIM1,10);
  
  /* Set trigger input as TIM3 */
  LL_TIM_SetTriggerInput(TIM1,LL_TIM_TS_ITR2);
  
  /* Set external clock mode 1 */
  LL_TIM_SetClockSource(TIM1,LL_TIM_CLOCKSOURCE_EXT_MODE1);
  
  /* Enable TIM1 counter */
  LL_TIM_EnableCounter(TIM1);
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
