/*
 * FILE               : usart.h
 * DESCRIPTION        : This file is iCore1S usart file header.
 * Author             : Bella.
 * Copyright          :
 *
 * History
 * --------------------
 * Rev                : 0.00
 * Date               : 06/24/2017
 *
 * create.
 * --------------------
 */
#ifndef __usart_h__
#define __usart_h__

//----------------------- Include files ------------------------//

#include "stm32f1xx_hal.h"

//--------------------------- Define ---------------------------//
#define UART_BUFFER_SIZE 100

//------------------------- Data struct ------------------------//
typedef struct{
	char receive_buffer[UART_BUFFER_SIZE];
	char receive_data;
	int counter;
	
	int receive_ok_flag;
	int baudrate;
	int error;
	int(* initialize)(unsigned long int);
	int(* send_string)(char *);
	int(* printf)(const char * ,...);
}UART_T;
//----------------------- Extern function ----------------------//

extern void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle);
extern void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle);
extern UART_HandleTypeDef huart2;
extern UART_T usart2;
extern UART_HandleTypeDef huart3;
extern UART_T usart3;

//----------------------- Extern variable ----------------------//
#endif // __uart_h__
