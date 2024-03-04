/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-25 20:56:10
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-04 18:08:28
 * @FilePath: /IWDG_demo/src/main.c
 * @Description: 由TIM2 产生PWM信号， 然后用高级定时器TIM1区捕获PWM信号
 * problem : !!!  无法从PWM输入，无法触发上升沿中断， 单独测试都没问题。
 */
// #include <stdio.h>
#include "main.h"
#include "systemclock.h"
#include "gpio.h"
#include "usart.h"
// #include "oled.h"
// #include "i2c.h"
#include "sys.h"
#include "gtim.h"
#include "esp8266.h"


// extern uint8_t receive_buff[128];
// extern UART_HandleTypeDef huart1;
// extern UART_HandleTypeDef huart2;


int main(){
    uint8_t cnt = 0;


    // 外设 闪存 系统tick
    HAL_Init();

    // clock
    SystemClock_Config();

    // 外设
    GPIO_Init();
    // MX_I2C1_Init();
    gtim_timx_pwn_chy_init(7200-1, 200-1);
    HAL_Delay(20);
    // OLED_Init();
    // UART1 接收从串口助手来的数据，不定长
    USART1_UART_Init();
    HAL_Delay(20);
    USART2_UART_Init();

    // UART2 接收从esp8266来的数据
    HAL_UARTEx_ReceiveToIdle_IT(&huart1, receive_buff, sizeof(receive_buff));
    HAL_UARTEx_ReceiveToIdle_IT(&huart2, receive_buff, sizeof(receive_buff));

    char tem[] = "Hello!\r\n";
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)tem, sizeof(tem));
    // HAL_UART_Transmit_IT(&huart2, (uint8_t*)tem, sizeof(tem));
    // printf("Program runing!\r\n");    
    // Configure_ESP8266_MQTT();
    // printf("esp8266 configure finish!\r\n");    
    HAL_Delay(1000);
    uint8_t res =  Configure_ESP8266_MQTT();
    res ? printf("The error code is %d!\r\n", res) : 0;

    // Subscribe_Topic("door_lock/test_sub", Qos1);

    while(1){
        HAL_Delay(100);
        if(cnt++ > 100) {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            // publishData("door_lock/test","Hello_Test");
            // publishData("door_lock/test_sub","test_sub_receive", Qos1);

        }
        
    }
}
