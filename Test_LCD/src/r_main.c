/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
 * No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
 * LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
 * ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
 * of this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2011, 2015 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * File Name    : r_main.c
 * Version      : CodeGenerator for RL78/G14 V2.04.02.01 [15 May 2015]
 * Device(s)    : R5F104LE
 * Tool-Chain   : GCCRL78
 * Description  : This file implements main function.
 * Creation Date: 15-02-16
 ***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
 ***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "r_cg_timer.h"
#include "lcd.h"
/* Start user code for include. Do not edit comment generated here */

/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
 ***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */


extern uint8_t uart1RxBuf[RX_BUF_LEN];				// UART1 receive buffer
extern uint16_t uart1RxCnt;						// UART1 receive counter
extern uint8_t uart1RxFlag;						// UART1 receive flag
extern uint8_t uart1RxErrFlag; 					// UART1 Receive Error Flag
extern uint8_t uart1RxOvrFlag; 					// UART1 Receive Overrun Flag

extern uint8_t uart1TxBuf[TX_BUF_LEN];				// UART1 Transmit buffer
extern uint16_t uart1TxCnt;						// UART1 Transmit counter
extern uint8_t uart1TxFlag;						// UART1 Transmit flag

extern MD_STATUS uart1Status;

extern uint8_t timer_interrupt;

int testMode = 0;
int normalMode = 1;
char myBuffer[40];
int myCounter = 0;
int welcome = 1;

/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);
void MSG_Welcome(void);
void letsWait(int t);


/***********************************************************************************************************************
 * Function Name: main
 * Description  : This function implements main function.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void main(void)
{
	R_MAIN_UserInit();
	/* Start user code. Do not edit comment generated here */
	uart1RxBuf[0] = 'r';
	uart1Status = R_UART1_Receive(&uart1RxBuf[0],1); // Prime UART2 Rx

	while (1U)
	{
		/*
		if(welcome)
		{
			MSG_Welcome();
			initLcd();
		}
		 */
		if (uart1RxFlag)
		{
			uart1RxFlag = 0U;
			welcome = 0;
			if(uart1RxBuf[0] == 0x81)
			{
				testMode = 1;
				normalMode = 0;
				uart1TxBuf[0] = 0x81;
				uart1Status = R_UART1_Send(uart1TxBuf,1);
			}
			else if(uart1RxBuf[0] == 0x80)
			{
				testMode = 0;
				normalMode = 1;
				uart1TxBuf[0] = 0x80;
				uart1Status = R_UART1_Send(uart1TxBuf,1);



			}

			else if((myCounter < 40)&&(uart1RxBuf[0] < 0x7F))
			{
				myBuffer[myCounter] = uart1RxBuf[0];
				myCounter++;
			}
			else if((testMode == 1)&&(uart1RxBuf[0] == 0xF4))
			{
				uart1TxBuf[0] = 0xF4;
				uart1Status = R_UART1_Send(uart1TxBuf,1);
				initLcd();
				int display_x = 0;
				int display_y = 0;
				int display_scroll = 0;
				int display_length = 16;
				int display_loop = 1;
				int ashley;

				if (myCounter > 15) {
					ashley = myCounter - 15;
				}
				else {
					ashley = 1;
				}

				for(display_y = 0 ; display_y < ashley ; display_y++)
				{
					for (display_x = 0 ; display_x < myCounter ; display_x++)
					{
						writeByteLcd(1U, myBuffer[(display_x+display_scroll)]);
						delayNoInt(3250);
						if (display_x == 7){
							writeByteLcd(0U, LCD_HOME_L2);
							delayNoInt(100);
						}
					}
					display_scroll++;
					writeByteLcd(0U, LCD_HOME_L1);
					delayNoInt(100);
					letsWait(350);
				}
				myCounter = 0;
			}

			uart1Status = R_UART1_Receive(uart1RxBuf,1);			// Prime UART2 Rx
		}
		//If a character has been transmitted
		if (uart1TxFlag)
		{
			uart1TxFlag = 0U; // clear tx flag
		}
	}
	/*
	/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
 * Function Name: R_MAIN_UserInit
 * Description  : This function adds user code before implementing main function.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
	/* Start user code. Do not edit comment generated here */
	EI();
	R_SAU0_Create();
	R_UART1_Create();
	R_UART1_Start();

	R_TAU0_Create();
	R_TAU0_Channel0_Start();

	uart1RxFlag = 0U;
	uart1TxFlag = 0U;
	uart1TxBuf[0] = 0x80;
	uart1Status = R_UART1_Send(uart1TxBuf,1);
	while(uart1TxFlag==0U)
	{
	}
	uart1TxFlag = 0U; // clear tx flag

	initLcd();
	MSG_Welcome();
	initLcd();

	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
void MSG_Welcome(void)
{
	int scrollCnt = 0;
	int j = 0;
	int i = 0;

	char msg[] = {"                Heyns K 18552463"};

	int length = sizeof(msg)/sizeof(char);

	for(i = 0 ; i < (length-16) ; i++)
	{
		for (j = 0 ; j < 16 ; j++)
		{
			writeByteLcd(1U, msg[(j+scrollCnt)]);
			delayNoInt(100);
			if (j == 7){
				writeByteLcd(0U, LCD_HOME_L2);
				delayNoInt(100);
			}
		}
		scrollCnt++;
		writeByteLcd(0U, LCD_HOME_L1);
		delayNoInt(100);
		letsWait(350);
	}
	letsWait(500);
}


void letsWait(int t)
{
	int a=0;
	for(a=0;a<t;a++)
	{
		delayNoInt(1000);
	}
}

/* End user code. Do not edit comment generated here */
