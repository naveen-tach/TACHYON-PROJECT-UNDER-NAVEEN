/*
 * profile_home.c
 *
 *  Created on: Dec 22, 2023
 *      Author: navee
 */

#include "profile_home.h"



uint8_t controlLogicFlag 	=	1	;
uint64_t lasttime			=	0	;
uint8_t runStopFlag 		=	0	;//this flag is for run and stop button, value are update as 1 and  2 accordingly
//uint8_t controlLogicFlag 	=	2	;
uint8_t timeOutFlag 		=	0	;
uint8_t timerAcceptFlag 	=	0	;

void homePage_init(uint64_t *currenttime, home_page_t *homePage_t, uint8_t *displayUartFlag, pid_params *pidparams,controller_params *controllerParam)
{
	controllerParam->runStopButton = runStopFlag ;

	profile_home_read(currenttime,homePage_t, displayUartFlag, &runStopFlag, &timeOutFlag, controllerParam);



	HAL_ADC_PollForConversion(&hadc1,1000);

	pidparams->dt = ( *currenttime -lasttime );
	lasttime = *currenttime ;


	  uint32_t adc[200];
	  memset(adc , 0 , sizeof(adc));

	  for(uint8_t i=0 ; i<sizeof(adc) / sizeof(adc[0]) ; i++)
	  {
		  adc[i] = HAL_ADC_GetValue(&hadc1) ;
	  }

	  controller_getCalculated_PID_value(&adc, homePage_t->mmhg, controllerParam, pidparams);


	  uint8_t data[200];
	  memset(data,0,sizeof(data));
	  sprintf(data,"min :%d, sec:%d, homePage_t->setMin %d, homePage_t->sec %d,\n",controllerParam->min,controllerParam->sec, homePage_t->setMin, homePage_t->setSec);
	  sprintf(data, "LP Time : %.2f ; ADC : %.2f ; volt :%.2f, kPa : %.2f : mmhg : %.2f : error : %.2f, UT :%.2f, target :%d,  Min:%d , sec:%d \n ",	pidparams->dt, controllerParam->adc,controllerParam->volt,controllerParam->kPa , controllerParam->mmhg,pidparams->error,pidparams->ut,homePage_t->mmhg,homePage_t->setMin,homePage_t->setSec);
	  HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);

	  if((homePage_t->mmhg <= controllerParam->mmhg ) && (timerAcceptFlag == 0) && (runStopFlag == 1) )
	  {
		  timerAcceptFlag 			= 	1	;
		  controllerParam->sec 		=	0	;
		  controllerParam->min		=	0	;
		  *currenttime				=	0	;
		  controllerParam->runTime	=	0	;
		  uint8_t data[200];
		  memset(data,0,sizeof(data));
		  sprintf(data,"mmhg is met %d\n",*currenttime);
		  HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
	  }

	  if( (homePage_t->setSec == controllerParam->sec ) && (homePage_t->setMin == controllerParam->min ) && (timerAcceptFlag == 1) )
	  {
		  uint8_t data[200];
		  memset(data,0,sizeof(data));
		  sprintf(data,"min :%d, sec:%d, homePage_t->setMin %d, homePage_t->sec %d,\n",controllerParam->min,controllerParam->sec, homePage_t->setMin, homePage_t->setSec);
		  HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
		  runStopFlag = 2 ;
		  timerAcceptFlag = 0 ;
	  }

	  //CHECK TIME BEFORE GOING FOR PID CONTROL

//	  /* @breif this condition is for control pressure based on RUN & STOP Command */
	  pid_core_functionality(runStopFlag, (pidparams->ut), &controlLogicFlag,  controllerParam->mmhg, homePage_t->mmhg );
//	  /* @Display function call start from here */
	  display_mmhgValueUpdateToDisplay(controllerParam->mmhg, runStopFlag);

	  display_runTimeUpdateToDisplay(controllerParam, *currenttime);



}

