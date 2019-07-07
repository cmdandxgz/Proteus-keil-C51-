#include <reg51.h>
#include "uart.h"
#include "display.h"
#include "include.h"

void uartInit() {
	TMOD = 0x20; //方式2
	TH1 = 0xfd;  //9600bps
	TL1 = 0xfd;
//	REN = 1;	//允许串口接收
//	SM0 = 1;	
//	SM1 = 1; //工作方式3 主从 //该方法初始化串口有毒，别用，垃圾软件。用SCON
	SCON = 0xd0; 

	ES = 0;		//串口中断	
	TR1 = 1;	//启动定时器1
	EA = 1;		//总中断

	SBUF = 0x00;
}

void uartWrite(uchar addr, uchar str) {
	TB8 = 1;  // 1发送地址，0发送数据
	SBUF = addr;
    while(!TI);    //判断是否发送成功（发送成功后TI会置1，需手动清0）
    TI = 0;

    TB8 = 0;        //发送数据
	SBUF = str;
    while(!TI);
	TI = 0;     
}

