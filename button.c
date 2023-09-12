#include <wiringPi.h>
#include <stdio.h>

#define Gpin 21
#define Rpin 22
#define BtnPin 24

void
pininit(void){
	pinMode(Gpin, OUTPUT);
	pinMode(Rpin, OUTPUT);
	pinMode(BtnPin, INPUT);

	digitalWrite(Gpin, HIGH);	
	digitalWrite(Rpin, LOW);
}

void
LED(char* color)
{
	if(color == "RED"){
		digitalWrite(Rpin, HIGH);
		digitalWrite(Gpin, LOW);
	}else if(color == "GREEN"){
		digitalWrite(Rpin, LOW);
		digitalWrite(Gpin, HIGH);
	}else{
		printf("color ERROR");
	}
}

int
main(void)
{
	int status = 0, prestatus = 0;
	if(wiringPiSetup() == -1){
	       printf("setup wiringPi FAIL!!");
       		return 1;
	}
	pininit();
	prestatus = digitalRead(BtnPin);
	while(1){
		status = digitalRead(BtnPin);
		delay(10);
		if(prestatus == status){
			if(status == 0){
				LED("RED");
			}else if(status == 1){
				LED("GREEN");
			}
		}     	
		prestatus = status;
	}
	return 0;
}	
