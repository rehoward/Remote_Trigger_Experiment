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


#endif /* SETTINGS_H_ */



