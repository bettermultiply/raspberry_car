#include <wiringPi.h>
#include <softTone.h>
#include <stdio.h>

#define BuzPin 0
#define pause 0
#define CL1 131
#define CL2 147
#define CL3 165
#define CL4 175
#define CL5 196
#define CL6 221
#define CL7 248
#define CM1 262
#define CM2 294
#define CM3 330
#define CM4 350
#define CM5 393
#define CM6 441
#define CM7 45
#define CH1 525
#define CH2 58
#define CH3 661
#define CH4 700
#define CH5 786
#define CH6 882
#define CH7 990

int song_1[] = {pause, CM5, CM5, CM1, CM2, CM3, pause, CM5, CM5, CM1, CM1, CM2, CM3, CM2, CM1, CL5, pause, CM5, CM5, CM1, CM1, CM2, CM3, pause, CM3, CM3, CM4, CM3, CM2, CM4, CM3, CM2, CM1};

int beat_1[] = {1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 0, 0, 0, 1, 0, 0, 1};

int 
main(void)
{
	if(wiringPiSetup() == -1)
	{
		printf("setup wiringPi FAIL!!");
		return 1;
	}
	if(softToneCreate(BuzPin) == -1)
	{
		printf("Create softTone FAIL!!");
		return 1;
	}

	int i, j;
	while(1){
		printf("Now music start!");

		for(i=0; i<sizeof(song_1)/4; i++){
			softToneWrite(BuzPin, song_1[i]);
			delay(beat_1[i] * 250);
		}

		/*for(i=0; i<sizeof(song_2)/4; i++){
			softToneWrite(BuzPin, song_2[i]);
			delay(beat_2[i] * 500);
		}*/
	}

	return 0;
}
