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
#include "py32f002xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t  aRxBuffer[RX_MAX_LEN] = {0};
uint32_t cRxIndex = 0;

/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigUsart(USART_TypeDef *USARTx);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure system clock */
  APP_SystemClockConfig();
  
  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);
  
  /* Configure USART */
  APP_ConfigUsart(USART1);
  
  /* Enable RX Not Empty Interrupt */
  LL_USART_EnableIT_RXNE(USART1);

  while (1)
  {
  }
}

/**
  * @brief  USART configuration.
  * @param  USARTx：USART module, can be USART1
  * @retval None
  */
static void APP_ConfigUsart(USART_TypeDef *USARTx)
{
/*Enable clock, initialize pins, enable NVIC interrupt*/
  
  /*Enable GPIOA clock*/
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  /*Enable USART1 clock*/
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1);
    
  /*GPIOA configuration*/
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  /*Select pin 2*/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
  /* Select alternate function mode */
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  /* Select output speed */
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  /* Select push-pull output mode */
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  /*Pull-up*/
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  /* Select USART1 function */
  GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
  /* Initialize GPIOA */
  LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
  /*Select pin 3*/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
  /* Select USART1 function */
  GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
  /* Initialize GPIOA */
  LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
      
  /*Set USART1 interrupt priority*/
  NVIC_SetPriority(USART1_IRQn,0);
  /*Enable USART1 interrupt*/
  NVIC_EnableIRQ(USART1_IRQn);
    
 /*Configure USART*/
  LL_USART_InitTypeDef USART_InitStruct = {0};
  /*Set baud rate*/
  USART_InitStruct.BaudRate = 115200;
  /*Set data width*/
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  /* Set stop bits */
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  /* Set parity */
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  /* Initialize USART */
  LL_USART_Init(USARTx, &USART_InitStruct);
  
  /* Configure as full duplex asynchronous mode */
  LL_USART_ConfigAsyncMode(USARTx);
  
  /* Enable UART module */
  LL_USART_Enable(USARTx);
      
}

/**
  * @brief  System clock configuration
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

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /*Configure HSISYS as system clock source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);

  /* Update system clock global variable SystemCoreClock (can also be updated by calling SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(8000000);
}

/**
  * @brief  USART Error interrupt handler function
  * @param  None
  * @retval None
  */
void APP_UsartErrorCallback(void)
{
  /* Turn on the LED */
  BSP_LED_On(LED_GREEN);
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
