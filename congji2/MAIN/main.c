#include <reg51.h>
#include "uart.h"

#define uchar unsigned char

sbit STAR = P2^3;
sbit OE = P2^4;

uchar vcc = 5;
char temp, v;

void init() {
	IT0 = 1;   //下降沿触发
 	EX0 = 1;   //关外部中断
 	EA = 1;    //总中断

	P2 &= 0xf8; //选择通道0				
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

	OE = 1;	//允许输出
	temp = P0; //取值
	OE = 0;
	uartWriteOne(temp);		//发送
	EX0 = 1;
}
