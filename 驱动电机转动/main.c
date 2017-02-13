#include <reg52.h>
sbit int1=P1^0;
void main(){
	int1=1;
	P1=0xff;
	while(1){
	}
}