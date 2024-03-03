/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-02-24 10:36:03
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-02 16:39:33
 * @FilePath: /Advance_TIM_Input_Mode/include/stm32f1xx_it.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.h
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file 
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
 ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F1xx_IT_H
#define __STM32F1xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif


void Error_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);


void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
// void TIM1_CC_IRQHandler(void);


#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_IT_H */
