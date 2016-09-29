#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit wela=P2^7;	//位选
sbit dula=P2^6;	//段选
//delay fun declaration
void delayxms(uint xms);
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
//main func
void main(){
  while(1){
     //control the two-pole light
	 P1=0x0e;
     //open dula choose
     dula=1;
	 //send data
	 P0=table[0];
	 //close dula choose
	 dula=0;
	 //clean the "shadow": a very important way to simplify the shadow
     P0=0xff;
	 //open wela choose
	 wela=1;
	 //send data
	 P0=0xfe;
	 //close wela choose
  	 wela=0;
	 delayxms(500);

	 //open dula choose
     dula=1;
	 //send data
	 P0=table[1];
	 //close dula choose
	 dula=0;
	 //clean the "shadow": a very important way to simplify the shadow
     P0=0xff;
	 //open wela choose
	 wela=1;
	 //send data
	 P0=0xfd;
	 //close wela choose
  	 wela=0;
	 delayxms(500);

	 //open dula choose
     dula=1;
	 //send data
	 P0=table[2];
	 //close dula choose
	 dula=0;
	 //clean the "shadow": a very important way to simplify the shadow
     P0=0xff;
	 //open wela choose
	 wela=1;
	 //send data
	 P0=0xfb;
	 //close wela choose
  	 wela=0;
	 delayxms(500);


	 //open dula choose
     dula=1;
	 //send data
	 P0=table[3];
	 //close dula choose
	 dula=0;
	 //clean the "shadow": a very important way to simplify the shadow
     P0=0xff;
	 //open wela choose
	 wela=1;
	 //send data
	 P0=0xf7;
	 //close wela choose
  	 wela=0;
	 delayxms(500);
	 
	 //open dula choose
     dula=1;
	 //send data
	 P0=table[4];
	 //close dula choose
	 dula=0;
	 //clean the "shadow": a very important way to simplify the shadow
     P0=0xff;
	 //open wela choose
	 wela=1;
	 //send data
	 P0=0xef;
	 //close wela choose
  	 wela=0;
	 delayxms(500);
	 
	 //open dula choose
     dula=1;
	 //send data
	 P0=table[5];
	 //close dula choose
	 dula=0;
	 //clean the "shadow": a very important way to simplify the shadow
     P0=0xff;
	 //open wela choose
	 wela=1;
	 //send data
	 P0=0xdf;
	 //close wela choose
  	 wela=0;
	 delayxms(500);
	 
	 //open dula choose
     dula=1;
	 //send data
	 P0=table[6];
	 //close dula choose
	 dula=0;
	 //clean the "shadow": a very important way to simplify the shadow
     P0=0xff;
	 //open wela choose
	 wela=1;
	 //send data
	 P0=0xbf;
	 //close wela choose
  	 wela=0;
	 delayxms(500);
	
	 //open dula choose
     dula=1;
	 //send data
	 P0=table[7];
	 //close dula choose
	 dula=0;
	 //clean the "shadow": a very important way to simplify the shadow
     P0=0xff;
	 //open wela choose
	 wela=1;
	 //send data
	 P0=0x7f;
	 //close wela choose
  	 wela=0;
	 delayxms(500);	 	 	  
  }
}
//delay func
void delayxms(uint xms){
   uint i,j;
   for(i=xms;i>0;i--)
     for(j=110;j>0;j--);
}