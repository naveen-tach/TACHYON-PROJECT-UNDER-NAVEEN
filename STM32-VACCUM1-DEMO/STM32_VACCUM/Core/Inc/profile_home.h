/*
 * profile_home.h
 *
 *  Created on: Dec 22, 2023
 *      Author: navee
 */

#ifndef INC_PROFILE_HOME_H_
#define INC_PROFILE_HOME_H_

#include "display.h"
#include "controller.h"
//#include <stdint.h>
//#include <string.h>
//#include <stdio.h>

extern ADC_HandleTypeDef hadc1;

typedef struct
{
	uint16_t	mmhg	;
	uint8_t		setMin	;
	uint8_t 	setSec	;

}home_page_t;

//below code is for profile home page
void profile_home_read(uint64_t *currenttime,home_page_t *homePage_t,uint8_t *displayUartFlag,  uint8_t *runStopFlag, uint8_t *timeOutFlag, controller_params *controllerParam);
void homePage_init(uint64_t *currenttime, home_page_t * homePage_t, uint8_t *displayUartFlag, pid_params *pid_param, controller_params *controllerParam);

//void pid_core_functionality(uint8_t runStopFlag,float ut, uint8_t *controlLogicFlag,uint8_t , uint8_t , uint8_t );
void pid_core_functionality(uint8_t runStopFlag, float ut, uint8_t *control, float currentMmhg, float targetMmhg);



#endif /* INC_PROFILE_HOME_H_ */
