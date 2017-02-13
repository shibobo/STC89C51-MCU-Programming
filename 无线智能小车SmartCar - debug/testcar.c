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
sbit feng=P0^0;
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
void display1602(uint bai0,uint shi0,uint ge0,uint bai1,uint shi1,uint ge1,uint qian,uint bai,uint shi,uint ge);
/**
*variable lists
*/
uchar left_pwm_value,right_pwm_value;
uchar push_left_pwm_value,push_right_pwm_value;

uchar a,b;
uint count;//定时器溢出的次数
uint count1;//定时器1溢出的次数
uint time;//echo输出的高电平持续的时间
ulong distance;//小车前进距离
uint qian,bai,shi,ge;
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
	write_data('r');
	write_data('p');
	write_data('m');
	
	write_com(0x80+0x08);
	write_data('L');
	write_data(':');
	write_data(table[10]);
	write_data(table[10]);
	write_data(table[10]);
	write_data('r');
	write_data('p');
	write_data('m');
	
	write_com(0x80+0x40);
	write_data('D');
	write_data('I');
	write_data('S');
	write_data(':');
	write_data(table[10]);
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
void display1602(uint bai0,uint shi0,uint ge0,uint bai1,uint shi1,uint ge1,uint qian,uint bai,uint shi,uint ge){
  P2=0x00;
	write_com(0x82);
	write_data(table[bai0]);
	write_data(table[shi0]);
	write_data(table[ge0]);
	
	write_com(0x80+0x0A);
	write_data(table[bai1]);
	write_data(table[shi1]);
	write_data(table[ge1]);
	
	write_com(0x80+0x44);
	write_data(table[qian]);
	write_data(table[bai]);
	write_data(table[shi]);
	write_data(table[ge]);
}
void timer0_start(){
	TMOD=0x21;//timer0 count to speed, timer1 to UART
	TH0=(65536-50000)/256;//50ms
	TL0=(65536-50000)%256;//50ms
	EA=1;
	ET0=1;
	TR0=1;
}
void timer2_start(){
	T2MOD=0;
	T2CON=0;
	RCAP2H=(65536-100)/256;//0.1ms
	RCAP2L=(65536-100)%256;
	TH2=RCAP2H;
	TL2=RCAP2L;
	//T2CON=0;
	TF2=0;
	ET2=1;
	EA=1;
	TR2=1;
}
void initUART(){
	//TMOD=0x21;//单独调试串口模块的时候需要加
	SCON=0x50;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	SM0=0;
	SM1=1;
	REN=1;
	EA=1;
	ES=1;
}
void outint_start(){
	IE0=0;
	EX0=1;
	IT0=1;
	EA=1;
	
	IE1=0;
	EX1=1;
	IT1=1;
	EA=1;
}
//pid control the speed
float pid_controller(float vset,float vreal){
	float pwmvalue;
	float ee,eeold;
	float P,I,D;
	eeold=ee;
	ee=vset-vreal;
	P=ee;
	I=I+ee;
	D=ee-eeold;
	pwmvalue=kp*P+ki*I+kd*D;
	return pwmvalue;
}
void set_accurate_speed(uchar svalue){
	push_left_pwm_value=pid_controller(svalue,temp0);
	if(push_left_pwm_value>=100){
		push_left_pwm_value=100;
	}else if(push_left_pwm_value<=0){
		push_left_pwm_value=0;
	}
}
void main(){
	timer2_start();//generate pwm
	timer0_start();//measure speed
	lcd_init();
	initUART();
	push_left_pwm_value=100;
	push_right_pwm_value=100;
	outint_start();//外部中断有问题，加入外部中断之后电机就不转动了
	//left_motor_go();
	//right_motor_go();
	while(1){		
		//debug
    if(flag_rec==1){
			flag_rec=0;
			ES=0;
			TI=1;
			switch(data_rec){
				//High speed
				case 65:
					push_left_pwm_value=100;
				  push_left_pwm_value=100;
					left_motor_go();
				  right_motor_go();
				  puts("ahead fast");
				  break;
				//Slow speed
				case 97:
					push_left_pwm_value=50;
				  push_left_pwm_value=50;
					left_motor_go();
				  right_motor_go();
				  puts("ahead slow");
					break;
				
				
				case 68:
					push_left_pwm_value=100;
				  push_left_pwm_value=100;
					left_motor_back();
				  right_motor_back();
				  puts("back fast");
					break;
				case 100:
					push_left_pwm_value=50;
				  push_left_pwm_value=50;
					left_motor_back();
				  right_motor_back();
				  puts("back slow");
					break;
				
				
				case 67:
				  push_left_pwm_value=100;
				  push_left_pwm_value=100;
					left_motor_stop();
				  right_motor_go();
				  puts("left fast");
					break;
			  case 99:
				  push_left_pwm_value=50;
				  push_left_pwm_value=50;
					left_motor_stop();
				  right_motor_go();
				  puts("left slow");
					break;
				
				
				case 66:
					push_left_pwm_value=100;
				  push_left_pwm_value=100;
					left_motor_go();
				  right_motor_stop();
				  puts("right fast");
					break;
			  case 98:
					push_left_pwm_value=50;
				  push_left_pwm_value=50;
					left_motor_go();
				  right_motor_stop();
				  puts("right slow");
					break;
				
				
				//stop
				case 83:
					left_motor_stop();
				  right_motor_stop();
				  puts("stop");
				  break;
				case 0:
					puts("error");
					break;
			}
			while(!TI);
			TI=0;
			ES=1;
		}
	}
}
//外部中断0
void out0() interrupt 0{
	EX0=0;
	n0++;
  EX0=1;
}
//外部中断1
void out1() interrupt 2{
	EX1=0;
	n1++;
	EX1=1;
}
void uartint() interrupt 4{
	ES=0;
	if(RI){
		RI=0;
		flag_rec=1;
		data_rec=SBUF;
	}
	ES=1;
}
void timer0() interrupt 1{
	TH0=(65536-50000)/256;
	TL0=(65536-80000)%256;
	count++;
	if(count==20){
		count=0;
		temp0=5*n0;
		n0=0;
		temp1=5*n1;
		n1=0;
		
		if(temp0>=temp1){
			distance+=temp1/60*2*3.14*3.2;
			if(distance%100==0 && distance>0){
				feng=0;
				delayms(1000);
				feng=1;
			}
			if(distance>=9999){
				distance=0;
			}
		}else{
			distance+=temp0/60*2*3.14*3.2;
		  if(distance%100==0 && distance>0){
				feng=0;
				delayms(1000);
				feng=1;
			}
			if(distance>=9999){
				distance=0;
			}
		}
		
		bai0=temp0/100;
		shi0=temp0%100/10;
		ge0=temp0%10;
		bai1=temp1/100;
		shi1=temp1%100/10;
		ge1=temp1%10;
		
		qian=distance/1000;
		bai=distance%1000/100;
		shi=distance%1000%100/10;
		ge=distance%10;
		
		display1602(bai0,shi0,ge0,bai1,shi1,ge1,qian,bai,shi,ge);
	}
}

void timer2() interrupt 5{
	TF2=0;
	//left
	left_pwm_value++;
	right_pwm_value++;
	if(left_pwm_value<=push_left_pwm_value){
		left_motor_pwm_port=1;
	}else{
		left_motor_pwm_port=0;
	}
	if(left_pwm_value==100){
		left_pwm_value=0;
	}
	//right
	if(right_pwm_value<=push_right_pwm_value){
		right_motor_pwm_port=1;
	}else{
		right_motor_pwm_port=0;
	}
	if(right_pwm_value==100){
		right_pwm_value=0;
	}
}