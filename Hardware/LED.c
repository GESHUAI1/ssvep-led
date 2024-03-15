/********************************************************************************
*Project Code		����Ŀ���ƻ����						*
*Create Date		����������							*
*Created By			��������								*
*Function			��ģ�鹦��							*
*Modify Date		���޸�����							*
*Document			���ο��ĵ�							*
*Others				���ر�˵������						*
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LED.h"
#include "tim.h"
#include "gpio.h"
#include "math.h"
#include "stdio.h"
#include "TimTask.h"
#include "Trigger.h"
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
led_set_t led_set;

/* USER CODE END PV */
/********************************************************************************
*Function Name	����������						*����˸Ƶ�ʿ���
*Create Date	����������						*2023��3��28��
*Created By		��������							*
*Function		����������						*iCH��ͨ����iFre���趨Ƶ��
*Modify Date	���޸�����						*
********************************************************************************/
void LED_Freq_Control(uint8_t iCH,float iFre)
{
	float iTemp[6]={0.0};
	uint16_t iPeriod[6]={0};
	uint16_t NEW_Prescaler[6]={0};
	/* ��һ������ʱ��Ƶ���趨 */
	iTemp[iCH-1] = iFre*2;
	/* �ڶ�������������  = Ƶ�� / Ԥ��Ƶϵ�� / ��ʱ��Ƶ�� */
	if(iTemp[iCH-1] <= 1) {
		/* �����Ƶ��2����ת��0.5HZ����������Լ�����һ�� */
		switch(iCH)
		{
			case 6:
				__HAL_TIM_SET_PRESCALER(&htim3,TIM_Default_Prescaler-1);
				break;
			case 4:
				__HAL_TIM_SET_PRESCALER(&htim4,TIM_Default_Prescaler-1);
				break;
			case 2:
				__HAL_TIM_SET_PRESCALER(&htim5,TIM_Default_Prescaler-1);
				break;
			case 1:
				__HAL_TIM_SET_PRESCALER(&htim9,TIM_Default_Prescaler-1);
				break;
			case 3:
				__HAL_TIM_SET_PRESCALER(&htim10,TIM_Default_Prescaler-1);
				break;
			case 5:
				__HAL_TIM_SET_PRESCALER(&htim11,TIM_Default_Prescaler-1);
				break;
			default:
				break;
		}
		
		/* ����������ֵ */
		iPeriod[iCH-1] = (uint16_t)(TIM_CLOCK/TIM_Default_Prescaler/iTemp[iCH-1]);
	}
	else {
		/* ���޸�Ԥ��Ƶϵ������СƵ����� */
		if(iTemp[iCH-1] <= 10) NEW_Prescaler[iCH-1] = (round)(TIM_Default_Prescaler/10);
		else if((iTemp[iCH-1] > 10)&&(iTemp[iCH-1] <= 50))  NEW_Prescaler[iCH-1] = (round)(TIM_Default_Prescaler/50);
		else if((iTemp[iCH-1] > 50)&&(iTemp[iCH-1] <= 100))  NEW_Prescaler[iCH-1] = (round)(TIM_Default_Prescaler/100);
		else if((iTemp[iCH-1] > 100)&&(iTemp[iCH-1] <= 200))  NEW_Prescaler[iCH-1] = (round)(TIM_Default_Prescaler/300);
		
		/* ����������ֵ */
		iPeriod[iCH-1] = (uint16_t)(TIM_CLOCK/NEW_Prescaler[iCH-1]/iTemp[iCH-1]);
		/* ���趨Ԥ��Ƶ */
		switch(iCH)
		{
			case 6:
				__HAL_TIM_SET_PRESCALER(&htim3,NEW_Prescaler[iCH-1]-1);
				break;
			case 4:
				__HAL_TIM_SET_PRESCALER(&htim4,NEW_Prescaler[iCH-1]-1);
				break;
			case 2:
				__HAL_TIM_SET_PRESCALER(&htim5,NEW_Prescaler[iCH-1]-1);
				break;
			case 1:
				__HAL_TIM_SET_PRESCALER(&htim9,NEW_Prescaler[iCH-1]-1);
				break;
			case 3:
				__HAL_TIM_SET_PRESCALER(&htim10,NEW_Prescaler[iCH-1]-1);
				break;
			case 5:
				__HAL_TIM_SET_PRESCALER(&htim11,NEW_Prescaler[iCH-1]-1);
				break;
			default:
				break;
		}
		
	}
	
	/* ���������޸Ķ�ʱ������ */
	switch(iCH)
	{
		/*ͨ��1*/
		case 6:
			{
				__HAL_TIM_SET_AUTORELOAD(&htim3,iPeriod[iCH-1]-1);		//���趨����
				htim3.Instance->EGR=TIM_EGR_UG; 						//����ʹ������Ч
			}
			break;
		/*ͨ��2*/
		case 4:
			{
				__HAL_TIM_SET_AUTORELOAD(&htim4,iPeriod[iCH-1]-1);		//���趨����
				htim4.Instance->EGR=TIM_EGR_UG; 						//����ʹ������Ч
			}
			break;
		/*ͨ��3*/
		case 2:
			{
				__HAL_TIM_SET_AUTORELOAD(&htim5,iPeriod[iCH-1]-1);		//���趨����
				htim5.Instance->EGR=TIM_EGR_UG; 						//����ʹ������Ч
			}
			break;
		/*ͨ��4*/
		case 1:
			{
				__HAL_TIM_SET_AUTORELOAD(&htim9,iPeriod[iCH-1]-1);		//���趨����
				htim9.Instance->EGR=TIM_EGR_UG; 						//����ʹ������Ч
			}
			break;
		/*ͨ��5*/
		case 3:
			{
				__HAL_TIM_SET_AUTORELOAD(&htim10,iPeriod[iCH-1]-1);		//���趨����
				htim10.Instance->EGR=TIM_EGR_UG; 						//����ʹ������Ч
			}
			break;
		/*ͨ��6*/
		case 5:
			{
				__HAL_TIM_SET_AUTORELOAD(&htim11,iPeriod[iCH-1]-1);		//���趨����
				htim11.Instance->EGR=TIM_EGR_UG; 						//����ʹ������Ч
			}
			break;
		
		default:
			break;
	}
	
}

/********************************************************************************
*Function Name	����������						*����ʾ������ر�
*Create Date	����������						*2023��3��28��
*Created By		��������							*
*Function		����������						*iCH��ѡ��ͨ����iEnable��ʹ��
*Modify Date	���޸�����						*
********************************************************************************/
void LED_Channel_Control(uint8_t iCH,uint8_t iEnable)
{
	switch(iCH)
	{
		/*ͨ��1��������ر�*/
		case 1:
			{
				if(1 == iEnable) CH4_ON;
				else CH4_OFF;
			}
			break;
		/*ͨ��2��������ر�*/
		case 2:
			{
				if(1 == iEnable) CH3_ON;
				else CH3_OFF;
			}
			break;
		/*ͨ��3��������ر�*/
		case 3:
			{
				if(1 == iEnable)  CH5_ON;
				else CH5_OFF;
			}
			break;
		/*ͨ��4��������ر�*/
		case 4:
			{
				if(1 == iEnable) CH2_ON;
				else CH2_OFF;
			}
			break;
		/*ͨ��5��������ر�*/
		case 5:
			{
				if(1 == iEnable) CH6_ON;
				else CH6_OFF;
			}
			break;
		/*ͨ��6��������ر�*/
		case 6:
			{
				if(1 == iEnable) CH1_ON;
				else CH1_OFF;
			}
			break;
		
		default:
			break;
	}
}


/********************************************************************************
*Function Name	����������						*ͨ��ָʾ��
*Create Date	����������						*2023��3��28��
*Created By		��������							*
*Function		����������						*
*Modify Date	���޸�����						*
********************************************************************************/
void Channel_LED_Control(uint8_t iCH)
{
	switch(iCH)
	{
		case 1:
		{
			if(led_set.ch_enable[0] == 1) CH4_Enable;
			else CH4_Disable;
		}
			break;
		case 2:
		{
			if(led_set.ch_enable[1] == 1) CH3_Enable;
			else CH3_Disable;
		}
			break;
		case 3:
		{
			if(led_set.ch_enable[2] == 1) CH5_Enable;
			else CH5_Disable;
		}
			break;
		case 4:
		{
			if(led_set.ch_enable[3] == 1) CH2_Enable;
			else CH2_Disable;
		}
			break;
		case 5:
		{
			if(led_set.ch_enable[4] == 1) CH6_Enable;
			else CH6_Disable;
		}
			break;
		case 6:
		{
			if(led_set.ch_enable[5] == 1) CH1_Enable;
			else CH1_Disable;
		}
			break;
		default:
			break;
	}
}


/********************************************************************************
*Function Name	����������						*����ʾ
*Create Date	����������						*2023��3��28��
*Created By		��������							*
*Function		����������						*
*Modify Date	���޸�����						*
********************************************************************************/
extern tim_ctl_t tim_ctl;
void LED_Show_Control(uint8_t iCH)
{
	/* ͨ��x���� */
	if((led_set.ch_enable[iCH-1] == 1)&&(led_set.ch_freq[iCH-1] != 0)) {
		/* ����˸ */
		if(1 == tim_ctl.Open_Flag[iCH-1]) LED_Channel_Control(iCH,1);
		else LED_Channel_Control(iCH,0);
	}
	/* ͨ��x�ر� */
	else if(led_set.ch_enable[iCH-1] == 0) {
		LED_Channel_Control(iCH,0);
	}
	
}
