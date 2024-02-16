/*
 * profile_write.c
 *
 *  Created on: Dec 21, 2023
 *      Author: navee
 */
#include "profile_write.h"

	uint8_t targetSrNo = 0 ;
	uint8_t serialNoRead_flag = 0;
	uint8_t writeOnSerialNo_flag = 0;


//uint16_t srNoAddr = 0x9002	;

void profile_write_Write(profile_write_params * profileParams)
{

	write_ee24(&profileParams->ee24Param);
}

void profile_write_show_data(profile_write_params * profileParams)
{

	uint8_t *read_data_buff[5];
	uint8_t read_data_size = sizeof(read_data_buff);

	readEe24(&read_data_buff,read_data_size, profileParams->ee24Param->serialNum);

//	write_page_details_update(profileParams->ee24Param->serialNum);

}

void writePage_init(uint8_t *displayUartFlag, home_page_t *homePage_t)
{
	ProfileWrieParamAddrs writeProfileParams = {
			.srNoAddr		=	0x9002	,
			.mmhgAddr		=	0x9004	,
			.minAddr		=	0x9005	,
			.secAddr		=	0x9006	,
			.warningAddr	=	0x9009

	};

	profile_write_serialNo_read(displayUartFlag,&targetSrNo, &serialNoRead_flag, &writeOnSerialNo_flag) ;
//	if(*displayUartFlag == 1)
//	{
		profile_write_serialNo_details_update(targetSrNo, &writeProfileParams, &serialNoRead_flag, displayUartFlag);
		if(serialNoRead_flag == 2)
		{
			uint8_t _arr[50] = { 0 } ;
			//below code is for write Warning to display for eeprom
			_arr[0]		= 	0x5A 	;
			_arr[1]		= 	0xA5	;
			_arr[2]		=	0x32	;
			_arr[3]		=	0x82	;
			_arr[5]		=	writeProfileParams.warningAddr>>0	;
			_arr[4]		=	writeProfileParams.warningAddr>>8 	;
			uint8_t * warningStr ="                            ";
			strcat(_arr,warningStr);
			HAL_UART_Transmit(&huart2, &_arr, strlen(_arr), HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart2, &_arr, strlen(_arr), HAL_MAX_DELAY);
			uint8_t data[30];
			memset(data,0,sizeof(data));
			sprintf(data,"its in write page\n");
			HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
			serialNoRead_flag = 3 ;
		}
		profile_write_details_to_ee24(targetSrNo, &writeOnSerialNo_flag, homePage_t, &serialNoRead_flag,displayUartFlag, &writeProfileParams);
//	}
//		uint8_t data[30];
//		memset(data,0,sizeof(data));
//		sprintf(data,"its in write page\n");
//		HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);




//		*displayUartFlag = 0 ;
//	}


}

