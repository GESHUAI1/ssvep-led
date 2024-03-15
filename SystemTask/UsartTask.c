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
*Function Name	����������						*ʮ����������ת�ַ�
*Create Date	����������						*
*Created By		��������							*
*Function		����������						*
*Modify Date	���޸�����						*
********************************************************************************/
void HexToChar(uint8_t* iData,uint16_t iLength)
{
	//�������
	memset(u1_msg.CharData,0,sizeof(u1_msg.CharData));
	//ת�����ݣ�ʮ������ ����> �ַ�
	memcpy(u1_msg.CharData,iData,iLength);
}

/********************************************************************************
*Function Name	����������						*�����жϽ��մ���
*Create Date	����������						*
*Created By		��������							*
*Function		����������						*
*Modify Date	���޸�����						*
********************************************************************************/
uint16_t icnt = 0;
void USART1_TI_RX(uint8_t InData,uint8_t* OutData)
{
	/* һ�ν���һ���ֽ� */
	u1_msg.recv_buf[icnt++] = InData;
	
	/* �Ի���������ֽڽ����ж� -- ĩβ��\r\n���س����У�*/
	if((u1_msg.recv_buf[icnt-2] == 0x0D)&&(u1_msg.recv_buf[icnt-1] == 0x0A))
	{
		memcpy(OutData,u1_msg.recv_buf,icnt);
		u1_msg.rx_length = icnt;
		/* ��ʱ��� */
		icnt = 0;
		/* ��������ת�� */
		HexToChar(u1_msg.recv_buf,u1_msg.rx_length);
		/* ����������� */
		memset(u1_msg.recv_buf,0x00,sizeof(u1_msg.recv_buf));
		/* ������ɱ�־ */
		u1_msg.rx_flag = 1;
	}
	
	/* ���������� */
	if(icnt > 255)
	{
		u1_msg.rx_length = icnt;
		memcpy(OutData,u1_msg.recv_buf,icnt);
		icnt=0;
		memset(u1_msg.recv_buf,0x00,sizeof(u1_msg.recv_buf));
	}
}

/********************************************************************************
*Function Name	����������						*���ڻص�����
*Create Date	����������						*
*Created By		��������							*
*Function		����������						*
*Modify Date	���޸�����						*
********************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/*�������������������������������������������� ����1��460800 ���жϽ��ա�������������������������������������������*/
	if(huart->Instance==huart1.Instance)
	{
		/* ���ձ��浽���� */
		USART1_TI_RX(u1_msg.recv_byte,u1_msg.recv_buf);
		/* �����жϽ��� */
		HAL_UART_Receive_IT(&huart1,&u1_msg.recv_byte,U1_RX_LENGTH);
		
	}
}

/********************************************************************************
*Function Name	����������						*Ԫ�ز��ҡ���׼���� bsearch ��
*Create Date	����������						*2023��3��28��
*Created By		��������							*
*Function		����������						*����Ԫ���±꣬���򷵻�0
*Modify Date	���޸�����						*
Indata�����������飻
iElement��������Ԫ�أ�
iNums��Indata���鳤�ȣ�
index_num����ѯ�����Ԫ���������е��±���ֵ
icnt����ֹ��ѯ����в�ֻ��1��
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
*Function Name	����������						*ATָ�����
*Create Date	����������						*2023��3��28��
*Created By		��������							*
*Function		����������						*
*Modify Date	���޸�����						*
********************************************************************************/
void U1_COMMAND_Handle(void)
{
	uint8_t i_Index[10]={0};
	uint8_t iEqual_nums=0;
	uint8_t iComma_nums=0;
	char tempchar[3]={0};
	
	//�������������
	memset(u1_msg.cmd_arrary,0,sizeof(u1_msg.cmd_arrary));
	memset(u1_msg.data_arrary,0,sizeof(u1_msg.data_arrary));
	
	/*������������������������������������������������ ���ж��Ƿ��Ǳ�׼ATָ���ʽ ������������������������������������������������*/
	strncpy(tempchar,u1_msg.CharData,3);
	if(strcmp(tempchar,"AT+") == 0)
	{
		/*������������������������������������������������ ��AT����ָ�� ������������������������������������������������*/
		if(u1_msg.rx_length > 4)
		{
			/* ��1������ѯԪ��"="���õ�Ԫ���±�i_Index��Ԫ�ظ���i_nums */
			iEqual_nums = Find_Elements(u1_msg.CharData,'=',u1_msg.rx_length,i_Index);
			
			/* ֻ��һ����=�� */
			if(iEqual_nums == 1) {
				//�ȿ�����ָ��
				strncpy(u1_msg.cmd_arrary,(char*)(&u1_msg.CharData[2]),i_Index[0]-1);
				//���
				uint8_t cmd_length = i_Index[0]-1;
				memset(i_Index,0,sizeof(i_Index));
				
					/* ��2������ѯԪ�ء�,�����õ�Ԫ���±�i_Index��Ԫ�ظ���i_nums */
					iComma_nums = Find_Elements(u1_msg.CharData,',',u1_msg.rx_length,i_Index);
					/* ���û��',' */
					if(iComma_nums == 0) {
						/* ������ǲ�ѯָ���ô���� */
						if((Find_Elements(u1_msg.CharData,'?',u1_msg.rx_length,i_Index) == 0) && (strcmp(u1_msg.cmd_arrary,"+MODE=") != 0))
						{
							printf(LED_RSP_Error);
						}
						/*������������������������ �����ģʽ���� ������������������������*/
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
						/*������������������������ ����ǲ�ѯָ�� ������������������������*/
						
					}
					/* ����"ģʽ���ѯ"ָ�� */
					else if((iComma_nums != 0)&&(strcmp(u1_msg.cmd_arrary,"+MODE=") == 0)) {
						printf(LED_RSP_Error);
					}
					
					/*������������������������������������������������ ��ȷ���������á�ָ�����ʵ��ָ����ࣩ ������������������������������������������������*/
					else if(iComma_nums != 0) {
						/*������������������������ ��һ��ָ�ͨ������/�ر� ������������������������*/
						if((strcmp(u1_msg.cmd_arrary,"+CH=") == 0)&&(iComma_nums == 5)) {
							
							/* char����תΪuint8_t */
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
											//ͳ�ƿ���ͨ����Ŀ
											u1_msg.ERP_cnt = u1_msg.ERP_cnt + 1;
										}
										else u1_msg.ERP_CH = 0;
									}
									else if(u1_msg.mode == 0) printf("Channel %d Disable\r\n",j+1);
								}
							}
							
							/* ERPͨ�� */
							if(u1_msg.ERP_cnt == 1) {
								u1_msg.ERP_cnt = 0;
								for(uint8_t j=0;j<6;j++) {
									if(u1_msg.enable[j] == 1) u1_msg.ERP_CH = j+1;				//ERPͨ��
								}
								printf("ERP Mode Channel %d Enable\r\n",u1_msg.ERP_CH);
							}
							else if(u1_msg.ERP_cnt > 1) {
								u1_msg.ERP_cnt = 0;
								printf(LED_RSP_Error);
							}
							
						}
						
						/*������������������������ �ڶ�ָ�ͨ��Ƶ������ ������������������������*/
						else if((strcmp(u1_msg.cmd_arrary,"+FREQ=") == 0)&&(iComma_nums == 1)) {
							/* ȷ������ͨ��������1λ������������ʵ������޸ļ��� */
							if(u1_msg.CharData[9] == ',') {
								/* ��ȷ��ͨ�� */
								uint8_t ich_num=(uint8_t)(u1_msg.CharData[8]-'0');
								/* ͨ��������0��6������ʵ������޸ļ��� */
								if((ich_num > 0)&&(ich_num <= 7))
								{
									/* ע�⣺�����ȼ�ȥ1���������ʹ�� */
									ich_num = ich_num-1;
									uint8_t iPoint=0;			//��¼С��������λ��
									uint8_t iBits=0;
									
									/* ����� */
									uint8_t data_false=0;
									
									/* ������������� */
									if(u1_msg.rx_length-12 > 0) {
										/* ����Ƶ�� */
										/* ��2.1����������ÿһλ�浽һ�����飬ͬʱ��ѯС��������λ�� */
										/* ע�⣺�洢�����Ǵ����λ����� */
										for(uint8_t k=10;k<u1_msg.rx_length-2;k++)	{
											u1_msg.data_arrary[ich_num][k-10] = (int8_t)(u1_msg.CharData[k]-'0');
											if(u1_msg.data_arrary[ich_num][k-10] == -2) iPoint=k-10;
										}
										/* ��2.2�����洢���� */
										for(uint8_t j=0;j<4;j++) {
											/* ������ڷǷ��ַ����룬��ӡ������Ϣ */
											/* 1�����ֲ���0~9֮�䲢�Ҳ���-2��С����ת��֮�󣩣�2��С���������λ��3��С���������λ */
											if(((u1_msg.data_arrary[ich_num][j] != -2)&&(u1_msg.data_arrary[ich_num][j]<0 || u1_msg.data_arrary[ich_num][j]>9)) || \
												(u1_msg.data_arrary[ich_num][0]==-2) || \
												u1_msg.data_arrary[ich_num][u1_msg.rx_length-3]==-2) {
													data_false=1;
													printf(LED_RSP_Error);
													break;
											}
										}
										
										/* �������������������������������� ��������������󣬼���Ƶ��ֵ -- ���԰���һ���Ƴ��������ط����� ��������������������������������*/
										if(data_false == 0)
										{
											/* ���������,1~1000HZ */
											if(iPoint == 0)	{
												iBits = u1_msg.rx_length-12;		//����λ��
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
											/* �����1λС��,0.1~99.9HZ */
											else {
												iBits = u1_msg.rx_length-12-1;		//����λ��
												/* 3������ + 1��С���� */
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
												/* 2������ + 1��С���� */
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
											
											/* Ƶ�ʷ�Χ0.1~100 */
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
										/* �������������������������������������������������������������������������������������������������������������������������������� */
										
									} //��������Ƶ����ֵ
									else printf(LED_RSP_Error);
								}	//ͨ��������1��6
								else printf(LED_RSP_Error);
							}	//ȷ������ͨ��������1λ������
							else printf(LED_RSP_Error);
						}	/* ���ǹ涨�Ĳ�������ָ�� -- ��һ����������µĲ�������ָ�� else if(����) */
						else printf(LED_RSP_Error);
						
						
					}
					
					
			}	//�����ֹһ��'=' �� û��'=' ������
			else printf(LED_RSP_Error);
		}	//F����ָ��ֻ�С�AT+\r\n��
		else printf(LED_RSP_Error);
	}
	/*������������������������������������������������ AT����ָ�� ������������������������������������������������*/
	else if(strcmp(u1_msg.CharData,CMD_AT_TEST) == 0) {
		printf(LED_RSP_OK);
	}
	else printf(LED_RSP_Error);			/* ��һ��Ҳ�������������ʽ��ָ�� else if(����) */
	
}




