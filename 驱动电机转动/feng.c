#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char 
#define uint unsigned int

sbit beep=P2^3;
sbit kaiguan=P3^0;

void delay()		   //??0.5ms?????
{
	uchar a;
	for(a=450;a>0;a--)
	{
		_nop_();
	}
}
void main()
{
	while(1)
	{
		if(!kaiguan)
		{
			uint m;
			for(m=800;m>0;m--)	  //????0.5ms*800
			{
				beep=~beep;		
				delay();		 //2000HZ????
			}
			for(m=500;m>0;m--)	 //????0.5ms*2*500
			{
				beep=~beep;
				delay();
				delay();		//1000HZ????
			}
		}
	}
}