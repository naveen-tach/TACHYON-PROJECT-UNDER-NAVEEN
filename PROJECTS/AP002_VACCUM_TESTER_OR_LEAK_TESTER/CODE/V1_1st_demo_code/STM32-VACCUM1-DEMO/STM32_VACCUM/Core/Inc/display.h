/*
 * display.h
 *
 *  Created on: Dec 15, 2023
 *      Author: naveen
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

//#include <stdint.h>
//#include <string.h>
//#include <stdio.h>


#include "myheader.h"
#include "controller.h"



#define RUN_STATE 1
#define STOP_STATE 2
#define CLEAR_MMHG_STATE 3
#define CLEAR_TIME_STATE 4

extern uint8_t modemRxBuff[MAX_MODEM_RX_BUFF];
extern uint8_t current_page ;



typedef struct
{
	volatile float 		 setpointt 			;
	volatile uint8_t	 setTimeInMin		;
	volatile uint8_t	 setTimeInSec		;
	volatile float 		 runTime 			;
	volatile uint8_t	 min				;
	volatile uint8_t	 sec				;
	volatile uint8_t 	ControlSystemFlag	;
	uint8_t 			controlTimeFlag		;

}displayParams;


void display_monitorRunningParametersFromDisplay(displayParams *display, uint8_t *displayUartFlag,	float currenttime);
void display_mmhgValueUpdateToDisplay( float mmhg,uint8_t ControlSystemFlag);

void display_runTimeUpdateToDisplay(controller_params *display , uint64_t currenttime);
void Page_validation(uint8_t *displayUartFlag, uint8_t *page_invoke);

//methods below are for profile write page
void profile_write_serialNo_details_update(uint8_t serNo, ProfileWrieParamAddrs *writeProfileParamsAddrs, uint8_t *flag, uint8_t *displayUartFlag);
void profile_write_serialNo_read( uint8_t *displayUartFlag,uint8_t *op, uint8_t *serialNo_read_flag,uint8_t *write_button_flag);





#endif /* INC_DISPLAY_H_ */
