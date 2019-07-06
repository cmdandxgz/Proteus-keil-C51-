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
	IT0 = 1;   //下降沿触发
 	EX0 = 0;   //关外部中断
 	EA = 1;    //总中断
	
	P2 &= 0xf8; //选择通道0				
	OE = 0;
	STAR = 0;
	STAR = 1;
	STAR = 0; //开始转化（给100ns高电平）

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
	v = (temp * vcc) / 255;		//转化成电压
	OE = 0;
	//uartWriteOne(temp);		//发送
	delay(100);
	EX0 = 1;
	STAR = 0;
	STAR = 1;
	STAR = 0; //开启新的转化
}
