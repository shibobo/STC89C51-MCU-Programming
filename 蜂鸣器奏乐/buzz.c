#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
//定义蜂鸣器
sbit buzz=P2^3;
sbit led1=P1^0;
sbit led2=P1^1;
//延时函数
void delayms(uint time);

void delayms(uint time){
	uint x,y;
	for(x=time;x>0;x--)
	   for(y=110;y>0;y--);
}
void main(){
	//大循环
	while(1){
		buzz=0;
		delayms(3000);
		buzz=1;
		delayms(3000);
	}
}