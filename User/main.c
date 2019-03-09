/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
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


//变量定义
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
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
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	uint8_t i=0;
	
	//定时器初始化
	SysTick_Init(); 
	delay_ms(10);
	
	//串口初始化
	USART_Config();
	USART3_Config();
	delay_ms(10);
	
	//电机初始化
	Wheel_Init();
	delay_ms(10);
		
//	//超声波初始化
//	SR04_Init();    //超声波初始化只有在收到start后才完成
//	delay_ms(10);
	printf("1111\n");  //必须加这一句，不然WIFI模块无法初始化，为什么？？？？
	#if 1
	//RRFIF卡初始化
	MFRC_Configuration();
	PcdReset();
	PcdAntennaOff();
	delay_ms(2);
	PcdAntennaOn();
	delay_ms(10);
	
	//LED初始化
	Led_Init();
	delay_ms(10);
		

	//ESP8266初始化
	ESP_EN_RST_GPIO_Config();
	delay_ms(10);
	ESP_Init();
	delay_ms(10);
		
	/* 发送一个字符串 */
	Usart_SendString( DEBUG_USARTx,"这是一个智能停车系统实验\n");	
	delay_ms(2000);
	
	#endif
  while(1)
	{	
		//串口1中断，与ESP8266通信
		if(f1==1)
		{
			f1=0;
			//printf("usart1 data:%s\n",usart1_data);
			Usart_SendString(USART3,usart1_data);  //判断AT指令是否是“\r\n”结尾，必须是该格式才有效		
			for(i=0;i<usart1_num;i++)
			{
				usart1_data[i]=0;
			}
			usart1_num=0;
		}		
		//串口3中断，WIFI数据检测
		if(f3==1)           
		{
			f3=0;
			Usart_SendString(USART1,usart3_data);
			ESP_Check(esp_data);       //检测函数
			delay_ms(200);     //该延时必须加，为什么？？？？
			for(i=0;i<usart3_num;i++)
			{
				usart3_data[i]=0;
			}
			usart3_num=0;
		}
		
	//wheel_test();
		
		//RFID卡检测
		MFRC_Check(esp_data);
			
		//超声波距离检测
		SR04_Count();
		
//		printf("程序运行完毕\n");
//		delay_ms(3000);
	}	
}
/*********************************************END OF FILE**********************/
