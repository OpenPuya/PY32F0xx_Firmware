/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
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
#define FLASH_USER_START_ADDR     0x08002000
/* Private variables ---------------------------------------------------------*/
typedef struct
{
  uint32_t arrA[64];
} NewDataType;                                                      /* Structure Definition */
#define VarA (*(volatile NewDataType *)FLASH_USER_START_ADDR)       /* Flash memory address definition */
uint32_t dat2[10];

uint32_t DATA[64] = {0x01010101, 0x23456789, 0x3456789A, 0x456789AB, 0x56789ABC, 0x6789ABCD, 0x789ABCDE, 0x89ABCDEF,
                     0x9ABCDEF0, 0xABCDEF01, 0xBCDEF012, 0xCDEF0123, 0xDEF01234, 0xEF012345, 0xF0123456, 0x01234567,
                     0x01010101, 0x23456789, 0x3456789A, 0x456789AB, 0x56789ABC, 0x6789ABCD, 0x789ABCDE, 0x89ABCDEF,
                     0x9ABCDEF0, 0xABCDEF01, 0xBCDEF012, 0xCDEF0123, 0xDEF01234, 0xEF012345, 0xF0123456, 0x01234567,
                     0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa,
                     0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa,
                     0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa,
                     0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa,
                    };

/* Private function prototypes -----------------------------------------------*/
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
  /*Reset of all peripherals, Initializes the Systick*/
  HAL_Init();

  /*Initialize button*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /*Wait for button press*/
  while (BSP_PB_GetState(BUTTON_USER));

  /*Initialize LED*/
  BSP_LED_Init(LED_GREEN);

  /*Configure system clock*/
  APP_SystemClockConfig();

  /*Unlock FLASH*/
  HAL_FLASH_Unlock();

  /*Erase FLASH*/
  APP_FlashErase();

  /*Check if FLASH is blank*/
  APP_FlashBlank();

  /*program FLASH*/
  APP_FlashProgram();

  /*Lock FLASH*/
  HAL_FLASH_Lock();

  /*Verify FLASH*/
  APP_FlashVerify();
  
  BSP_LED_On(LED_GREEN);

  while (1)
  {

  }
}

/**
  * @brief  System clock configuration
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Oscillator Configuration */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI; /* Selective Oscillator HSE,HSI,LSI */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                                       /* Enable HSI */
#if defined(RCC_HSIDIV_SUPPORT)
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                                       /* HSI not divided */
#endif
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz;                               /* Configure HSI output clock as 8MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                                                      /* Disable HSE */
  /*RCC_OscInitStruct.HSEFreq = RCC_HSE_16_24MHz;*/
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                                                      /* Disable LSI */
                         
  /* Initialize RCC oscillators */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Clock Source Configuration */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* RCC system clock types */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSISYS;                                         /* SYSCLK source is HSISYS */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                             /* AHB clock not divided */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                                              /* APB clock not divided */
  /* Initialize RCC system clock */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  Erase FLASH
  * @param  None
  * @retval None
  */
static void APP_FlashErase(void)
{
  uint32_t PAGEError = 0;
  FLASH_EraseInitTypeDef EraseInitStruct = {0};

  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGEERASE;                                     /* Erase type: FLASH_TYPEERASE_PAGEERASE = Page erase, FLASH_TYPEERASE_SECTORERASE = Sector erase */
  EraseInitStruct.PageAddress = FLASH_USER_START_ADDR;                                         /* Starting address for erase */
  EraseInitStruct.NbPages  = sizeof(DATA) / FLASH_PAGE_SIZE;                                   /* Number of pages to be erased */
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)                               /* Perform page erase, PAGEError returns the page with erase error, returns 0xFFFFFFFF for successful erase */
  {
    APP_ErrorHandler();
  }
}
/**
  * @brief  program FLASH
  * @param  None
  * @retval None
  */
static void APP_FlashProgram(void)
{
  uint32_t flash_program_start = FLASH_USER_START_ADDR ;                                /* Start address for flash program */
  uint32_t flash_program_end = (FLASH_USER_START_ADDR + sizeof(DATA));                  /* End address for flash program */
  uint32_t *src = (uint32_t *)DATA;                                                     /* Pointer to the array */

  while (flash_program_start < flash_program_end)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, flash_program_start, src) == HAL_OK)  /* Execute Program */
    {
      flash_program_start += FLASH_PAGE_SIZE;                                           /* Set flash start pointer to the first page */
      src += FLASH_PAGE_SIZE / 4;                                                       /* Update the data pointer */
    }
  }
}
/**
  * @brief  Check if FLASH is blank
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
  * @brief  Verify FLASH
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
