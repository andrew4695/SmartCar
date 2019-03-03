#include "esp8266.h"


void clear_buffer(void)
{
	uint8_t i=0;
	Usart_SendString(USART1,usart3_data);
	for(i=0;i<usart3_num;i++)
	{
		usart3_data[i]=0;
	}
	usart3_num=0;
}

void ESP_EN_RST_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	USART3_GPIO_APBxClkCmd(USART3_GPIO_CLK, ENABLE);
	
	// ��GPIO����Ϊ����ģʽ
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_8);  //оƬʹ�ܣ��ߵ�ƽ��Ч
	
	GPIO_SetBits(GPIOB,GPIO_Pin_9);  //��λ���ţ��͵�ƽ��Ч
	
	delay_ms(1000);
}

void ESP_SendSting(char *str)
{
	char *strx=NULL;
	
	Usart_SendString(USART3,str);
	delay_ms(300);			
	strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK	
	clear_buffer();
	while(strx==NULL)
	{
		
		Usart_SendString(USART3,str);
		delay_ms(300);			
		strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK			
		clear_buffer();
	}			
}

void ESP_Init(void)
{
	char *strx=NULL;
	
	Usart_SendString(USART3,"AT\r\n");
	delay_ms(300);			
	strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK	
	clear_buffer();
	while(strx==NULL)
	{
		
		Usart_SendString(USART3,"AT\r\n");
		delay_ms(300);			
		strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK			
		clear_buffer();
	}			

	Usart_SendString(USART3,"AT+CWMODE=2\r\n");
	delay_ms(300);			
	strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK	
	clear_buffer();
	while(strx==NULL)
	{
		
		Usart_SendString(USART3,"AT+CWMODE=2\r\n");
		delay_ms(300);			
		strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK			
		clear_buffer();
	}			

	Usart_SendString(USART3,"AT+RST\r\n");
	delay_ms(300);			
	strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK	
	clear_buffer();
	while(strx==NULL)
	{
		
		Usart_SendString(USART3,"AT+RST\r\n");
		delay_ms(300);			
		strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK			
		clear_buffer();
	}			
	
	Usart_SendString(USART3,"AT+CWSAP=\"SmartCar\",\"88888888\",1,3\r\n");
	delay_ms(300);			
	strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK	
	clear_buffer();
	while(strx==NULL)
	{
		
		Usart_SendString(USART3,"AT+CWSAP=\"SmartCar\",\"88888888\",1,3\r\n");
		delay_ms(300);			
		strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK			
		clear_buffer();
	}		

	Usart_SendString(USART3,"AT+CIPMUX=1\r\n");
	delay_ms(300);			
	strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK	
	clear_buffer();
	while(strx==NULL)
	{
		
		Usart_SendString(USART3,"AT+CIAMUX=1\r\n");
		delay_ms(300);			
		strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK			
		clear_buffer();
	}			
	
	Usart_SendString(USART3,"AT+CIPSERVER=1,8080\r\n");
	delay_ms(300);			
	strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK	
	clear_buffer();
	while(strx==NULL)
	{
		
		Usart_SendString(USART3,"AT+CIPSERVER=1,8080\r\n");
		delay_ms(300);			
		strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK			
		clear_buffer();
	}			
	
	Usart_SendString(USART3,"AT+CIPSTO=2000\r\n");
	delay_ms(300);			
	strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK	
	clear_buffer();
	while(strx==NULL)
	{
		
		Usart_SendString(USART3,"AT+CIPSTO=2000\r\n");
		delay_ms(300);			
		strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK			
		clear_buffer();
	}		

	Usart_SendString(USART3,"AT+CIPSTATUS\r\n");
	delay_ms(300);			
	strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK	
	clear_buffer();
	while(strx==NULL)
	{
		
		Usart_SendString(USART3,"AT+CIPSTATUS\r\n");
		delay_ms(300);			
		strx=strstr((const char*)usart3_data,(const char*)"OK");//����OK			
		clear_buffer();
	}			
}

void ESP_Check(char *pdata)
{
	char *strx=NULL;
	char cdm[10]={0};
	uint8_t i=0;
	
	strx=strstr((const char*)usart3_data,(const char*)"+IPD");
	
	if(strx!=NULL)
	{

		while(*strx++!=':');
		do{
				cdm[i++]=*strx++;		
		}while(*strx!=NULL);	
		//printf("*strx=%c\n",*strx);
		cdm[i]=0;

		if(strcmp(cdm,"start")==0)
		{
			SR04_Init();       //��������ʼ��ֻ�����յ�start������
			delay_ms(10);
			
			Wheel_Forward();
			GPIO_SetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_5);
			GPIO_ResetBits(GPIOB,GPIO_Pin_0); 
			printf("i am start\n");
			
		}
		else if(strcmp(cdm,"stop")==0)
		{
			SR04_DeInit();
			Wheel_Stop();
			GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1); 
			GPIO_ResetBits(GPIOB,GPIO_Pin_5); 
			printf("i am stop\n");			
		}
		else if(strcmp(cdm,"right")==0)
		{
			Wheel_Stop();
			Wheel_Right();
			//GPIO_SetBits(GPIOB,GPIO_Pin_1); 
			printf("i am right\n");			
		}
		else if(strcmp(cdm,"left")==0)
		{
			Wheel_Stop();
			Wheel_Left();
			//GPIO_SetBits(GPIOB,GPIO_Pin_1); 
			printf("i am left\n");			
		}
		else 
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_1); 
			strcpy(pdata,cdm);
			delay_ms(5);
		}
				
		i=0;
	}
}


