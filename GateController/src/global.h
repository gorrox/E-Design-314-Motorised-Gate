/*
 * global.h
 *
 *  Created on: May 4, 2016
 *      Author: trist
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "r_cg_timer.h"
#include "lcd.h"
#include "r_cg_rtc.h"
#include "infrared.h"
#include "adc.h"

//CONSTANTS
//Buffer sizes
#define RX_BUF_LEN 16
#define TX_BUF_LEN 16
//DVR
#define DVR_nFAULT	P14_bit.no6
#define DVR_PHASE	P4_bit.no1 //Default: 0 opening dir, 1 closing dir
#define DVR_nSLEEP	P4_bit.no2
#define DVR_ENABLE	P4_bit.no3
//Motor switches
#define SWITCH_OPENED	P0_bit.no5
#define SWITCH_CLOSED	P0_bit.no6
//Gate status
int gate_status;
#define GS_UNKNOWN	0
#define GS_OPENED	1
#define GS_CLOSED	2
#define GS_ESTOP	3
#define AUTO_CLOSE_DELAY 10000
//Board buttons
#define BTN_STEP		P7_bit.no7 //Menu step: 		INTP11, P77
#define BTN_STOP		P5_bit.no1 //Emergency stop: 	INTP2, P51
#define BTN_OPEN		P5_bit.no0 //Open gate:			INTP1, P50
#define BTN_CLOSE		P3_bit.no1 //Close gate:		INTP4, P31
//ADC
#define ADC_IN	P2_bit.no4

//VARIABLES
uint8_t mode;								// Controller mode
uint8_t GS_PREV_STATE;
uint8_t uart1RxBuf[RX_BUF_LEN];				// UART1 receive buffer
uint16_t uart1RxCnt;						// UART1 receive counter
uint8_t uart1RxFlag;						// UART1 receive flag
uint8_t uart1RxErrFlag; 					// UART1 Receive Error Flag
uint8_t uart1RxOvrFlag; 					// UART1 Receive Overrun Flag
uint8_t uart1TxBuf[TX_BUF_LEN];				// UART1 Transmit buffer
uint16_t uart1TxCnt;						// UART1 Transmit counter
uint8_t uart1TxFlag;						// UART1 Transmit flag
rtc_counter_value_t time_now;				// Real Time Clock
MD_STATUS uart1Status;
char myBuffer[RX_BUF_LEN];					// Data buffer
int myCounter;							// Data buffer counter
uint16_t pwm_counter;						// Pulse Width Modulation counter
uint8_t volatile pwm_edge;
uint8_t volatile switch_edge;
uint8_t volatile check_btns;
uint8_t gate_cmd;							//Triggered when UART/IR/PCB sends open/close
uint8_t auto_close;
uint8_t auto_close_cntr;

//FUNCTIONS in global.c
void init(void);
void core(void);
void displayCharLCD(char c);
void welcome(void);
void msDelay(int t);
void echo(uint8_t hex);
void echoData(uint8_t hex, uint8_t hex2);
void pwm(int cycles_per_second, int divisor);
void mtrBtn();
void boardBtn();
void openGate();
void closeGate();
void stopGate();
void buzzerBeep(uint8_t beeps);
uint8_t toHex(uint8_t decimal);
uint8_t toBCD(uint8_t hex);

#endif /* GLOBAL_H_ */
