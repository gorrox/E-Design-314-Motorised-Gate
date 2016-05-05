/*
 * adc.c
 *
 *  Created on: May 5, 2016
 *      Author: trist
 */

#include "adc.h"

//FUNCTIONS
void ADC(void)
{
	if(timer_adc_reader_10Hz_interrupt)
	{
		timer_adc_reader_10Hz_interrupt = 0;
		//adc_get_multiple_channels();

		// process data
		uint8_t current_plus_status[16];
//		current_plus_status[5] = '\0';
		//initial_current = ADC_value[3] / 10;
		initial_current = adc_get_reading()/10;
		//latest_current_reading = initial_current;

		//Collision detection
		/*
		//if (collision_det && (initial_current >= MTR_CURRENT_THRSH))
		if (initial_current >= MTR_CURRENT_THRSH)
		{
			//collision_det = 0;
			DVR_PHASE ^= 0x1; //Toggle motor direction
			DVR_nSLEEP = 1;
			GS_PREV_STATE = gate_status;
			gate_status = GS_UNKNOWN;
		}
		*/

		//Display
		if (!mode && dataPrint) //Normal mode
		{
			current_plus_status[7] = ' ';
			current_plus_status[8] = ' ';
			current_plus_status[9] = initial_current/10 + '0';
			current_plus_status[10] = (initial_current % 10) + '0';
			current_plus_status[11] = 'm';
			current_plus_status[12] = 'A';
			current_plus_status[13] = '\0';
			uint8_t i;
			switch(DVR_PHASE)
			{
				case 0: //opening
					for (i = 0; i < 7; i++)
					{
						current_plus_status[i] = "Opening"[i];
					}
					print_lcd(current_plus_status);
					break;
				case 1: //closing
					for (i = 0; i < 7; i++)
					{
						current_plus_status[i] = "Closing"[i];
					}
					print_lcd(current_plus_status);
					break;
			}
		}

	}
}

/**
 * get adc reading (single-shot reading of 1 channel)
 * @return: 10-bit adc result
 */
uint16_t adc_get_reading()
{
	uint16_t adc_result;
	//P7^=0x80;
	R_ADC_Start();
	while(!adc_ready);
	adc_ready=0;
	R_ADC_Get_Result(&adc_result);
	R_ADC_Stop();
	return adc_result;
}

/**
 * service the adc interrupt and get multiple readings
 */
void adc_multi_channel_interrupt_service_routine()
{
	static uint8_t cur_channel = 0;
	switch (INTAD_FSM_state) {
	case AD_SAMPLING:
		R_ADC_Get_Result((&(ADC_value[cur_channel])));
		cur_channel++;
		if (cur_channel == NUM_CHANNELS) {
			INTAD_FSM_state = AD_IDLE;
			cur_channel = 0;
			ADC_done = 1;
		}
		break;
	case AD_IDLE:
	default:
		INTAD_FSM_state = AD_IDLE;
		break;
	}
}

/**
 * get multiple channels from the adc
 */
void adc_get_multiple_channels()
{
	INTAD_FSM_state = AD_SAMPLING;
	ADC_done = 0;
	R_ADC_Start(); /* Start ADC (ADCS = 0n) */
	while (!ADC_done);

	volatile tiny_adc_reading = ADC_value[2] >> 3;
	//motor_power_ratio(tiny_adc_reading,128);
}
