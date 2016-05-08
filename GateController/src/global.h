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

/**
 * ENUMERATORS
 */
typedef enum status {UNKNOWN, OPENED, CLOSED, ESTOP} 	status;
typedef enum mode 	{NORMAL, TEST} 						mode;
/**
 * END ENUMERATORS
 */

/*CONSTANTS*/
	/* Buffer sizes */
#define RX_BUF_LEN 			16
#define TX_BUF_LEN 			16
	/*PWM*/
#define CYC_PER_SEC			100
#define DIV					25
	/* DVR */
#define DVR_nFAULT			P14_bit.no6
#define DVR_PHASE			P4_bit.no1
#define DVR_PHASE_OPEN 		0
#define DVR_PHASE_CLOSE		1
#define DVR_nSLEEP			P4_bit.no2
#define DVR_ENABLE			P4_bit.no3
	/* Motor switches */
#define SWITCH_OPENED		P0_bit.no5
#define SWITCH_CLOSED		P0_bit.no6
	/* Auto-close */
#define AUTO_CLOSE_DELAY 	10000
	/* Board buttons */
#define BTN_STEP			P7_bit.no7 	/*Menu step: 		INTP11, P77	*/
#define BTN_STOP			P5_bit.no1 	/*Emergency stop: 	INTP2, 	P51	*/
#define BTN_OPEN			P5_bit.no0 	/*Open gate:		INTP1, 	P50	*/
#define BTN_CLOSE			P3_bit.no1 	/*Close gate:		INTP4, 	P31	*/
/*END CONSTANTS*/

/*VARIABLES*/
	/* Control */
mode ctrlMode;							/*Controller mode				*/
status gate_status;						/*Current state of gate			*/
status prev_gate_status;				/*Previous state of gate		*/
	/* Real Time Clock */
rtc_counter_value_t time_now;			/*Real Time Clock				*/
	/* UART */
MD_STATUS uart1Status;					/*Status of the UART			*/
volatile uint8_t uart1RxFlag;			/*UART1 Receive flag			*/
uint8_t uart1RxBuf[RX_BUF_LEN];			/*UART1 Receive buffer			*/
uint16_t uart1RxCnt;					/*UART1 Receive counter			*/
volatile uint8_t uart1TxFlag;			/*UART1 Transmit flag			*/
uint8_t uart1TxBuf[TX_BUF_LEN];			/*UART1 Transmit buffer			*/
uint16_t uart1TxCnt;					/*UART1 Transmit counter		*/
char myBuffer[RX_BUF_LEN];				/*Data buffer					*/
int myCounter;							/*Data buffer counter			*/
	/* Interrupt flags */
uint16_t pwm_counter;					/*Pulse Width Modulation counter*/
volatile volatile pwm_edge;				/*PWM flag						*/
volatile volatile switch_edge;			/*Motor proximity trigger		*/
volatile volatile check_btns;			/*Motor proximity-check flag	*/
	/* Not Implemented */
uint8_t gate_cmd;						/*UART/IR/PCB open/close cmd	*/
uint8_t auto_close;						/*Auto-close flag				*/
uint8_t auto_close_cntr;				/*Auto-close counter			*/
/*END VARIABLES*/

/*FUNCTIONS*/
	/*Primary functions*/
void init(void);
void core(void);
void mtrBtn(void);
void boardBtn(void);
void IRtoLCD(void);
void uartReceive(void);
void uartSend(void);
void pwm(int cycles_per_second, int divisor);
	/*Auxiliary functions*/
void msDelay(int t);
void echo(uint8_t hex);
void echoData(uint8_t hex, uint8_t hex2);
void bufferToLCD(void);
void openGate(void);
void closeGate(void);
void stopGate(void);
void setRTC(void);
void sendRTC(void);
void buzzerBeep(uint8_t beeps);
uint8_t toHex(uint8_t decimal);
uint8_t toBCD(uint8_t hex);
/*END FUNCTIONS*/

#endif /* GLOBAL_H_ */
