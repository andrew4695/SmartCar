#include "delay.h"

uint32_t TimeUS=0;
uint32_t TimeMS=0;

void SysTick_Init(void)
{
	if(SysTick_Config(72))        //初始化SysTick计时器1us中断一次
	{
		while(1);
	}
}
void delay_us(uint32_t us)   //微秒延时
{
	TimeUS=us;
	while(TimeUS!=0);
}
void delay_ms(uint32_t ms)    //毫秒延时
{
	TimeMS=1000*ms;
	while(TimeMS!=0);	
}




