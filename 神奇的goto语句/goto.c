#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char	
sbit led0=P1^0;
sbit led2=P1^2;
void delayms(uint time){
	uint x,y;
	for(x=time;x>0;x--)
	  for(y=120;y>0;y--);
}
void main(){
	uint a=5;
	uint b=2;
	if(a>b){
		a=1;
		led0=~led0;
		delayms(1000);
		//goto A;
	}
	if(a==1){
		led2=~led2;
		delayms(1000);
	}
	while(1);
}