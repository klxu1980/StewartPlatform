/*
 * FILE                : exti.h
 * DESCRIPTION         : This file is for exti.h
 * Author              : Bella
 * Copyright           :
 *
 * History
 * --------------------
 * Rev                 : 0.00
 * Date                : 06/21/2017
 *
 * create.
 * --------------------
 */
#ifndef __exti_h__
#define __exti_h__

//--------------------------- Define ---------------------------//
#define KEY_INPUT  HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_2)

//----------------------- Include files ------------------------//

//-------------------------- Typedef ---------------------------//
typedef struct {
	int (* initialize)(void);
}EXTI_T;

//--------------------------- Extern ---------------------------//
extern EXTI_T exti;

#endif //__exti_h__
