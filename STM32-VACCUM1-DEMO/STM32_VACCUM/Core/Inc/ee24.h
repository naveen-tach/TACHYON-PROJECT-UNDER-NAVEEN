/*
 * ee24.h
 *
 *  Created on: Dec 20, 2023
 *      Author: navee
 */

#ifndef INC_EE24_H_
#define INC_EE24_H_

#include "myheader.h"

#define EEPROM_ADDR 0xA0

extern I2C_HandleTypeDef hi2c1;



typedef struct
{
	uint8_t 	serialNum	;
	uint16_t 	mmhg		;
	uint8_t 	setMin		;
	uint8_t		setSec		;

}ee24Params;

typedef struct
{
	uint8_t ID			;
	uint8_t securityL	;
	uint8_t password[6]	;

}ee24_auth_params_t;

void writeEe24(ee24Params *param);
void clearAllEe24(uint8_t serNo);
void readEe24(uint8_t *data_read, uint8_t data_read_size, uint8_t serNo);





#endif /* INC_EE24_H_ */
