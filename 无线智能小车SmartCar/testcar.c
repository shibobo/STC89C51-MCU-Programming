#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
/**
*port define
*/
//left motor
sbit int1=P1^0;
sbit int2=P1^1;
//right motor
sbit int3=P1^2;
sbit int4=P1^3;
//lcd1602 display
sbit lcden=P3^4;//EN
sbit lcdrs=P3^5;//RS
sbit lcdrw=P3^6;//RW
/**
*function lists
*/
void delayms(uint time);
void USModule_start();
void display(uchar dis);
void calculate_distance();
void USModule_init();
void timer0_init();
void lcd_init();
void write_com(uchar com);
void write_data(uchar dat);
void lcd_show();
void Motors_Handler();
void USMOdule_Handler();
//uart generator
void ConfigUART(uint baud);
//motor status
void left_motor_go();
void left_motor_back();
void left_motor_stop();

void right_motor_go(); 
void right_motor_back();
void right_motor_stop(); 
void timer2_start();
void display1602(uint bai0,uint shi0,uint ge0,uint bai1,uint shi1,uint ge1);
/**
*variable lists
*/
uchar a,b;
uint successful;//超声波模块高电平输出成功
uint US_OK;//可以进行超声波测距
uint count;//定时器溢出的次数
uint count1;//定时器1溢出的次数
uint time;//echo输出的高电平持续的时间
ulong distance;//超声波模块距离
uint bai,shi,ge;
uchar code table[]="0123456789";
uchar code tips[]="DISTANCE:";
//电机速度
uint temp0,bai0,shi0,ge0,n0,count;
uint temp1,bai1,shi1,ge1,n1;
sbit outint0=P3^2;//outside interrupt 0
sbit outint1=P3^3;//outside interrupt 1
sbit leden=P3^4;//1602 EN
sbit ledrs=P3^5;//1602 RS
sbit ledrw=P3^6;//1602 RW

//delayms
void delayms(uint time){
	uint x,y;
	for(x=time;x>0;x--)
	   for(y=114;y>0;y--);
}
//lcd1602初始化
void lcd_init(){
	lcden=0;
	lcdrw=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	
	write_com(0x80);
	write_data('R');
	write_data(':');
	write_data(table[0]);
	write_data(table[0]);
	write_data(table[0]);
	
	write_com(0x80+0x06);
	write_data('L');
	write_data(':');
	write_data(table[0]);
	write_data(table[0]);
	write_data(table[0]);
	
	write_com(0x80+0x40);
	write_data('D');
	write_data('I');
	write_data('S');
	write_data(':');
	write_data(table[0]);
	write_data(table[0]);
	write_data(' ');
	write_data('c');
	write_data('m');
	write_data(':');
	write_data(')');
}
//1602写命令
void write_com(uchar com){
	lcdrs=0;
	//ledrw=0;
	P2=com;
	delayms(5);
	lcden=1;
	delayms(5);
	lcden=0;
}
//1602写数据
void write_data(uchar dat){
	lcdrs=1;
	//ledrw=0;
	P2=dat;
	delayms(5);
	lcden=1;
	delayms(5);
	lcden=0;
}
//左轮前进
void left_motor_go(){
	int1=1;
	int2=0;
}
//左轮后退
void left_motor_back(){
	int1=0;
	int2=1;
}
//左轮停止
void left_motor_stop(){
	int1=0;
	int2=0;
}
//右轮前进
void right_motor_go(){
	int3=1;
	int4=0;
}
//右轮后退
void right_motor_back(){
	int3=0;
	int4=1;
}
//右轮停止
void right_motor_stop(){
	int3=0;
	int4=0;
}
//lcd1602显示转速
void display1602(uint bai0,uint shi0,uint ge0,uint bai1,uint shi1,uint ge1){
  write_com(0x80);
	write_data('R');
	write_data(':');
	write_data(' ');
	write_data(table[bai0]);
	write_data(table[shi0]);
	write_data(table[ge0]);
	
	write_com(0x80+0x06);
	write_data('L');
	write_data(':');
	write_data(' ');
	write_data(table[bai1]);
	write_data(table[shi1]);
	write_data(table[ge1]);
	
	write_com(0x80+0x40);
	write_data('D');
	write_data('I');
	write_data('S');
	write_data(':');
	write_data(table[0]);
	write_data(table[0]);
	write_data(' ');
	write_data('c');
	write_data('m');
	write_data(':');
	write_data(')');
}
void main(){
	TMOD=0x01;
	//IT0=1;
	//IT1=1;
	//EX1=1;
	//EX0=1;
	lcd_init();
	//TH0=(65536-50000)/256;
	//TL0=(65536-80000)%256;
	//EA=1;
	//ET0=1;
	//TR0=1;
	while(1){
		//display1602(bai0,shi0,ge0,bai1,shi1,ge1);
//		left_motor_go();
//		right_motor_go();
		//write_com(0x80);
		//write_data(table[bai0]);
		//write_data(table[shi0]);
		//write_data(table[ge0]);
	}
}
//外部中断0
void out0() interrupt 0{
	n0++;//高电平的个数
	//while(outint0==0);
}
//外部中断1
void out1() interrupt 2{
	n1++;
	//while(outint1==0);
}
void timer0() interrupt 1{
	TH0=(65536-50000)/256;
	TL0=(65536-80000)%256;
	count++;//1s
	if(count==20){
		count=0;
		//temp0=5*n0;
		temp0=125;
		//n0=0;
		bai0=temp0/100;
		shi0=temp0%100/10;
		ge0=temp0%10;
		
		//temp1=5*n1;
		temp1=256;
		//n1=0;
		bai1=temp1/100;
		shi1=temp1%100/10;
		ge1=temp1%10;
	}
}