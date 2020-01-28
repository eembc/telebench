/*==============================================================================
 *$RCSfile: thlib.h,v $
 *
 *   DESC : Test Harness Library Interface
 *
 *  EEMBC : Network Subcommittee 
 *
 *    CVS : $Revision: 1.6 $
 *          $Date: 2002/08/06 21:57:16 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th/src/thlib.h,v $
 *          
 * NOTE   :
 *          This header file contains the interface fuctions and
 *          structures for the Test Harness Library, which impliments
 *          the API.
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: thlib.h,v $
 * Revision 1.6  2002/08/06 21:57:16  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.5  2002/07/19 19:29:03  rick
 * Replace eembc_id string with Benchmark ID
 *
 * Revision 1.4  2002/04/23 18:33:57  rick
 * Match eembc_dt with Lite, remove stdinc.h
 *
 * Revision 1.3  2002/03/22 18:25:25  rick
 * Add uuencode to Networking th regular
 *
 * Revision 1.2  2002/03/21 22:31:10  rick
 * Network Harness, and empty benchmark fixes
 *
 * Revision 1.1  2002/02/15 19:26:40  rick
 * Networking converstion to TH_Lite
 *
 * Revision 1.3  2001/11/01 00:26:46  administrator
 * Beta 1.1 of encdec
 *
 * Revision 1.2  2001/10/20 06:07:48  rick
 * Add DES, RC5, RC4, RC2 Encryption Benchmarks.
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

#ifndef   THLIB_H        /* File Sentinal */
#define   THLIB_H

#include "eembc_dt.h"
#include "thvinfo.h"
#include "therror.h"
#include "thcfg.h"

/*------------------------------------------------------------------------------
 *                  **** Test Component Interface ****
 *------------------------------------------------------------------------------
 * Function Types
 */

/* 
 * The 'tcft_'  stands for 'test component function type'
 */

/* Forward reference to TCDef */
struct TCDef;

typedef int  (*tcft_run_test)( LoopCount iterations, int argc, const char* argv[] );
typedef int  (*tcft_test_main)( struct TCDef** tcdef, int argc, const char* argv[] );
typedef int  (*tcft_main)( int argc, char* argv[] );
typedef void (*tcft_entry)(void);

/*------------------------------------------------------------------------------
 * Typedefs and Structs
 */
typedef struct
   {
   unsigned char  major;
   unsigned char  minor;
   unsigned char  step;
   unsigned char  revision;
   }
   version_number;

/*------------------------------------------------------------------------------
 * Test Component Defintion
 *
 * A const pointer to this sturcture is returned from test component's
 * entry point to the test harness.  It is used by the test harness to
 * control the test or benchmark.
 *----------------------------------------------------------------------------*/

/* TCDef.revsion == 1  { this is revision 1 of this structure } */

#define TCDEF_REVISION (2)

typedef struct TCDef{
   /*------------------------------------
    * This section is the same 
    * for all versions of this structure
    */
   char				eembc_bm_id[ 16 ];/* id flag */
   char				member[ 16 ];     /* the member id */
   char				processor[ 16 ];  /* the processor id */
   char				platform[ 16 ];   /* the platform id */
   char				desc[ 64 ];       /* benchmark description */
   e_u16			revision;         /* The revision of this structure. */

   /*------------------------------------*/

   struct TCDef*   next;  /* pointer to the next TCDef
                           * This is how multiple benchmarks in
                           * on image is supported. */

   /*------------------------------------*/

   version_number  th_vnum_required;  /* TH Version Required        */
   version_number  target_vnum_required;  /* Target Hardware Version Required */
   version_number  bm_vnum;  /* the version of this bench mark */
   LoopCount       rec_iterations;

   /*
    * Test Harness Interface Pointers  ( tcips... :)
    */
   tcft_run_test   tcip_run_test;
   tcft_test_main  tcip_test_main;
   tcft_main       tcip_main;
   tcft_entry      tcpi_entry;
}TCDef;

typedef struct THTestResults
   {
   LoopCount         iterations;
   e_u32             duration;
   e_u16			 CRC;
   size_t            v1;
   size_t            v2;
   size_t            v3;
   size_t            v4;
   const char *info;
   }
THTestResults;

#define TH_MAX_ARGV  (64)

/* If we don't have the FP type, then we need to define it */
#ifndef _TH_TYPE_FP_
#define _TH_TYPE_FP_
typedef int FP;
#endif

#define TH_UNDEF_VALUE ((size_t)(-1))

/*----------------------------------------------------------------------------*/

/* hardcoded file definitions */
#define FILE_NAME_SIZE (128)

typedef size_t BlockSize;

typedef struct FileDef
   {
   char          name[ FILE_NAME_SIZE ];  /* the file name */
   BlockSize     size;                    /* the file size */
   char*         buf;                     /* the buffer that holds the file */
   Dword         crc;                     /* the file's CRC */
   BlockSize     buf_size;                /* the size of the buffer */
   }
FileDef;

/* Keep FD_SIZE and even multiple of 4 */
#define FD_SIZE ((size_t)ROUNDUP4(sizeof(FileDef)*2))

/*------------------------------------------------------------------------------
 * Test Harness Initialization Functions (referenced in thlib.c)
 *----------------------------------------------------------------------------*/

int  test_main( struct TCDef** tcdef, int argc, const char* argv[] );

/*------------------------------------------------------------------------------
 * The Test Harness Regular API
 *----------------------------------------------------------------------------*/

int    th_printf( const char *fmt, ... );
int    th_sprintf( char *str, const char *fmt, ... );
int    th_putchar( char c );
int    th_puts( const char *s );
int    th_putb( const char *b, size_t buf_size );
int    th_sends( const char *s );

size_t th_read_con( char *buf, size_t buf_size );
size_t th_con_chars_avail( void );

#define th_malloc( size ) th_malloc_x( size, __FILE__, __LINE__ )
void *th_malloc_x( size_t size, const char *file, int line );
#define th_free( blk ) th_free_x( blk, __FILE__, __LINE__ )
void    th_free_x( void *blk, const char *file, int line );
void    th_heap_reset( void );

int    th_timer_available( void );
int    th_timer_is_intrusive( void );
int    th_is_timer_running( void );
size_t th_ticks_per_sec( void );
size_t th_tick_granularity( void );

void   th_signal_start( void );
size_t th_signal_finished( void );

void   th_exit( int exit_code, const char *fmt, ... );

int    th_report_results( const THTestResults *results, e_u16 Expected_CRC );

int    th_enter_critical_section( void );
void   th_leave_critical_section( int cs_flag );

int    th_harness_poll( void );

const FileDef *th_get_file_def( const char *fn );
const FileDef *th_get_file_num( int n );

int th_send_buf_as_file( const char* buf, BlockSize length, const char* fn );

/* CRC Utilities */
#if CRC_CHECK || NON_INTRUSIVE_CRC_CHECK
e_u16 Calc_crc8(e_u8 data, e_u16 crc );
e_u16 Calc_crc16( e_u16 data, e_u16 crc );
e_u16 Calc_crc32( e_u32 data, e_u16 crc );
#endif

/*----------------------------------------------------------------------------*/

struct THDef;  /* GNU Needs this here */

int thlib_main( struct THDef * thdef_ptr, TCDef **tcdef_ptr,
                int argc, const char *argv[] );

/*----------------------------------------------------------------------------*/


#endif                /*  File Sentinal */

