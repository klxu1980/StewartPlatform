/*
 * --------------------
 * Company             : LUOYANG GINGKO TECHNOLOGY CO.,LTD.
                       : �������ӿƼ����޹�˾
 * --------------------
 * Project Name        : iCore1s usart
 * Description         : iCore1s usart
 * --------------------
 * Tool Versions       : uVision V5.17.0.0
 * Target Device       : STM32F103ZET6
 * --------------------
 * Engineer            : yangxu
 * Revision            : 0.01
 * Created Date        : 08/07/2017
 * --------------------
 * Engineer            :
 * Revision            :
 * Modified Date       :
 * --------------------
 * Additional Comments :
 *
 * --------------------
 *==========================================================
 *����˵��:
 *		�������سɹ���,ARM��ɫLED����,��ʼ��FPGA���ɵ�ram���в�
 *�ԡ���ARM LED һֱΪ��ɫ,������Գɹ�;��ARM LED ���,�����
 *ʧ�ܡ�
 *==========================================================
 */
//------------------------- Include -----------------------//

#include "stm32f1xx_hal.h"
#include "usart.h"
#include "led.h"
#include "wwdg.h"
#include "exti.h"
#include "exti.h"
#include "fsmc.h"
#include "system_clock.h"
#include "..\CtrlInterface.h"
#include "..\RobotCtrl\GlobalDef.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/*
 * Name                : main
 * Description         : ---
 * Author              : yangxu
 *
 * History
 * --------------------
 * Rev                 : 0.00
 * Date                : 2017.08.07
 * 
 * create.
 * --------------------
 */
 
int main(void)
{			
  HAL_Init();
  system_clock.initialize();

	led.initialize();
	
	exti.initialize();			//��ʼ���ж�
	wwdg.initialize();
	fsmc.initialize();
	
	usart3.initialize(UART3_BAUD_RATE);
	UART3_RS485_rev;
	
	usart2.initialize(9600);
	UART2_RS485_send;
		
	//LED_BLUE_OFF;
	//LED_GREEN_OFF;
	//LED_RED_OFF;
	
	int xx = 0;
	while(1)
	{
	 
		++xx;
	if(xx < 5000000)
		LED_RED_ON;
	else if(xx < 10000000)
		LED_RED_OFF;
	else
		xx = 0;
	
	}
}
