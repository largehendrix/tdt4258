#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sound.h"
//Include rest of music functions from other c file

extern struct tone *sampleArray;
extern int songlength;

void __attribute__ ((interrupt)) LETIMER0_IRQHandler(){

	*LETIMER0_IFC = 1;

	/* Feed new samples to the DAC */
		playSong(sampleArray, songlength);


}

void GPIO_Handler() {

    switch((*GPIO_PC_DIN)){
  		case 0xfe:
  			if(timer_running){
  				disableLowEnergyTimer();
  				disableDAC();
  				initSound();
  			}
  			timer_running = true;
  			setupDAC();
  			setupLowEnergyTimer();
  			sampleArray=mario;
  			songlength=215;
  			break;
  		case 0xfd:
  			if(timer_running){
  				disableLowEnergyTimer();
  				disableDAC();
  				initSound();
  			}
  			timer_running = true;
  			setupDAC();
  			setupLowEnergyTimer();
  			sampleArray=hit_received;
  			songlength=36;
  			break;
  		case 0xfb:
  			if(timer_running){
  				disableLowEnergyTimer();
  				disableDAC();
  				initSound();
  			}
  			timer_running = true;
  			setupDAC();
  			setupLowEnergyTimer();
  			sampleArray=hit_dealt;
  			songlength=41;
  			break;
  		case 0xf7:
  			if(timer_running){
  				disableLowEnergyTimer();
  				disableDAC();
  				initSound();
  			}
  			timer_running = true;
  			setupDAC();
  			setupLowEnergyTimer();
  			sampleArray=shoot;
  			songlength=15;
  			break;
  		case 0xef:
  			if(timer_running){
  				disableLowEnergyTimer();
  				disableDAC();
  				initSound();
  			}
  			timer_running = true;
  			runBattlefield = 1;
  			setupDAC();
  			setupLowEnergyTimer();
  			changeTopCounter(8000);
  			songlength=396000;
  			break;
  		case 0xdf:
  			if(timer_running){
  				disableLowEnergyTimer();
  				disableDAC();
  				initSound();
  			}
  			timer_running = true;
  			setupDAC();
  			setupLowEnergyTimer();
  			sampleArray=beep1;
  			songlength=1;
  			break;
  		case 0xbf:
  			if(timer_running){
  				disableLowEnergyTimer();
  				disableDAC();
  				initSound();
  			}
  			timer_running = true;
  			setupDAC();
  			setupLowEnergyTimer();
  			sampleArray=beep2;
  			songlength=1;
  			break;
  		case 0x7f:
  			if(timer_running){
  				disableLowEnergyTimer();
  				disableDAC();
  				initSound();
  			}
  			timer_running = true;
  			setupDAC();
  			setupLowEnergyTimer();
  			sampleArray=beep3;
  			songlength=1;
  			break;
  	}

}

void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() {
    GPIO_Handler();
}

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() {
    GPIO_Handler();
}
