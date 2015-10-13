#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "gpio.h"

/* function to set up GPIO mode and interrupts*/
void setupGPIO()
{
  /* TODO set input and output pins for the joystick */

  CMU_periClockEnable(CMU_GPIO, true);
  GPIO_IRQsetupRange(GPIO_portC, 0, 7, false, true, true);

  // LED setup
  GPIO_portSetupRange(GPIO_portA, 8, 15, GPIO_PUSHPULLDRIVE);
  GPIO_driveStrength(GPIO_portA, GPIO_HIGH);

  // Button setup
  GPIO_portSetupRange(GPIO_portC, 0, 7, GPIO_INPUTPULLFILTER);
  *GPIO_PC_DOUT = 0xFF; // pull-up

  NVIC_IRQenable(IRQ_GPIO_EVEN, true);
  NVIC_IRQenable(IRQ_GPIO_ODD, true);

  /* Example of HW access from C code: turn on joystick LEDs D4-D8
     check efm32gg.h for other useful register definitions
  */
  *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO; /* enable GPIO clock*/
  *GPIO_PA_CTRL = 2;  /* set high drive strength */
  *GPIO_PA_MODEH = 0x55555555; /* set pins A8-15 as output */
  *GPIO_PA_DOUT = 0x0700; /* turn on LEDs D4-D8 (LEDs are active low) */

  *GPIO_EXTIPSELL = 0x22222222; /*enable interrupts*/
  *GPIO_EXTIFALL = 0xff; /*set up for falling edge*/
  *GPIO_EXTIRISE = 0xff; /* set up for rising edge*/
  *GPIO_IEN = 0xff; /*enable interrupt generation*/

  /*Deepsleep mode*/
  *SCR = 6;
}
