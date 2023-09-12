#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <arpa/inet.h>

#include <wiringPi.h>
#include <softPwm.h>

#define BUFSIZE 512
#define PWMA 1
#define AIN2 2 
#define AIN1 3
#define PWMB 4
#define BIN2 5
#define BIN1 6

void
init()
{
	wiringPiSetup();
	for(int i=0; i<=6; i++){
		//PWMA to BIN1 is 1 to 6;
	       pinMode(i, OUTPUT);	
	}
	softPwmCreate(PWMA, 0, 100);
	softPwmCreate(PWMB, 0, 100);
}

int 
main(int argc, char* argv[])
{
	init();
	while(1){
		break;
	}
	return 0;
}
