/*
 * FILE                : led.h
 * DESCRIPTION         : This file is for led.h
 * Author              : Bella
 * Copyright           : 
 *
 * History
 * --------------------
 * Rev                 : 0.00
 * Date                : 06/14/2017
 *
 * create.
 * --------------------
 */

 #ifndef __led_h__
 #define __led_h__
 
 //--------------------------Define--------------------------//
 //ºìµÆ<----------------->PF5
 #define LED_RED_ON   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_5,GPIO_PIN_RESET)
 #define LED_RED_OFF  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_5,GPIO_PIN_SET)
 #define LED_R_TOGGLE		HAL_GPIO_TOGGLE(GPIOF,GPIO_PIN_5) 
 //ÂÌµÆ<----------------->PF4
 #define LED_GREEN_ON   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_4,GPIO_PIN_RESET)
 #define LED_GREEN_OFF  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_4,GPIO_PIN_SET)
 #define LED_GREEN_TOGGLE		HAL_GPIO_TOGGLE(GPIOF,GPIO_PIN_4) 

 //À¶µÆ<----------------->PF3
 #define LED_BLUE_ON   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_3,GPIO_PIN_RESET)
 #define LED_BLUE_OFF  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_3,GPIO_PIN_SET)
 #define LED_BLUE_TOGGLE		HAL_GPIO_TOGGLE(GPIOF,GPIO_PIN_3) 
 
 //RS485ÊÕ·¢Òý½Å¿ØÖÆ<---------------->PC6
 #define UART2_RS485_rev      HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET)
 #define UART2_RS485_send     HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET)
 #define UART2_RS485_TOGGLE		HAL_GPIO_TOGGLE(GPIOC,GPIO_PIN_7) 
 
 #define UART3_RS485_rev      HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET)
 #define UART3_RS485_send     HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET)
 #define UART3_RS485_TOGGLE		HAL_GPIO_TOGGLE(GPIOC,GPIO_PIN_6) 
 
 //------------------ FPGA ------------------------------------
 #define FPGA_Timer_ON   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET)
 #define FPGA_Timer_OFF  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET)
 #define FPGA_Timer_TOGGLE		HAL_GPIO_TOGGLE(GPIOB,GPIO_PIN_14)
 
 //--------------------------Include-------------------------//

 //--------------------------Typedef-------------------------//
 typedef struct {
	int (* initialize)(void);
}LED_T;
 
 //--------------------------Extern--------------------------//
 extern LED_T led;
 
 
 #endif //__led_h__
