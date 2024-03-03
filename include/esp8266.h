/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-02-28 17:04:17
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-03 23:12:22
 * @FilePath: /Mqtt_stm32_esp8266/include/esp8266_test.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __ESP8266_H_
#define __ESP8266_H_

/********************************** 用户需要设置的参数**********************************/
#define      ESP8266_ApSsid             "352"            //要连接的热点的名称
#define      ESP8266_ApPwd              "352newbee"      //要连接的热点的密钥

#define      ESP8266_TcpServer_IP       "8.146.199.13"   
#define      ESP8266_TcpServer_Port     "1883"            

#define      MQTT_ClientId_Pub          "user_pub"             
#define      MQTT_UserName              "pub_user_1"             
#define      MQTT_Passwd                "pub_passwd_1"             
#define      MQTT_ClientId_Sub          "user_sub"        


#define      MQTT_KeepLive_TIME         "60"             


void Init_ESP8266_MQTT();
void Configure_ESP8266_MQTT();
void publishData(char *topic,char *data);

#endif