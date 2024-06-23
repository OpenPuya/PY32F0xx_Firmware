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
#define STATE_OVER_THRESHOLD    0x00000001
#define STATE_WITHIN_THRESHOLD  0x00000002
#define STATE_UNDER_THRESHOLD   0x00000003

/* Private variables ---------------------------------------------------------*/
COMP_HandleTypeDef  hcomp1,hcomp2;
__IO uint32_t State = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_CompInit(void);
static void APP_InputVoltageLevelCheck(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main()
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();                                                             
  
  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize Comparator */
  APP_CompInit();
  while(1)
  {
    /* Check input voltage */
    APP_InputVoltageLevelCheck();                                        
    if(State==STATE_OVER_THRESHOLD)
    {
      BSP_LED_Toggle(LED_GREEN);
      HAL_Delay(200);
    }
    else if(State==STATE_WITHIN_THRESHOLD)
    {
      BSP_LED_On(LED_GREEN);
    }
    else
    {
      BSP_LED_Off(LED_GREEN);
    }
  }
}

/**
  * @brief  Comparator initialization
  * @param  None
  * @retval None
  */
static void APP_CompInit(void)
{
  hcomp1.Instance = COMP1;                                              /* Select COMP1 */
  hcomp1.Init.InputMinus      = COMP_INPUT_MINUS_VREFINT;               /* Negative input is VREF(1.2V) */
  hcomp1.Init.InputPlus       = COMP_INPUT_PLUS_IO3;                    /* Positive input is PA1 */
  hcomp1.Init.OutputPol       = COMP_OUTPUTPOL_NONINVERTED;             /* COMP1 polarity is non-inverted */
  hcomp1.Init.Mode            = COMP_POWERMODE_HIGHSPEED;               /* COMP1 power mode is set to High speed */
  hcomp1.Init.Hysteresis      = COMP_HYSTERESIS_DISABLE;                /* Hysteresis function is disabled */
  hcomp1.Init.WindowMode      = COMP_WINDOWMODE_COMP1_INPUT_PLUS_COMMON;/* COMP1 window mode */
  hcomp1.Init.TriggerMode     = COMP_TRIGGERMODE_IT_RISING_FALLING;     /* COMP1 interrupt on rising/falling edge */
  hcomp1.Init.DigitalFilter   = 0;

  /* Initialize COMP1 */
  if(HAL_COMP_Init(&hcomp1) != HAL_OK)                                  
  {
    APP_ErrorHandler();
  }
  /* Start COMP1 */
  HAL_COMP_Start(&hcomp1);                                              
  
  hcomp2.Instance = COMP2;                                              /* Select COMP2 */
  hcomp2.Init.InputMinus      = COMP_INPUT_MINUS_1_4VREFINT;            /* Negative input: VREF(0.3V) */
  hcomp2.Init.InputPlus       = COMP_INPUT_PLUS_IO3;                    /* Positive input: PA3 */
  hcomp2.Init.OutputPol       = COMP_OUTPUTPOL_NONINVERTED;             /* COMP2 polarity: non-inverted */
  hcomp2.Init.Mode            = COMP_POWERMODE_HIGHSPEED;               /* COMP2 power mode: High speed */
  hcomp2.Init.Hysteresis      = COMP_HYSTERESIS_DISABLE;                /* Hysteresis function disabled */
  hcomp2.Init.WindowMode      = COMP_WINDOWMODE_COMP1_INPUT_PLUS_COMMON;/* COMP2 window mode */
  hcomp2.Init.TriggerMode     = COMP_TRIGGERMODE_IT_RISING_FALLING;     /* COMP2 rising/falling edge interrupt */
  hcomp2.Init.DigitalFilter   = 0;

  /* COMP2 initialization */
  if(HAL_COMP_Init(&hcomp2) != HAL_OK)                                  
  {
    APP_ErrorHandler();
  }
  /* COMP2 start  */ 
  HAL_COMP_Start(&hcomp2);                                              
}

/**
  * @brief  Voltage comparison function
  * @param  None
  * @retval None
  */
static void APP_InputVoltageLevelCheck(void)
{
  /* Check the outputs of COMP1 and COMP2 */
  if (((HAL_COMP_GetOutputLevel(&hcomp1)) == COMP_OUTPUT_LEVEL_HIGH) 
   && ((HAL_COMP_GetOutputLevel(&hcomp2)) == COMP_OUTPUT_LEVEL_HIGH))
  {
    State = STATE_OVER_THRESHOLD;
  }
  else if (((HAL_COMP_GetOutputLevel(&hcomp1)) == COMP_OUTPUT_LEVEL_LOW)
       && ((HAL_COMP_GetOutputLevel(&hcomp2)) == COMP_OUTPUT_LEVEL_HIGH))
  {
    State = STATE_WITHIN_THRESHOLD;   
  }
  else if (((HAL_COMP_GetOutputLevel(&hcomp1)) == COMP_OUTPUT_LEVEL_LOW)
       && ((HAL_COMP_GetOutputLevel(&hcomp2)) == COMP_OUTPUT_LEVEL_LOW))
  {
    State = STATE_UNDER_THRESHOLD;
  }
}

/**
  * @brief  Comparator interrupt callback function
  * @param  hcomp：COMP handle
  * @retval None
  */
void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp)
{ 
  APP_InputVoltageLevelCheck();
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
