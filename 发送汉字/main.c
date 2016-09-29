#include <reg52.h>
#include <stdio.h>
//do not use define,use typedef
//#define uint unsigned int
//#define uchar unsigned char
typedef unsigned int INT16U;
typedef unsigned char INT8U;
void Delay_Ms(INT16U z){
	INT16U x,y;
	for(x=z;x>0;x--){
		for(y=114;y>0;y--);
	}
}
void UART_Init(){
	TMOD=0X20;
	TH1=0xfd;
	TL1=0xfd;  //9600bps
	TR1=1;     //start timer1
	SM0=0;
	SM1=1;     //work on mode 1
}
//main
void main(){
	UART_Init();
	while(1){
		TI=1;
		puts("你好，欢迎来到单片机世界\n");
		while(!TI);
		TI=0;
		Delay_Ms(1000);
	}
  
}