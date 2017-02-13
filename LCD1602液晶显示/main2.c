#include <reg52.h>
typedef unsigned int uint;
typedef unsigned char uchar;

sbit RS=P3^5;
sbit RW=P3^6;
sbit EN=P3^4;
//whether lcd is busy,busy wait
void Read_Busy(){
	uchar busy;
	P2=0xff;
	RS=0;
	RW=1;
	do{
		EN=1;
		busy=P0;
		EN=0;
	}while(busy & 0x80);
}
//write command
void Write_Cmd(uchar cmd){
	//busy or not
	Read_Busy();
	RS=0;
	RW=0;
	P2=cmd;
	EN=1;
	EN=0;
}
//write a byte
void Write_Data(uchar dat){
	Read_Busy();
	RS=1;
	RW=0;
	P0=dat;
	EN=1;
	EN=0;
}
//write a string
void max(uchar a,uchar b,uchar *max){
	*max=(a>b)?a:b;
}
//main
void main(){
	//settings
	//define an array
	//uchar i;
	//uchar a[10]={0,1,2,3,4,5,6,7,8,9};
	// uchar a[]={"monday"};
	uint k=1000;
	uchar i;
	uchar *a[]={"Monday","Tuesday","Wednesday"};
	uchar *pa;
	Write_Cmd(0x38);
	Write_Cmd(0x0f);
	Write_Cmd(0x01);
	Write_Cmd(0x07);
	//
	Write_Cmd(0x80 | 0x0F);
	//pa=&a[1];
	//Write_Data(*pa+'0');
	//for(i=0;i<10;i++){
		//Write_Data('0'+*(pa+i));
		//µÈ¼ÛÓÚWrite_Data('0'+*pa++);
	//}
	// pa=&a;
	// while(*pa!='\0'){
	// 	Write_Data(*pa++);
	// }
	for(i=0;i<3;i++){
		pa=a[i];
	    while(*pa!='\0'){
		    Write_Data(*pa++);
		    while(k--);
	    }
	}
	//Write_Data('0'+*(pa+1));
	//Write_Data('b');
	//Write_Data('c');

	while(1);
}