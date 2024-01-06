/*
 * profile_load.h
 *
 *  Created on: Dec 23, 2023
 *      Author: navee
 */

#ifndef INC_PROFILE_LOAD_H_
#define INC_PROFILE_LOAD_H_

#include "myheader.h"
#include "profile_home.h"

//FIRST ROW ADDRESS
#define FST_R_SRNO_ADDR 	0x1011
#define FST_R_MMHG_ADDR 	0x1021
#define FST_R_MIN_ADDR 		0x1031
#define FST_R_SEC_ADDR		0x1041
#define FST_R_APPLY_ADDR	0x1051

//SECOND ROW ADDRESS
#define SND_R_SRNO_ADDR 	0x1014
#define SND_R_MMHG_ADDR 	0x1024
#define SND_R_MIN_ADDR	 	0x1034
#define SND_R_SEC_ADDR		0x1044
#define SND_R_APPLY_ADDR	0x1054

//THIRD ROW ADREES
#define TRD_R_SRNO_ADDR 	0x1018
#define TRD_R_MMHG_ADDR 	0x1028
#define TRD_R_MIN_ADDR 		0x1038
#define TRD_R_SEC_ADDR		0x1048
#define TRD_R_APPLY_ADDR	0x1058

//TOP RIGHT CORNER HOME BUTTON
#define HOME_ADDR			0x9999

//FOURTH ROW ADDRESS
#define FRH_R_BACK_ADDR		0x1025
#define FTH_R_NEXT_ADDR		0x1026//3042

//UPDATE MMHG AND SET MIN AND SEC TO HOME PAGE
#define MMHG_TO_HOME_PAGE_ADDR	0X1000
#define MIN_TO_HOME_PAGE_ADDR 	0X1200
#define SEC_TO_HOME_PAGE_ADDR 	0X1300


typedef struct
{
	uint16_t applyAddr	;

}PL_applyAddr_t;

typedef struct
{
	uint16_t		backButton_addr 	;
	uint16_t 		nextButton_addr	;
	uint16_t 		homeButton_addr	;
	PL_applyAddr_t 	Fst_R_ApplyBottun_addr	;
	PL_applyAddr_t 	Snd_R_ApplyBottun_addr	;
	PL_applyAddr_t 	Trd_R_ApplyBottun_addr	;

}PL_direction_params_t;
typedef struct
{
	uint16_t 						srNoAddr	;
	uint16_t 						mmhgAddr	;
	uint16_t 						minAddr		;
	uint16_t 						secAddr		;
	PL_applyAddr_t 					applyaddr	;

}PL_params_t;


void profile_load_init(uint8_t *displayUartFlag, home_page_t *);
void profile_load_update_values(uint8_t *nextFlag, uint8_t *backFlag, uint8_t *applyFlag, home_page_t *);
void profile_load_read(uint8_t *displayUartFlag,uint8_t *nextFlag, uint8_t *backFlag, uint8_t *applyFlag, PL_direction_params_t *);

#endif /* INC_PROFILE_LOAD_H_ */
