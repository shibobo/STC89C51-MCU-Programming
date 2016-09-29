#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
//key define
sbit key1=P3^0;
sbit key2=P3^1;
sbit key3=P3^2;
sbit key4=P3^3;
sbit dula=P2^6;
sbit wela=P2^7;
uchar code table[]={
	0x3f,
	0x06,
	0x5b,
	0x4f,
	0x66,
	0x6d,
	0x7d,
	0x07,
	0x7f,
	0x6f,
	0x77,
	0x7c,
	0x39,
	0x5e,
	0x79,
	0x71
};
void delayms(uint);
void display(uchar);
void init();
void keyscan();
uchar num0,num;
//main
void main(){
	//init
	init();	
	while(1){
		//key scan
		
		display(num);
		keyscan();
	}
	
}
void init(){
	TMOD=0x01;
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	EA=1;
	ET0=1;
	TR0=1;
}
void delayms(uint xms){
	uint i,j;
	for(i=xms;i>0;i--){
		for(j=110;j>0;j--){
			//nothing to do
		}
	}

}
void display(uchar numdis){
	uchar shi,ge;
	shi=numdis/10;
	ge=numdis%10;

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
//define interrupt 1
void T0_time() interrupt 1{
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	num0++;
	if(num0==200){
		num0=0;
		num++;
		if (num==60)
		{
			num=0;
		}
	}
}
void keyscan(){
	//key1 is clicked
	if(key1==0){
		delayms(10);
		if(key1==0){
			num++;
			if(num==60){
				num=0;
			}
			while(!key1);
			
		}
	}
	//key2 is clicked
	if(key2==0){
		delayms(10);
		if(key2==0){
			num--;
			if (num==0)
			{
				num=60;
			}
			while(!key2);
		}
	}
}
