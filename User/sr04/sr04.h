#ifndef SR04_H_
#define SR04_H_

#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#include "wheel.h"
#include "delay.h"


#define SR04_RCC_CLK       RCC_APB2Periph_GPIOC
#define SR04_PORT      		 GPIOC
#define SR04_Trig_Pin      GPIO_Pin_6
#define SR04_Echo_Pin      GPIO_Pin_7


void SR04_Count(void);
void SR04_Init(void);
void SR04_DeInit(void);

#endif


