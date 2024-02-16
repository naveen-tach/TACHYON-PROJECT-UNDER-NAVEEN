/*
 * profile_load.c
 *
 *  Created on: Dec 23, 2023
 *      Author: navee
 */

#include "profile_load.h"

uint8_t nextFlag = 9 ;//9 IS FOR INITIAL PRINT LOAD PROFILE VALUE INSTANTLY WHEN ENTER TO LOAD PAGE
uint8_t backFlag = 0 ;
uint8_t applyFlag = 0;

void profile_load_init(uint8_t *displayUartFlag, home_page_t *homePage_t)
{
	PL_direction_params_t PL_direction_params = {
			.backButton_addr		=	FRH_R_BACK_ADDR		,
			.nextButton_addr		=	FTH_R_NEXT_ADDR		,
			.homeButton_addr		=	HOME_ADDR			,
			.Fst_R_ApplyBottun_addr	=	FST_R_APPLY_ADDR	,
			.Snd_R_ApplyBottun_addr	=	SND_R_APPLY_ADDR	,
			.Trd_R_ApplyBottun_addr	=	TRD_R_APPLY_ADDR
	};

	profile_load_update_values(&nextFlag, &backFlag, &applyFlag, homePage_t );
	profile_load_read(displayUartFlag,&nextFlag,&backFlag, &applyFlag,  &PL_direction_params);


//		uint8_t data[30];
//		memset(data,0,sizeof(data));
//		sprintf(data," tr :%d\n",homePage_t->setSec);
//		HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
}

