/*
 * infrared.h
 *
 *  Created on: Apr 13, 2016
 *      Author: trist
 */

#ifndef INFRARED_H_
#define INFRARED_H_

#include "iodefine.h"
#include "iodefine_ext.h"
#include "r_cg_macrodriver.h"

/**
 * CONSTANTS
 */
#define ir_64bitMessage_inHalfBits_total 128
#define ir_14bitMessage_inHalfBits_total 28
/*Hex address for Tristan Nel (18179460)*/
#define TNELaddr 0x84
#define IR_RX P14_bit.no1
/*Total receive ticks for a message*/
#define ir_14bitMessage_inQuarterBits_total 53
/*Total sampling ticks*/
#define ir_sampling_ticks_at_444us_total (ir_14bitMessage_inQuarterBits_total + 2)
/**
 * END CONSTANTS
 */


/**
 * VARIABLES
 */
volatile uint16_t ir_rxMessage;
volatile uint8_t dataReady;
volatile uint8_t dataPrint;
volatile uint8_t dataResponse;
/**
 * END VARIABLES
 */

/**
 * FUNCTIONS
 */
void IRcmd(void);
void receive(void);
/**
 * END FUNCTIONS
 */

#endif /* INFRARED_H_ */
