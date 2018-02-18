#include "pwm.h"
#include "Arduino.h"

const int PWM_Pin[4][4] ={{PA8,PA9,PA10,PA11},
													{PA0,PA1,PA2,PA3},
													{PA6,PA7,PB0,PB1},
													{PB6,PB7,PB8,PB9}};

TIM_TypeDef* TIMx[4]={TIM1,TIM2,TIM3,TIM4};

//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIMx_Init(TIM_TypeDef* TIMx,u16 arr,u16 psc,u8 CHx)//f=72MHz/arr/psc,���ռ�ձ�=arr
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

			 if(TIMx == TIM1)RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	else if(TIMx == TIM2)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	else if(TIMx == TIM3)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	else if(TIMx == TIM4)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	switch(CHx)
	{
		case 1:
			TIM_OC1Init(TIMx, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		case 2:
			TIM_OC2Init(TIMx, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		case 3:
			TIM_OC3Init(TIMx, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		case 4:
			TIM_OC4Init(TIMx, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
	}
	
	TIM_Cmd(TIMx, ENABLE);
//	TIM_TimeBaseStructure.TIM_Period = arr-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
//	TIM_TimeBaseStructure.TIM_Prescaler =psc-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

// 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_Pulse = arr-1-300; //���ô�װ�벶��ȽϼĴ���������ֵ
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
//	TIM_OC1Init(TIMx, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

//  TIM_CtrlPWMOutputs(TIMx,ENABLE);	//MOE �����ʹ��	

//	TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);  //CHxԤװ��ʹ��	 
//	
//	TIM_ARRPreloadConfig(TIMx, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
//	
//	TIM_Cmd(TIMx, ENABLE);  //ʹ��TIMx
}

uint8_t GetPWM_TIMx_CHx(int Pin)
{
	uint8_t i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(Pin==PWM_Pin[i][j])
			{
				i++,j++;
				return (i*10+j);
			}
		}
	}	
	return 0;
}

uint8_t PWM_Init(int Pin)
{
	uint32_t arr,psc;
	uint8_t PWM_TIMx,PWM_CHx;
	uint8_t PWM_TIMx_CHx = GetPWM_TIMx_CHx(Pin);
	if(PWM_TIMx_CHx==0)return 0;
	
	PWM_TIMx=PWM_TIMx_CHx/10%10;
	PWM_CHx=PWM_TIMx_CHx/1%10;
	
	pinMode(Pin,GPIO_Mode_AF_PP);
	
	arr = PWM_DutyCycle;
//	if(PWM_TIMx!=1)psc = 36000000/PWM_DutyCycle/PWM_Frequency;//f=36MHz(APB1),72MHz(APB2)/arr/psc,���ռ�ձ�=arr
//	else psc = 72000000/PWM_DutyCycle/PWM_Frequency;
	psc = 72000000/PWM_DutyCycle/PWM_Frequency;
	
	TIM_Cmd(TIMx[PWM_TIMx-1], DISABLE);
	TIMx_Init(TIMx[PWM_TIMx-1],arr-1,psc-1,PWM_CHx);
	return 1;
}

uint16_t pwmWrite(int pin,u16 val)
{
	uint8_t PWM_TIMx,PWM_CHx;
	uint8_t PWM_TIMx_CHx = GetPWM_TIMx_CHx(pin);
	if(PWM_TIMx_CHx==0)return 0;
	if(val==0)
	{
		digitalWrite(pin,LOW);
		return 0;
	}
	else if(val>=PWM_DutyCycle)
	{
		digitalWrite(pin,HIGH);
		return val;
	}
	
	PWM_TIMx=PWM_TIMx_CHx/10%10;
	PWM_CHx=PWM_TIMx_CHx/1%10;
	
	switch(PWM_CHx)
	{
		case 1: TIM_SetCompare1(TIMx[PWM_TIMx-1], val);break;
		case 2: TIM_SetCompare2(TIMx[PWM_TIMx-1], val);break;
		case 3: TIM_SetCompare3(TIMx[PWM_TIMx-1], val);break;
		case 4: TIM_SetCompare4(TIMx[PWM_TIMx-1], val);break;
	}
	return val;
}
