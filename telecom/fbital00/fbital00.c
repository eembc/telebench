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


