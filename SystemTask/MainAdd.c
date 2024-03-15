/********************************************************************************
*Project Code		：项目名称或代号						*
*Create Date		：创建日期							*2022年7月19日
*Created By			：创建人								*
*Function			：模块功能							*
*Modify Date		：修改日期							*
*Document			：参考文档							*
*Others				：特别说明部分						*
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "MainAdd.h"

#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "math.h"
#include "LED.h"
#include "Trigger.h"
#include "TimTask.h"
#include "UsartTask.h"
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
extern u1_msg_t u1_msg;
extern led_set_t led_set;
extern tim_ctl_t tim_ctl;
/* USER CODE END PV */

/********************************************************************************
*Function Name	：函数名称						*初始化资源添加
*Create Date	：创建日期						*2023年3月28日
*Created By		：创建人							*
*Function		：函数功能						*
*Modify Date	：修改日期						*
********************************************************************************/
void Main_Init_Add(void)
{
	/* 串口中断接收 */
	HAL_UART_Receive_IT(&huart1,&u1_msg.recv_byte,U1_RX_LENGTH);
	
	/* 初始化打印 */
	printf("\r\n===================================\r\nSSVEP&ERP LED Device Ready!\r\n");
	printf("Please configure the device first......\r\n===================================\r\n");
}

/********************************************************************************
*Function Name	：函数名称						*主循环资源添加
*Create Date	：创建日期						*2022年7月19日
*Created By		：创建人							*
*Function		：函数功能						*
*Modify Date	：修改日期						*
********************************************************************************/
void Main_Loop_Add(void)
{
	/* 串口接收 */
	if(u1_msg.rx_flag)
	{
		u1_msg.rx_flag = 0;
		U1_COMMAND_Handle();
		
		/* VEP模式 */
		if(u1_msg.mode == 0) {
			for(uint8_t i=0;i<6;i++) {
				led_set.ch_enable[i] = u1_msg.enable[i];
				if(u1_msg.data_freq[6] != 0) {
					led_set.ch_freq[i] = u1_msg.data_freq[6];
					u1_msg.data_freq[i] = u1_msg.data_freq[6];
				}
				else led_set.ch_freq[i] = u1_msg.data_freq[i];
				/* 修改频率 */
				LED_Freq_Control(i+1,led_set.ch_freq[i]);
				/* 通道指示灯开启或关闭 */
				Channel_LED_Control(i+1);
			}
		}
		else if(u1_msg.mode == 1) {
			//使能通道
			led_set.ch_enable[u1_msg.ERP_CH-1] = u1_msg.enable[u1_msg.ERP_CH-1];
			/* 修改频率 */
			led_set.ch_freq[u1_msg.ERP_CH-1] = u1_msg.data_freq[u1_msg.ERP_CH-1];
			LED_Freq_Control(u1_msg.ERP_CH,led_set.ch_freq[u1_msg.ERP_CH-1]);
			/* 通道指示灯开启或关闭 */
			Channel_LED_Control(u1_msg.ERP_CH);
			//熄灭其他通道指示灯
			for(uint8_t j=1;j <= 6;j++) {
				if(j != u1_msg.ERP_CH) {
					led_set.ch_enable[j-1] = 0;
					Channel_LED_Control(j);
					LED_Freq_Control(j,0);
				}
			}
		}
		/* 及时清零 */
		u1_msg.data_freq[6] = 0;
		/*开启/关闭定时器中断，控制闪烁频率*/
		if(led_set.ch_enable[6-1] == 1) HAL_TIM_Base_Start_IT(&htim3);
		else if(led_set.ch_enable[6-1] == 0) HAL_TIM_Base_Stop_IT(&htim3);
		if(led_set.ch_enable[4-1] == 1) HAL_TIM_Base_Start_IT(&htim4);
		else if(led_set.ch_enable[4-1] == 0) HAL_TIM_Base_Stop_IT(&htim4);
		if(led_set.ch_enable[2-1] == 1) HAL_TIM_Base_Start_IT(&htim5);
		else if(led_set.ch_enable[2-1] == 0) HAL_TIM_Base_Stop_IT(&htim5);
		if(led_set.ch_enable[1-1] == 1) HAL_TIM_Base_Start_IT(&htim9);
		else if(led_set.ch_enable[1-1] == 0) HAL_TIM_Base_Stop_IT(&htim9);
		if(led_set.ch_enable[3-1] == 1) HAL_TIM_Base_Start_IT(&htim10);
		else if(led_set.ch_enable[3-1] == 0) HAL_TIM_Base_Stop_IT(&htim10);
		if(led_set.ch_enable[5-1] == 1) HAL_TIM_Base_Start_IT(&htim11);
		else if(led_set.ch_enable[5-1] == 0) HAL_TIM_Base_Stop_IT(&htim11);
		
	}
	/* 灯显示控制 */
	for(uint8_t i=0;i<6;i++) LED_Show_Control(i+1);
	/* Trigger放置在 */
	if(u1_msg.mode) {
		if(1 == tim_ctl.Open_Flag[u1_msg.ERP_CH-1]) Trigger_ON;
		else Trigger_OFF;
	}
}



