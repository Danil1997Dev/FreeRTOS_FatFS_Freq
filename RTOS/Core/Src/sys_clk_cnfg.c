#include "sys_clk_cnfg.h"

volatile uint32_t freq;

ret_status SysClockPLLConfig(void)
{
	ret_status status;

	  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	  RCC_OscInitTypeDef RCC_OscStruct;
	  RCC_ClkInitTypeDef RCC_ClkStruct;
	  uint32_t laten;

	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	  RCC_OscInitStruct.PLL.PLLM = 25;
	  RCC_OscInitStruct.PLL.PLLN = 336;
	  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	  RCC_OscInitStruct.PLL.PLLQ = 7;

	  status.sysStat = HAL_RCC_OscConfig(&RCC_OscInitStruct);
	  if (status.sysStat != HAL_OK)
	  {
		status.nErrFnc = 1;
	    return status;
	  }

	  /** Initializes the CPU, AHB and APB buses clocks
	  */
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	  status.sysStat = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
	  if (status.sysStat != HAL_OK)
	  {
		status.nErrFnc = 2;
	    return status;
	  }

		freq = HAL_RCC_GetSysClockFreq();
	    HAL_RCC_GetClockConfig(&RCC_ClkStruct, &laten);
	    HAL_RCC_GetOscConfig(&RCC_OscStruct);

	    status.nErrFnc = 0;

	    return status;
}

ret_status SysClockHSEConfig(void)
{
	ret_status status;

	  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	  RCC_OscInitTypeDef RCC_OscStruct;
	  RCC_ClkInitTypeDef RCC_ClkStruct;
	  uint32_t laten;

	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

	  status.sysStat = HAL_RCC_OscConfig(&RCC_OscInitStruct);
	  if (status.sysStat != HAL_OK)
	  {
		status.nErrFnc = 1;
	    return status;
	  }

	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	  status.sysStat = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
	  if (status.sysStat != HAL_OK)
	  {
		status.nErrFnc = 2;
	    return status;
	  }

		freq = HAL_RCC_GetSysClockFreq();
	    HAL_RCC_GetClockConfig(&RCC_ClkStruct, &laten);
	    HAL_RCC_GetOscConfig(&RCC_OscStruct);
	    status.nErrFnc = 0;

	    return status;
}
