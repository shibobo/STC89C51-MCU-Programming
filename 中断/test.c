#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit dule=P2^6;
sbit wela=P2^7;
sbit led1=P1^0;
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
void display(uchar,uchar,uchar);
uchar num,num1,num2,bai,shi,ge;
//main
void main(){
	TMOD=0x01;
	//
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	//
	TH1=(65536-45872)/256;
	TL1=(65536-45872)%256;
	//
	EA=1;
	//
	ET0=1;
	//
	ET1=1;
	//
	TR0=1;
	//	
	TR1=1;
	while(1){
	   display(bai,shi,ge);
	}
		

  
}
//void display(uchar shi,uchar ge){
void display(uchar bai,uchar shi,uchar ge){
	//
	dule=1;
	P0=table[bai];
	dule=0;
	//
	P0=0xff;
	wela=1;
	P0=0xfe;
	wela=0;
	delayms(5);//

	dule=1;
	P0=table[shi];
	dule=0;
	P0=0xff;
	wela=1;
	P0=0xfd;
	wela=0;
	delayms(5);

	dule=1;
	P0=table[ge];
	dule=0;
	P0=0xff;
	wela=1;
	P0=0xfb;
	wela=0;
	delayms(5);
}
void delayms(uint xms){
	uint i,j;
	for (i=xms;i>0;i--)
	{
		for (j=110;j>0;j--)
		{
			//nothing to do
		}
	}

}
void T0_time() interrupt 1{
    TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	num1++;
	if (num1==4)
	{
		num1=0;
		led1=~led1;
	}
}
void T1_time() interrupt 3{
	TH1=(65536-45872)/256;
	TL1=(65536-45872)%256;
	num2++;
	if (num2==20)
	{
		num2=0;
		num++;
		if (num==999)
		{
			num=0;
		}
		bai=num/100;
		//shi=num/10%10;
		//another way to get shi
		shi=num%100/10;
		ge=num%10;
	}
}