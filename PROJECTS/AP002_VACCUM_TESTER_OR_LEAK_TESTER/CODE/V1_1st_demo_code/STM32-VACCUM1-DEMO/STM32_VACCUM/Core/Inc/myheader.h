/*
 * myheader.h
 *
 *  Created on: Dec 15, 2023
 *      Author: navee
 */

#ifndef INC_MYHEADER_H_
#define INC_MYHEADER_H_




//#include "pid.h"
//#include "stm32f1xx_hal.h"
#include "main.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern volatile uint16_t rxBufferCount;


//Profile write Page
typedef struct
{
	uint16_t srNoAddr 	;
	uint16_t mmhgAddr 	;
	uint16_t minAddr 	;
	uint16_t secAddr 	;
	uint16_t warningAddr ;

}ProfileWrieParamAddrs;

#define VACCUME_TEST_PAGE 200
#define PROFILE_HOME_PAGE   VACCUME_TEST_PAGE
#define PROFILE_WRITE_PAGE   201
#define PROFILE_LOAD_PAGE    202



#define MAX_MODEM_RX_BUFF 250
#define MAX_DEBUG_TX_BUFF 50


#define HOME_PAGE_NUMBER 0X00
#define AUTH_PAGE_NUMBER 0X07

//void uartSend(uint8_t *target)
//{
//	uint8_t data[30];
//	memset(data,0,sizeof(data));
//	sprintf(data," tr :%d\n",target);
//	HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
//}

#endif /* INC_MYHEADER_H_ */
