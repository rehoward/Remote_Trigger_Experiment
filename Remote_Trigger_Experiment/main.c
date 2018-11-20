//Timing generator for remote triggering of ammonia sensors


#include <msp430g2553.h>
#include <msp430.h> 

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT

  BCSCTL1 = CALBC1_1MHZ;		//DCO set to calibrated 1 MHz
  DCOCTL = CALDCO_1MHZ;			//DCO set to calibrated 1 MHz
  BCSCTL2 = 0x00;
  BCSCTL2 = DIVS_3 +DIVM_3;		//DCO is divided by 8, and sent to SMCLK

  
  P1DIR = 0xFF;										// Port 1 all set to output
  P1REN = 0x00;             						// Resistors disabled on inputs
  P1OUT = (BIT2|BIT4);           					// P1.0 and P1.6 set default low for programmable external trigger
		  	  	  	  	  	  	  	  	  	  	  	// P1.2 and P1.4 set high to provide a fixed trigger
		  	  	  	  	  	  	  	  	  	  	  	// All others set low.
		  	  	  	  	  	  	  	  	  	  	  	// P1.2/P1.3 and P1.4/P1.5 fixed high trigger.
  P2DIR = (BIT0|BIT1|BIT4|BIT5);					// P2.0,P2.1,P2.4,P2.5 set to output. All others set to input
  P2REN = (BIT2|BIT3|BIT6|BIT7);					// P2.2,P2.3,P2.6,P2.7 resistors enabled
  P2OUT = 0x00;										// all P2 resistors set to pulldown and all outputs set low
  	  	  	  	  	  	  	  	  	  	  	  	  	// P2.0/P2.1 and P2.4/P2.5 provide a fixed low trigger.
  P3DIR = 0x00;										// all P3 set to input
  P3REN = 0xFF;										// all P3 input resistors enabled
  P3OUT = 0x00;										// all P3 resistors set to pulldown
  
#define TENTH_SECOND  12500
#define ONE_SECOND  125000
#define ONE_HOUR    450000000


  while(1)
												//_delay_cycles(10000000) is 80 seconds
  {

			P1OUT |= BIT0;					//P1.0 High and P1.1 low.	Also lights LED
			_delay_cycles(TENTH_SECOND);	//delay cycle for P1.6/P1.7 to prevent packet collisions.
			P1OUT |= BIT6;					//P1.6 High and P1.7 low.	Also lights LED
			_delay_cycles(100*ONE_SECOND);  //On time

			P1OUT &= ~BIT0;					//P1.0 low and P1.1 low.	Also turns off LED
			_delay_cycles(TENTH_SECOND);	//delay cycle for P1.6/P1.7 to prevent packet collisions.
			P1OUT &= ~BIT6;					//P1.6 low and P1.7 low.	Also turns off LED

			_delay_cycles(ONE_HOUR);         //Off time
  }
}

