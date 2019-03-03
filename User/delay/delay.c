#include "delay.h"

uint32_t TimeUS=0;
uint32_t TimeMS=0;

void SysTick_Init(void)
{
	if(SysTick_Config(72))        //��ʼ��SysTick��ʱ��1us�ж�һ��
	{
		while(1);
	}
}
void delay_us(uint32_t us)   //΢����ʱ
{
	TimeUS=us;
	while(TimeUS!=0);
}
void delay_ms(uint32_t ms)    //������ʱ
{
	TimeMS=1000*ms;
	while(TimeMS!=0);	
}




