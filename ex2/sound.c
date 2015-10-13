#include "sound.h"
#include "efm32gg.h"
#include <stdint.h>
#include <stdbool.h>
#include "sound_data.h"

#define SAMPLING_FREQUENCY 32768


/*Function prototypes*/
void setupTimer();
void disableTimer();
int convert_from_ms(int millis);
void changeTopCounter(int sampleRate);
void setupDAC();
void disableDAC();



/*Global variables*/
bool timer_running;  		/* Used to control whether the timer is running or not*/
int duration;        		/* Keeps track of wave length */
int notes_pos;		 		/* Keeps track of the position in the pre-sampled data */
int pos;             		/* Keeps track of the position in the cusomized samples */

struct tone *sampleArray;   /* The sampleArray pased used in the playSong function */
int songlength;				/* Sample lenght */
int runBattlefield;			/* Variable used to run the battlefield intro */

bool iterate=false;         /* Set to true if tone has been played for a specified amount of time */
int counter=0;				/* Keeps track of time duration of tone */


/* Set all variables to default */
void initSound(){
	duration=0;
	notes_pos=0;
	counter=0;
	pos=0;
	songlength=0;
	iterate=false;
	runBattlefield = 0;
	changeTopCounter(SAMPLING_FREQUENCY);
}

/*
Function to play a note for a specified amount of milliseconds
*/
void playNotes(int note, int time){
	int cycles = convert_from_ms(time); //Cycle variable corresponds to amount of milliseconds specified in time-variable

	int sampling=PERIOD/note; //Create correct number of samples per waveform based on the number of samples per second


	/* if-else to transition between high and low */
	if(sampling/2>=duration){
		*DAC0_CH0DATA=2000;
		*DAC0_CH1DATA=2000;
	}
	else{
		*DAC0_CH0DATA=-2000;
		*DAC0_CH1DATA=-2000;
	}
	duration++;

	/* Reset duration if end of period */
	if(duration>=sampling){
		duration=0;
	}
	counter++;
	if(counter==cycles){
		iterate=true; //Iterate to next note if the current note has played for specified amount of time
	    counter=0;
	}
}
/* The function converts milliseconds
 * to the corresponding number of cycles.
 *
 */

int convert_from_ms(int millis){
	return millis * 15;
}

/* Function for playing samples.
 * Based on the sample array, and
 * the current postion in the sample
 * it calls the playNotes() function.
 * When end of the samples are reached
 * the function disables the timer
 * and the DAC.
 *
 */

void playSong(struct tone melody[], int size){

	playNotes(melody[pos].note, melody[pos].time);

	if(iterate==true){
        pos++;
        iterate=false;
	}
	else if(pos >= size){
		disableTimer();
		disableDAC();
		timer_running = false;
		initSound();
	 }
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
				disableTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			setupDAC();
			setupTimer();
			sampleArray=mario;
			songlength=215;
			break;
		case 0xfd:
			if(timer_running){
				disableTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			setupDAC();
			setupTimer();
			sampleArray=hit_received;
			songlength=36;
			break;
		case 0xfb:
			if(timer_running){
				disableTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			setupDAC();
			setupTimer();
			sampleArray=hit_dealt;
			songlength=41;
			break;
		case 0xf7:
			if(timer_running){
				disableTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			setupDAC();
			setupTimer();
			sampleArray=shoot;
			songlength=15;
			break;
		case 0xef:
			if(timer_running){
				disableTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			runBattlefield = 1;
			setupDAC();
			setupTimer();
			changeTopCounter(8000);
			songlength=396000;
			break;
		case 0xdf:
			if(timer_running){
				disableTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			setupDAC();
			setupTimer();
			sampleArray=beep1;
			songlength=1;
			break;
		case 0xbf:
			if(timer_running){
				disableTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			setupDAC();
			setupTimer();
			sampleArray=beep2;
			songlength=1;
			break;
		case 0x7f:
			if(timer_running){
				disableTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			setupDAC();
			setupTimer();
			sampleArray=beep3;
			songlength=1;
			break;
	}
}
