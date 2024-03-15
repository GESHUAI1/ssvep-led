/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USARTTASK_H
#define __USARTTASK_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct
{
	char CharData[255];			//字符数组
	char cmd_arrary[10];		//缓存指令，用于比较
	int8_t data_arrary[7][10];	//缓存数据，用于后续使用
	uint8_t rx_flag;			//接收标志位
	uint8_t recv_byte;			//（中断）单次接收字节
	uint8_t recv_buf[255];		//接收数据缓存区
	uint16_t rx_length;			//接收字节数
	float data_freq[7];
	uint8_t mode;
	uint8_t enable[6];
	uint8_t ERP_CH;
	uint8_t ERP_cnt;
}u1_msg_t;
/* USER CODE END ET */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define U1_RX_LENGTH			1

/*……………………………………………………………… 反馈消息 ………………………………………………………………*/
#define LED_RSP_OK					("\r\nOK\r\n")
#define LED_RSP_Error				("\r\nERROR\r\n")

/*……………………………………………………………… 接收指令 ………………………………………………………………*/
#define CMD_AT_TEST					("AT\r\n")			//AT测试指令
#define CMD_AT_MODE					("AT+MODE=")		//模式选择 -- 0：默认，SSVEP；1：ERP
#define CMD_AT_CH					("AT+CH=")			//通道开启关闭 -- 0：关闭；1：开启
#define CMD_AT_FREQ					("AT+FREQ=")		//通道频率 -- 0~50HZ，分辨率0.1HZ
#define CMD_AT_LEVEL				("AT+LEVEL=")		//亮度设置 -- 0~100级

/* USER CODE END Private defines */
void U1_COMMAND_Handle(void);

#endif

