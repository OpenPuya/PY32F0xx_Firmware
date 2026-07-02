/**
  ******************************************************************************
  * @file    py32f0xx_it.c
  * @author  MCU Application Team
  * @brief   Interrupt Service Routines.
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
#include "py32f0xx_it.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
 extern UART_HandleTypeDef UartHandle;
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*          Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/* PY32F0xx Peripheral Interrupt Handlers                                     */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file.                                          */
/******************************************************************************/
void USART1_IRQHandler(void)
{
  /* UART in mode Receiver */
  if ((__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_RXNE) != RESET) && \
      (__HAL_UART_GET_IT_SOURCE(&UartHandle, UART_IT_RXNE) != RESET))
  {
    aRxBuffer[cRxIndex] = (uint8_t)(UartHandle.Instance->DR & (uint8_t)0x00FF);

    /* Wait SR_TXE bit set 1 */
    while(__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_TXE) == RESET)
    {
    }
    
    /* Send received data */
    UartHandle.Instance->DR = aRxBuffer[cRxIndex];
    cRxIndex++;
    if(cRxIndex > (RX_MAX_LEN - 1))
    {
      cRxIndex = (RX_MAX_LEN - 1);
    }
  }
  if(__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_ORE) == SET)
  {
    __HAL_UART_CLEAR_OREFLAG(&UartHandle);
    
    /* Error callback function */
    APP_UsartErrorCallback();
  }
}

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
