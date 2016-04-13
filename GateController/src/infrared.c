/*
 * infrared.c
 *
 *  Created on: Apr 13, 2016
 *      Author: trist
 */

#include "infrared.h"
#include "lcd.h"
#include "r_cg_userdefine.h"


void receive(void)
{
	static volatile uint8_t ir_14bitMessage_inQuarterBits_counter = ir_14bitMessage_inQuarterBits_total;

	// this is so that the rising edge of the last bit being read
	// doesn't trigger the beginning of the next bit of sampling too quickly
	static volatile uint8_t ir_sampling_ticks_at_444us = ir_sampling_ticks_at_444us_total;

	static volatile uint8_t double_half_bit = 0x2;
	static volatile uint16_t ir_rxMessage_buffer = 0; //ir rx message buffer
	//	double_half_bit = 0;

	if (ir_sampling_ticks_at_444us){
		if (ir_14bitMessage_inQuarterBits_counter){
			// grab first half-bit
			if (!((ir_14bitMessage_inQuarterBits_counter + 1) % 4)){
				double_half_bit = (double_half_bit | IR_RX) << 1;
			}

			// if at the end of a full bit
			if (!((ir_14bitMessage_inQuarterBits_counter - 1) % 4)){
				double_half_bit |= IR_RX;
				if (!double_half_bit || (double_half_bit != 0x3)){
					// if it is a 0x10 or 0x01, then take the 2nd lowest significant bit
					ir_rxMessage_buffer |= ((double_half_bit & 0x2) >> 1);
					// if it's not the last bit, make place for the next bit
					if (ir_14bitMessage_inQuarterBits_counter - 1){
						ir_rxMessage_buffer <<= 1;
					}
				}
				double_half_bit = 0;
			}
			ir_14bitMessage_inQuarterBits_counter--;
		}
		ir_sampling_ticks_at_444us--;
	}
	else
	{
		ir_14bitMessage_inQuarterBits_counter = ir_14bitMessage_inQuarterBits_total;
		ir_sampling_ticks_at_444us = ir_sampling_ticks_at_444us_total;
		ir_rxMessage = ir_rxMessage_buffer;
		dataReady = 1;
		dataResponse = 1;
		dataPrint = 1;
		ir_rxMessage_buffer = 0;
		double_half_bit = 0x2;
		R_TAU0_Channel3_Stop();
		R_INTC7_Start();
	}
}

void IRcmd(void)
{
	if (dataReady && dataResponse)
	{
		uint8_t cmd = ir_rxMessage & 0x7;
		uint8_t addr = (ir_rxMessage >> 3) & 0xFF;
		uint8_t tog = (ir_rxMessage >> 11) & 0x6;

		if (addr == TNELaddr)
		{
			switch(cmd)
			{
				case 0x1: // OPEN
					if (mode) echo(0x88);
					DVR_PHASE = 0;
					DVR_nSLEEP = 1;
					gate_status = GS_UNKNOWN;
					break;
				case 0x2: // CLOSE
					if (mode) echo(0x90);
					DVR_PHASE = 1;
					DVR_nSLEEP = 1;
					gate_status = GS_UNKNOWN;
					break;
				case 0x3: //ESTOP
					if (mode) echo(0x84);
					DVR_nSLEEP = 0;
					gate_status = GS_ESTOP;
					break;
			}
		}
		dataResponse = 0;
	}
}
