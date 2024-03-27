/**
  ******************************************************************************
  * @file    py32f040_ll_comp.h
  * @author  MCU Application Team
  * @brief   Header file of COMP LL module.
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
#ifndef __PY32F040_LL_COMP_H
#define __PY32F040_LL_COMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx.h"

/** @addtogroup PY32F040_LL_Driver
  * @{
  */

#if defined (COMP1) || defined (COMP2) || defined(COMP3)

/** @defgroup COMP_LL COMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup COMP_LL_Private_Constants COMP Private Constants
  * @{
  */

/* Internal mask for pair of comparators instances window mode:               */
/* To select into literals LL_COMP_WINDOWMODE_COMPx_INPUT_PLUS_COMMON         */
/* the relevant bits for:                                                     */
/* (concatenation of multiple bits used in different registers)               */
/* - Comparator instance selected as master for window mode : register offset */
/* - Window mode enable or disable: bit value */
#define LL_COMP_WINDOWMODE_COMP_ODD_REGOFFSET_MASK  (0x00000000U) /* Register of COMP instance odd (COMP1_CSR, ...) defined as reference register */
#define LL_COMP_WINDOWMODE_COMP_EVEN_REGOFFSET_MASK (0x00000004U) /* Register of COMP instance even (COMP2_CSR, ...) offset vs register of COMP instance odd */
#define LL_COMP_WINDOWMODE_COMPX_REGOFFSET_MASK     (LL_COMP_WINDOWMODE_COMP_ODD_REGOFFSET_MASK | LL_COMP_WINDOWMODE_COMP_EVEN_REGOFFSET_MASK)
#define LL_COMP_WINDOWMODE_COMPX_SETTING_MASK       (COMP_CSR_WINMODE)
#define LL_COMP_WINDOWOUTPUT_BOTH_POS_VS_WINDOW     (1U)

/* COMP registers bits positions */
#define LL_COMP_WINDOWMODE_BITOFFSET_POS   (11U) /* Value equivalent to POSITION_VAL(COMP_CSR_WINMODE) */
#define LL_COMP_OUTPUT_LEVEL_BITOFFSET_POS (30U) /* Value equivalent to POSITION_VAL(COMP_CSR_COMP_OUT) */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup COMP_LL_Private_Macros COMP Private Macros
  * @{
  */

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  __REG__ Register basis from which the offset is applied.
  * @param  __REG_OFFFSET__ Offset to be applied (unit: number of registers).
  * @retval Pointer to register address
  */
#define __COMP_PTR_REG_OFFSET(__REG__, __REG_OFFFSET__)                        \
  ((__IO uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFFSET__) << 2U))))

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup COMP_LL_ES_INIT COMP Exported Init structure
  * @{
  */

/**
  * @brief  Structure definition of some features of COMP instance.
  */
typedef struct
{
  uint32_t PowerMode;                   /*!< Set comparator operating mode to adjust power and speed.
                                             This parameter can be a value of @ref COMP_LL_EC_POWERMODE
  
                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetPowerMode(). */
  
  uint32_t InputPlus;                   /*!< Set comparator input plus (non-inverting input).
                                             This parameter can be a value of @ref COMP_LL_EC_INPUT_PLUS

                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetInputPlus(). */

  uint32_t InputMinus;                  /*!< Set comparator input minus (inverting input).
                                             This parameter can be a value of @ref COMP_LL_EC_INPUT_MINUS
   
                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetInputMinus(). */
  
  uint32_t InputHysteresis;             /*!< Set comparator hysteresis mode of the input minus.
                                             This parameter can be a value of @ref COMP_LL_EC_INPUT_HYSTERESIS

                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetInputHysteresis(). */

  uint32_t OutputPolarity;              /*!< Set comparator output polarity.
                                             This parameter can be a value of @ref COMP_LL_EC_OUTPUT_POLARITY

                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetOutputPolarity(). */

  uint32_t DigitalFilter;               /*!< Specifies the digital filter. 
                                             This parameter must be a number between 0 and 0xFFFF 

                                             The filter is prohibited,when the value is zero. 
                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetDigitalFilter(). */

} LL_COMP_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Constants COMP Exported Constants
  * @{
  */

/** @defgroup COMP_LL_EC_COMMON_WINDOWMODE Comparator common modes - Window mode
  * @{
  */
#define LL_COMP_WINDOWMODE_DISABLE                 (0x00000000U)                                                    /*!< Window mode disable: Comparators 1 and 2 are independent */
#define LL_COMP_WINDOWMODE_COMP1_INPUT_PLUS_COMMON (COMP_CSR_WINMODE | LL_COMP_WINDOWMODE_COMP_EVEN_REGOFFSET_MASK)  /*!< Window mode enable: if used from COMP1 or COMP2 instance, comparators instances pair COMP1 and COMP2 have their input plus connected together, the common input is COMP1 input plus (COMP2 input plus is no more accessible). */
#define LL_COMP_WINDOWMODE_COMP2_INPUT_PLUS_COMMON (COMP_CSR_WINMODE | LL_COMP_WINDOWMODE_COMP_ODD_REGOFFSET_MASK)  /*!< Window mode enable: if used from COMP1 or COMP2 instance, comparators instances pair COMP1 and COMP2 have their input plus connected together, the common input is COMP2 input plus (COMP1 input plus is no more accessible). */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_PLUS Comparator inputs - Input plus (input non-inverting) selection
  * @{
  */
/* Note: These comments for V1C                    */
#define LL_COMP_INPUT_PLUS_IO0          (0x00000000U)     /*!< Comparator input plus connected to IO0 (OPA1 for COMP1, pin PA0 for COMP2, PA5 for COMP3) */
#define LL_COMP_INPUT_PLUS_IO1          (                                                            COMP_CSR_INPSEL_0) /*!< Comparator input plus connected to IO1 (PC1 for COMP1, PA1 for COMP2, PB1 for COMP3) */
#define LL_COMP_INPUT_PLUS_IO2          (                                        COMP_CSR_INPSEL_1                    ) /*!< Comparator input plus connected to IO2 (PC2 for COMP1, PA2 for COMP2, PB11 for COMP3) */
#define LL_COMP_INPUT_PLUS_IO3          (                                        COMP_CSR_INPSEL_1 | COMP_CSR_INPSEL_0) /*!< Comparator input plus connected to IO3 (PC3 for COMP1, PA3 for COMP2, PB14 for COMP3) */
#define LL_COMP_INPUT_PLUS_IO4          (                    COMP_CSR_INPSEL_2                                        ) /*!< Comparator input plus connected to IO4 (PA0 for COMP1, PA4 for COMP2, OPA3 for COMP3) */
#define LL_COMP_INPUT_PLUS_IO5          (                    COMP_CSR_INPSEL_2                     | COMP_CSR_INPSEL_0) /*!< Comparator input plus connected to IO5 (PA1 for COMP1, PA5 for COMP2, DAC1_VIN for COMP3) */
#define LL_COMP_INPUT_PLUS_IO6          (                    COMP_CSR_INPSEL_2 | COMP_CSR_INPSEL_1                    ) /*!< Comparator input plus connected to IO6 (PA2 for COMP1, PB1 for COMP2, DAC2_VIN for COMP3) */
#define LL_COMP_INPUT_PLUS_IO7          (                    COMP_CSR_INPSEL_2 | COMP_CSR_INPSEL_1 | COMP_CSR_INPSEL_0) /*!< Comparator input plus connected to IO7 (PA3 for COMP1, PB2 for COMP2, reserved for COMP3) */
#define LL_COMP_INPUT_PLUS_IO8          (COMP_CSR_INPSEL_3                                                            ) /*!< Comparator input plus connected to IO8 (PA4 for COMP1, PB10 for COMP2, reserved for COMP3) */
#define LL_COMP_INPUT_PLUS_IO9          (COMP_CSR_INPSEL_3                                         | COMP_CSR_INPSEL_0) /*!< Comparator input plus connected to IO9 (PA5 for COMP1, OPA2 for COMP2, reserved for COMP3) */
#define LL_COMP_INPUT_PLUS_IO10         (COMP_CSR_INPSEL_3                     | COMP_CSR_INPSEL_1                    ) /*!< Comparator input plus connected to IO10 (PA6 for COMP1, PB13 for COMP2, reserved for COMP3) */
#define LL_COMP_INPUT_PLUS_IO11         (COMP_CSR_INPSEL_3                     | COMP_CSR_INPSEL_1 | COMP_CSR_INPSEL_0) /*!< Comparator input plus connected to IO11 (PA7 for COMP1, PB14 for COMP2, reserved for COMP3) */
#define LL_COMP_INPUT_PLUS_IO12         (COMP_CSR_INPSEL_3 | COMP_CSR_INPSEL_2                                        ) /*!< Comparator input plus connected to IO12 (PB4 for COMP1, PB4 for COMP2, reserved for COMP3) */
#define LL_COMP_INPUT_PLUS_IO13         (COMP_CSR_INPSEL_3 | COMP_CSR_INPSEL_2                     | COMP_CSR_INPSEL_0) /*!< Comparator input plus connected to IO13 (PB5 for COMP1, PB6 for COMP2, reserved for COMP3) */
#define LL_COMP_INPUT_PLUS_IO14         (COMP_CSR_INPSEL_3 | COMP_CSR_INPSEL_2 | COMP_CSR_INPSEL_1                    ) /*!< Comparator input plus connected to IO14 (PB6 for COMP1, PB7 for COMP2, reserved for COMP3) */
#define LL_COMP_INPUT_PLUS_IO15         (COMP_CSR_INPSEL_3 | COMP_CSR_INPSEL_2 | COMP_CSR_INPSEL_1 | COMP_CSR_INPSEL_0) /*!< Comparator input plus connected to IO15 (DAC1_VIN for COMP1,DAC2_VIN for COMP2, reserved for COMP3) */

/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_MINUS Comparator inputs - Input minus (input inverting) selection
  * @{
  */
/* Note: These comments for V1C                    */
#define LL_COMP_INPUT_MINUS_IO0          (0x00000000U)     /*!< Comparator input plus connected to IO0 (PA0 for COMP1, pin PC0 for COMP2, PA5 for COMP3) */
#define LL_COMP_INPUT_MINUS_IO1          (                                                            COMP_CSR_INNSEL_0) /*!< Comparator input plus connected to IO1 (PA1 for COMP1, PC1 for COMP2, PB1 for COMP3) */
#define LL_COMP_INPUT_MINUS_IO2          (                                        COMP_CSR_INNSEL_1                    ) /*!< Comparator input plus connected to IO2 (PA2 for COMP1, PC2 for COMP2, PB11 for COMP3) */
#define LL_COMP_INPUT_MINUS_IO3          (                                        COMP_CSR_INNSEL_1 | COMP_CSR_INNSEL_0) /*!< Comparator input plus connected to IO3 (PA3 for COMP1, PC3 for COMP2, PB14 for COMP3) */
#define LL_COMP_INPUT_MINUS_IO4          (                    COMP_CSR_INNSEL_2                                        ) /*!< Comparator input plus connected to IO4 (PA4 for COMP1, PA0 for COMP2, PC7 for COMP3) */
#define LL_COMP_INPUT_MINUS_IO5          (                    COMP_CSR_INNSEL_2                     | COMP_CSR_INNSEL_0) /*!< Comparator input plus connected to IO5 (PA5 for COMP1, PA1 for COMP2, DAC1_VIN for COMP3) */
#define LL_COMP_INPUT_MINUS_IO6          (                    COMP_CSR_INNSEL_2 | COMP_CSR_INNSEL_1                    ) /*!< Comparator input plus connected to IO6 (PA6 for COMP1, PB0 for COMP2, DAC2_VIN for COMP3) */
#define LL_COMP_INPUT_MINUS_IO7          (                    COMP_CSR_INNSEL_2 | COMP_CSR_INNSEL_1 | COMP_CSR_INNSEL_0) /*!< Comparator input plus connected to IO7 (PA7 for COMP1, PB1 for COMP2, TS_VIN for COMP3) */
#define LL_COMP_INPUT_MINUS_IO8          (COMP_CSR_INNSEL_3                                                            ) /*!< Comparator input plus connected to IO8 (PC4 for COMP1, PB2 for COMP2, VREFINT for COMP3) */
#define LL_COMP_INPUT_MINUS_IO9          (COMP_CSR_INNSEL_3                                         | COMP_CSR_INNSEL_0) /*!< Comparator input plus connected to IO9 (PC5 for COMP1, PB3 for COMP2, VREFBUF for COMP3) */
#define LL_COMP_INPUT_MINUS_IO10         (COMP_CSR_INNSEL_3                     | COMP_CSR_INNSEL_1                    ) /*!< Comparator input plus connected to IO10 (DAC1_VIN for COMP1, DAC2_VIN for COMP2, VREFCMP for COMP3 ) */
#define LL_COMP_INPUT_MINUS_IO11         (COMP_CSR_INNSEL_3                     | COMP_CSR_INNSEL_1 | COMP_CSR_INNSEL_0) /*!< Comparator input plus connected to IO11 (VREFCMP for COMP1, VREFCMP for COMP2, reserved for COMP3) */
#define LL_COMP_INPUT_MINUS_IO12         (COMP_CSR_INNSEL_3 | COMP_CSR_INNSEL_2                                        ) /*!< Comparator input plus connected to IO12 (TS_VIN for COMP1, TS_VIN for COMP2, reserved for COMP3) */
#define LL_COMP_INPUT_MINUS_IO13         (COMP_CSR_INNSEL_3 | COMP_CSR_INNSEL_2                     | COMP_CSR_INNSEL_0) /*!< Comparator input plus connected to IO13 (VREFINT for COMP1, VREFINT for COMP2, reserved for COMP3) */
#define LL_COMP_INPUT_MINUS_IO14         (COMP_CSR_INNSEL_3 | COMP_CSR_INNSEL_2 | COMP_CSR_INNSEL_1                    ) /*!< Comparator input plus connected to IO14 (VREFBUF for COMP1, VREFBUF for COMP2, reserved for COMP3) */
#define LL_COMP_INPUT_MINUS_IO15         (COMP_CSR_INNSEL_3 | COMP_CSR_INNSEL_2 | COMP_CSR_INNSEL_1 | COMP_CSR_INNSEL_0) /*!< Comparator input plus connected to IO15 (PC0 for COMP1, PB12 for COMP2, reserved for COMP3) */

/**
  * @}
  */
  
/** @defgroup COMP_LL_EC_VREFCMP_DIV Comparator Vrefcmp Div
  * @{
  */
#define LL_COMP_VREFCMP_DIV_1_64VREFCMP     (0x00000000U)     
#define LL_COMP_VREFCMP_DIV_2_64VREFCMP     (                                                                                               COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_3_64VREFCMP     (                                                                            COMP_CSR_VCDIV_1                   )
#define LL_COMP_VREFCMP_DIV_4_64VREFCMP     (                                                                            COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_5_64VREFCMP     (                                                         COMP_CSR_VCDIV_2                                      ) 
#define LL_COMP_VREFCMP_DIV_6_64VREFCMP     (                                                         COMP_CSR_VCDIV_2                    | COMP_CSR_VCDIV_0)  
#define LL_COMP_VREFCMP_DIV_7_64VREFCMP     (                                                         COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1                   ) 
#define LL_COMP_VREFCMP_DIV_8_64VREFCMP     (                                                         COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_9_64VREFCMP     (                                      COMP_CSR_VCDIV_3                                                         )
#define LL_COMP_VREFCMP_DIV_10_64VREFCMP    (                                      COMP_CSR_VCDIV_3                                       | COMP_CSR_VCDIV_0)  
#define LL_COMP_VREFCMP_DIV_11_64VREFCMP    (                                      COMP_CSR_VCDIV_3                    | COMP_CSR_VCDIV_1                   )  
#define LL_COMP_VREFCMP_DIV_12_64VREFCMP    (                                      COMP_CSR_VCDIV_3                    | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_13_64VREFCMP    (                                      COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2                                      ) 
#define LL_COMP_VREFCMP_DIV_14_64VREFCMP    (                                      COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2                    | COMP_CSR_VCDIV_0)  
#define LL_COMP_VREFCMP_DIV_15_64VREFCMP    (                                      COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1                   ) 
#define LL_COMP_VREFCMP_DIV_16_64VREFCMP    (                                      COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0)      
#define LL_COMP_VREFCMP_DIV_17_64VREFCMP    (                   COMP_CSR_VCDIV_4                                                                            ) 
#define LL_COMP_VREFCMP_DIV_18_64VREFCMP    (                   COMP_CSR_VCDIV_4                                                          | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_19_64VREFCMP    (                   COMP_CSR_VCDIV_4                                       | COMP_CSR_VCDIV_1                   ) 
#define LL_COMP_VREFCMP_DIV_20_64VREFCMP    (                   COMP_CSR_VCDIV_4                                       | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_21_64VREFCMP    (                   COMP_CSR_VCDIV_4                    | COMP_CSR_VCDIV_2                                      ) 
#define LL_COMP_VREFCMP_DIV_22_64VREFCMP    (                   COMP_CSR_VCDIV_4                    | COMP_CSR_VCDIV_2                    | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_23_64VREFCMP    (                   COMP_CSR_VCDIV_4                    | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1                   )
#define LL_COMP_VREFCMP_DIV_24_64VREFCMP    (                   COMP_CSR_VCDIV_4                    | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_25_64VREFCMP    (                   COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3                                                         ) 
#define LL_COMP_VREFCMP_DIV_26_64VREFCMP    (                   COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3                                       | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_27_64VREFCMP    (                   COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3                    | COMP_CSR_VCDIV_1                   ) 
#define LL_COMP_VREFCMP_DIV_28_64VREFCMP    (                   COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3                    | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_29_64VREFCMP    (                   COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2                                      )  
#define LL_COMP_VREFCMP_DIV_30_64VREFCMP    (                   COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2                    | COMP_CSR_VCDIV_0)   
#define LL_COMP_VREFCMP_DIV_31_64VREFCMP    (                   COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1                   )      
#define LL_COMP_VREFCMP_DIV_32_64VREFCMP    (                   COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0)  
#define LL_COMP_VREFCMP_DIV_33_64VREFCMP    (COMP_CSR_VCDIV_5                                                                                               ) 
#define LL_COMP_VREFCMP_DIV_34_64VREFCMP    (COMP_CSR_VCDIV_5                                                                             | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_35_64VREFCMP    (COMP_CSR_VCDIV_5                                                          | COMP_CSR_VCDIV_1                   )  
#define LL_COMP_VREFCMP_DIV_36_64VREFCMP    (COMP_CSR_VCDIV_5                                                          | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_37_64VREFCMP    (COMP_CSR_VCDIV_5                                       | COMP_CSR_VCDIV_2                                      ) 
#define LL_COMP_VREFCMP_DIV_38_64VREFCMP    (COMP_CSR_VCDIV_5                                       | COMP_CSR_VCDIV_2                    | COMP_CSR_VCDIV_0)  
#define LL_COMP_VREFCMP_DIV_39_64VREFCMP    (COMP_CSR_VCDIV_5                                       | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1                   ) 
#define LL_COMP_VREFCMP_DIV_40_64VREFCMP    (COMP_CSR_VCDIV_5                                       | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_41_64VREFCMP    (COMP_CSR_VCDIV_5                    | COMP_CSR_VCDIV_3                                                         )   
#define LL_COMP_VREFCMP_DIV_42_64VREFCMP    (COMP_CSR_VCDIV_5                    | COMP_CSR_VCDIV_3                                       | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_43_64VREFCMP    (COMP_CSR_VCDIV_5                    | COMP_CSR_VCDIV_3                    | COMP_CSR_VCDIV_1                   ) 
#define LL_COMP_VREFCMP_DIV_44_64VREFCMP    (COMP_CSR_VCDIV_5                    | COMP_CSR_VCDIV_3                    | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_45_64VREFCMP    (COMP_CSR_VCDIV_5                    | COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2                                      )  
#define LL_COMP_VREFCMP_DIV_46_64VREFCMP    (COMP_CSR_VCDIV_5                    | COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2                    | COMP_CSR_VCDIV_0)  
#define LL_COMP_VREFCMP_DIV_47_64VREFCMP    (COMP_CSR_VCDIV_5                    | COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1                   ) 
#define LL_COMP_VREFCMP_DIV_48_64VREFCMP    (COMP_CSR_VCDIV_5                    | COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0)  
#define LL_COMP_VREFCMP_DIV_49_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4                                                                            )   
#define LL_COMP_VREFCMP_DIV_50_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4                                                          | COMP_CSR_VCDIV_0)  
#define LL_COMP_VREFCMP_DIV_51_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4                                       | COMP_CSR_VCDIV_1                   )     
#define LL_COMP_VREFCMP_DIV_52_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4                                       | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0)  
#define LL_COMP_VREFCMP_DIV_53_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4                    | COMP_CSR_VCDIV_2                                      )  
#define LL_COMP_VREFCMP_DIV_54_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4                    | COMP_CSR_VCDIV_2                    | COMP_CSR_VCDIV_0)  
#define LL_COMP_VREFCMP_DIV_55_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4                    | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1                   ) 
#define LL_COMP_VREFCMP_DIV_56_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4                    | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_57_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3                                                         ) 
#define LL_COMP_VREFCMP_DIV_58_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3                                       | COMP_CSR_VCDIV_0)  
#define LL_COMP_VREFCMP_DIV_59_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3                    | COMP_CSR_VCDIV_1                   ) 
#define LL_COMP_VREFCMP_DIV_60_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3                    | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0)   
#define LL_COMP_VREFCMP_DIV_61_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2                                      )     
#define LL_COMP_VREFCMP_DIV_62_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2                    | COMP_CSR_VCDIV_0) 
#define LL_COMP_VREFCMP_DIV_63_64VREFCMP    (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1                   )  
#define LL_COMP_VREFCMP_DIV_VREFCMP         (COMP_CSR_VCDIV_5 | COMP_CSR_VCDIV_4 | COMP_CSR_VCDIV_3 | COMP_CSR_VCDIV_2 | COMP_CSR_VCDIV_1 | COMP_CSR_VCDIV_0) 
/**
  * @}
  */  
 
/** @defgroup COMP_LL_EC_VREFCMP_SOURCE Comparator Vrefcmp Source
  * @{
  */
#define LL_COMP_VREFCMP_SOURCE_NONE         (0x00000000U)  
#define LL_COMP_VREFCMP_SOURCE_VCC          (COMP_CSR_VCSEL_0)
#define LL_COMP_VREFCMP_SOURCE_VREFBUF      (COMP_CSR_VCSEL_1)
#define LL_COMP_VREFCMP_SOURCE_VREF1P2V     (COMP_CSR_VCSEL_0 | COMP_CSR_VCSEL_1)  
/**
  * @}
  */   

/** @defgroup COMP_LL_EC_OUTPUT_POLARITY Comparator output - Output polarity
  * @{
  */
#define LL_COMP_OUTPUTPOL_NONINVERTED       (0x00000000U)           /*!< COMP output polarity is not inverted: comparator output is high when the plus (non-inverting) input is at a higher voltage than the minus (inverting) input */
#define LL_COMP_OUTPUTPOL_INVERTED          (COMP_CSR_POLARITY)     /*!< COMP output polarity is inverted: comparator output is low when the plus (non-inverting) input is at a lower voltage than the minus (inverting) input */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_LEVEL Comparator output - Output level
  * @{
  */
#define LL_COMP_OUTPUT_LEVEL_LOW            (0x00000000U)          /*!< Comparator output level low (if the polarity is not inverted, otherwise to be complemented) */
#define LL_COMP_OUTPUT_LEVEL_HIGH           (0x00000001U)          /*!< Comparator output level high (if the polarity is not inverted, otherwise to be complemented) */

/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_HYSTERESIS Comparator Hysteresis
  * @{
  */
#define LL_COMP_HYSTERESIS_ENABLE           (0x00000001U)          /*!< Comparator Hysteresis Enable */
#define LL_COMP_HYSTERESIS_DISABLE          (0x00000000U)          /*!< Comparator Hysteresis Disable */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_POWERMODE Comparator modes - Power mode
  * @{
  */
#define LL_COMP_POWERMODE_HIGHSPEED         ((uint32_t)0x00000000U)                       /*!< COMP power mode to high speed */
#define LL_COMP_POWERMODE_MEDIUMSPEED       (COMP_CSR_PWRMODE_0)                          /*!< COMP power mode to medium speed */


/**
  * @}
  */

/** @defgroup COMP_LL_EC_HW_DELAYS  Definitions of COMP hardware constraints delays
  * @note   Only COMP peripheral HW delays are defined in COMP LL driver driver,
  *         not timeout values.
  *         For details on delays values, refer to descriptions in source code
  *         above each literal definition.
  * @{
  */

/* Delay for comparator startup time.                                         */
/* Note: Delay required to reach propagation delay specification.             */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART").                                                       */
/* Unit: us                                                                   */
#define LL_COMP_DELAY_STARTUP_US          ( 80U) /*!< Delay for COMP startup time */

/* Delay for comparator voltage scaler stabilization time.                    */
/* Note: Voltage scaler is used when selecting comparator input               */
/*       based on VrefInt: VrefInt or subdivision of VrefInt.                 */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART_SCALER").                                                */
/* Unit: us                                                                   */
#define LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US ( 200U) /*!< Delay for COMP voltage scaler stabilization time */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Macros COMP Exported Macros
  * @{
  */
/** @defgroup COMP_LL_EM_WRITE_READ Common write and read registers macro
  * @{
  */

/**
  * @brief  Write a value in COMP register
  * @param  __INSTANCE__ comparator instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_COMP_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG((__INSTANCE__)->__REG__, (__VALUE__))

/**
  * @brief  Read a value in COMP register
  * @param  __INSTANCE__ comparator instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_COMP_ReadReg(__INSTANCE__, __REG__) READ_REG((__INSTANCE__)->__REG__)
/**
  * @}
  */

/** @defgroup COMP_LL_EM_HELPER_MACRO COMP helper macro
  * @{
  */

/**
  * @brief  Helper macro to select the COMP common instance
  *         to which is belonging the selected COMP instance.
  * @note   COMP common register instance can be used to
  *         set parameters common to several COMP instances.
  *         Refer to functions having argument "COMPxy_COMMON" as parameter.
  * @param  __COMPx__ COMP instance
  * @retval COMP common instance or value "0" if there is no COMP common instance.
  */
#define __LL_COMP_COMMON_INSTANCE(__COMPx__)     (COMP12_COMMON)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Functions COMP Exported Functions
  * @{
  */

/** @defgroup COMP_LL_EF_Configuration_comparator_common Configuration of COMP hierarchical scope: common to several COMP instances
  * @{
  */

/**
  * @brief  Set window mode of a pair of comparators instances
  * @rmtoll CSR      WINMODE        LL_COMP_SetCommonWindowMode
  * @param  COMPxy_COMMON Comparator common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_COMP_COMMON_INSTANCE() )
  * @param  WindowMode This parameter can be one of the following values:
  *         @arg @ref LL_COMP_WINDOWMODE_DISABLE
  *         @arg @ref LL_COMP_WINDOWMODE_COMP1_INPUT_PLUS_COMMON 
  *         @arg @ref LL_COMP_WINDOWMODE_COMP2_INPUT_PLUS_COMMON 
  * @retval None  
  */
__STATIC_INLINE void LL_COMP_SetCommonWindowMode(COMP_Common_TypeDef *COMPxy_COMMON, uint32_t WindowMode)
{
  uint32_t window_mode_tmp = WindowMode;

  __IO uint32_t *preg = __COMP_PTR_REG_OFFSET(COMPxy_COMMON->CSR_ODD, (window_mode_tmp & LL_COMP_WINDOWMODE_COMPX_REGOFFSET_MASK));

  /* Clear the potential previous setting of window mode */
  __IO uint32_t *preg_clear = __COMP_PTR_REG_OFFSET(COMPxy_COMMON->CSR_ODD, (~(window_mode_tmp & LL_COMP_WINDOWMODE_COMPX_REGOFFSET_MASK) & LL_COMP_WINDOWMODE_COMP_EVEN_REGOFFSET_MASK));
  CLEAR_BIT(*preg_clear,COMP_CSR_WINMODE);

  /* Set window mode */
  MODIFY_REG(*preg, COMP_CSR_WINMODE,(window_mode_tmp & LL_COMP_WINDOWMODE_COMPX_SETTING_MASK));
}

/**
  * @brief  Get window mode of a pair of comparators instances
  * @rmtoll CSR      WINMODE        LL_COMP_GetCommonWindowMode
  * @param  COMPxy_COMMON Comparator common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_COMP_COMMON_INSTANCE() )
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_WINDOWMODE_DISABLE 
  *         @arg @ref LL_COMP_WINDOWMODE_COMP1_INPUT_PLUS_COMMON 
  *         @arg @ref LL_COMP_WINDOWMODE_COMP2_INPUT_PLUS_COMMON 
  *
  */
__STATIC_INLINE uint32_t LL_COMP_GetCommonWindowMode(COMP_Common_TypeDef *COMPxy_COMMON)
{
   const uint32_t window_mode_comp_odd = (uint32_t)READ_BIT(COMPxy_COMMON->CSR_ODD, COMP_CSR_WINMODE);
   const uint32_t window_mode_comp_even = (uint32_t)READ_BIT(COMPxy_COMMON->CSR_EVEN, COMP_CSR_WINMODE);

   return (uint32_t)(window_mode_comp_odd | window_mode_comp_even
                    | ((window_mode_comp_even >> LL_COMP_WINDOWMODE_BITOFFSET_POS) * LL_COMP_WINDOWMODE_COMP_EVEN_REGOFFSET_MASK));
}
/**
  * @}
  */

/** @defgroup COMP_LL_EF_Configuration_comparator_inputs Configuration of comparator inputs
  * @{
  */

/**
  * @brief  Set comparator inputs minus (inverting) and plus (non-inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll CSR      INNSEL         LL_COMP_ConfigInputs\n
  *         CSR      INPSEL         LL_COMP_ConfigInputs
  * @param  COMPx Comparator instance
  * @param  InputMinus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_IO0
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_IO3
  *         @arg @ref LL_COMP_INPUT_MINUS_IO4
  *         @arg @ref LL_COMP_INPUT_MINUS_IO5
  *         @arg @ref LL_COMP_INPUT_MINUS_IO6
  *         @arg @ref LL_COMP_INPUT_MINUS_IO7
  *         @arg @ref LL_COMP_INPUT_MINUS_IO8
  *         @arg @ref LL_COMP_INPUT_MINUS_IO9
  *         @arg @ref LL_COMP_INPUT_MINUS_IO10
  *         @arg @ref LL_COMP_INPUT_MINUS_IO11
  *         @arg @ref LL_COMP_INPUT_MINUS_IO12
  *         @arg @ref LL_COMP_INPUT_MINUS_IO13
  *         @arg @ref LL_COMP_INPUT_MINUS_IO14
  *         @arg @ref LL_COMP_INPUT_MINUS_IO15
  * @param  InputPlus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO0
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO3
  *         @arg @ref LL_COMP_INPUT_PLUS_IO4
  *         @arg @ref LL_COMP_INPUT_PLUS_IO5
  *         @arg @ref LL_COMP_INPUT_PLUS_IO6
  *         @arg @ref LL_COMP_INPUT_PLUS_IO7
  *         @arg @ref LL_COMP_INPUT_PLUS_IO8
  *         @arg @ref LL_COMP_INPUT_PLUS_IO9
  *         @arg @ref LL_COMP_INPUT_PLUS_IO10
  *         @arg @ref LL_COMP_INPUT_PLUS_IO11
  *         @arg @ref LL_COMP_INPUT_PLUS_IO12
  *         @arg @ref LL_COMP_INPUT_PLUS_IO13
  *         @arg @ref LL_COMP_INPUT_PLUS_IO14
  *         @arg @ref LL_COMP_INPUT_PLUS_IO15
  * @retval None
  */
__STATIC_INLINE void LL_COMP_ConfigInputs(COMP_TypeDef *COMPx, uint32_t InputMinus, uint32_t InputPlus)
{
  MODIFY_REG(COMPx->CSR,COMP_CSR_INNSEL | COMP_CSR_INPSEL,InputMinus | InputPlus);
}

/**
  * @brief  Set comparator input plus (non-inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll CSR      INPSEL         LL_COMP_SetInputPlus
  * @param  COMPx Comparator instance
  * @param  InputPlus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO0
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO3
  *         @arg @ref LL_COMP_INPUT_PLUS_IO4
  *         @arg @ref LL_COMP_INPUT_PLUS_IO5
  *         @arg @ref LL_COMP_INPUT_PLUS_IO6
  *         @arg @ref LL_COMP_INPUT_PLUS_IO7
  *         @arg @ref LL_COMP_INPUT_PLUS_IO8
  *         @arg @ref LL_COMP_INPUT_PLUS_IO9
  *         @arg @ref LL_COMP_INPUT_PLUS_IO10
  *         @arg @ref LL_COMP_INPUT_PLUS_IO11
  *         @arg @ref LL_COMP_INPUT_PLUS_IO12
  *         @arg @ref LL_COMP_INPUT_PLUS_IO13
  *         @arg @ref LL_COMP_INPUT_PLUS_IO14
  *         @arg @ref LL_COMP_INPUT_PLUS_IO15
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetInputPlus(COMP_TypeDef *COMPx, uint32_t InputPlus)
{
  MODIFY_REG(COMPx->CSR, COMP_CSR_INPSEL, InputPlus);
}

/**
  * @brief  Get comparator input plus (non-inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll CSR      INPSEL         LL_COMP_GetInputPlus
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO0
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO3
  *         @arg @ref LL_COMP_INPUT_PLUS_IO4
  *         @arg @ref LL_COMP_INPUT_PLUS_IO5
  *         @arg @ref LL_COMP_INPUT_PLUS_IO6
  *         @arg @ref LL_COMP_INPUT_PLUS_IO7
  *         @arg @ref LL_COMP_INPUT_PLUS_IO8
  *         @arg @ref LL_COMP_INPUT_PLUS_IO9
  *         @arg @ref LL_COMP_INPUT_PLUS_IO10
  *         @arg @ref LL_COMP_INPUT_PLUS_IO11
  *         @arg @ref LL_COMP_INPUT_PLUS_IO12
  *         @arg @ref LL_COMP_INPUT_PLUS_IO13
  *         @arg @ref LL_COMP_INPUT_PLUS_IO14
  *         @arg @ref LL_COMP_INPUT_PLUS_IO15
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputPlus(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CSR, COMP_CSR_INPSEL));
}

/**
  * @brief  Set comparator input minus (inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll CSR      INMSEL         LL_COMP_SetInputMinus
  * @param  COMPx Comparator instance
  * @param  InputMinus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_IO0
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_IO3
  *         @arg @ref LL_COMP_INPUT_MINUS_IO4
  *         @arg @ref LL_COMP_INPUT_MINUS_IO5
  *         @arg @ref LL_COMP_INPUT_MINUS_IO6
  *         @arg @ref LL_COMP_INPUT_MINUS_IO7
  *         @arg @ref LL_COMP_INPUT_MINUS_IO8
  *         @arg @ref LL_COMP_INPUT_MINUS_IO9
  *         @arg @ref LL_COMP_INPUT_MINUS_IO10
  *         @arg @ref LL_COMP_INPUT_MINUS_IO11
  *         @arg @ref LL_COMP_INPUT_MINUS_IO12
  *         @arg @ref LL_COMP_INPUT_MINUS_IO13
  *         @arg @ref LL_COMP_INPUT_MINUS_IO14
  *         @arg @ref LL_COMP_INPUT_MINUS_IO15
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetInputMinus(COMP_TypeDef *COMPx, uint32_t InputMinus)
{
  MODIFY_REG(COMPx->CSR, COMP_CSR_INNSEL, InputMinus);
}

/**
  * @brief  Get comparator input minus (inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll CSR      INMSEL         LL_COMP_GetInputMinus
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_IO0
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_IO3
  *         @arg @ref LL_COMP_INPUT_MINUS_IO4
  *         @arg @ref LL_COMP_INPUT_MINUS_IO5
  *         @arg @ref LL_COMP_INPUT_MINUS_IO6
  *         @arg @ref LL_COMP_INPUT_MINUS_IO7
  *         @arg @ref LL_COMP_INPUT_MINUS_IO8
  *         @arg @ref LL_COMP_INPUT_MINUS_IO9
  *         @arg @ref LL_COMP_INPUT_MINUS_IO10
  *         @arg @ref LL_COMP_INPUT_MINUS_IO11
  *         @arg @ref LL_COMP_INPUT_MINUS_IO12
  *         @arg @ref LL_COMP_INPUT_MINUS_IO13
  *         @arg @ref LL_COMP_INPUT_MINUS_IO14
  *         @arg @ref LL_COMP_INPUT_MINUS_IO15
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputMinus(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CSR, COMP_CSR_INNSEL));
}

/**
  * @}
  */


/** @defgroup COMP_LL_EF_Configuration_comparator_vref Configuration of comparator Vref
  * @{
  */

/**
  * @brief Set comparator VrefCmp voltage divider configuration.  
  * @rmtoll CSR      COMP_CSR_COMP_VCDIV      LL_COMP_SetVrefCmpDivider
  * @param  COMPx Comparator instance    
  * @param  VrefCmpDiv can be one of the following values:
  *         @arg @ref LL_COMP_VREFCMP_DIV_1_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_2_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_3_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_4_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_5_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_6_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_7_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_8_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_9_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_10_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_11_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_12_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_13_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_14_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_15_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_17_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_18_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_19_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_20_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_21_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_22_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_23_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_24_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_25_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_26_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_27_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_28_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_29_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_30_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_31_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_32_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_33_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_34_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_35_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_36_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_37_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_38_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_39_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_40_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_41_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_42_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_43_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_44_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_45_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_46_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_47_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_48_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_49_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_50_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_51_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_52_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_53_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_54_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_55_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_56_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_57_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_58_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_59_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_60_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_61_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_62_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_63_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_VREFCMP
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetVrefCmpDivider(COMP_TypeDef *COMPx, uint32_t VrefCmpDiv)
{
  MODIFY_REG(COMP1->CSR, COMP_CSR_VCDIV, VrefCmpDiv);
}

/**
  * @brief Get comparator VREFCMP voltage divider configuration.
  * @rmtoll CSR      VCDIV      LL_COMP_GetVrefCmpDivider
  * @param  COMPx Comparator instance       
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_VREFCMP_DIV_1_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_2_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_3_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_4_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_5_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_6_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_7_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_8_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_9_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_10_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_11_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_12_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_13_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_14_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_15_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_17_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_18_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_19_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_20_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_21_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_22_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_23_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_24_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_25_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_26_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_27_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_28_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_29_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_30_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_31_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_32_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_33_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_34_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_35_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_36_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_37_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_38_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_39_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_40_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_41_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_42_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_43_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_44_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_45_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_46_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_47_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_48_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_49_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_50_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_51_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_52_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_53_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_54_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_55_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_56_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_57_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_58_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_59_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_60_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_61_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_62_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_63_64VREFCMP
  *         @arg @ref LL_COMP_VREFCMP_DIV_VREFCMP
  */
__STATIC_INLINE uint32_t LL_COMP_GetVrefCmpDivider(COMP_TypeDef *COMPx)
{
   return (uint32_t)(READ_BIT(COMP1->CSR, COMP_CSR_VCDIV));
}

/**
  * @brief  Set comparator VrefCmp reference source selection. 
  * @rmtoll CSR      VCSEL      LL_COMP_SetVrefCmpSource
  * @param  COMPx Comparator instance       
  * @param  VrefCmpSource can be one of the following values:
  *         @arg @ref LL_COMP_VREFCMP_SOURCE_NONE
  *         @arg @ref LL_COMP_VREFCMP_SOURCE_VCC
  *         @arg @ref LL_COMP_VREFCMP_SOURCE_VREFBUF
  *         @arg @ref LL_COMP_VREFCMP_SOURCE_VREF1P2V
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetVrefCmpSource(COMP_TypeDef *COMPx, uint32_t VrefCmpSource)
{
  MODIFY_REG(COMP1->CSR, COMP_CSR_VCSEL, VrefCmpSource);
}

/**
  * @brief  Get comparator VrefCmp reference source selection.
  * @rmtoll CSR      VCSEL      LL_COMP_GetVrefCmpSource
  * @param  COMPx Comparator instance       
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_VREFCMP_SOURCE_NONE
  *         @arg @ref LL_COMP_VREFCMP_SOURCE_VCC
  *         @arg @ref LL_COMP_VREFCMP_SOURCE_VREFBUF
  *         @arg @ref LL_COMP_VREFCMP_SOURCE_VREF1P2V
  */
__STATIC_INLINE uint32_t LL_COMP_GetVrefCmpSource(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMP1->CSR, COMP_CSR_VCSEL));
}

/**
  * @}
  */


/** @defgroup COMP_LL_EF_Configuration_comparator_Hysteresis Configuration of comparator Hysteresis
  * @{
  */
/**
  * @brief  Set comparator instance hysteresis mode of the input minus (inverting input).
  * @rmtoll CSR      HYST           LL_COMP_SetInputHysteresis
  * @param  COMPx Comparator instance
  * @param  InputHysteresis This parameter can be one of the following values:
  *         @arg @ref LL_COMP_HYSTERESIS_DISABLE
  *         @arg @ref LL_COMP_HYSTERESIS_ENABLE
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetInputHysteresis(COMP_TypeDef *COMPx, uint32_t InputHysteresis)
{
  if(InputHysteresis == LL_COMP_HYSTERESIS_ENABLE)
  {
    if(COMPx == COMP1)
    {
      SET_BIT(COMPx->CSR, COMP1_CSR_HYST);
    }
    else
    {
      SET_BIT(COMPx->CSR, COMP2_CSR_HYST);
    }
  }
  else
  {
    if(COMPx == COMP1)
    {
      CLEAR_BIT(COMPx->CSR, COMP1_CSR_HYST);
    }
    else
    {
      CLEAR_BIT(COMPx->CSR, COMP2_CSR_HYST);
    }    
  }
}

/**
  * @brief  Get comparator instance hysteresis mode of the minus (inverting) input.
  * @rmtoll CSR      HYST           LL_COMP_GetInputHysteresis
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_HYSTERESIS_DISABLE
  *         @arg @ref LL_COMP_HYSTERESIS_ENABLE
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputHysteresis(COMP_TypeDef *COMPx)
{ 
  if(COMPx==COMP1)
  {
    return ((READ_BIT(COMPx->CSR, COMP1_CSR_HYST)==COMP1_CSR_HYST) ? LL_COMP_HYSTERESIS_ENABLE : LL_COMP_HYSTERESIS_DISABLE);
  }
  else
  {
    return ((READ_BIT(COMPx->CSR, COMP2_CSR_HYST)==COMP2_CSR_HYST) ? LL_COMP_HYSTERESIS_ENABLE : LL_COMP_HYSTERESIS_DISABLE);
  }      
}
/**
  * @}
  */


/** @defgroup COMP_LL_EF_Configuration_comparator_modes Configuration of comparator modes
  * @{
  */

/**
  * @brief  Set comparator instance operating mode to adjust power and speed.
  * @rmtoll CSR      PWRMODE        LL_COMP_SetPowerMode
  * @param  COMPx Comparator instance
  * @param  PowerMode This parameter can be one of the following values:
  *         @arg @ref LL_COMP_POWERMODE_HIGHSPEED
  *         @arg @ref LL_COMP_POWERMODE_MEDIUMSPEED
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetPowerMode(COMP_TypeDef *COMPx, uint32_t PowerMode)
{
  MODIFY_REG(COMPx->CSR, COMP_CSR_PWRMODE, PowerMode);
}

/**
  * @brief  Get comparator instance operating mode to adjust power and speed.
  * @rmtoll CSR      PWRMODE        LL_COMP_GetPowerMode
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_POWERMODE_HIGHSPEED
  *         @arg @ref LL_COMP_POWERMODE_MEDIUMSPEED
  */
__STATIC_INLINE uint32_t LL_COMP_GetPowerMode(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CSR, COMP_CSR_PWRMODE));
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_Configuration_comparator_output Configuration of comparator output
  * @{
  */

/**
  * @brief  Set comparator instance output polarity.
  * @rmtoll CSR      POLARITY       LL_COMP_SetOutputPolarity
  * @param  COMPx Comparator instance
  * @param  OutputPolarity This parameter can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUTPOL_NONINVERTED
  *         @arg @ref LL_COMP_OUTPUTPOL_INVERTED
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetOutputPolarity(COMP_TypeDef *COMPx, uint32_t OutputPolarity)
{
  MODIFY_REG(COMPx->CSR, COMP_CSR_POLARITY, OutputPolarity);
}

/**
  * @brief  Get comparator instance output polarity.
  * @rmtoll CSR      POLARITY       LL_COMP_GetOutputPolarity
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUTPOL_NONINVERTED
  *         @arg @ref LL_COMP_OUTPUTPOL_INVERTED
  */
__STATIC_INLINE uint32_t LL_COMP_GetOutputPolarity(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CSR, COMP_CSR_POLARITY));
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_Operation Operation on comparator instance
  * @{
  */

/**
  * @brief  Enable comparator instance.
  * @note   After enable from off state, comparator requires a delay
  *         to reach reach propagation delay specification.
  *         Refer to device datasheet, parameter "tSTART".
  * @rmtoll CSR      EN             LL_COMP_Enable
  * @param  COMPx Comparator instance
  * @retval None
  */
__STATIC_INLINE void LL_COMP_Enable(COMP_TypeDef *COMPx)
{
  SET_BIT(COMPx->CSR, COMP_CSR_EN);
}


/**
  * @brief  Disable comparator instance.
  * @rmtoll CSR      EN             LL_COMP_Disable
  * @param  COMPx Comparator instance
  * @retval None
  */
__STATIC_INLINE void LL_COMP_Disable(COMP_TypeDef *COMPx)
{
  CLEAR_BIT(COMPx->CSR, COMP_CSR_EN);
}

/**
  * @brief  Get comparator enable state
  *         (0: COMP is disabled, 1: COMP is enabled)
  * @rmtoll CSR      EN             LL_COMP_IsEnabled
  * @param  COMPx Comparator instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_COMP_IsEnabled(COMP_TypeDef *COMPx)
{
  return ((READ_BIT(COMPx->CSR, COMP_CSR_EN) == (COMP_CSR_EN)) ? 1U : 0U);
}

/**
  * @brief  Read comparator instance output level.
  * @note   The comparator output level depends on the selected polarity
  *         (Refer to function @ref LL_COMP_SetOutputPolarity()).
  *         If the comparator polarity is not inverted:
  *          - Comparator output is low when the input plus
  *            is at a lower voltage than the input minus
  *          - Comparator output is high when the input plus
  *            is at a higher voltage than the input minus
  *         If the comparator polarity is inverted:
  *          - Comparator output is high when the input plus
  *            is at a lower voltage than the input minus
  *          - Comparator output is low when the input plus
  *            is at a higher voltage than the input minus
  * @rmtoll CSR      COMP_CSR_COMP_OUT       LL_COMP_ReadOutputLevel
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUT_LEVEL_LOW
  *         @arg @ref LL_COMP_OUTPUT_LEVEL_HIGH   
  */
__STATIC_INLINE uint32_t LL_COMP_ReadOutputLevel(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CSR, COMP_CSR_COMP_OUT)>> LL_COMP_OUTPUT_LEVEL_BITOFFSET_POS);
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_DigitalFilter DigitalFilter on comparator instance
  * @{
  */
/**
  * @brief  Enable comparator DigitalFilter.
  * @rmtoll FR       FLTEN          LL_COMP_EnableDigitalFilter
  * @param  COMPx Comparator instance   
  * @retval None
  */
__STATIC_INLINE void LL_COMP_EnableDigitalFilter(COMP_TypeDef *COMPx)
{
  SET_BIT(COMPx->FR, COMP_FR_FLTEN);
}

/**
  * @brief  Disable comparator DigitalFilter.
  * @rmtoll FR       FLTEN          LL_COMP_DisableDigitalFilter
  * @param  COMPx Comparator instance   
  * @retval None
  */
__STATIC_INLINE void LL_COMP_DisableDigitalFilter(COMP_TypeDef *COMPx)
{
  CLEAR_BIT(COMPx->FR, COMP_FR_FLTEN);
}

/**
  * @brief  Get comparator DigitalFilter state
  *         (0: Filter is Disabled, 1: Filter is Enabled).
  * @rmtoll FR       FLTEN          LL_COMP_IsEnabledDigitalFilter
  * @param  COMPx Comparator instance    
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_COMP_IsEnabledDigitalFilter(COMP_TypeDef *COMPx)
{
  return ((READ_BIT(COMPx->FR, COMP_FR_FLTEN) == (COMP_FR_FLTEN)) ? 1U : 0U);
}

/**
  * @brief  Set comparator DigitalFilter Value.
  * @rmtoll FR       FLTCNT         LL_COMP_SetDigitalFilter
  * @param  COMPx Comparator instance      
  * @param  FLTCNTValue Value between Min_Data=0x0000 and Max_Data=0xFFFF
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetDigitalFilter(COMP_TypeDef *COMPx,uint32_t FLTCNTValue)
{
  MODIFY_REG(COMPx->FR,COMP_FR_FLTCNT,FLTCNTValue << COMP_FR_FLTCNT_Pos);
}

/**
  * @brief  Get comparator DigitalFilter Value
  * @rmtoll FR       FLTCNT         LL_COMP_GetDigitalFilter
  * @param  COMPx Comparator instance          
  * @retval DigitalFilter Value between Min_Data=0x0000 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_COMP_GetDigitalFilter(COMP_TypeDef *COMPx)
{
    return (uint32_t)(READ_REG(COMPx->FR)>>COMP_FR_FLTCNT_Pos);
}


/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup COMP_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_COMP_DeInit(COMP_TypeDef *COMPx);
ErrorStatus LL_COMP_Init(COMP_TypeDef *COMPx, LL_COMP_InitTypeDef *COMP_InitStruct);
void        LL_COMP_StructInit(LL_COMP_InitTypeDef *COMP_InitStruct);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* COMP1 || COMP2 || COMP3 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PY32F040_LL_COMP_H */


/************************ (C) COPYRIGHT Puya *****END OF FILE****/
