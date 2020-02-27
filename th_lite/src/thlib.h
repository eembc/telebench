/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef THLIB_H_FILE
#define	THLIB_H_FILE

#include "therror.h"
#include "eembc_dt.h"
#include "thcfg.h"
#include "thvinfo.h"
#include "thal.h" /* al_main */

#define		VN_BAD_PTR          0x0001
#define		VN_BAD_MAJOR        0x0002
#define		VN_BAD_MINOR        0x0004
#define		VN_BAD_STEP         0x0008
#define		VN_BAD_REVISION     0x0010
#define		VN_EMPTY_STR        0x0020
#define		VN_BAD_VER_IND      0x0040
#define		VN_MAJOR_TOO_BIG    0x0080
#define		VN_MINOR_TOO_BIG    0x0100
#define		VN_REVISION_TOO_BIG 0x0200
#define		VN_BAD_PERIOD       0x0400

/*----------------------------------------------------------------------------*/

typedef struct{
   unsigned char  major;
   unsigned char  minor;
   unsigned char  step;
   unsigned char  revision;
} version_number;

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

   version_number	th_vnum_required;  /* TH Version Required        */
   version_number	target_vnum_required;  /* Target Hardware Version Required */
   version_number	bm_vnum;  /* the version of this bench mark */
   e_u32  			rec_iterations;

   /*
    * Test Harness Results
    */
   e_u32			iterations;
   e_u32            duration;
   e_u16            CRC;
   size_t			v1;		/* Verification Data, can be double via union */
   size_t			v2;
   size_t			v3;
   size_t			v4;
} TCDef;


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

#endif /*THLIB_H_FILE*/ 

/*------------------------------------------------------------------------------
 * The Test Harness Lite API
 *----------------------------------------------------------------------------*/

/* th_malloc automatically calls heap_initialize if it hasn't been called yet */
#define th_malloc( size ) th_malloc_x( size, __FILE__, __LINE__ )
void *th_malloc_x( size_t size, const char *file, int line );
#define th_free( blk ) th_free_x( blk, __FILE__, __LINE__ )
void    th_free_x( void *blk, const char *file, int line );
void    th_heap_reset( void );
void mem_heap_initialize(void);

/* Timer Routines */
void   th_signal_start( void );
e_u32 th_signal_finished( void );
int th_timer_available( void );
int th_timer_is_intrusive( void );
size_t th_ticks_per_sec( void );
size_t th_tick_granularity( void );

/* System Routines */
void   th_exit( int exit_code, const char *fmt, ... );
int th_report_results(TCDef *tcdef, e_u16 Expected_CRC );

/* CRC Utilities */
#if	CRC_CHECK || NON_INTRUSIVE_CRC_CHECK
e_u16 Calc_crc8(e_u8 data, e_u16 crc );
e_u16 Calc_crc16( e_u16 data, e_u16 crc );
e_u16 Calc_crc32( e_u32 data, e_u16 crc );
#endif

/* Display control */
int th_printf( const char *fmt, ... );
int th_sprintf( char *str, const char *fmt, ... );

/* Benchmark source code compatibility stubs */
int th_harness_poll( void );
