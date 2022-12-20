/*
 * FILE               : wwdg.h
 * DESCRIPTION        : This file is wwdg driver.
 * Author             : Bella
 * Copyright          :
 *
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 06/21/2017
 *
 * create.
 * -------------------
 */
 
#ifndef __wwdg_h__
#define __wwdg_h__

//--------------------------- Define ---------------------------//

//----------------------- Include files ------------------------//

#include "stm32f1xx_hal.h"
//-------------------------- Typedef ---------------------------//

typedef struct {
	int (* initialize)(void);
	void (* feed_dog)(WWDG_HandleTypeDef* hwwdg);
}WWDG_T;

//--------------------------- Extern ---------------------------//

extern WWDG_T wwdg;
extern WWDG_HandleTypeDef hwwdg;
//extern void MX_WWDG_Init(void);
#endif //__iwdg_h__
