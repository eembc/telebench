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
 * FUNC    : convolutionalEncode
 *
 * DESC    : 
 * Compute the sequence of BranchWords associated with the input DataBits
 * based on a 1/2 rate convolutional code specified by the NumberCodeVectors,
 * ConstraintLength and the CodeMatrix.
 * DataByteSize is provided to allow input/output data packing of multiple
 * bits per byte, the default is one bit per byte.
 * The CodeMatrix specifies the respective convolutional code by enumerating
 * NumberCodeVectors (default = 2) of size ConstraintLength in a column-wise
 * arrangment.
 *
 * RETURNS : Void
 * ---------------------------------------------------------------------------*/
void
convolutionalEncode (
    e_u8    *DataBits,                          /* Input data 1 bit per byte */
    e_s16   DataByteSize,                       /* Data size in bytes */
    e_s16   NumberCodeVectors,                  /* Number of code vectors (n) */
    e_s16   ConstraintLength,                   /* Constraint Length (K) */
    e_u8    (*CodeMatrix)[MAX_CODE_VECTORS],    /* Matrix of code vectors (column-wise) */
    e_u8    *BranchWords                        /* Output data 1 bit per byte */
)
{
    e_s16   SRIndex;
    e_s16   BWIndex;
    e_s16   DIndex;
    e_s16   CVIndex;
    e_u8    ShiftRegister[MAX_CONSTRAINT_LENGTH];

    /* Initializations */
    for (SRIndex = 0; SRIndex < ConstraintLength; SRIndex++) {
        ShiftRegister[SRIndex] = 0;
    }

    BWIndex = 0;

    /* Convolutional encoder loop */
    for (DIndex = 0; DIndex < DataByteSize; DIndex++) {

        /* Update the shift register */
        for (SRIndex = ConstraintLength-1; SRIndex > 0; SRIndex--) {
            ShiftRegister[SRIndex] = ShiftRegister[SRIndex-1];
        }

        /* Enter data into the shift register */
        ShiftRegister[0] = DataBits[DIndex];

        /* Compute each branchword value */
        for (CVIndex = 0; CVIndex < NumberCodeVectors; CVIndex++) {
            BranchWords[BWIndex] = 0;

            for (SRIndex = 0; SRIndex < ConstraintLength; SRIndex++) {
                if ( CodeMatrix[SRIndex][CVIndex] ) {
                    BranchWords[BWIndex] ^=  ShiftRegister[SRIndex];
                }
            } /* end SRIndex for */

            BWIndex++;
        } /* end CVIndex for */
    } /* end DIndex for */
}
