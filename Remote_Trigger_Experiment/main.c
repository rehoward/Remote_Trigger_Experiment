//Timing generator for bee feeding apparatus.

	//System with two feeding pumps, two UV LEDs, the indicators on the LaunchPad, light sensor,
	//and 2 wash pumps.

	//LEDs on the board are P1.0 and P1.6.
	//Pump1 (P2.2) on at the same time as UVLED1 (P2.1) and red board LED (P1.0)
	//Pump2 (P2.0) on at the same time as UVLED2 (P1.5) and green board LED (P1.6).
	//WashPump 1 (P1.4) on after each feeding pump 1 cycle and both red and green board LEDs
	//WashPump 2 (P1.2) on after each feeding pump 2 cycle and both red and green board LEDs

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
		//WashPumpOne and both board LEDs turned on for WASH_TIME.
		//
		//Pump2, UVLED2, and green LED turned on.
		//Pump2 turned off after FEEDING_TIME
		//UVLED2 and green LED turned off after ON_TIME_TWO.
		//WashPumpTwo and both board LEDs turned on for WASH_TIME.

		//Pump 1, UV LED 1, and red LED turned on.
		//Pump 1 turned off after FEEDING_TIME
		//UV LED1 and red LED turned off after ON_TIME_THREE.
		//WashPumpOne and both board LEDs turned on for WASH_TIME.

		//Pump 2, UV LED 2, and green LED turned on.
		//Pump 2 turned off after FEEDING_TIME
		//UV LE21 and green LED turned off after ON_TIME_FOUR.
		//WashPumpTwo and both board LEDs turned on for WASH_TIME.
		//
		//Pump 1, UV LED 1, and red LED turned on.
		//Pump 1 turned off after FEEDING_TIME
		//UV LED1 and red LED turned off after ON_TIME_FIVE.
		//WashPumpOne and both board LEDs turned on for WASH_TIME.

		//Pump 2, UV LED 2, and green LED turned on.
		//Pump 2 turned off after FEEDING_TIME
		//UV LED2 and green LED turned off after ON_TIME_SIX.
		//WashPumpTwo and both board LEDs turned on for WASH_TIME.


#include "main.h"
#include "msp430.h"
#include "stdint.h"

void setMSP430Pins() {
	  BCSCTL1 = CALBC1_1MHZ;		//DCO set to calibrated 1 MHz
	  DCOCTL = CALDCO_1MHZ;			//DCO set to calibrated 1 MHz
	  BCSCTL2 = DIVM_3 + DIVS_3;	//Set MCLK and SMCLK to DCOCLK.  MCLK and SMCLK divide by 8;

	  P1DIR = 0xFF;				// Port 1 all set to output
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

	return;
}

void WashCycleOne() {
	  P1OUT |= WASH_PUMP_ONE + RED_LED + GREEN_LED;		//Turn on WashPump and both board LEDs
	  _delay_cycles(WASH_TIME);						//Wash out feeder
	  P1OUT &= ~(WASH_PUMP_ONE|RED_LED|GREEN_LED);		//Turn off WashPump and both board LEDs
	return;
}

void WashCycleTwo() {
	  P1OUT |= WASH_PUMP_TWO + RED_LED + GREEN_LED;		//Turn on WashPump and both board LEDs
	  _delay_cycles(WASH_TIME);						//Wash out feeder
	  P1OUT &= ~(WASH_PUMP_TWO|RED_LED|GREEN_LED);		//Turn off WashPump and both board LEDs
	return;
}


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;		// Stop WDT

setMSP430Pins();
  
  //Prime all pumps
				//Turn on wash pumps (P1.4, P1.2) and red and green board LEDs (P1.0 and P1.6)
				P1OUT |= GREEN_LED + RED_LED + WASH_PUMP_ONE + WASH_PUMP_TWO;		//Turn on wash pumps (P1.4, P1.2) and red and green board LEDs
				_delay_cycles(WASH_PRIME_TIME);			//Prime feeder hoses
				P1OUT = 0x00;							//Pumps and LEDs off.
				_delay_cycles(ONE_SECOND);				//Flash LEDs to signal second half of prime cycle
														//Note, can't run all 4 pumps off battery at once.
				//Turn on PUMP1 (P2.2), Pump2 (P2.0), red, and green LEDs
				P1OUT |= GREEN_LED + RED_LED;
				P2OUT |= PUMP_1 + PUMP_2;
				_delay_cycles(FEED_PRIME_TIME);		//Prime feeder hoses and wash hoses

				//Turn off wash pumps and red and green board LEDs
				P1OUT &= ~(GREEN_LED | RED_LED);

				P2OUT &= ~(PUMP_1 | PUMP_2);			//Turn off pump 1 and 2


  while(1)

  {

//Cycle 1 Feeder 1
	  if(P2IN & BIT4)	{										//Check is P2.4 is high => not dark.

				  P1OUT |= RED_LED;								//If light, turn on red LED (P1.0)
				  P2OUT |= PUMP_1 + UVLED_1;					//Turn on feeder Pump1 (P2.2) and UVLED1 (P2.1)
				  _delay_cycles(FEEDING_TIME);					//Wait for Pump1 to deliver food
				  P2OUT &= ~PUMP_1;								//Turn off Pump1
				  P1OUT &= ~RED_LED;							//Turn off red LED
				  _delay_cycles(ON_TIME_ONE); 					//On time for UVLED1
				  P2OUT &= ~UVLED_1;							//Turn off UVLED1
				  WashCycleOne();
	  }

	  else{
					_delay_cycles(DARK_CHECK);		//Wait before moving to next cycle and checking again for light level
	  }



//Cycle 2 Feeder 2
	  if(P2IN & BIT4)	{										//Check is P2.4 is high => not dark.

					  P1OUT |= UVLED_2 + GREEN_LED;				//If light, turn on green LED (P1.6) and UVLED2 (P1.5)
					  P2OUT |= PUMP_2;							//Turn on feeder Pump2 (P2.0)
					  P1OUT |= UVLED_2;							//Turn on UVLED_1
					  _delay_cycles(FEEDING_TIME);				//Wait for Pump2 to deliver food
					  P2OUT &= ~PUMP_2;							//Turn off Pump2
					  P1OUT &= ~GREEN_LED;						//Turn off green LED
					  _delay_cycles(ON_TIME_TWO); 				//On time for UVLED2
					  P1OUT &= ~UVLED_2;						//Turn off UVLED2
					  WashCycleTwo();
		}
		else{
				  	_delay_cycles(DARK_CHECK);		//Wait before moving to next cycle and checking again for light level
		}

//Cycle 3 Feeder 1
	  	  if(P2IN & BIT4)	{										//Check is P2.4 is high => not dark.

	  				  P1OUT |= RED_LED;								//If light, turn on red LED (P1.0)
	  				  P2OUT |= PUMP_1 + UVLED_1;					//Turn on feeder Pump1 (P2.2) and UVLED1 (P2.1)
	  				  _delay_cycles(FEEDING_TIME);					//Wait for Pump1 to deliver food
	  				  P2OUT &= ~PUMP_1;								//Turn off Pump1
	  				  P1OUT &= ~RED_LED;							//Turn off red LED
	  				  _delay_cycles(ON_TIME_THREE); 					//On time for UVLED1
	  				  P2OUT &= ~UVLED_1;							//Turn off UVLED1
	  				  WashCycleOne();
	  	  }

	  	  else{
	  					_delay_cycles(DARK_CHECK);		//Wait before moving to next cycle and checking again for light level
	  	  }



//Cycle 4 Feeder 2
	  	  if(P2IN & BIT4)	{										//Check is P2.4 is high => not dark.

	  					  P1OUT |= UVLED_2 + GREEN_LED;				//If light, turn on green LED (P1.6) and UVLED2 (P1.5)
	  					  P2OUT |= PUMP_2;							//Turn on feeder Pump2 (P2.0)
	  					  P1OUT |= UVLED_2;							//Turn on UVLED_1
	  					  _delay_cycles(FEEDING_TIME);				//Wait for Pump2 to deliver food
	  					  P2OUT &= ~PUMP_2;							//Turn off Pump2
	  					  P1OUT &= ~GREEN_LED;						//Turn off green LED
	  					  _delay_cycles(ON_TIME_FOUR); 				//On time for UVLED2
	  					  P1OUT &= ~UVLED_2;						//Turn off UVLED2
	  					  WashCycleTwo();
	  		}
	  		else{
	  				  	_delay_cycles(DARK_CHECK);		//Wait before moving to next cycle and checking again for light level
	  		}

//Cycle 5 Feeder 1
	  		  	  if(P2IN & BIT4)	{										//Check is P2.4 is high => not dark.

	  		  				  P1OUT |= RED_LED;								//If light, turn on red LED (P1.0)
	  		  				  P2OUT |= PUMP_1 + UVLED_1;					//Turn on feeder Pump1 (P2.2) and UVLED1 (P2.1)
	  		  				  _delay_cycles(FEEDING_TIME);					//Wait for Pump1 to deliver food
	  		  				  P2OUT &= ~PUMP_1;								//Turn off Pump1
	  		  				  P1OUT &= ~RED_LED;							//Turn off red LED
	  		  				  _delay_cycles(ON_TIME_FIVE); 					//On time for UVLED1
	  		  				  P2OUT &= ~UVLED_1;							//Turn off UVLED1
	  		  				  WashCycleOne();
	  		  	  }

	  		  	  else{
	  		  					_delay_cycles(DARK_CHECK);		//Wait before moving to next cycle and checking again for light level
	  		  	  }



//Cycle 6 Feeder 2
	  		  	  if(P2IN & BIT4)	{										//Check is P2.4 is high => not dark.

	  		  					  P1OUT |= UVLED_2 + GREEN_LED;				//If light, turn on green LED (P1.6) and UVLED2 (P1.5)
	  		  					  P2OUT |= PUMP_2;							//Turn on feeder Pump2 (P2.0)
	  		  					  P1OUT |= UVLED_2;							//Turn on UVLED_1
	  		  					  _delay_cycles(FEEDING_TIME);				//Wait for Pump2 to deliver food
	  		  					  P2OUT &= ~PUMP_2;							//Turn off Pump2
	  		  					  P1OUT &= ~GREEN_LED;						//Turn off green LED
	  		  					  _delay_cycles(ON_TIME_SIX); 				//On time for UVLED2
	  		  					  P1OUT &= ~UVLED_2;						//Turn off UVLED2
	  		  					  WashCycleTwo();
	  		  		}
	  		  		else{
	  		  				  	_delay_cycles(DARK_CHECK);		//Wait before moving to next cycle and checking again for light level
	  		  		}










  }		//for whil()
}	// for main()




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
