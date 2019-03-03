#include "wheel.h"

void Wheel_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// 打开GPIO的时钟
	RCC_APB2PeriphClockCmd(WHELL_RCC_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = WHEEL_L_IN1|WHEEL_L_IN2|WHEEL_R_IN3|WHEEL_R_IN4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(WHEEL_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(WHEEL_PORT,WHEEL_L_IN1|WHEEL_L_IN2|WHEEL_R_IN3|WHEEL_R_IN4);
}

void Wheel_Forward(void)
{
	GPIO_SetBits(WHEEL_PORT,WHEEL_L_IN1|WHEEL_R_IN3);
	GPIO_ResetBits(WHEEL_PORT,WHEEL_L_IN2|WHEEL_R_IN4);
	printf("i am forward\n");
}
void Wheel_Back(void)
{
	GPIO_SetBits(WHEEL_PORT,WHEEL_L_IN2|WHEEL_R_IN4);
	GPIO_ResetBits(WHEEL_PORT,WHEEL_L_IN1|WHEEL_R_IN3);
	printf("i am back\n");
}
void Wheel_Right(void)
{
	GPIO_SetBits(WHEEL_PORT,WHEEL_L_IN1);
	GPIO_ResetBits(WHEEL_PORT,WHEEL_L_IN2|WHEEL_R_IN4|WHEEL_R_IN3);
	printf("i am right\n");
}
void Wheel_Left(void)
{
	GPIO_SetBits(WHEEL_PORT,WHEEL_R_IN3);
	GPIO_ResetBits(WHEEL_PORT,WHEEL_L_IN1|WHEEL_L_IN2|WHEEL_R_IN4);
	printf("i am left\n");
}
void Wheel_Stop(void)
{
	GPIO_ResetBits(WHEEL_PORT,WHEEL_L_IN1|WHEEL_L_IN2|WHEEL_R_IN3|WHEEL_R_IN4);
	printf("i am stop\n");
}






