/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
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
#define  PERIOD_VALUE       (uint32_t)(50 - 1)
#define  PULSE1_VALUE       10
#define  PULSE2_VALUE       20
#define  PULSE3_VALUE       30
#define  PULSE4_VALUE       40
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef sConfig;

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_TIM1_INIT(void);
static void APP_TIM1_PWM(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  APP_TIM1_INIT();

  APP_TIM1_PWM();

  /* Start PWM output on Channel 1 */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)                  
  {
    APP_ErrorHandler();
  }

  /* Start PWM output on Channel 2 */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_2) != HAL_OK)                  
  {
    APP_ErrorHandler();
  }

  /* Start PWM output on Channel 3 */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_3) != HAL_OK)                  
  {
    APP_ErrorHandler();
  }

  /* Start PWM output on Channel 4 */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_4) != HAL_OK)                  
  {
    APP_ErrorHandler();
  }

  /* infinite loop */
  while (1)
  {


  }
}
/**
  * @brief  Initialize TIM1
  * @param  None
  * @retval None
  */
static void APP_TIM1_INIT(void)
{
  /* Select TIM1 */
  TimHandle.Instance = TIM1;                                                  
  
  /* Auto-reload value */
  TimHandle.Init.Period            = 50;                                     

  /* Prescaler value */
  TimHandle.Init.Prescaler         = 800 - 1;                                 

  /* Clock not divided */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                  

  /* Up-counting mode*/
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                      

  /* No repetition */
  TimHandle.Init.RepetitionCounter = 1 - 1;                                   

  /* Auto-reload register not buffered */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;          

  /* Initialize clock settings */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                                
  {
    APP_ErrorHandler();
  }

}
/**
  * @brief  TIM1 PWM Configuration
  * @param  None
  * @retval None
  */
static void APP_TIM1_PWM(void)
{
  /*Output configured for PWM1 mode */
  sConfig.OCMode       = TIM_OCMODE_PWM1;                                     

  /*OC channel output active high */
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;                                 

  /*Disable the output compare fast mode */
  sConfig.OCFastMode   = TIM_OCFAST_DISABLE;                                  

  /*OCN channel output active high */
  sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                

  /*Idle state OC1N output low level */
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;                              

  /*Idle state OC1 output low level*/
  sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;                               

  /*Set CC1 pulse value to 10, resulting in a duty cycle of 10/50 = 20%*/
  sConfig.Pulse = PULSE1_VALUE;                                              

  /* Channel 1 configuration */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /*Set CC2 pulse value to 20, resulting in a duty cycle of 20/50 = 40% */
  sConfig.Pulse = PULSE2_VALUE;                                               

  /* Configure Channel 2 for PWM */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_2) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /*Set CC3 pulse value to 30, resulting in a duty cycle of 30/50 = 60%*/
  sConfig.Pulse = PULSE3_VALUE;                                              

  /* Configure Channel 3 for PWM */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_3) != HAL_OK)
  {
    /* Configuration Error */
    APP_ErrorHandler();
  }

  /* Set CC4 pulse value to 40, resulting in a duty cycle of 40/50 = 80% */
  sConfig.Pulse = PULSE4_VALUE;                                               

  /*Configure Channel 4 for PWM */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_4) != HAL_OK)
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
  /* infinite loop */
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
  /* infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
