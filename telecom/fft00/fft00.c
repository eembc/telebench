/*==============================================================================
 *$RCSfile: fft00.c,v $
 *
 *   DESC : Fixed Point Complex FFT/IFFT
 *
 *  EEMBC : Telecom Subcommittee 
 *
 * AUTHOR : RP
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2002/09/04 15:25:23 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/telecom/fft00/fft00.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: fft00.c,v $
 * Revision 1.5  2002/09/04 15:25:23  rick
 * Revert to 1.0 casts
 *
 * Revision 1.4  2002/05/22 17:55:18  rick
 * Replace assert.h with thassert.h, add assert functions to th lite.
 *
 * Revision 1.3  2002/04/25 16:09:01  rick
 * Bug #139: fft should not include  pow function
 *
 * Revision 1.2  2002/02/18 23:51:53  rick
 * Completed Telocom TH_Lite conversion
 *
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

/*******************************************************************************
    Includes                                                                    
*******************************************************************************/

#include "algo.h"
#include "thassert.h"
#if	FLOAT_SUPPORT
#include <math.h>
#endif


/*******************************************************************************
    Functions                                                                   
*******************************************************************************/

/*------------------------------------------------------------------------------
 * FUNC    : fxpfft
 *
 * DESC    : 
 * Compute the Fixed Point FFT on the 2**DataSizeExponent
 * complex input values stored in arrays InRealData and InImagData.
 * Return results in OutRealData and OutImagData
 * Requires precomputation of the sine & cosine twiddle factors.
 * Requires precomputation of the bit reversal indicies.
 *         
 * RETURNS : 
 * ---------------------------------------------------------------------------*/

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
)
{
    e_s32   WReal;
    e_s32   WImag;
    e_s32   tRealData;
    e_s32   tImagData;
    e_s16   DataSize;
    e_s16   ArgIndex;
    e_s16   DeltaIndex;
    e_s16   n1;
    e_s16   n2;
    e_s16   l;
    e_s16   i;
    e_s16   j;
    e_s16   k;
    e_s16   RealBitRevData[MAX_FFT_SIZE];
    e_s16   ImagBitRevData[MAX_FFT_SIZE];


/*( Make this a macro  -- Dave levine to supply code ) 8*/

    /* Bit Reversal */
    DataSize = 1 << DataSizeExponent;
    assert( (DataSize >= 4) && ((DataSize % 2) == 0) );
#ifdef D_INTERLEAVED
    for (i = 0; i < DataSize; i++) {
        RealBitRevData[i] = InRealData[2*BitRevInd[i]];
        ImagBitRevData[i] = InRealData[(2*BitRevInd[i])+1];
    }
#else
    for (i = 0; i < DataSize; i++) {
        RealBitRevData[i] = InRealData[BitRevInd[i]];
        ImagBitRevData[i] = InImagData[BitRevInd[i]];
    }
#endif

    /* FFT Computation */

    /* Step through the stages */
    for (k = 1; k <= DataSizeExponent; k++) {
        n1 = 1<<k;
        n2 = n1>>1;

        /* Initialize twiddle factor lookup indicies */
        ArgIndex = 0;
        DeltaIndex = (DataSize >> 1) / n2;

        /* Step through the butterflies */
        for(j = 0; j < n2; j++) {

            /* Lookup twiddle factors */
#ifdef C_INTERLEAVED
            WReal = CosineV[2*ArgIndex];
            WImag = CosineV[2*ArgIndex+1];
#else
            WReal = CosineV[ArgIndex];
            WImag = SineV[ArgIndex];
#endif
            ArgIndex += DeltaIndex;

            /* Process butterflies with the same twiddle factors */
            for(i = j; i < DataSize; i += n1) {
                l = i + n2;

                tRealData = ( WReal * RealBitRevData[l] ) + ( WImag * ImagBitRevData[l] );
                tImagData = ( WReal * ImagBitRevData[l] ) - ( WImag * RealBitRevData[l] );

                /* Scale twiddle products to accomodate 16 bit storage */
                tRealData = tRealData >> BUTTERFLY_SCALE_FACTOR;
                tImagData = tImagData >> BUTTERFLY_SCALE_FACTOR;
                RealBitRevData[l] = RealBitRevData[i] - tRealData;
                ImagBitRevData[l] = ImagBitRevData[i] - tImagData;
                RealBitRevData[i] += tRealData;
                ImagBitRevData[i] += tImagData;
            }
        }
    }

    /* Return bit reversed data to output arrays */
#ifdef D_INTERLEAVED
    for(i = 0; i < DataSize; i++) {
        OutRealData[2*i] = RealBitRevData[i];
        OutRealData[2*i+1] = ImagBitRevData[i];
    }
#else
    for(i = 0; i < DataSize; i++) {
        OutRealData[i] = RealBitRevData[i];
        OutImagData[i] = ImagBitRevData[i];
    }
#endif
}

/*------------------------------------------------------------------------------
 * FUNC    : ipow
 *
 * DESC    : Integer version of pow
 * RETURNS : y to the x power
 * ---------------------------------------------------------------------------*/
n_int	ipow(n_int x, n_int y)
{
	n_int	i,tmp=1;

	for (i=0;i<y;i++) tmp*=x;
	return tmp;
}

/*------------------------------------------------------------------------------
 * FUNC    : fxpifft
 *
 * DESC    : 
 * Compute the Radix 2  Decimation-in-Time IFFT on the 2**DataSizeExponent
 * complex input values stored in arrays RealData and ImagData.
 * Return results in OutRealData and OutImagData
 * Requires precomputation of the sine & cosine twiddle factors.
 * Requires precomputation of the bit reversal indicies.
 *
 * If IFFT_SCALE_FACTOR = 1 then generate code for 1/N ifft scaling.
 *
 * RETURNS : 
 * ---------------------------------------------------------------------------*/
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
)
{
    e_s32   WReal;
    e_s32   WImag;
    e_s32   tRealData;
    e_s32   tImagData;
    e_s16   DataSize;
    e_s16   ArgIndex;
    e_s16   DeltaIndex;
    e_s16   n1;
    e_s16   n2;
    e_s16   l;
    e_s16   i;
    e_s16   j;
    e_s16   k;
    e_s16   RealBitRevData[MAX_FFT_SIZE];
    e_s16   ImagBitRevData[MAX_FFT_SIZE];

    /* Bit Reversal */
    DataSize = 1<<DataSizeExponent;


#ifdef D_INTERLEAVED
    for (i = 0; i < DataSize; i++) {
        RealBitRevData[i] = InRealData[2*BitRevInd[i]];
        ImagBitRevData[i] = InRealData[(2*BitRevInd[i])+1];
    }
#else
    for(i = 0; i < DataSize; i++) {
        RealBitRevData[i] = InRealData[BitRevInd[i]];
        ImagBitRevData[i] = InImagData[BitRevInd[i]];
    }
#endif

    /* IFFT Computation */

    /* Step through the stages */
    for(k = 1; k <= DataSizeExponent; k++) {
        n1 = 1<<k;
        n2 = n1>>1;

        /* Initialize twiddle factor lookup indicies */
        ArgIndex = 0;
        DeltaIndex = (DataSize >> 1)/n2;

        /* Step through the butterflies */
        for(j = 0; j < n2; j++) {

            /* Lookup twiddle factors */


#ifdef C_INTERLEAVED

            WReal = CosineV[2*ArgIndex];
            WImag = -CosineV[2*ArgIndex+1];
#else

            WReal = CosineV[ArgIndex];

            /* Compute  proper sign of the sine term for IFFT */
            WImag = -SineV[ArgIndex];

#endif

            ArgIndex += DeltaIndex;

            /* Process butterflies with the same twiddle factors */
            for(i = j; i < DataSize; i += n1) {
                l = i + n2;

                tRealData = ( WReal * RealBitRevData[l] ) + ( WImag * ImagBitRevData[l] );
                tImagData = ( WReal * ImagBitRevData[l] ) - ( WImag * RealBitRevData[l] );

                /* Scale twiddle products to accomodate 16 bit storage */
                tRealData = tRealData >> BUTTERFLY_SCALE_FACTOR;
                tImagData = tImagData >> BUTTERFLY_SCALE_FACTOR;

                RealBitRevData[l] = RealBitRevData[i] - tRealData;
                ImagBitRevData[l] = ImagBitRevData[i] - tImagData;
                RealBitRevData[i] += tRealData;
                ImagBitRevData[i] += tImagData;

#if IFFT_SCALE_FACTOR
                /* 1/N IFFT scaling implemented each stage */
                RealBitRevData[l] >>= IFFT_SCALE_FACTOR;
                ImagBitRevData[l] >>= IFFT_SCALE_FACTOR;
                RealBitRevData[i] >>= IFFT_SCALE_FACTOR;
                ImagBitRevData[i] >>= IFFT_SCALE_FACTOR;
#endif

            }
        }
    }

    /* Return bit reversed data to output arrays */

#ifdef D_INTERLEAVED
    for(i = 0; i < DataSize; i++) {
        OutRealData[2*i] = RealBitRevData[i];
        OutRealData[2*i+1] = ImagBitRevData[i];
    }
#else
    for(i = 0; i < DataSize; i++) {
        OutRealData[i] = RealBitRevData[i];
        OutImagData[i] = ImagBitRevData[i];
    }
#endif
}

