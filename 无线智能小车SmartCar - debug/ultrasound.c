/**
*超声波模块的使用练习
*Trig接P2^0,Echo接P2^1
*/
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
#define ulong unsigned long
sbit trig=P2^0;
sbit echo=P2^1;

sbit dula=P2^6;
sbit wela=P2^7;

sbit feng=P2^3;

//lcd1602
sbit lcden=P3^4;//EN
sbit lcdrs=P3^5;//RS
sbit lcdrw=P3^6;//RW

uint successful;
uint count;//定时器溢出的次数
uint time;//echo输出的高电平持续的时间
ulong distance;
uint bai,shi,ge;
uchar code table[]="0123456789";
uchar code tips[]="DISTANCE:";
uchar code nothing[]="NOTHING GET";
//函数库
void delayms(uint);
void startModule();
void display(uchar);
void calculate_distance();
void ultrasound_module_init();
void timer1_init();
void write_data(uchar);
void write_com(uchar);
void lcd_show();
//
void delayms(uint time){
	uint x,y;
	for(x=time;x>0;x--)
	   for(y=110;y>0;y--);
}
void startModule(){
	trig=1;
	//delay_20us();//延时20us
		 _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  trig=0;
}
/*数码管显示
void display(uint b,uint s,uint g){
	delayms(5);
	dula=1;
	P0=table[b];
	dula=0;
	
	P0=0xff;
	wela=1;
	P0=0xfe;
	wela=0;
	delayms(5);
	
	dula=1;
	P0=table[s];
	dula=0;
	
	P0=0xff;
	wela=1;
	P0=0xfd;
	wela=0;
	delayms(5);
	
	dula=1;
	P0=table[g];
	dula=0;
	
	P0=0xff;
	wela=1;
	P0=0xfb;
	wela=0;
	delayms(5);
}*/
//LCD1602显示
void display(uchar dis){
	if(dis==0){
		uint num;
		for(num=0;num<11;num++){
			write_data(nothing[num]);
			delayms(5);
		}
  }else if(dis==1){
		if(distance<=10){
			feng=0;
		}else{
			feng=1;
		}
		bai=distance/100;
		shi=distance%100/10;
		ge=distance%100%10;
		write_data(table[bai]);
		write_data(table[shi]);
		write_data(table[ge]);
		write_data(' ');
		write_data('c');
		write_data('m');
  }
	
}
void calculate_distance(){
	time=TH1*256+TL1;//读出计时器中的值来计算距离
	time+=count*65536;
	//重新装入初值，计数
	TH1=0;
	TL1=0;
	distance=(time*1.7)/100;//单位是厘米
	if(distance>100 || successful==0){
		distance=0;//不接收数据
	}else{
		display(1);
	}
}
void ultrasound_module_init(){
	//trig echo都拉低电平
	trig=0;
	echo=0;
}
void timer1_init(){
	TMOD=0x10;//定时器1
	EA=1;
	TH1=0;
	TL1=0;
}

void lcd_init(){
	dula=0;
	wela=0;
	lcden=0;
	lcdrw=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}
void write_com(uchar com){
	lcdrs=0;
	//ledrw=0;
	P0=com;
	delayms(5);
	lcden=1;
	delayms(5);
	lcden=0;
}
void write_data(uchar dat){
	lcdrs=1;
	//ledrw=0;
	P0=dat;
	delayms(5);
	lcden=1;
	delayms(5);
	lcden=0;
}
void lcd_show(){
	uint num;
	write_com(0x80);
	for(num=0;num<9;num++){
		write_data(tips[num]);
		delayms(5);
	}
}

void main(){
	lcd_init();
	successful=0;
	ultrasound_module_init();
	timer1_init();
	//echo从低电平变成了高电平，接下来根据高电平持续的时间来计算距离
	//echo高电平持续时间和距离成正比
	while(1){
		//开始送20us高电平
		lcd_show();
	  startModule();
		while(!echo);//等待高电平来临，启动计时器
		TR1=1;
		while(echo);//等待高电平结束，关闭计时器
		TR1=0;
		successful=1;//高电平输出完成，成功
		calculate_distance();//计算距离
		delayms(10);//延时10ms再进行下次测距
	}
}
//中断服务程序
void timer1() interrupt 1{
	count++;
	TH1=0;
	TL1=0;
}