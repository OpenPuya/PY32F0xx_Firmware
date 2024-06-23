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
static void APP_ConfigTIM1OnePulse(void);
static void APP_ConfigTIM1Channel(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Configure system clock */
  APP_SystemClockConfig();
  
  /* Enable TIM1 and GPIOA clocks */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  
  /* Configure and enable TIM1 one-pulse mode */
  APP_ConfigTIM1OnePulse();
  
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  TIM1 one-pulse mode channel configuration function
  * @param  None
  * @retval None
  */
static void APP_ConfigTIM1Channel(void)
{
  /* Channel 2 configuration */
  /* Configure active edge as rising edge */
  LL_TIM_IC_SetPolarity(TIM1,LL_TIM_CHANNEL_CH2,LL_TIM_IC_POLARITY_RISING);
  /* Configure channel as input mode */
  LL_TIM_IC_SetActiveInput(TIM1,LL_TIM_CHANNEL_CH2,LL_TIM_ACTIVEINPUT_DIRECTTI);
  
  /* Channel 2 input mapped to PA9 */
  LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_9,LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetAFPin_8_15(GPIOA,LL_GPIO_PIN_9,LL_GPIO_AF_2);

  /* Enable channel 2 */
  LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2);
  
  /* Channel 1 configuration */
  /* Set output polarity to high */
  LL_TIM_OC_SetPolarity(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_OCPOLARITY_HIGH);
  /* Set idle state to low */
  LL_TIM_OC_SetIdleState(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_OCIDLESTATE_LOW);
  /* Set compare value to 200 */
  LL_TIM_OC_SetCompareCH1(TIM1,200);
  /* Configure channel as PWM2 mode */
  LL_TIM_OC_SetMode(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_OCMODE_PWM2);
  
  /* Output mapped to PA8 */
  LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_8,LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetAFPin_8_15(GPIOA,LL_GPIO_PIN_8,LL_GPIO_AF_2);

  /* Enable channel 1 */
  LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);
  
}

/**
  * @brief  TIM1 one-pulse mode configuration function
  * @param  None
  * @retval None
  */
static void APP_ConfigTIM1OnePulse(void)
{
  /* CK_INT not divided */
  LL_TIM_SetClockDivision(TIM1,LL_TIM_CLOCKDIVISION_DIV1);
  /* Up counting mode */
  LL_TIM_SetCounterMode(TIM1,LL_TIM_COUNTERMODE_UP);
  /* Set auto-reload value to 1000 */
  LL_TIM_SetAutoReload(TIM1,1000-1);
  /* Set CK_CNT prescaler value to 800 */
  LL_TIM_SetPrescaler(TIM1,800-1);

  /*  Set TIM1 as slave mode trigger */
  LL_TIM_SetSlaveMode(TIM1,LL_TIM_SLAVEMODE_TRIGGER);
  
  /* Set input trigger source as TI2FP2 */
  LL_TIM_SetTriggerInput(TIM1,LL_TIM_TS_TI2FP2);
  
  /* Trigger/output channel configuration */
  APP_ConfigTIM1Channel();
  
  /* Set one-pulse mode */
  LL_TIM_SetOnePulseMode(TIM1,LL_TIM_ONEPULSEMODE_SINGLE);
  
  /* Disable automatic output */
  LL_TIM_DisableAutomaticOutput(TIM1);
  /* Enable main output */
  LL_TIM_EnableAllOutputs(TIM1);
  
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
