#ifndef DELAY_H_
#define DELAY_H_

#include "stm32f10x.h"

extern uint32_t TimeUS;
extern uint32_t TimeMS;


void SysTick_Init(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

#endif



