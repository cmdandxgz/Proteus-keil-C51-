#include <reg51.h>
#include "display.h"
#include "uart.h"
#include "key.h"
#include "dac.h"
#include "include.h"


uchar readSbuf;
uchar readData;
uchar addr = CONG1;
int time = 0;
void time0Init() {
	TMOD |= 0x01;
	TH0 = 0xFC;	//1ms
	TL0 = 0x18;
	ET0 = 1;
	TR0 = 0;
	EA = 1;
}

void init() {
	time0Init();
	uartInit();
	keyInit();
	dacInit();
}

void main() {
	init();
	displayClear();
	while(1) {		
		delay(1000);
		outDac(readData/2);
	}
}

void uartRead() interrupt 4 {
	TR0 = 0;
	
	ES = 0;
	if(RI) {
		readSbuf = SBUF;
		readData = readSbuf;
		//v = (readData*VCC)/255;
		if(addr == CONG1) {
			displayAll(20, readSbuf);
		} else if(addr == CONG2) {
			displayAll(30, readSbuf);
		}
	}
	RI = 0;
	ES = 1;
	
	TR0 = 1;
}

void time0() interrupt 1 {
	ES = 0;

	TR0 = 0;
	TH0 = 0x0FC;	//1ms
	TL0 = 0x18;
	if(star == 1) {
		time++;
		if(time > 2000) {
			time = 0;
			if(addr == CONG1) {
				addr = CONG2;
			} else {
				addr = CONG1;
			}
		}
		if(time%30 == 0) {
		//	displayAll(addr,CMD);
			uartWrite(addr, CMD);
		}
	}	
	TR0 = 1;

	ES = 1;
}
