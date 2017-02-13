#include "myreg52.h"
#include <intrins.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
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
//ultrasound
sbit trig=P2^0;
sbit echo=P2^1;
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
//pwm值预设
uchar push_left_pwm_value=0;
uchar push_right_pwm_value=0;
//左右电机pwm配置
uchar left_pwm_value=0;
uchar right_pwm_value=0;
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
uint temp0,bai0,shi0,ge0,aa0,n0;
uint temp1,bai1,shi1,ge1,aa1,n1;
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
//启动超声波模块
void USModule_start(){
	trig=1;
	//delay_20us();//延时20us
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
//超声波模块初始化
void USModule_init(){
	//trig echo都拉低电平
	trig=0;
	echo=0;
}
//定时器1初始化
void timer0_init(){
	TH0=0;
	TL0=0;
	ET0=1;
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
//根据串口发送的数据控制电机
void Motors_Handler(){
	//ConfigUART(9600);
	//while(!RI);
		//RI=0;

		b=SBUF;
		//a=b;
		//SBUF=a;
		switch(b){
			//1，Ascii码为31，对应的十进制数为49
			//按下前进发送A,B,C对应低速、中速、高速
			//前进(A)
			case 65:
				//相应的操作
			  left_motor_go();
			  right_motor_go();
			  //display1602(bai0,shi0,ge0,bai1,shi1,ge1);
				break;
			//后退(D)
			case 68:
				left_motor_back();
			  right_motor_back();
				//display1602(bai0,shi0,ge0,bai1,shi1,ge1);
			  break;			
			//左转(原地左转圈C)
			case 67:
				left_motor_stop();
			  right_motor_go();
				//display1602(bai0,shi0,ge0,bai1,shi1,ge1);
			  break;		
			//右转(原地右转圈B)
			case 66:		
				left_motor_go();
			  right_motor_stop();
				//display1602(bai0,shi0,ge0,bai1,shi1,ge1);
			  break;
			//停止('S')
			case 83:
				left_motor_stop();
			  right_motor_stop();
			  //display1602(bai0,shi0,ge0,bai1,shi1,ge1);
			  break;
			//默认
			  default:
				left_motor_stop();
			  right_motor_stop();
			  display1602(bai0,shi0,ge0,bai1,shi1,ge1);
			  break;
		}
		//while(!TI);
		//TI=0;
}
//产生波特率9600
void ConfigUART(uint baud){
	SCON=0x50;
	TH1=256-(11059200/12/32)/baud;
	TL1=TH1;
	TR1=1;//启动定时器1
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
//超声波模块处理
void USModule_Handler(){
	lcd_show();//lcd初显示
	USModule_start();
	while(!echo);//等待高电平来临，启动计时器
	TR0=1;
	while(echo);//等待高电平结束，关闭计时器
	TR0=0;
	successful=1;//高电平输出完成，成功
	time=TH0*256+TL0;//读出计时器中的值来计算距离
	//重新装入初值，计数
	TH0=0;
	TL0=0;
	distance=(time*1.7)/100;//单位是厘米
	if(distance>700 || successful==0){
		distance=0;//不接收数据
	}
	if(distance<=10){
			//feng=0;
			left_motor_stop();
			right_motor_stop();
			delayms(1000);//遇到障碍时候延迟一秒，然后选择向右转弯
			left_motor_go();
			right_motor_stop();
		}else{
			//feng=1;
		}
		bai=distance/100;
		shi=distance%100/10;
		ge=distance%100%10;
		write_data(table[bai]);
		write_data(table[shi]);
		write_data(table[ge]);
		write_data(' ');
		write_data('c');
		write_data('m');
	  delayms(10);//延时10ms再进行下次测距
		
}
//lcd1602显示转速
void display1602(uint bai0,uint shi0,uint ge0,uint bai1,uint shi1,uint ge1){
	write_com(0x82);
	write_data(table[bai0]);
	write_data(table[shi0]);
	write_data(table[ge0]);
	write_com(0x80+0x08);
	write_data(table[bai1]);
	write_data(table[shi1]);
	write_data(table[ge1]);
}
void timer2_start(){
	//启动定时器2
	RCAP2H=(65536-1000)/256;//1ms产生一次溢出中断,用来产生pwm波
	RCAP2L=(65536-1000)%256;
	T2CON=0;
	ET2=1;
	TR2=1;
}
void timer0_start(){
	/*temp0=0;
	temp1=0;
	bai0=0;
	shi0=0;
	ge0=0;
	bai1=0;
	shi1=0;
	ge1=0;*/
	//TMOD=0x01;//定时器0工作模式1
	//TCON|=0x0F;
	TH0=(65536-50000)/256;
	TL0=(65536-80000)%256;
	EA=1;
	ET0=1;
	TR0=1;
	EX0=1;
	EX1=1;
}
//主程序
void main(){
	TMOD=0x21;//定时器0和1都使用
	//TCON|=0x0F;
	EA=1;
	//EX0=1;
	//EX1=1;
	//timer0_init();
	ConfigUART(9600);
	//lcd_init();
	//timer0_start();
	//successful=0;
	//USModule_init();
	//timer2_start();
	//display1602(bai0,shi0,ge0,bai1,shi1,ge1);
	while(1){
		//display1602(bai0,shi0,ge0,bai1,shi1,ge1);
	  Motors_Handler();//处理电机模块
		//USModule_Handler();//处理超声波模块
		//display1602(bai0,shi0,ge0,bai1,shi1,ge1);
		//display1602(1,2,3,4,5,6);
		/*ConfigUART(9600);
		b=SBUF;
		if(b==65){
			left_motor_go();
			right_motor_go();
		}else if(b==68){
			left_motor_back();
			right_motor_back();
		}else if(b==67){
			left_motor_stop();
			right_motor_go();
		}else if(b==66){
			left_motor_go();
			right_motor_stop();
		}*/
	}
}
/*void timer2() interrupt 5{
	TF2=0;
	//产生pwm波
	//left
	left_pwm_value++;
	right_pwm_value++;
	if(left_pwm_value<=push_left_pwm_value){
		left_motor_pwm_port=1;
	}else{
		left_motor_pwm_port=0;
	}
	if(left_pwm_value==10){
		left_pwm_value=0;
	}
	//right
	if(right_pwm_value<=push_right_pwm_value){
		right_motor_pwm_port=1;
	}else{
		right_motor_pwm_port=0;
	}
	if(right_pwm_value==10){
		right_pwm_value=0;
	}
}*/
//外部中断0
void out0() interrupt 0{
	n0++;//高电平的个数
	while(outint0==0);
}
//外部中断1
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
		//temp0=50;
		n0=0;
		bai0=temp0/100;
		shi0=temp0%100/10;
		ge0=temp0%10;
	}
	if(aa1==10){
		aa1=0;
		temp1=5*n1;
		//temp1=60;
		n1=0;
		bai1=temp1/100;
		shi1=temp1%100/10;
		ge1=temp1%10;
	}
}