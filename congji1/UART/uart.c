#include "uart.h"
#include <reg51.h>

#define uchar unsigned char

sbit STAR = P2^3;
uchar readSbuf, readData;
uchar readStar = 0;

void uartInit() {
	TMOD = 0x20; //方式2
	TH1 = 0xfd;  //9600bps
	TL1 = 0xfd; 
	REN = 1;	//允许串口接收
	SM0 = 1;	
	SM1 = 1; //工作方式3 主从
	SM2 = 1;  //只接受地址（主机TB8=1的时候。只需从机设置）

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
			if(readData == 1) {//开始
				EX0 = 1;
				STAR = 0;
				STAR = 1;
				STAR = 0;
			} else if(readData == 0) {//结束
				EX0 = 0;
				STAR = 0;
			}
			readStar = 0;	//本次结束
			SM2 = 1;	//接受地址
		}
	}
	if(readSbuf == 20) {
		readStar = 1;  //开始接受数据
		SM2 = 0;  //接受数据模式
	}
	RI = 0;
	ES = 1;
}
