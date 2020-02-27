/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef __ALGO_H
#define __ALGO_H

/*******************************************************************************
    Includes                                                                    
*******************************************************************************/

#include "thlib.h"

/*******************************************************************************
    Defines
*******************************************************************************/

/* 
 * MAX_DATA_SIZE: the number of bits in the packet which has been encoded by the
 * convolutional encoder. For each bit the Viterbi decoder reads in a pair of
 * branch values.
 *
 * Reasonable values for MAX_DATA_SIZE are in the range 200-400, multiples of 8.
 * The number chosen below is was chosen arbitrarily.
 */

#define     MAX_DATA_SIZE        344   


/* Compile time Data set select for uuencode: 
 * DATA_1 through DATA_4
 * DATA_4 is default
 */ 
#if	(!defined(DATA_1) && !defined(DATA_2) && !defined(DATA_3) && !defined(DATA_4))
#define DATA_4
#endif


void ViterbiDecoderIS136(e_s16 *EncodedStreamPtr, e_s16 *DecodedStreamPtr);

#endif /* __ALGO_H */
