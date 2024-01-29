/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef sConfig1,sConfig2,sConfig3;
TIM_BreakDeadTimeConfigTypeDef sBreakConfig;
uint32_t temp;
__IO uint32_t uwStep = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Error_Handler(void);
static void APP_TIM1_INIT(void);
static void APP_TIM1_PWM(void);
static void APP_TIM1_PWMBREAK(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();

  /* TIM1初始化*/
  APP_TIM1_INIT();

  /* TIM1 PWM配置 */
  APP_TIM1_PWM();

  /* 设置刹车和死区相关配置*/
  APP_TIM1_PWMBREAK();
  
  /*配置换相事件：软件方式*/
  HAL_TIMEx_ConfigCommutEvent_IT(&TimHandle, TIM_TS_NONE, TIM_COMMUTATION_SOFTWARE);
  
  /* 通道1开始输出PWM */
  if (HAL_TIM_OC_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)                  
  {
    Error_Handler();
  }

  /* 通道1N开启 */
  if (HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  /* 通道2开始输出PWM */
  if (HAL_TIM_OC_Start(&TimHandle, TIM_CHANNEL_2) != HAL_OK)                  
  {
    Error_Handler();
  }
  
  /* 通道2N开启 */
  if (HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }

  /* 通道3开始输出PWM */
  if (HAL_TIM_OC_Start(&TimHandle, TIM_CHANNEL_3) != HAL_OK)                  
  {
    Error_Handler();
  }

  /* 通道3N开启 */
  if (HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }

  /* 无限循环 */
  while (1)
  {
  }
}
/**
  * @brief  TIM1初始化函数
  * @param  无
  * @retval 无
  */
static void APP_TIM1_INIT(void)
{
  /* 选择TIM1 */
  TimHandle.Instance = TIM1;                                                  
  
  /* 自动重装载值 */
  TimHandle.Init.Period            = 1000 - 1;                                     

  /* 预分频为800-1 */
  TimHandle.Init.Prescaler         = 1 - 1;                                 

  /* 时钟不分频 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                  

  /* 向上计数*/
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                      
  
  /* 不重复计数 */
  TimHandle.Init.RepetitionCounter = 1 - 1;                                   

  /* 自动重装载寄存器没有缓冲 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;          

  /* 基础时钟初始化 */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                                
  {
    Error_Handler();
  }

}
/**
  * @brief  TIM1 PWM配置
  * @param  无
  * @retval 无
  */
static void APP_TIM1_PWM(void)
{
  /*输出配置为翻转模式 */
  sConfig1.OCMode       = TIM_OCMODE_PWM1;                                     

  /*OC通道输出高电平有效 */
  sConfig1.OCPolarity   = TIM_OCPOLARITY_HIGH;                                                                 

  /*OCN通道输出高电平有效 */
  sConfig1.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                

  /*空闲状态OC1N输出低电平 */
  sConfig1.OCNIdleState = TIM_OCNIDLESTATE_RESET;                              

  /*空闲状态OC1输出低电平*/
  sConfig1.OCIdleState  = TIM_OCIDLESTATE_RESET;                               

  sConfig1.OCFastMode   = TIM_OCFAST_DISABLE;                         /* 禁用快速模式 */

  /*设置通道1的占空比为 (1600/3200)=50% */
  sConfig1.Pulse = 500 - 1;                                              

  /* 通道1配置 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  sConfig2 = sConfig1;
  /* 设置通道2的占空比为 (800/3200)=25%*/
  sConfig2.Pulse = 250 - 1;                                               

  /* 通道2配置 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig2, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }

  sConfig3 = sConfig1;
  /* 设置通道1的占空比值为 (400/3200)=12.5% */
  sConfig3.Pulse = 125 - 1;                                              

  /* 通道3配置 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }

}

/**
  * @brief  设置刹车和死区相关配置
  * @param  无
  * @retval 无
  */
static void APP_TIM1_PWMBREAK(void)
{
  /*设置刹车和死区相关配置 */
  sBreakConfig.BreakState       = TIM_BREAK_ENABLE;                   

  /*设置死区时间*/
  sBreakConfig.DeadTime         = 1;                                  

  /*运行模式下关闭状态选择 OSSR=1*/
  sBreakConfig.OffStateRunMode  = TIM_OSSR_ENABLE;                    

  /*空闲状态下关闭状态选择 OSSI=1*/
  sBreakConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;                    

  /*锁定关闭*/
  sBreakConfig.LockLevel        = TIM_LOCKLEVEL_OFF;                  

  /*刹车输入低电平有效*/
  sBreakConfig.BreakPolarity    = TIM_BREAKPOLARITY_HIGH;             

  /*自动输出使能*/
  sBreakConfig.AutomaticOutput  = TIM_AUTOMATICOUTPUT_ENABLE;      

  /*刹车和死区状况配置*/
  if (HAL_TIMEx_ConfigBreakDeadTime(&TimHandle, &sBreakConfig) != HAL_OK)
  {
    Error_Handler();
  }

 


}

/**
  * @brief  换相事件执行函数，6步输出配置
  * @param  无
  * @retval 无
  */
void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim)
{
  if (uwStep == 0)
  {
    /*配置为PWM1*/
    sConfig1.OCMode     = TIM_OCMODE_PWM1;                             
    /*通道1配置为PWM*/
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1);   
    /*通道1输出PWM*/
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);                    
    /*PWM1N停止输出*/
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_1);                    

    /*配置为PWM1*/
    sConfig3.OCMode     = TIM_OCMODE_PWM1;                             
    /*通道3配置为PWM */
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3);   
    /*通道3N使能 */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_3);                   
    /*通道3PWM停止 */
    HAL_TIM_PWM_Stop(&TimHandle, TIM_CHANNEL_3);                      

    /*停止通道2 */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_2);                       
    /*停止通道2N */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_2);                   
    uwStep = 1;
  }

  else if (uwStep == 1)
  {
    /*配置为PWM1 */
    sConfig2.OCMode     = TIM_OCMODE_PWM1;                             
    /*通道2配置为PWM */
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig2, TIM_CHANNEL_2);   
    /*通道2N开始*/
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_2);                   
    /*停止通道3N */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_3);                   

    uwStep++;
  }

  else if (uwStep == 2)
  {
    /*配置为PWM1*/
    sConfig3.OCMode     = TIM_OCMODE_PWM1;                             
    /*通道3配置为PWM*/
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3);  
    /*通道3PWM启动*/
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_3);                     
 
    /*通道1输出关闭*/
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_1);                       

    uwStep++;
  }

  else if (uwStep == 3)
  {
    /*停止通道2N*/
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_2);                    
    /*配置为PWM1*/
    sConfig1.OCMode     = TIM_OCMODE_PWM1;                             
    /*通道1配置为PWM */
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1);  
    /*停止通道1N */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_1);      
 
    uwStep++;
  }
  else if (uwStep == 4)
  {
    /* 停止通道3 */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_3);                       

    /* 配置为PWM1 */
    sConfig2.OCMode     = TIM_OCMODE_PWM1;                             
    /*通道2配置为PWM */
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig2, TIM_CHANNEL_2);   
    /* 通道2PWM启动 */
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_2);                     

    uwStep++;
  }

  else if (uwStep == 5)
  {
    /* 配置为PWM1 */
    sConfig3.OCMode     = TIM_OCMODE_PWM1;                             
    /* 通道3配置为PWM */
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3);  
    /* 通道3NPWM启动 */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_3);                   

    /* 停止通道1N */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_1);                   

    uwStep++;
  }

  else
  {
    /* 配置为PWM1 */
    sConfig1.OCMode     = TIM_OCMODE_PWM1;                           
    /* 通道1配置为PWM*/
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1); 
    /*通道1输出PWM*/
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);                    

    /* 停止通道2 */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_2);                    

    uwStep = 1;
  }
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void Error_Handler(void)
{
  /* 无限循环 */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  输出产生断言错误的源文件名及行号
  * @param  file：源文件名指针
  * @param  line：发生断言错误的行号
  * @retval 无
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* 用户可以根据需要添加自己的打印信息,
     例如: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* 无限循环 */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
