/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct
{
	uint8_t ch_enable[6];		//通道启用/关闭
	float ch_freq[6];			//通道频率设置
	uint8_t mode_set;			//模式选择，0：默认SSVEP，1：ERP模式，2表示错误
//	float old_freq[6];			//保存之前的频率数值
}led_set_t;
/* USER CODE END ET */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define TIM_Default_Prescaler	1220			//定时器预设分频
#define TIM_Default_Period		65535			//定时器预设周期
#define TIM_CLOCK				8000000			//定时器时钟频率8MHZ/4分频


#define CH1_ON			HAL_GPIO_WritePin(GPIOA, CH1_CTL_Pin, GPIO_PIN_SET)
#define CH2_ON			HAL_GPIO_WritePin(GPIOA, CH2_CTL_Pin, GPIO_PIN_SET)
#define CH3_ON			HAL_GPIO_WritePin(GPIOA, CH3_CTL_Pin, GPIO_PIN_SET)
#define CH4_ON			HAL_GPIO_WritePin(GPIOA, CH4_CTL_Pin, GPIO_PIN_SET)
#define CH5_ON			HAL_GPIO_WritePin(GPIOA, CH5_CTL_Pin, GPIO_PIN_SET)
#define CH6_ON			HAL_GPIO_WritePin(GPIOA, CH6_CTL_Pin, GPIO_PIN_SET)

#define CH1_OFF			HAL_GPIO_WritePin(GPIOA, CH1_CTL_Pin, GPIO_PIN_RESET)
#define CH2_OFF			HAL_GPIO_WritePin(GPIOA, CH2_CTL_Pin, GPIO_PIN_RESET)
#define CH3_OFF			HAL_GPIO_WritePin(GPIOA, CH3_CTL_Pin, GPIO_PIN_RESET)
#define CH4_OFF			HAL_GPIO_WritePin(GPIOA, CH4_CTL_Pin, GPIO_PIN_RESET)
#define CH5_OFF			HAL_GPIO_WritePin(GPIOA, CH5_CTL_Pin, GPIO_PIN_RESET)
#define CH6_OFF			HAL_GPIO_WritePin(GPIOA, CH6_CTL_Pin, GPIO_PIN_RESET)

#define CH1_Enable		HAL_GPIO_WritePin(CH1_EN_GPIO_Port, CH1_EN_Pin, GPIO_PIN_RESET)
#define CH2_Enable		HAL_GPIO_WritePin(CH2_EN_GPIO_Port, CH2_EN_Pin, GPIO_PIN_RESET)
#define CH3_Enable		HAL_GPIO_WritePin(CH3_EN_GPIO_Port, CH3_EN_Pin, GPIO_PIN_RESET)
#define CH4_Enable		HAL_GPIO_WritePin(CH4_EN_GPIO_Port, CH4_EN_Pin, GPIO_PIN_RESET)
#define CH5_Enable		HAL_GPIO_WritePin(CH5_EN_GPIO_Port, CH5_EN_Pin, GPIO_PIN_RESET)
#define CH6_Enable		HAL_GPIO_WritePin(CH6_EN_GPIO_Port, CH6_EN_Pin, GPIO_PIN_RESET)

#define CH1_Disable		HAL_GPIO_WritePin(CH1_EN_GPIO_Port, CH1_EN_Pin, GPIO_PIN_SET)
#define CH2_Disable		HAL_GPIO_WritePin(CH2_EN_GPIO_Port, CH2_EN_Pin, GPIO_PIN_SET)
#define CH3_Disable		HAL_GPIO_WritePin(CH3_EN_GPIO_Port, CH3_EN_Pin, GPIO_PIN_SET)
#define CH4_Disable		HAL_GPIO_WritePin(CH4_EN_GPIO_Port, CH4_EN_Pin, GPIO_PIN_SET)
#define CH5_Disable		HAL_GPIO_WritePin(CH5_EN_GPIO_Port, CH5_EN_Pin, GPIO_PIN_SET)
#define CH6_Disable		HAL_GPIO_WritePin(CH6_EN_GPIO_Port, CH6_EN_Pin, GPIO_PIN_SET)
/* USER CODE END Private defines */
void LED_Freq_Control(uint8_t iCH,float iFre);
void LED_Channel_Control(uint8_t iCH,uint8_t iEnable);
void LED_Show_Control(uint8_t iCH);
void Channel_LED_Control(uint8_t iCH);
#endif

