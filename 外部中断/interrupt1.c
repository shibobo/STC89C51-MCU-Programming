#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit int0=P3^4;
sbit btn1=P3^0;
sbit led0=P1^0;
sbit feng=P2^3;
uchar count;
void delayms(uint time){
	uint x,y;
	for(x=time;x>0;x--)
	  for(y=110;y>0;y--);
}
void main(){
	TMOD=0x05;
	TR0=1;
	EA=1;
	ET0=1;
	while(1){
		int0=btn1;
		if(TL0==5){
			feng=0;
		}
	}
}