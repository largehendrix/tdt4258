#include "sounds.h"
#include "efm32gg.h"
#include <stdint.h>
#include <stdbool.h>
#include "sound_data.h"
#define SAMPLING_FREQUENCY 32768


/*Function prototypes*/
void setupLowEnergyTimer();
void disableLowEnergyTimer();
void changeTopCounter(int sampleRate);
void setupDAC();
void disableDAC();



/*Global variables*/
bool timer_running;  		/* Used to control whether the timer is running or not*/
int duration;        		/* Keeps track of wave length */
int notes_pos;		 		/* Keeps track of the position in the pre-sampled data */
int pos;             		/* Keeps track of the position in the cusomized samples */

int songlength;				/* Sample lenght */
int soundEffect;			/* Variable used to run sound samples for sound effects */
int counter=0;				/* Keeps track of time duration of tone */
bool iterate=false;         /* Set to true if tone has been played for a specified amount of time */


/* Set all variables to default */
void initSound(){
	duration=0;
	notes_pos=0;
	counter=0;
	pos=0;
	songlength=0;
	iterate=false;
	soundEffect = 0;
	changeTopCounter(SAMPLING_FREQUENCY);
}

/* Function for playing samples at 8000Hz.
 * The function pushes a sample every time it
 * is called. The samples are staticially
 * linked in sound_data.h. At the end of
 * the sample array the timer and DAC
 * are disabled.
 *
 */
void play_music(int size, int mode){
	int note = 0;

	if(mode == 1){
		note = (char)sounddata_data[notes_pos];
	}
	else if(mode == 2){
		note = (char)wilhelm[notes_pos];
	}
	else if(mode == 3){
		note = (char)xFiles[notes_pos];
	}
	else if(mode == 4){
		note = (char)humanMusic[notes_pos];
	}
	else if(mode == 5){
		note = (char)hoodini[notes_pos];
	}
	else if(mode == 6){
		note = (char)jump[notes_pos];
	}
	else if(mode == 7){
		note = (char)sword[notes_pos];
	}
	else if(mode == 8){
		note = (char)wasted[notes_pos];
	}



	*DAC0_CH0DATA = (note << 1);
	*DAC0_CH1DATA = (note << 1);

	if(notes_pos > size){
		notes_pos = 0;
		disableLowEnergyTimer();
		disableDAC();
		initSound();
	}

	notes_pos++;

}

/* Function to select melodies.
 * The function selects melodies based
 * on the button pushed. For selected
 * song the timer and DAC is enabled.
 * If a song is already playing. It
 * interrupt the song by disabling the
 * timer and DAC before it continues
 * selecting the new song.
 *
 */

void select_melodies(){

	switch((*GPIO_PC_DIN)){
		case 0xfe:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			soundEffect = 1;
			setupDAC();
			setupLowEnergyTimer();
			changeTopCounter(9000);
			songlength=396000;
			break;
		case 0xfd:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			soundEffect = 2;
			setupDAC();
			setupLowEnergyTimer();
			changeTopCounter(9000);
			songlength=8800;
			break;
		case 0xfb:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			soundEffect = 3;
			setupDAC();
			setupLowEnergyTimer();
			changeTopCounter(9000);
			songlength=75000;
			break;
		case 0xf7:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			soundEffect = 4;
			setupDAC();
			setupLowEnergyTimer();
			changeTopCounter(9000);
			songlength=11000;
			break;
		case 0xef:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			soundEffect = 5;
			setupDAC();
			setupLowEnergyTimer();
			changeTopCounter(9000);
			songlength=15900;
			break;
		case 0xdf:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			soundEffect = 6;
			setupDAC();
			setupLowEnergyTimer();
			changeTopCounter(9000);
			songlength=21900;
			break;
		case 0xbf:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			soundEffect = 7;
			setupDAC();
			setupLowEnergyTimer();
			changeTopCounter(9000);
			songlength=1800;
			break;
		case 0x7f:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			soundEffect = 8;
			setupDAC();
			setupLowEnergyTimer();
			changeTopCounter(9000);
			songlength=65000;
			break;
	}
}
