/*
 * printf_uart.h
 *
 *  Created on: Dec 31, 2024
 *      Author: user
 */

#ifndef INC_PRINTF_UART_H_
#define INC_PRINTF_UART_H_

#include "main.h"
#include "string.h"
#include "stdio.h"

#ifdef H_UART

void UART_Printf(const char* fmt, ...);

#endif
#endif /* INC_PRINTF_UART_H_ */
