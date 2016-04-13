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
* Creation Date: 4/13/2016
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_serial.h"
#include "r_cg_adc.h"
#include "r_cg_timer.h"
#include "r_cg_pclbuz.h"
/* Start user code for include. Do not edit comment generated here */
#include "lcd.h"
#include "string.h"
#include "infrared.h"
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
extern pwm_edge;
extern switch_edge;

//int mode = 0; // 0 for normal mode, 1 for test mode
//int pwm_flag = 0;
char myBuffer[40];
int myCounter = 0;
//int motorCounter = 0;
//int welcome = 1;

uint16_t pwm_counter;

void displayCharLCD(char c);
void welcome(void);
void msDelay(int t);
void echo(uint8_t hex);
void pwm(int cycles_per_second, int divisor);
void mtrBtn();
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

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
    uart1RxBuf[0] = 'r'; 								//Init to non-arbitrary
    uart1Status = R_UART1_Receive(&uart1RxBuf[0],1); 	//Prime UART to receive
    //PM7&=0x7F;
    ir_rxMessage = 0x0000;
    while (1U)
    {

    	mtrBtn();			//Switch pressed
    	IRcmd();
    	if (dataReady && dataPrint)
		{
			uint8_t ascii_word[16];
			word_to_ascii(ir_rxMessage, ascii_word);
			print_lcd(ascii_word);
			dataPrint = 0;
		}
        if (uart1RxFlag)	//Input received
        {
        	uart1RxFlag = 0U;

			if(uart1RxBuf[0] == 0x81)		//TEST MODE
			{
				mode = 1;
				echo(0x81);
				print_lcd("Test mode");
			}

			else if(uart1RxBuf[0] == 0x80)	//NORMAL MODE
			{
				mode = 0;
				echo(0x80);
				print_lcd("Normal mode");
			}

			else if(uart1RxBuf[0] == 0xF0)	//BUZZER ON
			{
				echo(0xF0);
				R_PCLBUZ0_Start();
			}

			else if(uart1RxBuf[0] == 0xF1)	//BUZZER OFF
			{
				echo(0xF1);
				R_PCLBUZ0_Stop();
			}

			else if(uart1RxBuf[0] == 0xF9)	//OPEN GATE
			{
				echo(0xF9);
				DVR_PHASE = 0;
				DVR_nSLEEP = 1;
				gate_status = GS_UNKNOWN;
				print_lcd("Gate opening...");
			}

			else if(uart1RxBuf[0] == 0xF8)	//CLOSE GATE
			{
				echo(0xF8);
				DVR_PHASE = 1;
				DVR_nSLEEP = 1;
				gate_status = GS_UNKNOWN;
				print_lcd("Gate closing...");
			}

			else if(uart1RxBuf[0] == 0xF7)	//READ CURRENT
			{
				echo(0xF7);
				//TODO
			}

			else if(uart1RxBuf[0] == 0xFF)	//READ STATUS
			{
				echo(0xFF);
				msDelay(10);
				switch(gate_status)
				{
					case GS_OPENED:
						echo(0x82);
						print_lcd("Opened");
						break;
					case GS_CLOSED:
						echo(0x81);
						print_lcd("Closed");
						break;
					case GS_UNKNOWN:
						echo(0x84);
						print_lcd("Unknown");
						break;
					case GS_ESTOP:
						//echo(0x84);
						print_lcd("Emergency stop");
						break;
				}
			}

			else if (uart1RxBuf[0] == 0xFC)	//READ IR CMD
			{
				echo(0xFC);
				msDelay(10);
				//Wait for complete message?
				//echo(ir_rxMessage);
				uint8_t cmd = ir_rxMessage & 0x7;
				uint8_t addr = (ir_rxMessage >> 3) & 0xFF;
				uint8_t tog = (ir_rxMessage >> 11) & 0x6;

				echo(addr);
				echo((tog<<6) + cmd);
			}

			//Buffer not full and input is not a command
			else if((myCounter < 40)&&(uart1RxBuf[0] < 0x7F))
			{
				myBuffer[myCounter] = uart1RxBuf[0];
				myCounter++;
			}
			//'Display to LCD' is activated during Test Mode
			else if((mode == 1)&&(uart1RxBuf[0] == 0xF4))
			{
				echo(0xF4);
				initLcd();
				int display_x = 0;
				int display_y = 0;
				int display_scroll = 0;
				int display_length = 16;
				int display_loop = 1;
				int overflow;

				//Determine overflow
				if (myCounter > 15) {
					overflow = myCounter - 15;
				}
				else {
					overflow = 1;
				}

				//For LCD index i
				for(display_y = 0 ; display_y < overflow ; display_y++)
				{
					//For message character j
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
					msDelay(350);
				}
				myCounter = 0;
			}

			uart1Status = R_UART1_Receive(uart1RxBuf,1);			// Prime UART2 Rx
        }

        if (uart1TxFlag)	//Output sent
        {
        	uart1TxFlag = 0U; //Clear Tx flag
        }

        pwm(100, 25); 		//PWM always running, motor toggled by DVR_nSLEEP

    }
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
	//Open connections
	EI();
	//R_SAU0_Create();
	//R_UART1_Create();
	R_UART1_Start();
	//R_TAU0_Create();
	R_TAU0_Channel0_Start();
	R_TAU0_Channel2_Start();

	//R_TMR_RD0_Create();
	R_TMR_RD0_Start();

	//R_PCLBUZ0_Create();

	dataPrint = 1;
	dataResponse = 1;
	dataReady = 0;
	R_INTC7_Start();

	//Init flags
	uart1RxFlag = 0U;
	uart1TxFlag = 0U;

	//Welcome user
	initLcd();
	welcome();
	initLcd();

	gate_status = GS_UNKNOWN;
	//Start in Normal mode
	mode = 0;
	echo(0x80);
	delayNoInt(100);
	uart1TxFlag = 0U; // clear tx flag
	print_lcd("Normal mode");

	//Motor off
	DVR_nSLEEP = 0;
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/*
 * Display a char on the LCD
 */
void displayCharLCD(char c)
{
	writeByteLcd(1U, c);
	delayNoInt(100);
}

/*
 * Welcome the user on LCD
 */
void welcome(void)
{
	int scrollCount = 0;
	int j = 0;
	int i = 0;

	char msg[] = {"                Nel T. 18179460"};

	int length = sizeof(msg)/sizeof(char);

	//For LCD index i
	for(i = 0 ; i < (length-16) ; i++)
	{
		//For message character j
		for (j = 0 ; j < 16 ; j++)
		{
			//Offset message for scroll effect
			writeByteLcd(1U, msg[(j+scrollCount)]);
			delayNoInt(100);
			//Jump to second line of LCD due to memory gap
			if (j == 7)
			{
				writeByteLcd(0U, LCD_HOME_L2);
				delayNoInt(100);
			}
		}
		scrollCount++;
		writeByteLcd(0U, LCD_HOME_L1);
		delayNoInt(100);
		msDelay(350);
	}
	msDelay(500);
}

/*
 * Delay for t milliseconds
 */
void msDelay(int t)
{
	int a = 0;
	for(a = 0; a < t; a++)
	{
		delayNoInt(1000);
	}
}

/*
 * Use to echo a received command back to sender
 */
void echo(uint8_t hex)
{
	uart1TxBuf[0] = hex;
	uart1Status = R_UART1_Send(uart1TxBuf,1);
}

/*
 * Software PWM implementation
 * Causes motor to rotate
 */
void pwm(int cycles_per_second, int divisor)
{
	if (pwm_edge){
		pwm_edge=0;
		//P4_bit.no3^=1;
		pwm_counter++;
		//P7^=0x80;
		//P4^=0x04;

		pwm_counter%=cycles_per_second; // 100 cycles per second

		if (pwm_counter < divisor) // div/cycles% duty cycle
		{
			//P4_bit.no3 = 1;
			DVR_ENABLE = 1;
		}
		else
		{
			DVR_ENABLE = 0;
		}
	}
}

void mtrBtn()
{
	if (switch_edge)
	{
		switch_edge = 0;

		if (SWITCH_OPENED)
		{
			if (DVR_PHASE == 0)
			{
				DVR_nSLEEP = 0;
				gate_status = GS_OPENED;
				print_lcd("Opened");
				msDelay(5);
			}

		}
		else if (SWITCH_CLOSED)
		{
			if (DVR_PHASE == 1) // if opening activated
			{
				DVR_nSLEEP = 0;
				gate_status = GS_CLOSED;
				print_lcd("Closed");
				msDelay(5);
			}
		}
	}
}
/* End user code. Do not edit comment generated here */
