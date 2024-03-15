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
#include "EXTItask.h"

#include "gpio.h"
#include "stdio.h"
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */
conn_flag_t conn_flag;
/********************************************************************************
*Function Name	：函数名称						*外部中断回调函数
*Create Date	：创建日期						*2023年4月12日
*Created By		：创建人							*
*Function		：函数功能						*
*Modify Date	：修改日期						*
********************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/*功能按钮——PA11*/
	if(GPIO_Pin==CH1_Conn_Pin) {
		conn_flag.det[0] = 0;
		/* 检测到低电平，连接上 */
		if(CH1_Value == GPIO_PIN_RESET)	{
			conn_flag.CH[0] = 1;
		}
		else if(CH1_Value == GPIO_PIN_SET)	{
			conn_flag.CH[0] = 0;
		}
		/* 及时清空外部中断 */
		__HAL_GPIO_EXTI_CLEAR_IT(CH1_Conn_Pin);
	}
}

/********************************************************************************
*Function Name	：函数名称						*连接检测
*Create Date	：创建日期						*2023年3月28日
*Created By		：创建人							*
*Function		：函数功能						*
*Modify Date	：修改日期						*
********************************************************************************/
void LED_Connect_Detect(void)
{
	if(conn_flag.det[0] == 0)
	{
		conn_flag.det[0] = 1;
		/* 检测到低电平，连接上 */
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




