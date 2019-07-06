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
	IT0 = 1;   //下降沿触发
 	EX0 = 1;   //开外部中断
 	EA = 1;    //总中断
	
	a = 0;
	b = 0;
	c = 0; //选输入通道0					
	OE = 0;
	STAR = 0;
	STAR = 1;
	STAR = 0; //开始转化（给100ns高电平）
	
}


void main() {
	
	init();
	while(1) {
	}
}


void int0() interrupt 1 {
	OE = 1;	//允许输出
	temp = P0; //取值
	v = (temp * vcc) / 255; //转化成电压
	OE = 0;

	STAR = 0;
	STAR = 1;
	STAR = 0; //开启新的转化
}
