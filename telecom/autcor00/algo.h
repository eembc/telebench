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

/* Compile time Data set select for uuencode: 
 * DATA_1 through DATA_3
 * DATA_3 is default
 */ 
#if	(!defined(DATA_1) && !defined(DATA_2) && !defined(DATA_3))
#define DATA_3
#endif

/* OUTPUT_SCALE is used to accomodate data size limit of 16 bits */
#define OUTPUT_SCALE 16

/*******************************************************************************
    Global Variables                                                            
*******************************************************************************/
#ifndef ALGO_GLOBALS            /* Don't define these twice! */
#define ALGO_GLOBALS
#endif /* ALGO_GLOBALS */

/*******************************************************************************
    Function Prototypes                                                         
*******************************************************************************/

void fxpAutoCorrelation (
    e_s16   *InputData,     /* input data */
    e_s16   *AutoCorrData,  /* output data */
    e_s16   DataSize,       /* size of input data */
    e_s16   NumberOfLags,   /* size of output data */
    e_s16   Scale           /* partial product scale (bits) */
    );

#endif /* __ALGO_H */
