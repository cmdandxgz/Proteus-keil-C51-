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
	TMOD = 0x20; //方式2
	TH1 = 0xfd;  //9600bps
	TL1 = 0xfd; 
//	REN = 1;	//允许串口接收
//	SM0 = 1;	
//	SM1 = 1; //工作方式3 主从
//	SM2 = 0;  //只接受地址（主机TB8=1的时候。只需从机设置） //该方法初始化串口有毒，别用，垃圾软件。用SCON
	SCON = 0xf0;

	ES = 1;		//串口中断	
	TR1 = 1;	//启动定时器1
	EA = 1;		//总中断
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
			if(readData == CMD) {//采集一次
				STAR = 0;
				STAR = 1;
				STAR = 0;
			}
			readStar = 0;	//本次结束
			SM2 = 0;	//接受地址
		}
	}
	if(readSbuf == ADDR) {
		readStar = 1;  //开始接受数据
		SM2 = 0;  //接受数据模式
	}

	RI = 0;
	ES = 1;
}
