#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit out1=P0^0;
sbit out2=P0^1;
sbit out3=P0^2;
sbit out4=P0^3;

sbit led1=P1^0;
sbit led2=P1^1;
sbit led3=P1^2;
sbit led4=P1^3;
void main(){
	//out=0  not_black;
	//out=1  is_black;
	while(1){
	if(out1==0){
		led1=1;
	}else{
		led1=0;
	}
	if(out2==0){
		led2=1;
	}else{
		led2=0;
	}
	if(out3==0){
		led3=1;
	}else{
		led3=0;
	}
	if(out4==0){
		led4=1;
	}else{
		led4=0;
	}
  }
}