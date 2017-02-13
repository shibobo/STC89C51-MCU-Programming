#include "myreg52.h"
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar count,count1;
sbit led4=P1^4;
sbit led5=P1^5;
//Ö÷³ÌÐò
void main(){
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1){
		if(count==50){
			count=0;
			led4=~led4;
		}
		if(count1==50){
			count1=0;
			led5=~led5;
		}
	}
	
}
void timer0() interrupt 1{
	//TF2=0;
	TH0=(65536-10)/256;
	TL0=(65536-10)%256;
	count++;
	count1++;
}