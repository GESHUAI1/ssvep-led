/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TRIGGER_H
#define __TRIGGER_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define Trigger_ON		HAL_GPIO_WritePin(Trigger_CTL_GPIO_Port, Trigger_CTL_Pin, GPIO_PIN_SET)
#define Trigger_OFF		HAL_GPIO_WritePin(Trigger_CTL_GPIO_Port, Trigger_CTL_Pin, GPIO_PIN_RESET)

/* USER CODE END Private defines */

#endif

