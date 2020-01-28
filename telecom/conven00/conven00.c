/*==============================================================================
 *$RCSfile: conven00.c,v $
 *
 *   DESC : Convolutional Encoder
 *
 * AUTHOR : RP
 *
 *  EEMBC : Telecom Subcommittee 
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2002/04/01 20:51:29 $
 *          $Author: administrator $
 *          $Source: d:/cvs/eembc2/telecom/conven00/conven00.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: conven00.c,v $
 * Revision 1.3  2002/04/01 20:51:29  administrator
 * Apply Standard Comment Block
 *
 * Revision 1.3  2002/03/11 22:11:50  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
 *
 * Revision 1.2  2002/02/18 23:51:49  rick
 * Completed Telocom TH_Lite conversion
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
