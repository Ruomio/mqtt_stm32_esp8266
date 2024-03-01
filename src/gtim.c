/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-02-24 10:36:13
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-02-25 14:34:26
 * @FilePath: /Advance_TIM_Input_Mode/src/gtim.c
 * @Description: 通用定时器TIM3 CH1 --> PA6
 *               通用定时器TIM2 CH2 --> PA1
 */
#include "gtim.h"

TIM_HandleTypeDef g_timx_pwm_chy_handle = {0};
void gtim_timx_pwn_chy_init(uint16_t psc, uint16_t arr) {
    

    g_timx_pwm_chy_handle.Instance = TIM2;
    g_timx_pwm_chy_handle.Init.Prescaler = psc;
    g_timx_pwm_chy_handle.Init.Period = arr;
    g_timx_pwm_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_timx_pwm_chy_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    

    HAL_TIM_PWM_Init(&g_timx_pwm_chy_handle);

    TIM_OC_InitTypeDef timx_oc_pwn_chy = {0};
    timx_oc_pwn_chy.OCMode = TIM_OCMODE_PWM1;
    timx_oc_pwn_chy.Pulse = arr/2;                      // 脉宽
    timx_oc_pwn_chy.OCPolarity = TIM_OCPOLARITY_HIGH;    // 当定时器计数值小于CCR1_Val时为高电平
    HAL_TIM_PWM_ConfigChannel(&g_timx_pwm_chy_handle, &timx_oc_pwn_chy, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&g_timx_pwm_chy_handle, TIM_CHANNEL_2);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim) {
    if(htim->Instance == TIM2) {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_TIM2_CLK_ENABLE();

        GPIO_InitStruct.Pin = GPIO_PIN_1;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);        
    }
}