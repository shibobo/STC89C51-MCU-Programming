#include <reg52.h>
//#include <intrins.h>
#include <stdlib.h>
#define uint unsigned int
#define uchar unsigned char
uchar code table[]="iloveyou";
uchar code table1[]="ilovemcu";
sbit leden=P3^4;//EN
sbit ledrs=P3^5;//RS
sbit ledrw=P3^6;//RW
sbit dula=P2^6;
sbit wela=P2^7;
uchar num;
uchar code a[]="cccd";
void delay(uint z){
	uint x,y;
	for(x=z;x>0;x--)
		for(y=114;y>0;y--);
}
void write_com(uchar com){
	ledrs=0;
	//ledrw=0;
	P2=com;
	P0=com;
	delay(5);
	leden=1;
	delay(5);
	leden=0;
}
void write_data(uchar date){
	ledrs=1;
	//ledrw=0;
	P2=date;
	P0=date;
	delay(5);
	leden=1;
	delay(5);
	leden=0;
}
//show a random number
void init(){
	//dula=0;
	//wela=0;
	leden=0;
	ledrw=0;
	P2=0x00;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}
//main
void main(){
	init();
	write_com(0x80+0x10);
	for(num=0;num<8;num++){
		write_data(table[num]);
		delay(5);
	}
	//change address
	write_com(0x80+0x50);
	for(num=0;num<8;num++){
		write_data(table1[num]);
		delay(5);
	}
	for(num=0;num<8;num++){
		write_com(0x18);
		delay(2000);
	}
	while(1);
}