/* main program 
	written by Sarah Ngo
	August 2017 */
	
#include <stdio.h>
#include <LPC23xx.H>                    /* LPC23xx definitions */

#include "Timer.h"
//#include "Uart1Tx.h"
#include "adc.h"

#define N_IIR 5		//number of coefficients

int main ()
{
//	char value[10];
//	short LED = 0x00;
	float data [N_IIR] = {0.0};		//array to store the inputs
	int i, k;  
	float result = 0;
	float NumCoeff[N_IIR]={0.0000954, 0.0002863, 0.0002863, 0.0000954};
	float DenCoeff[N_IIR]={1.0, -2.8116, 2.6405, -0.8281};
	float output[N_IIR] = {0.0};		//stores the output values
		
	//initializtions
	adc_init();	
	Timer1_Init();
//	Uart1_init();
	
	T1TCR = 0x02;			//reset timer counter
	Timer1_SetMR0(1150);		//match register gives sampling freq
	TIMER1_ENABLE;				//Start timer
	
while(1)
 {
			if (getInterruptFlag() == 1)
			{		
				clearInterruptFlag();
				
				data[0] = getAD_last();	//storing into an array	with position 0 always the newest value
				output[0] = 0;
				
					for (result = 0, i = 0; i < N_IIR; i++)
					{
						//filtering
						result += NumCoeff[i]*data[i]; 
						result -= DenCoeff[i]*output[i];		
					}
				output[0] = result;		//sotre filtered result
				result += 1500;	
				DACR = (result);  //send the value to the dac

				for (k = N_IIR - 1; k > 0; k--)
				{
					//shift the values so the newest is always at position 0
					data[k] = data[k-1];		
					output[k] = output[k-1]; 
				}
			}
	}
}
