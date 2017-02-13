#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar flag;//接收完成标志位
uchar msg_r[3];//收到的消息
uchar rec;
uchar i;
uchar code msg[]="i get ";//消息主体
void init(){
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	SM0=1;
	SM1=1;
	REN=1;
	EA=1;
	ES=1;//打开串口中断
}
void main(){
	init();
	msg_r[0]='b';
	msg_r[1]='e';
	msg_r[2]='a';
	while(1){
		//判断是否接收数据完成
    if(flag==1){
			ES=0;//关闭串口中断
			//先输出固定部分
			for(i=0;i<6;i++){
				SBUF=msg[i];
				while(!TI);
				TI=0;
			}
			for(i=0;i<3;i++){
				SBUF=msg_r[i];
			  while(!TI);
			  TI=0;
			}
			SBUF=rec;
			while(!TI);
			TI=0;
			ES=1;//重新打开串口中断
			flag=0;
		}			
	}
}
void serial() interrupt 4{
	RI=0;
	rec=SBUF;//接收数据
	flag=1;	
}