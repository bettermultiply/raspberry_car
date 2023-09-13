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
	softPwmCreate(1, 0, 100);
	softPwmCreate(4, 0, 100);
	digitalWrite(3, HIGH);
	digitalWrite(6, HIGH);
}

void run()
{
	digitalWrite(3, HIGH);
	digitalWrite(6, HIGH);
	softPwmWrite(4,speed*2);
	softPwmWrite(1,speed*2);
}

void brake()
{
	
	digitalWrite(1, LOW);
	digitalWrite(4, LOW);
	digitalWrite(3, LOW);
	digitalWrite(6, LOW);
}

void left(int sp)
{
	softPwmWrite(1,speed*0.5 + 10*sp);
	softPwmWrite(4, speed*2);
	delay(32);
}

void right(int sp)
{
	softPwmWrite(4,speed*0.4 + 5*sp);
	softPwmWrite(1,speed*2 );
	delay(32);
}

int
main(void)
{
	init();
	int sp = 0;
	while(1){
		SR = digitalRead(RIGHT);	
		SL = digitalRead(LEFT);
		if(SL == LOW){
			if(SR==LOW){
			  	run();
			
			}
			else if(SR==HIGH){
				left(sp);
				sp++;
			}
		}else if(SL == HIGH){
			if(SR==LOW){
				right(sp);
				sp++;
			}
			else if(SL == HIGH){ 
				brake();
				break;
			}
		}
	}

	return 0;
}


