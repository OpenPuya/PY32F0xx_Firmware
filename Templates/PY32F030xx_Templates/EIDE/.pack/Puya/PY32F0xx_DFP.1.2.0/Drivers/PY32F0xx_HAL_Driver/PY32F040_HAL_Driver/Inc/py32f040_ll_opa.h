/**
  ******************************************************************************
  * @file    py32f040_ll_opa.h
  * @author  MCU Application Team
  * @brief   Header file of OPA LL module.
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
#ifndef __PY32F040_LL_OPA_H
#define __PY32F040_LL_OPA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx.h"

/** @addtogroup PY32F040_LL_Driver
  * @{
  */

#if defined (OPA) 

/** @defgroup OPA_LL OPA
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup OPA_LL_Private_Constants OPA Private Constants
  * @{
  */


/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup OPA_LL_Private_Macros OPA Private Macros
  * @{
  */
  
/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)


#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup OPA_LL_Exported_Functions OPA Exported Functions
  * @{
  */

/** @defgroup OPA_LL_EF_CONFIGURATION_OPA_INSTANCE Configuration of OPA hierarchical scope: OPA instance
  * @{
  */

/**
  * @brief  Enable the OPA1.
  * @rmtoll CR1      EN1              LL_OPA1_Enable
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA1_Enable(OPA_TypeDef *OPAx)
{
  SET_BIT(OPAx->CR1, OPA_CR1_EN1);
}

/**
  * @brief  Disable the OPA1.
  * @rmtoll CR1      EN1              LL_OPA1_Disable
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA1_Disable(OPA_TypeDef *OPAx)
{
  CLEAR_BIT(OPAx->CR1, OPA_CR1_EN1);
}

/**
  * @brief  Get the OPA1 Enable state.
  * @rmtoll CR1      EN1              LL_OPA1_IsEnabled
  * @param  OPAx OPA instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_OPA1_IsEnabled(OPA_TypeDef *OPAx)
{
  return (READ_BIT(OPAx->CR1, OPA_CR1_EN1) == OPA_CR1_EN1);
}

/**
  * @brief  Enable the output of OPA1.
  * @rmtoll CR0      OP1OEN1          LL_OPA1_EnableOutput
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA1_EnableOutput(OPA_TypeDef *OPAx)
{
  SET_BIT(OPAx->CR0, OPA_CR0_OP1OEN1);
}

/**
  * @brief  Disable the output of OPA1.
  * @rmtoll CR0      OP1OEN1          LL_OPA1_DisableOutput
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA1_DisableOutput(OPA_TypeDef *OPAx)
{
  CLEAR_BIT(OPAx->CR0, OPA_CR0_OP1OEN1);
}

/**
  * @brief  Get the OPA1 Output state.
  * @rmtoll CR0      OP1OEN1          LL_OPA1_IsEnabledOutput
  * @param  OPAx OPA instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_OPA1_IsEnabledOutput(OPA_TypeDef *OPAx)
{
  return (READ_BIT(OPAx->CR0, OPA_CR0_OP1OEN1) == OPA_CR0_OP1OEN1);
}

/**
  * @brief  Enable the OPA2.
  * @rmtoll CR1      EN2              LL_OPA2_Enable
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA2_Enable(OPA_TypeDef *OPAx)
{
  SET_BIT(OPAx->CR1, OPA_CR1_EN2);
}

/**
  * @brief  Disable the OPA2.
  * @rmtoll CR1      EN2              LL_OPA2_Disable
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA2_Disable(OPA_TypeDef *OPAx)
{
  CLEAR_BIT(OPAx->CR1, OPA_CR1_EN2);
}

/**
  * @brief  Get the OPA2 Enable state.
  * @rmtoll CR1      EN2              LL_OPA2_IsEnabled
  * @param  OPAx OPA instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_OPA2_IsEnabled(OPA_TypeDef *OPAx)
{
  return (READ_BIT(OPAx->CR1, OPA_CR1_EN2) == OPA_CR1_EN2);
}

/**
  * @brief  Enable the OPA.
  * @rmtoll CR0      OP2OEN1          LL_OPA2_EnableOutput
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA2_EnableOutput(OPA_TypeDef *OPAx)
{
  SET_BIT(OPAx->CR0, OPA_CR0_OP2OEN1);
}

/**
  * @brief  Disable the the output of OPA2.
  * @rmtoll CR0      OP2OEN1          LL_OPA2_DisableOutput
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA2_DisableOutput(OPA_TypeDef *OPAx)
{
  CLEAR_BIT(OPAx->CR0, OPA_CR0_OP2OEN1);
}

/**
  * @brief Get the OPA2 Output state.
  * @rmtoll CR0      OP2OEN1          LL_OPA2_IsEnabledOutput
  * @param  OPAx OPA instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_OPA2_IsEnabledOutput(OPA_TypeDef *OPAx)
{
  return (READ_BIT(OPAx->CR0, OPA_CR0_OP2OEN1) == OPA_CR0_OP2OEN1);
}

#if defined(OPA_CR1_EN3)
/**
  * @brief  Enable the OPA3.
  * @rmtoll CR1      EN3              LL_OPA3_Enable
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA3_Enable(OPA_TypeDef *OPAx)
{
  SET_BIT(OPAx->CR1, OPA_CR1_EN3);
}

/**
  * @brief  Disable the OPA3.
  * @rmtoll CR1      EN3              LL_OPA3_Disable
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA3_Disable(OPA_TypeDef *OPAx)
{
  CLEAR_BIT(OPAx->CR1, OPA_CR1_EN3);
}

/**
  * @brief  Get the OPA3 Enable state.
  * @rmtoll CR1      EN3              LL_OPA3_IsEnabled
  * @param  OPAx OPA instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_OPA3_IsEnabled(OPA_TypeDef *OPAx)
{
  return (READ_BIT(OPAx->CR1, OPA_CR1_EN3) == OPA_CR1_EN3);
}

/**
  * @brief  Enable the output of OPA3.
  * @rmtoll CR0      OP3OEN1          LL_OPA3_EnableOutput
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA3_EnableOutput(OPA_TypeDef *OPAx)
{
  SET_BIT(OPAx->CR0, OPA_CR0_OP3OEN1); 
}

/**
  * @brief  Disable the output of OPA3.
  * @rmtoll CR0      OP3OEN1          LL_OPA3_DisableOutput
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA3_DisableOutput(OPA_TypeDef *OPAx)
{
  CLEAR_BIT(OPAx->CR0, OPA_CR0_OP3OEN1);
}

/**
  * @brief  Get the OPA3 Output state.
  * @rmtoll CR0      OP3OEN1          LL_OPA3_IsEnabledOutput
  * @param  OPAx OPA instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_OPA3_IsEnabledOutput(OPA_TypeDef *OPAx)
{
  return (READ_BIT(OPAx->CR0, OPA_CR0_OP3OEN1) == OPA_CR0_OP3OEN1);
}
#endif /* OPA_CR1_EN3 */

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup OPA_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

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

#endif /* OPA */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PY32F040_LL_OPA_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
