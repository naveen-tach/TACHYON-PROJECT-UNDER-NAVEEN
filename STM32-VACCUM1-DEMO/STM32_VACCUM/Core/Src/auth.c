/*
 * auth.c
 *
 *  Created on: Jan 1, 2024
 *      Author: navee
 */
#include "auth.h"


ee24_auth_params_t ee24_auth_params ={
		.ID			=	0	,
		.password	=	0	,
		.securityL	=	0	,
};
uint8_t aFlag = 1;
uint8_t auth_flag_switch_page = 0 ;

void auth_init(uint8_t *displayUartFlag, uint8_t *authFlag)
{
	if(*authFlag == 0)
	{
		auth_page_read(displayUartFlag,&auth_flag_switch_page, &ee24_auth_params, &aFlag, authFlag);
	}
	else
	{
		uint8_t data[30];
		memset(data,0,sizeof(data));
		sprintf(data,"authentication flag is not set as defualt\n");
		HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
	}
}
