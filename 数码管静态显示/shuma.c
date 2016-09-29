#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit wei=P2^7;//位选
sbit duan=P2^6; //段选

/**
* this is a c file created by the administor named shibobo
* ha ha ha ha ha !!!
*/
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
                0x80  //自定义
};
//定义延时子程序
void delay(uint z);

void main()
{
	duan=1;  //打开段选
	P0=0x5B;
	duan=0;  //关闭段选
	
	//delay(5);


	wei=1;	//打开位选
	P0=0x77;
	wei=0;	//关闭位选
	while(1);
}
//实现延时子程序
void delay(uint z)
{
  uint x,y;
  for(x=z;x>0;x--)
     for(y=100;y>0;y--);
}
