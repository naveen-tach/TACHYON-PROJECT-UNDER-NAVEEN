/*
 * profile_write.h
 *
 *  Created on: Dec 21, 2023
 *      Author: navee
 */

#ifndef INC_PROFILE_WRITE_H_
#define INC_PROFILE_WRITE_H_

#include "ee24.h"
#include "display.h"

#include "profile_home.h"


//uint16_t srNoAddr	;
//#define SRNOADDR 0X9002




typedef struct
{
//	uint8_t serNo ;
	 ee24Params * ee24Param ;

}profile_write_params;

void profile_write_Write(profile_write_params * profileParams) ;
void profile_write_show_data(profile_write_params * profileParams);

void writePage_init(uint8_t *displayUartFlag, home_page_t *homePage_t);


//display
void profile_write_details_to_ee24(uint8_t ,uint8_t *flag, home_page_t *homePage_t, uint8_t *serialNoReadFlag,uint8_t *displayUartFlag, ProfileWrieParamAddrs *writeProfileParamsAddrs);


#endif /* INC_PROFILE_WRITE_H_ */
