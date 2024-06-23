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
LPTIM_HandleTypeDef       LPTIMConf = {0};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_RCCOscConfig(void);
static void APP_LPTIMInit(void);
static void APP_LPTIMStart(void);
static void APP_delay_us(uint32_t nus);

/**
  * @brief   Main program
  * @retval  int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* Clock configuration */
  APP_RCCOscConfig();
  
  /* Initialize LED */
  BSP_LED_Init(LED3);
  
  /* Initialize button */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /* LPTIM initialization */
  APP_LPTIMInit();
  
  /* Enable PWR */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* Suspend Systick interrupt */
  HAL_SuspendTick();

  /* Turn on LED */
  BSP_LED_On(LED_GREEN);
  
  /* Wait for button press */
  while (BSP_PB_GetState(BUTTON_USER) != 0)
  {
  }

  /* Turn off LED */
  BSP_LED_Off(LED_GREEN);

  while (1)
  {
    /* Disable LPTIM */
    __HAL_LPTIM_DISABLE(&LPTIMConf);
   
    /* Enable LPTIM and interrupt, and start in single count mode */
    APP_LPTIMStart();
        
    /* Enter STOP mode with interrupt wakeup */
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  }
}

/**
  * @brief   Clock configuration function
  * @param   None
  * @retval  None
  */
static void APP_RCCOscConfig(void)
{
  RCC_OscInitTypeDef OSCINIT  = {0};
  RCC_PeriphCLKInitTypeDef LPTIM_RCC = {0};

  /* LSI clock configuration */
  OSCINIT.OscillatorType = RCC_OSCILLATORTYPE_LSI;  /* Set the oscillator type to LSI */
  OSCINIT.LSIState = RCC_LSI_ON;                    /* Enable LSI */
  /* Clock initialization */
  if (HAL_RCC_OscConfig(&OSCINIT) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* LPTIM clock configuration */
  LPTIM_RCC.PeriphClockSelection = RCC_PERIPHCLK_LPTIM;     /* Select peripheral clock: LPTIM */
  LPTIM_RCC.LptimClockSelection = RCC_LPTIMCLKSOURCE_LSI;   /* Select LPTIM clock source: LSI */
  /* Peripheral clock initialization */
  if (HAL_RCCEx_PeriphCLKConfig(&LPTIM_RCC) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Enable LPTIM clock */
  __HAL_RCC_LPTIM_CLK_ENABLE();
}

/**
  * @brief   Initialize LPTIM
  * @param   None
  * @retval  None
  */
static void APP_LPTIMInit(void)
{
  /* LPTIM configuration */
  LPTIMConf.Instance = LPTIM;                         /* LPTIM */
  LPTIMConf.Init.Prescaler = LPTIM_PRESCALER_DIV128;  /* Prescaler: 128 */
  LPTIMConf.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE; /* Immediate update mode */
  /* Initialize LPTIM */
  if (HAL_LPTIM_Init(&LPTIMConf) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief   Enable LPTIM and interrupt, and start in single count mode
  * @param   None
  * @retval  None
  */
static void APP_LPTIMStart(void)
{
  /* Enable autoreload interrupt */
  __HAL_LPTIM_ENABLE_IT(&LPTIMConf, LPTIM_IT_ARRM);

  /* Enable LPTIM */
  __HAL_LPTIM_ENABLE(&LPTIMConf);

  /* Load autoreload value */
  __HAL_LPTIM_AUTORELOAD_SET(&LPTIMConf, 51);

  /* Delay 120us */
  APP_delay_us(120);
  
  /* Start single count mode */
  __HAL_LPTIM_START_SINGLE(&LPTIMConf);
}

/**
  * @brief   LPTIM autoreload match interrupt callback function
  * @param   None
  * @retval  None
  */
void HAL_LPTIM_AutoReloadMatchCallback(LPTIM_HandleTypeDef *hlptim)
{
  BSP_LED_Toggle(LED_GREEN);
}

/**
  * @brief   Microsecond delay function
  * @param   nus ：delay time in microseconds
  * @retval  None
  */
static void APP_delay_us(uint32_t nus)
 {
  __IO uint32_t Delay =1+ nus * (SystemCoreClock / 24U) / 1000000U;
  do
  {
    __NOP();
  }
  while(Delay--);
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
