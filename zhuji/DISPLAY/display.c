#include "display.h"
#include "include.h"
#include <reg51.h>
#include <intrins.h>


sbit dula=P2^6;		//段选
sbit wela=P2^7;		//位选

uchar code weiTable[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x00};		//数码管各位的码表
uchar code duanTable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff};	//共阳极

void delay(uchar m)		//@11.0592MHz  100us
{
	uchar i;

	for(m; m > 0; m--) {
		_nop_();
		i = 43;
		while (--i);
	}
}

void displayOne(int wei, int num) {
	P0 = weiTable[wei];			//先位选在段选，，不然会出错！！！！！！
	wela = 1;
	wela = 0;

	P0 = duanTable[num];
	dula = 1;
	dula = 0;
	


	
}

void displayAll(int congji, uchar num) {	
	int x = 8;
	displayOne(0, congji/10);		// 显示从机号
	delay(x);
	displayOne(1, congji%10);
	delay(x);
	
	displayOne(5, num/100);		//显示采集数据
	delay(x);
	displayOne(6, (num%100)/10);
	delay(x);
	displayOne(7, num%10);
	delay(x);

	displayClear();
}

void displayClear() {
	uchar i;
	for(i = 0; i < 8; i++) {
		displayOne(i, 10);
	}
	P0 = weiTable[8];			
	wela = 1;
	wela = 0;
}
