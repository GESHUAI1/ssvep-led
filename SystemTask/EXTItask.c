/********************************************************************************
*Project Code		����Ŀ���ƻ����						*
*Create Date		����������							*2022��7��19��
*Created By			��������								*
*Function			��ģ�鹦��							*
*Modify Date		���޸�����							*
*Document			���ο��ĵ�							*
*Others				���ر�˵������						*
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "EXTItask.h"

#include "gpio.h"
#include "stdio.h"
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */
conn_flag_t conn_flag;
/********************************************************************************
*Function Name	����������						*�ⲿ�жϻص�����
*Create Date	����������						*2023��4��12��
*Created By		��������							*
*Function		����������						*
*Modify Date	���޸�����						*
********************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/*���ܰ�ť����PA11*/
	if(GPIO_Pin==CH1_Conn_Pin) {
		conn_flag.det[0] = 0;
		/* ��⵽�͵�ƽ�������� */
		if(CH1_Value == GPIO_PIN_RESET)	{
			conn_flag.CH[0] = 1;
		}
		else if(CH1_Value == GPIO_PIN_SET)	{
			conn_flag.CH[0] = 0;
		}
		/* ��ʱ����ⲿ�ж� */
		__HAL_GPIO_EXTI_CLEAR_IT(CH1_Conn_Pin);
	}
}

/********************************************************************************
*Function Name	����������						*���Ӽ��
*Create Date	����������						*2023��3��28��
*Created By		��������							*
*Function		����������						*
*Modify Date	���޸�����						*
********************************************************************************/
void LED_Connect_Detect(void)
{
	if(conn_flag.det[0] == 0)
	{
		conn_flag.det[0] = 1;
		/* ��⵽�͵�ƽ�������� */
		if(CH1_Value == GPIO_PIN_RESET)	{
			conn_flag.CH[0] = 1;
			printf("CH1 Connected OK.\r\n");
		}
		else {
			conn_flag.CH[0] = 0;
			printf("CH1 Disconnected !!!\r\n");
		}
	}
	
}




