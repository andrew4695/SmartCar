#include "sr04.h"



uint32_t CountTime=0;      //计算超声波延时的微秒时间，在SysTick中断中变化

void SR04_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(SR04_RCC_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = SR04_Trig_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SR04_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SR04_Echo_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //下拉输入
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SR04_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SR04_Echo_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;      //下拉输入
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
	
	GPIO_SetBits(SR04_PORT,SR04_Trig_Pin);                   //启动发送
	delay_us(10);                                     //延时10us,看是否收到响应
	GPIO_ResetBits(SR04_PORT,SR04_Trig_Pin);                //停止发送   
	for(i=0;i<2000;i++)                             //每次发送超声波要间隔一段时间
	{
		if(GPIO_ReadInputDataBit(SR04_PORT,SR04_Echo_Pin))       //Echo是否收到响应
		{
			CountTime=0;                                    //计时器归零
			while(GPIO_ReadInputDataBit(SR04_PORT,SR04_Echo_Pin));
			time=CountTime;																	//计算超声波发送到接收的时间	
			//printf("CountTime:%d\n",time);
			s=time*17*0.001; 															  //计算距离，厘米
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

