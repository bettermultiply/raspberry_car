#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <wiringPi.h>

#define LEFT 23
#define RIGHT 25
#define speed 50
#define max_mee
int SR, SL;

void
init()
{
	wiringPiSetup();
	pinMode(1, OUTPUT);
	pinMode(4, OUTPUT);
	//pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(5, OUTPUT);
	//pinMode(2, OUTPUT);
	//softPwmCreate(2, 0, 100);
	//softPwmCreate(3, 0, 100);
	softPwmCreate(1, 0, 100);
	softPwmCreate(4, 0, 100);
	//softPwmCreate(5, 0, 100);
	//softPwmCreate(6, 0, 100);
}

void run()
{
	//printf("run\n");
	softPwmWrite(4,speed);
	softPwmWrite(1,speed);
	digitalWrite(3,HIGH);
	digitalWrite(6,HIGH);
	digitalWrite(2,LOW);
	digitalWrite(5,LOW);
}

void brake()
{
	
	digitalWrite(1,0);
	digitalWrite(4,0);
	digitalWrite(3,0);
	digitalWrite(6,0);
}

void left(int sp)
{
	//softPwmWrite(3, 0);
	//digitalWrite(1,HIGH);
	//for(int i = 0;i < 10; i++)
	softPwmWrite(1, speed*2+10*sp);
	digitalWrite(2,HIGH);
	//digitalWrite(2, LOW);
	digitalWrite(6, HIGH);
	softPwmWrite(4,speed*2 + 10*sp);
	delay(32);
//digitalWrite(5, LOW);
	//softPwmWrite(6,speed*2);
}

void right(int sp)
{
	//softPwmWrite(6,0);
	//digitalWrite(4,HIGH);
	//digitalWrite(5,HIGH);
	softPwmWrite(4,speed*2+10*sp);
	digitalWrite(5, HIGH);
	digitalWrite(3,HIGH);
	softPwmWrite(1,speed*2 +10*sp);
	delay(32);
}

void back()
{
	digitalWrite(1,HIGH);
	digitalWrite(4,HIGH);
	digitalWrite(2,HIGH);
	digitalWrite(5,HIGH);
	
	delay(100);
	digitalWrite(2, LOW);
	digitalWrite(5, LOW);
}
	
int
main(void)
{
	init();
	//while(1){
	//	back();
	//}
	int turn_flag = 1;
	int sp=0;
	while(1){
		SR = digitalRead(RIGHT);	
		SL = digitalRead(LEFT);
		if(SL == LOW){
			if(SR==LOW){
				turn_flag = 1;
				sp=0;
			  	run();
			
			}
			else if(SR==HIGH){
				back();
				left(0);
				if(turn_flag&&sp <= 2){
					if(sp == 0){
						left(2);
						delay(32);
					}
					left(sp++);
					delay(32*((sp)));
					continue;
				}else if(turn_flag){
					left(sp-1);
					delay(32);
					turn_flag = 0;
				}
				sp=0;
				turn_flag = 1;;
				back();
			}
		}else if(SL == HIGH){
			if(SR==LOW){
				back();
				right(0);
				if(turn_flag&&sp<=2){
					if(sp == 0){
						right( 2);
						delay(32);
					}
					right(sp++);
					delay(32*((sp)));
					continue;
				}else if(turn_flag){
					right(sp-1);
					delay(32);
					turn_flag = 0;
				}
				sp=0;
				turn_flag = 1;
				back();
			}
			else if(SL == HIGH) brake();
		delay(20);
		}
	}

	return 0;
}


