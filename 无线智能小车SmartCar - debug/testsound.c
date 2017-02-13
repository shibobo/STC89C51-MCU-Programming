#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
#define kp 1
#define ki 0.5
#define kd 0
sfr T2MOD=0xc9;
/**
*port define
*/
//P1^6=ENA,P1^7=ENB
sbit left_motor_pwm_port=P1^6;
sbit right_motor_pwm_port=P1^7;
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
//feng
sbit feng=P1^4;
//sbit feng=P2^3;
sbit light1=P1^0;
sbit light2=P1^1;
//ultrasound
sbit trig=P0^4;
sbit echo=P0^5;
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
uchar left_pwm_value,right_pwm_value;
uchar push_left_pwm_value,push_right_pwm_value;

uchar a,b;
uint count;//定时器溢出的次数
uint count1;//定时器1溢出的次数
uint time;//echo输出的高电平持续的时间
ulong distance;//超声波模块距离
uint bai,shi,ge;
uchar code table[]="0123456789-";
uchar code tips[]="DISTANCE:";
//电机速度
uint temp0,bai0,shi0,ge0,n0,count;
uint temp1,bai1,shi1,ge1,n1;
sbit outint0=P3^2;//outside interrupt 0
sbit outint1=P3^3;//outside interrupt 1
sbit leden=P3^4;//1602 EN
sbit ledrs=P3^5;//1602 RS
sbit ledrw=P3^6;//1602 RW
uint flag_rec,data_rec,flag_v;
uint count_dis;
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
	P2=0x00;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	
	write_com(0x80);
	write_data('R');
	write_data(':');
	write_data(table[10]);
	write_data(table[10]);
	write_data(table[10]);
	
	write_com(0x80+0x06);
	write_data('L');
	write_data(':');
	write_data(table[10]);
	write_data(table[10]);
	write_data(table[10]);
	
	write_com(0x80+0x40);
	write_data('D');
	write_data('I');
	write_data('S');
	write_data(':');
	write_data(table[10]);
	write_data(table[10]);
	write_data(table[10]);
	write_data('c');
	write_data('m');
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
/*void display1602(uint bai0,uint shi0,uint ge0,uint bai1,uint shi1,uint ge1){
  P2=0x00;
	write_com(0x82);
	write_data(table[bai0]);
	write_data(table[shi0]);
	write_data(table[ge0]);
	
	write_com(0x80+0x08);
	write_data(table[bai1]);
	write_data(table[shi1]);
	write_data(table[ge1]);
	
	write_com(0x80+0x44);
	write_data(table[10]);
	write_data(table[10]);
	write_data(table[10]);
}*/
/*void timer0_start(){
	TMOD=0x21;//timer0 count to speed, timer1 to UART
	TH0=(65536-50000)/256;//50ms
	TL0=(65536-50000)%256;//50ms
	EA=1;
	ET0=1;
	TR0=1;
}*/
void timer0_start(){
	TMOD=0x21;//timer0 count to speed, timer1 to UART
	TH0=0;
	TL0=0;
	EA=1;
	ET0=1;
	//TR0=1;
}
void measureDistance_init(){
	trig=0;
	echo=0;
}
void measureDistance_start(){
	trig=1;
  _nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
  _nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
	trig=0;
}
void measureDistance_cal(){
	//measure the distance
	//while(!echo);
	//TR0=1;
	//while(echo);
	//TR0=0;
	//while(!echo);
	//TR0=1;
	//while(echo);
	//TR0=0;
	time=TH0*256+TL0+65536*count_dis;
	//time=2000;
	TH0=0;
	TL0=0;
	distance=(time*1.7)/100;
	if(distance>=200){
		distance=0;
	}else{
		if(distance<=20){
			feng=0;
      left_motor_go();
      right_motor_stop();
			delayms(5000);
			left_motor_go();
			right_motor_go();
			delayms(5000);
      feng=1;			
		}
		bai=distance/100;
		shi=distance%100/10;
		ge=distance%100%10;
		write_com(0x80+0x44);
		write_data(table[bai]);
		write_data(table[shi]);
		write_data(table[ge]);
		delayms(10);
	}
		/*if(distance<=20){
			 feng=0;
       left_motor_stop();
       right_motor_stop();
			 delayms(2000);//wait
       left_motor_go();
       right_motor_stop();
			 delayms(2000);
			 left_motor_go();
			 right_motor_go();
       feng=1;			
		}*/
}
void main(){
	//timer0_start();//measure speed
	lcd_init();
	left_motor_go();
	right_motor_go();
	//measureDistance_init();
	while(1){		
		//debug
		//measureDistance_start();
		//measureDistance_cal();
	}
}
void timer0() interrupt 1{
	TH0=0;
	TL0=0;
	count_dis++;
}