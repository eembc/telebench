/*==============================================================================
 *$RCSfile: fbital00.c,v $
 *
 *   DESC : Fixed Point Bit Allocation
 *
 *  EEMBC : Telecom Subcommittee 
 *
 * AUTHOR : RP
 *
 *    CVS : $Revision: 1.6 $
 *          $Date: 2002/06/14 16:31:20 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/telecom/fbital00/fbital00.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: fbital00.c,v $
 * Revision 1.6  2002/06/14 16:31:20  rick
 * Bug #184-#187: Remove compiler warnings
 *
 * Revision 1.5  2002/04/19 22:17:04  rick
 * Code cleanup for Linux build
 *
 * Revision 1.4  2002/04/01 20:51:46  administrator
 * Apply Standard Comment Block
 *
 * Revision 1.3  2002/03/23 00:51:48  rick
 * Visual C++ Build fixes
 *
 * Revision 1.2  2002/02/18 23:51:54  rick
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

/*******************************************************************************
    Functions                                                                   
*******************************************************************************/
/*------------------------------------------------------------------------------
 * FUNC    : FxpBitAllocation
 *
 * DESC    : 
 * Allocate BitsPerDMTSymbol over a set (size = NumberOfCarriers) of carriers
 * using a "water level" algorithm.
 * The SNR profile in dB is contained in the input array: CarrierSNRdB, the bit
 * allocation results are returned in the output array: CarrierBitAllocation.
 * Upon start WaterLeveldB contains the initial water level, upon exit it
 * contains the final water level.
 *
 * Requires precomputed bit allocation lookup table (AllocationMap).
 *
 * The range of CarrierSNR (dB) [-64.0, 63.998] (float)
 * is represented by the range [-32768, 32767] (fixed)
 *
 * RETURNS : 
 * ---------------------------------------------------------------------------*/

void
fxpBitAllocation (
    e_s16   *CarrierSNRdB,           /* input data */
    e_s16   *CarrierBitAllocation,   /* output data */
    e_u16    NumberOfCarriers,       /* size of input data */
    e_s16   WaterLeveldB_in,         /* Starting water level in dB */
    e_s16   *WaterLeveldB_out,       /* Final water level in dB */
    e_s16   *AllocationMap,          /* Lookup Table */
    e_u16    BitsPerDMTSymbol,        /* total bits for allocation */
	size_t	loop_cnt

)

{
    e_u16    TotalBits;
    e_u16    CarrierBits;
    e_s16   ccb;
    e_s32    DeltadB;
    e_s16   l_WaterLeveldB;

    /* Make a working copy */
    l_WaterLeveldB = WaterLeveldB_in;

    do {
        /* Allocate bits based on current water level */
        TotalBits = 0;
        for (ccb = 0; ccb < NumberOfCarriers; ccb++) {
            DeltadB = CarrierSNRdB[ccb] - l_WaterLeveldB;

            /* Check if any bits can be allocated to this carrier */
            if (DeltadB < 0) {
                CarrierBits = 0;
            } 
            else {
                if (DeltadB > 32767) {
                    CarrierBits = MAX_BITS_PER_CARRIER;
			    } 
                else {
                    CarrierBits = AllocationMap[(DeltadB >> 6)];
                }

                /* Limit per BitsPerDMTSymbol */
                /* Needed to insure convergence */
                if ((CarrierBits + TotalBits) > BitsPerDMTSymbol) {
                    CarrierBits = BitsPerDMTSymbol - TotalBits;
                }
            }

            /* Assign bits to carrier */
            CarrierBitAllocation[ccb] = CarrierBits;
            TotalBits += CarrierBits;
        }

        /* Update water level */
/* bug 90, 121
        l_WaterLeveldB += STEP_SIZE * 3 *
                        ((e_s16)(TotalBits - BitsPerDMTSymbol)) / NumberOfCarriers;
*/
		l_WaterLeveldB += (e_s32)STEP_SIZE * 3 *
                        ((e_s16)TotalBits - (e_s16)BitsPerDMTSymbol) /(e_s16) NumberOfCarriers;

    
    } while (TotalBits != BitsPerDMTSymbol);

    /* Store the result back to the caller */
    *WaterLeveldB_out = l_WaterLeveldB;
    
}


