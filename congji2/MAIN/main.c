#include <reg51.h>
#include "uart.h"

#define uchar unsigned char

sbit STAR = P2^3;
sbit OE = P2^4;

uchar vcc = 5;
char temp, v;

void init() {
	IT0 = 1;   //�½��ش���
 	EX0 = 1;   //���ⲿ�ж�
 	EA = 1;    //���ж�

	P2 &= 0xf8; //ѡ��ͨ��0				
	OE = 0;
	STAR = 0;

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
	OE = 0;
	uartWriteOne(temp);		//����
	EX0 = 1;
}
