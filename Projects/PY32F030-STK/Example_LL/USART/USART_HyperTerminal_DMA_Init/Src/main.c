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
uint8_t aTxBuffer[] = "UART Test";
uint8_t aRxBuffer[30];
__IO ITStatus UartReady = RESET;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigUsart(USART_TypeDef *USARTx);
static void APP_ConfigDma(USART_TypeDef *USARTx);
static void APP_UsartTransmit_DMA(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);
static void APP_UsartReceive_DMA(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure system clock */
  APP_SystemClockConfig();
  
  /* Configure USART */
  APP_ConfigUsart(USART1);
  
  /* Send "UART Test" using DMA and wait for transmission to complete */
  APP_UsartTransmit_DMA(USART1, (uint8_t*)aTxBuffer, sizeof(aTxBuffer)-1);
  while (UartReady != SET)
  {
  }
  UartReady = RESET;

  while (1)
  {
    /* Receive data */
    APP_UsartReceive_DMA(USART1, (uint8_t *)aRxBuffer, 12);
    while (UartReady != SET)
    {
    }
    UartReady = RESET;
    
    /* Send data */
    APP_UsartTransmit_DMA(USART1, (uint8_t*)aRxBuffer, 12);
    while (UartReady != SET)
    {
    }
    UartReady = RESET;
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
  * @brief  USART configuration function
  * @param  USARTx：USART module, can be USART1 or USART2
  * @retval None
  */
static void APP_ConfigUsart(USART_TypeDef *USARTx)
{
  /* Enable clock, initialize pins, enable NVIC interrupt */
  if (USARTx == USART1) 
  {
    /* Enable GPIOA clock */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    /* Enable USART1 clock */
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1);
        
    /* GPIOA configuration */
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* Select pin 2 */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
    /* Select alternate function mode */
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    /* Select output speed */
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    /* Select push-pull output mode */
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    /* Select pull-up */
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    /* Select USART1 function */
    GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
    /* Initialize GPIOA */
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    /* Select pin 3 */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
    /* Select USART1 function */
    GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
    /* Initialize GPIOA */
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    /* Set USART1 interrupt priority */
    NVIC_SetPriority(USART1_IRQn,0);
    /* Enable USART1 interrupt */
    NVIC_EnableIRQ(USART1_IRQn);
  }
  else if (USARTx == USART2)
  {
    /* Enable GPIOA clock */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    /* Enable USART1 clock */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
    
    /* GPIOA configuration */
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* Select pin 2 */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
    /* Select alternate function mode */
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    /* Select output speed */
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    /* Select push-pull output mode */
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    /* Select pull-up */
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    /* Select USART2 function */
    GPIO_InitStruct.Alternate = LL_GPIO_AF4_USART2;
    /* Initialize GPIOA */
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    /* Select pin 3 */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
    /* Select USART2 function */
    GPIO_InitStruct.Alternate = LL_GPIO_AF4_USART2;
    /* Initialize GPIOA */
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    /* Set USART1 interrupt priority */
    NVIC_SetPriority(USART2_IRQn,0);
    /* Enable USART1 interrupt */
    NVIC_EnableIRQ(USART2_IRQn);
  }

  /*Configure DMA*/
  APP_ConfigDma(USARTx);

  /* USART configuration */
  LL_USART_InitTypeDef USART_InitStruct = {0};
  /* Set baud rate */
  USART_InitStruct.BaudRate = 9600;
  /* Set data width */
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
  * @brief  DMA configuration function
  * @param  USARTx：USART module, can be USART1 or USART2
  * @retval None
  */
static void APP_ConfigDma(USART_TypeDef *USARTx)
{
  /* Enable DMA clock and syscfg clock */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);

  
  /* Configure DMA channel LL_DMA_CHANNEL_1 for transmission */
  LL_DMA_ConfigTransfer(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_MEMORY_TO_PERIPH | \
                      LL_DMA_MODE_NORMAL                   | \
                      LL_DMA_PERIPH_NOINCREMENT  | \
                      LL_DMA_MEMORY_INCREMENT  | \
                      LL_DMA_PDATAALIGN_BYTE | \
                      LL_DMA_MDATAALIGN_BYTE | \
                      LL_DMA_PRIORITY_LOW);
  
 
  /* Configure DMA channel LL_DMA_CHANNEL_2 for reception */
  LL_DMA_ConfigTransfer(DMA1, LL_DMA_CHANNEL_2, LL_DMA_DIRECTION_PERIPH_TO_MEMORY | \
                      LL_DMA_MODE_NORMAL                   | \
                      LL_DMA_PERIPH_NOINCREMENT  | \
                      LL_DMA_MEMORY_INCREMENT  | \
                      LL_DMA_PDATAALIGN_BYTE | \
                      LL_DMA_MDATAALIGN_BYTE | \
                      LL_DMA_PRIORITY_LOW);

  /* Configure DMA request mapping for channels associated with USART1 and USART2 */
  if (USARTx ==  USART1)
  {
    /* USART1_TX maps to channel LL_DMA_CHANNEL_1, USART1_RX maps to channel LL_DMA_CHANNEL_2 */
    LL_SYSCFG_SetDMARemap_CH1(LL_SYSCFG_DMA_MAP_USART1_TX);
    LL_SYSCFG_SetDMARemap_CH2(LL_SYSCFG_DMA_MAP_USART1_RX);
  }
  else
  {
    /* USART2_TX maps to channel LL_DMA_CHANNEL_1, USART2_RX maps to channel LL_DMA_CHANNEL_2 */
    LL_SYSCFG_SetDMARemap_CH1(LL_SYSCFG_DMA_MAP_USART2_TX);
    LL_SYSCFG_SetDMARemap_CH2(LL_SYSCFG_DMA_MAP_USART2_RX);
  }
  
  /*Set interrupt priority*/
  NVIC_SetPriority(DMA1_Channel1_IRQn, 1);
  /*Enable interrupt*/
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  
  /*Set interrupt priority*/
  NVIC_SetPriority(DMA1_Channel2_3_IRQn, 1);
  /*Enable interrupt*/
  NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
}

/**
  * @brief  USART transmit function
  * @param  USARTx：USART module, can be USART1 or USART2
  * @param  pData：transmit buffer
  * @param  Size：Size of the transmit buffer
  * @retval None
  */
static void APP_UsartTransmit_DMA(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{  
  /*Configure DMA channel 1*/
  LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
  LL_DMA_ClearFlag_GI1(DMA1);
  uint32_t *temp = (uint32_t *)&pData;
  LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, *(uint32_t *)temp);
  LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&(USARTx->DR));
  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, Size);
  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
  
  LL_USART_ClearFlag_TC(USARTx);

  /* Enable USART DMA channel for transmission */
  LL_USART_EnableDMAReq_TX(USARTx);
}

/**
  * @brief  USART receive function
  * @param  USARTx：USART module, can be USART1 or USART2
  * @param  pData：receive buffer
  * @param  Size：Size of the receive buffer
  * @retval None
  */
static void APP_UsartReceive_DMA(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{
  /*Configure DMA channel 2*/
  LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
  LL_DMA_ClearFlag_GI2(DMA1);
  uint32_t *temp = (uint32_t *)&pData;
  LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_2, *(uint32_t *)temp);
  LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_2, (uint32_t)&USARTx->DR);
  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, Size);
  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
  
  LL_USART_ClearFlag_ORE(USARTx);
  
  /* Enable USART DMA channel for transmission */
  LL_USART_EnableDMAReq_RX(USARTx);
}

/**
  * @brief  USART interrupt callback function
  * @param  USARTx：USART module, can be USART1 or USART2
  * @retval None
  */
void APP_UsartIRQCallback(USART_TypeDef *USARTx)
{
  /* Transmission complete */
  if ((LL_USART_IsActiveFlag_TC(USARTx) != RESET) && (LL_USART_IsEnabledIT_TC(USARTx) != RESET))
  {
    LL_USART_DisableIT_TC(USARTx);
    UartReady = SET;
  
    return;
  }
}

/**
  * @brief  DMA channel 1 interrupt callback function for transmission
  * @param  None
  * @retval None
  */
void APP_DmaChannel1IRQCallback(USART_TypeDef *USARTx)
{
  if(LL_DMA_IsActiveFlag_TC1(DMA1) == 1)
  {
    LL_DMA_ClearFlag_GI1(DMA1);
    LL_USART_DisableDMAReq_TX(USARTx);
    LL_USART_EnableIT_TC(USARTx);
  }
}

/**
  * @brief  DMA channel 2/3 interrupt callback function for reception
  * @param  None
  * @retval None
  */
void APP_DmaChannel2_3_IRQCallback(USART_TypeDef *USARTx)
{
  if(LL_DMA_IsActiveFlag_TC2(DMA1) == 1)
  {
    LL_DMA_ClearFlag_GI2(DMA1);
    LL_USART_DisableDMAReq_RX(USARTx);
    UartReady = SET;
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
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
