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
	pinMode(6, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(5, OUTPUT);
	softPwmCreate(1, 0, 100);
	softPwmCreate(4, 0, 100);
}

void run()
{
	digitalWrite(2,LOW);
	digitalWrite(5,LOW);
	softPwmWrite(4,speed);
	softPwmWrite(1,speed);
	digitalWrite(3,HIGH);
	digitalWrite(6,HIGH);
}

void brake()
{
	
	digitalWrite(1,0);
	digitalWrite(4,0);
	digitalWrite(3,0);
	digitalWrite(6,0);
}

void back()
{
	digitalWrite(3, LOW);
	digitalWrite(6, LOW);
	digitalWrite(1,HIGH);
	digitalWrite(4,HIGH);
	digitalWrite(2,HIGH);
	digitalWrite(5,HIGH);
	
	delay(4);
	digitalWrite(2, LOW);
	digitalWrite(5, LOW);
}

void left(int sp)
{
	back();
	digitalWrite(3, LOW);
	digitalWrite(5, LOW);
	digitalWrite(2,HIGH);
	digitalWrite(6, HIGH);
	softPwmWrite(1, speed*2);
	softPwmWrite(4,speed*2);
	delay(32);
}

void right(int sp)
{
	back();
	digitalWrite(2, LOW);
	digitalWrite(6, LOW);
	digitalWrite(5, HIGH);
	digitalWrite(3,HIGH);
	softPwmWrite(4,speed*2);
	softPwmWrite(1,speed*2);
	delay(48);
}

	
int
main(void)
{
	init();
	int turn_flag = 1;
	int turn=0;
	while(1){
		SR = digitalRead(RIGHT);	
		SL = digitalRead(LEFT);
		if(SL == LOW){
			if(SR==LOW){
				turn -= 2;
				if(turn < 0){
					turn = 0;
				}
			  	run();
			
			}
			else if(SR==HIGH){
				left(0);
				left(0);
				if(turn > 2){
					left(0);
					delay(32);	
					back();
				}
				turn++;
			}
		}else if(SL == HIGH){
			if(SR==LOW){
				right(0);
				right(0);
				if(turn > 2){
					right(0);
					delay(32);
					back();
				}
				turn++;
			}
			else if(SL == HIGH) brake();
		}
	}

	return 0;
}


