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
uint32_t uwStep = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigTIM1Base(void);
static void APP_Config6StepPWMChannel(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Configure system clock */
  APP_SystemClockConfig();
  
  /* Enable SysTick interrupt */
  LL_SYSTICK_EnableIT();
  
  /* Enable TIM1 and GPIO clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA|LL_IOP_GRP1_PERIPH_GPIOB);
  
  /* Configure and enable TIM16 Step PWM mode */
  APP_ConfigTIM1Base();
  
  /*  Infinite loop  */
  while (1)
  {
  }
}

/**
  * @brief  Configure TIM1 6StepPWM related GPIO
  * @param  None
  * @retval None
  */
static void APP_Config6StepPWMChannel(void)
{
  LL_GPIO_InitTypeDef TIM1CH1MapInit= {0};
  LL_TIM_OC_InitTypeDef TIM_OC_Initstruct ={0};

  /* Configure PA7/PA8/PA9/PA10 as TIM1_CH1N/TIM1_CH1/TIM1_CH2/TIM1_CH3 */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_7|LL_GPIO_PIN_8|LL_GPIO_PIN_9|LL_GPIO_PIN_10;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2; 
  TIM1CH1MapInit.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1CH1MapInit.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA,&TIM1CH1MapInit);
  
  /* Configure PB0/PB1 as TIM1_CH2N/TIM1_CH3N */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_0|LL_GPIO_PIN_1;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2; 
  TIM1CH1MapInit.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1CH1MapInit.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB,&TIM1CH1MapInit);
  
  /* Configure PWM channels */
  TIM_OC_Initstruct.OCMode        = LL_TIM_OCMODE_PWM1;     /* Mode: PWM1 */
  TIM_OC_Initstruct.OCState       = LL_TIM_OCSTATE_ENABLE;  /* Channel enable */
  TIM_OC_Initstruct.OCNState      = LL_TIM_OCSTATE_ENABLE;  /* Complementary channel enable */
  TIM_OC_Initstruct.OCPolarity    = LL_TIM_OCPOLARITY_HIGH; /* Active polarity: high level */
  TIM_OC_Initstruct.OCNPolarity   = LL_TIM_OCPOLARITY_HIGH; /* Complementary channel active polarity: high level */
  TIM_OC_Initstruct.OCIdleState   = LL_TIM_OCIDLESTATE_LOW; /* Complementary channel active polarity: high level */
  TIM_OC_Initstruct.OCNIdleState  = LL_TIM_OCIDLESTATE_LOW; /* Complementary channel idle state: low level */
  TIM_OC_Initstruct.CompareValue  = 50;                     /* Compare value: 50 */
  /* Configure channel 1 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH1,&TIM_OC_Initstruct);
  /* Configure channel 2 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH2,&TIM_OC_Initstruct);
  /* Configure channel 3 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH3,&TIM_OC_Initstruct);
  /* Disable all channel outputs */
  LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1|LL_TIM_CHANNEL_CH1N|
                                LL_TIM_CHANNEL_CH2|LL_TIM_CHANNEL_CH2N|
                                LL_TIM_CHANNEL_CH3|LL_TIM_CHANNEL_CH3N);
}

/**
  * @brief  TIM1 6StepPWM configuration function
  * @param  None
  * @retval None
  */
static void APP_ConfigTIM1Base(void)
{
  /* Configure TIM1 */
  LL_TIM_InitTypeDef TIM1CountInit = {0};
 
  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;  /* No clock division */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;      /* Up counting mode */
  TIM1CountInit.Prescaler           = 24-1;                       /* Prescaler value: 24 */
  TIM1CountInit.Autoreload          = 100-1;                      /* Autoreload value: 100 */
  TIM1CountInit.RepetitionCounter   = 0;                          /* Repetition counter value: 0 */
  
  /* Initialize TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);
  
  /* Configure TIM16 StepPWM related channels */
  APP_Config6StepPWMChannel();
  
  /* Enable COM interrupt */
  LL_TIM_EnableIT_COM(TIM1);
  /* Set COM interrupt priority */
  NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn,1);
  /* Enable COM interrupt NVIC IRQ */
  NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
  
  /* Enable preload feature */
  LL_TIM_CC_EnablePreload(TIM1);
  
  /* Enable main output */
  LL_TIM_EnableAllOutputs(TIM1);

  /* Enable TIM1 counter */
  LL_TIM_EnableCounter(TIM1);
}

/**
  * @brief  TIM1 COM interrupt callback function
  * @param  None
  * @retval None
  */
void APP_COMCallback(void)
{
  switch(uwStep)
  {
    /* TIM1 COM interrupt callback function */
    case 0:
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);   /* CH1 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3N);  /* CH3N: 1 */
      uwStep++;
      break;
    /* Step 2 configuration */
    case 1:
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);   /* CH1 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2N);  /* CH2N: 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3N); /* CH3N: 0 */
      uwStep++;
      break;
    /* Step 3 configuration */
    case 2:
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1);  /* CH1 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2N);  /* CH2N: 1 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3);   /* CH3 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3N); /* CH3N: 0 */
      uwStep++;
      break;
    /* Step 4 configuration */
    case 3:
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1);  /* CH1 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1N);  /* CH1N: 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3);   /* CH3 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3N); /* CH3N: 0 */
      uwStep++;
      break;
    /* Step 5 configuration */
    case 4:
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1);  /* CH1 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1N);  /* CH1N: 1 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2);   /* CH2 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3N); /* CH3N: 0 */
      uwStep++;
      break;
    /* Step 6 configuration */
    case 5:
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1);  /* CH1 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2);   /* CH2 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3N);  /* CH3N: 1 */
      uwStep++;
      break;
    /* 第1步配置 */
    case 6:
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);   /* CH1 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3N);  /* CH3N: 1 */
      uwStep = 1;
      break;
  }
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
  LL_RCC_HSI_SetCalibFreq(LL_RCC_HSICALIBRATION_24MHz);
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
  LL_Init1msTick(24000000);
  
  /* Update system clock global variable SystemCoreClock (can also be updated by calling SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(24000000);
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
