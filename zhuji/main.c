#include <reg51.h>
#include "display.h"
#include "uart.h"
#include "key.h"

#define uchar unsigned char
uchar addr = 20;
uchar readSbuf,readData;
void init() {
	uartInit();
	keyInit();
}

void main() {
	init();
	displayClear();
	while(1) {		
		//displayAll(20, readData);
	}
}

void uartRead() interrupt 4 {
	ES = 0;
	if(RI) {
		readSbuf = SBUF;
		readData = readSbuf;
		displayAll(addr, readData);
	}
	RI = 0;
	ES = 1;
}


