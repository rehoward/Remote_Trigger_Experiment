/*
 * settings.h
 *
 *  Created on: Nov 20, 2018
 *      Author: Rich
 */
/*
 * settings.h
 *

 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define PUMP_1		BIT2	//PUMP_1 is P2.2
#define PUMP_2		BIT0	//PUMP_2 is P2.0
#define UVLED_1		BIT1	//UVLED_1 is P2.1
#define UVLED_2		BIT5	//UVLED_2 is P1.5
#define WASH_PUMP	BIT4	//WASH is P1.4
#define RED_LED		BIT0	//RED_LED is P1.0
#define GREEN_LED	BIT6	//GREEN_LED is P1.6

//Clock set using 1 MHz XTAL divided by 8

#define	XTAL_Freq				125000

#define TENTH_SECOND  	     	 12500
#define ONE_SECOND  	    	XTAL_Freq
#define TEN_SECOND			   XTAL_Freq*10
#define	THIRTY_SECOND		   XTAL_Freq*30
#define ONE_HUNDRED_SECOND	  XTAL_Freq*100
#define HALF_HOUR			 XTAL_Freq*1800
#define ONE_HOUR    	 	 XTAL_Freq*3600
#define TWO_HOUR		    XTAL_Freq*2*3600
#define	TWO_AND_HALF_HOUR	XTAL_Freq*2.5
#define THREE_HOUR		   XTAL_Freq*3*3600

//Production timing
/*
#define PRIME_TIME			ONE_HUNDRED_SECOND		//Initial prime of hoses from feeder and wash resevoirs
#define WASH_TIME 			10*ONE_SECOND			//Time to wash out feeded after each feeding cycle
#define DARK_CHECK			HALF_HOUR				//Time to wait before checking light level again.
#define FEEDING_TIME		THIRTY_SECOND			//Time pump is on at beginning of each cycle to supply food.
#define ON_TIME_ONE			TWO_HOUR				//PUMP 1 on
#define ON_TIME_TWO			TWO_HOUR + HALF_HOUR	//PUMP 2 on
#define ON_TIME_THREE		THREE_HOUR				//pump 1 on
#define ON_TIME_FOUR		THREE_HOUR + HALF_HOUR	//pump 2 on
#define ON_TIME_FIVE		THREE_HOUR				//pump 1 on
#define ON_TIME_SIX			TWO_HOUR + HALF_HOUR	//pump 2 on

*/
//Test timing
#define PRIME_TIME			ONE_SECOND*20			//Initial prime of hoses from feeder and wash resevoirs
#define WASH_TIME 			10*ONE_SECOND			//Time to wash out feeded after each feeding cycle
#define DARK_CHECK			TEN_SECOND				//Time to wait before checking light level again.
#define FEEDING_TIME		TEN_SECOND				//Time pump is on at beginning of each cycle to supply food.
#define ON_TIME_ONE			TEN_SECOND				//PUMP 1 on
#define ON_TIME_TWO			TEN_SECOND				//PUMP 2 on
#define ON_TIME_THREE		TEN_SECOND				//pump 1 on
#define ON_TIME_FOUR		TEN_SECOND				//pump 2 on
#define ON_TIME_FIVE		TEN_SECOND				//pump 1 on
#define ON_TIME_SIX			TEN_SECOND				//pump 2 on


#endif /* SETTINGS_H_ */



