/*==============================================================================
 *$RCSfile: algo.h,v $
 *
 *   DESC : Convolutional Encoder
 *
 * AUTHOR : RP
 *
 *  EEMBC : Telecom Subcommittee 
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2002/04/01 20:51:29 $
 *          $Author: administrator $
 *          $Source: d:/cvs/eembc2/telecom/conven00/algo.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: algo.h,v $
 * Revision 1.5  2002/04/01 20:51:29  administrator
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

#ifndef ALGO_H
#define ALGO_H

/*******************************************************************************
    Includes                                                                    
*******************************************************************************/
#include "thlib.h"

/*******************************************************************************
    Defines                                                                     
*******************************************************************************/
#define MAX_CODE_VECTORS 2
#define MAX_CONSTRAINT_LENGTH 8

/* Compile time Data set select for uuencode: 
 * DATA_1 through DATA_3
 * DATA_3 is default
 */ 
#if	(!defined(DATA_1) && !defined(DATA_2) && !defined(DATA_3))
#define DATA_3
#endif


/*******************************************************************************
    Global Variables                                                            
*******************************************************************************/

/*******************************************************************************
    Function Prototypes                                                         
*******************************************************************************/
void
convolutionalEncode (
    e_u8    *DataBits,                          /* Input data 1 bit per byte */
    e_s16   DataByteSize,                       /* Data size in bytes */
    e_s16   NumberCodeVectors,                  /* Number of code vectors (n) */
    e_s16   ConstraintLength,                   /* Constraint Length (K) */
    e_u8    (*CodeMatrix)[MAX_CODE_VECTORS],    /* Matrix of code vectors (column-wise) */
    e_u8    *BranchWords                        /* Output data 1 bit per byte */
);

#endif

