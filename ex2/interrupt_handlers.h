#ifndef INTERRUPT_HANDLERS_H_
#define INTERRUPT_HANDLERS_H_

void __attribute__ ((interrupt)) TIMER1_IRQHandler();

void GPIO_Handler();

void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler();

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()

#endif
