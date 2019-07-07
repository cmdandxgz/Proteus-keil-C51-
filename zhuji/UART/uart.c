#include <reg51.h>
#include "uart.h"
#include "display.h"
#include "include.h"

void uartInit() {
	TMOD = 0x20; //��ʽ2
	TH1 = 0xfd;  //9600bps
	TL1 = 0xfd;
//	REN = 1;	//�����ڽ���
//	SM0 = 1;	
//	SM1 = 1; //������ʽ3 ���� //�÷�����ʼ�������ж������ã������������SCON
	SCON = 0xd0; 

	ES = 0;		//�����ж�	
	TR1 = 1;	//������ʱ��1
	EA = 1;		//���ж�

	SBUF = 0x00;
}

void uartWrite(uchar addr, uchar str) {
	TB8 = 1;  // 1���͵�ַ��0��������
	SBUF = addr;
    while(!TI);    //�ж��Ƿ��ͳɹ������ͳɹ���TI����1�����ֶ���0��
    TI = 0;

    TB8 = 0;        //��������
	SBUF = str;
    while(!TI);
	TI = 0;     
}

