#include <reg52.h>
#include <intrins.h>
//sbit led1=P1^0;
#define uchar unsigned char
#define uint unsigned int
//uint a=65535;
uchar i;
uchar temp;
void delay(uint z);

void main()
{
  temp=0xfe;
  P1=temp;
  while(1)
  {
	for(i=0;i<8;i++)
	{
	    temp=_crol_(temp,1);
		P1=temp;
		delay(1000);
	}
  }
}
//ÑÓÊ±×Ó³ÌÐò
void delay(uint z)
{
  uint x,y;
  for(x=z;x>0;x--)
     for(y=120;y>0;y--);
}
