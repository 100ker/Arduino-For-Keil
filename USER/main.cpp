#include "FileGroup.h"

//HardwareSerial Serial(USART1);//TX-PA9 RX-PA10
//HardwareSerial Serial2(USART2);//TX-PA2 RX-PA3
//HardwareSerial Serial3(USART3);//TX-PB10 RX-PB11
//HardwareSPI SPI(SPI1);//SCK-PB13 MISO-PB14 MOSI-PB15
//HardwareSPI SPI_2(SPI2);//SCK-PA5 MISO-PA6 MOSI-PA7
//TwoWire Wire(SCL_Pin, SDA_Pin, SOFT_FAST);

void setup()
{
	
}

void loop()
{
	
}

//*****************MAIN******************//
int main(void)
{
	delay_init();
	//ADCx_Init();//If use analogRead
	//ADCx_DMA_Init();
	setup();
	for(;;)loop();
}

//*****************UPGRADE LOGS******************//

//Finish in 2017.11.20 V_1.0 ֧��pinMode��digitalWrite��digitalRead��delay�Ȼ���Arduino API
//Upgrade 			 11.21 V_1.1 ����C++��д���򣬿��Լ��ݲ���Arduino�⺯��
//Upgrade 			 11.23 V_1.2 ��ֲPrint��Stream��WString��class
//Upgrade 			 12.12 V_1.3 ֧��millis��micros��Wire class������Serial class API(��Ŀ���ϴ�GitHub<Arduino_For_Keil>)
//Upgrade 	2018.1.10  V_1.4 ȫ��֧��Serial class���Լ���ʱ����
//Upgrade 			 1.12  V_1.5 ���Լ���SD���ļ�ϵͳ��֧�֣�����"_Keilduino"
//Upgrade 			 1.21  V_1.6 ֧��analogRead(DMA/NoDMA)��analogWrite
//Upgrade 			 1.23  V_1.7 ֧������GPIO�ⲿ�ж�
//Upgrade 			 1.31  V_1.8 �޸�����Pxx������������BUG��TIM2~TIM4��֧�����PWM
//Upgrade 			 2.1 	 V_1.9 HardwareSerial�м���end()��attachInterrupt()
//Upgrade 			 2.10  V_2.0 �޸ĺ���ָ�붨�巽ʽ 
