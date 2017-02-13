//keil5超好用的说
#include <reg52.h>
#include <intrins.h>
#include <string.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
//控制左边电机
sbit int1=P1^0;
sbit int2=P1^1;
//控制右边电机
sbit int3=P1^2;
sbit int4=P1^3;
//pwm调速
sbit left_motor_pwm_port=P1^6;
sbit right_motor_pwm_port=P1^7;
#define left_motor_go      {int1=1,int2=0;}
#define left_motor_back    {int1=0,int2=1;} 
#define right_motor_go     {int3=1,int4=0;} 
#define right_motor_back   {int3=0,int4=1;}
uchar code leddata[]={ 
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
//
uchar push_left_pwm_value=0;
uchar push_right_pwm_value=0;
uchar left_pwm_value=0;
uchar right_pwm_value=0;
//
bit right_motor_stop=1;
bit left_motor_stop =1;
//
//1602
sbit leden=P3^4;//EN
sbit ledrs=P3^5;//RS
sbit ledrw=P3^6;//RW
sbit dula=P2^6;
sbit wela=P2^7;
uchar code left_speed[]={"LS is five"};
uchar code right_speed[]={"RS is five"};
//char left_speed[];
//char right_speed[];
uchar num;
//
void delayms(uint z){
  uint x,y;
  for(x=z;x>0;x--)
    for(y=114;y>0;y--);
}
//
void write_com(uchar com){
  ledrs=0;
  //ledrw=0;
  P0=com;
  delayms(5);
  leden=1;
  delayms(5);
  leden=0;
}
void write_data(uchar date){
  ledrs=1;
  //ledrw=0;
  P0=date;
  delayms(5);
  leden=1;
  delayms(5);
  leden=0;
}
void write_1602_show(){
  //init 1602
  dula=0;
  wela=0;
  leden=0;
  ledrw=0;
  write_com(0x38);
  write_com(0x0c);
  write_com(0x06);
  write_com(0x01);
  //
  write_com(0x80);

  //uchar code left_speed[]="Left-Speed:5";
  //uchar code right_speed[]="Right-Speed:5";
  //strcat(left_speed,"abc");
  //strcat(right_speed,"123");
  for(num=0;num<10;num++){
    write_data(left_speed[num]);
    delayms(5);
  }
  //change address
  write_com(0x80+0x40);
  for(num=0;num<10;num++){
    write_data(right_speed[num]);
    delayms(5);
  }
}

void run(uchar val1,uchar val2){
  //set pwm value
  push_left_pwm_value=val1;
  push_right_pwm_value=val2;
  left_motor_go;
  right_motor_go;
}
void init(){
  TMOD=0X01;
  TH0= 0XF8;      //50ms??
  TL0= 0X30;
  TR0= 1;
  ET0= 1;
  EA = 1;
}
void main(){
   // while(1){
   // //??
   // int1=1;
   // int2=0;
   // int3=1;
   // int4=0;
   // delayms();
   // //??
   // int1=0;
   // int2=1;
   // int3=0;
   // int4=1;
   // delayms();
   // //??????
   // int1=0;
   // int2=0;
   // int3=1;
   // int4=0;
   // delayms();
   // //??????
   // int1=1;
   // int2=0;
   // int3=0;
   // int4=0;
   // delayms();
   // }
  init();
  while(1){
    //loop
    // run(2,2);
    // delayms(2000);
    // run(5,5);
    // delayms(2000);
    // run(8,8);
    // delayms(2000);
    uchar i;
    for(i=2;i<=10;i++){
      run(i,i);
      delayms(2000);
      write_1602_show();
    }
  }
}
void change_pwm_left(){
  //generate left pwm
  if(left_motor_stop){
    if(left_pwm_value<=push_left_pwm_value){
      left_motor_pwm_port=1;
    }else{
      left_motor_pwm_port=0;
    }
    if(left_pwm_value>=10){
      left_pwm_value=0;
    }
  }else{
    left_motor_pwm_port=0;
  }
}
void change_pwm_right(){
    //generate right pwm
  if(right_motor_stop){
    if(right_pwm_value<=push_right_pwm_value){
      right_motor_pwm_port=1;
    }else{
      right_motor_pwm_port=0;
    }
    if(right_pwm_value>=10){
      right_pwm_value=0;
    }
  }else{
    left_motor_pwm_port=0;
  }
}

void timer0() interrupt 1{
    TH0= 0XF8;      //1ms??
    TL0= 0X30;
    left_pwm_value++;
    right_pwm_value++;
    change_pwm_left();
    change_pwm_right();
}
