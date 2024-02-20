/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

uint8_t uartFlag = 0 ;
uint8_t flag = 0;
uint8_t uartRXBuff1[255] = { 0 } ;
uint8_t uartRXBuff2[255] = { 0 } ;
uint8_t uartRXBuff3[255] = { 0 } ;
uint8_t uartRxBuffCount1 = 0;
uint8_t uartRxBuffCount2 = 0;
uint8_t uartRxBuffCount3 = 0;
uint8_t data[255];

uint8_t UART2_RX_Buffer[20] ;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

static void removeAddr(uint8_t *source, uint8_t sourceSize)
{
	for(uint8_t i=0; i<sourceSize ; i++)
	{
		source[i] = source[i+1] ;
	}
}

void uart_bi_direction_init(uint8_t *uartFlag)
{

//	if(*uartFlag == 2)
//	{
//
//		  HAL_Delay(500);
//		  HAL_UART_Transmit(&huart1,&uartRXBuff2, uartRxBuffCount2, HAL_MAX_DELAY);
//		  memset(uartRXBuff2, 0, sizeof(uartRXBuff2));
//		  uartRxBuffCount2 = 0;
//		  *uartFlag == 0;
//
//
//	}
	if(*uartFlag == 1)
	{
		  HAL_Delay(100);
		  uint8_t addr = uartRXBuff1[0] ;
		  for(uint8_t i=0; i< uartRxBuffCount1; i++)
		  {
			  uartRXBuff1[i] = uartRXBuff1[i+1] ;
		  }

		  if( (addr - '0') == 3)
		  {
			  uartRxBuffCount1-- ;
			  HAL_UART_Transmit(&huart3,&uartRXBuff1,uartRxBuffCount1 , HAL_MAX_DELAY);
		  }
		  if( (addr - '0') == 2)
		  {
			  uartRxBuffCount1-- ;
			  HAL_UART_Transmit(&huart2,&uartRXBuff1, uartRxBuffCount1, HAL_MAX_DELAY);
		  }
		  memset(uartRXBuff1, 0, sizeof(uartRXBuff1));
		  uartRxBuffCount1 = 0;
		  *uartFlag == 0 ;

	}





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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  HAL_UART_Receive_IT(&huart2,&uartRXBuff2[uartRxBuffCount2],1);
  HAL_UART_Receive_IT(&huart1,&uartRXBuff1[uartRxBuffCount1],1);
  HAL_UART_Receive_IT(&huart3,&uartRXBuff3[uartRxBuffCount3],1);
//  HAL_UART_Transmit_IT(&huart1,&(huart->Instance->RDR), 1);

//  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(USART1_IRQn);
//
//  HAL_NVIC_SetPriority(USART2_IRQn, 2, 0);
//  HAL_NVIC_EnableIRQ(USART2_IRQn);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

//	  if(uartFlag == 2)
//	  {
//
//		  HAL_Delay(100);
//		  uint8_t dtt[255];
//		  memcpy(dtt,uartRXBuff2,uartRxBuffCount2);
//		  HAL_UART_Transmit(&huart1, &uartRXBuff2, uartRxBuffCount2, HAL_MAX_DELAY);
//		  HAL_UART_Transmit_DMA(&huart1, &uartRXBuff2, uartRxBuffCount2);
////		  uartFlag = 0;
//		  memset(uartRXBuff2,0,sizeof(uartRXBuff2));
//		  uartRxBuffCount2 = 0;
//
//
//	  }
//	  if(uartFlag == 1)
//	  {
//
//		  HAL_Delay(100);
//		  uint8_t dtt[255];
//		  memcpy(dtt,uartRXBuff1,uartRxBuffCount1);
//		  HAL_UART_Transmit(&huart2, &uartRXBuff1, uartRxBuffCount1, HAL_MAX_DELAY);
////		  HAL_UART_Transmit_DMA(&huart2, &uartRXBuff1, uartRxBuffCount1);
//		  uartFlag = 0;
//		  memset(uartRXBuff1,0,sizeof(uartRXBuff1));
//		  uartRxBuffCount1 = 0;
//
//
//	  }

	  uart_bi_direction_init(&flag);

//	  	if( flag == 2)
//		{
//	  		flag = 0 ;
//	  		HAL_Delay(1000);
//	  		HAL_UART_Transmit(&huart1,&uartRXBuff2, uartRxBuffCount2, HAL_MAX_DELAY);
//	  		memset(uartRXBuff2, 0, sizeof(uartRXBuff2));
//	  		uartRxBuffCount2 = 0 ;
//
//		}
  }

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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_ENABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_EnableFifoMode(&huart1) != HAL_OK)
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
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_ENABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_ENABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

  if(huart == &huart2)
  {
	  HAL_UART_Transmit(&huart1,&(huart->Instance->RDR), 1, 0);
	  HAL_UART_Receive_IT(&huart2,&uartRXBuff2[uartRxBuffCount2],1);
  }
  if(huart == &huart3)
  {
	  HAL_UART_Transmit(&huart1,&(huart->Instance->RDR), 1, 0);
	  HAL_UART_Receive_IT(&huart3,&uartRXBuff3[uartRxBuffCount3],1);
  }
  if(huart == &huart1)
  {
	  uartRXBuff1[uartRxBuffCount1++] =  huart->Instance->RDR;
	  flag = 1 ;
	  HAL_UART_Receive_IT(&huart1,&uartRXBuff1[uartRxBuffCount1],1);
  }

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
