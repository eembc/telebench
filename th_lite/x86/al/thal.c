/*==============================================================================
 *$RCSfile: thal.c,v $
 *
 *   DESC : Test Harness Adaptation Layer
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * AUTHOR : ARM Ltd., ECL, LLC
 *
 *    CVS : $Revision: 1.23 $
 *          $Date: 2002/10/02 17:20:45 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th_lite/x86/al/thal.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: thal.c,v $
 * Revision 1.23  2002/10/02 17:20:45  rick
 * Comment POSIX CLOCKS_PER_SEC effect on duration
 *
 * Revision 1.22  2002/08/08 20:50:43  rick
 * Compile out command line -i (iterations) when CRC_CHECK enabled.
 *
 * Revision 1.21  2002/07/18 23:31:39  rick
 * Add iterations to command line
 *
 * Revision 1.20  2002/07/17 17:47:28  rick
 * Fix Heap warnings
 *
 * Revision 1.19  2002/07/11 22:50:59  rick
 * Fix lite Heap init, tcdef results init, and stig's suggestions
 *
 * Revision 1.18  2002/06/07 20:23:47  rick
 * Bug 179: Split harness src and al dependancies
 *
 * Revision 1.17  2002/05/21 19:18:31  rick
 * Abstract al_sprintf for compilers w/o vsprintf
 *
 * Revision 1.16  2002/05/10 16:27:38  rick
 * Add al_main to API
 *
 * Revision 1.15  2002/05/02 19:36:08  rick
 * Add note to use vsprintf for conversions in al_printf
 *
 * Revision 1.14  2002/04/23 21:16:09  rick
 * Bug #124: printf formatting in report_info
 *
 * Revision 1.13  2002/04/19 20:56:28  rick
 * Fix clock inconsistency with th regular vs. lite
 *
 * Revision 1.12  2002/03/18 21:15:08  rick
 * Add al_report, cyclecount, crc fix in iirflt, and pktflow.
 *
 * Revision 1.8  2002/03/12 21:45:54  rick
 * TH Lite harness updates, and Build changes from directory changes
 *
 * Revision 1.10  2002/03/08 00:30:36  administrator
 * Fix Endian definition, vprintf, and rotate endian crc's
 *
 * Revision 1.10  2002/03/07 00:25:31  administrator
 * Add redirection for Tensilica Tools
 *
 * Revision 1.9  2002/02/27 17:40:49  rick
 * Update Documentation and API comments for 0.3
 *
 * Revision 1.7  2002/02/25 17:15:34  rick
 * Add comment blocks, fix atime th_report call.
 *
 * Revision 1.3  2002/02/21 22:00:20  rick
 * Replace assert functions with system calls, dependancy on ospf.
 *
 * Revision 1.6  2002/02/19 20:12:08  rick
 * Add long copyright message per Alan.
 *
 * Revision 1.1  2002/02/13 17:31:31  rick
 * TH_Lite, moved thlib to src, added thal
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

#include <stdlib.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#include "thlib.h"
#include "thal.h"


/*------------------------------------------------------------------------------
 * Local Defines
 */


/*------------------------------------------------------------------------------
 * Local Data
 */

static	clock_t  start_time;
static	clock_t  stop_time;

/*------------------------------------------------------------------------------
 * Platform Specific Header Files, Defines, Globals and Local Data
 */

/*
>> Put your platform specific code here
*/

/*------------------------------------------------------------------------------
 *                     >>> TARGET TIMER SUPPORT <<<
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 * The following five functions must be modified if you need to support a 
 * timer on your target which will be used to measure benchmark durations.
 *
 * IMPORTANT: You do not have to modify these functions if you don't want
 *            to support target based timing!  
 * ---------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * FUNC   : al_signal_start
 *
 * DESC   : Adaptation layer implimentation of th_signal_start()
 *
 *          This function is called when the benchmark starts.  It should
 *          start the target timer or record the current value of a free
 *          running timer.
 *
 * PORTING: If you want to support target based timing, you need to 
 *          fill in this function.
 * ---------------------------------------------------------------------------*/

void al_signal_start( void )
{
#if WINDOWS_EXAMPLE_CODE
        start_time      = clock();       
#else
        /* Board specific timer code */                      
        start_time      = clock();       
#endif
}

/*------------------------------------------------------------------------------
 * FUNC   : al_signal_finished
 *
 * DESC   : Adaptation layer implimentation of th_signal_finished()
 *
 *          This function is called when a benchmark or test finishes.  It
 *          stops the target timer or reads the value of a free running
 *          timer and calculates the number of timer ticks since
 *          al_signal_start() was called.
 *
 * RETURNS: The number of ticks since al_signal_start() was called.
 *
 * PORTING: If you want to support target based timing, you need to 
 *          fill in this function.
 * ---------------------------------------------------------------------------*/
   
size_t al_signal_finished( void )
{
#if WINDOWS_EXAMPLE_CODE 
	stop_time	= clock();
#else
	/* Board specific timer code  */ 
	stop_time	= clock();
#endif
	return (size_t)(stop_time-start_time);
}
   
/*------------------------------------------------------------------------------
 * FUNC   : al_ticks_per_sec
 *
 * DESC   : Adaptation layer implimentation of th_ticks_per_sec()
 *
 *          This function is used to determine the resolution of the target
 *          timer.  This value is reported to the host computer and is
 *          is used to report test results.
 *
 * RETURNS: The number of timer ticks per second.
 *
 * PORTING: If a target timer is supported, then this function must be 
 *          implemented.
 *
 *          If the target timer is NOT supported, then this function MUST
 *          return zero.
 *
 * NOTES:   ANSI C, POSIX requires that CLOCKS_PER_SEC equals 1000000
 *          independent of the actual resolution. 
 *
 *          On Linux and Solaris hosts this results in durations to be large
 *          numbers which always end with three zeros.  This is correct, 
 *          because the clock resolution is less than the POSIX required 
 *          resolution of 1000000. The resulting calculation to seconds is
 *          correct, and the actual resolution is measured to be 1000, or a
 *          millisecond timer.
 *
 *          Note that the time can wrap around.  On a 32 bit system
 *          where CLOCKS_PER_SEC equals 1000000 this function will
 *          return the same value approximately every 72 minutes.
 *          ( Excerpt from GNU man page clock )
 *
 * ---------------------------------------------------------------------------*/
   
size_t al_ticks_per_sec( void )
{
	return (size_t) CLOCKS_PER_SEC;
}

/*------------------------------------------------------------------------------
 * FUNC   : al_tick_granularity
 *
 * DESC   : used to determine the granularity of timer ticks.
 *
 *          Example 1: the value returned by al_stop_timer() may be 
 *          in milliseconds. In this case, al_ticks_pers_sec() would
 *          return 1000.  However, the timer interrupt may only occur
 *          once very 10ms.  So al_tick_granularity() would return 10.
 *
 *          Example 2: on another system, th_ticks_sec() returns 10
 *          and th_tick_granularity() returns 1.  This means that each
 *          incriment of the value returned by th_stop_timer() is in 100ms
 *          intervals.
 *
 * RETURNS: the granularity of the value returned by th_stop_timer()
 *
 * PORTING: If a target timer is supported, then this function must be 
 *          implemented.
 * ---------------------------------------------------------------------------*/
   
size_t al_tick_granularity( void )
{
	return 10;
}

/*------------------------------------------------------------------------------
 *                       >>> SUPPORT FUNCTIONS <<<
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 * These support functions are part of the Adaptaion Layer but do not
 * generally need to be modified.
 * ---------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * FUNC   : al_exit
 *                                    
 * DESC   : Exits the benchmark.
 *
 *
 * PARAMS : exit_code - the traditional exit code
 *
 *
 * PORTING: Standard C in stdlib.h
 * ---------------------------------------------------------------------------*/
   
void al_exit( int exit_code)

{
	exit(exit_code);
}

/*------------------------------------------------------------------------------
 * FUNC   : al_printf
 *                                    
 * DESC   : The traditional vprintf, control output from here.
 *
 *
 * PORTING: Standard C in stdio.h, and stdargs.h
 *
 * NOTE: To convert this to a string, use vsprintf, NOT sprintf.
 * ---------------------------------------------------------------------------*/
int		al_printf(const char *fmt, va_list	args)
{
	return	vprintf(fmt,args);
}

/*-----------------------------------------------------------------------------
 * FUNC   : al_sprintf
 *
 * DESC   : The traditional vsprintf, control output from here.
 *
 *
 * PORTING: Standard C in stdio.h, and stdargs.h
 *
 * NOTE: To convert this to a string, use vsprintf, NOT sprintf.
 * ---------------------------------------------------------------------------*/
int     al_sprintf(char *str, const char *fmt, va_list   args)
{
	return  vsprintf(str,fmt,args);
}

/*------------------------------------------------------------------------------
 * FUNC   : al_report_results
 *                                    
 * DESC   : Print additional messages below harness output.
 *
 *
 * PORTING: Use harness th_printf.
 * ---------------------------------------------------------------------------*/
void	al_report_results( void )
{
	/* Add any debug printing here, outside the normal log */
}

/*------------------------------------------------------------------------------
 * FUNC   : al_main
 *                                    
 * DESC   : Target Specific Initialization for all Benchmarks
 *
 *
 * PORTING: Use bmark_lite.c: main for benchmark specific init..
 * ---------------------------------------------------------------------------*/
extern	TCDef the_tcdef;

void	al_main( int argc, const char* argv[]  )
{

#if	!CRC_CHECK
	int	i;
#endif

	/* Unused */
	argc	= argc;
	argv	= argv;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * AL_SECTION_0
 */

/*
 * Command line processing for all benchmarks. Do not change iterations if CRC_CHECK
 * is being performed.
 */
#if	!CRC_CHECK
    for ( i = 1; i < argc; i++ )
    {
       if ( argv[i][0] == '-' && toupper( argv[i][1] ) == 'I' )
          {
          /* set the number of tcdef->rec_iterations from the command line */
          if ( isdigit( argv[i][2] ) )
             {
             the_tcdef.rec_iterations = (LoopCount)atol( argv[i]+2 );
             }
          else if ( i < (argc-1) && isdigit( argv[i+1][0] ) )
             {
             the_tcdef.rec_iterations = (LoopCount)atol( argv[i+1] );
             }
          }
       }
#endif

/*
 > Perform target specific command line processing here.
 > Many systems will not need to put anything in this section. However,
 > special command line options may make porting your benchmarks easier.
 */
   
   /*
   >> The first thing that's gotta happen is setting the mem_base and
   >> mem_size variables so that the TH knows where the free RAM is
   */

   /* >>>> NOTE, This is very important, you gotta do this  <<<<< */

	/* Initialize memory management (heap) data structures */
	mem_heap_initialize();

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * AL_SECTION_1
 */

/*
 > Perform target specific initialization here.  This should be really
 > low level code.  Many systems will not need to put anything in this
 > section.  However, your HW may require some initialization before
 > the logical console I/O channel opened.  That kind of stuff goes here.
 */

}
