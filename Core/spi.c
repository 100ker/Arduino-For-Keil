#include "spi.h"
#include "Arduino.h"

void SPI_begin(SPI_TypeDef* SPIx)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	switch((int)SPIx)
	{
		case (int)SPI1:
			RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE);
//			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
//			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������	
//			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//			GPIO_Init(GPIOA, &GPIO_InitStructure);
//			GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
			pinMode(PA5,GPIO_Mode_AF_PP);
			pinMode(PA6,GPIO_Mode_AF_PP);
			pinMode(PA7,GPIO_Mode_AF_OD);
			break;
		case (int)SPI2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
			RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
			break;
	}
}

void SPI_Settings(	SPI_TypeDef* SPIx,
										u16 SPI_Mode_MS,
										u16 SPI_DataSize,
										u16 SPI_MODE,
										u16 SPI_NSS,
										u16 SPI_BaudRatePrescaler,
										u16 SPI_FirstBit)
{
	SPI_InitTypeDef  SPI_InitStructure;
	u16 SPI_CPOL,SPI_CPHA;
	SPI_Cmd(SPIx,DISABLE);
	
	switch(SPI_MODE)
	{
		case 0:
			SPI_CPOL = SPI_CPOL_Low;
			SPI_CPHA = SPI_CPHA_1Edge;
			break;
		case 1:
			SPI_CPOL = SPI_CPOL_Low;
			SPI_CPHA = SPI_CPHA_2Edge;
			break;
		case 2:
			SPI_CPOL = SPI_CPOL_High;
			SPI_CPHA = SPI_CPHA_1Edge;
			break;
		case 3:
			SPI_CPOL = SPI_CPOL_High;
			SPI_CPHA = SPI_CPHA_2Edge;
			break;
	}

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_MS;		//����SPI����ģʽ:(SPI_Mode_Master,SPI_Mode_Slave)
	SPI_InitStructure.SPI_DataSize = SPI_DataSize;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL;		//ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA;	//���ݲ����ڵڶ���ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����(SPI_NSS_Soft,SPI_NSS_Hard)
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler;		//���岨����Ԥ��Ƶ��ֵ
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ(SPI_FirstBit_MSB,SPI_FirstBit_LSB)
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPIx, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPIx, ENABLE); //ʹ��SPI����
	
	//SPI1_SetSpeed(SPI_BaudRatePrescaler_8); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��  
	
	//SPI1_ReadWriteByte(0xff);//��������		 
}

void SPI_setBitOrder(SPI_TypeDef* SPIx,u16 SPI_FirstBit)
{
	SPI_InitTypeDef  SPI_InitStructure;
	SPI_Cmd(SPIx,DISABLE);
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit;
	SPI_Init(SPIx, &SPI_InitStructure);
	SPI_Cmd(SPIx, ENABLE);
}

void SPI_setDataSize(SPI_TypeDef* SPIx,u16 datasize)
{
	SPI_InitTypeDef  SPI_InitStructure;
	SPI_Cmd(SPIx,DISABLE);
	SPI_InitStructure.SPI_FirstBit = datasize;
	SPI_Init(SPIx, &SPI_InitStructure);
	SPI_Cmd(SPIx, ENABLE);
}

void SPI_setDataMode(SPI_TypeDef* SPIx,uint8_t dataMode)
{
	SPI_InitTypeDef  SPI_InitStructure;
	
	u16 SPI_CPOL,SPI_CPHA;
	SPI_Cmd(SPIx,DISABLE);
	
	switch(dataMode)
	{
		case 0:
			SPI_CPOL = SPI_CPOL_Low;
			SPI_CPHA = SPI_CPHA_1Edge;
			break;
		case 1:
			SPI_CPOL = SPI_CPOL_Low;
			SPI_CPHA = SPI_CPHA_2Edge;
			break;
		case 2:
			SPI_CPOL = SPI_CPOL_High;
			SPI_CPHA = SPI_CPHA_1Edge;
			break;
		case 3:
			SPI_CPOL = SPI_CPOL_High;
			SPI_CPHA = SPI_CPHA_2Edge;
			break;
	}
	
	SPI_InitStructure.SPI_CPOL = SPI_CPOL;		//ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA;	//���ݲ����ڵڶ���ʱ����
	SPI_Init(SPIx, &SPI_InitStructure);
	SPI_Cmd(SPIx, ENABLE);
}


//SPI �ٶ����ú���
//SpeedSet:
//SPI_BaudRatePrescaler_2   2��Ƶ   (SPI 36M@sys 72M)
//SPI_BaudRatePrescaler_8   8��Ƶ   (SPI 9M@sys 72M)
//SPI_BaudRatePrescaler_16  16��Ƶ  (SPI 4.5M@sys 72M)
//SPI_BaudRatePrescaler_256 256��Ƶ (SPI 281.25K@sys 72M)

void SPI_setClockDivider(SPI_TypeDef* SPIx,u16 clockDivider)
{
	SPI_InitTypeDef  SPI_InitStructure;
	SPI_Cmd(SPIx,DISABLE);
	SPI_InitStructure.SPI_BaudRatePrescaler = clockDivider;
	SPI_Init(SPIx, &SPI_InitStructure);
	SPI_Cmd(SPIx,ENABLE);
	//SPIx->CR1&=0XFFC7; 
	//SPIx->CR1|=SpeedSet;	//����SPI�ٶ�  
	//SPIx->CR1|=1<<6; 		//SPI�豸ʹ�� 
}

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI_ReadWriteByte(SPI_TypeDef* SPIx,u8 TxData)
{		
	u8 retry=0,data;		
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPIx, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}
		
	data=SPI_I2S_ReceiveData(SPIx); //����ͨ��SPIx������յ�����	
	return data;				    
}































