#include "sr04.h"



uint32_t CountTime=0;      //���㳬������ʱ��΢��ʱ�䣬��SysTick�ж��б仯

void SR04_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(SR04_RCC_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = SR04_Trig_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SR04_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SR04_Echo_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SR04_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(SR04_PORT,SR04_Trig_Pin);
	GPIO_ResetBits(SR04_PORT,SR04_Echo_Pin);
}

void SR04_DeInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(SR04_RCC_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = SR04_Trig_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SR04_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SR04_Echo_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;      //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SR04_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(SR04_PORT,SR04_Trig_Pin);
	GPIO_ResetBits(SR04_PORT,SR04_Echo_Pin);
}

void SR04_Count(void)
{
	uint16_t i=0;
	uint32_t time=0;
	float s=0;
	
	GPIO_SetBits(SR04_PORT,SR04_Trig_Pin);                   //��������
	delay_us(10);                                     //��ʱ10us,���Ƿ��յ���Ӧ
	GPIO_ResetBits(SR04_PORT,SR04_Trig_Pin);                //ֹͣ����   
	for(i=0;i<2000;i++)                             //ÿ�η��ͳ�����Ҫ���һ��ʱ��
	{
		if(GPIO_ReadInputDataBit(SR04_PORT,SR04_Echo_Pin))       //Echo�Ƿ��յ���Ӧ
		{
			CountTime=0;                                    //��ʱ������
			while(GPIO_ReadInputDataBit(SR04_PORT,SR04_Echo_Pin));
			time=CountTime;																	//���㳬�������͵����յ�ʱ��	
			//printf("CountTime:%d\n",time);
			s=time*17*0.001; 															  //������룬����
			printf("The SR04 distance:%.2fcm\n",s);
			
			GPIO_ResetBits(SR04_PORT,SR04_Echo_Pin); 
			break;
		}
	}
	
	if(s==0)
	{
		
	}
	else if(s<8)
	{		
		Wheel_Stop();
		Wheel_Left();
		delay_ms(2000);
		Wheel_Forward();
	}
	else
	{
		Wheel_Forward();
	}
	
}

