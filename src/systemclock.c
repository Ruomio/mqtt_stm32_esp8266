/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-25 21:49:59
 * @LastEditors: PapillonAz 1065940593@q.com
 * @LastEditTime: 2023-10-25 22:20:09
 * @FilePath: /IWDG_demo/src/systemclock.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "systemclock.h"

void SystemClock_Config(){
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // Initializes RCC Oscillators 内外部晶震设置
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){
        Error_Handler();
    }

    // Initializes CPU AHB APB clocks
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_SYSCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_SYSCLK_DIV1;
    // 当主频为24MHz或以下时，可以将LATENCY设置为0，48MHz时设置为 1，主频72MHz 需要插入2个等待
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK){
        Error_Handler();
    }

}