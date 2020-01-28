/*==============================================================================
 *$RCSfile: algo.h,v $
 *
 *   DESC : Fixed Point Complex FFT/IFFT
 *
 *  EEMBC : Telecom Subcommittee 
 *
 * AUTHOR : RP
 *
 *    CVS : $Revision: 1.4 $
 *          $Date: 2002/05/13 20:26:03 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/telecom/fft00/algo.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: algo.h,v $
 * Revision 1.4  2002/05/13 20:26:03  rick
 * Fix missing shifts in 16, and 32 bit CRC
 *
 * Revision 1.3  2002/04/25 16:09:01  rick
 * Bug #139: fft should not include  pow function
 *
 *
 *------------------------------------------------------------------------------
 * Copyright (c) 1998-2002 by the EDN Embedded Microprocessor 
 * Benchmark Consortium (EEMBC), Inc. 
 * 
 * All Rights Reserved. This is licensed program product and 
 * is owned by EEMBC. The Licensee understands and agrees that the 
 * Benchmarks licensed by EEMBC hereunder (including methods or concepts 
 * utilized therein) contain certain information that is confidential 
 * and proprietary which the Licensee expressly agrees to retain in the 
 * strictest confidence and to use only in conjunction with the Benchmarks 
 * pursuant to the terms of this Agreement. The Licensee further agrees 
 * to keep the source code and all related documentation confidential and 
 * not to disclose such source code and/or related documentation to any 
 * third party. The Licensee and any READER of this code is subject to 
 * either the EEMBC Member License Agreement and/or the EEMBC Licensee 
 * Agreement. 
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, EEMBC DISCLAIMS ALL 
 * WARRANTIES, EITHER EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, 
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
 * PURPOSE, WITH REGARD TO THE BENCHMARKS AND THE ACCOMPANYING 
 * DOCUMENTATION. LICENSEE ACKNOWLEDGES AND AGREES THAT THERE ARE NO 
 * WARRANTIES, GUARANTIES, CONDITIONS, COVENANTS, OR REPRESENTATIONS BY 
 * EEMBC AS TO MARKETABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR OTHER 
 * ATTRIBUTES, WHETHER EXPRESS OR IMPLIED (IN LAW OR IN FACT), ORAL OR 
 * WRITTEN. 
 * 
 * Licensee hereby agrees by accessing this source code that all benchmark 
 * scores related to this code must be certified by ECL prior to publication 
 * in any media, form, distribution, or other means of conveyance of 
 * information subject to the terms of the EEMBC Member License Agreement 
 * and/or EEMBC Licensee Agreement. 
 * 
 * Other Copyright Notice (if any): 
 * 
 * For conditions of distribution and use, see the accompanying README file.
 * ===========================================================================*/

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
