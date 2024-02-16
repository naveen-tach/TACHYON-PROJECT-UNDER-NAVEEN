/*
 * ee24.c
 *
 *  Created on: Dec 20, 2023
 *      Author: navee
 */



#include "stm32f1xx_hal.h"
#include "ee24.h"


  void writeEe24(ee24Params *param)
  {
	  uint8_t data_write[5];
	  uint8_t k = 0;
	  memset(data_write,0,sizeof(data_write));

	  data_write[0]	=	param->serialNum	;
	  data_write[1]	=	(param->mmhg>>0)	;
	  data_write[2]	=	(param->mmhg>>8)	;
	  data_write[3]	=	param->setMin		;
	  data_write[4]	=	param->setSec		;

	  uint8_t index = param->serialNum * 5 - 5 ;

		uint8_t data[30];
		memset(data,0,sizeof(data));
		sprintf(data,"write: :%d : %d : %d: %d:%d\n",data_write[0],data_write[1],data_write[2],data_write[3],data_write[4]);
		HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);

	  for(uint8_t i=1;i<10;i++)
	  {
	      if(index >= 16*i - 4)
	      {
	          k = i;
	      }
	  }

	  index = index+ k;


	  if (HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, index, 1, &data_write , sizeof(data_write), HAL_MAX_DELAY) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  HAL_Delay(2000);

  }

  void clearAllEe24(uint8_t serNo)
  {
	  uint8_t temp[5];
	  memset(temp,0,sizeof(temp));

	  uint8_t index = serNo * 5 - 5 ;


	  if (HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, index, 1, &temp , sizeof(temp), HAL_MAX_DELAY) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  HAL_Delay(2000);


  }

  void readEe24(uint8_t *data_read, uint8_t data_read_size, uint8_t serNo)
  {
	  uint8_t k = 0;
	  memset(data_read,0,data_read_size);

	  uint8_t index = serNo * 5 - 5 ;

	  for(uint8_t i=1;i<10;i++)
	  {
	      if(index >= 16*i - 4)
	      {
	          k = i ;
	      }
	  }

	  index = index+ k;

	  if (HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDR, index, 1, data_read, data_read_size, HAL_MAX_DELAY) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  HAL_Delay(2000);
	  uint8_t data[20];
	  memset(data,0,sizeof(data));
	  sprintf(data,"sr no:%d,idx :%d \n",serNo,index);
	  HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
	  for(uint8_t i=0;i<5;i++)
	  {
		  memset(data,0,sizeof(data));
		  sprintf(data,"data is [%d] :%d \n",i,data_read[i]);
		  HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
	  }
  }


  /*
   * BELOW CODE IS FOR AUTHENTICATION
   */

  // @breif below function is for read authentication values
  char readEe24_For_Auth_admin(ee24_auth_params_t *auth_params)
  {
//		uint8_t data[30];
//		memset(data,0,sizeof(data));
//		sprintf(data," tr :%d\n",target);
//		HAL_UART_Transmit(&huart1, &auth_params->ID, strlen(auth_params->ID), HAL_MAX_DELAY);
//		HAL_UART_Transmit(&huart1, &auth_params->password, strlen(auth_params->password), HAL_MAX_DELAY);
	  uint8_t flag = 0 ;//true
	  uint8_t data_read[8];
	  memset(data_read,0,sizeof(data_read));
	  uint8_t i = 0;
//	  uint8_t data[8];
	  uint8_t k=2;
//
//
//
	  if (HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDR, 600, 1, &data_read, sizeof(data_read), HAL_MAX_DELAY) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  HAL_Delay(2000);

//	  sprintf(data," 1 :%d, ID :%d \n",data_read[1],auth_params->ID);
//	  HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);

	  if(auth_params->ID == data_read[1])
	  {
		  for( i=0; i<6; i++)
		  {
			  if( auth_params->password[i] == data_read[k])
			  {
					uint8_t data[30];
					memset(data,0,sizeof(data));
					sprintf(data," its matched %d\n",i);
					HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
			  }
			  else
			  {
					uint8_t data[30];
					memset(data,0,sizeof(data));
					sprintf(data,"please enter correct password\n");
					HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
					break ;
			  }

			  k++;
		  }
		  if(i == 6)
			  flag = 1 ;

	  }
	  else
	  {
			uint8_t data[30];
			memset(data,0,sizeof(data));
			sprintf(data,"please enter admin user id\n");
			HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
	  }
	  return flag ;


  }

  // @breif below function
//  void writeEe24_For_Auth(ee24_auth_params_t *auth_params, uint8_t serNo)
//  {
//	  uint64_t index = 600 + ( 5*serNo ) ;
//
//	  uint8_t data_write[8];
//	  uint8_t k = 1;
//	  memset(data_write,0,sizeof(data_write));
//
//	  data_write[0] 	= 	auth_params->ID			;
//
//	  for(uint8_t i=0; i<4; i++)
//	  {
//		  data_write[k] = 	auth_params->password[i]	;
//		  k++;
//	  }
//	  if (HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, index, 1, &data_write , sizeof(data_write), HAL_MAX_DELAY) != HAL_OK)
//	  {
//	    Error_Handler();
//	  }
//	  HAL_Delay(2000);
//
//
//  }

  void writeEe24_For_Auth_Admin(ee24_auth_params_t *auth_params)
  {
	  uint64_t index = 600 ;
	  uint8_t data_write[9];
	  uint8_t k = 2 ;
	  memset(data_write,0,sizeof(data_write));

	  data_write[0] 	= 	0 ; //auth_params->securityL	;
	  data_write[1]		=	auth_params->ID			;

	  for(uint8_t i=0; i<6; i++)
	  {
		  data_write[k] = 	auth_params->password[i] ;
		  k++;
	  }
		uint8_t data[30];
		memset(data,0,sizeof(data));
//		sprintf(data," admin:\n");
//		HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
//		HAL_UART_Transmit(&huart1, &data_write, 8, HAL_MAX_DELAY);
	  if (HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, index, 1, &data_write , sizeof(data_write), HAL_MAX_DELAY) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  HAL_Delay(2000);
  }

