/*==============================================================================
 *$RCSfile: thlib.h,v $
 *
 *   DESC : Test Harness Library Interface
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * AUTHOR : ARM Ltd., ECL, LLC
 *
 *    CVS : $Revision: 1.19 $
 *          $Date: 2002/07/19 19:29:24 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th_lite/src/thlib.h,v $
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
 * Revision 1.19  2002/07/19 19:29:24  rick
 * Replace eembc_id string with Benchmark ID
 *
 * Revision 1.18  2002/06/28 17:00:11  rick
 * Beta 2 Documentation
 *
 * Revision 1.17  2002/05/14 19:12:22  rick
 * Add th_sprintf for bmdebug calls
 *
 * Revision 1.16  2002/05/10 17:09:08  rick
 * Add al_main to API
 *
 * Revision 1.15  2002/04/23 18:34:06  rick
 * Match eembc_dt with Lite, remove stdinc.h
 *
 * Revision 1.14  2002/04/04 17:03:22  rick
 * thvinfo 4.0B1
 *
 * Revision 1.13  2002/04/03 23:18:46  rick
 * Clear warnings from gcc
 *
 * Revision 1.12  2002/03/18 21:15:09  rick
 * Add al_report, cyclecount, crc fix in iirflt, and pktflow.
 *
 * Revision 1.7  2002/03/12 21:45:54  rick
 * TH Lite harness updates, and Build changes from directory changes
 *
 * Revision 1.13  2002/03/11 22:11:49  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
 *
 * Revision 1.12  2002/03/08 00:30:37  administrator
 * Fix Endian definition, vprintf, and rotate endian crc's
 *
 * Revision 1.10  2002/02/27 17:40:49  rick
 * Update Documentation and API comments for 0.3
 *
 * Revision 1.9  2002/02/25 17:15:35  rick
 * Add comment blocks, fix atime th_report call.
 *
 * Revision 1.8  2002/02/21 19:52:11  administrator
 * Build TH_Lite makefile for cygwin
 *
 * Revision 1.7  2002/02/19 20:12:09  rick
 * Add long copyright message per Alan.
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
