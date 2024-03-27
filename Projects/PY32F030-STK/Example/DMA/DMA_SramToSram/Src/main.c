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
/* Private variables ---------------------------------------------------------*/
DMA_HandleTypeDef     DmaHandle;
uint32_t aSRC_Const_Buffer[BUFFER_SIZE];       /* Source buffer for data transfer */
uint32_t aDST_Buffer[BUFFER_SIZE];             /* Destination buffer for data transfer */
__IO uint32_t transferCompleteDetected=0;      /* Set to 1 when transfer is complete */
__IO uint32_t transferErrorDetected=0;         /* Set to 1 when transfer encounters an error */
__IO uint32_t transferFailedDetected=0;        /* Set to 1 when the transferred data is corrupted */

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_DmaConfig(void);
static void APP_TransferComplete(DMA_HandleTypeDef *DmaHandle);
static void APP_TransferError(DMA_HandleTypeDef *DmaHandle);


/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);
  
  /* Initialize data in DMA source buffer */
  for (uint8_t i = 0; i < BUFFER_SIZE; i++)
  {
    aSRC_Const_Buffer[i] = i;
  }

  /* Configure DMA */
  APP_DmaConfig();

  /* Enable DMA and DMA interrupts */
  if (HAL_DMA_Start_IT(&DmaHandle, (uint32_t)&aSRC_Const_Buffer, (uint32_t)&aDST_Buffer, BUFFER_SIZE) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  while (1)
  {
    /* DMA transfer completed with incorrect data */
    if(transferFailedDetected == 1 && transferCompleteDetected == 1 )
    {
      while(1)
      {
        BSP_LED_Toggle(LED_GREEN);
        HAL_Delay(500);
      }
    }

    /* DMA transfer completed with correct data */
    if(transferFailedDetected == 0 && transferCompleteDetected == 1 )
    {
      BSP_LED_On(LED_GREEN);
      while(1)
      {
      }
    }

    /* DMA transfer error */
    if(transferErrorDetected == 1 )
    {
      BSP_LED_On(LED_GREEN);
      while(1)
      {
        BSP_LED_Toggle(LED_GREEN);
        HAL_Delay(500);
      }
    }
  }
}

/**
  * @brief  DMA configuration function
  * @param  None
  * @retval None
  */
static void APP_DmaConfig(void)
{
  __HAL_RCC_DMA_CLK_ENABLE();                               /* Enable DMA clock */

  DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;          /* Memory-to-memory mode */
  DmaHandle.Init.PeriphInc = DMA_PINC_ENABLE;               /* Peripheral address increment mode enabled */
  DmaHandle.Init.MemInc = DMA_MINC_ENABLE;                  /* Memory address increment mode enabled */
  DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD; /* Peripheral data width is 32 bits */
  DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;    /* Memory data width is 32 bits */
  DmaHandle.Init.Mode = DMA_NORMAL;                         /* DMA circular mode disabled */
  DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;              /* Channel priority set to high */

  DmaHandle.Instance = DMA1_Channel1;                       /* Select DMA channel 1 */
  /* DMA initialization */
  if (HAL_DMA_Init(&DmaHandle) != HAL_OK)                   
  {
    APP_ErrorHandler();
  }

  /* Register callback functions to be called after error or successful transfer */
  HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_CPLT_CB_ID, APP_TransferComplete);
  HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_ERROR_CB_ID, APP_TransferError);
  /* Enable DMA1_Channel1 interrupt */
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

/**
  * @brief  DMA transfer complete function
  * @param  DmaHandle：DMA handle
  * @retval None
  */
static void APP_TransferComplete(DMA_HandleTypeDef *DmaHandle)
{
  for(uint16_t i=0 ; i<BUFFER_SIZE; i++)
  {
    if(aDST_Buffer[i] != aSRC_Const_Buffer[i])
    {
      transferFailedDetected=1;
      break;
    }
  }
  transferCompleteDetected=1;
}

/**
  * @brief  DMA transfer error function
  * @param  DmaHandle：DMA handle
  * @retval None
  */
static void APP_TransferError(DMA_HandleTypeDef *DmaHandle)
{
  transferErrorDetected = 1;
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
