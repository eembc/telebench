/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef   THAL_H       /* File Sentinal */
#define   THAL_H

#include "thcfg.h"
#include "heapport.h"

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

   /*------------------------------------------------------------------------------
    * Global Defines
   */

#define FATAL_EXIT (-32766)

   /*------------------------------------------------------------------------------
    * Global data
   */

#define PF_BUF_SIZE (1024)
   extern char pf_buf[ PF_BUF_SIZE ];

   /*----------------------------------------------------------------------------*/

   int    al_lc_open( void );
   void   al_lc_close( void );
   int    al_write_con( const char *buf, size_t buf_size );
   size_t al_read_con( char *buf, size_t buf_size );
   size_t al_con_chars_avail( void );

   size_t al_ticks( void );
   size_t al_ticks_per_sec( void );
   size_t al_tick_granularity( void );

   void   al_signal_start( void );
   size_t al_signal_finished( void );
   void   al_exit( int exit_code, const char *fmt, va_list args );
   void	al_report_results( void );

   extern char *mem_base;
   extern BlockSize mem_size;

   /*----------------------------------------------------------------------------*/

#ifdef __cplusplus    /* Take this out if you don't need it */
   }
#endif

#endif                /*  File Sentinal */
