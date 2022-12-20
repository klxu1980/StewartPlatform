/*
 * FILE								: KEY.h
 * DESCRIPTION				: This file is for KEY.h
 * Author							: Bella
 * Copyright					:
 *
 * History
 * --------------------
 * Rev								: 0.00
 * Date								: 05/24/2017
 *
 * create.
 * --------------------
 */
 #ifndef __KEY_h__
 #define __KEY_h__
 //-----------------define-------------------------------//
#define KEY_INPUT  HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_2)

//----------------------- Include files ------------------------//

//-------------------------- Typedef ---------------------------//
typedef struct {
	int (* initialize)(void);
}KEY_T;

//--------------------------- Extern ---------------------------//
extern KEY_T key;

 #endif //__KEY_h__
