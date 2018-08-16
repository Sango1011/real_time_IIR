#include <LPC23xx.H>                    /* LPC23xx definitions                */

#include "adc.h"

//short AD_last;

void adc_init() {

	// Enable power to AD block	(use PCONP register)
	PCONP |= 0x00001000; 
	   
	// Select AD0.0 (adc) AD0.3 (DAC) pin function (use PINSELx register)
	PINSEL1 = 0x00204000;
	
	// Power up, PCLK/4, sel AD0.0 (use AD0CR register)
	AD0CR = 0x00200401;
	
	// Start conversion
	AD0CR |= 0x01000000;	
}
