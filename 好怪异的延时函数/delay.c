#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit dula=P2^6;
sbit wela=P2^7;
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
                0x00,  //??
                0x80  //???
};
void delayms(uint z)
{
  uint x,y;
  for(x=z;x>0;x--)
     for(y=120;y>0;y--);
}
void display(uchar num){
	uchar shi,ge;
	shi=num/10;
	ge=num%10;
	
	dula=1;
	P0=table[shi];
	dula=0;
	
	P0=0xff;
	wela=1;
	P0=0xfe;
	wela=0;
	delayms(5);
	
	dula=1;
	P0=table[ge];
	dula=0;
	
	P0=0xff;
	wela=1;
	P0=0xfd;
	wela=0;
	delayms(5);
}
void main(){
	uchar x=89;
	display(x);
}
