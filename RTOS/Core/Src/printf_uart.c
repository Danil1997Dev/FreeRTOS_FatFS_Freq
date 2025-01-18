/*
 * printf_uart.c
 *
 *  Created on: Dec 31, 2024
 *      Author: user
 */
#include "printf_uart.h"

#ifdef H_UART

extern UART_HandleTypeDef H_UART;

#endif

void UART_Printf(const char* fmt, ...) {
    char buff[256];
    __builtin_va_list args;
    __builtin_va_start(args, fmt);
    vsnprintf(buff, sizeof(buff), fmt, args);
    HAL_UART_Transmit(&huart3, (uint8_t*)buff, strlen(buff), HAL_MAX_DELAY);
    __builtin_va_end(args);
}
