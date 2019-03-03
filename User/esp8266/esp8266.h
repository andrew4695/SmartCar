#ifndef ESP8266_H_
#define ESP8266_H_
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "delay.h"
#include "string.h"
#include "wheel.h"
#include "sr04.h"

extern char usart1_data[100];
extern char usart3_data[100];
extern uint8_t usart1_num;
extern uint8_t usart3_num;
extern uint8_t f1,f3;


void clear_buffer(void);
void ESP_EN_RST_GPIO_Config(void);
void ESP_SendSting(char *str);
void ESP_Init(void);
void ESP_Check(char *pdata);


#endif

