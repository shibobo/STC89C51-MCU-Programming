#include <reg52.h>
//#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char;
//a用来给P1口赋值
uchar a;
//声明延时函数
void delayms(void);
//实现延时函数
void delayms(void){
    uint i,j;
    for(i=100;i>0;i--)
	   for(j=100;j>0;j--);
}
//主函数
void main(void){
    a=0xfe;
	while(1){
	  P1=a;
	  delayms();
	  //循环左移一位
	  a=_crol_(a,1);
	  //a=a<<1;
	}
}
