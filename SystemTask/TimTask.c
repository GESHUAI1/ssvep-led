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
#include "TimTask.h"
#include "tim.h"

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */
tim_ctl_t tim_ctl;
/********************************************************************************
*Function Name	：函数名称						*定时器回调函数
*Create Date	：创建日期						*2022年7月19日
*Created By		：创建人							*
*Function		：函数功能						*
*Modify Date	：修改日期						*
********************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/*……………………………………………… 主定时器 TIMx，任务：闪烁频率控制，默认0.1HZ（注意：亮灭，周期x2） ………………………………………………*/
	if(htim->Instance==htim3.Instance)
	{
		/* 翻转标志位，控制灯的闪烁 */
		if(tim_ctl.Open_Flag[6-1] != 0) tim_ctl.Open_Flag[6-1] = 0;
		else tim_ctl.Open_Flag[6-1] = 1;
	}
	if(htim->Instance==htim4.Instance)
	{
		/* 翻转标志位，控制灯的闪烁 */
		if(tim_ctl.Open_Flag[4-1] != 0) tim_ctl.Open_Flag[4-1] = 0;
		else tim_ctl.Open_Flag[4-1] = 1;
	}
	if(htim->Instance==htim5.Instance)
	{
		/* 翻转标志位，控制灯的闪烁 */
		if(tim_ctl.Open_Flag[2-1] != 0) tim_ctl.Open_Flag[2-1] = 0;
		else tim_ctl.Open_Flag[2-1] = 1;
	}
	if(htim->Instance==htim9.Instance)
	{
		/* 翻转标志位，控制灯的闪烁 */
		if(tim_ctl.Open_Flag[1-1] != 0) tim_ctl.Open_Flag[1-1] = 0;
		else tim_ctl.Open_Flag[1-1] = 1;
	}
	if(htim->Instance==htim10.Instance)
	{
		/* 翻转标志位，控制灯的闪烁 */
		if(tim_ctl.Open_Flag[3-1] != 0) tim_ctl.Open_Flag[3-1] = 0;
		else tim_ctl.Open_Flag[3-1] = 1;
	}
	if(htim->Instance==htim11.Instance)
	{
		/* 翻转标志位，控制灯的闪烁 */
		if(tim_ctl.Open_Flag[5-1] != 0) tim_ctl.Open_Flag[5-1] = 0;
		else tim_ctl.Open_Flag[5-1] = 1;
	}
	
}

