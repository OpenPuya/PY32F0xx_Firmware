/**
  ******************************************************************************
  * @file    py32f072_ll_system.h
  * @author  MCU Application Team
  * @brief   Header file of SYSTEM LL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PY32F072_LL_SYSTEM_H
#define PY32F072_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx.h"

/** @addtogroup PY32F072_LL_Driver
  * @{
  */

#if defined (FLASH) || defined (SYSCFG) || defined (DBGMCU)

/** @defgroup SYSTEM_LL SYSTEM
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Private_Constants SYSTEM Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Constants SYSTEM Exported Constants
  * @{
  */

/** @defgroup SYSTEM_LL_EC_REMAP SYSCFG REMAP
  * @{
  */
#define LL_SYSCFG_REMAP_FLASH               0x00000000U                                           /*!< Main Flash memory mapped at 0x00000000 */
#define LL_SYSCFG_REMAP_SYSTEMFLASH         SYSCFG_CFGR1_MEM_MODE_0                               /*!< System Flash memory mapped at 0x00000000 */
#define LL_SYSCFG_REMAP_SRAM                (SYSCFG_CFGR1_MEM_MODE_1 | SYSCFG_CFGR1_MEM_MODE_0)   /*!< Embedded SRAM mapped at 0x00000000 */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TIMBREAK TIMER BREAK INPUT
  * @{
  */
#if defined(SYSCFG_CFGR2_LOCKUP_LOCK)
#define LL_SYSCFG_TIMBREAK_LOCKUP_TO_ALL      SYSCFG_CFGR2_LOCKUP_LOCK
#endif
#if defined(SYSCFG_CFGR2_PVD_LOCK)
#define LL_SYSCFG_TIMBREAK_PVD_TO_ALL         SYSCFG_CFGR2_PVD_LOCK
#endif
#if defined(SYSCFG_CFGR2_COMP1_BRK_TIM1)
#define LL_SYSCFG_TIMBREAK_COMP1_TO_TIM1      SYSCFG_CFGR2_COMP1_BRK_TIM1
#endif
#if defined(SYSCFG_CFGR2_COMP2_BRK_TIM1)
#define LL_SYSCFG_TIMBREAK_COMP2_TO_TIM1      SYSCFG_CFGR2_COMP2_BRK_TIM1
#endif
#if defined(SYSCFG_CFGR2_COMP3_BRK_TIM1)
#define LL_SYSCFG_TIMBREAK_COMP3_TO_TIM1      SYSCFG_CFGR2_COMP3_BRK_TIM1
#endif

#if defined(SYSCFG_CFGR2_COMP1_BRK_TIM15)
#define LL_SYSCFG_TIMBREAK_COMP1_TO_TIM15     SYSCFG_CFGR2_COMP1_BRK_TIM15
#endif
#if defined(SYSCFG_CFGR2_COMP2_BRK_TIM15)
#define LL_SYSCFG_TIMBREAK_COMP2_TO_TIM15     SYSCFG_CFGR2_COMP2_BRK_TIM15
#endif
#if defined(SYSCFG_CFGR2_COMP3_BRK_TIM15)
#define LL_SYSCFG_TIMBREAK_COMP3_TO_TIM15     SYSCFG_CFGR2_COMP3_BRK_TIM15
#endif

#if defined(SYSCFG_CFGR2_COMP1_BRK_TIM16)
#define LL_SYSCFG_TIMBREAK_COMP1_TO_TIM16     SYSCFG_CFGR2_COMP1_BRK_TIM16
#endif
#if defined(SYSCFG_CFGR2_COMP2_BRK_TIM16)
#define LL_SYSCFG_TIMBREAK_COMP2_TO_TIM16     SYSCFG_CFGR2_COMP2_BRK_TIM16
#endif
#if defined(SYSCFG_CFGR2_COMP3_BRK_TIM16)
#define LL_SYSCFG_TIMBREAK_COMP3_TO_TIM16     SYSCFG_CFGR2_COMP3_BRK_TIM16
#endif

#if defined(SYSCFG_CFGR2_COMP1_BRK_TIM17)
#define LL_SYSCFG_TIMBREAK_COMP1_TO_TIM17     SYSCFG_CFGR2_COMP1_BRK_TIM17
#endif
#if defined(SYSCFG_CFGR2_COMP2_BRK_TIM17)
#define LL_SYSCFG_TIMBREAK_COMP2_TO_TIM17     SYSCFG_CFGR2_COMP2_BRK_TIM17
#endif
#if defined(SYSCFG_CFGR2_COMP3_BRK_TIM17)
#define LL_SYSCFG_TIMBREAK_COMP3_TO_TIM17     SYSCFG_CFGR2_COMP3_BRK_TIM17
#endif
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_ETR_SRC_TIM1 TIM1 ETR SOURCE
  * @{
  */
#define LL_SYSCFG_ETR_SRC_TIM1_GPIO          0x00000000U
#if defined(COMP1)
#define LL_SYSCFG_ETR_SRC_TIM1_COMP1         SYSCFG_CFGR1_ETR_SRC_TIM1_0
#endif
#if defined(COMP2)
#define LL_SYSCFG_ETR_SRC_TIM1_COMP2         SYSCFG_CFGR1_ETR_SRC_TIM1_1
#endif
#define LL_SYSCFG_ETR_SRC_TIM1_ADC           (SYSCFG_CFGR1_ETR_SRC_TIM1_1 | SYSCFG_CFGR1_ETR_SRC_TIM1_0)
#if defined(COMP3)
#define LL_SYSCFG_ETR_SRC_TIM1_COMP3         SYSCFG_CFGR1_ETR_SRC_TIM1_2
#endif
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_ETR_SRC_TIM2 TIM2 ETR SOURCE
  * @{
  */
#define LL_SYSCFG_ETR_SRC_TIM2_GPIO          0x00000000U
#if defined(COMP1)
#define LL_SYSCFG_ETR_SRC_TIM2_COMP1         SYSCFG_CFGR1_ETR_SRC_TIM2_0
#endif
#if defined(COMP2)
#define LL_SYSCFG_ETR_SRC_TIM2_COMP2         SYSCFG_CFGR1_ETR_SRC_TIM2_1
#endif
#define LL_SYSCFG_ETR_SRC_TIM2_ADC           (SYSCFG_CFGR1_ETR_SRC_TIM2_1 | SYSCFG_CFGR1_ETR_SRC_TIM2_0)
#if defined(COMP3)
#define LL_SYSCFG_ETR_SRC_TIM2_COMP3         SYSCFG_CFGR1_ETR_SRC_TIM2_2
#endif
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_ETR_SRC_TIM3 TIM3 ETR SOURCE
  * @{
  */
#define LL_SYSCFG_ETR_SRC_TIM3_GPIO          0x00000000U
#if defined(COMP1)
#define LL_SYSCFG_ETR_SRC_TIM3_COMP1         SYSCFG_CFGR1_ETR_SRC_TIM3_0
#endif
#if defined(COMP2)
#define LL_SYSCFG_ETR_SRC_TIM3_COMP2         SYSCFG_CFGR1_ETR_SRC_TIM3_1
#endif
#define LL_SYSCFG_ETR_SRC_TIM3_ADC           (SYSCFG_CFGR1_ETR_SRC_TIM3_1 | SYSCFG_CFGR1_ETR_SRC_TIM3_0)
#if defined(COMP3)
#define LL_SYSCFG_ETR_SRC_TIM3_COMP3         SYSCFG_CFGR1_ETR_SRC_TIM3_2
#endif
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TIM1_IC1_SRC TIM1 IC1 SOURCE
  * @{
  */
#define LL_SYSCFG_TIM1_IC1_SRC_IO            0x00000000U
#if defined(COMP1)
#define LL_SYSCFG_TIM1_IC1_SRC_COMP1         SYSCFG_CFGR1_TIM1_IC1_SRC_0
#endif
#if defined(COMP2)
#define LL_SYSCFG_TIM1_IC1_SRC_COMP2         SYSCFG_CFGR1_TIM1_IC1_SRC_1
#endif
#if defined(COMP3)
#define LL_SYSCFG_TIM1_IC1_SRC_COMP3         (SYSCFG_CFGR1_TIM1_IC1_SRC_1 | SYSCFG_CFGR1_TIM1_IC1_SRC_0)
#endif
/**
  * @}
  */


/** @defgroup SYSTEM_LL_EC_TIM2_IC4_SRC TIM2 IC4 SOURCE
  * @{
  */
#define LL_SYSCFG_TIM2_IC4_SRC_IO            0x00000000U
#if defined(COMP1)
#define LL_SYSCFG_TIM2_IC4_SRC_COMP1         SYSCFG_CFGR1_TIM2_IC4_SRC_0
#endif
#if defined(COMP2)
#define LL_SYSCFG_TIM2_IC4_SRC_COMP2         SYSCFG_CFGR1_TIM2_IC4_SRC_1
#endif
#if defined(COMP3)
#define LL_SYSCFG_TIM2_IC4_SRC_COMP3         (SYSCFG_CFGR1_TIM2_IC4_SRC_1 | SYSCFG_CFGR1_TIM2_IC4_SRC_0)
#endif
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TIM3_IC1_SRC TIM3 IC1 SOURCE
  * @{
  */
#define LL_SYSCFG_TIM3_IC1_SRC_IO            0x00000000U
#if defined(COMP1)
#define LL_SYSCFG_TIM3_IC1_SRC_COMP1         SYSCFG_CFGR1_TIM3_IC1_SRC_0
#endif
#if defined(COMP2)
#define LL_SYSCFG_TIM3_IC1_SRC_COMP2         SYSCFG_CFGR1_TIM3_IC1_SRC_1
#endif
#if defined(COMP3)
#define LL_SYSCFG_TIM3_IC1_SRC_COMP3         (SYSCFG_CFGR1_TIM3_IC1_SRC_1 | SYSCFG_CFGR1_TIM3_IC1_SRC_0)
#endif
/**
  * @}
  */

#if (defined(DMA) || defined(DMA1))
/** @defgroup SYSTEM_LL_EC_DMA_MAP DMA MAP
  * @{
  */
#define LL_SYSCFG_DMA_MAP_ADC1           (0x00000000U)
#define LL_SYSCFG_DMA_MAP_DAC1           (                                                                                                                                  SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_DAC2           (                                                                                                        SYSCFG_CFGR3_DMA1_MAP_1                          )
#define LL_SYSCFG_DMA_MAP_SPI1_RD        (                                                                                                        SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_SPI1_WR        (                                                                              SYSCFG_CFGR3_DMA1_MAP_2                                                    )
#define LL_SYSCFG_DMA_MAP_SPI2_RD        (                                                                              SYSCFG_CFGR3_DMA1_MAP_2                           | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_SPI2_WR        (                                                                              SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1                          )
#define LL_SYSCFG_DMA_MAP_USART1_RD      (                                                                              SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_USART1_WR      (                                                    SYSCFG_CFGR3_DMA1_MAP_3                                                                              )
#define LL_SYSCFG_DMA_MAP_USART2_RD      (                                                    SYSCFG_CFGR3_DMA1_MAP_3                                                     | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_USART2_WR      (                                                    SYSCFG_CFGR3_DMA1_MAP_3                           | SYSCFG_CFGR3_DMA1_MAP_1                          )
#define LL_SYSCFG_DMA_MAP_USART3_RD      (                                                    SYSCFG_CFGR3_DMA1_MAP_3                           | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_USART3_WR      (                                                    SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2                                                    )
#define LL_SYSCFG_DMA_MAP_USART4_RD      (                                                    SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2                           | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_USART4_WR      (                                                    SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1                          )
#define LL_SYSCFG_DMA_MAP_I2C1_RD        (                                                    SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_I2C1_WR        (                          SYSCFG_CFGR3_DMA1_MAP_4                                                                                                        )
#define LL_SYSCFG_DMA_MAP_I2C2_RD        (                          SYSCFG_CFGR3_DMA1_MAP_4                                                                               | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_I2C2_WR        (                          SYSCFG_CFGR3_DMA1_MAP_4                                                     | SYSCFG_CFGR3_DMA1_MAP_1                          )
#define LL_SYSCFG_DMA_MAP_TIM1_CH1       (                          SYSCFG_CFGR3_DMA1_MAP_4                                                     | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM1_CH2       (                          SYSCFG_CFGR3_DMA1_MAP_4                           | SYSCFG_CFGR3_DMA1_MAP_2                                                    )
#define LL_SYSCFG_DMA_MAP_TIM1_CH3       (                          SYSCFG_CFGR3_DMA1_MAP_4                           | SYSCFG_CFGR3_DMA1_MAP_2                           | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM1_CH4       (                          SYSCFG_CFGR3_DMA1_MAP_4                           | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1                          )
#define LL_SYSCFG_DMA_MAP_TIM1_COM       (                          SYSCFG_CFGR3_DMA1_MAP_4                           | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM1_TRG       (                          SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_3                                                                              )
#define LL_SYSCFG_DMA_MAP_TIM1_UP        (                          SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_3                                                     | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM2_CH1       (                          SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_3                           | SYSCFG_CFGR3_DMA1_MAP_1                          )
#define LL_SYSCFG_DMA_MAP_TIM2_CH2       (                          SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_3                           | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM2_CH3       (                          SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2                                                    )
#define LL_SYSCFG_DMA_MAP_TIM2_CH4       (                          SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2                           | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM2_UP        (                          SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1                          )
#define LL_SYSCFG_DMA_MAP_TIM2_TRG       (                          SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM3_CH1       (SYSCFG_CFGR3_DMA1_MAP_5                                                                                                                                  )
#define LL_SYSCFG_DMA_MAP_TIM3_CH2       (SYSCFG_CFGR3_DMA1_MAP_5                                                                                                         | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM3_CH3       (SYSCFG_CFGR3_DMA1_MAP_5                                                                               | SYSCFG_CFGR3_DMA1_MAP_1                          )
#define LL_SYSCFG_DMA_MAP_TIM3_CH4       (SYSCFG_CFGR3_DMA1_MAP_5                                                                               | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM3_UP        (SYSCFG_CFGR3_DMA1_MAP_5                                                     | SYSCFG_CFGR3_DMA1_MAP_2                                                    )
#define LL_SYSCFG_DMA_MAP_TIM3_TRG       (SYSCFG_CFGR3_DMA1_MAP_5                                                     | SYSCFG_CFGR3_DMA1_MAP_2                           | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM6_UP        (SYSCFG_CFGR3_DMA1_MAP_5                                                     | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1                          )
#define LL_SYSCFG_DMA_MAP_TIM7_UP        (SYSCFG_CFGR3_DMA1_MAP_5                                                     | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM15_CH1      (SYSCFG_CFGR3_DMA1_MAP_5                           | SYSCFG_CFGR3_DMA1_MAP_3                                                                              )
#define LL_SYSCFG_DMA_MAP_TIM15_CH2      (SYSCFG_CFGR3_DMA1_MAP_5                           | SYSCFG_CFGR3_DMA1_MAP_3                                                     | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM15_UP       (SYSCFG_CFGR3_DMA1_MAP_5                           | SYSCFG_CFGR3_DMA1_MAP_3                           | SYSCFG_CFGR3_DMA1_MAP_1                          )
#define LL_SYSCFG_DMA_MAP_TIM15_TRG      (SYSCFG_CFGR3_DMA1_MAP_5                           | SYSCFG_CFGR3_DMA1_MAP_3                           | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM15_COM      (SYSCFG_CFGR3_DMA1_MAP_5                           | SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2                                                    )
#define LL_SYSCFG_DMA_MAP_TIM16_CH1      (SYSCFG_CFGR3_DMA1_MAP_5                           | SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2                           | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM16_UP       (SYSCFG_CFGR3_DMA1_MAP_5                           | SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1                          )
#define LL_SYSCFG_DMA_MAP_TIM17_CH1      (SYSCFG_CFGR3_DMA1_MAP_5                           | SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM17_UP       (SYSCFG_CFGR3_DMA1_MAP_5 | SYSCFG_CFGR3_DMA1_MAP_4                                                                                                        )
#if defined(USBD)
#define LL_SYSCFG_DMA_MAP_USB            (SYSCFG_CFGR3_DMA1_MAP_5 | SYSCFG_CFGR3_DMA1_MAP_4                                                                               | SYSCFG_CFGR3_DMA1_MAP_0)
#endif /* USBD */
#define LL_SYSCFG_DMA_MAP_LCD            (SYSCFG_CFGR3_DMA1_MAP_5 | SYSCFG_CFGR3_DMA1_MAP_4                                                     | SYSCFG_CFGR3_DMA1_MAP_1                          )
#endif /* DMA Or DMA1 */
/**
  * @}
  */
  
/** @defgroup SYSTEM_LL_EC_GPIO_PORT GPIO PORT
  * @{
  */
#define LL_SYSCFG_GPIO_PORTA              0x00000000U
#define LL_SYSCFG_GPIO_PORTB              0x00000001U
#define LL_SYSCFG_GPIO_PORTC              0x00000002U
#define LL_SYSCFG_GPIO_PORTF              0x00000003U
/**
  * @}
  */
  
/** @defgroup SYSTEM_LL_EC_GPIO_PIN GPIO PIN
  * @{
  */
#define LL_SYSCFG_GPIO_PIN_0              0x00000001U
#define LL_SYSCFG_GPIO_PIN_1              0x00000002U
#define LL_SYSCFG_GPIO_PIN_2              0x00000004U
#define LL_SYSCFG_GPIO_PIN_3              0x00000008U
#define LL_SYSCFG_GPIO_PIN_4              0x00000010U
#define LL_SYSCFG_GPIO_PIN_5              0x00000020U
#define LL_SYSCFG_GPIO_PIN_6              0x00000040U
#define LL_SYSCFG_GPIO_PIN_7              0x00000080U
#define LL_SYSCFG_GPIO_PIN_8              0x00000100U
#define LL_SYSCFG_GPIO_PIN_9              0x00000200U
#define LL_SYSCFG_GPIO_PIN_10             0x00000400U
#define LL_SYSCFG_GPIO_PIN_11             0x00000800U
#define LL_SYSCFG_GPIO_PIN_12             0x00001000U
#define LL_SYSCFG_GPIO_PIN_13             0x00002000U
#define LL_SYSCFG_GPIO_PIN_14             0x00004000U
#define LL_SYSCFG_GPIO_PIN_15             0x00008000U
/**
  * @}
  */
  
/** @defgroup SYSTEM_LL_EC_LATENCY FLASH LATENCY
  * @{
  */
#define LL_FLASH_LATENCY_0                 0x00000000U               /*!< FLASH Zero Latency cycle */
#define LL_FLASH_LATENCY_1                 FLASH_ACR_LATENCY_0       /*!< FLASH One Latency cycle */
#define LL_FLASH_LATENCY_2                 FLASH_ACR_LATENCY_1       /*!< FLASH Two Latency cycle */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_GPIO_SEL GPIO SEL
  * @{
  */
#define LL_SYSCFG_GPIO_SEL_FASTIO          0x00000000U 
#define LL_SYSCFG_GPIO_SEL_AHB             SYSCFG_CFGR1_GPIO_AHB_SEL
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB1_GRP1_STOP_IP  DBGMCU APB1 GRP1 STOP IP
  * @{
  */
#if defined(DBGMCU_APB_FZ1_DBG_TIM2_STOP)
#define LL_DBGMCU_APB1_GRP1_TIM2_STOP      DBGMCU_APB_FZ1_DBG_TIM2_STOP        /*!< TIM2 counter stopped when core is halted */
#endif
#if defined(DBGMCU_APB_FZ1_DBG_TIM3_STOP)
#define LL_DBGMCU_APB1_GRP1_TIM3_STOP      DBGMCU_APB_FZ1_DBG_TIM3_STOP        /*!< TIM3 counter stopped when core is halted */
#endif
#if defined(DBGMCU_APB_FZ1_DBG_TIM6_STOP)
#define LL_DBGMCU_APB1_GRP1_TIM6_STOP      DBGMCU_APB_FZ1_DBG_TIM6_STOP        /*!< TIM6 counter stopped when core is halted */
#endif
#if defined(DBGMCU_APB_FZ1_DBG_TIM7_STOP)
#define LL_DBGMCU_APB1_GRP1_TIM7_STOP      DBGMCU_APB_FZ1_DBG_TIM7_STOP        /*!< TIM7 counter stopped when core is halted */
#endif
#if defined(DBGMCU_APB_FZ1_DBG_RTC_STOP)
#define LL_DBGMCU_APB1_GRP1_RTC_STOP       DBGMCU_APB_FZ1_DBG_RTC_STOP         /*!< RTC Calendar frozen when core is halted */
#endif
#if defined(DBGMCU_APB_FZ1_DBG_WWDG_STOP)
#define LL_DBGMCU_APB1_GRP1_WWDG_STOP      DBGMCU_APB_FZ1_DBG_WWDG_STOP        /*!< Debug Window Watchdog stopped when Core is halted */
#endif
#if defined(DBGMCU_APB_FZ1_DBG_IWDG_STOP)
#define LL_DBGMCU_APB1_GRP1_IWDG_STOP      DBGMCU_APB_FZ1_DBG_IWDG_STOP        /*!< Debug Independent Watchdog stopped when Core is halted */
#endif
#if defined(DBGMCU_APB_FZ1_DBG_CAN_STOP)
#define LL_DBGMCU_APB1_GRP1_CAN_STOP       DBGMCU_APB_FZ1_DBG_CAN_STOP          /*!< Debug CAN stopped when Core is halted */
#endif

#if defined(DBGMCU_APB_FZ1_DBG_I2C1_SMBUS_TIMEOUT)
#define LL_DBGMCU_APB1_GRP1_I2C1_SMBUS_TIMEOUT      DBGMCU_APB_FZ1_DBG_I2C1_SMBUS_TIMEOUT        /*!< Debug I2C1 SMBUS TIMEOUT stopped when Core is halted */
#endif

#if defined(DBGMCU_APB_FZ1_DBG_I2C2_SMBUS_TIMEOUT)
#define LL_DBGMCU_APB1_GRP1_I2C2_SMBUS_TIMEOUT      DBGMCU_APB_FZ1_DBG_I2C2_SMBUS_TIMEOUT        /*!< Debug I2C2 SMBUS TIMEOUT stopped when Core is halted */
#endif

#if defined(DBGMCU_APB_FZ1_DBG_LPTIM_STOP)
#define LL_DBGMCU_APB1_GRP1_LPTIM1_STOP    DBGMCU_APB_FZ1_DBG_LPTIM_STOP      /*!< LPTIM1 counter stopped when Core is halted */
#endif
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB2_GRP1_STOP_IP DBGMCU APB2 GRP1 STOP IP
  * @{
  */
#if defined(DBGMCU_APB_FZ2_DBG_TIM1_STOP)
#define LL_DBGMCU_APB1_GRP2_TIM1_STOP      DBGMCU_APB_FZ2_DBG_TIM1_STOP        /*!< TIM1 counter stopped when core is halted */
#endif
#if defined(DBGMCU_APB_FZ2_DBG_TIM14_STOP)
#define LL_DBGMCU_APB1_GRP2_TIM14_STOP     DBGMCU_APB_FZ2_DBG_TIM14_STOP       /*!< TIM14 counter stopped when core is halted */
#endif
#if defined(DBGMCU_APB_FZ2_DBG_TIM15_STOP)
#define LL_DBGMCU_APB1_GRP2_TIM15_STOP     DBGMCU_APB_FZ2_DBG_TIM15_STOP       /*!< TIM15 counter stopped when core is halted */
#endif
#if defined(DBGMCU_APB_FZ2_DBG_TIM16_STOP)
#define LL_DBGMCU_APB1_GRP2_TIM16_STOP     DBGMCU_APB_FZ2_DBG_TIM16_STOP       /*!< TIM16 counter stopped when core is halted */
#endif
#if defined(DBGMCU_APB_FZ2_DBG_TIM17_STOP)
#define LL_DBGMCU_APB1_GRP2_TIM17_STOP     DBGMCU_APB_FZ2_DBG_TIM17_STOP       /*!< TIM17 counter stopped when core is halted */
#endif
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Functions SYSTEM Exported Functions
  * @{
  */

/** @defgroup SYSTEM_LL_EF_SYSCFG SYSCFG
  * @{
  */
/**
  * @brief  Set FASTIO or AHB to access the GPIO register control
  * @rmtoll SYSCFG_CFGR1 GPIO_AHB_SEL      LL_SYSCFG_SetGPIOAccess
  * @param  GPIOSel This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_SEL_FASTIO
  *         @arg @ref LL_SYSCFG_GPIO_SEL_AHB
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetGPIOAccess(uint32_t GPIOSel)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_GPIO_AHB_SEL, GPIOSel);
}

/**
  * @brief  Get FASTIO or AHB to access the GPIO register control
  * @rmtoll SYSCFG_CFGR1 GPIO_AHB_SEL      LL_SYSCFG_GetGPIOAccess
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_SEL_FASTIO
  *         @arg @ref LL_SYSCFG_GPIO_SEL_AHB
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetGPIOAccess(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_GPIO_AHB_SEL));
}  

/**
  * @brief  Set memory mapping at address 0x00000000
  * @rmtoll SYSCFG_CFGR1 MEM_MODE      LL_SYSCFG_SetRemapMemory
  * @param  Memory This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetRemapMemory(uint32_t Memory)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE, Memory);
}

/**
  * @brief  Get memory mapping at address 0x00000000
  * @rmtoll SYSCFG_CFGR1 MEM_MODE      LL_SYSCFG_GetRemapMemory
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetRemapMemory(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE));
}

/**
  * @brief  Enables COMPx as TIMx break input
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  TIMBreakInputs This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP3_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM15
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM15
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP3_TO_TIM15
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP3_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM17
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM17
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP3_TO_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableTIMBreakInputs(uint32_t TIMBreakInputs)
{
  SET_BIT(SYSCFG->CFGR2, TIMBreakInputs);
}

/**
  * @brief  Disables COMPx as TIMx break input
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  TIMBreakInputs This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP3_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM15
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM15
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP3_TO_TIM15
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP3_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM17
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM17
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP3_TO_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableTIMBreakInputs(uint32_t TIMBreakInputs)
{
  CLEAR_BIT(SYSCFG->CFGR2, TIMBreakInputs);
}

/**
  * @brief  Indicate if COMPx as TIMx break input
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  TIMBreakInputs This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP3_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM15
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM15
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP3_TO_TIM15
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP3_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM17
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM17
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP3_TO_TIM17
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledTIMBreakInputs(uint32_t TIMBreakInputs)
{
  return ((READ_BIT(SYSCFG->CFGR2, TIMBreakInputs) == (TIMBreakInputs)) ? 1UL : 0UL);
}

/**
  * @brief  Set the TIMER1 ETR input source
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_GPIO
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_COMP1
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_COMP2
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_COMP3
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_ADC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetTIM1ETRSource(uint32_t source)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_ETR_SRC_TIM1, source);
}

/**
  * @brief  Get the TIMER1 ETR input source
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_GPIO
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_COMP1
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_COMP2
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_COMP3
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_ADC
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetTIM1ETRSource(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_ETR_SRC_TIM1));
}

/**
  * @brief  Set the TIMER2 ETR input source
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM2_GPIO
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM2_COMP1
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM2_COMP2
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM2_COMP3
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM2_ADC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetTIM2ETRSource(uint32_t source)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_ETR_SRC_TIM2, source);
}

/**
  * @brief  Get the TIMER2 ETR input source
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM2_GPIO
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM2_COMP1
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM2_COMP2
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM2_COMP3
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM2_ADC
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetTIM2ETRSource(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_ETR_SRC_TIM2));
}

/**
  * @brief  Set the TIMER3 ETR input source
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM3_GPIO
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM3_COMP1
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM3_COMP2
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM3_COMP3
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM3_ADC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetTIM3ETRSource(uint32_t source)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_ETR_SRC_TIM3, source);
}

/**
  * @brief  Get the TIMER3 ETR input source
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM3_GPIO
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM3_COMP1
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM3_COMP2
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM3_COMP3
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM3_ADC
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetTIM3ETRSource(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_ETR_SRC_TIM3));
}

/**
  * @brief  Set the TIMER1 IC1 source
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_TIM1_IC1_SRC_IO
  *         @arg @ref LL_SYSCFG_TIM1_IC1_SRC_COMP1
  *         @arg @ref LL_SYSCFG_TIM1_IC1_SRC_COMP2
  *         @arg @ref LL_SYSCFG_TIM1_IC1_SRC_COMP3
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetTIM1IC1Source(uint32_t source)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_TIM1_IC1_SRC, source);
}

/**
  * @brief  Get the TIMER1 IC1 source
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_TIM1_IC1_SRC_IO
  *         @arg @ref LL_SYSCFG_TIM1_IC1_SRC_COMP1
  *         @arg @ref LL_SYSCFG_TIM1_IC1_SRC_COMP2
  *         @arg @ref LL_SYSCFG_TIM1_IC1_SRC_COMP3
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetTIM1IC1Source(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_TIM1_IC1_SRC));
}

/**
  * @brief  Set the TIMER2 IC4 source
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_TIM2_IC4_SRC_IO
  *         @arg @ref LL_SYSCFG_TIM2_IC4_SRC_COMP1
  *         @arg @ref LL_SYSCFG_TIM2_IC4_SRC_COMP2
  *         @arg @ref LL_SYSCFG_TIM2_IC4_SRC_COMP3
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetTIM2IC4Source(uint32_t source)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_TIM2_IC4_SRC, source);
}

/**
  * @brief  Get the TIMER2 IC4 source
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_TIM2_IC4_SRC_IO
  *         @arg @ref LL_SYSCFG_TIM2_IC4_SRC_COMP1
  *         @arg @ref LL_SYSCFG_TIM2_IC4_SRC_COMP2
  *         @arg @ref LL_SYSCFG_TIM2_IC4_SRC_COMP3
  * @retval None
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetTIM2IC4Source(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_TIM2_IC4_SRC));
}

/**
  * @brief  Set the TIMER3 IC1  source
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_TIM3_IC1_SRC_IO
  *         @arg @ref LL_SYSCFG_TIM3_IC1_SRC_COMP1
  *         @arg @ref LL_SYSCFG_TIM3_IC1_SRC_COMP2
  *         @arg @ref LL_SYSCFG_TIM3_IC1_SRC_COMP3
  */
__STATIC_INLINE void LL_SYSCFG_SetTIM3IC1Source(uint32_t source)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_TIM3_IC1_SRC, source);
}

/**
  * @brief  Get the TIMER3 IC1 source
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_TIM3_IC1_SRC_IO
  *         @arg @ref LL_SYSCFG_TIM3_IC1_SRC_COMP1
  *         @arg @ref LL_SYSCFG_TIM3_IC1_SRC_COMP2
  *         @arg @ref LL_SYSCFG_TIM3_IC1_SRC_COMP3
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetTIM3IC1Source(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_TIM3_IC1_SRC));
}

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_GPIO_ENS GPIO Filter Control
  * @{
  */
/**
  * @brief  Enable GPIO Filter
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  GPIOPort This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PORTA
  *         @arg @ref LL_SYSCFG_GPIO_PORTB
  *         @arg @ref LL_SYSCFG_GPIO_PORTC
  *         @arg @ref LL_SYSCFG_GPIO_PORTF
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PIN_0
  *         @arg @ref LL_SYSCFG_GPIO_PIN_1
  *         @arg @ref LL_SYSCFG_GPIO_PIN_2
  *         @arg @ref LL_SYSCFG_GPIO_PIN_3
  *         @arg @ref LL_SYSCFG_GPIO_PIN_4
  *         @arg @ref LL_SYSCFG_GPIO_PIN_5
  *         @arg @ref LL_SYSCFG_GPIO_PIN_6
  *         @arg @ref LL_SYSCFG_GPIO_PIN_7
  *         @arg @ref LL_SYSCFG_GPIO_PIN_8
  *         @arg @ref LL_SYSCFG_GPIO_PIN_9
  *         @arg @ref LL_SYSCFG_GPIO_PIN_10
  *         @arg @ref LL_SYSCFG_GPIO_PIN_11
  *         @arg @ref LL_SYSCFG_GPIO_PIN_12
  *         @arg @ref LL_SYSCFG_GPIO_PIN_13
  *         @arg @ref LL_SYSCFG_GPIO_PIN_14
  *         @arg @ref LL_SYSCFG_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableGPIOFilter(uint32_t GPIOPort, uint32_t GPIOPin)
{
  if(GPIOPort == LL_SYSCFG_GPIO_PORTA)
  {
    SET_BIT(SYSCFG->PAENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTB)
  {
    SET_BIT(SYSCFG->PBENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTC)
  {    
    SET_BIT(SYSCFG->PCENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTF)
  {
    SET_BIT(SYSCFG->PFENS, GPIOPin);
  }
  else
  {
    
  }
}

/**
  * @brief  Disable GPIO Filter
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  GPIOPort This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PORTA
  *         @arg @ref LL_SYSCFG_GPIO_PORTB
  *         @arg @ref LL_SYSCFG_GPIO_PORTC
  *         @arg @ref LL_SYSCFG_GPIO_PORTF
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PIN_0
  *         @arg @ref LL_SYSCFG_GPIO_PIN_1
  *         @arg @ref LL_SYSCFG_GPIO_PIN_2
  *         @arg @ref LL_SYSCFG_GPIO_PIN_3
  *         @arg @ref LL_SYSCFG_GPIO_PIN_4
  *         @arg @ref LL_SYSCFG_GPIO_PIN_5
  *         @arg @ref LL_SYSCFG_GPIO_PIN_6
  *         @arg @ref LL_SYSCFG_GPIO_PIN_7
  *         @arg @ref LL_SYSCFG_GPIO_PIN_8
  *         @arg @ref LL_SYSCFG_GPIO_PIN_9
  *         @arg @ref LL_SYSCFG_GPIO_PIN_10
  *         @arg @ref LL_SYSCFG_GPIO_PIN_11
  *         @arg @ref LL_SYSCFG_GPIO_PIN_12
  *         @arg @ref LL_SYSCFG_GPIO_PIN_13
  *         @arg @ref LL_SYSCFG_GPIO_PIN_14
  *         @arg @ref LL_SYSCFG_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableGPIOFilter(uint32_t GPIOPort, uint32_t GPIOPin)
{
  if(GPIOPort == LL_SYSCFG_GPIO_PORTA)
  {
    CLEAR_BIT(SYSCFG->PAENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTB)
  {
    CLEAR_BIT(SYSCFG->PBENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTC)
  {    
    CLEAR_BIT(SYSCFG->PCENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTF)
  {
    CLEAR_BIT(SYSCFG->PFENS, GPIOPin);
  }
  else
  {
    
  }
}

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_FLASH FLASH
  * @{
  */

/**
  * @brief  Set FLASH Latency
  * @rmtoll FLASH_ACR    LATENCY       LL_FLASH_SetLatency
  * @param  Latency This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  *         @arg @ref LL_FLASH_LATENCY_2
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetLatency(uint32_t Latency)
{
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, Latency);
}

/**
  * @brief  Get FLASH Latency
  * @rmtoll FLASH_ACR    LATENCY       LL_FLASH_GetLatency
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  *         @arg @ref LL_FLASH_LATENCY_2
  */
__STATIC_INLINE uint32_t LL_FLASH_GetLatency(void)
{
  return (uint32_t)(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY));
}

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_OCREF TIM Ocref Control
  * @{
  */

#if defined(COMP3)
/**
  * @brief  Enable COMP3 Ocref CLR TIM3
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableCOMP3OcrefCLRTIM3()
{
  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP3_OCREF_CLR_TIM3);
}

/**
  * @brief  Disable COMP3 Ocref CLR TIM3
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableCOMP3OcrefCLRTIM3()
{
  CLEAR_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP3_OCREF_CLR_TIM3);
}

/**
  * @brief  Enable COMP3 Ocref CLR TIM3
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableCOMP3OcrefCLRTIM2()
{
  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP3_OCREF_CLR_TIM2);
}

/**
  * @brief  Disable COMP3 Ocref CLR TIM3
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableCOMP3OcrefCLRTIM2()
{
  CLEAR_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP3_OCREF_CLR_TIM2);
}

/**
  * @brief  Enable COMP3 Ocref CLR TIM1
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableCOMP3OcrefCLRTIM1()
{
  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP3_OCREF_CLR_TIM1);
}

/**
  * @brief  Disable COMP3 Ocref CLR TIM1
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableCOMP3OcrefCLRTIM1()
{
  CLEAR_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP3_OCREF_CLR_TIM1);
}
#endif

/**
  * @brief  Enable COMP2 Ocref CLR TIM3
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableCOMP2OcrefCLRTIM3()
{
  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP2_OCREF_CLR_TIM3);
}

/**
  * @brief  Disable COMP2 Ocref CLR TIM3
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableCOMP2OcrefCLRTIM3()
{
  CLEAR_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP2_OCREF_CLR_TIM3);
}

/**
  * @brief  Enable COMP2 Ocref CLR TIM2
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableCOMP2OcrefCLRTIM2()
{
  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP2_OCREF_CLR_TIM2);
}

/**
  * @brief  Disable COMP2 Ocref CLR TIM2
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableCOMP2OcrefCLRTIM2()
{
  CLEAR_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP2_OCREF_CLR_TIM2);
}

/**
  * @brief  Enable COMP2 Ocref CLR TIM1
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableCOMP2OcrefCLRTIM1()
{
  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP2_OCREF_CLR_TIM1);
}

/**
  * @brief  Disable COMP2 Ocref CLR TIM1
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableCOMP2OcrefCLRTIM1()
{
  CLEAR_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP2_OCREF_CLR_TIM1);
}

/**
  * @brief  Enable COMP1 Ocref CLR TIM3
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableCOMP1OcrefCLRTIM3()
{
  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP1_OCREF_CLR_TIM3);
}

/**
  * @brief  Disable COMP1 Ocref CLR TIM3
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableCOMP1OcrefCLRTIM3()
{
  CLEAR_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP1_OCREF_CLR_TIM3);
}

/**
  * @brief  Enable COMP1 Ocref CLR TIM2
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableCOMP1OcrefCLRTIM2()
{
  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP1_OCREF_CLR_TIM2);
}

/**
  * @brief  Disable COMP1 Ocref CLR TIM2
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableCOMP1OcrefCLRTIM2()
{
  CLEAR_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP1_OCREF_CLR_TIM2);
}

/**
  * @brief  Enable COMP1 Ocref CLR TIM1
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableCOMP1OcrefCLRTIM1()
{
  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP1_OCREF_CLR_TIM1);
}

/**
  * @brief  Disable COMP1 Ocref CLR TIM1
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableCOMP1OcrefCLRTIM1()
{
  CLEAR_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_COMP1_OCREF_CLR_TIM1);
}

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_DBGMCU DBGMCU
  * @{
  */

/**
  * @brief  Return the device revision identifier
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetRevisionID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_REV_ID) >> DBGMCU_IDCODE_REV_ID_Pos);
}

/**
  * @brief  Enable the Debug Module during STOP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Indicate if enable the Debug Module during STOP mode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGStopMode(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP) == (DBGMCU_CR_DBG_STOP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Debug Module during SLEEP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGSleepMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Disable the Debug Module during SLEEP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGSleepMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Indicate if enable the Debug Module during SLEEP mode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGSleepMode(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP) == (DBGMCU_CR_DBG_SLEEP)) ? 1UL : 0UL);
}


/**
  * @brief  Freeze APB1 peripherals (group1 peripherals)
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM6_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM7_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_CAN_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_SMBUS_TIMEOUT
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APBFZ1, Periphs);
}

/**
  * @brief  Unfreeze APB1 peripherals (group1 peripherals)
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM6_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM7_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_CAN_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_SMBUS_TIMEOUT
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APBFZ1, Periphs);
}

/**
  * @brief  Indicate if Freeze APB1 peripherals (group1 peripherals)
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be one of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM6_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM7_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_CAN_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_SMBUS_TIMEOUT
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C2_SMBUS_TIMEOUT
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_APB1_GRP1_IsFreezePeriph(uint32_t Periphs)
{
  return ((READ_BIT(DBGMCU->APBFZ1, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Freeze APB1 peripherals(group2 peripherals)
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM15_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP2_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APBFZ2, Periphs);
}

/**
  * @brief  Unfreeze APB1 peripherals(group2 peripherals)
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM15_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP2_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APBFZ2, Periphs);
}

/**
  * @brief  Indicate if Freeze APB1 peripherals (group2 peripherals)
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be one of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM15_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM17_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_APB1_GRP2_IsFreezePeriph(uint32_t Periphs)
{
  return ((READ_BIT(DBGMCU->APBFZ2, Periphs) == (Periphs)) ? 1UL : 0UL);
}
/**
  * @}
  */
/**
  * @}
  */

/**
  * @}
  */



#endif /* defined (FLASH) || defined (SYSCFG) || defined (DBGMCU) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PY32F072_LL_SYSTEM_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
