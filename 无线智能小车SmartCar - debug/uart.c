#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
uint flag_rec,b,data_rec;

void initUART(){
	TMOD=0x20;
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

void main(){
	initUART();
	while(1){		
		//debug
    if(flag_rec==1){
			flag_rec=0;
			ES=0;
			TI=1;
			switch(data_rec){
				case 65:
					//left_motor_go();
				  //right_motor_go();
				  puts("go ahead");
					break;
				case 68:
					//left_motor_back();
				  //right_motor_back();
				  puts("go back");
					break;
				case 67:
					//left_motor_stop();
				  //right_motor_go();
				  puts("go left");
					break;
				case 66:
					//left_motor_go();
				  //right_motor_stop();
				  puts("go right");
					break;
				case 0:
					puts("fuck");
					break;
			}
			while(!TI);
			TI=0;
			ES=1;
		}  
	}
}
void uartint() interrupt 4{
		//light=~light;
	//if(RI){
			RI=0;
			b=SBUF;
		  flag_rec=1;
		  if(b==65){
				data_rec=65;
			}else if(b==66){
				data_rec=66;
			}else if(b==67){
				data_rec=67;
			}else if(b==68){
				data_rec=68;
			}else{
				data_rec=0;
			}
	//}
}
/*#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include <stdlib.h>
#define uint unsigned int
#define uchar unsigned char
sbit dula=P2^6;
sbit wela=P2^7;
uchar flag,a;
uchar t0num;
float ad_vo,ad_val;
uchar flag_uart,flag_on,flag_time;
void init(){
	TMOD=0x21;
	SCON=0x50;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	ET0=1;
	SM0=0;
	SM1=1;
	REN=1;
	EA=1;
	ES=1;
}
void main(){
	init();
	while(1){
		if(flag_uart==1){
			flag_uart=0;
			ES=0;
			TI=1;
			switch(flag_on){
				case 0:
					puts("turn on ad");
					break;
				case 1:
					printf("turn off ad");
					break;
				case 2:
					puts("error!");
					break;
			}
			while(!TI);
			TI=0;
			ES=1;
		}
	}
}
void ser() interrupt 4{
	RI=0;
	a=SBUF;
	flag_uart=1;
	if(a==48){
		flag_on=0;
	}else if(a==49){
		flag_on=1;
	}else{
		flag_on=2;
	}
}*/