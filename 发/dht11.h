#ifndef __DHT11_H_
#define __DHT11_H_
#include <reg52.h>

#define uchar unsigned char
#define uint  unsigned int
sbit  Data  = P1^0 ;
sbit  Data_1= P1^1;

void DHT11_delay_us(uchar n);
void DHT11_delay_ms(uint z);
void DHT11_start();
uchar DHT11_rec_byte();      //接收一个字节



void DHT11_receive(uchar *temp,uchar *humi) ;     //接收40位的数据
void DHT11_receive_1(uchar *temp,uchar *humi)  ;

#endif


