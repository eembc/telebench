/*==============================================================================
 *$RCSfile: anytoi.h,v $
 *
 *   DESC : Test Harness routines for benchmarks
 *
 * AUTHOR : ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2002/04/23 18:33:56 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th/src/anytoi.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: anytoi.h,v $
 * Revision 1.3  2002/04/23 18:33:56  rick
 * Match eembc_dt with Lite, remove stdinc.h
 *
 * Revision 1.2  2002/03/21 22:31:08  rick
 * Network Harness, and empty benchmark fixes
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

#ifndef   ANYTOI_H
#define   ANYTOI_H

#include "eembc_dt.h"

/*------------------------------------------------------------------------------
 * Values returned by find_num_type()
 */

#define T_DEC    1
#define T_INT    2
#define T_OCT    3
#define T_HEX    4

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

   int find_num_type( const char *sp );

   /* All these (word and dword) conversions are unsigned. */
   /* Note that if the string holds a negative decimal value, the conversion */
   /* will be signed, but the aanytoi() and anytol() functions will return */
   /* the value as unsgined.  In this case, merely cast the return */
   /* value to an int or long. */

   Word  hextoi( const char *sp );
   Word  octtoi( const char *sp );
   Word  dectoi( const char *sp );
   Word  anytoi( const char *sp );

   Dword hextol( const char *sp );
   Dword octtol( const char *sp );
   Dword dectol( const char *sp );
   Dword anytol( const char *sp );

#ifdef __cplusplus
   }
#endif
#endif
/*==============================================================================
 * ENDOF  : ANYTOI.H
 * ===========================================================================*/
