/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

/*******************************************************************************
    Includes                                                                    
*******************************************************************************/
#include "algo.h"

/*******************************************************************************
    Functions                                                                   
*******************************************************************************/
/*------------------------------------------------------------------------------
 * FUNC    : fxpAutoCorrelation
 *
 * DESC    : 
 *
 * Compute the autocorrelation of the InputData (size = DataSize),
 * store the results in AutoCorrData (size = NumberOfLags).
 * For this application NumberOfLags is small (<64) so a direct
 * sum-of-products implementation is used to compute the output.
 * Partial products are scaled by Scale bits.
 *
 *         
 * RETURNS : 
 *      true/false
 * ---------------------------------------------------------------------------*/

void
fxpAutoCorrelation (
    e_s16   *InputData,     /* input data */
    e_s16   *AutoCorrData,  /* output data */
    e_s16   DataSize,       /* size of input data */
    e_s16   NumberOfLags,   /* size of output data */
    e_s16   Scale           /* partial product scale (bits) */
)
{
    n_int   i;
    n_int   lag;
    n_int   LastIndex;
    e_s32    Accumulator;

    /* Compute AutoCorrelation */
    for (lag = 0; lag < NumberOfLags; lag++) {
        Accumulator = 0;
        LastIndex = DataSize - lag;
        for (i = 0; i < LastIndex; i++) {
            Accumulator += ((e_s32) InputData[i] * (e_s32) InputData[i+lag]) >> Scale;
        }

        /* Extract MSW of 1.31 fixed point accumulator */
        AutoCorrData[lag] = (e_s16) (Accumulator >> 16) ;
    }
}

