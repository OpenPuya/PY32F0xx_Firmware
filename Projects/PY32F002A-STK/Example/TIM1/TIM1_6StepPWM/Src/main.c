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
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef sConfig1,sConfig2,sConfig3;
__IO uint32_t uwStep = 0;

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

  /* Initialize TIM1*/
  APP_TIM1_INIT();

  /* TIM1 PWM Configuration */
  APP_TIM1_PWM();

  /*Configuration of phase change events: software method*/
  HAL_TIMEx_ConfigCommutEvent_IT(&TimHandle, TIM_TS_NONE, TIM_COMMUTATION_SOFTWARE);
  
  /* Channel 1 starts to output PWM */
  if (HAL_TIM_OC_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)                  
  {
    APP_ErrorHandler();
  }

  /* Channel 1N starts to output PWM */
  if (HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Channel 2 starts to output PWM */
  if (HAL_TIM_OC_Start(&TimHandle, TIM_CHANNEL_2) != HAL_OK)                  
  {
    APP_ErrorHandler();
  }
  
  /* Channel 2N starts to output PWM */
  if (HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_2) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Channel 3 starts to output PWM */
  if (HAL_TIM_OC_Start(&TimHandle, TIM_CHANNEL_3) != HAL_OK)                  
  {
    APP_ErrorHandler();
  }

  /* Channel 3N starts to output PWM */
  if (HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_3) != HAL_OK)
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
  TimHandle.Init.Period            = 1000 - 1;                                     

  /* Prescaler value */
  TimHandle.Init.Prescaler         = 1 - 1;                                 

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
  sConfig1.OCMode       = TIM_OCMODE_PWM1;                                     

  /*OC channel output active high */
  sConfig1.OCPolarity   = TIM_OCPOLARITY_HIGH;                                                                 

  /*OCN channel output active high */
  sConfig1.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                

  /*Idle state OC1N output low level */
  sConfig1.OCNIdleState = TIM_OCNIDLESTATE_RESET;                              

  /*Idle state OC1 output low level*/
  sConfig1.OCIdleState  = TIM_OCIDLESTATE_RESET;                               

  sConfig1.OCFastMode   = TIM_OCFAST_DISABLE;                         /* Disable fast mode */

  /*Set the duty cycle of channel 1 to (500/1000)=50% */
  sConfig1.Pulse = 500 - 1;                                              

  /* Channel 1 configuration */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  sConfig2 = sConfig1;
  /* Set the duty cycle of channel 1 to (250/1000)=250%*/
  sConfig2.Pulse = 250 - 1;                                               

  /* Channel 2 configuration */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig2, TIM_CHANNEL_2) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  sConfig3 = sConfig1;
  /* Set the duty cycle of channel 1 to (125/1000)=12.5% */
  sConfig3.Pulse = 125 - 1;                                              

  /* Channel 3 configuration */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3) != HAL_OK)
  {
    /* Configuration Error */
    APP_ErrorHandler();
  }

}

/**
  * @brief  Phase change event execution function, 6-step output configuration
  * @param  None
  * @retval None
  */
void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim)
{
  if (uwStep == 0)
  {
    /*Configured as PWM1*/
    sConfig1.OCMode     = TIM_OCMODE_PWM1;                             
    /*Channel 1 is configured as PWM*/
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1);   
    /*Channel 1 output PWM*/
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);                    
    /*Channel 1N stop output*/
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_1);                    

    /*Configured as PWM1*/
    sConfig3.OCMode     = TIM_OCMODE_PWM1;                             
    /*Channel 3 is configured as PWM */
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3);   
    /*Channel 3N output PWM */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_3);                   
    /*Channel 3 stop output */
    HAL_TIM_PWM_Stop(&TimHandle, TIM_CHANNEL_3);                      

    /*Channel 2 stop output */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_2);                       
    /*Channel 2N stop output */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_2);                   
    uwStep = 1;
  }

  else if (uwStep == 1)
  {
    /*Configured as PWM1 */
    sConfig2.OCMode     = TIM_OCMODE_PWM1;                             
    /*Channel 2 is configured as PWM */
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig2, TIM_CHANNEL_2);   
    /*Channel 2N starts output.*/
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_2);                   
    /*Channel 3N stop output */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_3);                   

    uwStep++;
  }

  else if (uwStep == 2)
  {
    /*Configured as PWM1*/
    sConfig3.OCMode     = TIM_OCMODE_PWM1;                             
    /*Channel 3 is configured as PWM*/
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3);  
    /*Channel 3 starts output.*/
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_3);                     
 
    /*Channel 1 stop output*/
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_1);                       

    uwStep++;
  }

  else if (uwStep == 3)
  {
    /*Channel 2N stop output*/
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_2);                    
    /*Configured as PWM1*/
    sConfig1.OCMode     = TIM_OCMODE_PWM1;                             
    /*Channel 1 is configured as PWM */
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1);  
    /*Channel 1N starts output */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_1);      
 
    uwStep++;
  }
  else if (uwStep == 4)
  {
    /* Channel 3 stop output */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_3);                       

    /* Configured as PWM1 */
    sConfig2.OCMode     = TIM_OCMODE_PWM1;                             
    /*Channel 2 is configured as PWM */
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig2, TIM_CHANNEL_2);   
    /* Channel 2 starts output */
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_2);                     

    uwStep++;
  }

  else if (uwStep == 5)
  {
    /* Configured as PWM1 */
    sConfig3.OCMode     = TIM_OCMODE_PWM1;                             
    /* Channel 3 is configured as PWM */
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3);  
    /* Channel 3N starts output */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_3);                   

    /* Channel 1N stop output */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_1);                   

    uwStep++;
  }

  else
  {
    /* Configured as PWM1 */
    sConfig1.OCMode     = TIM_OCMODE_PWM1;                           
    /* Channel 1 is configured as PWM*/
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1); 
    /*Channel 1 output PWM*/
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);                    

    /* Channel 2 stop output */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_2);                    

    uwStep = 1;
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
