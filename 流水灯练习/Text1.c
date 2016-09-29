#include <reg52.h>
#include <intrins.h>
#define uint unsigned int	   //52系列单片机头文件
sbit led1=P1^0;		   //声明单片机p1口第一个
sbit led2=P1^1;
void delay(uint time1,uint time2);
/** 任意点亮
void main(){
   //led1=0;		       //点亮第一个放光二极管
   //led2=0;
   //P1=0x00;					//点亮所有的二极管
   //P1=0xaa;						//1,3,5,7亮
   P1=0x55;					//2,4,6,8亮
}*/
/**
void main(void){
   P1=0xFE;
   while(1);
}*/
/**void main(void){
  unsigned char i,j;
  for(i=255;i>0;i--)
    for(j=255;j>0;j--)
  P1=0xfe;
}*/

/**void main(void){
    //大循环
	while(1){
	    led1=0;
		led2=1;
		//延时
		delay(100,100);
		led1=1;
		led2=0;
		//延时
		delay(100,100);
	};
}*/
void delay(uint time1,uint time2){
    uint i,j;
    for(i=time1;i>0;i--)
	    for(j=time2;j>0;j--);
}
//左移测试a<<1;右移测试a>>1
unsigned char a;
void main(void){
    a=0xFF;
	while(1){
        a=a>>1;
		P1=a;
		delay(200,200);
		if(a==0x00){
		    a=0xFF;
		}
	}
}
