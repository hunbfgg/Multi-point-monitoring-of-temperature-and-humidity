#include ".\\nRF24L01\\nRF24L01.h"
#include "def.h"
#include "dht11.h"

#define uchar unsigned char
#define uint unsigned int
char read_data();
void delay(uchar z);

unsigned char tem,hmi;
unsigned char tem_1,hmi_1;

void Delay1(unsigned int s)
{
	unsigned int i;
	for(i=0; i<s; i++);
	for(i=0; i<s; i++);
}

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
 int a=0;
	uchar TxBuf[20]={0};	 // 

  init_io() ;
	UsartInit();

	nRF24L01_TxPacket(TxBuf);	// Transmit Tx buffer data
	Delay1(6000);
	
	while(1)
	{	
			
		DHT11_receive(&tem,&hmi);
		DHT11_receive_1(&tem_1,&hmi_1);
		PutString("OK\r\n");
	
		TxBuf[0]='#';	
		TxBuf[1]=tem/10+1-1;
		TxBuf[2]=tem%10+1-1;
		TxBuf[3]=hmi/10+1-1;
		TxBuf[4]=hmi%10+1-1;
		
		
		
		TxBuf[5]=tem_1/10+1-1;
		TxBuf[6]=tem_1%10+1-1;
		TxBuf[7]=hmi_1/10+1-1;
		TxBuf[8]=hmi_1%10+1-1;
		
			
		nRF24L01_TxPacket(TxBuf);	// Transmit Tx buffer data
		PutString(TxBuf);
		PutString("\r\n");
		PutString("I send\r\n");
		DHT11_delay_ms(1000);
//			SetRX_Mode();
//			
//   		if(nRF24L01_RxPacket(RxBuf))
//			{
//						
//			if(	RxBuf[1]==1)
//			{	 	
//				LED1 = 0;
//			}
//			if(	RxBuf[2]==1)
//			{
//				LED2 = 0;
//			}
//		}

		} 

	}
		
