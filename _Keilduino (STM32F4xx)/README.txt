# A Cross-platform migration Project @FASTSHIFT
# Arduino for STM32F4xx

# https://github.com/FASTSHIFT/Arduino-For-Keil

ע��{ 
	�˰汾�ı�׼�����Ĭ�Ͼ���Ƶ����25MHz;
	�����ؾ���Ϊ8MHz,��Ҫ��system_stm32f4xx.c -> ��254�� -> PLL_M���� 25 ��Ϊ 8
}

//*********************************UPGRADE LOGS************************************//

//Finish in 2018.8.1    V_1.0 ����STM32F4xx��־�����(1.3.0��)����ֲ��ȫ����ArduinoAPI
//Upgrade   2018.8.14   V_1.1 ����USART��ش��룬�޸�Tone��ֻռ��һ����ʱ��(��ʹ��toneSetTimer()�����л�),time_exti����Ϊtimer
//Upgrade   2018.8.17   V_1.2 ��Arduino.h����˸���������GPIO�Ĵ��������������������������ļ�����
//Upgrade   2018.8.17   V_1.3 ���WCharacter.h��֧��Arduino�й�Characters�ĺ��������mcu_type.h��ʹArduino.h���Կ�MCUʹ��
//Upgrade   2018.11.28  V_1.4 ������ע��
//Upgrade   2019.2.17   V_1.5 ����Ч���Լ�������,SPI���ѿ�����������
//Upgrade   2019.3.22   V_1.6 ΪSysTick��������ж����ȼ�����ֹ�������жϴ��(�ǳ���Ҫ!)
//Upgrade   2019.5.9    V_1.7 ����:ADC�⡢PWM�⡢��ʱ���⡢Servo�⡢PIN_MAP��������ӳ���Tone���ѿ�����������