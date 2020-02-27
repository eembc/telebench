/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#include "thfli.h"
#include "thlib.h"
#include "therror.h"
#include "printfe.h"

#include <stdio.h>

/*------------------------------------------------------------------------------
 * This sturcture is intentionally static.  Nothing outside this file
 * should have access to this structure.  All of the access to the test
 * harness functionality is procedural.
*/
static THDef *thdef = NULL;

/*------------------------------------------------------------------------------
 * FUNC   : thlib_main
 *
 * DESC   : This is the entry point to a 'test' or 'bench mark'
 *
 *          This is the first function called in the test component by the
 *          test harness.
 *
 * PARAMS : A pointer to a THDef structure. (an input paramter)
 *          A pointer to a TCDef structure. (an output paramter )
 *
 * RETURNS: Description of the functions return values (if applicable)
 * ---------------------------------------------------------------------------*/

int thlib_main

   ( /*in*/ THDef *thdef_ptr, /*out*/ TCDef **tcdef_ptr, int argc, const char *argv[] )

   {
   int    rv;
   TCDef *tcdef;

   /* First, we check the pointer parameters.  If either is NULL then
    * we cannot continue.
   */
   if (thdef_ptr == NULL || tcdef_ptr == NULL)
      return THE_BAD_PTR;

   /* Check the revision of the test harness.  Note, this test allows
    * older bench marks to run on newer test harnesses.  E.g. the test
    * harness can be updated without re-compiling all the benchmarks
    */
   if (thdef_ptr->revision > THDEF_REVISION)
      return THE_BAD_THDEF_VERSION;

   /* We have a non-null pointer that points to the same kind of test
    * harness defintion structure we were compiled with!  Yay!
    */
   thdef = thdef_ptr;  /* Pointer copy!  (not structure copy) */

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * Now we will call any test harness library initialization functions.
    * These may fail so we will return their error codes
    */

   /* No initialization here yet... (there probably will be in a
    * subsiquent version :)
    */

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * now, call the bench marks init routine.
    * At this point in time, it is legal for the test component to call
    * >any< of the test API functions!
    *
    * The tc_init() function should initialize and return.  This can take
    * awhile, but it must return.  Note, no benchmarking takes place
    * during this call.
    *
    * If this function succeeds, it will return a pointer to a test component
    * defintion structure. If it fails, it will return NULL.
   */

   rv = test_main( &tcdef, argc, argv );

   /* Ok, we need to make sure that the Test or Benchmark was compiled
    * with the same version as the library...  both should have been
    * compiled with the exact same header file... but you never know
   */
   if (tcdef->revision > TCDEF_REVISION)
      return THE_BAD_TCDEF_VERSION;

   /* Check to see if initialization of the test or benchmark
    *was successfull,
   */
   if (rv == Success)
      {
      /* Hey! it worked, copy the tc defition to the the
       * caller's tcdef structure
      */
      *tcdef_ptr = tcdef; /* Pointer copy!  not structure copy */
      }

   return rv;
   }

/*------------------------------------------------------------------------------
 * FUNC   : pf_sender
 *
 * DESC   : The sender engine for the console printf
 *
 *          This sends characters to the 'logical console'
 *
 * NOTE   : This function is not used if the printf engine from the compiler
 *          is used for the test harness.  This function is used if the
 *          small printf engine in th_com\printfe.c is used.
 * ---------------------------------------------------------------------------*/

#if USE_TH_PRINTF
static int pf_sender( char c, void *ptr )

   {
   if (th_putchar( c ) == -1)
      return 0;
   else
      return 1;
   }
#endif

/*==============================================================================
 *                         >>> THE API <<<
 * ===========================================================================*/

/*------------------------------------------------------------------------------
 * FUNC   : th_printf
 *
 * DESC   : The basic printf function.
 *
 *          Output goes to the logical console
 *
 * PARAMS : fmt - the classic printf format string
 * ---------------------------------------------------------------------------*/

int th_printf( const char *fmt, ... )

   {
   int rv;
#if USE_TH_PRINTF
   va_list args;
   va_start( args, fmt );
   rv = printfe( pf_sender, 0, fmt, args );
   va_end( args );
#else
   /* 
    * Not using home grown printf.  Using the one
    * from the compiler which built the test harness.
    */
   va_list args;
   va_start( args, fmt );
   rv = ( *thdef->thip_printf ) ( fmt, args );
   va_end( args );
#endif
   return rv;
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_sprintf
 *
 * DESC   : The basic sprintf function.
 *
 * PARAMS : fmt - the classic printf format string
 * ---------------------------------------------------------------------------*/

int th_sprintf( char *str, const char *fmt, ... )

   {
   int rv;
   va_list args;
   va_start( args, fmt );
   rv = vsprintf( str, fmt, args );
   va_end( args );
   return rv;
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_putchar
 *
 * DESC   : Sends a character to the logical console.
 *
 * NOTE   : A '\n' is translated to a '\r\n'
 *
 * RETURNS: the character sent.  If there was an error, then -1 is returned.
 *          In the error case, the character may have been sent
 *          (there is no way to tell).
 * ---------------------------------------------------------------------------*/

int th_putchar( char c )

   {
   return (*thdef->thip_putchar) ( c );
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_puts
 *
 * DESC   : Sends a string to the logical console
 *
 *          '\n' characters in the string are translated to a '\r\n' sequence.
 *
 * PARAMS : s - the null terminated string to send.
 *
 * NOTE   : This function sends a '\n' (newline) character after the
 *          string.  This is like the puts() stdandard library function.
 *
 *          If you don't like this, you can use the th_sends() which
 *          does what puts() should have in the first place.
 *
 * RETURNS: A nonnegative value if successful. If puts fails in any
 *          way it returns -1.  Note, in the failure case, none-some-or-all
 *          of the string may have been sent.
 * ---------------------------------------------------------------------------*/

int th_puts( const char *s )

   {
   if (th_sends( s ) == -1)
      return -1;

   if (th_putchar( '\n' ) == -1)
      return -1;

   return 1;
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_putb
 *
 * DESC   : Sends the contents of a buffer to the logical console
 *
 *          This function send the contents of the buffer to the logical
 *          console as a sring of charcters.
 *
 * PARAMS : b - a pointer to a buffer containing the data to send
 *          buf_size - the sizie, in bytes, of the buffer
 *
 * NOTE   : This function DOES NOT translate '\n' characters to the '\r\n'
 *          sequence.  The contents of the buffer are sent as is.
 *
 * RETURNS: A nonnegative value if successful. If puts fails in any
 *          way it returns -1.  Note, in the failure case, none-some-or-all
 *          of the buffer may have been sent.
 *
 *   NOTE : this function >never< returns zero.
 * ---------------------------------------------------------------------------*/

int th_putb( const char *buf, size_t buf_size )

   {
   if (( *thdef->thip_write_con ) ( buf, buf_size ) != Success)
      return -1;

   return 1;
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_sends
 *
 * DESC   : Sends a string to the logical console
 *
 *          This function is just like th_puts() but it DOES NOT sends
 *          a '\n' (newline) character after the string.
 *
 *          '\n' characters in the string are translated to a '\r\n' sequence.
 *
 * RETURNS: A nonnegative value if successful. If puts fails in any
 *          way it returns -1.  Note, in the failure case, none-some-or-all
 *          of the string may have been sent.
 *
 *   NOTE : this function >never< returns zero.
 * ---------------------------------------------------------------------------*/

int th_sends( const char *s )

   {
   return (*thdef->thip_sends) ( s );
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_con_chars_avail
 *
 * DESC   : used to see how much data is available form the console channel
 *
 * RETURNS: the number of bytes (characters) in the input buffer or queue for
 *          the logical console channel.  E.g. this function returns the
 *          maximum ammount of data which can be read using the_read_con()
 * ---------------------------------------------------------------------------*/

size_t th_con_chars_avail( void )

   {
   return (*thdef->thip_con_chars_avail)();
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_read_con
 *
 * DESC   : Reads data from the logical console channel.
 *
 *          This function will read up to read_cnt characters from the logical
 *          console channel's input buffers and place them in the buffer.
 *
 *          If there are less than read_cnt charcaters in the input buffer
 *          then they will be placed in the buffer.  E.g. this function
 *          will not wait for characters to come in on the console channel.
 *
 * NOTE   : This funtion is designed to be used with th_con_chars_avail()
 *
 * PARAMS : buf - the buffer in which to place any data read
 *          read_cnt - the number of characters to read and place
 *          in the buffer
 *
 * RETURNS: the number of bytes actually placed
 *          in the buffer.  If there is no data to be read from the logical
 *          console channel, then this function will return zero.
 * ---------------------------------------------------------------------------*/

size_t th_read_con( char *buf, size_t read_cnt )

   {
   return (*thdef->thip_read_con) ( buf, read_cnt );
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_timer_available
 *
 * DESC   : used to determine if the duration timer is available.
 *
 * RETURNS: TRUE if the target supports the duration timer.
 *          FALSE if not
 * ---------------------------------------------------------------------------*/

int th_timer_available( void )
{
	return thdef->target_timer_avail;
}

/*------------------------------------------------------------------------------
 * FUNC   : th_timer_is_intrusive
 *
 * DESC   : used to determine if the timer function is intrusive.
 *
 *          Intrusive usually means that operating and maintaining the timer
 *          has a run time overhead.  For example, using a 10ms interrupt
 *          to incriment a timer value is intrusive because the interrupt
 *          service routine takes CPU time.
 *
 *          If an intrusive target timer is used to measure benchmarks, then
 *          its effect must be measured and taken into account.
 *
 *          Some target timers may not be intrusive.  For example, a target
 *          with a built in real time clock can measure time without an
 *          interrupt service routine.
 *
 *          Another way to build a non-intrusive timer is to cascade
 *          counter/timer circuits to get very large divisors.  For example,
 *          with a 20mhz system clock two 16bit timers could be cascaded to
 *          measure durations up to 3 minutes and 34 seconds before rolling
 *          over.
 *
 *    NOTE: If the timer is not avaialable, then this function returns
 *          FALSE.
 *
 *
 * RETURNS: TRUE if the target's duration timer is intrusive
 *          FALSE if it is not
 * ---------------------------------------------------------------------------*/

int th_timer_is_intrusive( void )
{
	return thdef->target_timer_is_intrusive;
}

/*------------------------------------------------------------------------------
 * FUNC   : th_ticks_per_sec
 *
 * DESC   : used to determine the number of timer ticks per second.
 *
 * RETURNS: The number of timer ticks per second returned by th_stop_timer()
 * ---------------------------------------------------------------------------*/

size_t th_ticks_per_sec( void )
{
	return (*thdef->thip_ticks_per_sec)();
}

/*------------------------------------------------------------------------------
 * FUNC   : th_tick_granularity
 *
 * DESC   : used to determine the granularity of timer ticks.
 *
 *          For example, the value returned by th_stop_timer() may be
 *          in milliseconds. In this case, th_ticks_pers_sec() would
 *          return 1000.  However, the timer interrupt may only occur
 *          once very 10ms.  So th_tick_granularity() would return 10.
 *
 *          However, on another system, th_ticks_sec() might return 10
 *          and th_tick_granularity() could return 1.  This means that each
 *          incriment of the value returned by th_stop_timer() is in 100ms
 *          intervals.
 *
 * RETURNS: the granularity of the value returned by th_stop_timer()
 * ---------------------------------------------------------------------------*/

size_t th_tick_granularity( void )
{
	return (*thdef->thip_tick_granularity)();
}

/*------------------------------------------------------------------------------
 * FUNC    : th_malloc_x
 *
 * DESC    : Test Harness malloc()
 *
 *           This works just like malloc() from the standard library.
 *
 * PARAMS  : size - is the size of the memory block neded
 *           file - the __FILE__ macro from where the call was made
 *           line - the __LINE__ macro from where the call was made
 *
 * NOTE    : This function is usually invoked by using th th_malloc()
 *           macro.
 *
 * RETURNS : A void pointer to the allocated block.  Use a cast to asssign
 *           it to the proper poitner type.
 *           The NULL value is returned if a block ofthe specified size cannot
 *           be allocated.
 * ---------------------------------------------------------------------------*/

void *th_malloc_x( size_t size, const char *file, int line )
{
	return (*thdef->thip_malloc) ( size, file, line );
}

/*------------------------------------------------------------------------------
 * FUNC    : th_free_x
 *
 * DESC    : Test Harness free()
 *
 *           This works just like free() from the standard library.
 *
 * PARAMS  : ptr - points to the block pointer returned by th_malloc().
 *           file - the __FILE__ macro from where the call was made
 *           line - the __LINE__ macro from where the call was made
 *
 * NOTE    : This function is usually invoked by using th th_free()
 *           macro.
 *
 * NOTE    : It is valid to pass the null pointer to this function.
 * ---------------------------------------------------------------------------*/

void th_free_x( void *block, const char *file, int line )

   {
   ( *thdef->thip_free ) ( block, file, line );
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_heap_reset()
 *
 * DESC   : Resets the heap to its initialized state
 *
 *          Calling this function implicitly free's all the memory which
 *          has been allocated with th_malloc()
 * ---------------------------------------------------------------------------*/

void th_heap_reset( void )

   {
   ( *thdef->thip_heap_reset )();
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_signal_start()
 *
 * DESC   : Signals the host system the test has started
 *
 *          Calling this function signals the host system that the test
 *          has actually started.  The host uses this signal to begin
 *          measuring the duration of the test (bench mark).
 *
 *          If a target based timer is avaialable, this this function will
 *          also start the target's timer.
 * ---------------------------------------------------------------------------*/

void th_signal_start( void )

   {
   ( *thdef->thip_signal_start )();
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_signal_finished
 *
 * DESC   : Signals the host that the test is finished
 *
 *          This function is called to signal the host system that the
 *          currently executing test or benchmark is finished.  The host
 *          uses this signal to mark the stop time of the test and to
 *          measure the duration of the test.
 *
 * RETURNS: The duration of the test in 'ticks' as measured by the target's
 *          timer (if one is available).  If the target does not have a timer,
 *          or it is not supported by the TH, then this function returns
 *          TH_UNDEF_VALUE.
 *
 * NOTE   : There are intentionally no parameters for this function.  It is
 *          designed to have very low overhead. It causes a short message to
 *          be sent to the host indicating.  The results of the test are
 *          reported using another function.
 * ---------------------------------------------------------------------------*/

size_t th_signal_finished( void )

   {
   return (*thdef->thip_signal_finished)();
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_exit
 *
 * DESC   : Used to exit a test or benchmark with an error message
 *
 *          Both a numeric value and a ASCII string are reported to the
 *          host.
 *
 * NOTE   : This can be called at any time to indicate that
 *          a test has finihsed.  This function does return.  Calling this
 *          function DOES imply that the test is finished.
 * ---------------------------------------------------------------------------*/

void th_exit( int exit_code, const char *fmt, ... )

   {
   va_list args;
   va_start( args, fmt );
   ( *thdef->thip_exit ) ( exit_code, fmt, args );
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_report_results
 *
 * DESC   : Used to report a test's results after it is finished
 *
 *          This function is used to report the results of a test after
 *          it has run.  It must only be called after a call to
 *          th_finished() call.
 * ---------------------------------------------------------------------------*/

int th_report_results( const THTestResults *results, e_u16 Expected_CRC )
{
   return ( *thdef->thip_report_results ) ( results, Expected_CRC );
}

/*------------------------------------------------------------------------------
 * FUNC   : th_harness_poll
 *
 * DESC   : Gives the test harness some CPU time.
 *
 *          This function can be called during the execution of a test
 *          or benchmark to give the test harness some execution time so it
 *          can respond to commands from a host.
 *
 * CAVEAT : Only debug or test versions of true bench marks should call this
 *          function as it uses CPU time.
 *
 * RETURNS: TRUE if the test should keep running.
 *          FALSE if the stop message has been received form the host
 *          and the benchmark or test should stop.
 * ---------------------------------------------------------------------------*/

int th_harness_poll( void )

   {
   return (*thdef->thip_harness_poll)();
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_get_file_def
 *
 * DESC   : Gets the file defintion (FileDef*) for a specific file
 *
 *          Give a file name, this function returns a pointer to the file
 *          defintion structure for the file.  If the file does not exist
 *          then NULL is returned.
 *
 *          The FileDef structure is documented in the THLIB.H file.
 *
 *          Note file name matches are NOT case sensitive.
 *
 * PARAMS : fn - a pointer to a string containing the file name
 *
 * RETURNS: A pointer to the FileDef struct
 *          or NULL if the file has not yet been downloaded
 * ---------------------------------------------------------------------------*/

const FileDef *th_get_file_def( const char *fn )

   {
   return (*thdef->thip_get_file_def) ( fn );
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_get_file_def
 *
 * DESC   : Gets the file defintion (FileDef*) for a specific file
 *
 *          Give a file number index, this function returns a pointer to the
 *          file defintion structure for the file.  If the file does not exist
 *          then NULL is returned.
 *
 *          The FileDef structure is documented in the THLIB.H file.
 *
 * PARAMS : index - The index of the file to find.  The most recent file
 *                  downloaded has an index number of zero. The previous file
 *                  has index 1. etc. etc
 *
 * RETURNS: A pointer to the FileDef struct
 *          or NULL if the file has not yet been downloaded
 * ---------------------------------------------------------------------------*/

const FileDef *th_get_file_num( int idx )

   {
   return (*thdef->thip_get_file_num) ( idx );
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_send_buf_as_file
 *
 * DESC   : Sends a buffer (as a file) to the host using ZMODEM
 *
 *          This function sends the contents of a buffer to the host
 *          system using the ZMODEM protocol.  The buffer ends up on the
 *          host system with the specified file name.
 *
 * PARAMS : buf    - a pointer to the buffer to send
 *          length - the length of the buffer
 *          fn     - the name to use on the host system.
 *
 * RETRUNS: Success of the file was succesfully sent.
 *          Failure otherwise.
 *
 * CAVEAT : Note that if a file exists on the remote system it will
 *          be overwritten.
 *----------------------------------------------------------------------------*/

int th_send_buf_as_file( const char* buf, BlockSize length, const char* fn )

   {
   return (*thdef->thip_send_buf_as_file)( buf, length, fn );
   }


/*------------------------------------------------------------------------------
 * Malloc and Free Mapping
 *----------------------------------------------------------------------------*/

#if MAP_MALLOC_TO_TH
/*
 * If this is called by OS or crt0 thip will not be initialized, and
 * we need to give up. Attempt to return Error 8.
 */
void * malloc( size_t foo )
{
	if (thdef)
		return th_malloc( foo );
	else {
		exit(THE_OUT_OF_MEMORY);
	}
}

void free( void* ptr )
{
	if (thdef)
		th_free( ptr );
}

#endif

