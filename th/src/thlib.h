/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

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

