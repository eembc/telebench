/*==============================================================================
 *$RCSfile: thal.c,v $
 *
 *   DESC : Test Harness routines for benchmarks
 *
 * AUTHOR : ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.15 $
 *          $Date: 2002/10/02 17:20:35 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th/x86/al/thal.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: thal.c,v $
 * Revision 1.15  2002/10/02 17:20:35  rick
 * Comment POSIX CLOCKS_PER_SEC effect on duration
 *
 * Revision 1.14  2002/08/08 19:06:22  rick
 * Change fgetc return variable to int to pick up -1 EOF vs. 0xff char.
 *
 * Revision 1.13  2002/08/06 22:52:05  rick
 * Integrate HAVE_MALLOC_H
 *
 * Revision 1.12  2002/08/06 21:57:40  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.11  2002/07/11 22:50:28  rick
 * Fix lite Heap init, tcdef results init, and stig's suggestions
 *
 * Revision 1.10  2002/06/07 20:23:39  rick
 * Bug 179: Split harness src and al dependancies
 *
 * Revision 1.9  2002/05/29 22:25:37  rick
 * Set recommended iterations with make
 *
 * Revision 1.8  2002/05/03 18:02:51  rick
 * Match windows timer granularity to thv32e1
 *
 * Revision 1.7  2002/04/23 18:33:56  rick
 * Match eembc_dt with Lite, remove stdinc.h
 *
 * Revision 1.6  2002/04/19 20:56:28  rick
 * Fix clock inconsistency with th regular vs. lite
 *
 * Revision 1.5  2002/04/19 15:19:48  rick
 * Bug #154: Some preprocessors can't handle unterminated strings in # directives
 *
 * Revision 1.4  2002/03/22 22:57:54  rick
 * Change project files for lowercase, and techtag empty, th, and th_lite
 *
 * Revision 1.3  2002/03/21 22:31:08  rick
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

#include <stdlib.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <string.h> /* strlen */

#include "eembc_dt.h"
#include "thcfg.h"
#include "thal.h"
#include "thfl.h"
#include "thfli.h"
#include "heap.h"

/*------------------------------------------------------------------------------
 * The one and only globaly defined THDef structure
 */

THDef the_thdef =
   {
   /*- - - - - - - - - - - - - - - - - -
    * TARGET DESCRIPTION
   */

   { '!','!','!','!','E','E','M','B','C','-','T','H','!','!','!','!' },
   EEMBC_TH_ID,
   EEMBC_MEMBER_COMPANY,
   EEMBC_PROCESSOR,
   EEMBC_TARGET,

   THDEF_REVISION,

   /* Test Harness Version Number (from SRC\THVINFO.H) */
   { EEMBC_TH_MAJOR, EEMBC_TH_MINOR, EEMBC_TH_STEP, EEMBC_TH_REVISION },

   /* Target Hardware Version Number */
   { TARGET_MAJOR, TARGET_MINOR, TARGET_STEP, TARGET_REVISION },

   0,                             /* Target hardware specific info */

   TARGET_TIMER_AVAIL,            /* target_timer_avail */
   TARGET_TIMER_INTRUSIVE,        /* target_timer_is_intrusive */

   /*- - - - - - - - - - - - - - - - - -
    * Interface fuctions
   */
   i_printf,
   i_sprintf,
   i_sends,
   i_putchar,
   i_write_con,
   i_read_con,
   i_con_chars_avail,

   i_ticks_per_sec,
   i_tick_granularity,
   i_malloc,
   i_free,
   i_heap_reset,

   i_signal_start,
   i_signal_finished,
   i_exit,
   i_report_results,
   i_harness_poll,

   i_get_file_def,
   i_get_file_num,

   i_send_buf_as_file

   };

/*------------------------------------------------------------------------------
 * Required Global Data - The Functional layer needs this, do not delete.
*/

char pf_buf[ PF_BUF_SIZE ];

char*     mem_base = NULL;
BlockSize mem_size = 0;

/*------------------------------------------------------------------------------
 * Local Defines
 */

#define EV_ZERO (-32767)   /* used by al_exit to indicate an exit
                            * value of zero */

/*------------------------------------------------------------------------------
 * Local Data
 */

static jmp_buf exit_point;

static clock_t start_time;
static clock_t stop_time;

/*------------------------------------------------------------------------------
 * Platform Specific Header Files, Defines, Globals and Local Data
*/

/*
>> Put your platform specific stuff here
*/

/*------------------------------------------------------------------------------
 *                       >>> LOGICAL CONSOLE I/O <<<
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * These four functions must be modified to support the logical console
 * I/O channel on your targert.
 * ---------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * FUNC   : al_lc_open
 *
 * DESC   : Opens the Logical Console for I/O
 *
 *          After this function has been called, then calls to the
 *          I/O functions al_write_con(), al_put_str_con(), al_read_con()
 *          and al_con_chars_avail() can be made.
 *
 * RETURNS: Success if the logical console could be opened
 *          Failure if it could not be opened
 *
 * PORTING: you will have to fully impliment this function
 *
 *          Note, there are no parameters to this function.  For systems
 *          with a serial port, this should initialize the SP to a fixed
 *          baud rate with No parity, 8 data bits and 1 stop bit.
 * ---------------------------------------------------------------------------*/

int al_lc_open( void )

   {
   return Success;
   }

/*------------------------------------------------------------------------------
 * FUNC   : al_lc_close
 *
 * DESC   : closes the Logical Console for I/O
 *
 *          After this funcion has been called, then calls to the
 *          I/O functions al_send_con(), al_read_con(), al_put_str_con() and
 *          al_con_chars_avail()  >cannot< be made.
 *
 *          Note, this function has not return value.  If the logical console
 *          channel was open, it closes it and returns.  If it was not open
 *          it merely returns.
 *
 * PORTING: you will have to fully impliment this function
 * ---------------------------------------------------------------------------*/

void al_lc_close( void )

   {
   }

/*------------------------------------------------------------------------------
 * FUNC   : al_write_con
 *
 * DESC   : Sends data to the logical console
 *
 * PARAMS : tx_buf     - a pointer to a buffer containing the data to send
 *          byte_count - the number of bytes from the buffer to send.  If this
 *                       value is zero, then no data is sent to the logical
 *                       console.
 *
 * RETURNS: Success if all the characters were sent.
 *          Failure if all the characters could not be sent.  In this case
 *                  some of the characters MAY have been sent.
 *
 * PORTING: You will need to fully impliment this funciton
 * ---------------------------------------------------------------------------*/

int al_write_con( const char* tx_buf, size_t byte_count )

   {
   /* This logic must be preserved */
   if ( byte_count == 0 )
      return Success;

   fwrite( tx_buf, sizeof(char), byte_count, stdout );

   return Success;
   }

/*------------------------------------------------------------------------------
 * FUNC   : al_read_con
 *
 * DESC   : Reads data from the logical console
 *
 *          This function makes best effort attempt to ready the specified
 *          number of bytes from the logical console I/O channel.  Bytes
 *          read are placed in the specified buffer.
 *
 * NOTE   : See the comments for al_con_chars_avail() below.
 *
 * PARAMS : rx_buf - a pointer to a buffer where the data read is placed
 *          byte_count - the number of bytes to read from the logical console
 *
 * RETURNS: The number of bytes actually read. A return value of zero is
 *          legal and indicates that no data was available to be read.  In this
 *          case, the receive buffer is not modified in any way.
 *
 * PORTING: You will need to fully impliment this function
 *
 *          Note that this function makes a 'best effort'  E.g. it should time
 *          out or simply give up if the byte_count has not been satisfied
 *          and there is no more data to be read from the logical console.
 *
 *          This function does not have to time out, though you could build
 *          a small timout into it.
 *
 *          The skeleton below is merely a suggestion, but illusrates how the
 *          function can be implemented.
 * ---------------------------------------------------------------------------*/

size_t al_read_con( char* rx_buf, size_t byte_count )

   {
   int	ic;
   size_t cnt = 0;

   while( byte_count )
      {
      ic = fgetc( stdin );

      if ( ic == EOF )
         t_exit( 1, "\nInput Stream EOF\n" );

      *rx_buf++ = (char)ic;

      byte_count--; /* Got one! */
      cnt++;        /* count the bytes received */
      }

   return cnt;
   }

/*------------------------------------------------------------------------------
 * FUNC   : al_con_chars_avail
 *
 * DESC   : Returns the number of characters available to be read
 *
 *          This function returns the number of bytes available from
 *          the logical console I/O channel.
 *
 *          The value returned by this function can be passed to
 *          al_read_con().  In this case, al_read_con() is guarnateed to
 *          get the requested number of bytes.  In other words, the following
 *          idiom is typical:
 *
 *          If ( (cnt=al_con_chars_avail()) > 0 )
 *             {
 *             al_read_con( buf, cnt );
 *             }
 *
 * RETURNS: The number of bytes waiting to be read on the logical console
 *          I/O channel.  If zero (0) is returned, then no data is available
 *          to be read.
 *
 * PORTING: This function can return a 0, 1 or a number greater than 1 (duh!).
 *          The reason I say this is that a basic implimentation will only
 *          return 0 or 1.  However, a more advanced version may return a
 *          value greater than 1.
 *
 *          ** Example: The UART on AMD AM186ES processor does not have any
 *          receive FIFO.  There is only one receive holding register. For
 *          this uart, al_con_chars_avail() will return a 0 if there is no
 *          data waiting in the receive holding register.  It will return
 *          a one if there is a character ready to receive.
 *
 *          ** Example: The UART on the AMD AM186CC has a 16 character
 *          receive FIFO in addition to the receive holding register.  There
 *          is a status bit that indicates if this FIFO holds 8 or more
 *          characters.  So, for this UART this function will return a
 *             0 - if there is no data to receive
 *             1 - if there is data in the recieve holding register but
 *                 the FIFO flag is NOT set
 *             9 - if there is data in the receive holding register
 *                 and the FIFO flag IS set.
 *          In the 3'd case, we know there is one character in the RHR,
 *          and >at least< 8 characters in the recieve FIFO.
 * ---------------------------------------------------------------------------*/

size_t al_con_chars_avail( void )

   {
   return 1;
   }

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
 * DESC   : Exits the benchmark by long jumping back into main
 *
 *          Unlike a traditional exit() call, this supports a printf
 *          style message to be printed at exit time.
 *
 * PARAMS : exit_code - the traditional exit code
 *          fmt       - a reglar printf style format string
 *          args      - a pointer to the argument list
 *
 * NOTE   : If (fmt == NULL) then the fmt and args aguments are ignored.
 *
 * PORTING: Usually you will not have to do anything to this function.
 *          However, we have run accross a couple of compilers that do
 *          not support longjmp()!!!!!   In this case, just exit straight
 *          from this fuction.  This skips the cleanup code in AL_SECTION's
 *          4, 5 and 6.  What ever you do, this function CANNOT return!
 * ---------------------------------------------------------------------------*/

void al_exit( int exit_code, const char* fmt, va_list args )

   {
   if ( exit_code == 0 )
      exit_code = EV_ZERO;

   if ( fmt != NULL )
      {
      vsprintf( pf_buf, fmt, args );  /* Do the printf stuff */

      /* we don't care what the return value of al_write_con() is because we
       * cannot return from this function anyway.
      */
      al_write_con( pf_buf, strlen(pf_buf) );
      }

   longjmp( exit_point, exit_code );
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
 *                                >>> MAIN <<<
 * ---------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * FUNC   : main
 *
 * DESC   : Target specific entry point for the test harness
 *
 * NOTE   : Some targets may not support argc, argv or a return value.  For
 *          these targets, just do a void main( void )
 *
 *          For these systems, pass argc with a value of one (1) and pass
 *          a pointer to an array with a single pointer to a non-empty string.
 *          The string should contain something like "TH"
 * ---------------------------------------------------------------------------*/

int main( int argc, const char* argv[] )

   {
   int ev = 0;

	/* Unused */
	argc	= argc;
	argv	= argv;

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * AL_SECTION_0
    */

   /*
   >> The first thing that's gotta happen is setting the mem_base and
   >> mem_size variables so that the TH knows where the free RAM is
   */

   /* >>>> NOTE, This is very important, you gotta do this  <<<<< */

   mem_base = malloc( HEAP_SIZE );
   mem_size = HEAP_SIZE;

   if ( mem_base == 0 )
     {
     fprintf( stderr, "\nCANNOT ALLOCATE ANY MEMORY!\n" );
     exit(0);
     }

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * AL_SECTION_1
    */

   /*
   >> Perform target specific initialization here.  This should be really
   >> low level code.  Many systems will not need to put anything in this
   >> section.  However, your HW may require some initialization before
   >> the logical console I/O channel opened.  That kind of stuff goes here.
   >>
   >> Any initializatio code that can be placed after the call to al_lc_open()
   >> should be placed in AL_SECTION_3
   */

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * AL_SECTION_2
    *
    * Open the logical console I/O channel. This should be done as soon
    * as possible in the initialization process.  Error messages cannot
    * be sent to the logical console until this call is made.
   */

   al_lc_open();

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * AL_SECTION_3
   */

   /*
   >> Most of the system initialization code should go here.
   */

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * AL_SECTION_4
    *
    * Ok, we must setup a setjmp() point for th_exit().  E.g. if th_exit()
    * is called, then setjmp() returns with
   */

   {
   if ( (ev=setjmp( exit_point )) == 0 )
      {
      ev = th_main( argc,(const char **)argv );
      }
   else
      {
      /*
       * th_exit() was called
       * For the windows version, we just exit the program
      */
      }
   }

   if ( ev == EV_ZERO )
      ev = 0;

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * AL_SECTION_5
   */

   /*
   >> Perfrom target Specific Clean Up Here.  You may not have any, but if
   >> you do, it goes here.
   */

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * AL_SECTION_6
   */

   al_lc_close(); /* Close the logical Console */

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * AL_SECTION_7
   */

   /*
   >> Here is where you can do any last cleanup that needs to happen
   >> after you close the Logical Console I/O channel.
   */

   if ( ev == FATAL_EXIT )
      {
      /*
      >> Handle a fatal exit here.  If ev == FATA_EXIT then the TH code
      >> detected some problem that could not be recovered from.  In this
      >> case, operation cannot continue.
      >>
      >> Note that we do not need an error message here as the TH will
      >> already have printed one.
      */
      }

   return ev;
   }

