#include<wiringPi.h>
#define Gpin 21
#define Rpin 22

void led_init(void);
void led_on_color(int);
void led_off_color(int);

int
main(int argc, char* argv[])
{
	wiringPiSetup();
	led_init();
	int n = 0;
	int color=0;
	while(1)
	{
		color = n%2 ? Gpin : Rpin;		
		led_on_color(color);
		delay(50);
		led_off_color(color);
		delay(50);
		n++;
	}

	return 0;
}

void
led_init(void)
{
	pinMode(Gpin, OUTPUT);
	pinMode(Rpin, OUTPUT);
}

void 
led_on(void)
{
	digitalWrite(Gpin, HIGH);
	digitalWrite(Rpin, HIGH);
}

void
led_off(void)
{
	digitalWrite(Gpin, LOW);
	digitalWrite(Rpin, LOW);
}

void
led_off_color(int color)
{
	digitalWrite(color, LOW);
}

void
led_on_color(int color)
{
	digitalWrite(color, HIGH);
}
