/*
 * global.h
 *
 *  Created on: Apr 11, 2016
 *      Author: trist
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "r_cg_macrodriver.h"

/*CONSTANTS*/
#define debug_msg 0x37C0		/*DEBUG*/
#define fullHalfBitLength 128
#define frameHalfBitLength 28
#define toggle 0x800 			/*Use to toggle the toggle bit*/
#define frameBaseDef 0x3420; 	/*Add one of 3 codes below after toggling the toggle bit*/
								/*Student nr - code is 0x84, already included*/
	/*COMMAND CODES*/
#define openCode 0x1
#define closeCode 0x2
#define bothCode 0x3
	/*BUTTONS*/
#define btnOpen P4_bit.no1
#define btnClose P13_bit.no7
/*END CONSTANTS*/

/*VARIABLES*/
	/*FLAGS*/
volatile uint8_t btnOpenTrigger;
volatile uint8_t btnCloseTrigger;
volatile uint16_t frameBase;
volatile uint8_t modulate; 		/*RC5 Manchester 38Khz pulse train toggle*/
volatile uint8_t tx; 			/*Flag for current transmitting action*/
	/*DATA*/
volatile uint16_t msg; 			/*16 bit message buffer*/

/*FUNCTIONS*/
void init(void);
void core(void);
void transmit(void);
void btnOpenTriggered(void);
void btnCloseTriggered(void);
/*END FUNCTIONS*/

#endif /* GLOBAL_H_ */
