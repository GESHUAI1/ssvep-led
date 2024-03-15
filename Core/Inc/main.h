/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CH5_CTL_Pin GPIO_PIN_0
#define CH5_CTL_GPIO_Port GPIOA
#define CH4_CTL_Pin GPIO_PIN_1
#define CH4_CTL_GPIO_Port GPIOA
#define CH6_Conn_Pin GPIO_PIN_3
#define CH6_Conn_GPIO_Port GPIOA
#define CH6_EN_Pin GPIO_PIN_4
#define CH6_EN_GPIO_Port GPIOA
#define CH5_Conn_Pin GPIO_PIN_5
#define CH5_Conn_GPIO_Port GPIOA
#define CH5_EN_Pin GPIO_PIN_6
#define CH5_EN_GPIO_Port GPIOA
#define CH4_Conn_Pin GPIO_PIN_7
#define CH4_Conn_GPIO_Port GPIOA
#define CH4_EN_Pin GPIO_PIN_0
#define CH4_EN_GPIO_Port GPIOB
#define Trigger_CTL_Pin GPIO_PIN_2
#define Trigger_CTL_GPIO_Port GPIOB
#define CH1_CTL_Pin GPIO_PIN_8
#define CH1_CTL_GPIO_Port GPIOA
#define CH2_CTL_Pin GPIO_PIN_9
#define CH2_CTL_GPIO_Port GPIOA
#define CH3_CTL_Pin GPIO_PIN_10
#define CH3_CTL_GPIO_Port GPIOA
#define CH6_CTL_Pin GPIO_PIN_11
#define CH6_CTL_GPIO_Port GPIOA
#define CH1_Conn_Pin GPIO_PIN_4
#define CH1_Conn_GPIO_Port GPIOB
#define CH1_EN_Pin GPIO_PIN_5
#define CH1_EN_GPIO_Port GPIOB
#define CH2_Conn_Pin GPIO_PIN_6
#define CH2_Conn_GPIO_Port GPIOB
#define CH2_EN_Pin GPIO_PIN_7
#define CH2_EN_GPIO_Port GPIOB
#define CH3_Conn_Pin GPIO_PIN_8
#define CH3_Conn_GPIO_Port GPIOB
#define CH3_EN_Pin GPIO_PIN_9
#define CH3_EN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
