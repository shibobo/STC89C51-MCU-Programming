#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit int0=P3^4;
sbit led1=P2^0;
sbit led5=P1^5;
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
		led1=0;
		//delayms(1);
		led1=1;
		//delayms(1);
	}
}

void int_out() interrupt 1{
	count++;
	if(count==2){
		led5=~led5;
	}
	
}