/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-25 22:34:39
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-03 15:59:42
 * @FilePath: /IWDG_demo/src/uart.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "usart.h"
#include "main.h"
// #include "sys.h"


UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

uint8_t receive_buff[64];
uint8_t receive_flga;

void USART1_UART_Init(void){
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = USART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if( HAL_UART_Init(&huart1) != HAL_OK ){
        Error_Handler();
    }   

}

void USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }


}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle){
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if(uartHandle->Instance == USART1){
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /** 
         * PA9  -> USART1_TX
         * PA10 -> USART1_RX
         */
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* 中断配置 */
        HAL_NVIC_SetPriority(USART1_IRQn,1,3);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
    else if(uartHandle->Instance == USART2) {
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* 中断配置 */
        HAL_NVIC_SetPriority(USART2_IRQn,1,3);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle){

    if(uartHandle->Instance == USART1){
        __HAL_RCC_USART1_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
        HAL_NVIC_DisableIRQ(USART1_IRQn);
    }
    else if(uartHandle->Instance==USART2)
    {
        __HAL_RCC_USART2_CLK_DISABLE();

        /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);
        /* USART2 interrupt Deinit */
        HAL_NVIC_DisableIRQ(USART2_IRQn);

    }
}

/**
 * @description: UART2 连接esp8266， 当接受来自UART1的数据时，要发送给esp8266
 * @param {UART_HandleTypeDef} *huart
 * @return {*}
 */
// HAL_UART_Receive_IT(&huart1, receive_buff, sizeof(receive_buff));
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    /* 串口助手 --> UART1 --> UART2 
     */
    if(huart->Instance == USART1) {
        HAL_UART_Transmit_IT(&huart1, (uint8_t*)"UART1_Callback\r\n", sizeof("UART1_Callback\r\n"));
        // 接受消息回显到串口助手
        // printf("%s\r\n",receive_buff);          

        // 接受从UART1来的信息后，通过UART2将消息发送到esp8266
        HAL_UART_Transmit_IT(&huart2, receive_buff, sizeof(receive_buff));    
        
        HAL_UART_Receive_IT(&huart1, receive_buff, sizeof(receive_buff));
    }
    else if(huart->Instance == USART2) {
        HAL_UART_Transmit_IT(&huart2, (uint8_t*)"UART2_Callback\r\n", sizeof("UART2_Callback\r\n"));    

        // 接受从UART_Rx 来的信息, 后通过UART1 回显到串口助手
        // printf("%s\r\n",receive_buff);
        HAL_UART_Transmit_IT(&huart1, receive_buff, sizeof(receive_buff));

        
        HAL_UART_Receive_IT(&huart2, receive_buff, sizeof(receive_buff));
    }

}
     
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    if(huart->Instance == USART1) {
        // HAL_UART_Transmit_IT(&huart1, (uint8_t*)"UART1_Ex_Callback\r\n", sizeof("UART1_Ex_Callback\r\n"));
        // printf("UART1 ExCall Back\r\n");
        // 接受消息回显到串口助手
        // printf("%s\r\n",receive_buff);          

        // 接受从UART1来的信息后，通过UART2将消息发送到esp8266
        HAL_UART_Transmit_IT(&huart2, receive_buff, Size);    
        
        HAL_UARTEx_ReceiveToIdle_IT(&huart1, receive_buff, sizeof(receive_buff));
    }
    else if(huart->Instance == USART2) {
        // HAL_UART_Transmit_IT(&huart1, (uint8_t*)"UART2_Ex_Callback\r\n", sizeof("UART2_Ex_Callback\r\n"));
        // printf("UART2 ExCall Back\r\n");      

        // 接受从UART_Rx 来的信息, 后通过UART1 回显到串口助手
        // printf("%s\r\n",receive_buff);
        HAL_UART_Transmit_IT(&huart1, receive_buff, Size);

        
        HAL_UARTEx_ReceiveToIdle_IT(&huart2, receive_buff, sizeof(receive_buff));
    }
}


/**
 * @description: UART1 发送数据到串口助手和发送到 连接UART2的esp8266
 * @param {unsigned char} *Data
 * @param {unsigned int} length
 * @return {*}
 */
/* void USART1_SendData(unsigned char *Data, unsigned int length)
{

    // USART_SendData(USART3,*Data++);
    // while (USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET);
    HAL_USART_Transmit_IT(&huart1, (int8_t*)Data, length);
    HAL_USART_Transmit_IT(&huart2, (int8_t*)Data, length);

} */


/* ======================================================================================= */
/* =======================================UART2=========================================== */
/* ======================================================================================= */



/**
 * @description: UART2 发送到esp8266
 * @param {unsigned char} *Data
 * @param {unsigned int} length
 * @return {*}
 */
/* void USART2_SendData(unsigned char *Data, unsigned int length)
{

    // USART_SendData(USART3,*Data++);
    // while (USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET);
    HAL_USART_Transmit_IT(&huart2, (int8_t*)Data, length);

} */