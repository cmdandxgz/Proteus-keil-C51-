#include <reg51.h>
#include <intrins.h>
#include "uart.h"

#define uchar unsigned char

sbit STAR = P2^3;
sbit OE = P2^4;

uchar vcc = 5;
uchar temp, v;

void delay(uchar m)		//@11.0592MHz  100us
{
	uchar i;

	for(m; m > 0; m--) {
		_nop_();
		i = 43;
		while (--i);
	}
}


void init() {
	IT0 = 1;   //�½��ش���
 	EX0 = 0;   //���ⲿ�ж�
 	EA = 1;    //���ж�
	
	P2 &= 0xf8; //ѡ��ͨ��0				
	OE = 0;
	STAR = 0;
	STAR = 1;
	STAR = 0; //��ʼת������100ns�ߵ�ƽ��

	uartInit();
}


void main() {
	
	init();
	while(1) {
		
	
	}
}


void int0() interrupt 1 {
	EX0 = 0;
	OE = 1;	//�������
	temp = P0; //ȡֵ
	v = (temp * vcc) / 255;		//ת���ɵ�ѹ
	OE = 0;
	//uartWriteOne(temp);		//����
	delay(100);
	EX0 = 1;
	STAR = 0;
	STAR = 1;
	STAR = 0; //�����µ�ת��
}
