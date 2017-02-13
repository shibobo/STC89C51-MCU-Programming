#include "myreg52.h"
#include <intrins.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
/**
*端口定义
*/
//P1^6接电机驱动模块ENA,P1^7接电机驱动模块ENB
sbit left_motor_pwm_port=P1^6;
sbit right_motor_pwm_port=P1^7;
//左边电机的接法
sbit int1=P1^0;
sbit int2=P1^1;
//右边电机的接法
sbit int3=P1^2;
sbit int4=P1^3;
//超声波模块
sbit trig=P2^0;
sbit echo=P2^1;
//蜂鸣器
sbit feng=P2^3;
sbit led_left=P1^4;
sbit led_right=P1^5;
//lcd1602液晶显示模块
sbit lcden=P3^4;//EN
sbit lcdrs=P3^5;//RS
sbit lcdrw=P3^6;//RW
sbit dula=P2^6;
sbit wela=P2^7;
/**
*函数清单
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
//产生波特率	
void ConfigUART(uint baud);
//电机转动状态配置
void left_motor_go();
void left_motor_back();
void left_motor_stop();

void right_motor_go(); 
void right_motor_back();
void right_motor_stop(); 
void timer2_start();
/**
*变量清单
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

//延时函数
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
	dula=0;
	wela=0;
	lcden=0;
	lcdrw=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}
//1602写命令
void write_com(uchar com){
	lcdrs=0;
	//ledrw=0;
	P0=com;
	delayms(5);
	lcden=1;
	delayms(5);
	lcden=0;
}
//1602写数据
void write_data(uchar dat){
	lcdrs=1;
	//ledrw=0;
	P0=dat;
	delayms(5);
	lcden=1;
	delayms(5);
	lcden=0;
}
//1602初显示
void lcd_show(){
	uint num;
	write_com(0x80);
	for(num=0;num<9;num++){
		write_data(tips[num]);
		delayms(5);
	}
}
//根据串口发送的数据控制电机
void Motors_Handler(){
	ConfigUART(9600);
	//while(!RI);
		//RI=0;

		b=SBUF;
		//a=b;
		//SBUF=a;
		switch(b){
			//1，Ascii码为31，对应的十进制数为49
			//按下前进发送A,B,C对应低速、中速、高速
			//前进
			case 65:
				//相应的操作
			  left_motor_go();
			  right_motor_go();
				break;
			//后退
			case 68:
				left_motor_back();
			  right_motor_back();
				break;
			//左转(原地左转圈)
			case 67:
				left_motor_stop();
			  right_motor_go();
				break;
			//右转(原地右转圈)
			case 66:
				left_motor_go();
			  right_motor_stop();
				break;
			//停止
			case 83:
				left_motor_stop();
			  right_motor_stop();
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
			feng=0;
			left_motor_stop();
			right_motor_stop();
			delayms(1000);//遇到障碍时候延迟一秒，然后选择向右转弯
			left_motor_go();
			right_motor_stop();
		}else{
			feng=1;
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
void timer2_start(){
	//启动定时器2
	RCAP2H=(65536-1000)/256;//1ms产生一次溢出中断,用来产生pwm波
	RCAP2L=(65536-1000)%256;
	T2CON=0;
	ET2=1;
	TR2=1;
}
//主程序
void main(){
	TMOD=0x21;//定时器0和1都使用
	EA=1;
	timer0_init();
	//lcd_init();
	//successful=0;
	//USModule_init();
	timer2_start();
	push_left_pwm_value=9;
	push_right_pwm_value=9;
	while(1){
		Motors_Handler();//处理电机模块
		//USModule_Handler();//处理超声波模块
	}
}
void timer2() interrupt 5{
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
}