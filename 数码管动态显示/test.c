#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit dula=P2^6;
sbit wela=P2^7;
uint index=0;
uint num=25;
//要显示的数据
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
                0x00,  //熄灭
                0x80  //自定义
};
void delay();
void main(){
    //回顾上节课的东西，点亮后四个二极管
	P1=0xf0;
	/**
	//位选
	wela=1;
	P0=0x00;
	wela=0;
	//段选
	dula=1;
	P0=0xff;
	dula=0;
	while(1); */
	//打开位选
	wela=1;
	//送数据（全部选中）
	P0=0x00;
	//关闭位选
	wela=0;

	//打开段选
	//dula=1;
	//循环送数据
	while(1){
		for(index=0;index<=num;index++){
		    dula=1;
			P0=table[index];
			delay();
			dula=0;
		}	   
	}
	//P0=table[1];
	//关闭段选
	//dula=0;
}
void delay(){
   uint i,j;
   for(i=200;i>0;i--)
     for(j=200;j>0;j--);
}