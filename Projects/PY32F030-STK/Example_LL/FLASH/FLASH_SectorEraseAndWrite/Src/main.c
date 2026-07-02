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
#define FLASH_USER_START_ADDR     0x08004000

/* Private variables ---------------------------------------------------------*/
const uint32_t DATA[64] =
{
  0x01010101, 0x23456789, 0x3456789A, 0x456789AB, 0x56789ABC, 0x6789ABCD, 0x789ABCDE, 0x89ABCDEF,
  0x9ABCDEF0, 0xABCDEF01, 0xBCDEF012, 0xCDEF0123, 0xDEF01234, 0xEF012345, 0xF0123456, 0x01234567,
  0x01010101, 0x23456789, 0x3456789A, 0x456789AB, 0x56789ABC, 0x6789ABCD, 0x789ABCDE, 0x89ABCDEF,
  0x9ABCDEF0, 0xABCDEF01, 0xBCDEF012, 0xCDEF0123, 0xDEF01234, 0xEF012345, 0xF0123456, 0x01234567,
  0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA,
  0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA,
  0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA,
  0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA,
};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_FlashErase(void);
static void APP_FlashProgram(void);
static void APP_FlashBlank(void);
static void APP_FlashVerify(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Initialize clock, configure system clock as HSI */
  APP_SystemClockConfig();
  
  /* Enable SYSCFG and PWR clocks */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize button */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /* Wait for the button to be pressed, to prevent erasing FLASH on every power-up */
  while (BSP_PB_GetState(BUTTON_USER))
  {
  }

  /* Unlock FLASH */
  LL_FLASH_Unlock(FLASH);

  LL_FLASH_TIMMING_SEQUENCE_CONFIG_24M();

  /* Erase FLASH */
  APP_FlashErase();

  /* Check if FLASH is blank */
  APP_FlashBlank();

  /* Program FLASH */
  APP_FlashProgram();

  /* Lock FLASH */
  LL_FLASH_Lock(FLASH);

  /* Verify FLASH */
  APP_FlashVerify();
  
  BSP_LED_On(LED_GREEN);

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
  /*  Set FLASH Latency Before modifying the HSI */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  /* SET HSI to 24MHz */
  LL_RCC_HSI_SetCalibFreq(LL_RCC_HSICALIBRATION_24MHz);
  /* Enable HSI */
  LL_RCC_HSI_Enable();
  while (LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Configure HSISYS as system clock and initialize it */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* Set APB1 prescaler and initialize it */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(24000000);

  /* Update system clock global variable SystemCoreClock (can also be updated by calling SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(24000000);
}

/**
  * @brief  FLASH erase function
  * @param  None
  * @retval None
  */
static void APP_FlashErase(void)
{
  /* Wait Busy=0 */
  while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);

  /* Enable EOP */
  LL_FLASH_EnableIT_EOP(FLASH);

  /* Enable Sector Erase */
  LL_FLASH_EnableSectorErase(FLASH);

  /* Set Erase Address */
  LL_FLASH_SetEraseAddress(FLASH,FLASH_USER_START_ADDR);

  /* Wait Busy=0 */
  while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);

  /* Wait EOP=1 */
  while(LL_FLASH_IsActiveFlag_EOP(FLASH)==0);

  /* Clear EOP */
  LL_FLASH_ClearFlag_EOP(FLASH);

  /* Disable EOP */
  LL_FLASH_DisableIT_EOP(FLASH);

  /* Disable Sector Erase */
  LL_FLASH_DisableSectorErase(FLASH);
}

/**
  * @brief  FLASH programming function
  * @param  None
  * @retval None
  */
static void APP_FlashProgram(void)
{
  uint32_t flash_program_start = FLASH_USER_START_ADDR ;                                /* Start address of user write flash */
  uint32_t flash_program_end = (FLASH_USER_START_ADDR + sizeof(DATA));                  /* End address of user write flash */
  uint32_t *src = (uint32_t *)DATA;                                                     /* Pointer to array */

  while (flash_program_start < flash_program_end)
  {
    /* Wait Busy=0 */
    while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);
    
    /* Enable EOP */
    LL_FLASH_EnableIT_EOP(FLASH);

    /* Enable Program */
    LL_FLASH_EnablePageProgram(FLASH);

    /* Page Program */
    LL_FLASH_PageProgram(FLASH,flash_program_start,src);
    
    /* Wait Busy=0 */
    while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);
    
    /* Wait EOP=1 */
    while(LL_FLASH_IsActiveFlag_EOP(FLASH)==0);
    
    /* Clear EOP */
    LL_FLASH_ClearFlag_EOP(FLASH);
   
    /* Disable EOP */
    LL_FLASH_DisableIT_EOP(FLASH);

    /* Disable Program */
    LL_FLASH_DisablePageProgram(FLASH);
    flash_program_start += FLASH_PAGE_SIZE;                                           /* Point to the start address of the next page to be written */
    src += FLASH_PAGE_SIZE / 4;                                                       /* Point to the next data to be written */
  }
}

/**
  * @brief  FLASH blank check function
  * @param  None
  * @retval None
  */
static void APP_FlashBlank(void)
{
  uint32_t addr = 0;

  while (addr < sizeof(DATA))
  {
    if (0xFFFFFFFF != HW32_REG(FLASH_USER_START_ADDR + addr))
    {
      APP_ErrorHandler();
    }
    addr += 4;
  }
}

/**
  * @brief  FLASH verification function
  * @param  None
  * @retval None
  */
static void APP_FlashVerify(void)
{
  uint32_t addr = 0;

  while (addr < sizeof(DATA))
  {
    if (DATA[addr / 4] != HW32_REG(FLASH_USER_START_ADDR + addr))
    {
      APP_ErrorHandler();
    }
    addr += 4;
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  while (1);
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
