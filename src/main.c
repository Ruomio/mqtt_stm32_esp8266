/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-25 20:56:10
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-01 11:05:52
 * @FilePath: /IWDG_demo/src/main.c
 * @Description: 由TIM2 产生PWM信号， 然后用高级定时器TIM1区捕获PWM信号
 * problem : !!!  无法从PWM输入，无法触发上升沿中断， 单独测试都没问题。
 */
#include <stdio.h>
#include "main.h"
#include "systemclock.h"
#include "gpio.h"
#include "usart.h"
// #include "oled.h"
// #include "i2c.h"
#include "sys.h"
#include "gtim.h"
// #include "esp8266.h"


extern char receive_buff[128];



int main(){
    uint8_t cnt = 0;


    // 外设 闪存 系统tick
    HAL_Init();

    // clock
    SystemClock_Config();

    // 外设
    GPIO_Init();
    // MX_I2C1_Init();
    HAL_Delay(20);
    // OLED_Init();
    USART1_UART_Init();
    USART2_UART_Init();
    // gtim_timx_pwn_chy_init(7200-1, 10000-1);
    // UART1 接收从串口助手来的数据
    HAL_UART_Receive_IT(&huart1, (uint8_t*)receive_buff, sizeof(receive_buff));
    // UART2 接收从esp8266来的数据
    HAL_UART_Receive_IT(&huart2, (uint8_t*)receive_buff, sizeof(receive_buff));


    printf("Program runing!\r\n");    
    // Configure_ESP8266_MQTT();
    // printf("esp8266 configure finish!\r\n");    
    
    while(1){
        HAL_Delay(100);
        if(cnt++ > 10) {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            // publishData("door_lock/test","Hello_Test");
        }
        
    }
}
