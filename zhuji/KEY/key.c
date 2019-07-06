#include <reg51.h>
#include "display.h"
#include "key.h"
#include "uart.h"

unsigned char star = 0;

sbit key = P3^2;
void keyInit() {
	IT0 = 1;   //�½��ش���
 	EX0 = 1;   //���ⲿ�ж�
 	EA = 1;    //���ж�
}

void keyInt() interrupt 0 {
	EX0 = 0;
	keyScand();
	EX0 = 1;
}

void keyScand() {
	if(key == 0) {
		delay(10); //1ms
		while(key == 0){;}
		if(star == 0) {	//��ʼ
			ES = 1;
			star = 1;
			uartWrite(20, 1);
			uartWrite(30, 1);
		} else {
			ES = 0;
			star = 0;	//ֹͣ
			uartWrite(20, 0);
			uartWrite(30, 0);
			displayClear();
		}
	}
}
