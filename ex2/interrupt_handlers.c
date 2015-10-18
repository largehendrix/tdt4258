#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sounds.h"

extern struct tone *sampleArray;
extern int songlength;
extern int runBattlefield;

void disableLowEnergyTimer();
void disableDAC();

/* Low Energy Timer interrupt handler */
/* Called every time interrupt is pushed*/

void __attribute__ ((interrupt)) LETIMER0_IRQHandler()
{
	/*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
    */
	*LETIMER0_IFC = 1;

	/* Feed new samples to the DAC */
	if(runBattlefield){
		play_music(songlength, runBattlefield);
	}
}

/* GPIO even pin interrupt handler */
/* Calls a function that selects a melody. Depending on button pushed different sound will be played. */

void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	/* TODO handle button pressed event, remember to clear pending interrupt */
	select_melodies();
	*GPIO_IFC = 0xff;
	*GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);
}

/* GPIO odd pin interrupt handler */
/* Calls a function that selects a melody. Depending on button pushed different sound will be played. */

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	/* TODO handle button pressed event, remember to clear pending interrupt */
	*GPIO_IFC = 0xff;
	select_melodies();
	*GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);
}
