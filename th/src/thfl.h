/*==============================================================================
 *$RCSfile: thfl.h,v $
 *
 *   DESC : Test Harness routines for benchmarks
 *
 * AUTHOR : ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.4 $
 *          $Date: 2002/08/06 21:57:16 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th/src/thfl.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
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
