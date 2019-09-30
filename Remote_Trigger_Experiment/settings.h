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
#define TEN_SECOND			   XTAL_Freq*10		//17 seconds by stopwatch when divide by 8
#define ONE_HUNDRED_SECOND	  XTAL_Freq*100		//171 seconds by stopwatch when divide by 8
#define ONE_HOUR    	 	 XTAL_Freq*3600
#define THREE_HOUR		   XTAL_Freq*3*3600

//#define ON_TIME_ONE		ONE_SECOND
#define ON_TIME_ONE			10*ONE_SECOND
#define ON_TIME_TWO			5*ONE_SECOND
//#define ON_TIME 			ONE_HUNDRED_SECOND


//#define OFF_TIME 			ONE_SECOND
#define OFF_TIME 			10*ONE_SECOND
//#define OFF_TIME 			ONE_HUNDRED_SECOND
//#define OFF_TIME 			ONE_HOUR
//#define OFF_TIME 			THREE_HOUR


#endif /* SETTINGS_H_ */



