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
#include "TimTask.h"
#include "tim.h"

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */
tim_ctl_t tim_ctl;
/********************************************************************************
*Function Name	����������						*��ʱ���ص�����
*Create Date	����������						*2022��7��19��
*Created By		��������							*
*Function		����������						*
*Modify Date	���޸�����						*
********************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/*������������������������������������ ����ʱ�� TIMx��������˸Ƶ�ʿ��ƣ�Ĭ��0.1HZ��ע�⣺��������x2�� ������������������������������������*/
	if(htim->Instance==htim3.Instance)
	{
		/* ��ת��־λ�����ƵƵ���˸ */
		if(tim_ctl.Open_Flag[6-1] != 0) tim_ctl.Open_Flag[6-1] = 0;
		else tim_ctl.Open_Flag[6-1] = 1;
	}
	if(htim->Instance==htim4.Instance)
	{
		/* ��ת��־λ�����ƵƵ���˸ */
		if(tim_ctl.Open_Flag[4-1] != 0) tim_ctl.Open_Flag[4-1] = 0;
		else tim_ctl.Open_Flag[4-1] = 1;
	}
	if(htim->Instance==htim5.Instance)
	{
		/* ��ת��־λ�����ƵƵ���˸ */
		if(tim_ctl.Open_Flag[2-1] != 0) tim_ctl.Open_Flag[2-1] = 0;
		else tim_ctl.Open_Flag[2-1] = 1;
	}
	if(htim->Instance==htim9.Instance)
	{
		/* ��ת��־λ�����ƵƵ���˸ */
		if(tim_ctl.Open_Flag[1-1] != 0) tim_ctl.Open_Flag[1-1] = 0;
		else tim_ctl.Open_Flag[1-1] = 1;
	}
	if(htim->Instance==htim10.Instance)
	{
		/* ��ת��־λ�����ƵƵ���˸ */
		if(tim_ctl.Open_Flag[3-1] != 0) tim_ctl.Open_Flag[3-1] = 0;
		else tim_ctl.Open_Flag[3-1] = 1;
	}
	if(htim->Instance==htim11.Instance)
	{
		/* ��ת��־λ�����ƵƵ���˸ */
		if(tim_ctl.Open_Flag[5-1] != 0) tim_ctl.Open_Flag[5-1] = 0;
		else tim_ctl.Open_Flag[5-1] = 1;
	}
	
}

