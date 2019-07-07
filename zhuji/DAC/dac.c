#include <reg51.h>
#include "dac.h"

sbit LE = P2^3;
sbit CS = P2^2;


void dacInit(){
	outLock(0xf0);
}

void outLock(uchar out) {
	LE = 1;
	P1 = out;
	LE = 0;
}

void outDac(uchar out) {
	outLock(out);
	CS = 0;
}
