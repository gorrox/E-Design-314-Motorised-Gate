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
* File Name    : r_cg_userdefine.h
* Version      : CodeGenerator for RL78/G14 V2.04.02.01 [15 May 2015]
* Device(s)    : R5F104LE
* Tool-Chain   : GCCRL78
* Description  : This file includes user definition.
* Creation Date: 4/13/2016
***********************************************************************************************************************/

#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/

/* Start user code for function. Do not edit comment generated here */
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
//Controller mode
int mode;

#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "r_cg_timer.h"
#include "lcd.h"
#include "global.c"
/* End user code. Do not edit comment generated here */
#endif
