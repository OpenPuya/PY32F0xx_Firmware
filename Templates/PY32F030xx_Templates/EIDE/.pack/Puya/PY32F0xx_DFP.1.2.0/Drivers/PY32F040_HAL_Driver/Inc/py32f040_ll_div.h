/**
  ******************************************************************************
  * @file    py32f040_ll_div.h
  * @author  MCU Application Team
  * @brief   Header file of DIV LL module.
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
#ifndef PY32F040_LL_DIV_H
#define PY32F040_LL_DIV_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx.h"

/** @addtogroup PY32F040_LL_Driver
  * @{
  */

#if defined (DIV)

/** @defgroup DIV_LL DIV
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup DIV_LL_Exported_Constants DIV Exported Constants
  * @{
  */

/** @defgroup DIV_LL_EC_MODE Sign mode Selection
  * @{
  */
#define LL_DIV_MODE_UNSIGNED             0x00000000U
#define LL_DIV_MODE_SIGNED               DIV_SIGN_DIV_SIGN
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup DIV_LL_Exported_Macros DIV Exported Macros
  * @{
  */
/** @defgroup DIV_LL_EM_WRITE_READ Common Write and read registers macros
  * @{
  */
/**
  * @brief  Write a value in DIV register
  * @param  __INSTANCE__ DIV Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_DIV_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in DIV register
  * @param  __INSTANCE__ DIV Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_DIV_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup DIV_LL_Exported_Functions DIV Exported Functions
  * @{
  */

/**
  * @brief  Set the DIV sign.
  * @param  DIVx DIV Instance
  * @param  Sign This parameter can be one of the following values:
  *         @arg @ref LL_DIV_MODE_UNSIGNED
  *         @arg @ref LL_DIV_MODE_SIGNED
  * @retval None
  */
__STATIC_INLINE void LL_DIV_SetSign(DIV_TypeDef *DIVx, uint32_t Sign)
{
  MODIFY_REG(DIVx->SIGN, DIV_SIGN_DIV_SIGN, Sign);
}

/**
  * @brief  Get the DIV sign.
  * @param  DIVx DIV Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DIV_MODE_UNSIGNED
  *         @arg @ref LL_DIV_MODE_SIGNED
  */
__STATIC_INLINE uint32_t LL_DIV_GetSign(DIV_TypeDef *DIVx)
{
  return (uint32_t)(READ_BIT(DIVx->SIGN, DIV_SIGN_DIV_SIGN));
}

/**
  * @brief  Set the DIV Dividend value.
  * @param  DIVx DIV Instance
  * @param  Dividend This parameter must be a number between Min_Data = 0x00000000 and Max_Data = 0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void LL_DIV_SetDividend(DIV_TypeDef *DIVx, int32_t Dividend)
{
  WRITE_REG(DIVx->DEND, Dividend);
}

/**
  * @brief  Get the DIV Dividend value.
  * @param  DIVx DIV Instance
  * @retval Returned value is a number between Min_Data = 0x00000000 and Max_Data = 0xFFFFFFFF
  */
__STATIC_INLINE int32_t LL_DIV_GetDividend(DIV_TypeDef *DIVx)
{
  return (int32_t)(READ_REG(DIVx->DEND));
}


/**
  * @brief  Set the DIV Divisor value.
  * @param  DIVx DIV Instance
  * @param  Divisor This parameter must be a number between Min_Data = 0x00000000 and Max_Data = 0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void LL_DIV_SetDivisor(DIV_TypeDef *DIVx, int32_t Divisor)
{
  WRITE_REG(DIVx->SOR, Divisor);
}

/**
  * @brief  Get the DIV Divisor value.
  * @param  DIVx DIV Instance
  * @retval Returned value is a number between Min_Data = 0x00000000 and Max_Data = 0xFFFFFFFF
  */
__STATIC_INLINE int32_t LL_DIV_GetDivisor(DIV_TypeDef *DIVx)
{
  return (int32_t)(READ_REG(DIVx->SOR));
}

/**
  * @brief  Get the DIV Quotient value.
  * @param  DIVx DIV Instance
  * @retval Returned value is a number between Min_Data = 0x00000000 and Max_Data = 0xFFFFFFFF
  */
__STATIC_INLINE int32_t LL_DIV_GetQuotient(DIV_TypeDef *DIVx)
{
  return (int32_t)(READ_REG(DIVx->QUOT));
}

/**
  * @brief  Get the DIV Remainder value.
  * @param  DIVx DIV Instance
  * @retval Returned value is a number between Min_Data = 0x00000000 and Max_Data = 0xFFFFFFFF
  */
__STATIC_INLINE int32_t LL_DIV_GetRemainder(DIV_TypeDef *DIVx)
{
  return (int32_t)(READ_REG(DIVx->REMA));
}

/**
  * @brief  Check if Divide by zero warning flag bit is set.
  * @param  DIVx DIV Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DIV_IsActiveFlag_DIV_ZERO(DIV_TypeDef *DIVx)
{
  return ((READ_BIT(DIVx->STAT, DIV_STAT_DIV_ZERO) == (DIV_STAT_DIV_ZERO)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Division operation end flag bit is set.
  * @param  DIVx DIV Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DIV_IsActiveFlag_DIV_END(DIV_TypeDef *DIVx)
{
  return ((READ_BIT(DIVx->STAT, DIV_STAT_DIV_END) == (DIV_STAT_DIV_END)) ? 1UL : 0UL);
}


/**
  * @}
  */


/**
  * @}
  */

#endif /* DIV */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PY32F040_LL_DIV_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
