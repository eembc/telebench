/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#include "thcfg.h"

#include <string.h>
#include <ctype.h>

#if !USE_TH_PRINTF
/* get the compiler's printf stuff
#include <stdarg.h>
 */
#include <stdlib.h>	/* atol */
#include <stdio.h>
#endif

#include "thfl.h"
#include "thfli.h"
#include "printfe.h"
#include "thal.h"
#include "therror.h"
#include "heap.h"
#include "memmgr.h"
#include "ssubs.h"
#include  "uuencode.h"

/*------------------------------------------------------------------------------
 * Local Data
 */

#define CMD_BUF_SIZE    (16)

#define IN_BUF_SIZE (CMD_LINE_SIZE + CMD_BUF_SIZE + 1)
#define CL_BUF_SIZE IN_BUF_SIZE

static char  inbuf[ IN_BUF_SIZE ];
static char  clbuf[ CL_BUF_SIZE ];

static const char* argva[ MAX_ARGC ];
static int         argca =0;
static const char* argv0_pgm = NULL;  /* the programs argv[0] */

static TCDef *the_tcdef_ptr = NULL;

/* Global for matrix */
LoopCount iterations = 0;

static int autogo = FALSE;

/*==============================================================================
 *             -- Funcational Layer Interface Functions --
 *============================================================================*/

/*------------------------------------------------------------------------------
 * FUNC   : i_printf
 *
 * DESC   : Functional Layer implimentation of th_printf()
 *
 *          This function sends a string to the logical console I/O channel.
 *          '\n' characters are translated to the '\r\n' sequence.
 *
 * RETURNS: The number of charactrers printf'ed
 * ---------------------------------------------------------------------------*/

int i_printf( const char *fmt, va_list args )

   {
   int len;

   vsprintf( pf_buf, fmt, args );  /* Do the printf stuff */

#if !defined( NO_CRLF_XLATE )
   len = xlate_nl_inplace( pf_buf ); /* Translate '\n' to '\r\n' */
#else
   len = strlen( pf_buf );
#endif

   if (al_write_con( pf_buf, (size_t) len ) == Success) /*lint !e571*/
      return len;
   else
      return 0;
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_sprintf
 *
 * DESC   : Functional layer implimentation of th_printf()
 *
 * RETURNS: the number of characters printf'ed
 * ---------------------------------------------------------------------------*/

int i_sprintf( char *str, const char *fmt, va_list args )

   {
   /* this comes from the printf engine built into the TH or from the
    * compiler's C library.
   */
   return vsprintf( str, fmt, args );
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_sends
 *
 * DESC   : Functinoal layer implimentation of th_sends()
 *
 *          This function sends a null termianted string to the logical
 *          console I/O channel. '\n' characters are translated to
 *          the '\r\n' sequence.
 *
 * PARAMS : str - points to a string to send.  If this is NULL, then this
 *                function just returns the value '1';
 *
 * RETURNS: A nonnegative value if successful. If it fails in any
 *          way it returns -1.  Note, in the failure case, none-some-or-all
 *          of the string may have been sent.
 * ---------------------------------------------------------------------------*/

int i_sends( const char *str )

   {
   int len;

   if (str == NULL)
      return 1;

#if !defined( NO_CRLF_XLATE )
   len = xlate_nl( str, pf_buf );
   if (al_write_con( pf_buf, (size_t) len ) != Success) /*lint !e571*/
      return -1;
   else
      return  1;
#else
   len = strlen( str );
   if (al_write_con( str, (size_t) len ) != Success) /*lint !e571*/
      return -1;
   else
      return  1;
#endif

   }
/*------------------------------------------------------------------------------
 * FUNC   : i_putchar
 *
 * DESC   : Functional layer implimentation of th_putchar()
 *
 *          This function sends a character to the logical
 *          console I/O channel. A '\n' characters is translated to
 *          the '\r\n' sequence.
 *
 * PARAMS : c - the character to send
 *
 * PORTING: You should not need to modify this function
 *
 * RETURNS: the character sent.  If there was an error, then -1 is returned.
 *          In the error case, the character may have been sent
 *          (there is no way to tell).
 * ---------------------------------------------------------------------------*/

int i_putchar( char c )

   {
#if !defined( NO_CRLF_XLATE )
   const char cr = '\r';

   if ( c == '\n' && al_write_con( &cr, 1 ) != Success )
      return -1;
#endif

   if ( al_write_con( &c, 1 ) != Success )
      return -1;

   /* Note, we 'and' the character with 0xFF >after< casting to to an
    * int so that the all F's value for the character (-1) will not
    * get cast to a -1 int.
   */
   return (int) c & 0xFF;
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_write_con
 *
 * DESC   : functional layer implimentation of th_write_con()
 * ---------------------------------------------------------------------------*/

int i_write_con( const char *buf, size_t buf_size )

   {
   return al_write_con( buf, buf_size );
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_read_con
 *
 * DESC   : functional layer implimentation of th_read_con()
 * ---------------------------------------------------------------------------*/

size_t i_read_con( char *buf, size_t buf_size )

   {
   return al_read_con( buf, buf_size );
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_con_chars_avail
 *
 * DESC   : functional layer implimentation of th_con_chars_avail()
 * ---------------------------------------------------------------------------*/

size_t i_con_chars_avail( void )

   {
   return al_con_chars_avail();
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_ticks_per_sec
 *
 * DESC   : functional layer implimentation of th_ticks_per_sec()
 * ---------------------------------------------------------------------------*/

size_t i_ticks_per_sec( void )

   {
   return al_ticks_per_sec();
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_tick_granularity
 *
 * DESC   : functional layer implimentation of th_tick_granularity()
 * ---------------------------------------------------------------------------*/

size_t i_tick_granularity( void )

   {
   return al_tick_granularity();
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_malloc
 *
 * DESC   : functional layer implimentation of th_malloc()
 * ---------------------------------------------------------------------------*/

void *i_malloc( size_t size, const char *file, int line )

   {
#if HAVE_MALLOC_H
	file=file;
	line=line;
	return	malloc(size);
#elif COMPILE_OUT_HEAP
	size=size;
	t_printf( "** ERROR: Heap Routines are compiled out! %s:%d\n", file, line );
	t_exit( 1, "\n" );
	/* 
	 * NOTE : If this code executes, then the heap routines have been compiled
	 *        out by setting the COMPILE_OUT_HEAP define in THCFG.H.
	 *        This means you CANNOT run benchmarks that need the heap!
	 */
	return NULL;
#else
   void *block = heap_alloc( th_heap, size );

   if (block == NULL)
      {
         t_printf( "** ERROR:  Out Of memory! size=%ld %s:%d\n", size, file, line );
         t_exit( 1, "--      :  Detected in %s:%d\n", file, line );
      }

   return block;
#endif
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_free
 *
 * DESC   : functional layer implimentation of i_free()
 * ---------------------------------------------------------------------------*/

void i_free( void *block, const char *file, int line )

   {
#if HAVE_MALLOC_H
	file=file;
	line=line;
	free(block);
#elif COMPILE_OUT_HEAP
/* do nothing */
	file=file;
	line=line;
	block=block;
#else
	file=file;
	line=line;
	heap_free( th_heap, block );
#endif
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_heap_reset
 *
 * DESC   : functional layer implimentation of th_heap_reset()
 * ---------------------------------------------------------------------------*/

void i_heap_reset()

   {
#if COMPILE_OUT_HEAP
#else
   heap_reset( th_heap );
#endif
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_signal_start
 *
 * DESC   : functional layer implimentation of th_signal_start()
 * ---------------------------------------------------------------------------*/

void i_signal_start( void )

   {
   t_printf( ">> START!\n" ); /* Do before calling adaptaion layer */

   al_signal_start();
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_signal_finished
 *
 * DESC   : functional layer implimentation of th_signal_finished()
 * ---------------------------------------------------------------------------*/

size_t i_signal_finished( void )

   {
   size_t rv;

   rv = al_signal_finished();

   t_printf( ">> FINISHED!\n" );  /* Do this AFTER calling the adaption layer */

   return rv;
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_exit
 *
 * DESC   : functional layer implimentation of th_exit()
 * ---------------------------------------------------------------------------*/

void i_exit( int exit_code, const char *fmt, va_list args )

   {
   al_exit( exit_code, fmt, args );
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_get_file_def
 *
 * DESC   : functional layer implimentation of th_get_file_def()
 * ---------------------------------------------------------------------------*/

FileDef *i_get_file_def( const char *fn )

   {
   return mem_get_file_def( fn );
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_get_file_num
 *
 * DESC   : functional layer implimentation of i_get_file_num()
 * ---------------------------------------------------------------------------*/

FileDef *i_get_file_num( int n )

   {
   return mem_get_file_num( n );
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_send_buf_as_file
 *
 * DESC   : functional layer implimentation of i_send_buf_as_file()
 * ---------------------------------------------------------------------------*/

int i_send_buf_as_file( const char* buf, BlockSize length, const char* fn )

   {
	return uu_send_buf ( buf, length, fn ); 
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_report_results
 *
 * DESC   : functional layer implimentation of th_report_results()
 * ---------------------------------------------------------------------------*/

int i_report_results( const THTestResults *results, e_u16 Expected_CRC )
{
int	exit_code = Success;

/* Used to unload double from two vx results variables */ 
#if	VERIFY_FLOAT && FLOAT_SUPPORT
	typedef union {
		double	d;
		size_t	v[2];
	} d_union;
	d_union	dunion;
#endif

/* Standard Results Section */

#if		CRC_CHECK
t_printf(  "--  Intrusive CRC     = %4x\n",results->CRC);
#elif	NON_INTRUSIVE_CRC_CHECK
t_printf(  "--  Non-Intrusive CRC = %4x\n",results->CRC);
#else
t_printf(  "--  No CRC check      = 0000\n"); 
#endif
t_printf(  "--  Iterations        = %5u\n", results->iterations );
t_printf(  "--  Target Duration   = %5u\n", results->duration );
#if		VERIFY_INT
t_printf(  "--  v1                = %d\n", results->v1);
t_printf(  "--  v2                = %d\n", results->v2);
t_printf(  "--  v3                = %d\n", results->v3);
t_printf(  "--  v4                = %d\n", results->v4);
#endif
#if		VERIFY_FLOAT && FLOAT_SUPPORT
dunion.v[0]	= results->v1;
dunion.v[1] = results->v2;
t_printf(  "--  v1v2              = %f\n", dunion.d);
dunion.v[0]	= results->v3;
dunion.v[1] = results->v4;
t_printf(  "--  v3v4              = %f\n", dunion.d);
#endif

#if		FLOAT_SUPPORT
   if (results -> duration > 0)
      {
      double fduration;
      double fiterations;
      double ticks_per_sec;
      double its_per_sec;

      /* Ok, lets do this in floating point.... */

      fduration = results -> duration;
	  fiterations = results->iterations;
      ticks_per_sec = th_ticks_per_sec();

      its_per_sec = fiterations / ( fduration / ticks_per_sec );

      th_printf( "--  Iterations/Sec  = %12.3f\n", its_per_sec );
      th_printf( "--  Total Run Time  = %12.3fsec\n", fduration / ticks_per_sec );
      th_printf( "--  Time / Iter     = %18.9fsec\n", 1.0 / its_per_sec );
      }
#endif

   if (results -> info != NULL && results -> info[ 0 ] != '\0')
      t_printf( "-- Info             = %s\n", results -> info );

   /* Failure Section */
#if		CRC_CHECK || NON_INTRUSIVE_CRC_CHECK
	if( results->CRC != Expected_CRC ){
		t_printf("--  Failure: Actual CRC %x, Expected CRC %x\n",results->CRC,Expected_CRC);
		exit_code = Failure;
	} 
#endif

	if (iterations != results->iterations) {
		t_printf("--  Failure: Actual iterations %x, Expected iterations %x\n",results->iterations,iterations);
		exit_code = Failure;
	}

	return	exit_code;
}

/*------------------------------------------------------------------------------
 * FUNC   : i_harness_poll
 *
 * DESC   : Functional layer implimentation of th_harness_poll()
 *
 *          This function is called periodically ( via th_harness_poll() )
 *          while a benchmark is running.  It detects if the user has
 *          requested that the test or benchmark stop.  This is done by
 *          sending the 3 escape characters in a row.
 *
 * RETURNS: TRUE if the benchmark should continue to run
 *          FALSE to stop the currently running bencmark
 *
 * NOTE   : If BMDEBUG is defined as FALSE, then this function will >always<
 *          return TRUE so that a benchmark that calls it always runs.
 *
 *        : Since the variable 'c' is static, this function is not re-entrant
 *          but this should not be a problem.
 * ---------------------------------------------------------------------------*/

int i_harness_poll( void )

   {
#if BMDEBUG
   static char c;
   static int esc_cnt = 0;

   if (al_con_chars_avail() > 0)
      {
      /* we have at least one character available -> read it */
      if ( al_read_con( &c, 1 ) > 0 )
         {
         if ( c == '\033' )
            {
            if ( ++esc_cnt >= 3 )
               return FALSE;  /* Received 3 escapes in a row. */
            }
         else
            {
            esc_cnt = 0;
            return TRUE;
            }
         }
      }
#endif

   return TRUE;
   }

/*==============================================================================
 *                  -- Funcational Layer Implimenation --
 * ===========================================================================*/

#if		!HAVE_ASSERT_H
/*------------------------------------------------------------------------------
 * FUNC   : __assertfail
 *
 * DESC   : Called by the assert() macro when a condition fails
 *
 * NOTE   : Does not return!
 * ---------------------------------------------------------------------------*/

void __assertfail( const char *msg, const char *cond, const char *file, int line )

   {
   t_exit( 2, msg, cond, efn( file ), line );
   }

/*------------------------------------------------------------------------------
 * FUNC   : __fatal
 *
 * DESC   : called when a fatal error is encountered
 * ---------------------------------------------------------------------------*/

void __fatal( const char *msg, const char *file, int line )

   {
   t_exit( 2, msg, efn( file ), line );
   }
#endif

/*------------------------------------------------------------------------------
 * FUNC   : report_info
 *
 * DESC   : Reports the system info to the use or HCP
 * ---------------------------------------------------------------------------*/

static void report_info( void )
{
   t_printf( ">>------------------------------------------------------------\n" );
   t_printf( ">> EEMBC Component          : %s\n", the_thdef . desc );
   t_printf( ">> EEMBC Member Company     : %s\n", the_thdef . member );
   t_printf( ">> Target Processor         : %s\n", the_thdef . processor );
   t_printf( ">> Target Platform          : %s\n", the_thdef . platform );
   t_printf( ">> Target Timer Available   : %s\n", the_thdef . target_timer_avail ? "YES" : "NO" );
   t_printf( ">> Target Timer Intrusive   : %s\n", the_thdef . target_timer_is_intrusive ? "YES" : "NO" );
   t_printf( ">> Target Timer Rate        : %d\n", th_ticks_per_sec());
   t_printf( ">> Target Timer Granularity : %d\n", th_tick_granularity());
#if	CRC_CHECK
   t_printf( ">> Required Iterations      : %d\n", the_tcdef_ptr->rec_iterations);
#else
   t_printf( ">> Recommended Iterations   : %d\n", the_tcdef_ptr->rec_iterations);
#endif
   if (iterations != the_tcdef_ptr->rec_iterations)
   t_printf( ">> Programmed Iterations    : %d\n", iterations );
   t_printf( ">> Bench Mark               : %s\n", the_tcdef_ptr->desc );
}

/*------------------------------------------------------------------------------
 * FUNC   : dectost
 *
 * DESC   : Decimal to size_t
 *
 *          Converts ascii decimal digits to a size_t value.
 * ---------------------------------------------------------------------------*/

static size_t dectost( const char *sp )

   {
   int i;
   size_t rslt = 0;

   for (i = 0; isdigit( *sp ) && i < 10; sp++, i++)
      {
      rslt *= 10;

      rslt += ( *sp - '0' ); /*lint !e737*/
      }

   return (rslt);
   }

/*------------------------------------------------------------------------------
 * FUNC   : fisrt_digit
 *
 * RETURNS: A pointer to the first digit in a string
 * ---------------------------------------------------------------------------*/

static const char *first_digit( const char *s )

   {
   while (*s)
      if (*s >= '0' && *s <= '9')
         return s;
      else
         s++;

   return NULL;
   }

/*------------------------------------------------------------------------------
 * FUNC   : set_cmd_line
 *
 * DESC   : Sets up the command line for the benchmark
 * ---------------------------------------------------------------------------*/

static void set_cmd_line( const char* input )

   {
   char* s = clbuf;

   /*
    * NOTE: if the benchmark command line (stored in 'input') is
    * declared, we still set argca to 1 and point argva[0] to a non-null
    * string.
    */

   argca    = 1;
   if ( argv0_pgm != NULL )
      argva[0] = argv0_pgm;  /* use the one from the executable's cmd line */
   else
      argva[0] = "TH";       /* just use a default value */
   argva[1] = NULL;

   if ( input == NULL || *input == '\0' )
      return;

   cpystr( clbuf, input, CL_BUF_SIZE );

   for(;;)
      {
      /* skip past leading spaces */
	   while (isspace(*s)) s++;

      if ( *s == '\0')
         {
         break;
         }
      else
         {
         /* point to the argument */
         argva[ argca ] = s;
         argca++;
         }

      /* find the end of the argument */
      while( *s && !isspace(*s) ) s++;

      *s++ = '\0'; /* Terminate the argument */
      }

   argva[ argca ] = NULL;
   }

/*------------------------------------------------------------------------------
 * FUNC   : get_next_sub_string
 *
 * DESC   : Gets the next space delimited sub string from a string
 *
 * PARAMS : cmd_buf - the sub-string is copied to this buffer
 *          s       - this is the source string
 *
 * RETURNS: Returns a pointer to the next charcter from the source
 *          string to scan.  Returns NULL '\0' if its done and there
 *          are no more sub-strings.
 * ---------------------------------------------------------------------------*/

static const char *get_next_sub_string( char *cmd_buf, const char *s, int max_len )

   {
   int len = 0;

   /* skip past leading spaces */
   while (isspace(*s)) s++;

   if (*s == '\0')
      {
      *cmd_buf = '\0';
      return 0;
      }

   while (*s > ' ' && *s <= '~')
      {
      if (( ++len ) < max_len)   /* pre-increment on purpose */
         *cmd_buf++ = *s++;
      else
         s++;
      }

   *cmd_buf = '\0';

   return s;

   /* note, the pre-increment of len in the above if statement
    * allows room for the terminating null character in the cmd_buf.  Eg.
    * If max_len== 2 then you can put 1 character pluss the terminating
    * null charcter in the cmd_buf.
   */
   }

/*------------------------------------------------------------------------------
 * FUNC   : parse_command
 *
 * DESC   : parses commands
 *
 * RETURNS: Returns one of
 *             KEEP_COMMANDING  keep parsing commands
 *             RUN_BENCHMARK    run the benchmark or test
 *             USER_EXIT        exit the TH
 * ---------------------------------------------------------------------------*/
#define AUTOGO	FALSE
#define KEEP_COMMANDING 1
#define RUN_BENCHMARK   2
#define USER_EXIT       3

static int parse_command( const char *in_buf )

   {
   size_t      its;
   const char *s;
   char        cmd_buf[ CMD_BUF_SIZE ];

   s = get_next_sub_string( cmd_buf, in_buf, CMD_BUF_SIZE );

   /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 'n' -- Check for the iterations command
   */

   if (str_icmp( cmd_buf, "n" ) == 0)
      {
      if (( s = first_digit( s )) != NULL)
         {
         its = dectost( s );

         if (its > 0)
            {
            iterations = its;
            }
         else
            {
            t_printf( "{ Reset iterations to recommended value }\n\n" );
            iterations = the_tcdef_ptr->rec_iterations;
            }

         if (sizeof( size_t ) == sizeof( int ))
            t_printf( ">> Iterations : %u\n", iterations );
         else
            t_printf( ">> Iterations : %lu\n", iterations );
         }
      }

   /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 'g' -- Check for the go command
   */

   if (str_icmp( cmd_buf, "g" ) == 0)
      return RUN_BENCHMARK;

   /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 'I' -- Check for the info command
   */

   if (str_icmp( cmd_buf, "i" ) == 0)
      {
      report_info();
      }

   /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 'DIR' -- Dump the files that have been downloaded
   */

   if (str_icmp( cmd_buf, "dir" ) == 0)
      mem_report_files();

   /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 'DNF' -- Delete Newest File
   */

   if (str_icmp( cmd_buf, "dnf" ) == 0)
      {
      mem_delete_newest_file();                   /*list !534*/
      t_printf( "\nNewest File Deleted\n" );
      }

   /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 'DAF' -- Delete All Files
   */

   if (str_icmp( cmd_buf, "daf" ) == 0)
      {
      if ( mem_get_file_num( 0 ) == NULL )
         {
         t_printf( "\nNo Files to delete\n\n" );
         }
      else
         {
         mem_delete_all_files();
         t_printf( "\nAll Files Deleted\n\n" );
         }
      }

   /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 'mem' -- Report memory info
   */

   if (str_icmp( cmd_buf, "mem" ) == 0)
      {
      mem_report_info();
      }

   /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 'EXIT' -- Exit the TH
   */

   if (str_icmp( cmd_buf, "exit" ) == 0)
      {
      mem_delete_all_files();
      return USER_EXIT;
      }

   /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 'cl' -- Set the command line
   */

   if (str_icmp( cmd_buf, "cl" ) == 0)
      {
      if ( is_all_white_space( s ) )
         {
         int i;

         t_printf( "\n-- Benchmark Command Line, ARGS:%d\n\n", argca );

         for( i = 0; i < argca; i++ )
            t_printf( "   ARG%d: '%s'\n", i, argva[i] );
         }
      else
         {
         set_cmd_line( s );
         t_printf( "\n-- Command line set\n" );
         }

      return KEEP_COMMANDING;
      }

   /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 'zcl' -- zap the command line
   */

   if (str_icmp( cmd_buf, "zcl" ) == 0)
      {
      t_printf( "\n-- Zap Benchmark Command Line\n", argca );

      set_cmd_line( "" );

      return KEEP_COMMANDING;
      }

   /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 'ver' -- The Version Command
   */

   if (str_icmp( cmd_buf, "ver" ) == 0)
      {
      t_printf( ">> TH: %s\n", the_thdef.desc );
      t_printf( ">> BM: %s\n", the_tcdef_ptr->desc );
      t_printf( ">> ID: %s\n", the_tcdef_ptr->eembc_bm_id );

      return KEEP_COMMANDING;
      }

   /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 'sff' -- Send First File.  This is an undocumented test function
    *          It sends the first file in the memory manager.
   */

   if (str_icmp( cmd_buf, "sff" ) == 0)
      {
      FileDef *fd;

      t_printf( "Send First File\n" );

      if ( (fd=mem_get_file_num( 0 )) == NULL )
         {
         t_printf( "\nNo Files to send\n\n" );
         }
      else
         {
		 uu_send_buf ( fd->buf, fd->size, fd->name ); 
         }

      return KEEP_COMMANDING;
      }

   /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 'h' 'help' '?'  -- help
   */
#if !BE_SMALL
   if (str_icmp( cmd_buf, "h" ) == 0 ||
       str_icmp( cmd_buf, "help" ) == 0 ||
       str_icmp( cmd_buf, "?" ) == 0
     )
      {
      t_printf( "\n-- Commands -- \n" );
      t_printf( "n <number>   : set the number of test iterations(n 0 to reset to default)\n" );
      t_printf( "g            : go, run the benchmark or test\n" );
      t_printf( "i            : show a bunch of nifty info\n" );
      t_printf( "cl <text>    : set the command line to text\n" );
      t_printf( "zcl          : zap the command line\n" );
      t_printf( "dir          : display the downloaded files\n" );
      t_printf( "dnf          : delete the newest file\n" );
      t_printf( "daf          : delete all the downloaded files\n" );
      t_printf( "mem          : display memory info\n" );
      t_printf( "exit         : exit the test harness\n" );
      t_printf( "ver          : dump version of TH and BM\n" );
      t_printf( "\n" );
      }
#endif

   return KEEP_COMMANDING;
   }

/*------------------------------------------------------------------------------
 * FUNC   : wait_for_start_signal
 *
 * DESC   : Waits for a start signal from the user or the HCP
 *
 * RETURNS: Returns one of
 *             KEEP_COMMANDING  keep parsing commands
 *             RUN_BENCHMARK    run the benchmark or test
 *             USER_EXIT        exit the TH
 * ---------------------------------------------------------------------------*/

static int wait_for_start_signal( void )

   {
#if AUTOGO
   /* the first time this function si called return RUN_BENCHMARK, the second
    * time its called return USER_EXIT
   */
   static int state = RUN_BENCHMARK;
   if ( state == RUN_BENCHMARK )
      {
      state = USER_EXIT;
      return RUN_BENCHMARK;
      }
   return USER_EXIT;

#else

   int   i;
   char  cc;
   static int state = RUN_BENCHMARK;

   if ( autogo )
      {
      if ( state == RUN_BENCHMARK )
         {
         state = USER_EXIT;
         return RUN_BENCHMARK;
         }
      return USER_EXIT;
      }

   prompt:
   t_printf( "TH +> " );

   i = 0;

   for (;;)
      {
/*      get_some_more:*/

      if (al_con_chars_avail())
         {
         al_read_con( &cc, 1 );
         /* echo the character and put it in the input buffer*/
         if (cc >= ' ' && cc <= '~')
            {
            if ( i < (IN_BUF_SIZE-1) )
               {
               inbuf[ i++ ] = cc;
               inbuf[ i ] = '\0';
               al_write_con( &cc, 1 );
               }
            }

         /* do we have an end-of-line */
         if (cc == '\n' || cc == '\r')
            {
            t_printf( "\n" );

            switch (parse_command( inbuf ))
               {
               case USER_EXIT:         /* exit the TH */
                  t_printf( "\n" );
                  return USER_EXIT;

               case RUN_BENCHMARK:     /* run the benchmark or test */
                  t_printf( "\n" );
                  report_info();
                  return RUN_BENCHMARK;

               default:
                  case KEEP_COMMANDING:   /* keep parsing commands */
                  goto prompt;
               }
            }
         else
            if (cc == '\033')
               return USER_EXIT;
         }
      }
#endif
   }

/*------------------------------------------------------------------------------
 * FUNC   : thpf_sender
 *
 * DESC   : The sender engine for the console printf
 *
 *          This sends characters to the 'logical console'
 * ---------------------------------------------------------------------------*/

#if USE_TH_PRINTF

static int thpf_sender( char c, void *ptr )

   {
   if (i_write_con( &c, 1 ) != Success)
      return 0;
   else
      return 1;
   }

#endif

/*------------------------------------------------------------------------------
 * FUNC   : t_printf
 *
 * DESC   : Printf for the test harness functional layer.
 *
 *          The test harness functional layer needs its own printf which
 *          sends data to the logical console.  This function does exactly
 *          the same thing as th_printf, uses the same printf engine and
 *          the data goes to the same place.
 *
 *          All test harness functional layer code should use this printf()
 *          and not the th_printf() call.
 * ---------------------------------------------------------------------------*/

int t_printf( const char *fmt, ... )

   {
#if USE_TH_PRINTF
   int rv;
   va_list args;
   va_start( args, fmt );
   rv = printfe( thpf_sender, NULL, fmt, args );
   va_end( args );
   return rv;
#else
   /* Not using home grown printf.  Using the one */
   /* from the compiler which built the test harness. */
   /* */
   int rv;
   va_list args;
   va_start( args, fmt );
   rv = i_printf( fmt, args );
   va_end( args );
   return rv;
#endif
   }

/*------------------------------------------------------------------------------
 * FUNC   : t_sprintf
 *
 * DESC   : sprintf for the test harness functional layer.
 *
 *          The test harness functional layer needs its own sprintf.  This
 *          function does exactly
 *          the same thing as th_sprintf, and uses the same printf.
 *
 *          All test harness functional layer code should use this call
 *          and not the th_printf() call.
 * ---------------------------------------------------------------------------*/

int t_sprintf( char* str, const char *fmt, ... )

   {
   int rv;
   va_list args;
   va_start( args, fmt );
   rv = vsprintf( str, fmt, args );
   va_end( args );
   return rv;
   }

/*------------------------------------------------------------------------------
 * FUNC   : t_exit
 *
 * DESC   : Used to exit a test or benchmark
 *
 *          Both a numeric value and a ASCII string are reported to the
 *          host.
 *
 * NOTE   : This can be called at any time to indicate that
 *          a test has finihsed.  This function does return.  Calling this
 *          function DOES imply that the test is finished.
 * ---------------------------------------------------------------------------*/

void t_exit( int exit_code, const char *fmt, ... )

   {
   va_list args;
   va_start( args, fmt );
   al_exit( exit_code, fmt, args );
   }

/*------------------------------------------------------------------------------
 * FUNC   : efn
 *
 * DESC   : returns a pointer to the file name portion of a path
 *
 *          Used to trim off drive letters and directory paths from file
 *          specs.
 *
 * NOTE    : this function assumes that both the '\' and '/' characters
 *           are directory path separators.  E.g. we handle both Microsoft
 *           and Unix style paths.
 *
 * RETURNS : a pointer to the file name
 * ---------------------------------------------------------------------------*/

const char *efn( const char *fn )

   {
   const char *s;
   const char *end;

   /* Find the right most ':' or '/' or '\' in the string */

   for (end = s = fn; *s; s++)
      {
      if (*s == '/' || *s == '\\' || *s == ':')
         end = s + 1;
      }

   return end;
   }

/*------------------------------------------------------------------------------
 * FUNC   : th_main
 *
 * DESC   : The portable (target independent) test harness entry point
 * ---------------------------------------------------------------------------*/

int th_main( int argc, const char *argv[] )

   {
   int rv = Success;
   int i;

   /* First, print out the version of the TH */
   t_printf( "\n------------------------------\n" );
   t_printf( ">> TH: %s\n", the_thdef.desc );


   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

   rv = thlib_main( &the_thdef, &the_tcdef_ptr, argc, argv );

   if (rv != Success)
      {
      t_printf( "\n** FATAL ERROR: %s:%d\n", SOURCE_FILE, __LINE__ );
#if !BE_SMALL
      t_printf(   "   the benchmark or test entry function failed.\n" );
      t_printf(   "   The test cannot run.\n\n" );
#endif
      }
   else
      {

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     * Scan the executable's command line for parameters.
     * Its important to note that this gets done BEFORE we call thlib_main()
    */

    /* For starters, we'll just assume we want to use the recomended
     * iterations.
     *
     *(?) Does tcip_rec_iters return size_t?  Does it get its value from
     *    a size_t data type or a Dword!  Check this out and fix....
    */
    iterations = the_tcdef_ptr->rec_iterations;

    /* remember the program's argv[0] value.  This will get passed to
     * the benchmark.  (see how set_cmd_line() works )
     * If argc <= 0 then the program has no command line and argv[0] for the
     * benchmarks just gets set to a default value.
    */
    if ( argc > 0 )
       argv0_pgm = argv[0];
    else
       argv0_pgm = NULL;

    for ( i = 1; i < argc; i++ )
       {
       if ( strcmp( argv[i], "-AUTOGO" ) == 0 ||
            strcmp( argv[i], "-autogo" ) == 0)
          {
          /* set the autogo flag which makes the benchmark run with no
           * command line input... e.g. it runs and exits
          */
          autogo = TRUE;
          }
#if		!CRC_CHECK
       if ( argv[i][0] == '-' && toupper( argv[i][1] ) == 'I' )
          {
	       if ( strcmp( &argv[i][2], "default" ) == 0 ||
    	        strcmp( &argv[i][2], "DEFAULT" ) == 0 )
        	  {
	            t_printf( "{ Reset iterations to recommended value }\n\n" );
    	        iterations = the_tcdef_ptr->rec_iterations;
    	      }
          else if ( isdigit( argv[i][2] ) )
             {
             /* set the number of iterations from the command line */
             iterations = (LoopCount)atol( argv[i]+2 );
             }
          else if ( i < (argc-1) && isdigit( argv[i+1][0] ) )
             {
             /* set the number of iterations from the command line */
             iterations = (LoopCount)atol( argv[i+1] );
             }
          }
#endif
       }

       /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        * Hey!  Everything is OK!  We have a command line so lets
        * just run the darned thing
       */
       mem_mgr_init(); /* intialize the memory management sub-system */

       if ( argc == 0)
          {
          /* opps, no command line! The target executable doesn't support this
           * so just make the command line empty */
          set_cmd_line( NULL );
          }
       else
          {
          /* Copy the executable's command line to the 'inbuf' buffer
           * and use this to set the command line */

          inbuf[0] = '\0';

          for( i = 1; i < argc; i++ )
             {
			  /* strip the ones we handle in the harness */
	         if ( strcmp( argv[i], "-autogo" ) == 0 ||
                  strcmp( argv[i], "-AUTOGO" ) == 0)
                    continue;
                 /* For the -i option, handle three
                  * cases:  -idefault (case
                  * insensitive), -i<n>, and -i <n>. */
                 if ( argv[i][0] == '-' && toupper( argv[i][1] ) == 'I' )
                 {
                    if (strcmp(&argv[i][2], "default") == 0 ||
                          strcmp(&argv[i][2], "DEFAULT") == 0 ||
                          isdigit(argv[i][2]))
                       continue;
                    else if (i < (argc-1) && isdigit(
                                argv[i+1][0]))
                    {
                       /* Skip over the next argument, the
                        * numeric argument, as well. */
                       i++;
                       continue;
                    }
                 }

             strcat( inbuf, argv[i] );
             strcat( inbuf, " " );
             }

          set_cmd_line( inbuf );
          }

      /* Now: gather commands and run benchmarks, as directed by the user */
      for(;;)
         {
         t_printf( ">> BM: %s\n", the_tcdef_ptr->desc );
         t_printf( ">> ID: %s\n\n", the_tcdef_ptr->eembc_bm_id );

         switch( wait_for_start_signal() )
            {
            case KEEP_COMMANDING:
               break;

            case RUN_BENCHMARK:
               mem_heap_initialize();  /* start the heap up! */

               /* Ok, now go execute the test.... */
               rv = the_tcdef_ptr->tcip_run_test( iterations, argca, argva );

               if ( rv == SUCCESS )
                  t_printf( ">> DONE!\n" );
               else
                  t_printf( ">> Failure: %d\n", rv );
               /* 
                * user defined print information
                * outside fixed standard log so automated scripts still work
                */
               al_report_results();
            break;

            default:
            case USER_EXIT:
               t_printf( ">> USER EXIT!\n" );
               return Success;
            }
         }
      }

   return rv;
   }


/*==============================================================================
 * Check to make sure we have everytyhing we need from THCFG.H
 *
 * If you get one of these error messages, it means that the TH requires
 * a defintion that is not in the version of THCFG.H you are using.  You
 * probably need to add configuration macro's to your THCFG.H from the
 * latest TH release.
 */

#ifndef EEMBC_MEMBER_COMPANY
#error EEMBC_MEMBER_COMPANY Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef EEMBC_PROCESSOR
#error EEMBC_PROCESSOR Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef EEMBC_TARGET
#error EEMBC_TARGET Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef TARGET_MAJOR
#error TARGET_MAJOR Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef TARGET_MINOR
#error TARGET_MINOR Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef TARGET_STEP
#error TARGET_STEP Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef TARGET_REVISION
#error TARGET_REVISION Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef CMD_LINE_SIZE
#error CMD_LINE_SIZE Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef MAX_ARGC
#error MAX_ARGC Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef EE_BIG_ENDIAN
#error EE_BIG_ENDIAN Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef EE_LITTLE_ENDIAN
#error EE_LITTLE_ENDIAN Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef FLOAT_SUPPORT
#error FLOAT_SUPPORT Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef USE_TH_PRINTF
#error USE_TH_PRINTF Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef TURN_ON_VERIFY_HEAP
#error TURN_ON_VERIFY_HEAP Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef TURN_ON_DEBUG_HEAP
#error TURN_ON_DEBUG_HEAP Not Defined, Your THCFG.H file needs to be updated
#endif
#ifndef MAP_MALLOC_TO_TH
#error MAP_MALLOC_TO_TH Not Defined, Your THCFG.H file needs to be updated
#endif
#ifdef EEMBC_BIG_ENDIAN
#error EEMBC_BIG_ENDIAN should be EE_BIG_ENDIAN, Your THCFG.H file needs to be updated
#endif
#ifdef EEMBC_LITTLE_ENDIAN
#error EEMBC_LITTLE_ENDIAN should be EE_LITTLE_ENDIAN, Your THCFG.H file needs to be updated
#endif

