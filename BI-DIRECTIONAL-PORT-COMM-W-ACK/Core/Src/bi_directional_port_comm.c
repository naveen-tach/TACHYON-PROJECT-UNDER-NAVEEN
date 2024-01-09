/*
 * bi_directional_port_comm.c
 *
 *  Created on: Jan 8, 2024
 *      Author: navee
 */


#include "bi_directional_port_comm.h"


void UartTransfor(UART_HandleTypeDef *huart,uint8_t *data, uint8_t dataSize)
{
	HAL_UART_Transmit(huart, data, dataSize, 1);
}

void clearUartBuff()
{
	memset(uartRXBuff2,0,sizeof(uartRXBuff2));
	uartRxBuffCount2 = 0;
}
void clearUartBuff3()
{
	memset(uartRXBuff3,0,sizeof(uartRXBuff3));
	uartRxBuffCount3 = 0;
}

void ack(uint8_t *biDirectFlag,uint8_t *data, uint8_t size)
{
	if(*biDirectFlag == 2)
	{
		uint8_t Data[255] ;
		memset(Data,0,sizeof(Data));
		Data[0] = 0x01 ;
		strcat(Data,data);
		UartTransfor(&huart2,Data,size+1);

	}
	if(*biDirectFlag == 3)
	{
		uint8_t Data[255] ;
		memset(Data,0,sizeof(Data));
		Data[0] = 0x01 ;
		strcat(Data,data);
		UartTransfor(&huart3,Data,size+1);

	}
}

void bi_directional_port_Comm_init(uint8_t *biDirectFlag)
{
	if( *biDirectFlag == 2)
	{
		HAL_Delay(10);

		uint8_t data[255] ;
		memset(data,0,sizeof(data));
		data[0] = 0x02 ;
		strcat(data,uartRXBuff2);
		UartTransfor(&huart1, &data,uartRxBuffCount2+1);
		ack(biDirectFlag, uartRXBuff2, uartRxBuffCount2);
		memset(data,0,sizeof(data));
		*biDirectFlag = 0 ;
		clearUartBuff();

	}
	if( *biDirectFlag == 3)
		{
			HAL_Delay(100);

			uint8_t data[255] ;
			memset(data,0,sizeof(data));
			data[0] = 0x03 ;
			strcat(data,uartRXBuff3);
			UartTransfor(&huart1, &data,uartRxBuffCount3+1);
			ack(biDirectFlag, uartRXBuff3, uartRxBuffCount3);
			memset(data,0,sizeof(data));
			*biDirectFlag = 0 ;
			clearUartBuff3();

		}

}
