/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
//#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include "wheel.h"
#include "sr04.h"
#include "delay.h"
#include "esp8266.h"
#include "mfrc522.h"


//��������
char usart1_data[100]={0};
char usart3_data[100]={0};
uint8_t usart1_num=0;
uint8_t usart3_num=0;
uint8_t f1=0,f3=0;
char esp_data[10]={0};

void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_0); 
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
}

void wheel_test(void)
{
	GPIO_SetBits(WHEEL_PORT,WHEEL_L_IN2);
	GPIO_ResetBits(WHEEL_PORT,WHEEL_L_IN1);
//	GPIO_SetBits(WHEEL_PORT,WHEEL_R_IN4);
//	GPIO_ResetBits(WHEEL_PORT,WHEEL_R_IN3);
}

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	uint8_t i=0;
	
	//��ʱ����ʼ��
	SysTick_Init(); 
	delay_ms(10);
	
	//���ڳ�ʼ��
	USART_Config();
	USART3_Config();
	delay_ms(10);
	
	//�����ʼ��
	Wheel_Init();
	delay_ms(10);
		
//	//��������ʼ��
//	SR04_Init();    //��������ʼ��ֻ�����յ�start������
//	delay_ms(10);
	printf("1111\n");  //�������һ�䣬��ȻWIFIģ���޷���ʼ����Ϊʲô��������
	#if 1
	//RRFIF����ʼ��
	MFRC_Configuration();
	PcdReset();
	PcdAntennaOff();
	delay_ms(2);
	PcdAntennaOn();
	delay_ms(10);
	
	//LED��ʼ��
	Led_Init();
	delay_ms(10);
		

	//ESP8266��ʼ��
	ESP_EN_RST_GPIO_Config();
	delay_ms(10);
	ESP_Init();
	delay_ms(10);
		
	/* ����һ���ַ��� */
	Usart_SendString( DEBUG_USARTx,"����һ������ͣ��ϵͳʵ��\n");	
	delay_ms(2000);
	
	#endif
  while(1)
	{	
		//����1�жϣ���ESP8266ͨ��
		if(f1==1)
		{
			f1=0;
			//printf("usart1 data:%s\n",usart1_data);
			Usart_SendString(USART3,usart1_data);  //�ж�ATָ���Ƿ��ǡ�\r\n����β�������Ǹø�ʽ����Ч		
			for(i=0;i<usart1_num;i++)
			{
				usart1_data[i]=0;
			}
			usart1_num=0;
		}		
		//����3�жϣ�WIFI���ݼ��
		if(f3==1)           
		{
			f3=0;
			Usart_SendString(USART1,usart3_data);
			ESP_Check(esp_data);       //��⺯��
			delay_ms(200);     //����ʱ����ӣ�Ϊʲô��������
			for(i=0;i<usart3_num;i++)
			{
				usart3_data[i]=0;
			}
			usart3_num=0;
		}
		
	//wheel_test();
		
		//RFID�����
		MFRC_Check(esp_data);
			
		//������������
		SR04_Count();
		
//		printf("�����������\n");
//		delay_ms(3000);
	}	
}
/*********************************************END OF FILE**********************/
