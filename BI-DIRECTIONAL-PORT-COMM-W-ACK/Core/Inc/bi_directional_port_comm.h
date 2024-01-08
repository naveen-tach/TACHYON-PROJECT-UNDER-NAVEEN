/*
 * bi_directional_port_comm.h
 *
 *  Created on: Jan 8, 2024
 *      Author: navee
 */

#ifndef INC_BI_DIRECTIONAL_PORT_COMM_H_
#define INC_BI_DIRECTIONAL_PORT_COMM_H_

#include "main.h"



extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;


extern uint16_t uartRxBuffCount ;
extern uint8_t uartRXBuff[255] ;
extern uint8_t biDirect_2_Flag ;

void port(uint8_t *data, uint8_t dataSize);

void bi_directional_port_Comm_init(uint8_t *biDirectFlag);



#endif /* INC_BI_DIRECTIONAL_PORT_COMM_H_ */
