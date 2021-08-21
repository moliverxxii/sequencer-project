/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "seq_def.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */



/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
const static uint8_t notes_led[] =
{
		0x01,
		0x02,
		0x04,
		0x08,
		0x10,
		0x20,
		0x40,
		0x80
};

const static uint8_t gammes[5][8] =
{
		{0,2,4,5,7,9,11,12},
		{0,2,3,5,7,8,10,12},
		{0,2,3,5,7,8,10,12},
		{0,3,5,6,7,10,12,15},
		{0,2,4,6,8,10,12,14}
};

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void seq_gen(seq_TypeDef* sequence);
void seq_play_step(seq_TypeDef* sequence);
//void SEQ_DispStep(seq_TypeDef* sequence);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define WHEEL_A_Pin GPIO_PIN_14
#define WHEEL_A_GPIO_Port GPIOC
#define WHEEL_A_EXTI_IRQn EXTI15_10_IRQn
#define CLOCK_Pin GPIO_PIN_15
#define CLOCK_GPIO_Port GPIOC
#define CLOCK_EXTI_IRQn EXTI15_10_IRQn
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOA
#define CV_MODE_Pin GPIO_PIN_1
#define CV_MODE_GPIO_Port GPIOA
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_TX_GPIO_Port GPIOA
#define CV_TONIC_2_Pin GPIO_PIN_3
#define CV_TONIC_2_GPIO_Port GPIOA
#define CV_OUT_Pin GPIO_PIN_4
#define CV_OUT_GPIO_Port GPIOA
#define NO_Pin GPIO_PIN_5
#define NO_GPIO_Port GPIOA
#define NOA6_Pin GPIO_PIN_6
#define NOA6_GPIO_Port GPIOA
#define CV_TONIC_1_Pin GPIO_PIN_7
#define CV_TONIC_1_GPIO_Port GPIOA
#define NOB0_Pin GPIO_PIN_0
#define NOB0_GPIO_Port GPIOB
#define WHEEL_B_Pin GPIO_PIN_1
#define WHEEL_B_GPIO_Port GPIOB
#define WHEEL_B_EXTI_IRQn EXTI1_IRQn
#define LAST_STEP_Pin GPIO_PIN_8
#define LAST_STEP_GPIO_Port GPIOA
#define TRIG_OUT_Pin GPIO_PIN_11
#define TRIG_OUT_GPIO_Port GPIOA
#define WHEEL_BTN_Pin GPIO_PIN_12
#define WHEEL_BTN_GPIO_Port GPIOA
#define WHEEL_BTN_EXTI_IRQn EXTI15_10_IRQn
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define VCP_RX_Pin GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA
#define NO_BTN_LD3_Pin GPIO_PIN_3
#define NO_BTN_LD3_GPIO_Port GPIOB
#define PREV_SEQ_Pin GPIO_PIN_4
#define PREV_SEQ_GPIO_Port GPIOB
#define NEXT_SEQ_Pin GPIO_PIN_5
#define NEXT_SEQ_GPIO_Port GPIOB
#define NEXT_SEQ_EXTI_IRQn EXTI9_5_IRQn
#define LED_MAT_CL_Pin GPIO_PIN_6
#define LED_MAT_CL_GPIO_Port GPIOB
#define LED_MAT_DA_Pin GPIO_PIN_7
#define LED_MAT_DA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
