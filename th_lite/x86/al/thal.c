/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

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
