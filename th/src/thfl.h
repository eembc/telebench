/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef   THFL_H        /* File Sentinal */
#define   THFL_H

#include "thcfg.h"
#include "thfli.h"

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------
 * The one and only globaly defined THDef structure
*/
extern THDef the_thdef;

/*------------------------------------------------------------------------------
 * Interface Functions
*/

int    i_printf( const char *fmt, va_list args );
int    i_sprintf( char *str, const char *fmt, va_list args );
int    i_sends( const char *str );
int    i_putchar( char c );
int    i_write_con( const char *buf, size_t buf_size );
size_t i_read_con( char *buf, size_t buf_size );
size_t i_con_chars_avail( void );

FP     i_open( const char file_name, int oflag );
int    i_read( const FP file_ptr, char *buf, size_t buf_size );
int    i_write( const FP file_ptr, const char *buf, size_t buf_size );
int    i_close( FP file_ptr );

int    i_is_timer_running( void );
size_t i_ticks( void );
size_t i_ticks_per_sec( void );
size_t i_tick_granularity( void );

void *i_malloc( size_t size, const char *fn, int line );
void   i_free( void *block, const char *fn, int line );
void   i_heap_reset( void );

void   i_signal_start( void );
size_t i_signal_finished( void );
void   i_exit( int exit_code, const char *fmt, va_list args );
int    i_report_results( const THTestResults * results, e_u16 Expected_CRC );

int    i_enter_critical_section( void );
void   i_leave_critical_section( int cs_flag );
int    i_harness_poll( void );

FileDef *i_get_file_def( const char *fn );
FileDef *i_get_file_num( int n );

int i_send_buf_as_file( const char* buf, BlockSize length, const char* fn );

/*----------------------------------------------------------------------------*/

int th_main( int argc, const char *argv[] );

int xlate_nl( const char *str, char *dest_buf );
int xlate_nl_inplace( char *str );

int t_printf( const char *fmt, ... );
int t_sprintf( char* str, const char *fmt, ... );
void t_exit( int exit_code, const char *fmt, ... );

const char *efn( const char *fn );

#define SOURCE_FILE efn( __FILE__ )

void __assertfail( const char *msg, const char *cond, const char *file, int line );
void __fatal( const char *msg, const char *file, int line );

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
   }
#endif

#endif                /* File Sentinal */

/*==============================================================================
 * FOOT NOTES :
 *
 * FN#1 : This is a foot note
 *
 *------------------------------------------------------------------------------
 * HISTORY:
 *
 * $Log: thfl.h,v $
 * Revision 1.4  2002/08/06 21:57:16  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.3  2002/04/23 18:33:56  rick
 * Match eembc_dt with Lite, remove stdinc.h
 *
 * Revision 1.2  2002/03/21 22:31:10  rick
 * Network Harness, and empty benchmark fixes
 *
 * Revision 1.1  2002/02/15 19:26:40  rick
 * Networking converstion to TH_Lite
 *
 * Revision 1.1  1999/11/06 15:11:21  Richard.Russell
 * Initial revision
 * Revision 1.1  1999/10/18 23:10:03  richardr
 * Initial revision
 * Revision 1.1  1999/10/18 22:47:58  richardr
 * Initial revision
 * Revision 1.1  1999/10/18 22:15:59  richardr
 * Initial revision
 * Revision 1.7  1999/03/02 15:09:53  rrussell
 * Updated for V3.1
 * Revision 1.6  1999/01/22 13:50:04  rrussell
 * Made strictly ANSI 'C'
 * Revision 1.5  1999/01/20 19:46:06  rrussell
 * All comments are now C Style
 * Cimples clean with GCC -ansi and -pedantic
 * Revision 1.4  1999/01/15 13:29:09  rrussell
 * Checking before port-a-thon
 * Revision 1.3  1999/01/15 13:29:09  rrussell
 * Intermediate check in.
 * Revision 1.2  1998/10/12 19:49:45  rrussell
 * Added support for
 *   - new heap manager
 *   - using either the heap manager or the compilers malloc
 *   - assert and fatal
 * Revision 1.1  1998/10/01 13:51:54  rrussell
 * Initial revision
 *
 * -----------------------------------------------------------------------------
 * ENDOF  : TEMPL.H
 * ===========================================================================*/
