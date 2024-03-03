/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-25 22:33:47
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-03 21:58:02
 * @FilePath: /IWDG_demo/include/uart.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __USART_H__
#define __USART_H__

#include "main.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

extern uint8_t receive_buff[64];

void USART1_UART_Init(void);


void USART2_UART_Init(void);

// void USART1_SendData(unsigned char *Data, unsigned int length);



#endif