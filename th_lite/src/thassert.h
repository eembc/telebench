/*==============================================================================
 *$RCSfile: thassert.h,v $
 *
 *   DESC : Test Harness assert functions
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * AUTHOR : ECL, LLC
 *
 *    CVS : $Revision: 1.2 $
 *          $Date: 2002/05/23 16:31:53 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th_lite/src/thassert.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: thassert.h,v $
 * Revision 1.2  2002/05/23 16:31:53  rick
 * Bug #169, #170, #172, #173: Char/assert fixes
 *
 * Revision 1.1  2002/05/22 17:55:26  rick
 * Replace assert.h with thassert.h, add assert functions to th lite.
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

#if		HAVE_ASSERT_H

#include	<assert.h>

#elif   !defined(ASSERT_H)

#define ASSERT_H


#ifdef __cplusplus
extern "C" {
#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * assert functions coded to harness
*/

#ifndef NDEBUG
extern void __assertfail( const char *msg, const char *cond, const char *file, int line );

#define assert(p)   ((p) ? ((void)0) : \
                     __assertfail( "\n** ASSERT : %s, file %s, line %d\n", \
                     #p, __FILE__, __LINE__ ))
#else
#define assert() ((void)0)
#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * fatal error  (just like assert, but always triggers)
*/

#ifndef NDEBUG
extern void __fatal( const char* msg, const char* file, int line );

#define fatal()     (__fatal( "\n** FATAL : file %s, line %d\n",  \
                        __FILE__, __LINE__ ) )
#else
#define fatal()   ((void)0)
#endif


#ifdef __cplusplus
}
#endif

#endif /* File sentinal */

