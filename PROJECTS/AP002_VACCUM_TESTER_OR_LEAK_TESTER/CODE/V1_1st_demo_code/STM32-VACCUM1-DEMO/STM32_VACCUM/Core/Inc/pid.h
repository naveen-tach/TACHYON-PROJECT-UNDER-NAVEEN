/*
 * pid.h
 *
 *  Created on: Dec 15, 2023
 *      Author: naveen
 */

#ifndef INC_PID_H_
#define INC_PID_H_
#include <stdint.h>

typedef struct
{
	float 	kp				;
	float 	ki 				;
	float 	kd 				;

	float 	previouserror	;
	float 	error			;
	uint64_t 	dt			;
	float 	I				;

	float 	ut				;

}pid_params;

//float PID(float setpoint ,float messurement , float dt);
float PID( pid_params *pid);


#endif /* INC_PID_H_ */
