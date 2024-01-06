/*
 * pid.c
 *
 *  Created on: Dec 15, 2023
 *      Author: navee
 */
#include "pid.h"

float PID( pid_params *pid)
{
	float P = (pid->kp) * (pid->error) ;

	  float i =pid->I* pid->ki * pid->dt * (pid->error);
//
//	  float D = kd * (previouserror);

	  pid->previouserror = pid->error;

	 return P+i ;

}


