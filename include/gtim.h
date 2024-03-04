/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-02-24 10:36:03
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-04 18:07:57
 * @FilePath: /Advance_TIM_Input_Mode/include/gtim.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __GTIM_H__
#define __GTIM_H__

#include "main.h"

extern TIM_HandleTypeDef g_timx_pwm_chy_handle;

void gtim_timx_pwn_chy_init(uint16_t psc, uint16_t arr);

#endif //_GTIM_H__