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
uint32_t TIM1DataBuff[] = {2,200,3,300,4,400,5,500,6,600,7,700,8,800,9,900};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigTIM1Base(void);
static void APP_ConfigPWMChannel(void);
static void APP_ConfigDMABurst(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Configure system clock */
  APP_SystemClockConfig();
  
  /* Enable TIM1, GPIO, DMA, and SYSCFG clocks */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  
  /* Configure TIM1 PWM channels */
  APP_ConfigPWMChannel();
  
  /* Configure DMA channel */
  APP_ConfigDMABurst();
  
  /* Configure and enable TIM1 DMA Burst mode */
  APP_ConfigTIM1Base();
  
  while (1)
  {
  }
}

/**
  * @brief  Configure TIM1 PWM mode and related GPIO
  * @param  None
  * @retval None
  */
static void APP_ConfigPWMChannel(void)
{
  LL_GPIO_InitTypeDef TIM1CH1MapInit= {0};
  LL_TIM_OC_InitTypeDef TIM_OC_Initstruct = {0};

  /* Configure PA8 as TIM1_CH1 */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_8;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2; 
  TIM1CH1MapInit.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1CH1MapInit.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA,&TIM1CH1MapInit);

  TIM_OC_Initstruct.OCMode        = LL_TIM_OCMODE_PWM1;     /* Channel mode: PWM1 */
  TIM_OC_Initstruct.OCState       = LL_TIM_OCSTATE_ENABLE;  /* Channel state: enabled */
  TIM_OC_Initstruct.OCPolarity    = LL_TIM_OCPOLARITY_HIGH; /* Channel active polarity: high level */
  TIM_OC_Initstruct.OCIdleState   = LL_TIM_OCIDLESTATE_LOW; /* Channel idle polarity: low level */
  /* Channel 1 compare value: 100 */
  TIM_OC_Initstruct.CompareValue  = 100;
  /* Configure channel 1 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH1,&TIM_OC_Initstruct);
}

/**
  * @brief  Configure DMA Burst transfer
  * @param  None
  * @retval None
  */
static void APP_ConfigDMABurst(void)
{
  
  LL_DMA_InitTypeDef DMA_TIM1DMABurst ={0};
  
  /* Configure DMA channel 1 */
  DMA_TIM1DMABurst.PeriphOrM2MSrcAddress  = (uint32_t)&(TIM1->DMAR);          /* Destination address */
  DMA_TIM1DMABurst.MemoryOrM2MDstAddress  = (uint32_t)TIM1DataBuff;           /* Source address */
  DMA_TIM1DMABurst.Direction              = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;/* Transfer direction: Memory to peripheral */
  DMA_TIM1DMABurst.Mode                   = LL_DMA_MODE_NORMAL;               /* Normal mode */
  DMA_TIM1DMABurst.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT;        /* Disable peripheral address increment */
  DMA_TIM1DMABurst.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;          /* Enable memory address increment */
  DMA_TIM1DMABurst.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_WORD;           /* Data size alignment: Word */
  DMA_TIM1DMABurst.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_WORD;           /* Data size alignment: Word */
  DMA_TIM1DMABurst.Priority               = LL_DMA_PRIORITY_MEDIUM;           /* Channel priority: Medium */
  DMA_TIM1DMABurst.NbData                 = 16;                               /* Number of data: 16 */
  /* Initialize DMA channel 1 */
  LL_DMA_Init(DMA1,LL_DMA_CHANNEL_1,&DMA_TIM1DMABurst);
  
  /* Map TIM1 update interrupt to channel 1 */
  LL_SYSCFG_SetDMARemap_CH1(LL_SYSCFG_DMA_MAP_TIM1_UP);
  
  /* Enable DMA transfer complete interrupt */
  LL_DMA_EnableIT_TC(DMA1,LL_DMA_CHANNEL_1);
  
  /* Enable DMA channel 1 */
  LL_DMA_EnableChannel(DMA1,LL_DMA_CHANNEL_1);
  
  /* Enable DMA channel 1 interrupt request */
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  NVIC_SetPriority(DMA1_Channel1_IRQn,0);
}

/**
  * @brief  Configure TIM base
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
  TIM1CountInit.Autoreload          = 1000-1;                     /* Autoreload value: 1000 */
  TIM1CountInit.RepetitionCounter   = 1;                          /* Repetition counter value: 1 */
  
  /* Initialize TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit); 
  
  /* Enable update event DMA request */
  LL_TIM_EnableDMAReq_UPDATE(TIM1);
  
  /* Configure DMA burst transfer */
  LL_TIM_ConfigDMABurst(TIM1,LL_TIM_DMABURST_BASEADDR_RCR,LL_TIM_DMABURST_LENGTH_2TRANSFERS);
  
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
