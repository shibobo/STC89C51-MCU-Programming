#include <reg52.h>
//#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
uchar num;
//main
/*void delayms(uint z){
    uint x,y;
	for(x<z;x>0;x--)
	    for(y=114;y>0;y--);
}*/
void UART_init(){
    TMOD=0x20;//T1工作在方式2
	TH1=0xfd;
	TL1=0xfd;  //比特率为9600
	TR1=1;    //启动T1定时器
	SM0=0;    //
	SM1=1;    //串口工作在方式1
	REN=1;    //串口允许接收位
	EA=1;     //开总中断
	ES=1;     //串口中断打开
}
void main(){
	UART_init();
	while(1);
		//{
		//SBUF=num;
		
		//while(!RI);
		//P1=SBUF;
		//RI=0;
		//num++;
		//delayms(5000);
	//}
}
void UART() interrupt 4{
	// if (TI)
	// {
	// 	SBUF=num;
	// 	TI=0;
	// }
	if (RI)  //检测是否接收完成
	{
		num=SBUF;  //num取出接收
		P1=SBUF;
		num++;
		RI=0;
		SBUF=num;
		while(!TI);
		TI=0;
	}
}