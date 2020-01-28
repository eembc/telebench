/*==============================================================================
 *$RCSfile: thal.h,v $
 *
 *   DESC : Test Harness Adaptation Layer interface
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * AUTHOR : ARM Ltd., ECL, LLC
 *
 *    CVS : $Revision: 1.13 $
 *          $Date: 2002/05/21 19:18:33 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th_lite/src/thal.h,v $
 *          
 *  NOTE! : IMPORTANT! Do not include any host specific include files here
 *          like WINDOWS.H or SOLARIS.H.  This file is intended to be a host
 *          independent interface to the Test Harness Adaptation Layer used by
 *          the Test Harness Functional Layer.
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: thal.h,v $
 * Revision 1.13  2002/05/21 19:18:33  rick
 * Abstract al_sprintf for compilers w/o vsprintf
 *
 * Revision 1.12  2002/05/10 16:30:31  rick
 * Add al_main to API
 *
 * Revision 1.11  2002/03/18 21:15:09  rick
 * Add al_report, cyclecount, crc fix in iirflt, and pktflow.
 *
 * Revision 1.8  2002/03/12 21:45:54  rick
 * TH Lite harness updates, and Build changes from directory changes
 *
 * Revision 1.10  2002/03/08 00:30:37  administrator
 * Fix Endian definition, vprintf, and rotate endian crc's
 *
 * Revision 1.7  2002/02/27 17:40:49  rick
 * Update Documentation and API comments for 0.3
 *
 * Revision 1.5  2002/02/27 00:22:13  rick
 * Add HAVE_MALLOC_H, al_printf to harness.
 *
 * Revision 1.7  2002/02/25 17:15:35  rick
 * Add comment blocks, fix atime th_report call.
 *
 * Revision 1.5  2002/02/19 20:12:09  rick
 * Add long copyright message per Alan.
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

#ifndef   THAL_H       /* File Sentinal */
#define   THAL_H

#include "thcfg.h"

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

   /*------------------------------------------------------------------------------
    * Global Defines
   */

#define FATAL_EXIT (-32766)

   /*------------------------------------------------------------------------------
    * Global data
    */


   /*------------------------------------------------------------------------------
    * The Test Harness Lite Application Layer API
    */

	size_t	al_ticks( void );
	size_t	al_ticks_per_sec( void );
	size_t	al_tick_granularity( void );

	void	al_signal_start( void );
	size_t	al_signal_finished( void );
	void	al_exit( int exit_code);
	int		al_printf(const char *fmt, va_list args);
	int		al_sprintf(char *str, const char *fmt, va_list args);
	void	al_report_results( void );
	void	al_main(int argc, const char* argv[]);

   /*----------------------------------------------------------------------------*/

#ifdef __cplusplus    /* Take this out if you don't need it */
   }
#endif

#endif                /*  File Sentinal */

