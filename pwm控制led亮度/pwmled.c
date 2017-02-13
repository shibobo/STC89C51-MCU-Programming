/**
*产生1000Hz,周期为1ms的pwm波
*/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit pwm_up=P3^0;
sbit pwm_down=P3^1;

sbit dula=P2^6;
sbit wela=P2^7;

//sbit led1=P1^0;
//sbit led_show=P1^1;

sbit pwm1=P1^0;
sbit pwm2=P1^1;
sbit pwm3=P1^2;
uint count=0;
uint count1=0;
uint pwm_rate=0;

void delayms(uint z)
{
  uint x,y;
  for(x=z;x>0;x--)
     for(y=120;y>0;y--);
}
void main(){
	TMOD=0x01;
	TH0=(65536-10)/256;
	TL0=(65536-10)%256;
	TR0=1;
	ET0=1;
	EA=1;
	P1=0xff;
	pwm_rate=50;
	while(1){
		if(!pwm_up){
			if(pwm_rate<100){
				pwm_rate+=10;
			}
			if(pwm_rate==100){
				pwm_rate=0;
			}
			delayms(5);
		}
		if(!pwm_down){
			if(pwm_rate>0){
				pwm_rate-=10;
			}
			if(pwm_rate==0){
				pwm_rate=90;
			}
			delayms(5);
		}
	}
}
void timer0() interrupt 1{
	TH0=(65536-10)/256;
	TL0=(65536-10)%256;
	count++;//0.01ms溢出一次
	count1++;
	if(count<=pwm_rate){//10%占空比
		pwm1=1;
	}else{
		pwm1=0;
	}
	if(count>=100){
		count=0;
	}
	
	if(count1<=80){//80%占空比
		pwm3=1;
	}else{
		pwm3=0;
	}
	if(count1>=100){
		count1=0;
	}
	pwm2=0;
}