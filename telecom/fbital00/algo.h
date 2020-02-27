/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef ALGO_H
#define ALGO_H

/*******************************************************************************
    Includes                                                                    
*******************************************************************************/
#include "thlib.h"

/*******************************************************************************
    Defines                                                                     
*******************************************************************************/
/* STEP_SIZE 51 (fixed) is equivalent to 0.099609 (float) */
#define STEP_SIZE               51
#define MAX_BITS_PER_CARRIER    12
#define ALLOCATION_MAP_SIZE     512

/* Compile time Data set select for uuencode: 
 * DATA_1 through DATA_6
 * DATA_6 is default
 */ 
#if	(!defined(DATA_2) && !defined(DATA_3) && !defined(DATA_6))
#define DATA_6
#endif

/*******************************************************************************
    Global Variables                                                            
*******************************************************************************/
#ifndef ALGO_GLOBALS            /* Don't define these twice! */
#define ALGO_GLOBALS
#endif /* ALGO_GLOBALS */

/*******************************************************************************
    Function Prototypes                                                         
*******************************************************************************/
void
fxpBitAllocation (
    e_s16   *CarrierSNRdB,          /* input data */
    e_s16   *CarrierBitAllocation,  /* output data */
    e_u16   NumberOfCarriers,       /* size of input data */
    e_s16   WaterLeveldB_in,        /* Starting water level in dB */
    e_s16   *WaterLeveldB_out,      /* Final water level in dB */
    e_s16   *AllocationMap,         /* Lookup Table */
    e_u16    BitsPerDMTSymbol,        /* total bits for allocation */
	size_t	loop_cnt
);

#endif /* __fBitAl00_H */
