#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit wele=P2^7;
sbit dule=P2^6;
//main
void main(){
   dule=1;
   P0=0x7f;
   dule=0;

   P0=0xff;
   wele=1;
   P0=0x00;
   wele=0;  
}