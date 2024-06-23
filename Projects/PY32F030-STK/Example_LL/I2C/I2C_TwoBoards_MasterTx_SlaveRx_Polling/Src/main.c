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
/* I2C SPEEDCLOCK defined as maximum value: Fast mode (400kHz) */
#define I2C_SPEEDCLOCK           400000
#define I2C_DUTYCYCLE            LL_I2C_DUTYCYCLE_2

/* Private variables ---------------------------------------------------------*/
const uint8_t aLedOn[]           = "LED ON";
#ifdef SLAVE_BOARD
uint8_t      aReceiveBuffer[0xF] = {0};
uint8_t ubReceiveIndex      = 0;
#else /* MASTER_BOARD */
uint8_t  ubNbDataToTransmit = sizeof(aLedOn);
uint8_t*      pTransmitBuffer    = (uint8_t*)aLedOn;
#endif /* SLAVE_BOARD */

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
#ifdef SLAVE_BOARD
static void     APP_ConfigI2cSlave(void);
static void     APP_ActivateI2cSlave(void);
static void     APP_HandleI2cSlave(void);
static uint8_t  APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength);
#else /* MASTER_BOARD */
static void     APP_ConfigI2cMaster(void);
static void     APP_ActivateI2cMaster(void);
static void     APP_HandleI2cMaster(void);
#endif /* SLAVE_BOARD */

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

  /* Initialize button */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  #ifdef SLAVE_BOARD
  /* Configure I2C1 (I2C configuration and related GPIO initialization in slave mode) */
  APP_ConfigI2cSlave();

  /* Wait for the user to press the button to start the transfer */
  while(BSP_PB_GetState(BUTTON_KEY) == 1)
  {}

  /* Enable I2C1 peripheral (slave) */
  APP_ActivateI2cSlave();

  /* Handle I2C1 events (slave) */
  APP_HandleI2cSlave();
#else /* MASTER_BOARD */
  /* Configure I2C1 (I2C configuration and related GPIO initialization in master mode) */
  APP_ConfigI2cMaster();

  /* Wait for the user to press the button to start the transfer */
  while(BSP_PB_GetState(BUTTON_KEY) == 1)
  {}

  /* Enable I2C1 peripheral (master) */
  APP_ActivateI2cMaster();

  /* Handle I2C1 events (master) */
  APP_HandleI2cMaster();
#endif /* SLAVE_BOARD */

  while (1)
  {
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

#ifdef SLAVE_BOARD
/**
  * @brief  Configure I2C1 in slave mode
  * @param  None
  * @retval None
  */
static void APP_ConfigI2cSlave(void)
{
  /* (1) Enable GPIO clock ************************/

  /* Enable GPIOA peripheral clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* (2) Enable I2C1 peripheral clock *************************************/

  /* Enable I2C1 peripheral clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

  /* Configure SCL pin: Alternative function, High speed, Open-drain, Pull-up */
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Configure SDA pin: Alternative function, High speed, Open-drain, Pull-up */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* (3) Configure I2C1 functional parameters***********************/
  
  /* Disable I2C1 before modifying configuration registers */
  LL_I2C_Disable(I2C1);
  
  /* Configure slave address:
    * - OwnAddress1 is SLAVE_OWN_ADDRESS
    */
  LL_I2C_SetOwnAddress1(I2C1, SLAVE_OWN_ADDRESS, 0);

  /* Enable clock stretching */
  /* Reset value is clock stretching enabled */
  /* LL_I2C_EnableClockStretching(I2C1); */
  
  /* Enable general call */
  /* Reset value is general call disabled */
  /* LL_I2C_EnableGeneralCall(I2C1); */
}

/**
  * @brief  Enable I2C1 (slave)
  * @param  None
  * @retval None
  */
static void APP_ActivateI2cSlave(void)
{
  LL_I2C_Enable(I2C1);
}

#else /* MASTER_BOARD */

/**
  * @brief  Configure I2C1 in master mode
  * @param  None
  * @retval None
  */
static void APP_ConfigI2cMaster(void)
{
  LL_RCC_ClocksTypeDef rcc_clocks = {0};

  /* (1) Enable GPIO clock ************************/

  /* Enable GPIOA peripheral clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* (2) Enable I2C1 peripheral clock *************************************/

  /* Enable I2C1 peripheral clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

  /* Configure SCL pin: Alternative function, High speed, Open-drain, Pull-up */
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Configure SDA pin: Alternative function, High speed, Open-drain, Pull-up */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* (3) Configure I2C1 functional parameters********************************/
  
  /* Disable I2C1 before modifying configuration registers */
  LL_I2C_Disable(I2C1);
  
  /* Get system clock frequency */
  LL_RCC_GetSystemClocksFreq(&rcc_clocks);

  /* Configure SCL clock speed */
  LL_I2C_ConfigSpeed(I2C1, rcc_clocks.PCLK1_Frequency, I2C_SPEEDCLOCK, I2C_DUTYCYCLE);

  /* Enable clock stretching */
  /* Reset value is clock stretching enabled */
  /* LL_I2C_EnableClockStretching(I2C1); */

  
  /* Enable general call */
  /* Reset value is general call disabled */
  /* LL_I2C_EnableGeneralCall(I2C1); */
}

/**
  * @brief  Enable I2C1 (Master)
  * @param  None
  * @retval None
  */
static void APP_ActivateI2cMaster(void)
{
  LL_I2C_Enable(I2C1);
}
#endif /* SLAVE_BOARD */

#ifdef SLAVE_BOARD
/**
  * @brief  Slave handling function
  * @param  None
  * @retval None
  */
static void APP_HandleI2cSlave(void)
{
  /* (1) Prepare for ACK on slave address reception ************************/
  LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);

  /* (2) Wait for ADDR flag and check address match and direction ************/
  while(!LL_I2C_IsActiveFlag_ADDR(I2C1))
  {
  }

  /* Verify transfer direction, when Read direction, slave enters receiver mode */
  if(LL_I2C_GetTransferDirection(I2C1) == LL_I2C_DIRECTION_READ)
  {
    /* Clear ADDR flag value in ISR register */
    LL_I2C_ClearFlag_ADDR(I2C1);
  }
  else
  {
    /* Clear ADDR flag value in ISR register */
    LL_I2C_ClearFlag_ADDR(I2C1);

    /* Call error function */
    APP_ErrorHandler();
  }

  /* (3) Loop until end of transfer received (STOP flag occurrence) ***************/

  /* Loop until STOP flag is set */
  while(!LL_I2C_IsActiveFlag_STOP(I2C1))
  {
    /* (3.1) Receive data (RXNE flag set) **********************************/

    /* Check RXNE flag value in ISR register */
    if(LL_I2C_IsActiveFlag_RXNE(I2C1))
    {
      /* Read character from Receive Data register.
       RXNE flag is cleared by reading data from DR register */
      aReceiveBuffer[ubReceiveIndex++] = LL_I2C_ReceiveData8(I2C1);
    }

    /* (3.2) Receive data (BTF flag set) ***********************************/
    /* Check BTF flag value in ISR register */
    if(LL_I2C_IsActiveFlag_BTF(I2C1))
    {
      /* Read character from Receive Data register.
       BTF flag is cleared by reading data from DR register */
      aReceiveBuffer[ubReceiveIndex++] = LL_I2C_ReceiveData8(I2C1);
    }
  }

  /* (4) Clear pending flags, check data consistency **************************/
  LL_I2C_ClearFlag_STOP(I2C1);

  /* Check if data requests turning on LED */
  if(APP_Buffercmp8((uint8_t*)aReceiveBuffer, (uint8_t*)aLedOn, (ubReceiveIndex-1)) == 0)
  {
    /* Turn on LED:
      * - Expected bytes have been received
      * - Slave Rx sequence successfully completed
      */
      BSP_LED_On(LED_GREEN);
  }
  else
  {
    /* Call error function */
    APP_ErrorHandler();
  }
}

/**
  * @brief  Character comparison function
  * @param  pBuffer1：buffer containing characters to be compared
  * @param  pBuffer2：buffer containing characters to be compared
  * @param  BufferLength：length of the character to be compared
  * @retval 0: characters match completely; 1: characters do not match completely;
  */
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}

#else /* MASTER_BOARD */

/**
  * @brief  Master handling function
  * @param  None
  * @retval None
  */
static void APP_HandleI2cMaster(void)
{
  /* (1) Enable Acknowledge of Master data reception ************************/
  LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
  
  /* (2) Start condition generation towards slave device ***********************/
   /* Master generates Start condition */
  LL_I2C_GenerateStartCondition(I2C1);

  /* (3) Loop until start is sent (SB flag set) ********************/
  while(!LL_I2C_IsActiveFlag_SB(I2C1))
  {
  }

  /* (4) Send slave address with 7-bit slave address + direction bit */
    LL_I2C_TransmitData8(I2C1, SLAVE_OWN_ADDRESS | I2C_REQUEST_WRITE);

  /* (5) Loop until address is acknowledged (ADDR flag set)*******/
  /* Loop until ADDR flag is set */
  while(!LL_I2C_IsActiveFlag_ADDR(I2C1))
  {
  }

  /* (6) Clear ADDR flag and loop until end of transfer (ubNbDataToTransmit == 0) */
  /* Clear ADDR flag value in ISR register */
  LL_I2C_ClearFlag_ADDR(I2C1);

  /* Loop until TXE flag is set */
  while(ubNbDataToTransmit > 0)
  {
    /* (6.1) Send data (TXE flag set) **********************************/

    /* Check TXE flag value in ISR register */
    if(LL_I2C_IsActiveFlag_TXE(I2C1))
    {
      /* Write data into Transmit Data register.
       TXE flag is cleared by writing data into DR register */
      LL_I2C_TransmitData8(I2C1, (*pTransmitBuffer++));

      ubNbDataToTransmit--;
    }
  }

  /* (7) End of transmission, data consistency checking on slave side *****/ 
  /* Generate Stop condition */
  LL_I2C_GenerateStopCondition(I2C1);

  /* Turn on LED:
    * - Expected bytes have been sent
    * - Master Tx sequence successfully completed
    */
  BSP_LED_On(LED_GREEN);
}
#endif /* SLAVE_BOARD */

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
