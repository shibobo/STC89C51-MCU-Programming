#include <reg52.h>
#define uint unsigned int;
#define uchar unsigned char;
sbit led1=P1^0;
uchar num;
void main(){
   //选择定时器0，工作方式为方式1，TMOD送00000001H
   TMOD=0x01;
   //设置TL0，TH0
   //晶振频率为11.0592MHz时，定时50ms送数字45872
   TH0=(65536-45872)/256;
   TL0=(65536-45872)%256;
   EA=1;//开总中断
   ET0=1;//开定时器0中断
   TR0=1;//启动计时器0
   while(1){//程序进行到这里时候等待中断
	   if(num==20){
	      num=0;
         //取反，led1灭
		   led1=~led1;
	   }   
   }
}
void T0_time() interrupt 1{
   //重装初值
   TH0=(65536-45872)/256;
   TL0=(65536-45872)%256;
   num++;   
}
