#include "uart.h"
#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define ADDR 0x30
#define CMD 0x01

sbit STAR = P2^3;
uchar readSbuf, readData;
uchar readStar = 0;

void uartInit() {
	TMOD = 0x20; //��ʽ2
	TH1 = 0xfd;  //9600bps
	TL1 = 0xfd; 
//	REN = 1;	//�����ڽ���
//	SM0 = 1;	
//	SM1 = 1; //������ʽ3 ����
//	SM2 = 0;  //ֻ���ܵ�ַ������TB8=1��ʱ��ֻ��ӻ����ã� //�÷�����ʼ�������ж������ã������������SCON
	SCON = 0xf0;

	ES = 1;		//�����ж�	
	TR1 = 1;	//������ʱ��1
	EA = 1;		//���ж�
}

void uartWriteOne(uchar str) {
   		SBUF = str;
    	while(!TI);
		TI = 0;     	
}

void uartRead() interrupt 4 {	
	ES = 0;
	if(RI) {
		readSbuf = SBUF;
		if(readStar) {
			readData = readSbuf;
			if(readData == CMD) {//�ɼ�һ��
				STAR = 0;
				STAR = 1;
				STAR = 0;
			}
			readStar = 0;	//���ν���
			SM2 = 0;	//���ܵ�ַ
		}
	}
	if(readSbuf == ADDR) {
		readStar = 1;  //��ʼ��������
		SM2 = 0;  //��������ģʽ
	}

	RI = 0;
	ES = 1;
}
