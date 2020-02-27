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

#define MAX_FFT_SIZE 256  /* changed to 256 because that is what it really is arw 02/23/00 */

/* Compile time Data set select for uuencode: 
 * DATA_1 or DATA_2 or DATA_3
 * DATA_3 is default
 */ 
#if	(!defined(DATA_1) && !defined(DATA_2) && !defined(DATA_3))
#define DATA_3
#endif

/*
 *  Use interleaved representation -- you need to decide on this yourself!! arw/ECL
 */

/* Allow settings by compiler define */
#ifndef	SET_INTERLEAVE

/* default, case. */
#if (!defined(C_INTERLEAVED) && !defined(D_INTERLEAVED))
#define C_INTERLEAVED 
#define D_INTERLEAVED
#endif

#endif

/* 
 *  TRIG_SCALE_FACTOR is used for greatest twiddle factor precision 
 */
#define TRIG_SCALE_FACTOR 32768

/* 
 * BUTTERFLY_SCALE_FACTOR = log2(TRIG_SCALE_FACTOR) is used to
 *  accomodate accumulator size limit of 32 bits 
 */
#define BUTTERFLY_SCALE_FACTOR 15

/* 
 * STAGE_SCALE_FACTOR is used to prevent overflow from
 *  accumulation at each processing stage 
 */
#define STAGE_SCALE_FACTOR 1
#define DATA_SIZE_EXPONENT   8

/* 
 * IFFT_SCALE_FACTOR = 1 provides for 1/N ifft output scaling
 * IFFT_SCALE_FACTOR = 0 disables 1/N ifft output scaling 
 */
#define IFFT_SCALE_FACTOR 0


/*******************************************************************************
    TypeDefs                                                            
*******************************************************************************/

/*******************************************************************************
    Global Variables                                                            
*******************************************************************************/
#ifndef ALGO_GLOBALS            /* Don't define these twice! */
#define ALGO_GLOBALS
#endif /* ALGO_GLOBALS */

/*******************************************************************************
    Function Prototypes                                                         
*******************************************************************************/


n_int	ipow(n_int x, n_int y);

void
fxpfft (
    e_s16   *InRealData,        /* real part of input data */
    e_s16   *InImagData,        /* imaginary part of input data */
    e_s16   *OutRealData,       /* real part of output data */
    e_s16   *OutImagData,       /* imaginary part of output data */
    e_s16   DataSizeExponent,   /* size of data = 2**DataSizeExponent */
    e_s16   *SineV,             /* Sine table */
    e_s16   *CosineV,           /* Cosine table */
    e_s16   *BitRevInd          /* bit reversal indicies */
);

void
fxpifft (
    e_s16   *InRealData,        /* real part of input data */
    e_s16   *InImagData,        /* imaginary part of input data */
    e_s16   *OutRealData,       /* real part of output data */
    e_s16   *OutImagData,       /* imaginary part of output data */
    e_s16   DataSizeExponent,   /* size of data = 2**DataSizeExponent */
    e_s16   *SineV,             /* Sine table */
    e_s16   *CosineV,           /* Cosine table */
    e_s16   *BitRevInd          /* bit reversal indicies */
);


#endif /* ALGO_H */
