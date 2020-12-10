#include "nRF24L01.h"
#include "def.h"
#include "lcd.h"
#include "dht11.h"

#define uchar unsigned char
#define uint unsigned int

unsigned char tem,hmi;


char read_data();
void delay(uchar z);

void delayms(uint x)
{
	uchar i,j;
	for(i=x;i>0;i--)
		for(j=110;j>0;j--);
}
void delay(uchar z)
{
	uint x,y;
	for(x=z;x>0;x--)
	 for(y=110;y>0;y--);
}
void delay_10us()
{
	uchar i;
	i--;i--;i--;i--;i--;i--;
}

void UsartInit()
{
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=0XFA;				//计数器初始值设置，注意波特率是4800的
	TL1=0XFA;
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;					//打开计数器
}


void Usart() interrupt 4
{
	unsigned char receiveData;

	receiveData=SBUF;//出去接收到的数据
	RI = 0;//清除接收中断标志位
	SBUF=receiveData;//将接收到的数据放入到发送寄存器
	while(!TI);			 //等待发送数据完成
	TI=0;						 //清除发送完成标志位
}


void PutString(unsigned char *TXStr) 
{ 
	ES=0; 
	while(*TXStr!=0) 
	{ 
		SBUF=*TXStr;
		while(TI==0);
		TI=0; 
		TXStr++;
	}
	ES=1; 
}



void main()
{
	uchar RxBuf[20]={0};
//	init();	
	init_io() ;
	UsartInit();
	LcdInit();
	
	LcdWriteCom(0x80);
	LcdWriteData('H');
	LcdWriteData('1');
	LcdWriteData(':');
	
	LcdWriteCom(0x80+9);
	LcdWriteData('H');
	LcdWriteData('2');
	LcdWriteData(':');
	
	LcdWriteCom(0x80+0x40+4);
	LcdWriteData('H');
	LcdWriteData('3');
	LcdWriteData(':');
	
	
	
	while(1)
	{	
		DHT11_receive(&tem,&hmi);
		LcdWriteCom(0x80+3);
		LcdWriteData(tem/10+'0');
		LcdWriteData(tem%10+'0');
		LcdWriteData(' ');
		LcdWriteData(hmi/10+'0');
		LcdWriteData(hmi%10+'0');
		
		
		
		SetRX_Mode();	
		
		PutString("no receive!\r\n");
		if(nRF24L01_RxPacket(RxBuf))
		{	
			LcdWriteCom(0x80+12);
			LcdWriteData(RxBuf[1]+'0');
			LcdWriteData(RxBuf[2]+'0');
			LcdWriteData(' ');
			LcdWriteCom(0x80+0x40);
			LcdWriteData(RxBuf[3]+'0');
			LcdWriteData(RxBuf[4]+'0');
			
			LcdWriteCom(0x80+0x40+7);
			LcdWriteData(RxBuf[5]+'0');
			LcdWriteData(RxBuf[6]+'0');
			LcdWriteData(' ');
			LcdWriteData(RxBuf[7]+'0');
			LcdWriteData(RxBuf[8]+'0');
			
			PutString("I receive\r\n");
			PutString(RxBuf);
			PutString("\r\n");
		} 
	
	}
}
	
			
