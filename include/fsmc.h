/*
 * FILE               : usart.h
 * DESCRIPTION        : This file is iCore1S usart file header.
 * Author             : yangxu
 * Copyright          :
 *
 * History
 * --------------------
 * Rev                : 0.00
 * Date               : 08/07/2017
 *
 * create.
 * --------------------
 */
//-----------------define-------------------------------//
#ifndef __fsmc_h__
#define __fsmc_h__

//-----------------Include files-------------------------//
#include "stm32f1xx_hal.h"
//----------------- Define ------------------------------//

#define fpga_write(offset,data)	*((volatile unsigned short int *)(0x60000000 + (offset << 17))) = data

#define fpga_read(offset)	*((volatile unsigned short int *)(0x60000000 + (offset << 17)))

//----------------- Typedef -----------------------------//
typedef struct{
	int (* initialize)(void);
}FSMC_T;
//---------------- Extern -------------------------------//
extern FSMC_T fsmc;

#endif //__fsmc_h__
