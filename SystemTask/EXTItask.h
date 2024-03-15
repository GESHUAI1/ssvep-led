/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EXTITASK_H
#define __EXTITASK_H
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
typedef struct
{
	uint8_t CH[6];
	uint8_t old_state;
	uint8_t det[6];
}conn_flag_t;

#define	CH1_Value  					HAL_GPIO_ReadPin(CH1_Conn_GPIO_Port,CH1_Conn_Pin)

/* USER CODE END Private defines */
void LED_Connect_Detect(void);

#endif

