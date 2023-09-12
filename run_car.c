#include<wiringPi.h>
#include<stdio.h>
#include<stdlib.h>
//#include<conio.h>

#define GPIO1 1
#define GPIO2 2
#define GPIO3 3
#define GPIO4 4
#define GPIO5 5
#define GPIO6 6
#define fore 1
#define back 2
#define left 3
#define right 4

enum keys {UP='k', LEFT='h', RIGHT='l', DOWN='j', END='q'};

void
init_pin()
{
	pinMode(GPIO1, OUTPUT);
	pinMode(GPIO2, OUTPUT);
	pinMode(GPIO3, OUTPUT);
	pinMode(GPIO4, OUTPUT);
	pinMode(GPIO5, OUTPUT);
	pinMode(GPIO6, OUTPUT);
}

void
run(int signal)
{
	if(signal > 0 && signal < 5){
		digitalWrite(GPIO1, HIGH);
		digitalWrite(GPIO4, HIGH);
		if(signal == fore){
			digitalWrite(GPIO3, HIGH);
			digitalWrite(GPIO6, HIGH);
		}else if(signal == back){
			digitalWrite(GPIO2, HIGH);
			digitalWrite(GPIO5, HIGH);
		}else if(signal  == right){
			digitalWrite(GPIO3, HIGH);
		}else if(signal == left){
			digitalWrite(GPIO6, HIGH);
		}
	}
		
}

void
stop()
{
	int signal = 0;
	do{
		signal++;
		digitalWrite(signal, LOW);
	}while(signal < 6);
}



int 
main(void)
{
	if(wiringPiSetup() == -1)
	{
		return 1;
	}
	init_pin();
	system("/bin/stty raw");
	char ch = 0;
	while(1){
		ch = getchar();
		int signal = 0;
		//	printf("%d", c);
		switch(ch)
		{
			case UP:
				signal = fore;	
				break;
			case DOWN:
				signal = back;
				break;
			case LEFT:
				signal = left;
				break;
			case RIGHT:
				signal = right;
				break;
			case END:
				goto end;
				break;
		}
		run(signal);
		delay(100);
		stop();
	}
/*
	digitalWrite(GPIO1, HIGH);
	digitalWrite(GPIO2, HIGH);
	digitalWrite(GPIO4, HIGH);
	digitalWrite(GPIO5, HIGH);
	delay(1 * 500);
	digitalWrite(GPIO4, LOW);
	digitalWrite(GPIO5, LOW);
	digitalWrite(GPIO1, LOW);
	digitalWrite(GPIO2, LOW);
*/
end:
	printf('\n');
	system("/bin/stty cooked");
	return 0;
}
