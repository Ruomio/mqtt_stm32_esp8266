/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-02-24 10:36:13
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-03 22:39:09
 * @FilePath: /Advance_TIM_Input_Mode/src/sys.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "sys.h"
#include "oled.h"
#include "usart.h"

// #define OLED
#define UART1
// #define UART2


int _write(int file, char* ptr, int len) {

#ifdef OLED
    OLED_NewFrame();
    for(int i=0; i< len; i++) {
        OLED_PrintASCIIChar(i*6, 0, ptr[i], &afont12x6, OLED_COLOR_NORMAL);
        // OLED_PrintASCIIChar(6, 12, (len + '0'), &afont12x6, OLED_COLOR_NORMAL);
        // OLED_PrintASCIIChar(i*6, 12, (char)i + 'a', &afont12x6, OLED_COLOR_NORMAL);
    }
    OLED_ShowFrame();
#endif


#ifdef UART1

    for (int i = 0; i < len; i++)  
    {  
        while((USART1->SR&0X40)==0);//等待上一次串口数据发送完成  
        USART1->DR = (uint8_t) ptr[i];       //写DR,串口1将发送数据
    }  

#endif

#ifdef UART2
    for (int i = 0; i < len; i++)  
    {  
        while((USART2->SR&0X40)==0);//等待上一次串口数据发送完成  
        USART2->DR = (uint8_t) ptr[i];       //写DR,串口1将发送数据
    }  

#endif


    return 0;
}