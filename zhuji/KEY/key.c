#include <reg51.h>
#include "display.h"
#include "key.h"
#include "uart.h"
#include "include.h"
uchar star;
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
		delay(1); //0.1ms
		if(star == 0) {	//��ʼ
			star = 1;
			TR0 = 1;
		} else {
			star = 0;	//ֹͣ
			readData = 0;
			TR0 = 0;
			time = 0;
			displayClear();
		}
		while(key != 0){;}
	}
}
