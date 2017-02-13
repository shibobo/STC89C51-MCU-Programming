#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
uint temp,qian,bai,shi,ge,aa,n;
sbit dula=P2^6;
sbit wela=P2^7;
sbit outint=P3^2;//外部中断从这里引入
uchar code table[]={ 
                0x3F,  //"0"
                0x06,  //"1"
                0x5B,  //"2"
                0x4F,  //"3"
                0x66,  //"4"
                0x6D,  //"5"
                0x7D,  //"6"
                0x07,  //"7"
                0x7F,  //"8"
                0x6F  //"9"
};
void delayms(uint time){
	uint x,y;
	for(x=time;x>0;x--)
	  for(y=110;y>0;y--);
}
void display(uint qian,uint bai,uint shi,uint ge){
	dula=1;
	P0=table[qian];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfe;
	wela=0;
	delayms(5);
	
	dula=1;
	P0=table[bai];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfd;
	wela=0;
	delayms(5);
	
	dula=1;
	P0=table[shi];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfb;
	wela=0;
	delayms(5);
	
	dula=1;
	P0=table[ge];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xf7;
	wela=0;
	delayms(5);
}
void init(){
	dula=0;
	wela=0;
	temp=0;
	TMOD=0x01;//定时器0工作模式1
	TCON|=0x03;
	TH0=(65536-50000)/256;
	TL0=(65536-80000)%256;
	EA=1;
	ET0=1;
	TR0=1;
}
void main(){
	EA=1;
	EX0=1;
	init();
	while(1){
		display(qian,bai,shi,ge);
		//display(1,2,5,6);
	}
}
void out1() interrupt 0{
	n++;//高电平的个数
	while(outint==0);
}
void timer0() interrupt 1{
	TH0=(65536-50000)/256;
	TL0=(65536-80000)%256;
	aa++;
	if(aa==20){
		aa=0;
		temp=5*n;
		n=0;
		qian=temp/1000;
		bai=temp%1000/100;
		shi=temp%100/10;
		ge=temp%10;
	}
}