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
#include "UsartTask.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
u1_msg_t u1_msg;
/* USER CODE END PV */

/********************************************************************************
*Function Name	：函数名称						*十六进制数组转字符
*Create Date	：创建日期						*
*Created By		：创建人							*
*Function		：函数功能						*
*Modify Date	：修改日期						*
********************************************************************************/
void HexToChar(uint8_t* iData,uint16_t iLength)
{
	//清空数组
	memset(u1_msg.CharData,0,sizeof(u1_msg.CharData));
	//转换数据：十六进制 ——> 字符
	memcpy(u1_msg.CharData,iData,iLength);
}

/********************************************************************************
*Function Name	：函数名称						*串口中断接收处理
*Create Date	：创建日期						*
*Created By		：创建人							*
*Function		：函数功能						*
*Modify Date	：修改日期						*
********************************************************************************/
uint16_t icnt = 0;
void USART1_TI_RX(uint8_t InData,uint8_t* OutData)
{
	/* 一次接收一个字节 */
	u1_msg.recv_buf[icnt++] = InData;
	
	/* 对缓存的所有字节进行判断 -- 末尾是\r\n（回车换行）*/
	if((u1_msg.recv_buf[icnt-2] == 0x0D)&&(u1_msg.recv_buf[icnt-1] == 0x0A))
	{
		memcpy(OutData,u1_msg.recv_buf,icnt);
		u1_msg.rx_length = icnt;
		/* 及时清空 */
		icnt = 0;
		/* 数据类型转换 */
		HexToChar(u1_msg.recv_buf,u1_msg.rx_length);
		/* 情况缓存数组 */
		memset(u1_msg.recv_buf,0x00,sizeof(u1_msg.recv_buf));
		/* 接收完成标志 */
		u1_msg.rx_flag = 1;
	}
	
	/* 缓冲区满溢 */
	if(icnt > 255)
	{
		u1_msg.rx_length = icnt;
		memcpy(OutData,u1_msg.recv_buf,icnt);
		icnt=0;
		memset(u1_msg.recv_buf,0x00,sizeof(u1_msg.recv_buf));
	}
}

/********************************************************************************
*Function Name	：函数名称						*串口回调函数
*Create Date	：创建日期						*
*Created By		：创建人							*
*Function		：函数功能						*
*Modify Date	：修改日期						*
********************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/*………………………………………………………… 串口1，460800 ，中断接收…………………………………………………………*/
	if(huart->Instance==huart1.Instance)
	{
		/* 接收保存到数组 */
		USART1_TI_RX(u1_msg.recv_byte,u1_msg.recv_buf);
		/* 开启中断接收 */
		HAL_UART_Receive_IT(&huart1,&u1_msg.recv_byte,U1_RX_LENGTH);
		
	}
}

/********************************************************************************
*Function Name	：函数名称						*元素查找【标准函数 bsearch 】
*Create Date	：创建日期						*2023年3月28日
*Created By		：创建人							*
*Function		：函数功能						*返回元素下标，否则返回0
*Modify Date	：修改日期						*
Indata：待查找数组；
iElement：待查找元素；
iNums：Indata数组长度；
index_num：查询结果，元素在数组中的下标数值
icnt：防止查询结果中不只有1个
********************************************************************************/
uint8_t Find_Elements(char *Indata,char iElement,uint16_t iNums,uint8_t *index_num)
{
	uint8_t icnt=0;
	for(uint16_t i=0;i<iNums;i++)
	{
		if(Indata[i] == iElement)	index_num[icnt++] = i;
	}
	return icnt;
}


/********************************************************************************
*Function Name	：函数名称						*AT指令解析
*Create Date	：创建日期						*2023年3月28日
*Created By		：创建人							*
*Function		：函数功能						*
*Modify Date	：修改日期						*
********************************************************************************/
void U1_COMMAND_Handle(void)
{
	uint8_t i_Index[10]={0};
	uint8_t iEqual_nums=0;
	uint8_t iComma_nums=0;
	char tempchar[3]={0};
	
	//先情况缓存区域
	memset(u1_msg.cmd_arrary,0,sizeof(u1_msg.cmd_arrary));
	memset(u1_msg.data_arrary,0,sizeof(u1_msg.data_arrary));
	
	/*……………………………………………………………… 先判断是否是标准AT指令格式 ………………………………………………………………*/
	strncpy(tempchar,u1_msg.CharData,3);
	if(strcmp(tempchar,"AT+") == 0)
	{
		/*……………………………………………………………… 非AT测试指令 ………………………………………………………………*/
		if(u1_msg.rx_length > 4)
		{
			/* 第1步、查询元素"="，得到元素下标i_Index和元素个数i_nums */
			iEqual_nums = Find_Elements(u1_msg.CharData,'=',u1_msg.rx_length,i_Index);
			
			/* 只有一个“=” */
			if(iEqual_nums == 1) {
				//先拷贝出指令
				strncpy(u1_msg.cmd_arrary,(char*)(&u1_msg.CharData[2]),i_Index[0]-1);
				//清空
				uint8_t cmd_length = i_Index[0]-1;
				memset(i_Index,0,sizeof(i_Index));
				
					/* 第2步、查询元素“,”，得到元素下标i_Index和元素个数i_nums */
					iComma_nums = Find_Elements(u1_msg.CharData,',',u1_msg.rx_length,i_Index);
					/* 如果没有',' */
					if(iComma_nums == 0) {
						/* 如果不是查询指令，那么报错 */
						if((Find_Elements(u1_msg.CharData,'?',u1_msg.rx_length,i_Index) == 0) && (strcmp(u1_msg.cmd_arrary,"+MODE=") != 0))
						{
							printf(LED_RSP_Error);
						}
						/*……………………………… 如果是模式设置 ………………………………*/
						else if(strcmp(u1_msg.cmd_arrary,"+MODE=") == 0) {
							if(u1_msg.CharData[cmd_length+2] == '0')	{
								u1_msg.mode = 0;
								printf("\r\nSSVEP Mode Set OK\r\n");
							}
							else if(u1_msg.CharData[cmd_length+2] == '1')	{
								u1_msg.mode = 1;
								uint8_t Ucnt=0;
								for(uint8_t i=0;i<6;i++) {
									if(u1_msg.enable[i] != 0) Ucnt++;
								}
								if(Ucnt > 1) memset(u1_msg.enable,0,sizeof(u1_msg.enable));
								printf("\r\nERP Mode Set OK\r\n");
							}
							else {
								u1_msg.mode = 2;
								printf("\r\nMode Set ERROR\r\n");
							}
						}
						/*……………………………… 如果是查询指令 ………………………………*/
						
					}
					/* 错误"模式或查询"指令 */
					else if((iComma_nums != 0)&&(strcmp(u1_msg.cmd_arrary,"+MODE=") == 0)) {
						printf(LED_RSP_Error);
					}
					
					/*……………………………………………………………… 正确“参数设置”指令（根据实际指令，分类） ………………………………………………………………*/
					else if(iComma_nums != 0) {
						/*……………………………… 第一条指令：通道启用/关闭 ………………………………*/
						if((strcmp(u1_msg.cmd_arrary,"+CH=") == 0)&&(iComma_nums == 5)) {
							
							/* char类型转为uint8_t */
							u1_msg.enable[0] = (uint8_t)(u1_msg.CharData[6] - '0');
							u1_msg.enable[1] = (uint8_t)(u1_msg.CharData[8] - '0');
							u1_msg.enable[2] = (uint8_t)(u1_msg.CharData[10] - '0');
							u1_msg.enable[3] = (uint8_t)(u1_msg.CharData[12] - '0');
							u1_msg.enable[4] = (uint8_t)(u1_msg.CharData[14] - '0');
							u1_msg.enable[5] = (uint8_t)(u1_msg.CharData[16] - '0');
							
							for(uint8_t j=0;j<6;j++)
							{
								if((u1_msg.enable[j] != 0)&&(u1_msg.enable[j] != 1))
								{
									printf(LED_RSP_Error);
									memset(u1_msg.enable,0,sizeof(u1_msg.enable));
									break;
								}
								else {
									if(u1_msg.enable[j] == 1) {
										
										if(u1_msg.mode == 0) printf("Channel %d Enable\r\n",j+1);
										
										if(u1_msg.mode) {
											//统计开启通道数目
											u1_msg.ERP_cnt = u1_msg.ERP_cnt + 1;
										}
										else u1_msg.ERP_CH = 0;
									}
									else if(u1_msg.mode == 0) printf("Channel %d Disable\r\n",j+1);
								}
							}
							
							/* ERP通道 */
							if(u1_msg.ERP_cnt == 1) {
								u1_msg.ERP_cnt = 0;
								for(uint8_t j=0;j<6;j++) {
									if(u1_msg.enable[j] == 1) u1_msg.ERP_CH = j+1;				//ERP通道
								}
								printf("ERP Mode Channel %d Enable\r\n",u1_msg.ERP_CH);
							}
							else if(u1_msg.ERP_cnt > 1) {
								u1_msg.ERP_cnt = 0;
								printf(LED_RSP_Error);
							}
							
						}
						
						/*……………………………… 第二指令：通道频率设置 ………………………………*/
						else if((strcmp(u1_msg.cmd_arrary,"+FREQ=") == 0)&&(iComma_nums == 1)) {
							/* 确定输入通道数字是1位正整数，根据实际情况修改即可 */
							if(u1_msg.CharData[9] == ',') {
								/* 先确定通道 */
								uint8_t ich_num=(uint8_t)(u1_msg.CharData[8]-'0');
								/* 通道数字是0到6，根据实际情况修改即可 */
								if((ich_num > 0)&&(ich_num <= 7))
								{
									/* 注意：这里先减去1，方便后续使用 */
									ich_num = ich_num-1;
									uint8_t iPoint=0;			//记录小数点所在位置
									uint8_t iBits=0;
									
									/* 先清除 */
									uint8_t data_false=0;
									
									/* 如果有输入数字 */
									if(u1_msg.rx_length-12 > 0) {
										/* 计算频率 */
										/* 第2.1步：把数据每一位存到一个数组，同时查询小数点所在位置 */
										/* 注意：存储数字是从最高位存起的 */
										for(uint8_t k=10;k<u1_msg.rx_length-2;k++)	{
											u1_msg.data_arrary[ich_num][k-10] = (int8_t)(u1_msg.CharData[k]-'0');
											if(u1_msg.data_arrary[ich_num][k-10] == -2) iPoint=k-10;
										}
										/* 第2.2步：存储数据 */
										for(uint8_t j=0;j<4;j++) {
											/* 如果存在非法字符输入，打印错误消息 */
											/* 1、数字不在0~9之间并且不是-2（小数点转换之后）；2、小数点在最低位；3、小数点在最高位 */
											if(((u1_msg.data_arrary[ich_num][j] != -2)&&(u1_msg.data_arrary[ich_num][j]<0 || u1_msg.data_arrary[ich_num][j]>9)) || \
												(u1_msg.data_arrary[ich_num][0]==-2) || \
												u1_msg.data_arrary[ich_num][u1_msg.rx_length-3]==-2) {
													data_false=1;
													printf(LED_RSP_Error);
													break;
											}
										}
										
										/* ———————————————— 如果输入数据无误，计算频率值 -- 可以把这一步移出到其他地方计算 ————————————————*/
										if(data_false == 0)
										{
											/* 如果是整数,1~1000HZ */
											if(iPoint == 0)	{
												iBits = u1_msg.rx_length-12;		//数据位数
												if(iBits == 4) u1_msg.data_freq[ich_num] = u1_msg.data_arrary[ich_num][0]*1000 + \
																							u1_msg.data_arrary[ich_num][1]*100 + \
																							u1_msg.data_arrary[ich_num][2]*10 + \
																							u1_msg.data_arrary[ich_num][3];
												else if(iBits == 3) u1_msg.data_freq[ich_num] = u1_msg.data_arrary[ich_num][0]*100 + \
																								u1_msg.data_arrary[ich_num][1]*10 + \
																								u1_msg.data_arrary[ich_num][2];
												else if(iBits == 2) u1_msg.data_freq[ich_num] = u1_msg.data_arrary[ich_num][0]*10 + u1_msg.data_arrary[ich_num][1];
												else if(iBits == 1) u1_msg.data_freq[ich_num] = u1_msg.data_arrary[ich_num][0];
											}
											/* 如果是1位小数,0.1~99.9HZ */
											else {
												iBits = u1_msg.rx_length-12-1;		//数据位数
												/* 3个数字 + 1个小数点 */
												if(iBits == 3) {
													if(iPoint == 2) {
														u1_msg.data_freq[ich_num] = u1_msg.data_arrary[ich_num][0]*10 + \
																					u1_msg.data_arrary[ich_num][1] + \
																					u1_msg.data_arrary[ich_num][3]*0.1;
													}
													else {
														data_false = 1;
														printf(LED_RSP_Error);
													}
												}
												/* 2个数字 + 1个小数点 */
												else if(iBits == 2) {
													if(iPoint == 1) {
														u1_msg.data_freq[ich_num] = u1_msg.data_arrary[ich_num][0]+u1_msg.data_arrary[ich_num][2]*0.1;
													}
													else {
														data_false = 1;
														printf(LED_RSP_Error);
													}
												}
											}
											
											/* 频率范围0.1~100 */
											if((data_false == 0)&&(u1_msg.data_freq[ich_num] <= 100)) {
												if(ich_num < 6) printf("Channel %d Frequence = %.1f Set OK\r\n",ich_num+1,u1_msg.data_freq[ich_num]);
												else if(ich_num == 6) {
													if(u1_msg.mode == 0) printf("All Channel Frequence = %.1f Set OK\r\n",u1_msg.data_freq[ich_num]);
													else printf(LED_RSP_Error);
												}
											}
											else if(u1_msg.data_freq[ich_num] > 100) {
												printf("Frequence Out of Range!!!\r\n");
											}
										}
										/* ———————————————————————————————————————————————————————————————— */
										
									} //必须输入频率数值
									else printf(LED_RSP_Error);
								}	//通道数字是1到6
								else printf(LED_RSP_Error);
							}	//确定输入通道数字是1位正整数
							else printf(LED_RSP_Error);
						}	/* 不是规定的参数设置指令 -- 这一步可以添加新的参数设置指令 else if(……) */
						else printf(LED_RSP_Error);
						
						
					}
					
					
			}	//如果不止一个'=' 或 没有'=' 均报错
			else printf(LED_RSP_Error);
		}	//F发送指令只有“AT+\r\n”
		else printf(LED_RSP_Error);
	}
	/*……………………………………………………………… AT测试指令 ………………………………………………………………*/
	else if(strcmp(u1_msg.CharData,CMD_AT_TEST) == 0) {
		printf(LED_RSP_OK);
	}
	else printf(LED_RSP_Error);			/* 这一步也可以添加其他形式的指令 else if(……) */
	
}




