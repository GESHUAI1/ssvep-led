/********************************************************************************
*Project Code		：项目名称或代号						*
*Create Date		：创建日期							*
*Created By			：创建人								*
*Function			：模块功能							*
*Modify Date		：修改日期							*
*Document			：参考文档							*
*Others				：特别说明部分						*
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
*Function Name	：函数名称						*灯闪烁频率控制
*Create Date	：创建日期						*2023年3月28日
*Created By		：创建人							*
*Function		：函数功能						*iCH：通道，iFre：设定频率
*Modify Date	：修改日期						*
********************************************************************************/
void LED_Freq_Control(uint8_t iCH,float iFre)
{
	float iTemp[6]={0.0};
	uint16_t iPeriod[6]={0};
	uint16_t NEW_Prescaler[6]={0};
	/* 第一步：定时器频率设定 */
	iTemp[iCH-1] = iFre*2;
	/* 第二步：计算周期  = 频率 / 预分频系数 / 定时器频率 */
	if(iTemp[iCH-1] <= 1) {
		/* 如果从频率2，跳转到0.5HZ，会出错，所以加上这一句 */
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
		
		/* 计算周期数值 */
		iPeriod[iCH-1] = (uint16_t)(TIM_CLOCK/TIM_Default_Prescaler/iTemp[iCH-1]);
	}
	else {
		/* 先修改预分频系数，减小频率误差 */
		if(iTemp[iCH-1] <= 10) NEW_Prescaler[iCH-1] = (round)(TIM_Default_Prescaler/10);
		else if((iTemp[iCH-1] > 10)&&(iTemp[iCH-1] <= 50))  NEW_Prescaler[iCH-1] = (round)(TIM_Default_Prescaler/50);
		else if((iTemp[iCH-1] > 50)&&(iTemp[iCH-1] <= 100))  NEW_Prescaler[iCH-1] = (round)(TIM_Default_Prescaler/100);
		else if((iTemp[iCH-1] > 100)&&(iTemp[iCH-1] <= 200))  NEW_Prescaler[iCH-1] = (round)(TIM_Default_Prescaler/300);
		
		/* 计算周期数值 */
		iPeriod[iCH-1] = (uint16_t)(TIM_CLOCK/NEW_Prescaler[iCH-1]/iTemp[iCH-1]);
		/* 先设定预分频 */
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
	
	/* 第三步：修改定时器参数 */
	switch(iCH)
	{
		/*通道1*/
		case 6:
			{
				__HAL_TIM_SET_AUTORELOAD(&htim3,iPeriod[iCH-1]-1);		//后设定周期
				htim3.Instance->EGR=TIM_EGR_UG; 						//立即使配置生效
			}
			break;
		/*通道2*/
		case 4:
			{
				__HAL_TIM_SET_AUTORELOAD(&htim4,iPeriod[iCH-1]-1);		//后设定周期
				htim4.Instance->EGR=TIM_EGR_UG; 						//立即使配置生效
			}
			break;
		/*通道3*/
		case 2:
			{
				__HAL_TIM_SET_AUTORELOAD(&htim5,iPeriod[iCH-1]-1);		//后设定周期
				htim5.Instance->EGR=TIM_EGR_UG; 						//立即使配置生效
			}
			break;
		/*通道4*/
		case 1:
			{
				__HAL_TIM_SET_AUTORELOAD(&htim9,iPeriod[iCH-1]-1);		//后设定周期
				htim9.Instance->EGR=TIM_EGR_UG; 						//立即使配置生效
			}
			break;
		/*通道5*/
		case 3:
			{
				__HAL_TIM_SET_AUTORELOAD(&htim10,iPeriod[iCH-1]-1);		//后设定周期
				htim10.Instance->EGR=TIM_EGR_UG; 						//立即使配置生效
			}
			break;
		/*通道6*/
		case 5:
			{
				__HAL_TIM_SET_AUTORELOAD(&htim11,iPeriod[iCH-1]-1);		//后设定周期
				htim11.Instance->EGR=TIM_EGR_UG; 						//立即使配置生效
			}
			break;
		
		default:
			break;
	}
	
}

/********************************************************************************
*Function Name	：函数名称						*灯显示开启或关闭
*Create Date	：创建日期						*2023年3月28日
*Created By		：创建人							*
*Function		：函数功能						*iCH：选择通道，iEnable：使能
*Modify Date	：修改日期						*
********************************************************************************/
void LED_Channel_Control(uint8_t iCH,uint8_t iEnable)
{
	switch(iCH)
	{
		/*通道1：开启或关闭*/
		case 1:
			{
				if(1 == iEnable) CH4_ON;
				else CH4_OFF;
			}
			break;
		/*通道2：开启或关闭*/
		case 2:
			{
				if(1 == iEnable) CH3_ON;
				else CH3_OFF;
			}
			break;
		/*通道3：开启或关闭*/
		case 3:
			{
				if(1 == iEnable)  CH5_ON;
				else CH5_OFF;
			}
			break;
		/*通道4：开启或关闭*/
		case 4:
			{
				if(1 == iEnable) CH2_ON;
				else CH2_OFF;
			}
			break;
		/*通道5：开启或关闭*/
		case 5:
			{
				if(1 == iEnable) CH6_ON;
				else CH6_OFF;
			}
			break;
		/*通道6：开启或关闭*/
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
*Function Name	：函数名称						*通道指示灯
*Create Date	：创建日期						*2023年3月28日
*Created By		：创建人							*
*Function		：函数功能						*
*Modify Date	：修改日期						*
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
*Function Name	：函数名称						*灯显示
*Create Date	：创建日期						*2023年3月28日
*Created By		：创建人							*
*Function		：函数功能						*
*Modify Date	：修改日期						*
********************************************************************************/
extern tim_ctl_t tim_ctl;
void LED_Show_Control(uint8_t iCH)
{
	/* 通道x开启 */
	if((led_set.ch_enable[iCH-1] == 1)&&(led_set.ch_freq[iCH-1] != 0)) {
		/* 灯闪烁 */
		if(1 == tim_ctl.Open_Flag[iCH-1]) LED_Channel_Control(iCH,1);
		else LED_Channel_Control(iCH,0);
	}
	/* 通道x关闭 */
	else if(led_set.ch_enable[iCH-1] == 0) {
		LED_Channel_Control(iCH,0);
	}
	
}
