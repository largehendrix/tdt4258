#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/*
  TODO calculate the appropriate sample period for the sound wave(s)
  you want to generate. The core clock (which the timer clock is derived
  from) runs at 14 MHz by default. Also remember that the timer counter
  registers are 16 bits.
*/
/* The period between sound samples, in clock cycles */
#define SAMPLE_PERIOD 32748

/* Declaration of peripheral setup functions */
void setupTimer(uint32_t period);
void setupDAC();
void setupNVIC();
void setupLowEnergyTimer();
void setupGPIO();
void changeTopCounter(int sample_rate);
void initSound();

/* Your code will start executing here */
int main(void) {
  /* Call the peripheral setup functions */
	initSound(); /* Reset every global variable at reset */
  setupGPIO();

	/* These functions are called when needed. E.g when we play tunes. See
	 * sounds.c:selectMelodies() */
	//setupDAC();
  //setupLowEnergyTimer();
  //setupTimer(48000);

  /* Enable interrupt handling */
 	setupNVIC();
 
  /* TODO for higher energy efficiency, sleep while waiting for interrupts
     instead of infinite loop for busy-waiting
  */

 	*SCR = 6;
  __asm("WFI");

  	while(1){}

  	return 0;
}

void setupNVIC()
{
  /* TODO use the NVIC ISERx registers to enable handling of interrupt(s)
     remember two things are necessary for interrupt handling:
      - the peripheral must generate an interrupt signal
      - the NVIC must be configured to make the CPU handle the signal
     You will need TIMER1, GPIO odd and GPIO even interrupt handling for this
     assignment.
  */
	 *ISER0 = 0x4000802;
}
