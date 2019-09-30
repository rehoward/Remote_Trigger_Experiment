//Timing generator for remote triggering of ammonia sensors
	  //System with two pump drivers and two UV LED drivers, as well as the indicator LEDs on the Launchpad itself.
	  //LEDs on the board are P1.0 and P1.6.
	  //Pump 1 (P2.2) on at the same time as UV LED 1 (P2.1) and red board LED (P1.0)
	  //Pump 2 (P2.0) on at the same time as UV LED 2 (P1.5) and green board LED (P1.6).

	  //Want on time for each UV LED to be 3 hours +/- 30 minutes  Will use light sensor to turn on and off.
	  //CdS photoresistor.  Dark over 100K, direct sun cloudy 140 ohms, deep shade 2K ohms.
	  //Will start with 5K ohms as good threshold.
	  //Set P2.5 high, 4.7K to P2.4 and sensor to P2.4 to P2.3 (set low)
	  // Pump 2 25mL/minute level


#include "main.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT

  BCSCTL1 = CALBC1_1MHZ;		//DCO set to calibrated 1 MHz
  DCOCTL = CALDCO_1MHZ;			//DCO set to calibrated 1 MHz
  BCSCTL2 = DIVM_3 + DIVS_3;		//Set MCLK and SMCLK to DCOCLK.  MCLK and SMCLK divide by 8;


  
  P1DIR = ~BIT2;									// Port 1 all set to output except P1.2 set to input for light sensor
  P1REN = 0x00;             						// Resistors disabled on inputs
  P1OUT = 0x00;           							// Port 1 all set low

  P2DIR = ~BIT4;									// Port 2 set to output except P2.4 set to input for light sensor
  P2REN = BIT4;										// Port 2 resistor disabled except for P2.4.
  P2OUT = BIT5;								// all P2 resistors set to pulldown and all outputs set low
  	  	  	  	  	  	  	  	  	  	  	  	  	// except P2.5 which is Vcc to light sensor
  	  	  	  	  	  	  	  	  	  	  	  	  	//P2.3 stays low as Vdd for light sensor

  P3DIR = 0x00;										// all P3 set to input.  P3 not used
  P3REN = 0xFF;										// all P3 input resistors enabled
  P3OUT = 0x00;										// all P3 resistors set to pulldown
  

  while(1)

  {


	  	    if(P2IN & BIT4)	{						//Check is P2.4 is high => not dark.
				P1OUT |= BIT0;						//If light, turn on red LED P1.0
				_delay_cycles( ONE_SECOND);
				P1OUT &= ~BIT0;
				_delay_cycles( ONE_SECOND);
				P1OUT |= BIT0;
			}
			else{
				P1OUT &= ~BIT0;
			}
	  	  /*
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

 */ }
}

