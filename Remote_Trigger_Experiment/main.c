//Timing generator for remote triggering of ammonia sensors



#include "main.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT

  BCSCTL1 = CALBC1_1MHZ;		//DCO set to calibrated 1 MHz
  DCOCTL = CALDCO_1MHZ;			//DCO set to calibrated 1 MHz
  BCSCTL2 = 0x00;
  BCSCTL2 = DIVS_3 +DIVM_3;		//DCO is divided by 8, and sent to SMCLK

  
  P1DIR = 0xFF;										// Port 1 all set to output
  P1REN = 0x00;             						// Resistors disabled on inputs
  P1OUT = 0x00;           							// Port 1 all set low
		  	  	  	  	  	  	  	  	  	  	  	// P1.2 and P1.4 set high to provide a fixed trigger
		  	  	  	  	  	  	  	  	  	  	  	// All others set low.
		  	  	  	  	  	  	  	  	  	  	  	// P1.2/P1.3 and P1.4/P1.5 fixed high trigger.
  //P2DIR = (BIT0|BIT1|BIT4|BIT5);					// P2.0,P2.1,P2.4,P2.5 set to output. All others set to input
  P2DIR = 0xFF;										// Port 2 set to output
  P2REN = 0x00;										// Port 2 resistor disabled.
  P2OUT = 0x00;										// all P2 resistors set to pulldown and all outputs set low

  P3DIR = 0x00;										// all P3 set to input
  P3REN = 0xFF;										// all P3 input resistors enabled
  P3OUT = 0x00;										// all P3 resistors set to pulldown
  

  P2OUT &= ~BIT0;					//P2.0 low. Motor 2 off
  P1OUT &= ~BIT5;					//P1.5 UV LED 2 off
  P1OUT &= ~BIT6;					//Green board LED off

  P2OUT &= ~BIT2;					//P2.2 Low.  Turns off motor 1
  P2OUT &= ~BIT1;					//P2.1 low.  Turns off UV LED 1
  P1OUT &= ~BIT0;					//P1.0 low.  Turns off  red LED on board

  while(1)
												//_delay_cycles(10000000) is 80 seconds
  {
	  //System with two pump drivers and two UV LED drivers, as well as the indicator LEDs on the Launchpad itself.
	  //LEDs on the board are P1.0 and P1.6.
	  //Motor 1 (P2.2) on at the same time as UV LED 1 (P2.1) and red board LED (P1.0)
	  //Motor 2 (P2.0) on at the same time as UV LED 2 (P1.5) and green board LED (P1.6).

	  //Want on time for each UV LED to be 3 hours +/- 30 minutes  Cycle ends 1 hour before sunset and starts at sunrise.
	  //For this month, good enough is on at 7am and off at 4:45pm.

			P1OUT |= BIT0;					//P1.0 High. Lights red LED on board
			P2OUT |= BIT2;					//P2.2 High.  Turns on motor 1
			P2OUT |= BIT1;					//P2.1 High.  Turns on UV LED 1

			_delay_cycles(ON_TIME_ONE); 	//On time for Motor1 and UV LED 1

			P2OUT &= ~BIT2;					//P2.2 Low.  Turns off motor 1
			P2OUT &= ~BIT1;					//P2.1 low.  Turns off UV LED 1
			P1OUT &= ~BIT0;					//P1.0 low.  Turns off  red LED on board

			P1OUT |= BIT6;					//P1.6 High. Lights  green LED on board
			P2OUT |= BIT0;					//P2.0 High.  Turns on Motor 2
			P1OUT |= BIT5;					//P1.5 High.  Turns on UV LED 2

			_delay_cycles(ON_TIME_TWO); 		 //On time for Motor 2  UV LED 2

			P2OUT &= ~BIT0;					//P2.0 Low.  Turns off Motor 2
			P1OUT &= ~BIT5;					//P1.5 low.  Turns off UV LED 2
			P1OUT &= ~BIT6;					//P1.6 low.  Turns off green LED on board


  }
}

