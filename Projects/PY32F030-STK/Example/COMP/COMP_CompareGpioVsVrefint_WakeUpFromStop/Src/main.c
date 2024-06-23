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
  
/* Private variables ---------------------------------------------------------*/
COMP_HandleTypeDef hcomp1;

/* Private define ------------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_RccInit(void);
static void APP_CompInit(void);
static void APP_CompIt(void);
static void APP_LedRun(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{  
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();

  /* Initialize button */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);
 
  /* Suspend SysTick interrupt */
  HAL_SuspendTick();

  /* Initialize clock settings */
  APP_RccInit();

  /* Initialize COMP */
  APP_CompInit();
 
  /* Enable interrupts */
  APP_CompIt();
 
  /* Start COMP */
  HAL_COMP_Start(&hcomp1);
  
  BSP_LED_On(LED_GREEN);

  /* Wait for button press */
  while(BSP_PB_GetState(BUTTON_USER) != 0)
  {
  }
  BSP_LED_Off(LED_GREEN);

  /* Enter STOP mode */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);  

  /* Resume the SysTick interrupt */
  HAL_ResumeTick();

  HAL_Delay(1000);
  while(1)
  {
    APP_LedRun();
  }
}

/**
  * @brief  Comparator clock configuration function
  * @param  None
  * @retval None
  */
static void APP_RccInit(void)
{                    
  RCC_OscInitTypeDef RCCCONF       = {0};
  RCC_PeriphCLKInitTypeDef COMPRCC = {0} ;
  
  RCCCONF.OscillatorType = RCC_OSCILLATORTYPE_LSI;        /* RCC uses internal LSI */
  RCCCONF.LSIState = RCC_LSI_ON;                          /* Enable LSI */
  RCCCONF.PLL.PLLState = RCC_PLL_NONE;

  COMPRCC.PeriphClockSelection = RCC_PERIPHCLK_COMP1;     /* Peripheral selection: COMP1 */
  COMPRCC.Comp1ClockSelection = RCC_COMP1CLKSOURCE_LSC;   /* Independent clock source for COMP1: LSC */

  HAL_RCC_OscConfig(&RCCCONF);                            /* Initialize clock settings */
  HAL_RCCEx_PeriphCLKConfig(&COMPRCC);                    /* Initialize RCC peripheral clock settings */
}

/**
  * @brief  Comparator initialization function
  * @param  None
  * @retval None
  */
static void APP_CompInit(void)
{ 
  __HAL_RCC_COMP1_CLK_ENABLE();                           /* Enable COMP1 clock */

  hcomp1.Instance = COMP1;                              /* COMP1 */

  hcomp1.Init.InputPlus = COMP_INPUT_PLUS_IO3;               /* Positive input: PA1 */
  hcomp1.Init.InputMinus = COMP_INPUT_MINUS_VREFINT;         /* Negative input: VREFINT */
  hcomp1.Init.OutputPol = COMP_OUTPUTPOL_NONINVERTED;        /* COMP1 polarity is non-inverted */
  hcomp1.Init.Mode = COMP_POWERMODE_MEDIUMSPEED;             /* COMP1 power mode: Medium speed */
  hcomp1.Init.Hysteresis = COMP_HYSTERESIS_ENABLE;           /* Hysteresis function enabled */
  hcomp1.Init.WindowMode = COMP_WINDOWMODE_DISABLE;          /* Window function disable */
  hcomp1.Init.TriggerMode = COMP_TRIGGERMODE_IT_FALLING;     /* Trigger mode: Falling edge interrupt */
  hcomp1.Init.DigitalFilter = 0;
                           
  HAL_COMP_Init(&hcomp1);
}

/**
  * @brief  Comparator interrupt enable function
  * @param  None
  * @retval None
  */
static void APP_CompIt(void)
{
  /* Enable COMP interrupt */
  HAL_NVIC_EnableIRQ(ADC_COMP_IRQn);
  HAL_NVIC_SetPriority(ADC_COMP_IRQn, 0x01, 0);
}

/**
  * @brief  LED toggle function
  * @param  None
  * @retval None
  */
static void APP_LedRun(void)
{
  BSP_LED_Toggle(LED_GREEN);
  HAL_Delay(200);
  BSP_LED_Toggle(LED_GREEN);
  HAL_Delay(200);
}

/**
  * @brief  Comparator interrupt callback function
  * @param  hcomp：Comparator handle
  * @retval None
  */
void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp)
{
  BSP_LED_On(LED_GREEN);
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
