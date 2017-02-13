#include <reg52.h>
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
                0x6F,  //"9"
                0x77,  //"A"
                0x7C,  //"B"
                0x39,  //"C"
                0x5E,  //"D"
                0x79,  //"E"
                0x71,  //"F"
                0x76,  //"H"
                0x38,  //"L"
                0x37,  //"n"
                0x3E,  //"u"
                0x73,  //"P"
                0x5C,  //"o"
                0x40,  //"-"
};
void delayms(uchar time){
	uint i,j;
	for(i=time;i>0;i--){
		for(j=110;j>0;j--){
			//to do something
		}
	}
}
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
void display(uchar value){
	uchar bai,shi,ge;
	bai=value/100;
	shi=value%100/10;
	ge=value%10;
	
	dula=1;
	P0=table[bai];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfe;
	wela=0;
	delayms(5);
	
	dula=1;
	P0=table[shi];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfd;
	wela=0;
	delayms(5);
	
	dula=1;
	P0=table[ge];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfb;
	wela=0;
	delayms(5);
}
float get_ad(){
	float adval;
	//产生随机数
	//随机数=(0~100)%100,即100以内的随机数对100取余数
	//srand((uint)time(NULL));
	adval=rand()%256;
	return adval;
}
void main(){
	init();
	wela=1;
	P0=0xff;
	wela=0;
	while(1){
		if(flag_uart==1){
			flag_uart=0;
			ES=0;
			TI=1;
			switch(flag_on){
				case 0:
					puts("turn on ad");
			    TR0=1;//定时器0开启
					break;
				case 1:
					printf("turn off ad");
				  TR0=0;//定时器0关闭
					break;
				case 2:
					puts("error!");
					break;
			}
			while(!TI);
			TI=0;
			ES=1;
		}
		if(flag_time==1){
			flag_time=0;
			ad_val=get_ad();
			display(ad_val);
			ad_vo=ad_val/256.0*5.0;
			ES=0;
			TI=1;
			printf("ad_val=%f\n",ad_val);
			printf("the voltage is %fV\n",ad_vo);
			while(!TI);
			TI=0;
			ES=1;
		}
		display(ad_val);	
	}
}
void timer0() interrupt 1{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	t0num++;
	if(t0num==20){//每1s采集一次数据
		t0num=0;
		flag_time=1;
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
}