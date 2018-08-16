/*********************************************************************
*  Code for routines for handing interupts                           *
*  Written for MCB2300 board 										 *
*  (Fall 2013)
*********************************************************************/
#include <LPC23xx.H>                    /* LPC23xx definitions                */
#include "EINT0.h"
#include "Keypad.h"
#include "LED.h"

/*******************************************************************************/
int signal;							  /* variable signal interrupt has been serviced */
int key_flag;
/*******************************************************************************/

extern void EINT0_init (void)
{
	PINSEL4 |= 1 << 20;					//change pin P2.10 function to EINT0
	EXTMODE = 0;								//EXTMODE is level-sensitve
	EXTPOLAR = 0;							//EXTPOLAR0 is low-active
	VICVectAddr14 = (unsigned long) EINT0_IRQHandler;		//points to EINT0 handler
	VICVectCntl0 = 0;					//set priority to 0
	VICIntEnable |= 0x00004000;
	signal = 0;
}
	

/* EINT0 IRQ: executed when P2.10 connected to GND                             */
__irq void EINT0_IRQHandler (void) {
	
	EXTINT      = 1;        /* Clear interrupt flag */
  VICVectAddr = 0;        /* Acknowledge Interrupt */
	get_key();
	signal = 1; 
	key_flag = 1;
}
