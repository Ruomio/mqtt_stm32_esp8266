/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-02-28 21:45:51
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-02-29 09:52:54
 * @FilePath: /Mqtt_stm32_esp8266/src/spi.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * SPI_1 PIN: PA_4:NSS , PA_5_:SCK , PA_6:MISO , PA_7:MOSI
 */
#include "spi.h"


SPI_HandleTypeDef g_spi_1 = {0};
void spi_1_init() {
    g_spi_1.Instance = SPI1;
    g_spi_1.Init.Mode = SPI_MODE_MASTER;
    g_spi_1.Init.Direction = SPI_DIRECTION_2LINES;
    g_spi_1.Init.DataSize = SPI_DATASIZE_8BIT;
    g_spi_1.Init.CLKPolarity = SPI_POLARITY_LOW;
    g_spi_1.Init.CLKPhase = SPI_PHASE_1EDGE;
    g_spi_1.Init.NSS = SPI_NSS_SOFT;
    g_spi_1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    g_spi_1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    g_spi_1.Init.TIMode = SPI_TIMODE_DISABLE;
    g_spi_1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    g_spi_1.Init.CRCPolynomial = 3;
    
    HAL_SPI_Init(&g_spi_1);
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi) {
    if(hspi->Instance == SPI1) {
        __HAL_RCC_SPI1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /* PA_4:NSS , PA_5_:SCK , PA_6:MISO , PA_7:MOSI */
        GPIO_InitTypeDef gpio_struct = {0};
        gpio_struct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
        gpio_struct.Mode = GPIO_MODE_AF_PP;
        gpio_struct.Pull = GPIO_PULLUP;
        gpio_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &gpio_struct);
    }
}