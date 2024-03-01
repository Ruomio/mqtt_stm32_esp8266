/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-02-29 10:23:35
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-01 11:09:58
 * @FilePath: /Mqtt_stm32_esp8266/src/esp8266.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "esp8266.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 将数据通过ESP8266发送到MQTT服务器
void publishData(char *topic,char *data)
{
    // 构建MQTT发布消息
    char mqttMessage[100];
    sprintf(mqttMessage, "AT+MQTTPUBLISH=0,\"%s\",\"%s\"\r\n",topic, data);

    // 发送MQTT发布消息
    // USART1_SendString(mqttMessage);
    USART1_SendData(mqttMessage, sizeof(mqttMessage));
}



// 处理收到的MQTT订阅消息
void processMQTTMessage(char* message)
{
    // 处理收到的消息
    printf("收到消息:%s\r\n", message);
    
}

// 接收并处理ESP8266接收到的MQTT订阅消息
void receiveAndProcessMQTTMessage()
{
    while (1)
    {
        char receivedData = USART1_ReceiveByte();
        if (receivedData == '+')  // 收到MQTT订阅消息的开始符号
        {
            char mqttMessage[100];
            int i = 0;
            while (receivedData != '\n')  // 持续接收消息内容直到换行符
            {
                receivedData = USART1_ReceiveByte();
                mqttMessage[i++] = receivedData;
            }
            processMQTTMessage(mqttMessage);
        }
    }
}

// 使用STM32向ESP8266发送AT指令设置MQTT参数, 宏定义在头文件当中
void Configure_ESP8266_MQTT()
{
    printf("AT+CWMODE=1\r\n"); // 设置为Station模式
    printf("AT+CWJAP=\"%s\",\"%s\"\r\n", ESP8266_ApSsid, ESP8266_ApPwd); // 连接WiFi网络
    printf("AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", ESP8266_TcpServer_IP, ESP8266_TcpServer_Port); // 连接MQTT服务器
    // printf("AT+MQTTUSERCONFIG=0,\"username\",\"password\"\r\n"); // 设置MQTT用户名和密码
    printf("AT+MQTTCLIENTCONFIG=0,\"%s\",%s,0\r\n", MQTT_ClientId, MQTT_KeepLive_TIME); // 配置MQTT客户端ID和心跳时间
}

// 处理收到的MQTT订阅消息
void Process_MQTT_Message(char* topic, char* message)
{
    if (strcmp(topic, "temperature") == 0)
    {
        float temperature = atof(message); // 将字符串转换为浮点数
        // 温度处理逻辑
        // ...
    }
}

// 接收并处理ESP8266接收到的MQTT订阅消息
void Receive_And_Process_MQTT_Message()
{
    while (1)
    {
        char receivedData = USART1_ReceiveByte();
        if (receivedData == '+')  // 收到MQTT订阅消息的开始符号
        {
            char mqttTopic[50], mqttMessage[100];
            int i = 0;

            // 解析MQTT主题
            while (receivedData != ',')
            {
                receivedData = USART1_ReceiveByte();
                mqttTopic[i++] = receivedData;
            }
            mqttTopic[i - 1] = '\0';

            // 解析MQTT消息内容
            receivedData = USART1_ReceiveByte();
            i = 0;
            while (receivedData != '\n')
            {
                receivedData = USART1_ReceiveByte();
                mqttMessage[i++] = receivedData;
            }
            mqttMessage[i - 1] = '\0';

            Process_MQTT_Message(mqttTopic, mqttMessage);
        }
    }
}


// 发送在sys.c 文件中，重定向了printf函数


// 接收ESP8266发送的数据
char USART1_ReceiveByte()
{
    // while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    // return USART_ReceiveData(USART1);


    while (__HAL_UART_GET_FLAG(&huart1, USART_FLAG_RXNE) == RESET);
    // HAL_UART_Receive(&huart1, receive_buff, sizeof(receive_buff), 1000);
    return (char)USART1->DR;
}