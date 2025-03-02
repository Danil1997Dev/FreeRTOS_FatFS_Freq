/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdlib.h"
#include "printf_uart.h"
#include "sys_clk_cnfg.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern volatile unsigned long totalTickCnt;
extern volatile uint32_t freq;
extern UART_HandleTypeDef huart3;
extern SD_HandleTypeDef hsd;
extern uint32_t freqRef;
extern uint8_t bufRX[1];
char bfrInfo[1024];
uint32_t precIdelInt;
uint16_t precIdelChar;
ret_status statusClk;
/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
//extern void SysClockPLLConfig(void);
//extern void SysClockHSEConfig(void);
/* USER CODE END FunctionPrototypes */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);
void vApplicationIdleHook(void);
void vApplicationTickHook(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
	totalTickCnt = 0;

}

__weak unsigned long getRunTimeCounterValue(void)
{
return totalTickCnt;
}
/* USER CODE END 1 */

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
	  char *pStrIdle = NULL;

	vTaskGetRunTimeStats(bfrInfo);
	pStrIdle = strstr(bfrInfo,"IDLE");
	if (pStrIdle)
	{
		freq = HAL_RCC_GetSysClockFreq();
		pStrIdle = strstr(pStrIdle,"%");
		const char *pStrIdelStart = pStrIdle;
		while (*(pStrIdle) != '\t')
		{
			pStrIdle--;
		}

		if ((pStrIdelStart-(pStrIdle+1)) == 1)
		{
			precIdelChar = *(pStrIdle+1);
		}
		else if ((pStrIdelStart-(pStrIdle+1)) == 2)
		{
			precIdelChar = (*(pStrIdle+2) << 8) | (*(pStrIdle+1) << 0);
		}
		else if ((pStrIdelStart-(pStrIdle+1)) > 3)
		{
			precIdelChar = (*(pStrIdle+2) << 8) | (*(pStrIdle+1) << 0);
		}
		precIdelInt = atoi((char *)&precIdelChar);

		if (precIdelInt > 50)
		{
			if (freq == freqRef)
			{
//				statusClk = SysClockPLLConfig();
				statusClk = SysClockHSEConfig();
				HAL_UART_DeInit(&huart3);
				HAL_UART_Init(&huart3);
				HAL_UART_Receive_IT(&huart3, bufRX, sizeof(bufRX));
			}
		}
		else
		{
			statusClk = SysClockPLLConfig();
//			HAL_SD_DeInit(&hsd);
//			HAL_SD_Init(&hsd);
			HAL_UART_DeInit(&huart3);
			HAL_UART_Init(&huart3);
			HAL_UART_Receive_IT(&huart3, bufRX, sizeof(bufRX));
		}
		freq = HAL_RCC_GetSysClockFreq();
	}
}
/* USER CODE END 2 */

/* USER CODE BEGIN 3 */
void vApplicationTickHook( void )
{
   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
}
/* USER CODE END 3 */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */

