/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


#include "display.h"
#include "controller.h"
//#include "pid.h"
#include "myheader.h"

#include "profile_write.h"
#include "profile_home.h"
#include "profile_load.h"

#include "auth.h"

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

//uint32_t  adcData;
uint8_t data[200];
volatile uint64_t currenttime =0;
//float lasttime =0;

/*@brief this variables are used for control system*/

float arrval[200];

//uint8_t controlTimeFlag		=	0	;
uint8_t displayUartFlag 	=	0	;
uint8_t authFlag = 0;




/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

volatile unsigned long millis = 0;
volatile uint16_t rxBufferCount = 0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


static void main_Page_Functionality()
{

//	pidparams.dt = ( currenttime -lasttime );
//	lasttime = currenttime ;
//	HAL_ADC_PollForConversion(&hadc1,1000);
//
//	  uint32_t adc[200];
//	  memset(adc , 0 , sizeof(adc));
//
//	  for(uint8_t i=0 ; i<sizeof(adc) / sizeof(adc[0]) ; i++)
//	  {
//
//		  adc[i] = HAL_ADC_GetValue(&hadc1) ;
//	  }
//
//	  controller_getCalculated_PID_value(&adc, &displayParam, &controllerParam, &pidparams);
//
//
//	  sprintf(data, "LP Time : %.2f ; ADC : %u ; volt :%.2f, kPa : %.2f : mmhg : %.2f : error : %.2f, UT :%.2f, target :%.2f Min:%d , sec:%d \n ",	pidparams.dt, controllerParam.adc,controllerParam.volt,controllerParam.kPa , controllerParam.mmhg,pidparams.error,pidparams.ut,displayParam.setpointt,displayParam.setTimeInMin,displayParam.setTimeInSec);
//	  HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
//	  memset(arrval,0,sizeof(arrval));
//
//	  /* @breif this condition is for control pressure based on RUN & STOP Command */
//	  if(	(displayParam.ControlSystemFlag == RUN_STATE)	)
//	  {
//	//		  bangBangControllerOn(&pidparams)	;
//		  if(pidparams->ut >= -4  && pidparams->ut <= 4  && controlLogicFlag == 1)
//		  {
//
//			  HAL_GPIO_WritePin(VACCUM_SUCKER_GPIO_Port,VACCUM_SUCKER_Pin,1);
//			  HAL_GPIO_WritePin(VACCUM_PRESSURE_GPIO_Port,VACCUM_PRESSURE_Pin,1);
//			  HAL_Delay (5);
//	//			  sprintf(data, "in btw suck & vaccume\n");
//	//			  HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
//	//			  memset(arrval,0,sizeof(arrval));
//
//			  if( pidparams->ut >=4)
//			  {
//				  controlLogicFlag = 0;
//			  }
//
//		  }
//	//		  vaccume_sucker_call(&pidparams)	;
//		  if( (pidparams->ut >= -4 && controlLogicFlag == 0) || (pidparams->ut >= 5) )
//		   {
//				  HAL_GPIO_WritePin(VACCUM_SUCKER_GPIO_Port,VACCUM_SUCKER_Pin,0);
//				  HAL_GPIO_WritePin(VACCUM_PRESSURE_GPIO_Port,VACCUM_PRESSURE_Pin,1);
//				  HAL_Delay (5);
//	//				  sprintf(data, "full suck\n");
//	//				  HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
//	//				  memset(arrval,0,sizeof(arrval));
//
//				  if(pidparams->ut <= -3 )
//				  {
//					  controlLogicFlag =1 ;
//				  }
//		  }
//	//		  vaccume_blower_call(&pidparams)	;
//		  if(pidparams->ut < -7)
//		  {
//			  HAL_GPIO_WritePin(VACCUM_SUCKER_GPIO_Port,VACCUM_SUCKER_Pin,0);
//			  HAL_GPIO_WritePin(VACCUM_PRESSURE_GPIO_Port,VACCUM_PRESSURE_Pin,0);
//			  HAL_Delay (5);
//		  }
//	  }
//
//	  else if(	(displayParam.ControlSystemFlag == STOP_STATE)	)
//	  {
//	//		  bangBangControllerOff()	;
//		  HAL_GPIO_WritePin(VACCUM_SUCKER_GPIO_Port,VACCUM_SUCKER_Pin,1);
//		  HAL_GPIO_WritePin(VACCUM_PRESSURE_GPIO_Port,VACCUM_PRESSURE_Pin,0);
//		  HAL_Delay (5);
//	  }
//
//	  if(displayParam.controlTimeFlag == 1){
//
//		  if(	displayParam.setTimeInMin == displayParam.min	)
//		  {
//			  if(	displayParam.setTimeInSec	==	displayParam.sec	)
//			  {
//				  displayParam.controlTimeFlag = 0;
//				  displayParam.ControlSystemFlag = STOP_STATE;
//			  }
//		  }
//	  }
//
//
//	  /* @Display function call start from here */
//
//	  display_monitorRunningParametersFromDisplay(&displayParam, &displayUartFlag,currenttime);
//	  display_mmhgValueUpdateToDisplay(controllerParam.mmhg, 1);
//	  display_runTimeUpdateToDisplay(&displayParam, currenttime);


}

void pid_core_functionality(uint8_t runStopFlag, float ut, uint8_t *control, float currentMmhg, float targetMmhg)
{

	if( runStopFlag == 1)
	{
		if( (ut >= 1) )
		{
			HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
			HAL_GPIO_WritePin(VACCUM_SUCKER_GPIO_Port,VACCUM_SUCKER_Pin,0);
			HAL_GPIO_WritePin(VACCUM_PRESSURE_GPIO_Port,VACCUM_PRESSURE_Pin,1);
			HAL_Delay (5);
		}
		else
		{

		  HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
		  HAL_GPIO_WritePin(VACCUM_SUCKER_GPIO_Port,VACCUM_SUCKER_Pin,1);
		  HAL_GPIO_WritePin(VACCUM_PRESSURE_GPIO_Port,VACCUM_PRESSURE_Pin,1);
		  HAL_Delay (5);
		}
//		if( currentMmhg >= targetMmhg+2 )
//		{
//			HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
//			HAL_GPIO_WritePin(VACCUM_SUCKER_GPIO_Port,VACCUM_SUCKER_Pin,1);
//			HAL_GPIO_WritePin(VACCUM_PRESSURE_GPIO_Port,VACCUM_PRESSURE_Pin,0);
//		}
	}
	else if( ( runStopFlag == 2 ) || currentMmhg > targetMmhg )//STOP BUTTON
	{
//		  uint8_t _data[20];
//		  sprintf(_data,"its in stop %d, %d\n",runStopFlag, timeOutFlag);
//		  HAL_UART_Transmit(&huart1, &_data, strlen(_data), HAL_MAX_DELAY);
		HAL_GPIO_WritePin(VACCUM_SUCKER_GPIO_Port,VACCUM_SUCKER_Pin,1);
		HAL_GPIO_WritePin(VACCUM_PRESSURE_GPIO_Port,VACCUM_PRESSURE_Pin,0);
		HAL_Delay (5);
	}

//	if( timeOutFlag != 1)
//	{
//		  uint8_t _data[20];
//		  sprintf(_data,"its in %d\n",runStopFlag);
//		  HAL_UART_Transmit(&huart1, &_data, strlen(_data), HAL_MAX_DELAY);
//	}
}

static void profile_page_change1(uint8_t value)
{

	uint8_t nextPage_buff[] = { 0x5A, 0xA5, 0x07, 0x82, 0x00, 0x84, 0x5A, 0x01,00,value } ;

	HAL_UART_Transmit(&huart2, &nextPage_buff, 10, HAL_MAX_DELAY);

}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */



  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2);

	HAL_UART_Receive_IT(&huart2,&modemRxBuff[rxBufferCount],1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_ADC_Start(&hadc1);
  HAL_GPIO_WritePin(VACCUM_PRESSURE_GPIO_Port,VACCUM_PRESSURE_Pin,1);
  HAL_Delay (100);
  HAL_GPIO_WritePin(VACCUM_SUCKER_GPIO_Port,VACCUM_SUCKER_Pin,1);
  HAL_Delay (100);

  // Start timer
  HAL_TIM_Base_Start(&htim2);
  //TODO: need to verify below line after code implimentaion
  display_clearModemBuffer();

//	TODO: need to uncomment below commented line for Home Page
  controller_params controllerParam =
  {
		  .kPa 				=	0.0f	,
		  .mmhg				=	0.0f	,
		  .adc				=	0.0f	,
		  .volt				=	0.0f	,
		  .runTime			=	0		,
		  .sec				=	0.0		,
		  .min				=	0.0		,
		  .runStopButton	=	0
  };


  displayParams displayParam =
  {
		  .min 					=	0	,
		  .sec					=	0	,
		  .runTime				=	0	,
		  .setTimeInMin			=	0	,
		  .setTimeInSec			=	0	,

		  .setpointt			=	0	,
		  .ControlSystemFlag	=	0	,
		  .controlTimeFlag		=	2
  };

  pid_params pidparams =
  {
		  .kp				=	2		,
		  .ki				=	0.01175	,
		  .kd				=	0.05	,

		  .dt				=	0.0f	,

		  .I				=	0.0f	,
		  .error			=	0.0f	,
		  .previouserror	=	0.0f	,

		  .ut				=	0.0f
  };
//
//
//  ee24Params SerialNubParam =
//  {
//		  .serialNum	=	1	,
//		  .mmhg			=	560	,
//		  .setMin		=	20	,
//		  .setSec		=	23
//  };

  uint8_t data[100] ;
  uint8_t  page_invoke = 1;

//  writeEe24(&SerialNubParam);
  
  home_page_t homePage_t =
  {
		  .mmhg		=	000	,
		  .setMin	=	0	,
		  .setSec	=	0	,
  };
  profile_page_change1(AUTH_PAGE_NUMBER);//AUTHENTICATION PAGE ADDRESS
//  ee24_auth_params_t auth_params =
//  {
//		  .ID = 1,
//		  .password = "1254567" ,
//  };
//  writeEe24_For_Auth_Admin(&auth_params);
//  	readEe24_For_Auth_admin(&auth_params);

  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */

	  auth_init(&displayUartFlag, &authFlag);
//		uint8_t data[30];
//		memset(data,0,sizeof(data));
//		sprintf(data," authFlag :%d\n",authFlag);
//		HAL_UART_Transmit(&huart1, &data, strlen(data), HAL_MAX_DELAY);
		if(authFlag == 1 )
		{
			 profile_page_change1(HOME_PAGE_NUMBER);
		}

	  while(authFlag == 1 )
	  {
			switch(current_page)
			{
				case ( PROFILE_WRITE_PAGE ) :
				{

					writePage_init(&displayUartFlag, &homePage_t);
					break ;
				}
				case ( PROFILE_HOME_PAGE |VACCUME_TEST_PAGE ) :
				{


					homePage_init(&currenttime, &homePage_t, &displayUartFlag, &pidparams, &controllerParam);

					break ;
				}
				case ( PROFILE_LOAD_PAGE ) :
				{
					profile_load_init( &displayUartFlag, &homePage_t);
					break ;
				}
			}
	  }






  }

  HAL_ADC_Stop(&hadc1);
//  HAL_Delay(1000);
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7200-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */



  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, VACCUM_PRESSURE_Pin|VACCUM_SUCKER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : VACCUM_PRESSURE_Pin VACCUM_SUCKER_Pin */
  GPIO_InitStruct.Pin = VACCUM_PRESSURE_Pin|VACCUM_SUCKER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{


	if( htim->Instance == TIM2 )
	{
		currenttime++;

	}

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
   */
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

  if(huart == &huart2){
	  displayUartFlag =1;

	if(rxBufferCount > MAX_MODEM_RX_BUFF){
		rxBufferCount = 0;
	}
    modemRxBuff[rxBufferCount] = huart->Instance->DR;
    rxBufferCount++;



  }
    HAL_UART_Receive_IT(&huart2,&modemRxBuff[rxBufferCount],1);
//    HAL_UART_Transmit(&huart1, &modemRxBuff, strlen(modemRxBuff), 1);

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
