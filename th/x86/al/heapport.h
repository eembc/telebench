/*==============================================================================
 *$RCSfile: heapport.h,v $
 *
 * DESC   : A nifty little heap manager
 *
 *  EEMBC : Technical Advisory Board (TechTag)
 *
 *    CVS : $Revision: 1.6 $
 *          $Date: 2002/07/26 20:52:55 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th/x86/al/heapport.h,v $
 *
 *          
 * NOTE   :
 *    define TURN_ON_VERIFY_HEAP as 1 to turn on all the heap checking stuff
 *    define TURN_ON_DEBUG_HEAP  as 1 to turn on debug printf output
 *
 *    this is usually done from a make file or IDE
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: heapport.h,v $
 * Revision 1.6  2002/07/26 20:52:55  rick
 * Add harness.h for Application overrides
 *
 * Revision 1.5  2002/07/17 17:47:13  rick
 * Fix Heap warnings
 *
 * Revision 1.4  2002/04/23 18:33:56  rick
 * Match eembc_dt with Lite, remove stdinc.h
 *
 * Revision 1.3  2002/04/19 23:33:26  rick
 * guard offset and length from expressions
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

#if	!defined(HEAPPORT_H)
#define   HEAPPORT_H

#include "thlib.h" 

/*------------------------------------------------------------------------------
 * Note, we use the !defined() test here  so that a value defined in
 * a make file or from an IDE will take precedence
 *----------------------------------------------------------------------------*/

#if !defined( TURN_ON_VERIFY_HEAP )
#define TURN_ON_VERIFY_HEAP 0
#endif

#if !defined( TURN_ON_DEBUG_HEAP )
#define TURN_ON_DEBUG_HEAP 0
#endif

/*------------------------------------------------------------------------------
 * Heap Porting Interface for 32bit x86
 *----------------------------------------------------------------------------*/

/* Both of these macros must resolve to the void pointer (void*) type */

#define PTR_ADD( ptr, offset ) ((void*)((char*)(ptr) + (offset)))
#define PTR_SUB( ptr, offset ) ((void*)((char*)(ptr) - (offset)))

#if	!defined(HEAP_ALIGN_V)
#error HEAP_ALIGN_V not defined! (must be an even power of 2)
#endif

/* 
 * This macro rounds up a number to an even power of HEAP_ALIGN_V
 */
#define HEAP_ALIGN(x) (((x) + ((HEAP_ALIGN_V)-1)) & ~((HEAP_ALIGN_V)-1))

#endif

