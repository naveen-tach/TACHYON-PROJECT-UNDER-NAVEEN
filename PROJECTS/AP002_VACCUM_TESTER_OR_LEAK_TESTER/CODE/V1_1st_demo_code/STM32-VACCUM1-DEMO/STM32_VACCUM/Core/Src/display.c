/*
 * display.c
 *
 *  Created on: Dec 15, 2023
 *      Author: naveen
 */
#include "display.h"
#include "ee24.h"
#include "profile_home.h"
#include "profile_write.h"
#include "profile_load.h"
#include "auth.h"

uint8_t modemRxBuff[MAX_MODEM_RX_BUFF];
uint8_t current_page  = 200;

void display_clearModemBuffer(){

	memset(modemRxBuff,0,sizeof(modemRxBuff));
	rxBufferCount=0;

}


void display_monitorRunningParametersFromDisplay(displayParams *display,uint8_t *displayUartFlag ,	float currenttime )
{

	uint8_t tempbuff[MAX_MODEM_RX_BUFF];
	uint8_t indexX			= 0	;
	uint8_t size			= 0 ;
	uint8_t setValueBuff[10]= { 0x00 } ;
	char 	*c 				= NULL ;
	uint8_t runCmdBuff[]	= { 0x5A, 0xA5, 0x06, 0x83, 0x17, 0x00, 0x01, 0x00, 0x01 }	;
	uint8_t StopCmdBuff[]	= { 0x5A, 0xA5, 0x06, 0x83, 0x18, 0x00, 0x01, 0x10, 0x00 } 	;
	uint8_t mmhgClearBuff[]	= { 0x5A, 0xA5, 0x06, 0x83, 0x10, 0x00, 0x01, 0x00, 0x00 }	;
	uint8_t timeClearBuff[]	= { 0x5A, 0xA5, 0x06, 0x83, 0x30, 0x00, 0x01, 0x00, 0x00 }	;
	uint8_t setPointAddr[]	= { 0x0F, 0xFF } ;
	uint8_t setMinAddr[]	= { 0x11, 0xFF } ;
	uint8_t setSecAddr[]	= { 0x12, 0xFF } ;

	/*@breif this condition to check flag for uart interrupt trigger	 */

	  if(*displayUartFlag == 1 )
	  {
		  HAL_Delay(5);

		  for(int i=0; i< rxBufferCount ; i++)
		  {
			  tempbuff[i] = modemRxBuff[i];
		  }
		  display_clearModemBuffer();

		  tempbuff[sizeof(tempbuff) - 1 ]					=	'\0'	;
		  runCmdBuff[sizeof(runCmdBuff) -  1 ] 				=	'\0'	;
		  StopCmdBuff[sizeof(StopCmdBuff) - 1 ]				=	'\0'	;
		  mmhgClearBuff[sizeof(mmhgClearBuff) - 1]			=	'\0'	;
		  timeClearBuff[sizeof(timeClearBuff) - 1]			=	'\0'	;
		  setPointAddr[sizeof(setPointAddr) - 1]			=	'\0' 	;
		  setMinAddr[sizeof(setMinAddr) - 1 ]				=	'\0'	;
		  setSecAddr[sizeof(setSecAddr) - 1]				=	'\0'	;

		  /* @ brief this below code check received buff have Run command or not  */
//		  c	= 	strstr((char *)tempbuff,(char *)runCmdBuff);
//		  if( c	!=	NULL )
//		  {
//			  display->ControlSystemFlag	= RUN_STATE;
//			  display->controlTimeFlag		=	1	;
//			  display->runTime = currenttime ;
//			  display->min = 0	;
//			  uint8_t minute_buff[] = {0x5A, 0xA5, 0x05, 0x82, 0x15, 0x00, 0x00, 0x00 };
//			  HAL_UART_Transmit(&huart2, &minute_buff, sizeof(minute_buff), HAL_MAX_DELAY);
//
//		  }
//		  c = NULL ;
//		  c	= 	strstr((char *)tempbuff,(char *)StopCmdBuff);
//		  if(c != NULL)
//		  {
//			  display->ControlSystemFlag = STOP_STATE ;
//		  }
//		  c	= NULL ;
//		  c = strstr((char *)tempbuff,(char *)mmhgClearBuff);
//		  if(c != NULL)
//		  {
//			  display->ControlSystemFlag =  CLEAR_MMHG_STATE ;
//		  }
//		  c	= NULL ;
//		  c = strstr((char *)tempbuff,(char *)timeClearBuff);
//		  if( c != NULL)
//		  {
//			  display->ControlSystemFlag =	CLEAR_TIME_STATE ;
//		  }
		  c = NULL ;

		  /* @brief this below code snippet checks whether the received buffer has Setpoint or not to set MMHG threshold */
		  c = strstr((char *)tempbuff, (char *)setPointAddr);
		  if( c != NULL )
		  {
			  indexX = 0 ;
			  indexX = c - (char *)tempbuff ;


			  if(tempbuff[ indexX - 1 ]	==	0x83 )
			  {
				  size 		= tempbuff[ indexX + 4 ] ;
				  indexX 	= indexX + 5 ;

				  for(uint8_t i =0; i< size; i++)
				  {
					  setValueBuff[i] = tempbuff[indexX] ;
					  indexX++;
				  }
				  display->setpointt = atoi(setValueBuff);
				  memset(tempbuff,0,sizeof(tempbuff));
				  memset(setValueBuff,0,sizeof(setValueBuff));

			  }

		  }
		  c = NULL ;

		  /* @brief this below code snippet checks whether the received buffer has Min value or not to set time */
		  c = strstr((char *)tempbuff, (char *)setMinAddr);
		  if( c != NULL)
		  {
			  indexX =0;
			  indexX = c - ( char *)tempbuff ;
			  if(tempbuff[ indexX - 1 ]	==	0x83 )
			  {
				  size 		= tempbuff[ indexX + 4 ] ;
				  indexX 	= indexX + 5 ;

				  for(uint8_t i =0; i< size; i++)
				  {
					  setValueBuff[i] = tempbuff[indexX] ;
					  indexX++;
				  }
				  display->setTimeInMin = atoi(setValueBuff);
				  memset(tempbuff,0,sizeof(tempbuff));
				  memset(setValueBuff,0,sizeof(setValueBuff));
			  }

		  }
		  c = NULL ;
		  /* @brief this below code snippet checks whether the received buffer has Sec value or not to set time */
		  c = strstr((char *)tempbuff, (char *)setSecAddr);
		  if( c != NULL)
		  {
			  indexX =0;
			  indexX = c - ( char *)tempbuff ;
			  if(tempbuff[ indexX - 1 ]	==	0x83 )
			  {
				  size 		= tempbuff[ indexX + 4 ] ;
				  indexX 	= indexX + 5 ;

				  for(uint8_t i =0; i< size; i++)
				  {
					  setValueBuff[i] = tempbuff[indexX] ;
					  indexX++;
				  }
				  display->setTimeInSec = atoi(setValueBuff);
				  memset(tempbuff,0,sizeof(tempbuff));
				  memset(setValueBuff,0,sizeof(setValueBuff));
			  }

		  }
		  *displayUartFlag = 0;
	  }

}



void display_mmhgValueUpdateToDisplay( float mmhg,uint8_t runStopFlag)
{

	  uint8_t _mmhgPayLoad[50]  ; //= {0x5A ,0xA5, 0x07 ,0x82 ,0x14 ,0x00};
	  uint8_t _mmhglen 	=	sizeof(_mmhgPayLoad);

	  memset(_mmhgPayLoad,0,_mmhglen);




	  _mmhgPayLoad[0]	=	0x5A	;
	  _mmhgPayLoad[1]	=	0xA5	;
	  _mmhgPayLoad[2]	=	0x06	;
	  _mmhgPayLoad[3]	=	0x82	;
	  _mmhgPayLoad[4]	=	0x14	;
	  _mmhgPayLoad[5]	=	0x00	;


	  uint64_t 	_mmhg		 = (int)(mmhg) ;

//	  uint8_t exp[20];
//	  memset(exp,0,sizeof(exp));
//	  sprintf(exp,"mmhg:%d\n",_mmhg);
//
//	  HAL_UART_Transmit(&huart1, &exp, sizeof(exp), HAL_MAX_DELAY);

	  uint8_t 	iteration 	 =	0 	;
	  uint8_t 	arr[20] ;
	  uint8_t	j			 =	0	;
	  memset(arr, 0 ,sizeof(arr));

	  while(_mmhg>0)
	  {
		  _mmhg 			= _mmhg/10		;

		  iteration++;
	  }

//	  _mmhg =	(int)(mmhg);

	  sprintf(&arr,"%03d",(int)(mmhg));


	  for(uint8_t i= 6 ;i <=6+iteration ; i++)
	  {
		  _mmhgPayLoad[i] =  arr[j];
		  j++;
	  }

//	  if(runStopFlag != 2)//stop button clicked if value is 2
//	  {
		  HAL_UART_Transmit(&huart2, &_mmhgPayLoad, 9, HAL_MAX_DELAY);
//	  }

	  memset(_mmhgPayLoad,0,_mmhglen);


}


static void display_secUpdate(controller_params *display )
{
	uint8_t _arr[100];
	memset(_arr,0, sizeof(_arr));

	_arr[0]		= 	0x5A 	;
	_arr[1]		= 	0xA5	;
	_arr[2]		=	0x05	;
	_arr[3]		=	0x82	;
	_arr[4]		=	0x16	;
	_arr[5]		=	0x00	;


	uint8_t _sec		=	(display->sec)	;
	uint8_t arr[10] 			;
	uint8_t iter		=	0	;
	uint8_t j			=	0	;

	memset(arr,0,sizeof(arr));


	while(_sec > 0)
	{
		_sec 		=	_sec/10		;
		iter++;
	}
	sprintf(&arr,"%02d",(display->sec));

	for(uint8_t i= 6 ; i<=6+iter ;i++)
	{
		_arr[i] = arr[j];
		j++;
	}
	if( (display->runStopButton != 2) )
	{
		HAL_UART_Transmit(&huart2, &_arr, 8, HAL_MAX_DELAY);
	}

	memset(_arr,0,sizeof(_arr));

}


void display_runTimeUpdateToDisplay(controller_params *display,uint64_t currenttime)
{
	uint8_t _arr[100];
	memset(_arr,0, sizeof(_arr));



	uint8_t buff[100];
	memset(buff,0, sizeof(buff));
	uint64_t  ms = currenttime -	display->runTime	;
	display->sec = (ms/1000);

	display_secUpdate(display);

	_arr[0]		= 	0x5A 	;
	_arr[1]		= 	0xA5	;
	_arr[2]		=	0x05	;
	_arr[3]		=	0x82	;
	_arr[4]		=	0x15	;
	_arr[5]		=	0x00	;


	if(display->sec == 60 )
	{
		display->runTime = currenttime ;
		display->sec =0;
		display->min++;
//		memset(_arr,0,sizeof(_arr));
	}

	uint8_t _min		= (display->min)	;
	uint8_t arr[10] 			;
	uint8_t iter		=	0	;
	uint8_t j			=	0	;

	memset(arr,0,sizeof(arr));

	while(_min > 0)
	{
		_min 		=	_min/10		;
		iter++;
	}
	sprintf(&arr,"%02d",display->min);

	for(uint8_t i= 6 ; i<=6+iter ;i++)
	{
		_arr[i] = arr[j];
		j++;
	}

	if( ( display->runStopButton != 2 )  )//stop button value 2
	{
		HAL_UART_Transmit(&huart2, _arr, 8, HAL_MAX_DELAY);
	}


}



static void getTargetAddr(uint8_t *_arr, uint8_t _arrSize,uint16_t targetAddr , uint8_t value)
{
	_arr[0]		= 	0x5A 	;
	_arr[1]		= 	0xA5	;
	_arr[2]		=	0x05	;
	_arr[3]		=	0x82	;
	_arr[5]		=	targetAddr>>0	;
	_arr[4]		=	targetAddr>>8 	;

//		uint8_t data[30];
//		memset(data,0,sizeof(data));
//		sprintf(data," tr :%d\n",targetAddr>>8);
//	uint8_t data = targetAddr>>0 ;
//		HAL_UART_Transmit(&huart1, &data, sizeof(data), HAL_MAX_DELAY);

	uint8_t _srNo		=	value	;
	uint8_t arr[10] 			;
	uint8_t iter		=	0	;
	uint8_t j			=	0	;


	memset(arr,0,sizeof(arr));


	while(_srNo > 0)
	{
		_srNo 		=	_srNo/10		;
		iter++;
	}
	sprintf(&arr,"%02d",value);


	for(uint8_t i= 6 ; i<8 ;i++)
	{
		_arr[i] = arr[j];
		j++;
	}


}

static void getTargetAddrfor16bit(uint8_t *_arr, uint8_t _arrSize,uint16_t targetAddr , uint16_t value)
{
	_arr[0]		= 	0x5A 	;
	_arr[1]		= 	0xA5	;
	_arr[2]		=	0x06	;
	_arr[3]		=	0x82	;
	_arr[5]		=	targetAddr>>0	;
	_arr[4]		=	targetAddr>>8 	;

	uint16_t _srNo		=	value	;
	uint8_t arr[10] 			;
	uint8_t iter		=	0	;
	uint8_t j			=	0	;


	memset(arr,0,sizeof(arr));


	while(_srNo > 0)
	{
		_srNo 		=	_srNo/10		;
		iter++	;
	}
	sprintf(&arr,"%03d",value);


	for(uint8_t i= 6 ; i<10 ;i++)
	{
		_arr[i] = arr[j];
		j++;
	}
}

/*
 * profile write page methods are below
 */
void profile_write_serialNo_details_update(uint8_t serNo, ProfileWrieParamAddrs *writeProfileParamsAddrs, uint8_t *serialNoReadFlag, uint8_t *displayUartFlag)
{
	if(*serialNoReadFlag == 1)
	{
		/** below detials are for send serial NO. */

		uint8_t _arr[50] ;

		//below code is for write Serial number to display for eeprom
		memset(_arr , 0 , sizeof(_arr));
		getTargetAddr(_arr, sizeof(_arr),writeProfileParamsAddrs->srNoAddr , serNo) ;
		HAL_UART_Transmit(&huart2, &_arr, strlen(_arr), HAL_MAX_DELAY);
		HAL_Delay(100);

		//below code is for Read data from Eeprom based on Serial number
		memset(_arr,0,sizeof(_arr));
		uint8_t eepromRead[5] = {0};
		readEe24(eepromRead,sizeof(eepromRead),serNo);

		uint16_t __mmhg = eepromRead[1] << 0 | eepromRead[2] << 8 ;
//		uint8_t data[30];

		//below code is for write mmhg value to display from EEprom with respect to serial number
		memset(_arr , 0 , sizeof(_arr));
		getTargetAddrfor16bit(_arr, sizeof(_arr),writeProfileParamsAddrs->mmhgAddr, __mmhg) ;
		HAL_UART_Transmit(&huart2, &_arr, strlen(_arr), HAL_MAX_DELAY);
//		HAL_UART_Transmit(&huart1, &_arr, strlen(_arr), HAL_MAX_DELAY);
		HAL_Delay(100);

		//belowcode is for profile write min to display from eeprom with respect to Serial number
		memset(_arr , 0 , sizeof(_arr));
		getTargetAddr(_arr, sizeof(_arr),writeProfileParamsAddrs->minAddr, eepromRead[3]) ;
		HAL_UART_Transmit(&huart2, &_arr, strlen(_arr), HAL_MAX_DELAY);
		HAL_Delay(100);

		//below code is for profile write sec to display from eeprom with respect to Serial number
		memset(_arr , 0 , sizeof(_arr));
		getTargetAddr(_arr, sizeof(_arr),writeProfileParamsAddrs->secAddr, eepromRead[4]) ;
		HAL_UART_Transmit(&huart2, &_arr, strlen(_arr), HAL_MAX_DELAY);
		HAL_Delay(100);

		*serialNoReadFlag = 2;

//		*displayUartFlag = 0 ;
//		*serialNoReadFlag == 0 ;


	}

}
static void strdecat(char *str, uint8_t n) {
    size_t len = strlen(str);

    if (n >= len) {
        // If n is greater than or equal to the length of the string,
        // simply set the first character to the null terminator to empty the string.
        str[0] = '\0';
    } else {
        // Move the null terminator n positions from the end.
        str[len - n] = '\0';
    }
}

static void profile_page_change(uint8_t value)
{
//	if(addr == 0)//home Page
//	{

		uint8_t nextPage_buff[] = { 0x5A, 0xA5, 0x07, 0x82, 0x00, 0x84, 0x5A, 0x01, 00, value } ;
		HAL_UART_Transmit(&huart2, &nextPage_buff, sizeof(nextPage_buff), HAL_MAX_DELAY);
		current_page = PROFILE_HOME_PAGE ;
//	}


}

void profile_write_details_to_ee24(uint8_t serialNo ,uint8_t *writeButtonFlag, home_page_t *homePage_t, uint8_t *serialNoReadFlag, uint8_t *displayUartFlag, ProfileWrieParamAddrs *writeProfileParamsAddrs )
{

	if(*writeButtonFlag == 1)
	{
		uint8_t flag = 0;

		if(*serialNoReadFlag == 3)
		{
			flag = 1;
			ee24Params params = {
					.mmhg		=	homePage_t->mmhg,
					.setMin		=	homePage_t->setMin,
					.setSec		=	homePage_t->setSec,
					.serialNum	=	serialNo
			};
			writeEe24(&params);
			profile_page_change(HOME_PAGE_NUMBER);
			*serialNoReadFlag = 0 ;

		}
		else if( flag == 0)
		{
			uint8_t data[30];
			memset(data,0,sizeof(data));
			sprintf(data," write button clieked without serial No!!\n");
			HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
			uint8_t _arr[50] = { 0 } ;
			//below code is for write Warning to display for eeprom
			_arr[0]		= 	0x5A 	;
			_arr[1]		= 	0xA5	;
			_arr[2]		=	0x32	;
			_arr[3]		=	0x82	;
			_arr[5]		=	writeProfileParamsAddrs->warningAddr>>0		;
			_arr[4]		=	writeProfileParamsAddrs->warningAddr>>8 	;
			uint8_t * warningStr ="please enter the serial No:(";
			strcat(_arr,warningStr);
			HAL_UART_Transmit(&huart2, &_arr, strlen(_arr), HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart2, &_arr, strlen(_arr), HAL_MAX_DELAY);
//			HAL_Delay(500);
//			strdecat(_arr,strlen(warningStr));
//			HAL_UART_Transmit(&huart2, &_arr, strlen(_arr), HAL_MAX_DELAY);
//			uint8_t *warningStrEmp = ""
		}

		*writeButtonFlag = 0 ;
	}
//	*displayUartFlag = 0 ;

}

void profile_write_serialNo_read( uint8_t *displayUartFlag, uint8_t *op, uint8_t *serialNo_read_flag,uint8_t *write_button_flag) //,uint8_t rxBufferCount
{
	/** example packate  = 5A A5 0A 83 90 06 03 5A 02 39 38 FF FF #98 */
	uint8_t tempbuff[MAX_MODEM_RX_BUFF] = {0};
	char 	*c 				= NULL ;
	uint8_t indexX = 0;
	uint8_t size = 0 ;
	uint8_t receivedBuff[2]= {0} ;

	uint8_t read_serialNo_addr[] = { 0x90,0x06 } ;
	uint8_t home_page_buff[]	= { 0x5A, 0xA5, 0x06, 0x83, 0x99, 0x99, 0x01, 0x00, 0x01 }	;
	uint8_t write_button_buff[]	= { 0x5A, 0xA5, 0x06, 0x83, 0x90, 0x08, 0x01, 0x00, 0x01 }	;
	home_page_buff[sizeof(home_page_buff) -  1 ] 				=	'\0'	;
	read_serialNo_addr[sizeof(read_serialNo_addr) -  1 ] 		=	'\0'	;
	write_button_buff[sizeof(write_button_buff) -  1 ] 			=	'\0'	;

	if( *displayUartFlag == 1)
	{
		HAL_Delay(1);

		for(int i=0; i< rxBufferCount ; i++)
		{
			tempbuff[i] = modemRxBuff[i];
		}
		display_clearModemBuffer();
//		HAL_UART_Transmit(&huart1, &tempbuff, strlen(tempbuff), HAL_MAX_DELAY);

		c = strstr((char *)tempbuff, (char *)read_serialNo_addr ) ;
		if( c != NULL )
		{
			indexX = 0 ;
			indexX = c - (char *)tempbuff ;


			if(tempbuff[ indexX - 1 ]	==	0x83 )
			{
				if(tempbuff[ indexX - 2 ]	==	0x0A)
				{
					size		= 0 ;
					size 		= tempbuff[ indexX + 4 ] ;
					indexX 		= indexX + 5 ;

					for(uint8_t i =0; i< size; i++)
					{
						receivedBuff[i] = tempbuff[indexX] ;
						indexX++;
					}
					 *serialNo_read_flag = 1 ;//true
					 *op = atoi(receivedBuff);

				}
			}

		}
		c = NULL ;
		c = strstr((char *)tempbuff, (char *)home_page_buff ) ;
		if( c != NULL)
		{
			current_page 	= 	PROFILE_HOME_PAGE	;
		}
		c = NULL ;
		c = strstr((char *)tempbuff, (char *)write_button_buff ) ;
		if( c != NULL)
		{
			*write_button_flag = 1 ;//write command
		}


		*displayUartFlag = 0 ;

	}

}


void Page_validation(uint8_t *displayUartFlag, uint8_t *page_invoke)
{

	uint8_t tempbuff[MAX_MODEM_RX_BUFF];
	char 	*c 				= NULL ;

	uint8_t save_page_buff[]	= { 0x5A, 0xA5, 0x06, 0x83, 0x10, 0x01, 0x01, 0x00, 0x01 }	;
	uint8_t home_page_buff[]	= { 0x5A, 0xA5, 0x06, 0x83, 0x99, 0x99, 0x01, 0x00, 0x01 }	;
	uint8_t load_page_buff[]	= { 0x5A, 0xA5, 0x06, 0x83, 0x10, 0x02, 0x01, 0x00, 0x01 } 	;

	save_page_buff[sizeof(save_page_buff) -  1 ] 				=	'\0'	;
	home_page_buff[sizeof(home_page_buff) -  1 ] 				=	'\0'	;

	if(*displayUartFlag == 1 && *page_invoke == 0)
	{
		HAL_Delay(5);

		for(int i=0; i< rxBufferCount ; i++)
		{
			tempbuff[i] = modemRxBuff[i];
		}
		display_clearModemBuffer();
//		uint8_t data[30];
//		memset(data,0,sizeof(data));
//		sprintf(data," hm %d \n");
//		HAL_UART_Transmit(&huart1, &tempbuff, strlen(tempbuff), HAL_MAX_DELAY);


		c = strstr((char *)tempbuff, (char *)save_page_buff );
		if( c != 	NULL )
		{
			*page_invoke = 1 ;
			current_page = PROFILE_WRITE_PAGE ;
		}
		c = NULL ;
		c = strstr((char *)tempbuff, (char *)home_page_buff );
		if( c != NULL)
		{
			*page_invoke = 1 ;
			current_page = PROFILE_HOME_PAGE ;
		}
		c = NULL ;
		c = strstr((char *)tempbuff, (char *)load_page_buff );
		if( c != NULL)
		{
			current_page = PROFILE_LOAD_PAGE ;
		}
		*displayUartFlag = 0 ;
	}

}

/**
 * below code is written for Home Page
 */
void profile_home_read(uint64_t *currenttime, home_page_t *homePage_t,uint8_t *displayUartFlag, uint8_t *runStopFlag, uint8_t *timeOutFlag, controller_params *controllerParam)
{
	uint8_t tempbuff[MAX_MODEM_RX_BUFF] = {0};
	char 	*c 				= NULL ;
	uint8_t indexX = 0;
	uint8_t size = 0 ;
	uint8_t receivedBuff[10]= {0} ;
//	uint8_t setValueBuff[10]= { 0x00 } ;

	uint8_t profile_write_buff[]	= { 0x5A, 0xA5, 0x06, 0x83, 0x10, 0x90, 0x01, 0x00, 0x01 }	;
	uint8_t profile_load_buff[]		= { 0x5A, 0xA5, 0x06, 0x83, 0x10, 0x02, 0x01, 0x00, 0x01 }	;
	uint8_t setMmhgAddr[]	= { 0x0F, 0xFF } ;
	uint8_t setMinAddr[]	= { 0x11, 0xFF } ;
	uint8_t setSecAddr[]	= { 0x12, 0xFF } ;

	uint8_t runButtonBuff[]	= { 0x5A, 0xA5, 0x06, 0x83, 0x17, 0x00, 0x01, 0x00, 0x01 }	;
	uint8_t StopButtonBuff[]= { 0x5A, 0xA5, 0x06, 0x83, 0x18, 0x00, 0x01, 0x10, 0x00 } 	;



	profile_write_buff[sizeof(profile_write_buff) -  1 ] 				=	'\0'	;
	profile_load_buff[sizeof(profile_load_buff) -  1 ] 					=	'\0'	;
	setMmhgAddr[sizeof(setMmhgAddr) - 1]								=	'\0' 	;
	setMinAddr[sizeof(setMinAddr) - 1 ]									=	'\0'	;
	setSecAddr[sizeof(setSecAddr) - 1]									=	'\0'	;
	runButtonBuff[sizeof(runButtonBuff) - 1]							=	'\0'	;
	StopButtonBuff[sizeof(StopButtonBuff) - 1]							=	'\0'	;



	if( *displayUartFlag == 1)
	{
		HAL_Delay(1);

		for(int i=0; i< rxBufferCount ; i++)
		{
			tempbuff[i] = modemRxBuff[i];
		}

		display_clearModemBuffer();


		c = strstr((char *)tempbuff, (char *)profile_write_buff ) ;
		if( c != NULL )
		{

//			*page_invoke = 0 ;
			current_page = PROFILE_WRITE_PAGE ;
			uint8_t data[30];
			memset(data,0,sizeof(data));
			sprintf(data," write profile called \n");
			HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
		}

		c = NULL ;
		c = strstr((char *)tempbuff, (char *)profile_load_buff ) ;
		if( c != NULL )
		{
//			*page_invoke = 0 ;
			current_page = PROFILE_LOAD_PAGE ;
			uint8_t data[30];
			memset(data,0,sizeof(data));
			sprintf(data," load profile called \n");
			HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
		}
		c = NULL ;

		  /* @brief this below code snippet checks whether the received buffer has Setpoint or not to set MMHG threshold */
	    c = strstr((char *)tempbuff, (char *)setMmhgAddr);
	    if( c != NULL )
	    {
		    indexX = 0 ;
		    indexX = c - (char *)tempbuff ;


		  if(tempbuff[ indexX - 1 ]	==	0x83 )
		  {
			  size 		= tempbuff[ indexX + 4 ] ;
			  indexX 	= indexX + 5 ;

			  for(uint8_t i =0; i< size; i++)
			  {
				  receivedBuff[i] = tempbuff[indexX] ;
				  indexX++;
			  }
			  homePage_t->mmhg = atoi(receivedBuff);
			  memset(tempbuff,0,sizeof(tempbuff));
			  memset(receivedBuff,0,sizeof(receivedBuff));

		  }

	  }
	  c = NULL ;

	  /* @brief this below code snippet checks whether the received buffer has Min value or not to set time */
	  c = strstr((char *)tempbuff, (char *)setMinAddr);
	  if( c != NULL)
	  {
		  indexX =0;
		  indexX = c - ( char *)tempbuff ;
		  if(tempbuff[ indexX - 1 ]	==	0x83 )
		  {
			  size 		= tempbuff[ indexX + 4 ] ;
			  indexX 	= indexX + 5 ;

			  for(uint8_t i =0; i< size; i++)
			  {
				  receivedBuff[i] = tempbuff[indexX] ;
				  indexX++;
			  }
			  homePage_t->setMin = atoi(receivedBuff);
			  memset(tempbuff,0,sizeof(tempbuff));
			  memset(receivedBuff,0,sizeof(receivedBuff));
		  }

	  }
	  c = NULL ;
	  /* @brief this below code snippet checks whether the received buffer has Sec value or not to set time */
	  c = strstr((char *)tempbuff, (char *)setSecAddr);
	  if( c != NULL)
	  {
		  indexX =0;
		  indexX = c - ( char *)tempbuff ;
		  if(tempbuff[ indexX - 1 ]	==	0x83 )
		  {
			  size 		= tempbuff[ indexX + 4 ] ;
			  indexX 	= indexX + 5 ;

			  for(uint8_t i =0; i< size; i++)
			  {
				  receivedBuff[i] = tempbuff[indexX] ;
				  indexX++;
			  }
			  homePage_t->setSec = atoi(receivedBuff);
			  memset(tempbuff,0,sizeof(tempbuff));
			  memset(receivedBuff,0,sizeof(receivedBuff));
		  }
	  }
	  c = NULL ;
	  c = strstr((char *)tempbuff, (char *)runButtonBuff);
	  if(c!= NULL)
	  {
		  controllerParam->min = 0;
		  controllerParam->runTime = 0 ;
		  controllerParam->sec = 0 ;
		  *runStopFlag = 1	;//for run
		  *currenttime = 0 ;
		  *timeOutFlag = 0 ;
		  uint8_t _arr[50];
		  getTargetAddr(_arr, sizeof(_arr),0x1500,00 ) ;
		  HAL_UART_Transmit(&huart2, _arr, 8, HAL_MAX_DELAY);

	  }
	  c = NULL ;
	  c = strstr((char *)tempbuff, (char *)StopButtonBuff);
	  if(c!= NULL)
	  {
		  *runStopFlag = 2	;//for stop
	  }

	  *displayUartFlag = 0;
	}

}

/*
 * below code is for load page
 */
void profile_load_read(uint8_t *displayUartFlag,uint8_t *nextFlag, uint8_t *backFlag, uint8_t *applyFlag, PL_direction_params_t *direction_params)
{

	uint8_t tempbuff[MAX_MODEM_RX_BUFF] = {0};
	char 	*c 				= NULL ;
	uint8_t indexX = 0;
	uint8_t size = 0 ;
	uint8_t receivedBuff[10]= {0} ;

	uint8_t nextbutton_buff[]  = { 0x5A, 0xA5, 0x06, 0x83, 0x10, 0x26, 0x01, 0x00, 0x01 };
	uint8_t backbutton_buff[]  = { 0x5A, 0xA5, 0x06, 0x83, 0x10, 0x25, 0x01, 0x00, 0x01 };
	uint8_t homeButton_buff[]  = { 0x5A, 0xA5, 0x06, 0x83, 0x99, 0x99, 0x01, 0x00, 0x01 };
	uint8_t firstApply_buff[]  = { 0x5A, 0xA5, 0x06, 0x83, 0x10, 0x51, 0x01, 0x00, 0x01 };
	uint8_t secondApply_buff[] = { 0x5A, 0xA5, 0x06, 0x83, 0x10, 0x54, 0x01, 0x00, 0x01 };
	uint8_t thirdApply_buff[]  = { 0x5A, 0xA5, 0x06, 0x83, 0x10, 0x58, 0x01, 0x00, 0x01 };



	nextbutton_buff[sizeof(nextbutton_buff) -  1 ] 				=	'\0'	;
	backbutton_buff[sizeof(backbutton_buff) -  1 ] 				=	'\0'	;
	homeButton_buff[sizeof(homeButton_buff) -  1 ] 				=	'\0'	;
	firstApply_buff[sizeof(firstApply_buff) -  1 ] 				=	'\0'	;
	secondApply_buff[sizeof(secondApply_buff) -  1 ] 			=	'\0'	;
	thirdApply_buff[sizeof(thirdApply_buff) -  1 ] 				=	'\0'	;


	if( *displayUartFlag == 1)
	{
		HAL_Delay(1);

		for(int i=0; i< rxBufferCount ; i++)
		{
			tempbuff[i] = modemRxBuff[i];
		}

		display_clearModemBuffer();

		c = strstr((char *)tempbuff, (char *)nextbutton_buff);
		if( c!= NULL)
		{
			*nextFlag = 1;
		}
		c= NULL ;

		c = strstr((char *)tempbuff, (char *)backbutton_buff);
		if( c!= NULL)
		{
			*backFlag = 1;
		}
		*displayUartFlag = 0 ;

		c= NULL ;
		c = strstr((char *)tempbuff, (char *)homeButton_buff);
		if( c!= NULL)
		{
			current_page = PROFILE_HOME_PAGE ;
		}
		c= NULL ;
		c = strstr((char *)tempbuff, (char *)firstApply_buff);//FIRSTAPPLY BUTTON
		if( c!= NULL)
		{
			*applyFlag = 1;
		}
		c= NULL ;

		c = strstr((char *)tempbuff, (char *)secondApply_buff);//FIRSTAPPLY BUTTON
		if( c!= NULL)
		{
			*applyFlag = 2;
		}
		c= NULL ;

		c = strstr((char *)tempbuff, (char *)thirdApply_buff);//FIRSTAPPLY BUTTON
		if( c!= NULL)
		{
			*applyFlag = 3;
		}



		*displayUartFlag = 0 ;

	}
}



static void profile_load_update_values_uartFormate_8(uint8_t *eepromRead,uint8_t eepromReadSize, PL_params_t *lineXParams)
{
	uint8_t _arr[50] ;
	memset(_arr,0,sizeof(_arr));

	memset(_arr , 0 , sizeof(_arr));
	getTargetAddr(_arr, sizeof(_arr),lineXParams->srNoAddr,eepromRead[0] ) ;
	HAL_UART_Transmit(&huart2, &_arr, strlen(_arr), HAL_MAX_DELAY);
//	HAL_UART_Transmit(&huart1, &_arr, strlen(_arr), HAL_MAX_DELAY);
	HAL_Delay(1);

	uint16_t __mmhg = eepromRead[1] << 0 | eepromRead[2] << 8 ;
	memset(_arr , 0 , sizeof(_arr));
	getTargetAddrfor16bit(_arr, sizeof(_arr),lineXParams->mmhgAddr, __mmhg) ;
	HAL_UART_Transmit(&huart2, &_arr, strlen(_arr), HAL_MAX_DELAY);
//	HAL_UART_Transmit(&huart1, &_arr, strlen(_arr), HAL_MAX_DELAY);
//	HAL_Delay(100);
	HAL_Delay(1);

	//belowcode is for profile write min to display from eeprom with respect to Serial number
	memset(_arr , 0 , sizeof(_arr));
	getTargetAddr(_arr, sizeof(_arr),lineXParams->minAddr, eepromRead[3]) ;
		HAL_UART_Transmit(&huart2, &_arr, strlen(_arr), HAL_MAX_DELAY);
//	HAL_UART_Transmit(&huart1, &_arr, strlen(_arr), HAL_MAX_DELAY);
//	HAL_Delay(100);
	HAL_Delay(1);

	//below code is for profile write sec to display from eeprom with respect to Serial number
	memset(_arr , 0 , sizeof(_arr));
	getTargetAddr(_arr, sizeof(_arr),lineXParams->secAddr, eepromRead[4]) ;
		HAL_UART_Transmit(&huart2, &_arr, strlen(_arr), HAL_MAX_DELAY);
//	HAL_UART_Transmit(&huart1, &_arr, strlen(_arr), HAL_MAX_DELAY);
//	HAL_Delay(100);
	HAL_Delay(1);

}
static void push_load_value_homePage(uint16_t mmhg, uint8_t min, uint8_t sec)
{
	uint8_t _arr[50] ;
	memset(_arr,0,sizeof(_arr));

	memset(_arr , 0 , sizeof(_arr));
	getTargetAddrfor16bit(_arr, sizeof(_arr),MMHG_TO_HOME_PAGE_ADDR ,mmhg ) ;
	HAL_UART_Transmit(&huart2, &_arr, 9, HAL_MAX_DELAY);

	memset(_arr , 0 , sizeof(_arr));
	getTargetAddr(_arr, sizeof(_arr),MIN_TO_HOME_PAGE_ADDR, min ) ;
	HAL_UART_Transmit(&huart2, &_arr, 8, HAL_MAX_DELAY);

	memset(_arr , 0 , sizeof(_arr));
	getTargetAddr(_arr, sizeof(_arr),SEC_TO_HOME_PAGE_ADDR, sec ) ;
	HAL_UART_Transmit(&huart2, &_arr, 8, HAL_MAX_DELAY);


}

void profile_load_update_values(uint8_t *nextFlag , uint8_t *backFlag, uint8_t *applyFlag, home_page_t * homePage_t)
{
	static uint16_t e24_index = 0 ;
	static uint8_t nextcounter = 0;
	uint8_t eepromRead[5] = {0};

	PL_params_t lineOneParams = {
			.srNoAddr	=	FST_R_SRNO_ADDR	,
			.mmhgAddr	=	FST_R_MMHG_ADDR	,
			.minAddr	=	FST_R_MIN_ADDR	,
			.secAddr	=	FST_R_SEC_ADDR	,
			.applyaddr	=	FST_R_APPLY_ADDR

	};
	PL_params_t lineSecondParams = {
			.srNoAddr	=	SND_R_SRNO_ADDR	,
			.mmhgAddr	=	SND_R_MMHG_ADDR	,
			.minAddr	=	SND_R_MIN_ADDR	,
			.secAddr	=	SND_R_SEC_ADDR	,
			.applyaddr	=	SND_R_APPLY_ADDR

	};
	PL_params_t lineThirdParams = {
			.srNoAddr	=	TRD_R_SRNO_ADDR	,
			.mmhgAddr	=	TRD_R_MMHG_ADDR	,
			.minAddr	=	TRD_R_MIN_ADDR	,
			.secAddr	=	TRD_R_SEC_ADDR	,
			.applyaddr	=	TRD_R_APPLY_ADDR

	};
	if(*nextFlag == 9 )
	{
		memset(eepromRead,0,sizeof(eepromRead));
		readEe24(eepromRead,sizeof(eepromRead), e24_index);
		profile_load_update_values_uartFormate_8(&eepromRead, sizeof(eepromRead), &lineOneParams);

		memset(eepromRead,0,sizeof(eepromRead));
		readEe24(eepromRead,sizeof(eepromRead),e24_index+1);
		profile_load_update_values_uartFormate_8(&eepromRead, sizeof(eepromRead), &lineSecondParams);

		memset(eepromRead,0,sizeof(eepromRead));
		readEe24(eepromRead,sizeof(eepromRead),e24_index+2);
		profile_load_update_values_uartFormate_8(&eepromRead, sizeof(eepromRead), &lineThirdParams);

		e24_index = 3 ;

		*nextFlag = 0;
	}


	if(*nextFlag == 1)
	{
		nextcounter++ ;

		memset(eepromRead,0,sizeof(eepromRead));
		readEe24(eepromRead,sizeof(eepromRead), ( e24_index * nextcounter ) );
		profile_load_update_values_uartFormate_8(&eepromRead, sizeof(eepromRead), &lineOneParams);

		memset(eepromRead,0,sizeof(eepromRead));
		readEe24(eepromRead,sizeof(eepromRead),( e24_index * nextcounter )+1 );
		profile_load_update_values_uartFormate_8(&eepromRead, sizeof(eepromRead), &lineSecondParams);

		memset(eepromRead,0,sizeof(eepromRead));
		readEe24(eepromRead,sizeof(eepromRead),( e24_index * nextcounter )+2 );
		profile_load_update_values_uartFormate_8(&eepromRead, sizeof(eepromRead), &lineThirdParams);

		*nextFlag = 0;
	}

	if(*backFlag == 1)
	{
		nextcounter-- ;
		memset(eepromRead,0,sizeof(eepromRead));
		readEe24(eepromRead,sizeof(eepromRead), ( e24_index * nextcounter ) );
		profile_load_update_values_uartFormate_8(&eepromRead, sizeof(eepromRead), &lineOneParams);

		memset(eepromRead,0,sizeof(eepromRead));
		readEe24(eepromRead,sizeof(eepromRead),( e24_index * nextcounter )+1 );
		profile_load_update_values_uartFormate_8(&eepromRead, sizeof(eepromRead), &lineSecondParams);

		memset(eepromRead,0,sizeof(eepromRead));
		readEe24(eepromRead,sizeof(eepromRead),( e24_index * nextcounter )+2 );
		profile_load_update_values_uartFormate_8(&eepromRead, sizeof(eepromRead), &lineThirdParams);

		*nextFlag = 0 ;

		*backFlag = 0 ;
	}
	if(*applyFlag == 1)
	{
		memset(eepromRead,0,sizeof(eepromRead));
		readEe24(eepromRead,sizeof(eepromRead), ( e24_index * nextcounter ) );

		uint16_t __mmhg = eepromRead[1] << 0 | eepromRead[2] << 8 ;
		homePage_t->mmhg 		= 	__mmhg 			;
		homePage_t->setMin 		=	eepromRead[3]	;
		homePage_t->setSec 		=	eepromRead[4]	;

		profile_page_change(HOME_PAGE_NUMBER);
		push_load_value_homePage(homePage_t->mmhg , homePage_t->setMin, homePage_t->setSec);

		*applyFlag = 0 ;

	}

	if(*applyFlag == 2)
	{
		memset(eepromRead,0,sizeof(eepromRead));
		readEe24(eepromRead,sizeof(eepromRead), ( e24_index * nextcounter ) + 1 );

		uint16_t __mmhg = eepromRead[1] << 0 | eepromRead[2] << 8 ;
		homePage_t->mmhg 		= 	__mmhg 			;
		homePage_t->setMin 		=	eepromRead[3]	;
		homePage_t->setSec 		=	eepromRead[4]	;
		profile_page_change(HOME_PAGE_NUMBER);
		push_load_value_homePage(homePage_t->mmhg , homePage_t->setMin, homePage_t->setSec);


		*applyFlag = 0 ;
	}
	if(*applyFlag == 3)
	{
		memset(eepromRead,0,sizeof(eepromRead));
		readEe24(eepromRead,sizeof(eepromRead), ( e24_index * nextcounter ) + 2 );

		uint16_t __mmhg = eepromRead[1] << 0 | eepromRead[2] << 8 ;
		homePage_t->mmhg 		= 	__mmhg 			;
		homePage_t->setMin 		=	eepromRead[3]	;
		homePage_t->setSec 		=	eepromRead[4]	;

		profile_page_change(HOME_PAGE_NUMBER);
		push_load_value_homePage(homePage_t->mmhg , homePage_t->setMin, homePage_t->setSec);

		*applyFlag = 0 ;
	}

}

/*
 * AUTH: BELOW CODE IS FOR AUTH PAGE
 */
void auth_page_read(uint8_t *displayUartFlag, uint8_t *authFlag, ee24_auth_params_t *ee24_auth_params,uint8_t *aFlag, uint8_t *pageflag)
{
	uint8_t tempbuff[MAX_MODEM_RX_BUFF] = {0};
	memset(tempbuff,0,sizeof(tempbuff));
	char 	*c 				= NULL ;
	uint8_t indexX = 0;
	uint8_t size = 0 ;
	uint8_t receivedBuff[10]= {0} ;

	uint8_t userNameAddr_buff[] = { 0x70, 0xFF};
	uint8_t PasswordAddr_buff[] = { 0x71, 0xFF};
	uint8_t loginButtonAddr[] = { 0x5A, 0xA5, 0x06, 0x83, 0x73, 0xFF, 0x01, 0x00, 0x01 };

	userNameAddr_buff[ sizeof(userNameAddr_buff) - 1] = '\0'	;
	PasswordAddr_buff[ sizeof(PasswordAddr_buff) - 1] = '\0'	;
	loginButtonAddr[ sizeof(loginButtonAddr) -	1]	  =	'\0'	;


	if(*displayUartFlag == 1)
	{
		HAL_Delay(1);
		for(int i=0; i< rxBufferCount ; i++)
		{
			tempbuff[i] = modemRxBuff[i];
		}
//		HAL_UART_Transmit(&huart1, &tempbuff, strlen(tempbuff), HAL_MAX_DELAY);
		display_clearModemBuffer();

		c = strstr( (char *)tempbuff, (char *)userNameAddr_buff);
		if( c != NULL)
		{
			indexX =0;
			indexX = c - ( char *)tempbuff ;
			if(tempbuff[ indexX - 1 ]	==	0x83 )
			{
				size 		= tempbuff[ indexX + 4 ] ;
				indexX 	= indexX + 5 ;

				for(uint8_t i =0; i< size; i++)
				{
					receivedBuff[i] = tempbuff[indexX] ;
					indexX++;
				}
				ee24_auth_params->ID	=	atoi(receivedBuff) ;
				memset(receivedBuff, 0, sizeof(receivedBuff));
				memset(tempbuff, 0, sizeof(tempbuff));

				sprintf(receivedBuff,"id :%d,%d",ee24_auth_params->ID,*aFlag  );
				HAL_UART_Transmit(&huart1, &receivedBuff, strlen(receivedBuff), HAL_MAX_DELAY);
				memset(receivedBuff, 0, sizeof(receivedBuff));
			}

			++*aFlag ;
		}

		c = NULL ;
		c = strstr( (char *)tempbuff, (char *)PasswordAddr_buff);
		if( c != NULL)
		{
			indexX =0;
			indexX = c - ( char *)tempbuff ;

			if(tempbuff[ indexX - 1 ]	==	0x83 )
			{

				size 		= tempbuff[ indexX + 4 ] ;
				indexX 	= indexX + 5 ;
//
				for(uint8_t i =0; i< size; i++)
				{
//					receivedBuff[i] = tempbuff[indexX] ;
					ee24_auth_params->password[i] = tempbuff[indexX] ;
					indexX++ ;
				}

				memset(tempbuff, 0, sizeof(tempbuff));
				HAL_UART_Transmit(&huart1, &ee24_auth_params->password , strlen( ee24_auth_params->password ), HAL_MAX_DELAY);
				memset(receivedBuff, 0, sizeof(receivedBuff));

				++*aFlag ;
			}

		}
		c = NULL ;
		c = strstr( (char *)tempbuff, (char *)loginButtonAddr);
		if( c != NULL)
		{
			if( *aFlag  >= 3)
			{
//				readEe24_For_Auth_admin(ee24_auth_params);
				*pageflag = readEe24_For_Auth_admin(ee24_auth_params);
//				uint8_t data[30];
//				memset(data,0,sizeof(data));
//				sprintf(data," user\n" );
//				HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
				*aFlag = 1 ;

			}
			else
			{

				uint8_t data[30];
				memset(data,0,sizeof(data));
				sprintf(data," user id or password not clicked %d\n",*aFlag );
				HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
				*aFlag = 1 ;
			}
		}

		*displayUartFlag = 0 ;
	}
}
