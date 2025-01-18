/*
 * sys_clk_cnfg.h
 *
 *  Created on: Dec 31, 2024
 *      Author: user
 */

#ifndef INC_SYS_CLK_CNFG_H_
#define INC_SYS_CLK_CNFG_H_

#include "main.h"

typedef struct{
	uint32_t sysStat;
	uint32_t nErrFnc;
}ret_status;

//volatile uint32_t freq;


ret_status SysClockPLLConfig(void);
ret_status SysClockHSEConfig(void);

#endif /* INC_SYS_CLK_CNFG_H_ */
