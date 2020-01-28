/*==============================================================================
 *$RCSfile: algo.h,v $
 *
 *   DESC : This file contains the Main and other TH_Lite support functions
 *
 *  EEMBC : Telecom Subcommittee 
 *
 * AUTHOR : RP
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2002/07/17 17:44:30 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/telecom/fbital00/algo.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: algo.h,v $
 * Revision 1.5  2002/07/17 17:44:30  rick
 * Key outputdata files based on input filename
 *
 * Revision 1.4  2002/06/14 16:31:17  rick
 * Bug #184-#187: Remove compiler warnings
 *
 * Revision 1.3  2002/04/01 20:51:45  administrator
 * Apply Standard Comment Block
 *
 * Revision 1.2  2002/03/23 00:51:47  rick
 * Visual C++ Build fixes
 *
 * Revision 1.1  2002/02/18 23:51:54  rick
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

#ifndef ALGO_H
#define ALGO_H

/*******************************************************************************
    Includes                                                                    
*******************************************************************************/
#include "thlib.h"

/*******************************************************************************
    Defines                                                                     
*******************************************************************************/
/* STEP_SIZE 51 (fixed) is equivalent to 0.099609 (float) */
#define STEP_SIZE               51
#define MAX_BITS_PER_CARRIER    12
#define ALLOCATION_MAP_SIZE     512

/* Compile time Data set select for uuencode: 
 * DATA_1 through DATA_6
 * DATA_6 is default
 */ 
#if	(!defined(DATA_2) && !defined(DATA_3) && !defined(DATA_6))
#define DATA_6
#endif

/*******************************************************************************
    Global Variables                                                            
*******************************************************************************/
#ifndef ALGO_GLOBALS            /* Don't define these twice! */
#define ALGO_GLOBALS
#endif /* ALGO_GLOBALS */

/*******************************************************************************
    Function Prototypes                                                         
*******************************************************************************/
void
fxpBitAllocation (
    e_s16   *CarrierSNRdB,          /* input data */
    e_s16   *CarrierBitAllocation,  /* output data */
    e_u16   NumberOfCarriers,       /* size of input data */
    e_s16   WaterLeveldB_in,        /* Starting water level in dB */
    e_s16   *WaterLeveldB_out,      /* Final water level in dB */
    e_s16   *AllocationMap,         /* Lookup Table */
    e_u16    BitsPerDMTSymbol,        /* total bits for allocation */
	size_t	loop_cnt
);

#endif /* __fBitAl00_H */
