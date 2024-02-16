/*
 * controller.c
 *
 *  Created on: Dec 15, 2023
 *      Author: naveen
 */

#include "controller.h"





//float controller_getCalculated_PID_value(uint32_t *arr,	displayParams *displayparam, controller_params *controller,	pid_params *pid)

float controller_getCalculated_PID_value(uint32_t *arr,	uint16_t homepage_t_mmhg, controller_params *controller,	pid_params *pid)
{
	float arrval[200];

//	for(uint8_t i=0; i< 200 ; i++)
//	{
//		for (uint8_t j = 0; j < 200 - i - 1; j++)
//		{
//			if (arr[j] > arr[j + 1])
//			{
//				float temp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = temp;
//			}
//		}
//	}

	uint32_t temp_adc = controller_calculateFilteredValue(arr,sizeof(arr)/sizeof(arr[0]), controller->adc);

	controller->adc 	= temp_adc	;

	controller->volt = controller->adc /ADC_TO_VOLTAGE ;


	memset(arrval,0,sizeof(arrval));
	for(uint8_t i=0; i< sizeof(arrval)/sizeof(arrval[0]) ; i++)
	{

		arrval[i] =( controller->volt + 0.475 )/0.045 ;
	}

	controller->kPa = controller_calculateFilteredValueFloat(arrval,sizeof(arrval)/sizeof(arrval[0]) , controller->kPa);

	memset(arrval,0,sizeof(arrval));
	for(int i=0 ; i<sizeof(arrval) / sizeof(arrval[0]) ; i++)
	{
		arrval[i] =  760 - (  (controller->kPa) * 7.5001 ) ; //832.568
	}

	controller->mmhg = controller_calculateFilteredValueFloat(arrval,sizeof(arrval)/sizeof(arrval[0]) , controller->mmhg);

    memset(arrval,0,sizeof(arrval));
//	for(int i=0 ; i<sizeof(arrval) / sizeof(arrval[0]) ; i++)
//	{
//		  arrval[i] = displayparam->setpointt - controller->mmhg ;
//	}
	for(int i=0 ; i<sizeof(arrval) / sizeof(arrval[0]) ; i++)
	{
		  arrval[i] = homepage_t_mmhg - controller->mmhg ;
	}
	pid->error = controller_calculateFilteredValueFloat(arrval,sizeof(arrval)/sizeof(arrval[0]) , pid->error);

	float _ut = PID(pid ) ;
	pid->ut = _ut	;




}


float controller_calculateFilteredValueFloat(float arr[],uint8_t dataSize, float prevVal)
{
	float val =0;
	uint8_t counter =0;

	for(uint8_t i=0; i<dataSize ; i++)
	{

		val = val + arr[i];
		counter++;
	}
	val = val/counter ;

	return ( val + prevVal )/2 ;
}


uint32_t controller_calculateFilteredValue(uint32_t data[], uint8_t dataSize, uint32_t prevAdc)
{
	uint32_t filterValue =0;
	uint8_t count =0;
	for(uint8_t i=0 ; i<dataSize ;i++)
	{
		filterValue = filterValue + data[i];
		count++ ;
	}
	filterValue = filterValue /count ;

	uint32_t op = (prevAdc + filterValue )/2 ;
	return  op ;
}
