#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
uint temp0,bai0,shi0,ge0,aa0,n0;
uint temp1,bai1,shi1,ge1,aa1,n1;
sbit outint0=P3^2;//外部中断从这里引
sbit outint1=P3^3;//外部中断从这里引
sbit leden=P3^4;//EN
sbit ledrs=P3^5;//RS
sbit ledrw=P3^6;//RW
//sbit dula=P2^6;
//sbit wela=P2^7;
uchar code table[]="0123456789";
uchar code table1[]={ 
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
void write_com(uchar com){
	ledrs=0;
	//ledrw=0;
	P2=com;
	delayms(5);
	leden=1;
	delayms(5);
	leden=0;
}
void write_data(uchar date){
	ledrs=1;
	//ledrw=0;
	P2=date;
	delayms(5);
	leden=1;
	delayms(5);
	leden=0;
}
void init(){
	//dula=0;
	//wela=0;
	temp0=0;
	temp1=0;
	bai0=0;
	shi0=0;
	ge0=0;
	bai1=0;
	shi1=0;
	ge1=0;
	TMOD=0x01;//定时器0工作模式1
	TCON|=0x0F;
	TH0=(65536-50000)/256;
	TL0=(65536-80000)%256;
	ET0=1;
	TR0=1;
	EA=1;
}
void display1602(uint bai0,uint shi0,uint ge0,uint bai1,uint shi1,uint ge1){
	write_com(0x80);
	write_data('R');
	write_data(':');
	write_data(table[bai0]);
  //delayms(5);
	write_data(table[shi0]);
	//delayms(5);
	write_data(table[ge0]);
	//delayms(5);
	write_com(0x80+0x06);
	write_data('L');
	write_data(':');
	//delayms(5);
	write_data(table[bai1]);
  //delayms(5);
	write_data(table[shi1]);
	//delayms(5);
	write_data(table[ge1]);
	//delayms(5);
}
void init1602(){
	leden=0;
	ledrw=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}
void main(){
	EA=1;
	EX0=1;
	EX1=1;
	init1602();
	init();
	while(1){
		display1602(bai0,shi0,ge0,bai1,shi1,ge1);
		//display1602(1,2,3,4,5,6);
		//write_com(0x80);
		//write_data(table[2]);
	}
}
void out0() interrupt 0{
	n0++;//高电平的个数
	while(outint0==0);
}
void out1() interrupt 2{
	n1++;
	while(outint1==0);
}
void timer0() interrupt 1{
	TH0=(65536-50000)/256;
	TL0=(65536-80000)%256;
	aa0++;
	aa1++;
	if(aa0==10){
		aa0=0;
		temp0=5*n0;
		n0=0;
		bai0=temp0/100;
		shi0=temp0%100/10;
		ge0=temp0%10;
	}
	if(aa1==10){
		aa1=0;
		temp1=5*n1;
		n1=0;
		bai1=temp1/100;
		shi1=temp1%100/10;
		ge1=temp1%10;
	}
}