//Timing generator for bee feeding apparatus.

	//System with two feeding pumps, two UV LEDs, the indicators on the LaunchPad, light sensor, and a wash pump.

	//LEDs on the board are P1.0 and P1.6.
	//Pump1 (P2.2) on at the same time as UVLED1 (P2.1) and red board LED (P1.0)
	//Pump2 (P2.0) on at the same time as UVLED2 (P1.5) and green board LED (P1.6).
	//WashPump (P1.4) on after each feeding pump cycle and both red and green board LEDs
	//Want on time for each UV LED to be 3 hours +/- 30 minutes.
		//time is varied to preclude bees learning pattern
		//feeding pump is on for a fixed time at the beginning of the on-time cycle.
		// Pump 2 25mL/minute

	//Will use light sensor to gate feeding cycle so no activity at night.
		//Check at the start of each feeding cycle--if light do whole cycle, else wait DARK_CHECK and skip to next cycle
		//CdS photoresistor.  Dark over 100K, direct sun cloudy 140 ohms, deep shade 2K ohms.
		//Will start with 5K ohms as good threshold.
		//Set P2.5 high, 4.7K to P2.4 and sensor to P2.4 to P2.3 (set low)

	//Basic cycle
		//Power up reset followed by timing cycle to prime all 3 pumps for PRIME_TIME

		//Pump1, UVLED1, and red LED turned on.
		//Pump1 turned off after FEEDING_TIME
		//UVLED1 and red LED turned off after ON_TIME_ONE.
		//WashPump and both board LEDs turned on for WASH_TIME.
		//
		//Pump2, UVLED2, and green LED turned on.
		//Pump2 turned off after FEEDING_TIME
		//UVLED2 and green LED turned off after ON_TIME_TWO.
		//WashPump and both board LEDs turned on for WASH_TIME.

		//Pump 1, UV LED 1, and red LED turned on.
		//Pump 1 turned off after FEEDING_TIME
		//UV LED1 and red LED turned off after ON_TIME_THREE.
		//Wash pump and both board LEDs turned on for WASH_TIME.

		//Pump 2, UV LED 2, and green LED turned on.
		//Pump 2 turned off after FEEDING_TIME
		//UV LE21 and green LED turned off after ON_TIME_FOUR.
		//Wash pump and both board LEDs turned on for WASH_TIME.
		//
		//Pump 1, UV LED 1, and red LED turned on.
		//Pump 1 turned off after FEEDING_TIME
		//UV LED1 and red LED turned off after ON_TIME_FIVE.
		//Wash pump and both board LEDs turned on for WASH_TIME.

		//Pump 2, UV LED 2, and green LED turned on.
		//Pump 2 turned off after FEEDING_TIME
		//UV LED2 and green LED turned off after ON_TIME_SIX.
		//Wash pump and both board LEDs turned on for WASH_TIME.


#include "main.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;		// Stop WDT

  BCSCTL1 = CALBC1_1MHZ;		//DCO set to calibrated 1 MHz
  DCOCTL = CALDCO_1MHZ;			//DCO set to calibrated 1 MHz
  BCSCTL2 = DIVM_3 + DIVS_3;	//Set MCLK and SMCLK to DCOCLK.  MCLK and SMCLK divide by 8;
  
  P1DIR = 0xFF;				// Port 1 all set to output except P2.4 set to input for light sensor
  P1REN = 0x00;				// Resistors disabled on inputs
  P1OUT = 0x00;				// Port 1 all set low

  P2DIR = ~BIT4;			// Port 2 set to output except P2.4 set to input for light sensor
  P2REN = BIT4;				// Port 2 resistor disabled except for P2.4 for light sensor.
  P2OUT = BIT5;				// all P2 resistors set to pulldown and all outputs set low
  	  	  	  	  	  	  	  	  // except P2.5 which is Vcc to light sensor
  	  	  	  	  	  	  	  	  //P2.3 stays low as Vdd for light sensor

  P3DIR = 0x00;				// all P3 set to input.  P3 not used
  P3REN = 0xFF;				// all P3 input resistors enabled
  P3OUT = 0x00;				// all P3 resistors set to pulldown
  
  //Prime all pumps
				P1OUT |= BIT0 + BIT6 + BIT4;		//Turn on wash pump (P1.4) and red and green board LEDs
				P2OUT |= BIT2 + BIT0;				//Turn on PUMP1 (P2.2) and Pump2 (P2.0)
				_delay_cycles(PRIME_TIME);			//Prime feeder hoses
				P1OUT &= ~(BIT0 | BIT6 | BIT4);		//Turn off wash pump and red and green board LEDs
				P2OUT &= ~(BIT2 | BIT0);			//Turn off pump 1 and 2

/*													//Routine for testing light sensor
				if(P2IN & BIT4)	{					//Check is P2.4 is high => not dark.
					P1OUT |= BIT0;					//If light, turn on red LED P1.0
					_delay_cycles( ONE_SECOND);
					P1OUT &= ~BIT0;
					_delay_cycles( ONE_SECOND);
					P1OUT |= BIT0;
					}

				else{
					P1OUT &= ~BIT0;
					 }

*/

  while(1)

  {
	  if(P2IN & BIT4)	{					//Check is P2.4 is high => not dark.

		  P1OUT |= BIT0;					//If light, turn on red LED (P1.0)
		  P2OUT |= BIT1 + BIT2;				//Turn on feeder Pump1 (P2.2) and UVLED1 (P2.1)
		  _delay_cycles(FEEDING_TIME);		//Wait for Pump1 to deliver food
		  P2OUT &= ~BIT2;					//Turn off Pump1
		  P1OUT &= ~BIT0;					//Turn off red LED
		  _delay_cycles(ON_TIME_ONE); 		//On time for UVLED1
		  P2OUT &= ~BIT1;					//Turn off UVLED1
		  P1OUT |= BIT4 + BIT0 + BIT6;		//Turn on WashPump and both board LEDs
		  _delay_cycles(WASH_TIME);			//Wash out feeder
		  P1OUT &= ~(BIT4 |BIT0 |BIT6);		//Turn off WashPump and both board LEDs
	  }
	else{
			_delay_cycles(DARK_CHECK);		//Wait before moving to next cycle and checking again for light level
		}

	  if(P2IN & BIT4)	{						//Check is P2.4 is high => not dark.

		  P1OUT |= BIT6 + BIT5;				//If light, turn on green LED (P1.6) and UVLED2 (P1.5)
		  P2OUT |= BIT0 + BIT2;				//Turn on feeder Pump2 (P2.0)
		  _delay_cycles(FEEDING_TIME);		//Wait for Pump2 to deliver food
		  P2OUT &= ~BIT0;					//Turn off Pump2
		  P1OUT &= ~BIT6;					//Turn off green LED
		  _delay_cycles(ON_TIME_TWO); 		//On time for UVLED2
		  P1OUT &= ~BIT5;					//Turn off UVLED2
		  P1OUT |= BIT4 + BIT0 + BIT6;		//Turn on WashPump and both board LEDs
	  	  _delay_cycles(WASH_TIME);			//Wash out feeder
	  	  P1OUT &= ~(BIT4 | BIT0 | BIT6);	//Turn off WashPump and both board LEDs
  	  }
	  	else{
	  			_delay_cycles(DARK_CHECK);	//Wait before moving to next cycle and checking again for light level
	  		}


  }
}




/*Testing code for pins
// 	    if(P2IN & BIT4)	{						//Check is P2.4 is high => not dark.
			P1OUT |= BIT0 + BIT4 +BIT3 + BIT5 + BIT6;
			P2OUT |= BIT0 + BIT1 + BIT2;   //If light, turn on red LED P1.0
			_delay_cycles( 5*ONE_SECOND);
			P1OUT &= ~(BIT0 | BIT4 | BIT3 | BIT5 | BIT6);
			P2OUT &= ~(BIT0 | BIT1 | BIT2) ;
			//P2OUT &= BIT0 + ~BIT1 + ~BIT2 + ~BIT3 + ~BIT4 + BIT5 + ~BIT6 + ~BIT7 ;
		//	P2OUT = 0x20;
			_delay_cycles( 5*ONE_SECOND);

	//	}
	//	else{
	//		P1OUT &= ~BIT0;
	//	}
*/
