#ifndef WHEEL_H_
#define WHEEL_H_

#include "stm32f10x.h"
#include "stdio.h"
#include "stm32f10x_it.h"

#define WHELL_RCC_CLK  RCC_APB2Periph_GPIOC
#define WHEEL_PORT     GPIOC
//#define WHEEL_L_IN1    GPIO_Pin_8
//#define WHEEL_L_IN2    GPIO_Pin_9
//#define WHEEL_R_IN3    GPIO_Pin_10
//#define WHEEL_R_IN4    GPIO_Pin_11
#define WHEEL_L_IN1    GPIO_Pin_10
#define WHEEL_L_IN2    GPIO_Pin_11
#define WHEEL_R_IN3    GPIO_Pin_9
#define WHEEL_R_IN4    GPIO_Pin_8



void Wheel_Init(void);
void Wheel_Forward(void);
void Wheel_Back(void);
void Wheel_Right(void);
void Wheel_Left(void);
void Wheel_Stop(void);


#endif


