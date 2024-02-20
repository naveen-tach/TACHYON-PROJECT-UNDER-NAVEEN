/*
 * auth.h
 *
 *  Created on: Jan 1, 2024
 *      Author: navee
 */

#ifndef INC_AUTH_H_
#define INC_AUTH_H_

#include <stdint.h>
#include "myheader.h"
#include "ee24.h"


void auth_init(uint8_t *displayUartFlag, uint8_t *authFlag);

void auth_page_read(uint8_t *displayUartFlag, uint8_t *authFlag,ee24_auth_params_t *ee24_auth_params, uint8_t *aFlag, uint8_t *pageflag );


#endif /* INC_AUTH_H_ */
