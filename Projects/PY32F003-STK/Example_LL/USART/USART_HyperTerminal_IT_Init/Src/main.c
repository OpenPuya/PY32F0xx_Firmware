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
#include "py32f003xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
#define TXSTARTMESSAGESIZE    (COUNTOF(aTxStartMessage) - 1)
#define TXENDMESSAGESIZE      (COUNTOF(aTxEndMessage) - 1)

/* Private variables ---------------------------------------------------------*/
uint8_t aRxBuffer[12] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
uint8_t aTxStartMessage[] = "\n\r USART Hyperterminal communication based on IT \n\r Enter 12 characters using keyboard :\n\r";
uint8_t aTxEndMessage[] = "\n\r Example Finished\n\r";

uint8_t *TxBuff = NULL;
__IO uint16_t TxCount = 0;

uint8_t *RxBuff = NULL;
__IO uint16_t RxCount = 0;

__IO ITStatus UartReady = RESET;

uint8_t  EieFlags = 0;
uint32_t ErrorFlags = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigUsart(USART_TypeDef *USARTx);
static void APP_UsartTransmit_IT(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);
static void APP_UsartReceive_IT(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);
static void APP_WaitToReady(void);

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

  /* Initialize USART */
  APP_ConfigUsart(USART1);
  
  /* Send a notification message indicating the start of communication through interruption */
  APP_UsartTransmit_IT(USART1, (uint8_t*)aTxStartMessage, TXSTARTMESSAGESIZE);
  APP_WaitToReady();

  /* Receive data using interrupt */
  APP_UsartReceive_IT(USART1, (uint8_t *)aRxBuffer, 12);
  APP_WaitToReady();

  /* Sending data through interrupt mode */
  APP_UsartTransmit_IT(USART1, (uint8_t*)aRxBuffer, 12);
  APP_WaitToReady();
    
  /* Send a notification message indicating the end of communication through interruption */
  APP_UsartTransmit_IT(USART1, (uint8_t*)aTxEndMessage, TXENDMESSAGESIZE);
  APP_WaitToReady();

  if(EieFlags)
  {
    /* If some error occurs during transmission, the LED blinking
       and the test failed */
      BSP_LED_Toggle(LED_GREEN);
      LL_mDelay(500);
  }
  else
  {
    /* Turn on LED if test passes then enter infinite loop */
    BSP_LED_On(LED_GREEN);
  }
  
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  Configure system clock
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

  /* Configure HSISYS as system clock source */
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
  * @brief  Wait for transfer to complete
  * @param  None
  * @retval None
  */
static void APP_WaitToReady(void)
{
  while (UartReady != SET);
  
  UartReady = RESET;
}

/**
  * @brief  USART configuration
  * @param  USARTx：USART module, can be USART1 or USART2
  * @retval None
  */
static void APP_ConfigUsart(USART_TypeDef *USARTx)
{
  /*Enable clock, initialize pins, enable NVIC interrupt*/
  if (USARTx == USART1) 
  {
    /*Enable GPIOA clock*/
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    /*Enable USART1 clock*/
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1);
    
    /*GPIOA configuration*/
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /*Select pin 2*/
    GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
    /*Select alternate function mode*/
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    /*Select output speed*/
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    /*Select push-pull output mode*/
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    /*Select pull-up*/
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    /*Select USART1 function*/
    GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
    /*Initialize GPIOA*/
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    /*Select pin 3*/
    GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
    /*Select USART1 function*/
    GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
    /*Initialize GPIOA*/
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    /*Set USART1 interrupt priority*/
    NVIC_SetPriority(USART1_IRQn,0);
    /*Enable USART1 interrupt*/
    NVIC_EnableIRQ(USART1_IRQn);
  }
  else if (USARTx == USART2)
  {
    /*Enable GPIOA clock*/
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    /*Enable USART1 clock*/
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
    
    /*GPIOA configuration*/
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /*Select pin 2*/
    GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
    /*Select alternate function mode*/
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    /*Select output speed*/
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    /*Select push-pull output mode*/
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    /*Select pull-up*/
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    /*Select USART2 function*/
    GPIO_InitStruct.Alternate = LL_GPIO_AF4_USART2;
    /*Initialize GPIOA*/
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    /*Select pin 3*/
    GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
    /*Select USART2 function*/
    GPIO_InitStruct.Alternate = LL_GPIO_AF4_USART2;
    /*Initialize GPIOA*/
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    /*Set USART1 interrupt priority*/
    NVIC_SetPriority(USART2_IRQn,0);
    /*Enable USART1 interrupt*/
    NVIC_EnableIRQ(USART2_IRQn);
  }
  
  /*USART configuration*/
  LL_USART_InitTypeDef USART_InitStruct = {0};
  /*Set baud rate*/
  USART_InitStruct.BaudRate = 9600;
  /*Set data width*/
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  /* Set stop bits */
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  /* Set parity */
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  /*Initialize USART*/
  LL_USART_Init(USARTx, &USART_InitStruct);
  
  /*Configure as full duplex asynchronous mode*/
  LL_USART_ConfigAsyncMode(USARTx);
  
  /*Enable UART module*/
  LL_USART_Enable(USARTx);
}

/**
  * @brief  USART transmit function
  * @param  USARTx：USART module, can be USART1 or USART2
  * @param  pData：transmit buffer
  * @param  Size：Size of the transmit buffer
  * @retval None
  */
static void APP_UsartTransmit_IT(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{
  TxBuff = pData;
  TxCount = Size;
  
  /*Enable transmit data register empty interrupt*/
  LL_USART_EnableIT_TXE(USARTx); 
}

/**
  * @brief  USART receive function
  * @param  USARTx：USART module, can be USART1 or USART2
  * @param  pData：receive buffer
  * @param  Size：Size of the receive buffer
  * @retval None
  */
static void APP_UsartReceive_IT(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{
  RxBuff = pData;
  RxCount = Size;
  
  /* Enable parity error interrupt */
  LL_USART_EnableIT_PE(USARTx);

  /* Enable error interrupt */
  LL_USART_EnableIT_ERROR(USARTx);

  /* Enable receive data register not empty interrupt */
  LL_USART_EnableIT_RXNE(USARTx);
}

/**
  * @brief  USART interrupt callback function
  * @param  USARTx：USART module, can be USART1 or USART2
  * @retval None
  */
void APP_UsartIRQCallback(USART_TypeDef *USARTx)
{
  /* Check if the receive data register is not empty */
  ErrorFlags = (LL_USART_IsActiveFlag_PE(USARTx) | LL_USART_IsActiveFlag_FE(USARTx) |\
                         LL_USART_IsActiveFlag_ORE(USARTx) | LL_USART_IsActiveFlag_NE(USARTx));
  if (ErrorFlags == RESET)
  {
    if ((LL_USART_IsActiveFlag_RXNE(USARTx) != RESET) && (LL_USART_IsEnabledIT_RXNE(USARTx) != RESET))
    {
      *RxBuff = LL_USART_ReceiveData8(USARTx);
       RxBuff++;
      if (--RxCount == 0U)
      {
        LL_USART_DisableIT_RXNE(USARTx);
        LL_USART_DisableIT_PE(USARTx);
        LL_USART_DisableIT_ERROR(USARTx);
        LL_USART_DisableDirectionRx(USARTx);
        
        UartReady = SET;
      }
      return;
    }
  }
  
  /* Receive error */ 
  if (ErrorFlags != RESET)
  {
    /* Clearing the ORE bit here will clear the FE, PE, NE,
       and flag bits together */
    LL_USART_ClearFlag_ORE(USARTx);
    
    /* Error callback function */
    APP_UsartErrorCallback();
    
    return;
  }
  
  /* Transmit data register empty  */ 
  if ((LL_USART_IsActiveFlag_TXE(USARTx) != RESET) && (LL_USART_IsEnabledIT_TXE(USARTx) != RESET))
    {
    /* To prevent the TC flag bit from being affected by other operations during
       data transmission, read the SR register in conjunction with write the DR 
       Register to clear the TC flag bit.
    */
    (void)(USARTx->SR);
      LL_USART_TransmitData8(USARTx, *TxBuff);
      TxBuff++;
      if (--TxCount == 0U)
      { 
        LL_USART_DisableIT_TXE(USARTx);
        LL_USART_EnableIT_TC(USARTx);
      }
      return;
  }
  
  /* Transmission complete  */
  if ((LL_USART_IsActiveFlag_TC(USARTx) != RESET) && (LL_USART_IsEnabledIT_TC(USARTx) != RESET))
  {
    LL_USART_DisableIT_TC(USARTx);
    UartReady = SET;
    return;
  }
}

/**
  * @brief  USART Error handling function
  * @param  None
  * @retval None
  */
void APP_UsartErrorCallback(void)
{
  EieFlags = ErrorFlags;
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
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line)  */
  /* infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
