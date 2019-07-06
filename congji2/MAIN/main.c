#include <reg51.h>
#include<intrins.h>


#define uchar unsigned char

sbit a = P2^0;
sbit b = P2^1;
sbit c = P2^2;
sbit STAR = P2^3;
sbit OE = P2^4;

uchar vcc = 5;
uchar temp, v;

void init() {
	IT0 = 1;   //�½��ش���
 	EX0 = 1;   //���ⲿ�ж�
 	EA = 1;    //���ж�
	
	a = 0;
	b = 0;
	c = 0; //ѡ����ͨ��0					
	OE = 0;
	STAR = 0;
	STAR = 1;
	STAR = 0; //��ʼת������100ns�ߵ�ƽ��
	
}


void main() {
	
	init();
	while(1) {
	}
}


void int0() interrupt 1 {
	OE = 1;	//�������
	temp = P0; //ȡֵ
	v = (temp * vcc) / 255; //ת���ɵ�ѹ
	OE = 0;

	STAR = 0;
	STAR = 1;
	STAR = 0; //�����µ�ת��
}
