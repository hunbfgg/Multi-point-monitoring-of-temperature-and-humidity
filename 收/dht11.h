#ifndef __DHT11_H_
#define __DHT11_H_
#include <reg52.h>

#define uchar unsigned char
#define uint  unsigned int
sbit  Data  = P1^0 ;
void DHT11_delay_us(uchar n);
void DHT11_delay_ms(uint z);
void DHT11_start();
uchar DHT11_rec_byte();      //����һ���ֽ�


void DHT11_receive(uchar *temp,uchar *humi) ;     //����40λ������

#endif


