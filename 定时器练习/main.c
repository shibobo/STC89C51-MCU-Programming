#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit we=P2^7;
sbit du=P2^6;
uchar count0,count1;
uchar temp0,temp1=0x7f;
uchar code leddata[]={ 
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
                0x00,  //熄灭
                0x00  //自定义 
                };
void delayms(uint z){
    uint x,y;
	for(x=z;x>0;x--)
	    for(y=114;y>0;y--);
}
void display(uchar i){
    uchar shi,ge;
	shi=i/10;
	ge=i%10;

	P0=0xff;
	we=1;
	P0=0xfe;//点亮第1位数码管
	we=0;

	du=1;
	P0=leddata[shi];
	du=0;
	delayms(5);

	P0=0xff;
	we=1;
	P0=0xfd;//点亮第2位数码管
	we=0;

	du=1;
	P0=leddata[ge];
	du=0;
	delayms(5);
}
void init(){
    TMOD=0x11;//定时器T0，T1
	TH1=TH0=0x4b;
	TL1=TL0=0xfd;
	ET1=ET0=1;
	TR1=TR0=1;
	EX0=1; //开外部中断0
	IT0=0; //外部中断0为低电平触发方式
	EA=1;  //开总中断
}
//main
void main(){
    init();//调用配置函数
	while(1){
	    display(temp0);//数码管显示
	}
}
void int0() interrupt 0{
    TR0=0;//关闭定时器0
}
void timer0() interrupt 1{
    TH0=0x4b;
	TL0=0xfd;
	count0++;
	if(count0==10){
	    count0=0;
		temp0++;
		if(temp0>60){
		    temp0=0;
		}
	}
}
void timer1() interrupt 3{
    TH1=0x4b;
	TL1=0xfd;
	count1++;
	if(count1==10){
	    count1=0;
		P1=temp1;
		temp1=_cror_(temp1,1);
	}


}