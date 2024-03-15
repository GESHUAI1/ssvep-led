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
	char CharData[255];			//�ַ�����
	char cmd_arrary[10];		//����ָ����ڱȽ�
	int8_t data_arrary[7][10];	//�������ݣ����ں���ʹ��
	uint8_t rx_flag;			//���ձ�־λ
	uint8_t recv_byte;			//���жϣ����ν����ֽ�
	uint8_t recv_buf[255];		//�������ݻ�����
	uint16_t rx_length;			//�����ֽ���
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

/*������������������������������������������������ ������Ϣ ������������������������������������������������*/
#define LED_RSP_OK					("\r\nOK\r\n")
#define LED_RSP_Error				("\r\nERROR\r\n")

/*������������������������������������������������ ����ָ�� ������������������������������������������������*/
#define CMD_AT_TEST					("AT\r\n")			//AT����ָ��
#define CMD_AT_MODE					("AT+MODE=")		//ģʽѡ�� -- 0��Ĭ�ϣ�SSVEP��1��ERP
#define CMD_AT_CH					("AT+CH=")			//ͨ�������ر� -- 0���رգ�1������
#define CMD_AT_FREQ					("AT+FREQ=")		//ͨ��Ƶ�� -- 0~50HZ���ֱ���0.1HZ
#define CMD_AT_LEVEL				("AT+LEVEL=")		//�������� -- 0~100��

/* USER CODE END Private defines */
void U1_COMMAND_Handle(void);

#endif

