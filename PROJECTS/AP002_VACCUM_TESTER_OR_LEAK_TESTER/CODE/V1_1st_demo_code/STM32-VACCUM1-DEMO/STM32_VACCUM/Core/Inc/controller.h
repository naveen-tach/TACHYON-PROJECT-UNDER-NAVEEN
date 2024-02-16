/*
 * controller.h
 *
 *  Created on: Dec 15, 2023
 *      Author: navee
 */

#ifndef INC_CONTROLLER_H_
#define INC_CONTROLLER_H_

//#include "myheader.h"
//#include "display.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "pid.h"

#define ADC_TO_VOLTAGE 1240.909

extern struct controller_params  controller_param;

typedef struct
{
	  volatile float kPa		;
	  volatile float mmhg 		;
	  volatile float adc		;
	  volatile float volt		;
	  volatile uint8_t min 		;
	  volatile uint8_t sec		;
	  volatile uint64_t runTime	;
	  uint8_t runStopButton 	;

}controller_params;

//float controller_getCalculated_PID_value(uint32_t *arr,	displayParams *displayparam,	 controller_params *controller,	pid_params *pid);
float controller_getCalculated_PID_value(uint32_t *arr,		uint16_t homepage_t_mmhg, controller_params *controller,	pid_params *pid);

float controller_calculateFilteredValueFloat(float arr[],uint8_t dataSize, float prevVal);
uint32_t controller_calculateFilteredValue(uint32_t data[], uint8_t dataSize, uint32_t prevAdc);

#endif /* INC_CONTROLLER_H_ */
