#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#define CLOCK_FREQUENCY 14000000

/*
    TODO enable and set up the timer
    
    1. Enable clock to timer by setting bit 6 in CMU_HFPERCLKEN0
    2. Write the period to register TIMER1_TOP
    3. Enable timer interrupt generation by writing 1 to TIMER1_IEN
    4. Start the timer by writing 1 to TIMER1_CMD
    
    This will cause a timer interrupt to be generated every (period) cycles. Remember to configure the NVIC as well, otherwise the interrupt handler will not be invoked.
  */

/* We chose to use Low Energy Timer (LETIMER) instead of ordinary timer. In order to do that we had to do some changes
 * in the efm32gg.h, as it lacked a few addresses.
*/

/* Set up of the low energy timer. This function configures the timer with a sample rate of 32768
 */

void setupLowEnergyTimer(){	

	*CMU_OSCENCMD = (1 << 6);						/* Enable the low frequency oscillator */
	*CMU_HFCORECLKEN0 |= (1 << 4); 					/* Enable LE clock */
	*LETIMER0_CTRL |= (1 << 9); 					/* Set COMP0 as TOP register*/
	*CMU_LFACLKEN0 |= (1 << 2);		                /* Enable LOW energy timer 0 */
	*LETIMER0_TOP = 1;								/* Set TOP to 1 */
	*LETIMER0_IEN = 1;							    /* Enable interrupts */
	*LETIMER0_CMD = 1;								/* Start timer */ 

}

/* Changing the sample rate. Makes it possible for a tune play 8000Hz samples. */

void changeTopCounter(int sample_rate){
	*LETIMER0_TOP = 32768/sample_rate;
}

/* Function to disable the low energy timer. Used to save energy when the timer
 * is not needed. Reverse to setupLowEnergyTimer()
 */

void disableLowEnergyTimer(){
	*CMU_OSCENCMD &= ~(1 << 6);
	*CMU_HFCORECLKEN0 &= (1 << 4);
	*LETIMER0_CTRL &= (1 << 9);
	*CMU_LFACLKEN0 &= (1 << 2);
	*LETIMER0_TOP = 0;
	*LETIMER0_IEN = 0;
	*LETIMER0_CMD = 0;
}
