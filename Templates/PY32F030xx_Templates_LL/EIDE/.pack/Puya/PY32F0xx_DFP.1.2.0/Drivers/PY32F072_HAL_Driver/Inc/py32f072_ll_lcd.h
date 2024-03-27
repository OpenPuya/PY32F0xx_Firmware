/**
  ******************************************************************************
  * @file    py32f072_ll_lcd.h
  * @author  MCU Application Team
  * @brief   Header file of LCD LL module.
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
#ifndef __PY32F072_LL_LCD_H
#define __PY32F072_LL_LCD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx.h"
/** @addtogroup PY32F072_LL_Driver
  * @{
  */

#if defined (LCD)

/** @defgroup LCD_LL LCD
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup LCD_LL_ES_INIT LCD Exported Init structures
  * @{
  */

/**
  * @brief LL LCD Init Structure definition
  */
typedef struct
{
  uint32_t Contrast;        /*!< Configures the LCD Contrast.
                                 This parameter can be one value of @ref LCD_LL_EC_Contrast */
  uint32_t BiasSrc;         /*!< Configures the LCD Bias Source.
                                 This parameter can be one value of @ref LCD_LL_EC_BiasSource */
  uint32_t Duty;            /*!< Configures the LCD Duty.
                                 This parameter can be one value of @ref LCD_LL_EC_Duty */
  uint32_t Bias;            /*!< Configures the LCD Bias.
                                 This parameter can be one value of @ref LCD_LL_EC_Bias */
  uint32_t ScanFre;         /*!< Configures the LCD Scan Frequency.
                                 This parameter can be one value of @ref LCD_LL_EC_ScanFrequency */
  uint32_t Mode;            /*!< Configures the LCD Mode.
                                 This parameter can be one value of @ref LCD_LL_EC_Mode */
}LL_LCD_InitTypeDef;

/** 
  * @brief  LCD SEG COM port output enable configuration
  */
typedef struct
{
    uint32_t Seg0_31;
    union{
        uint32_t Seg32_39_Com0_7;
        struct
        {
            uint32_t Seg32_35     :4;
            uint32_t Seg36Com7    :1;
            uint32_t Seg37Com6    :1;
            uint32_t Seg38Com5    :1;
            uint32_t Seg39Com4    :1;
            uint32_t Com0_3       :4;
            uint32_t Mux          :1;
        }SegComBit;
    }Seg32_39_Com0_7_t;
}LL_LCD_SegComTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup LCD_LL_Exported_Constants LCD Exported Constants
  * @{
  */

/** @defgroup LCD_LL_EC_Contrast LCD Contrast
  * @{
  */
#define LL_LCD_CONTRASTLEVEL_0               ((uint32_t)0x00000000U)
#define LL_LCD_CONTRASTLEVEL_1               (LCD_CR0_CONTRAST_0)
#define LL_LCD_CONTRASTLEVEL_2               (LCD_CR0_CONTRAST_1)
#define LL_LCD_CONTRASTLEVEL_3               (LCD_CR0_CONTRAST_1 | LCD_CR0_CONTRAST_0)
#define LL_LCD_CONTRASTLEVEL_4               (LCD_CR0_CONTRAST_2)
#define LL_LCD_CONTRASTLEVEL_5               (LCD_CR0_CONTRAST_2 | LCD_CR0_CONTRAST_0)
#define LL_LCD_CONTRASTLEVEL_6               (LCD_CR0_CONTRAST_2 | LCD_CR0_CONTRAST_1)
#define LL_LCD_CONTRASTLEVEL_7               (LCD_CR0_CONTRAST_2 | LCD_CR0_CONTRAST_1 | LCD_CR0_CONTRAST_0)
#define LL_LCD_CONTRASTLEVEL_8               (LCD_CR0_CONTRAST_3)
#define LL_LCD_CONTRASTLEVEL_9               (LCD_CR0_CONTRAST_3 | LCD_CR0_CONTRAST_0)
#define LL_LCD_CONTRASTLEVEL_10              (LCD_CR0_CONTRAST_3 | LCD_CR0_CONTRAST_1)
#define LL_LCD_CONTRASTLEVEL_11              (LCD_CR0_CONTRAST_3 | LCD_CR0_CONTRAST_1 | LCD_CR0_CONTRAST_0)
#define LL_LCD_CONTRASTLEVEL_12              (LCD_CR0_CONTRAST_3 | LCD_CR0_CONTRAST_2)
#define LL_LCD_CONTRASTLEVEL_13              (LCD_CR0_CONTRAST_3 | LCD_CR0_CONTRAST_2 | LCD_CR0_CONTRAST_0)
#define LL_LCD_CONTRASTLEVEL_14              (LCD_CR0_CONTRAST_3 | LCD_CR0_CONTRAST_2 | LCD_CR0_CONTRAST_1)
#define LL_LCD_CONTRASTLEVEL_15              (LCD_CR0_CONTRAST_3 | LCD_CR0_CONTRAST_2 | LCD_CR0_CONTRAST_1 | LCD_CR0_CONTRAST_0)
/**
  * @}
  */

/** @defgroup LCD_LL_EC_BiasSource LCD Bias Source
  * @{
  */
#define LL_LCD_BIAS_SRC_IN_RES_HIGH_POWER     (LCD_CR0_BSEL_2 | LCD_CR0_BSEL_1) /* Internal resistance partial voltage, high power consumption mode */
#define LL_LCD_BIAS_SRC_IN_RES_LOW_POWER      (LCD_CR0_BSEL_2)                  /* Internal resistance partial voltage, low power consumption mode */
#define LL_LCD_BIAS_SRC_IN_RES_MID_POWER      (LCD_CR0_BSEL_1)                  /* Internal resistance partial voltage, medium power consumption mode */
#define LL_LCD_BIAS_SRC_EXT_RES               ((uint32_t)0x00000000U)           /* External resistance mode */
/**
  * @}
  */

/** @defgroup LCD_LL_EC_Duty LCD Duty
  * @{
  */
#define LL_LCD_DUTY_STATIC                 ((uint32_t)0x00000000U)                              /*!< Static duty */
#define LL_LCD_DUTY_1_2                    (LCD_CR0_DUTY_0)                                     /*!< 1/2 duty    */
#define LL_LCD_DUTY_1_3                    (LCD_CR0_DUTY_1)                                     /*!< 1/3 duty    */
#define LL_LCD_DUTY_1_4                    ((LCD_CR0_DUTY_1 | LCD_CR0_DUTY_0))                  /*!< 1/4 duty    */
#define LL_LCD_DUTY_1_6                    ((LCD_CR0_DUTY_2 | LCD_CR0_DUTY_0))                  /*!< 1/6 duty    */
#define LL_LCD_DUTY_1_8                    ((LCD_CR0_DUTY_2 | LCD_CR0_DUTY_1 | LCD_CR0_DUTY_0)) /*!< 1/8 duty    */
/**
  * @}
  */

/** @defgroup LCD_LL_EC_Bias LCD Bias Source
  * @{
  */
#define LL_LCD_BIAS_1_3                    ((uint32_t)0x00000000U) /*!< 1/3 Bias */
#define LL_LCD_BIAS_1_2                    (LCD_CR0_BIAS)          /*!< 1/2 Bias */
/**
  * @}
  */

/** @defgroup LCD_LL_EC_ScanFrequency LCD Scan Frequency
  * @{
  */
#define LL_LCD_SCAN_FRE_64HZ               ((uint32_t)0x00000000U)
#define LL_LCD_SCAN_FRE_128HZ              (LCD_CR0_LCDCLK_0)
#define LL_LCD_SCAN_FRE_256HZ              (LCD_CR0_LCDCLK_1)
#define LL_LCD_SCAN_FRE_512HZ              (LCD_CR0_LCDCLK_1 | LCD_CR0_LCDCLK_0)
/**
  * @}
  */

/** @defgroup LCD_LL_EC_Mode LCD Mode
  * @{
  */
#define LL_LCD_MODE_0                    ((uint32_t)0x00000000U)
#define LL_LCD_MODE_1                    (LCD_CR1_MODE)
/**
  * @}
  */

/** @defgroup LCD_LL_EC_RAMRegister LCD RAMRegister
  * @{
  */
#define LL_LCD_RAM_REGISTER0               ((uint32_t)0x00000000U) /*!< LCD RAM Register 0  */
#define LL_LCD_RAM_REGISTER1               ((uint32_t)0x00000001U) /*!< LCD RAM Register 1  */
#define LL_LCD_RAM_REGISTER2               ((uint32_t)0x00000002U) /*!< LCD RAM Register 2  */
#define LL_LCD_RAM_REGISTER3               ((uint32_t)0x00000003U) /*!< LCD RAM Register 3  */
#define LL_LCD_RAM_REGISTER4               ((uint32_t)0x00000004U) /*!< LCD RAM Register 4  */
#define LL_LCD_RAM_REGISTER5               ((uint32_t)0x00000005U) /*!< LCD RAM Register 5  */
#define LL_LCD_RAM_REGISTER6               ((uint32_t)0x00000006U) /*!< LCD RAM Register 6  */
#define LL_LCD_RAM_REGISTER7               ((uint32_t)0x00000007U) /*!< LCD RAM Register 7  */
#define LL_LCD_RAM_REGISTER8               ((uint32_t)0x00000008U) /*!< LCD RAM Register 8  */
#define LL_LCD_RAM_REGISTER9               ((uint32_t)0x00000009U) /*!< LCD RAM Register 9  */
#define LL_LCD_RAM_REGISTER10              ((uint32_t)0x0000000AU) /*!< LCD RAM Register 10 */
#define LL_LCD_RAM_REGISTER11              ((uint32_t)0x0000000BU) /*!< LCD RAM Register 11 */
#define LL_LCD_RAM_REGISTER12              ((uint32_t)0x0000000CU) /*!< LCD RAM Register 12 */
#define LL_LCD_RAM_REGISTER13              ((uint32_t)0x0000000DU) /*!< LCD RAM Register 13 */
#define LL_LCD_RAM_REGISTER14              ((uint32_t)0x0000000EU) /*!< LCD RAM Register 14 */
#define LL_LCD_RAM_REGISTER15              ((uint32_t)0x0000000FU) /*!< LCD RAM Register 15 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup LCD_LL_Exported_Macros LCD Exported Macros
  * @{
  */

/** @defgroup LCD_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in LCD register
  * @param  __INSTANCE__ LCD Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_LCD_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in LCD register
  * @param  __INSTANCE__ LCD Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_LCD_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */
  
/* Exported functions --------------------------------------------------------*/
/** @defgroup LCD_LL_Exported_Functions LCD Exported Functions
  * @{
  */

/**
  * @brief  Set LCD Contrast.
  * @param  LCDx LCD Instance
  * @param  Contrast This parameter can be one of the following values:
  *         @arg @ref LL_LCD_CONTRASTLEVEL_0
  *         @arg @ref LL_LCD_CONTRASTLEVEL_1
  *         @arg @ref LL_LCD_CONTRASTLEVEL_2
  *         @arg @ref LL_LCD_CONTRASTLEVEL_3
  *         @arg @ref LL_LCD_CONTRASTLEVEL_4
  *         @arg @ref LL_LCD_CONTRASTLEVEL_5
  *         @arg @ref LL_LCD_CONTRASTLEVEL_6
  *         @arg @ref LL_LCD_CONTRASTLEVEL_7
  *         @arg @ref LL_LCD_CONTRASTLEVEL_8
  *         @arg @ref LL_LCD_CONTRASTLEVEL_9
  *         @arg @ref LL_LCD_CONTRASTLEVEL_10
  *         @arg @ref LL_LCD_CONTRASTLEVEL_11
  *         @arg @ref LL_LCD_CONTRASTLEVEL_12
  *         @arg @ref LL_LCD_CONTRASTLEVEL_13
  *         @arg @ref LL_LCD_CONTRASTLEVEL_14
  *         @arg @ref LL_LCD_CONTRASTLEVEL_15
  * @retval None
  */
__STATIC_INLINE void LL_LCD_SetContrast(LCD_TypeDef *LCDx, uint32_t Contrast)
{
  MODIFY_REG(LCDx->CR0, LCD_CR0_CONTRAST, Contrast);
}

/**
  * @brief  Get LCD contrast.
  * @param  LCDx LCD Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LCD_CONTRASTLEVEL_0
  *         @arg @ref LL_LCD_CONTRASTLEVEL_1
  *         @arg @ref LL_LCD_CONTRASTLEVEL_2
  *         @arg @ref LL_LCD_CONTRASTLEVEL_3
  *         @arg @ref LL_LCD_CONTRASTLEVEL_4
  *         @arg @ref LL_LCD_CONTRASTLEVEL_5
  *         @arg @ref LL_LCD_CONTRASTLEVEL_6
  *         @arg @ref LL_LCD_CONTRASTLEVEL_7
  *         @arg @ref LL_LCD_CONTRASTLEVEL_8
  *         @arg @ref LL_LCD_CONTRASTLEVEL_9
  *         @arg @ref LL_LCD_CONTRASTLEVEL_10
  *         @arg @ref LL_LCD_CONTRASTLEVEL_11
  *         @arg @ref LL_LCD_CONTRASTLEVEL_12
  *         @arg @ref LL_LCD_CONTRASTLEVEL_13
  *         @arg @ref LL_LCD_CONTRASTLEVEL_14
  *         @arg @ref LL_LCD_CONTRASTLEVEL_15
  */
__STATIC_INLINE uint32_t LL_LCD_GetContrast(LCD_TypeDef *LCDx)
{
  return (uint32_t)(READ_BIT(LCDx->CR0, LCD_CR0_CONTRAST));
}

/**
  * @brief  Set LCD bias source.
  * @param  LCDx LCD Instance
  * @param  BiasSource This parameter can be one of the following values:
  *         @arg @ref LL_LCD_BIAS_SRC_IN_RES_HIGH_POWER
  *         @arg @ref LL_LCD_BIAS_SRC_IN_RES_LOW_POWER
  *         @arg @ref LL_LCD_BIAS_SRC_IN_RES_MID_POWER
  *         @arg @ref LL_LCD_BIAS_SRC_EXT_RES
  * @retval None
  */
__STATIC_INLINE void LL_LCD_SetBiasSource(LCD_TypeDef *LCDx, uint32_t BiasSource)
{
  MODIFY_REG(LCDx->CR0, LCD_CR0_BSEL, BiasSource);
}

/**
  * @brief  Get LCD bias source.
  * @param  LCDx LCD Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LCD_BIAS_SRC_IN_RES_HIGH_POWER
  *         @arg @ref LL_LCD_BIAS_SRC_IN_RES_LOW_POWER
  *         @arg @ref LL_LCD_BIAS_SRC_IN_RES_MID_POWER
  *         @arg @ref LL_LCD_BIAS_SRC_EXT_RES
  */
__STATIC_INLINE uint32_t LL_LCD_GetBiasSource(LCD_TypeDef *LCDx)
{
  return (uint32_t)(READ_BIT(LCDx->CR0, LCD_CR0_BSEL));
}

/**
  * @brief  Set LCD duty.
  * @param  LCDx LCD Instance
  * @param  Duty This parameter can be one of the following values:
  *         @arg @ref LL_LCD_DUTY_STATIC
  *         @arg @ref LL_LCD_DUTY_1_2
  *         @arg @ref LL_LCD_DUTY_1_3
  *         @arg @ref LL_LCD_DUTY_1_4
  *         @arg @ref LL_LCD_DUTY_1_6
  *         @arg @ref LL_LCD_DUTY_1_8
  * @retval None
  */
__STATIC_INLINE void LL_LCD_SetDuty(LCD_TypeDef *LCDx, uint32_t Duty)
{
  MODIFY_REG(LCDx->CR0, LCD_CR0_DUTY, Duty);
}

/**
  * @brief  Get LCD duty.
  * @param  LCDx LCD Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LCD_DUTY_STATIC
  *         @arg @ref LL_LCD_DUTY_1_2
  *         @arg @ref LL_LCD_DUTY_1_3
  *         @arg @ref LL_LCD_DUTY_1_4
  *         @arg @ref LL_LCD_DUTY_1_6
  *         @arg @ref LL_LCD_DUTY_1_8
  */
__STATIC_INLINE uint32_t LL_LCD_GetDuty(LCD_TypeDef *LCDx)
{
  return (uint32_t)(READ_BIT(LCDx->CR0, LCD_CR0_DUTY));
}

/**
  * @brief  Set LCD bias.
  * @param  LCDx LCD Instance
  * @param  Bias This parameter can be one of the following values:
  *         @arg @ref LL_LCD_BIAS_1_3
  *         @arg @ref LL_LCD_BIAS_1_2
  * @retval None
  */
__STATIC_INLINE void LL_LCD_SetBias(LCD_TypeDef *LCDx, uint32_t Bias)
{
  MODIFY_REG(LCDx->CR0, LCD_CR0_BIAS, Bias);
}

/**
  * @brief  Get LCD bias.
  * @param  LCDx LCD Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LCD_BIAS_1_3
  *         @arg @ref LL_LCD_BIAS_1_2
  */
__STATIC_INLINE uint32_t LL_LCD_GetBias(LCD_TypeDef *LCDx)
{
  return (uint32_t)(READ_BIT(LCDx->CR0, LCD_CR0_BIAS));
}

/**
  * @brief  Set LCD scan frequency.
  * @param  LCDx LCD Instance
  * @param  ScanFre This parameter can be one of the following values:
  *         @arg @ref LL_LCD_SCAN_FRE_64HZ
  *         @arg @ref LL_LCD_SCAN_FRE_128HZ
  *         @arg @ref LL_LCD_SCAN_FRE_256HZ
  *         @arg @ref LL_LCD_SCAN_FRE_512HZ
  * @retval None
  */
__STATIC_INLINE void LL_LCD_SetScanFre(LCD_TypeDef *LCDx, uint32_t ScanFre)
{
  MODIFY_REG(LCDx->CR0, LCD_CR0_LCDCLK, ScanFre);
}

/**
  * @brief  Get LCD scan frequency.
  * @param  LCDx LCD Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LCD_SCAN_FRE_64HZ
  *         @arg @ref LL_LCD_SCAN_FRE_128HZ
  *         @arg @ref LL_LCD_SCAN_FRE_256HZ
  *         @arg @ref LL_LCD_SCAN_FRE_512HZ
  */
__STATIC_INLINE uint32_t LL_LCD_GetScanFre(LCD_TypeDef *LCDx)
{
  return (uint32_t)(READ_BIT(LCDx->CR0, LCD_CR0_LCDCLK));
}

/**
  * @brief  Set LCD mode.
  * @param  LCDx LCD Instance
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_LCD_MODE_0
  *         @arg @ref LL_LCD_MODE_1
  * @retval None
  */
__STATIC_INLINE void LL_LCD_SetMode(LCD_TypeDef *LCDx, uint32_t Mode)
{
  MODIFY_REG(LCDx->CR1, LCD_CR1_MODE, Mode);
}

/**
  * @brief  Get LCD mode.
  * @param  LCDx LCD Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LCD_MODE_0
  *         @arg @ref LL_LCD_MODE_1
  */
__STATIC_INLINE uint32_t LL_LCD_GetMode(LCD_TypeDef *LCDx)
{
  return (uint32_t)(READ_BIT(LCDx->CR1, LCD_CR1_MODE));
}

/**
  * @brief  Enable LCD peripheral.
  * @param  LCDx LCD Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCD_Enable(LCD_TypeDef *LCDx)
{
  SET_BIT(LCDx->CR0, LCD_CR0_EN);
}

/**
  * @brief  Disable LCD peripheral.
  * @param  LCDx LCD Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCD_Disable(LCD_TypeDef *LCDx)
{
  CLEAR_BIT(LCDx->CR0, LCD_CR0_EN);
}

/**
  * @brief  Check if LCD peripheral is enabled
  * @param  LCDx LCD Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCD_IsEnabled(LCD_TypeDef *LCDx)
{
  return ((READ_BIT(LCDx->CR0, LCD_CR0_EN) == (LCD_CR0_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable LCD DMA.
  * @param  LCDx LCD Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCD_EnableDMA(LCD_TypeDef *LCDx)
{
  SET_BIT(LCDx->CR1, LCD_CR1_DMAEN);
}

/**
  * @brief  Disable LCD DMA.
  * @param  LCDx LCD Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCD_DisableDMA(LCD_TypeDef *LCDx)
{
  CLEAR_BIT(LCDx->CR1, LCD_CR1_DMAEN);
}

/**
  * @brief  Check if LCD DMA is enabled.
  * @param  LCDx LCD Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCD_IsEnabledDMA(LCD_TypeDef *LCDx)
{
  return ((READ_BIT(LCDx->CR1, LCD_CR1_DMAEN) == (LCD_CR1_DMAEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable LCD blink mode.
  * @param  LCDx LCD Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCD_EnableBlink(LCD_TypeDef *LCDx)
{
  SET_BIT(LCDx->CR1, LCD_CR1_BLINKEN);
}

/**
  * @brief  Disable LCD blink mode.
  * @param  LCDx LCD Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCD_DisableBlink(LCD_TypeDef *LCDx)
{
  CLEAR_BIT(LCDx->CR1, LCD_CR1_BLINKEN);
}

/**
  * @brief  Check if LCD blink mode is enabled.
  * @param  LCDx LCD Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCD_IsEnabledBlink(LCD_TypeDef *LCDx)
{
  return ((READ_BIT(LCDx->CR1, LCD_CR1_BLINKEN) == (LCD_CR1_BLINKEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the number of frames corresponding to LCD blink frequency and interrupt interval.
  * @param  LCDx LCD Instance
  * @param  Count Value between Min_Data=0x00 and Max_Data=0x3F
  * @retval None
  */
__STATIC_INLINE void LL_LCD_SetBlinkCount(LCD_TypeDef *LCDx, uint32_t Count)
{
  MODIFY_REG(LCDx->CR1, LCD_CR1_BLINKCNT, Count);
}

/**
  * @brief  Get the number of frames corresponding to LCD blink frequency and interrupt interval.
  * @param  LCDx LCD Instance
  * @retval Returned between Min_Data=0x00 and Max_Data=0x3F
  */
__STATIC_INLINE uint32_t LL_LCD_GetBlinkCount(LCD_TypeDef *LCDx)
{
  return (uint32_t)(READ_BIT(LCDx->CR1, LCD_CR1_BLINKCNT));
}

/**
  * @brief  Enable LCD interrupt.
  * @param  LCDx LCD Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCD_EnableIT(LCD_TypeDef *LCDx)
{
  SET_BIT(LCDx->CR1, LCD_CR1_IE);
}

/**
  * @brief  Disable LCD interrupt.
  * @param  LCDx LCD Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCD_DisableIT(LCD_TypeDef *LCDx)
{
  CLEAR_BIT(LCDx->CR1, LCD_CR1_IE);
}

/**
  * @brief  Check if LCD interrupt is enabled
  * @param  LCDx LCD Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCD_IsEnabledIT(LCD_TypeDef *LCDx)
{
  return ((READ_BIT(LCDx->CR1, LCD_CR1_IE) == (LCD_CR1_IE)) ? 1UL : 0UL);
}

/**
  * @brief  Get LCD interrupt flag.
  * @param  LCDx LCD Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCD_IsActiveFlag_INTF(LCD_TypeDef *LCDx)
{
  return ((READ_BIT(LCDx->CR1, LCD_CR1_INTF) == (LCD_CR1_INTF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear LCD interrupt flag.
  * @param  LCDx LCD Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCD_ClearFlag_INTF(LCD_TypeDef *LCDx)
{
  CLEAR_BIT(LCDx->INTCLR, LCD_INTCLR_INTF_CLR);
}

/**
  * @brief  Set LCD SEG COM port output enable.
  * @param  LCDx LCD Instance
  * @param  SegCom pointer to a LCD_SegComTypeDef structure that contains
  *         the configuration information for LCD SEG COM port output enable.
  * @retval None
  */
__STATIC_INLINE void LL_LCD_SetSegCom(LCD_TypeDef *LCDx, LL_LCD_SegComTypeDef *SegCom)
{
  WRITE_REG(LCDx->POEN0, SegCom->Seg0_31);
  WRITE_REG(LCDx->POEN1, SegCom->Seg32_39_Com0_7_t.Seg32_39_Com0_7);
}

/**
  * @brief  Writes a word in the specific LCD RAM.
  * @param  LCDx LCD Instance
  * @param  RAMRegisterIndex specifies the LCD RAM Register.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_LCD_RAM_REGISTER0
  *         @arg @ref LL_LCD_RAM_REGISTER1
  *         @arg @ref LL_LCD_RAM_REGISTER2
  *         @arg @ref LL_LCD_RAM_REGISTER3
  *         @arg @ref LL_LCD_RAM_REGISTER4
  *         @arg @ref LL_LCD_RAM_REGISTER5
  *         @arg @ref LL_LCD_RAM_REGISTER6
  *         @arg @ref LL_LCD_RAM_REGISTER7
  *         @arg @ref LL_LCD_RAM_REGISTER8
  *         @arg @ref LL_LCD_RAM_REGISTER9
  *         @arg @ref LL_LCD_RAM_REGISTER10
  *         @arg @ref LL_LCD_RAM_REGISTER11
  *         @arg @ref LL_LCD_RAM_REGISTER12
  *         @arg @ref LL_LCD_RAM_REGISTER13
  *         @arg @ref LL_LCD_RAM_REGISTER14
  *         @arg @ref LL_LCD_RAM_REGISTER15
  * @param  Data specifies LCD Data Value to be written.
  * @retval None
  */
__STATIC_INLINE void LL_LCD_Write(LCD_TypeDef *LCDx, uint32_t RAMRegisterIndex, uint32_t Data)
{
  WRITE_REG(LCDx->RAM[RAMRegisterIndex], Data);
}

/**
  * @brief  Clears the LCD RAM registers.
  * @param  LCDx LCD Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCD_Clear(LCD_TypeDef *LCDx)
{
  register uint32_t counter = 0U;
  for(counter = LL_LCD_RAM_REGISTER0; counter <= LL_LCD_RAM_REGISTER15; counter++)
  {
    LCDx->RAM[counter] = 0U;
  }
}
  
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup LCD_LL_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus LL_LCD_DeInit(LCD_TypeDef *LCDx);
ErrorStatus LL_LCD_Init(LCD_TypeDef *LCDx, LL_LCD_InitTypeDef *LCD_InitStruct);
void        LL_LCD_StructInit(LL_LCD_InitTypeDef *LCD_InitStruct);
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
  
#endif /* defined (LCD)*/
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PY32F072_LL_LCD_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
