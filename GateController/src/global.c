/*
 * global.c
 *
 *  Created on: Feb 21, 2016
 *      Author: Tristan Nel - 18179460
 */

#include "r_cg_userdefine.h"
#include "r_cg_rtc.h"

uint8_t uart1RxBuf[RX_BUF_LEN];				// UART1 receive buffer
uint16_t uart1RxCnt;						// UART1 receive counter
uint8_t uart1RxFlag;						// UART1 receive flag
uint8_t uart1RxErrFlag; 					// UART1 Receive Error Flag
uint8_t uart1RxOvrFlag; 					// UART1 Receive Overrun Flag

uint8_t uart1TxBuf[TX_BUF_LEN];				// UART1 Transmit buffer
uint16_t uart1TxCnt;						// UART1 Transmit counter
uint8_t uart1TxFlag;

rtc_counter_value_t time_now;

MD_STATUS uart1Status;
