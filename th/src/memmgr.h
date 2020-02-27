/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef   MEMMGR_H      /* File Sentinal */
#define   MEMMGR_H

#include "thcfg.h"
#include "thfli.h"
#include "heap.h"

/*----------------------------------------------------------------------------*/

#define MIN_MEMORY     (4096) /* always keep 4k for the heap */

extern void *th_heap;      /* the TH heap */


void     mem_mgr_init( void );
void     mem_heap_initialize( void );
FileDef *mem_alloc_file_space( const char *name, BlockSize size );
void     mem_report_files( void );
void     mem_report_info( void );

int      mem_delete_newest_file( void );
void     mem_delete_all_files( void );
FileDef *mem_get_file_def( const char *fn );
FileDef *mem_get_file_num( int n );

/*----------------------------------------------------------------------------*/

#endif                  /*  File Sentinal */

