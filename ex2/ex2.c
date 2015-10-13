#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/* The period between sound samples, in clock cycles */
#define   SAMPLE_PERIOD   0

/* Declaration of peripheral setup functions */

void setupTimer();
void setupDAC();
void setupNVIC();
void setupGPIO();
void changeTopCounter(int sample_rate);
void initSound();


/* Your code will start executing here */
int main(void)
{
  /* Call the peripheral setup functions */
  setupGPIO();
  setupDAC();
  setupTimer(SAMPLE_PERIOD);

  /* Enable interrupt handling */
  setupNVIC();

  __asm("WFI"); /* Wait for interrupts */

  while(1){}

  return 0;
}

void setupNVIC()
{
*ISER0 = 0x4000802;

}
