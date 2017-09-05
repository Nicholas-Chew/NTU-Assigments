//************************************************
//   Blink_LED.c CE2007’s Lab #2 sample program
//   This program blinks the LEDs on the DE0 board
//
//************************************************
#include <stdint.h>                                // for ISO C99 data type declaration

#define DE0_LEDs		  *((uint32_t *)(0xA0000000))  // Address of LEDs on DE0 (lowest 10 bits)
#define DE0_SLIDE_SW	  *((volatile uint32_t *)(0xA0001000))  // Address of LEDs on DE0 (lowest 10 bits)
#define DE0_7SEG_DISP	  *((volatile uint32_t *) (0xA0004000)) //Address of 7 Seg Disp

int main (void){ 
int32_t i ;	
uint8_t sevenSegCode[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};

  while(1) {
		DE0_7SEG_DISP= sevenSegCode[DE0_SLIDE_SW];   
		DE0_LEDs=0x155|DE0_SLIDE_SW;                   // turn on all LEDs 
		for (i=0;i<0x1FFFFF;i++);         // delay
		
		DE0_7SEG_DISP= sevenSegCode[DE0_SLIDE_SW];  
		DE0_LEDs=0x2AA|DE0_SLIDE_SW;                   // turn off all LEDs
		for (i=0;i<0x1FFFFF;i++);         // delay     
	}
}

