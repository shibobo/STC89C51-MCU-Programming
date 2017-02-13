#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
uint count=0;
uint flag=0;
void main(){
	flag=0;
	EA=1;
	EX0=1;
	IE0=0;
	while(1){
		while(flag==0);
		switch(count%10){
			case 0:
				P1=0x00;
				break;
			case 1:
				P1=0xf0;
				break;
			case 2:
				P1=0x0f;
				break;
			default:
				P1=0xfe;
				break;
		}
		flag=0;
	}
	
}
void int0() interrupt 0{
	count++;
	flag=1;
}