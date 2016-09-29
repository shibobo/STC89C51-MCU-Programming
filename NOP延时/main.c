#include <reg52.h>
#include <intrins.h>
#define uint unsigned int 
//main
uint i;
void main(){
	P1=0xff;
	//wait for 1 second
	//110*50*20=1s
	for(i=0;i<110*1000;i++){
		_nop_();
	}
	P1=0x00;
	while(1);
}