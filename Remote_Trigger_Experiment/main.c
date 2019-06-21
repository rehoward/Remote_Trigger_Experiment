//Timing generator for remote triggering of ammonia sensors



#include "main.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT

  BCSCTL1 = CALBC1_1MHZ;		//DCO set to calibrated 1 MHz
  DCOCTL = CALDCO_1MHZ;			//DCO set to calibrated 1 MHz
  BCSCTL2 = 0x00;
  BCSCTL2 = DIVS_3 +DIVM_3;		//DCO is divided by 8, and sent to SMCLK

  //Goal is to wire 8 ports in parallel to power directly an ammonia sensor--30 mA
  P1DIR = 0xFF;										// Port 1 all set to output
  P1REN = 0x00;             						// Resistors disabled on inputs
  P1OUT = 0x00;  									// P1 set default low

  P2DIR = 0xFF;										// Port 2 all set to output
  P2REN = 0x00;										// Resistors disabled on inputs
  P2OUT = 0x00;										// P2 set default low

  P3DIR = 0x00;										// all P3 set to input
  P3REN = 0xFF;										// all P3 input resistors enabled
  P3OUT = 0x00;										// all P3 resistors set to pulldown
  



  while(1)
												//_delay_cycles(10000000) is 80 seconds
  {

			P1OUT = 0xFF;							//P1 set high.	Also lights LED P1.0
			P2OUT = 0xFF;							//P2.set high.
			_delay_cycles(ON_TIME);  //On time

			P1OUT = 0x00;					//P1 all low.	Also turns off LED
			P2OUT = 0x00;					//P2 all low.

			_delay_cycles(OFF_TIME);         //Off time
  }
}

