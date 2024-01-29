/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
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
EXTI_HandleTypeDef exti_handle;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void App_ExtiConfig(void);

/**
  * @brief  应用程序入口函数.
  * @param  无
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();       
  
  /* 初始化按键 */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);  
 
  /* 配置外部中断 */
  App_ExtiConfig();                             

  /* 配置USART */
  DEBUG_USART_Config();                        

  /* LED亮 */
  BSP_LED_On(LED_GREEN);

  /* 等待按键按下 */
  while (BSP_PB_GetState(BUTTON_USER))
  {
  }

  /* LED灭 */
  BSP_LED_Off(LED_GREEN);
  
  /* 打印"SLEEP MODE!" */
  printf("SLEEP MODE!\n\n");

  /* systick中断关闭，防止systick中断唤醒 */
  HAL_SuspendTick();  

  /* 进入SLEEP模式 */
  HAL_PWR_EnterSLEEPMode(PWR_SLEEPENTRY_WFE);

  /* systick中断开启 */
  HAL_ResumeTick();    

  /* 打印"WAKEUP OK!" */
  printf("WAKEUP OK!\n\n");

  while (1)
  {
    /* LED 闪烁 */
    BSP_LED_Toggle(LED_GREEN);
    HAL_Delay(200);
  }
}

/**
  * @brief  中断配置函数
  * @param  无
  * @retval 无
  */
static void App_ExtiConfig(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  __HAL_RCC_GPIOA_CLK_ENABLE();                  /* 使能GPIOA时钟 */
  GPIO_InitStruct.Mode  = GPIO_MODE_EVT_FALLING; /* GPIO模式为下降沿事件 */
  GPIO_InitStruct.Pull  = GPIO_PULLUP;           /* 上拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;  /* 速度为高速 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  /* 初始化GPIO */
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);             /* 使能EXTI中断 */
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void APP_ErrorHandler(void)
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

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
