//************************************************
//	 ToneGen.c      CE2007's Lab #2 sample program
//   This program generates a saw tooth waveform 
//   in the audible range on DAC-A.
// 
//   School of Computer Engineering
//   Nanyang Technological University, Singapore
//************************************************
#include <stdint.h>
#define DAC_A				    *((volatile uint16_t *)(0x80000050))   // address of DAC-A
#define DE0_SLIDE_SW		*((volatile uint32_t *)(0xA0001000))   // address of slide switch
#define DE0_LEDs			  *((volatile uint32_t *)(0xA0000000))   // address of LEDs

void main (void){  
int16_t countD;
int32_t i;
  while (1) {

		if (DE0_SLIDE_SW & 1<<0) {       // controlled by slide switch  0
		   //Going up
		   for (countD = 0; countD < 16; countD++){
  		     DAC_A = countD;
		   //Delay is change to 200, same frequency as 'saw tooth'
      	   for(i = 0; i < 200; i++);			
		   }
		   //Going down
		   for (countD = 15; countD > 0; countD--){
  		     DAC_A = countD;
      	   for(i = 0; i < 200; i++);  
		   }  
		   
		}
    else if (DE0_SLIDE_SW ==0 ) {          // no slide switch is activated
			 DE0_LEDs = DE0_LEDs^(1<<8);    // blink LED
		   for (i=0;i<0x1FFFFF;i++);      // delay
		}
  }
}
