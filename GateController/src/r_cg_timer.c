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
* File Name    : r_cg_timer.c
* Version      : CodeGenerator for RL78/G14 V2.04.02.01 [15 May 2015]
* Device(s)    : R5F104LE
* Tool-Chain   : GCCRL78
* Description  : This file implements device driver for TAU module.
* Creation Date: 5/4/2016
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_TAU0_Create
* Description  : This function initializes the TAU0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Create(void)
{
    TAU0EN = 1U;    /* supplies input clock */
    TPS0 = _0000_TAU_CKM0_FCLK_0 | _0040_TAU_CKM1_FCLK_4 | _0300_TAU_CKM2_FCLK_6 | _0000_TAU_CKM3_FCLK_8;
    /* Stop all channels */
    TT0 = _0001_TAU_CH0_STOP_TRG_ON | _0002_TAU_CH1_STOP_TRG_ON | _0004_TAU_CH2_STOP_TRG_ON |
          _0008_TAU_CH3_STOP_TRG_ON | _0200_TAU_CH1_H8_STOP_TRG_ON | _0800_TAU_CH3_H8_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    /* Mask channel 1 interrupt */
    TMMK01 = 1U;    /* disable INTTM01 interrupt */
    TMIF01 = 0U;    /* clear INTTM01 interrupt flag */
    /* Mask channel 1 higher 8 bits interrupt */
    TMMK01H = 1U;    /* disable INTTM01H interrupt */
    TMIF01H = 0U;    /* clear INTTM01H interrupt flag */
    /* Mask channel 2 interrupt */
    TMMK02 = 1U;    /* disable INTTM02 interrupt */
    TMIF02 = 0U;    /* clear INTTM02 interrupt flag */
    /* Mask channel 3 interrupt */
    TMMK03 = 1U;    /* disable INTTM03 interrupt */
    TMIF03 = 0U;    /* clear INTTM03 interrupt flag */
    /* Mask channel 3 higher 8 bits interrupt */
    TMMK03H = 1U;    /* disable INTTM03H interrupt */
    TMIF03H = 0U;    /* clear INTTM03H interrupt flag */
    /* Set INTTM00 low priority */
    TMPR100 = 1U;
    TMPR000 = 1U;
    /* Set INTTM01 low priority */
    TMPR101 = 1U;
    TMPR001 = 1U;
    /* Set INTTM02 low priority */
    TMPR102 = 1U;
    TMPR002 = 1U;
    /* Set INTTM03 low priority */
    TMPR103 = 1U;
    TMPR003 = 1U;
    /* Channel 0 used as interval timer */
    TMR00 = _8000_TAU_CLOCK_SELECT_CKM1 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_COMBINATION_SLAVE |
            _0000_TAU_TRIGGER_SOFTWARE | _0000_TAU_MODE_INTERVAL_TIMER | _0000_TAU_START_INT_UNUSED;
    TDR00 = _F617_TAU_TDR00_VALUE;
    TO0 &= ~_0001_TAU_CH0_OUTPUT_VALUE_1;
    TOE0 &= ~_0001_TAU_CH0_OUTPUT_ENABLE;
    /* Channel 1 used as interval timer */
    TMR01 = _4000_TAU_CLOCK_SELECT_CKM2 | _0000_TAU_CLOCK_MODE_CKS | _0800_TAU_8BITS_MODE | _0000_TAU_TRIGGER_SOFTWARE |
            _0000_TAU_MODE_INTERVAL_TIMER | _0000_TAU_START_INT_UNUSED;
    TDR01L = _F9_TAU_TDR01L_VALUE;
    TOM0 &= ~_0002_TAU_CH1_OUTPUT_COMBIN;
    TOL0 &= ~_0002_TAU_CH1_OUTPUT_LEVEL_L;
    TO0 &= ~_0002_TAU_CH1_OUTPUT_VALUE_1;
    TOE0 &= ~_0002_TAU_CH1_OUTPUT_ENABLE;
    /* Channel 2 used as interval timer */
    TMR02 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_COMBINATION_SLAVE |
            _0000_TAU_TRIGGER_SOFTWARE | _0000_TAU_MODE_INTERVAL_TIMER | _0000_TAU_START_INT_UNUSED;
    TDR02 = _00C7_TAU_TDR02_VALUE;
    TOM0 &= ~_0004_TAU_CH2_OUTPUT_COMBIN;
    TOL0 &= ~_0004_TAU_CH2_OUTPUT_LEVEL_L;
    TO0 &= ~_0004_TAU_CH2_OUTPUT_VALUE_1;
    TOE0 &= ~_0004_TAU_CH2_OUTPUT_ENABLE;
    /* Channel 3 used as interval timer */
    TMR03 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_16BITS_MODE |
            _0000_TAU_TRIGGER_SOFTWARE | _0000_TAU_MODE_INTERVAL_TIMER | _0000_TAU_START_INT_UNUSED;
    TDR03 = _1BBF_TAU_TDR03_VALUE;
    TOM0 &= ~_0008_TAU_CH3_OUTPUT_COMBIN;
    TOL0 &= ~_0008_TAU_CH3_OUTPUT_LEVEL_L;
    TO0 &= ~_0008_TAU_CH3_OUTPUT_VALUE_1;
    TOE0 &= ~_0008_TAU_CH3_OUTPUT_ENABLE;
}

/***********************************************************************************************************************
* Function Name: R_TAU0_Channel0_Start
* Description  : This function starts TAU0 channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel0_Start(void)
{
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMMK00 = 0U;    /* enable INTTM00 interrupt */
    TS0 |= _0001_TAU_CH0_START_TRG_ON;
}

/***********************************************************************************************************************
* Function Name: R_TAU0_Channel0_Stop
* Description  : This function stops TAU0 channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel0_Stop(void)
{
    TT0 |= _0001_TAU_CH0_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_TAU0_Channel1_Lower8bits_Start
* Description  : This function starts TAU0 channel 1 Lower 8 bits counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel1_Lower8bits_Start(void)
{
    TMIF01 = 0U;    /* clear INTTM01 interrupt flag */
    TMMK01 = 0U;    /* enable INTTM01 interrupt */
    TS0 |= _0002_TAU_CH1_START_TRG_ON;
}

/***********************************************************************************************************************
* Function Name: R_TAU0_Channel1_Lower8bits_Stop
* Description  : This function stops TAU0 channel 1 Lower 8 bits counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel1_Lower8bits_Stop(void)
{
    TT0 |= _0002_TAU_CH1_STOP_TRG_ON;
    /* Mask channel 1 interrupt */
    TMMK01 = 1U;    /* disable INTTM01 interrupt */
    TMIF01 = 0U;    /* clear INTTM01 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_TAU0_Channel2_Start
* Description  : This function starts TAU0 channel 2 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel2_Start(void)
{
    TMIF02 = 0U;    /* clear INTTM02 interrupt flag */
    TMMK02 = 0U;    /* enable INTTM02 interrupt */
    TS0 |= _0004_TAU_CH2_START_TRG_ON;
}

/***********************************************************************************************************************
* Function Name: R_TAU0_Channel2_Stop
* Description  : This function stops TAU0 channel 2 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel2_Stop(void)
{
    TT0 |= _0004_TAU_CH2_STOP_TRG_ON;
    /* Mask channel 2 interrupt */
    TMMK02 = 1U;    /* disable INTTM02 interrupt */
    TMIF02 = 0U;    /* clear INTTM02 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_TAU0_Channel3_Start
* Description  : This function starts TAU0 channel 3 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel3_Start(void)
{
    TMIF03 = 0U;    /* clear INTTM03 interrupt flag */
    TMMK03 = 0U;    /* enable INTTM03 interrupt */
    TS0 |= _0008_TAU_CH3_START_TRG_ON;
}

/***********************************************************************************************************************
* Function Name: R_TAU0_Channel3_Stop
* Description  : This function stops TAU0 channel 3 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel3_Stop(void)
{
    TT0 |= _0008_TAU_CH3_STOP_TRG_ON;
    /* Mask channel 3 interrupt */
    TMMK03 = 1U;    /* disable INTTM03 interrupt */
    TMIF03 = 0U;    /* clear INTTM03 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_TMR_RD0_Create
* Description  : This function initializes the TMRD0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TMR_RD0_Create(void)
{
    TRD0EN = 1U;    /* enable input clock supply */ 
    TRDSTR |= _04_TMRD_TRD0_COUNT_CONTINUES;
    TRDSTR &= (uint8_t)~_01_TMRD_TRD0_COUNT_START;  /* disable TMRD0 operation */
    TRDMK0 = 1U;    /* disable TMRD0 interrupt */
    TRDIF0 = 0U;    /* clear TMRD0 interrupt flag */
    /* Set INTTRD0 low priority */
    TRDPR10 = 1U;
    TRDPR00 = 1U;
    TRDMR |= _00_TMRD_TRDGRC0_GENERAL | _00_TMRD_TRDGRD0_GENERAL;
    TRDPMR |= _01_TMRD_TRDIOB0_PWM_MODE;
    TRDDF0 = _00_TMRD_TRDIOD_FORCEDCUTOFF_DISABLE | _00_TMRD_TRDIOC_FORCEDCUTOFF_DISABLE |
             _00_TMRD_TRDIOB_FORCEDCUTOFF_DISABLE;
    TRDOER1 &= _F0_TMRD_CHANNEL0_OUTPUT_DEFAULT;
    TRDOER1 |= _01_TMRD_TRDIOA0_OUTPUT_DISABLE | _00_TMRD_TRDIOB0_OUTPUT_ENABLE | _04_TMRD_TRDIOC0_OUTPUT_DISABLE |
               _08_TMRD_TRDIOD0_OUTPUT_DISABLE;
    TRDOCR |= _00_TMRD_TRDIOB0_INITIAL_OUTPUT_L;
    TRDCR0 |= _00_TMRD_INETNAL_CLOCK_F1_FIH | _20_TMRD_COUNTER_CLEAR_TRDGRA;
    TRDIER0 = _01_TMRD_IMIA_ENABLE | _02_TMRD_IMIB_ENABLE | _10_TMRD_OVIE_ENABLE;
    TRDPOCR0 = _01_TMRD_TRDIOB_OUTPUT_ACTIVE_H;
    TRDGRA0 = _1F3F_TMRD_TRDGRA0_VALUE;
    TRDGRB0 = _14EF_TMRD_TRDGRB0_VALUE;
    /* Set TRDIOB0 pin */
    POM1 &= 0xDFU;
    P1 &= 0xDFU;
    PM1 &= 0xDFU;
}

/***********************************************************************************************************************
* Function Name: R_TMR_RD0_Start
* Description  : This function starts TMRD0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TMR_RD0_Start(void)
{
   volatile uint8_t trdsr_dummy;
    
    TRDIF0 = 0U;    /* clear TMRD0 interrupt flag */
    trdsr_dummy = TRDSR0; /* read TRDSR0 before write 0 */
    TRDSR0 = 0x00U; /* clear TRD0 each interrupt request */
    TRDMK0 = 0U;    /* enable TMRD0 interrupt */
    TRDSTR |= _04_TMRD_TRD0_COUNT_CONTINUES;
    TRDSTR |= _01_TMRD_TRD0_COUNT_START;    /* start TMRD0 counter */
}

/***********************************************************************************************************************
* Function Name: R_TMR_RD0_Stop
* Description  : This function stops TMRD0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TMR_RD0_Stop(void)
{
    volatile uint8_t trdsr_dummy;
    
    TRDSTR |= _04_TMRD_TRD0_COUNT_CONTINUES;
    TRDSTR &= (uint8_t)~_01_TMRD_TRD0_COUNT_START;  /* stop TMRD0 counter */
    TRDMK0 = 1U;    /* disable TMRD0 interrupt */
    TRDIF0 = 0U;    /* clear TMRD0 interrupt flag */
    trdsr_dummy = TRDSR0; /* read TRDSR0 before write 0 */
    TRDSR0 = 0x00U; /* clear TRD0 each interrupt request */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
