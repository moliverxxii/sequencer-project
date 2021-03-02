/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define HT16K33_I2C_ADDRESS (0xE0)
#define I2C_BUFSIZE 40
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;
uint8_t I2CMasterBuffer[I2C_BUFSIZE];
static uint8_t blackBoard[I2C_BUFSIZE];
uint8_t table[64];
uint8_t tune[I2C_BUFSIZE];
uint8_t way[I2C_BUFSIZE];

char scale[] = "mm";
static char ga1[] = "ma";
static char ga2[] = "mm";
static char ga3[] = "mh";
static char ga4[] = "bl";
static char a[] = "A";
static char b[] = "B";
static char c[] = "C";
static char d[] = "D";
static char e[] = "E";
static char f[] = "F";
static char g[] = "G";
char tonic[] = "A";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
void SystemClock_Config(void);
void Display(float, int, int, int);
void LED_Matrix_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int __io_putchar(int ch) {
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);

  return ch;
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


  /* USER CODE BEGIN Init */
	  HAL_Init();
  /* USER CODE END Init */

  /* Configure the system clock */


  /* USER CODE BEGIN SysInit */
	  SystemClock_Config();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  /* USER CODE BEGIN 2 */
	  MX_GPIO_Init();
	  MX_USART2_UART_Init();
	  MX_I2C1_Init();
	  table[1]=1;
	  table[2]=2;
	  table[3]=4;
	  table[4]=3;
	  table[5]=8;
	  table[6]=5;
	  table[7]=7;
	  table[8]=6;
	  printf("\r\n Bonjour !!\r\n");


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  for (int j = 1; j < 9; j++) {
		  //printf("\r\n=== %d ===\r\n",j);
		if (table[j]<8) {
			table[j] = table[j]+1;
		}
		else{
			table[j]=1;
		}
	  }
	  //Display(0,0,0,0);
  }
}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

void LED_Matrix_Init()
{
	printf("\r\n=== LED MATRIX ===\r\n");
	printf("SCL sur D5 et SDA sur D4\r\n");

	I2CMasterBuffer[0] = 0x21;		// Turn on internal oscillator
	HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 1, HAL_MAX_DELAY);
	HAL_Delay(1);

	I2CMasterBuffer[0] = 0x81;		// Display on, blinking off
	HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 1, HAL_MAX_DELAY);
	HAL_Delay(1);
	I2CMasterBuffer[0] = 0xEA;		// Dimming duty a donf!
	HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 1, HAL_MAX_DELAY);
	HAL_Delay(1);
	for (int i = 0 ; i < 17 ; i++) {
		I2CMasterBuffer[i] = 0;
	}
	for (int i = 0 ; i < 17 ; i++) {
		blackBoard[i] = 0;
	}
}
  /* USER CODE END 3 */


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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
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
  hi2c1.Init.Timing = 0x00707CBB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : WHEELB_Pin */
  GPIO_InitStruct.Pin = WHEELB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(WHEELB_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : WHEELA_Pin */
  GPIO_InitStruct.Pin = WHEELA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(WHEELA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD3_Pin */
  GPIO_InitStruct.Pin = LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD3_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

}

/* USER CODE BEGIN 4 */
void Display(float dir, int seq, int flat, int sharp)
{
	int charging = 0;
	//All 12 sequences complete
	for (int i = 1 ; i < 17 ; i++) {
					way[i] = 0;
			}
	while (seq == 12){
				way[5]=(1<<3)+(1<<4);
				way[7]=(1<<2)+(1<<3);
				way[9]=(1<<3)+(1<<4);
				way[11]=(1<<4)+(1<<5);
				way[13]=(1<<5)+(1<<6);
				HAL_I2C_Master_Transmit(&hi2c1, HT16K33_I2C_ADDRESS, way, 17, HAL_MAX_DELAY);
	}

	//Choix tonique
	while(seq == 0){

		for (int i = 1 ; i < 17 ; i++) {
				tune[i] = 0;
		}
		if (strcmp(tonic,a)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4);
			tune[4]=(1<<2)+(1<<5);
			tune[6]=(1<<2)+(1<<5);
			tune[8]=(1<<1)+(1<<2)+(1<<3)+(1<<4);
			//printf("\r\n===%d===\r\n",tune[2]);
		}
		else if (strcmp(tonic,b)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[4]=(1<<1)+(1<<3)+(1<<5);
			tune[6]=(1<<1)+(1<<3)+(1<<4)+(1<<5);
			tune[8]=(1<<1)+(1<<2)+(1<<3);
		}
		else if (strcmp(tonic,c)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[4]=(1<<1)+(1<<5);
			tune[6]=(1<<1)+(1<<5);
			tune[8]=(1<<1)+(1<<5);
		}
		else if (strcmp(tonic,d)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[4]=(1<<1)+(1<<5);
			tune[6]=(1<<1)+(1<<5);
			tune[8]=(1<<2)+(1<<3)+(1<<4);
		}
		else if (strcmp(tonic,e)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[4]=(1<<1)+(1<<3)+(1<<5);
			tune[6]=(1<<1)+(1<<3)+(1<<5);
			tune[8]=(1<<1)+(1<<5);
		}
		else if (strcmp(tonic,f)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[4]=(1<<3)+(1<<5);
			tune[6]=(1<<3)+(1<<5);
			tune[8]=(1<<5);
		}
		else if (strcmp(tonic,g)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[4]=(1<<1)+(1<<5);
			tune[6]=(1<<1)+(1<<3)+(1<<5);
			tune[8]=(1<<1)+(1<<2)+(1<<3)+(1<<5);
		}
		else{
			tune[2]=0;
			tune[4]=0;
			tune[6]=0;
			tune[8]=0;
		}

		if (sharp){
			tune[12]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[14]=(1<<2)+(1<<4);
			tune[16]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			//printf("\r\n===%d===\r\n",tune[14]);
		}
		else if (flat){
			tune[12]=(1<<1)+(1<<2)+(1<<3)+(1<<4);
			tune[14]=(1<<1)+(1<<2);
			tune[16]=0;
		}
		else{
			tune[12]=0;
			tune[14]=0;
			tune[16]=0;
		}
		HAL_I2C_Master_Transmit(&hi2c1, HT16K33_I2C_ADDRESS, tune, 17, HAL_MAX_DELAY);
		//printf("\r\n===printed===\r\n");
		//printf("\r\n===%d===\r\n",tune[14]);

	}

	//Directions
	for (int i = 1 ; i < 17 ; i++) {
		way[i] = 0;
	}

	while (dir>0){
		//fleche verte
		way[7]=(1<<6)+(1<<2);
		way[9]=(1<<5)+(1<<3);
		way[11]=(1<<4);
		//fleche rouge
		way[6]=(1<<6)+(1<<2);
		way[8]=(1<<5)+(1<<3);
		way[10]=(1<<4);
		HAL_I2C_Master_Transmit(&hi2c1, HT16K33_I2C_ADDRESS, way, 17, HAL_MAX_DELAY);
	}
	while (dir<0){
		//fleche verte
		way[9]=(1<<6)+(1<<2);
		way[7]=(1<<5)+(1<<3);
		way[5]=(1<<4);
		//fleche rouge
		way[12]=(1<<6)+(1<<2);
		way[10]=(1<<5)+(1<<3);
		way[8]=(1<<4);
		HAL_I2C_Master_Transmit(&hi2c1, HT16K33_I2C_ADDRESS, way, 17, HAL_MAX_DELAY);
	}


	for (int i = 1 ; i < 17 ; i++) {
		way[i] = 0;
	}

	//Chargement

	int k = 0;
	while (charging) {
		for (int j = 1; j < 17; j++) {
			I2CMasterBuffer[j] = k << (j / 2);
			I2CMasterBuffer[j + 3] = k << ((j + 1) / 2);
			//printf("\r\n===charge===\r\n");
		}
		HAL_I2C_Master_Transmit(&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 17, HAL_MAX_DELAY);
		if (k == 0x80) {
			k = 1;
		}
		else {
			k <<= 1;
			HAL_Delay(100);
		}
	}
	printf("\r\n===no charging anymore===\r\n");
	//gamme
	while (dir == 0){
		if (strcmp(scale,ga1)==0){ //majeur
			for (int j = 1; j < 17; j+=2)
			{
				if ((table[j/2+1]==3)|(table[j/2+1]==7)){
					I2CMasterBuffer[j] = 1<<(table[j/2+1]-1);
				}
				else{
					I2CMasterBuffer[j+1] = 1<<(table[j/2+1]-1);
				}
			}
			HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 17, HAL_MAX_DELAY);
			//printf("\r\n===Fck===\r\n");
		}
		else if (strcmp(scale,ga2)==0){ //mineur mélodique
			for (int j = 1; j < 17; j+=2) {
				if ((table[j/2+1]==2)|(table[j/2+1]==7)){
					I2CMasterBuffer[j] = 1<<(table[j/2+1]-1);
				}
				else{
					I2CMasterBuffer[j+1] = 1<<(table[j/2+1]-1);
				}
			}
			HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 17, HAL_MAX_DELAY);
		}
		else if (strcmp(scale,ga3)==0){ //mineur harmonique
			for (int j = 1; j < 17; j+=2) {
				if ((table[j/2+1]==2)|(table[j/2+1]==5)|(table[j/2+1]==7)){
					I2CMasterBuffer[j] = 1<<(table[j/2+1]-1);
				}
				else if(table[j/2+1]==6){
					I2CMasterBuffer[j] = 1<<(table[j/2+1]-1);
					I2CMasterBuffer[j+1] = 1<<(table[j/2+1]-1);
				}
				else{
					I2CMasterBuffer[j+1] = 1<<(table[j/2+1]-1);
				}
			}
			HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 17, HAL_MAX_DELAY);
		}
		else if (strcmp(scale,ga4)==0){ //blues
			for (int j = 1; j < 17; j+=2) {
				if ((table[j/2+1]==2)|(table[j/2+1]==6)|(table[j/2+1]==8)){
					I2CMasterBuffer[j] = 1<<(table[j/2+1]-1);
				}
				else if((table[j/2+1]==1)|(table[j/2+1]==5)|(table[j/2+1]==7)){
					I2CMasterBuffer[j] = 1<<(table[j/2+1]-1);
					I2CMasterBuffer[j+1] = 1<<(table[j/2+1]-1);
				}
				else{
					I2CMasterBuffer[j+1] = 1<<(table[j/2+1]-1);
				}
			}
			HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 17, HAL_MAX_DELAY);
		}
		//else {
			//HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, blackBoard, 17, HAL_MAX_DELAY);
		//}
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
	printf("\r\n===error===\r\n");
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
