/*==============================================================================
 *$RCSfile: memmgr.c,v $
 *
 *   DESC : The memory managment sub-system
 *
 *          This module manages the free system memory
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.7 $
 *          $Date: 2002/08/06 22:52:03 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th/src/memmgr.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: memmgr.c,v $
 * Revision 1.7  2002/08/06 22:52:03  rick
 * Integrate HAVE_MALLOC_H
 *
 * Revision 1.6  2002/05/23 20:22:39  rick
 * Clear ansi warnings
 *
 * Revision 1.5  2002/05/22 17:55:20  rick
 * Replace assert.h with thassert.h, add assert functions to th lite.
 *
 * Revision 1.4  2002/04/02 17:06:27  administrator
 * Remove whitespace before # directives
 *
 * Revision 1.3  2002/03/22 22:57:54  rick
 * Change project files for lowercase, and techtag empty, th, and th_lite
 *
 * Revision 1.2  2002/03/21 22:31:09  rick
 * Network Harness, and empty benchmark fixes
 *
 * Revision 1.1  2002/02/15 19:26:40  rick
 * Networking converstion to TH_Lite
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

#include <string.h>

#include "thfl.h"
#include "thfli.h"
#include "printfe.h"
#include "thal.h"
#include "therror.h"
#include "heap.h"
#include "ssubs.h"
#include "memmgr.h"
#include "thcfg.h"
#include "thassert.h"

/*------------------------------------------------------------------------------
 * Global Data
 */

void *th_heap = NULL;

/*------------------------------------------------------------------------------
 * Local Data
 */

static char *heap_base = NULL;
static BlockSize heap_size = 0;

static int       file_count = 0;
static FileDef *first_file = NULL;

/*------------------------------------------------------------------------------
 * FUNC   : mem_mgr_init()
 *
 * DESC   : Initialize the memory management sub-system
 * ---------------------------------------------------------------------------*/

void mem_mgr_init()

   {
   if (mem_base == NULL)
      t_exit( FATAL_EXIT, "\nFATAL ERROR: mem_base == NULL %s:%d", SOURCE_FILE, __LINE__ -1 );

   if (mem_size == 0)
      t_exit( FATAL_EXIT, "\nFATAL ERROR: mem_size == 0 %s:%d", SOURCE_FILE, __LINE__ -1 );

/*   assert( (FD_SIZE % 4) == 0 );*/

   heap_base = mem_base;
   heap_size = mem_size;
   }

/*------------------------------------------------------------------------------
 * FUNC   : mem_mgr_init()
 *
 * DESC   : Initialize the heap itself
 *
 * PURPOSE: We could have easily called heap_initialize from the place
 *          where mem_heap_initialize() is called but this would have meaned
 *          making the heap_base and heap_size variables global.
 * ---------------------------------------------------------------------------*/

void mem_heap_initialize()

   {
#if HAVE_MALLOC_H
/* do nothing */
#elif COMPILE_OUT_HEAP
/* do nothing */
#else
   th_heap = heap_initialize( heap_base, heap_size );
#endif
   }

/*------------------------------------------------------------------------------
 * FUNC   : mem_alloc_file_space
 *
 * DESC   : Allocate space for a file
 *
 *          This function allocoates memory from the top of the free ram
 *          area.  This is used by the
 *
 * RETURNS: A pointer to the file defition, or NULL if there was not enough
 *          space to allocate for the file.
 * ---------------------------------------------------------------------------*/

FileDef *mem_alloc_file_space( const char *name, BlockSize size )

   {
   BlockSize fsize;
   BlockSize bsize;
   FileDef *fd;

   /* Round file size up to nearest multiple of 4 */
   fsize = ROUNDUP4( size );

   bsize = fsize + FD_SIZE;

   if (( heap_size >= ( MIN_MEMORY + bsize )))
      {
      heap_size -= bsize;

      fd = ( FileDef * ) ( heap_base + heap_size );

      cpystr( fd -> name, name, FILE_NAME_SIZE );

      fd -> size = size;

      fd -> buf_size = bsize;

      fd -> buf = (( char * ) fd ) + FD_SIZE;

      fd -> crc = 0xFFFFFFFF;

      file_count++;

      first_file = fd;

      return first_file;
      }

   /* Not enough file space */

   return NULL;
   }

/*------------------------------------------------------------------------------
 * FUNC   : mem_delete_all_files
 *
 * DESC   : Deletes all the files in the file area
 * ---------------------------------------------------------------------------*/

void mem_report_files()

   {
   int i;
   FileDef *fd;

   if (file_count == 0)
      {
      t_printf( "\n-- No Files\n\n" );
      return;
      }

   t_printf( "\n" );
   t_printf( "          #        CRC     Size  Name\n" );
   t_printf( "         --  ----------  -------  ---------------------------------------\n" );

   for (fd = first_file, i = 0; i < file_count; i++)
      {
      if (sizeof( BlockSize ) == sizeof( long ))
         t_printf( "-- File: %2d 0x%08X  %7lu  %s\n", i + 1, fd -> crc, fd -> size, fd -> name );
      else
         t_printf( "-- File: %2d 0x%08X  %7u  %s\n", i + 1, fd -> crc, fd -> size, fd -> name );

      fd = ( FileDef * ) ((( char * ) fd ) + fd -> buf_size );
      }

   t_printf( "\n\n" );
   }

/*------------------------------------------------------------------------------
 * FUNC   : p_bs()
 * ---------------------------------------------------------------------------*/

static void pbs( char type, BlockSize bs )

   {
	/* initialize to largest else case */
   const char *fmt = "%08X";

   if (sizeof( BlockSize ) == 2)
      {
      if (type == 'd')
         fmt = "%5u";
      else
         fmt = "%04X";
      }
   else
      if (sizeof( BlockSize ) == 4)
         {
         if (type == 'd')
            fmt = "%8u";
         else
            fmt = "%08X";
         }

   t_printf( fmt, bs );
   }

/*------------------------------------------------------------------------------
 * FUNC   : mem_report_info
 *
 * DESC   : Report memory information
 * ---------------------------------------------------------------------------*/

void mem_report_info()

   {
   BlockSize file_room = mem_size - heap_size;
   #if !COMPILE_OUT_HEAP
   HeapStats stats;
   BlockSize bfb;
   #endif
   t_printf( "\nRAM Memory Base      = %p", mem_base );

   t_printf( "\nRAM Size             = " );
   pbs( 'd', mem_size );
   t_printf( "  0x" );
   pbs( 'x', mem_size );

   if (file_count)
      {
      t_printf( "\n" );
      t_printf( "\nFile Area            = %p", first_file );
      t_printf( "\nFile Area Size       = " );
      pbs( 'd', file_room );
      t_printf( "  0x" );
      pbs( 'x', file_room );
      }

#if COMPILE_OUT_HEAP
   t_printf( "\n" );
   t_printf( "\nHeap Routines Compiled out! ");
#else

   t_printf( "\n" );
   t_printf( "\nHeap Base            = %p", heap_base );

   t_printf( "\nHeap Size            = " );
   pbs( 'd', heap_size );
   t_printf( "  0x" );
   pbs( 'x', heap_size );

   if (th_heap != NULL)
      {
      heap_stats( th_heap, &stats );
      bfb = heap_biggest_free_block( th_heap );

      t_printf( "\nHeap Free Mem        = " );
      pbs( 'd', stats . free );
      t_printf( "  0x" );
      pbs( 'x', stats . free );

      t_printf( "\nFree Block Count     = " );
      pbs( 'd', stats . num_free );

      t_printf( "\nAlloced Block Count  = " );
      pbs( 'd', stats . num_alloced );

      t_printf( "\nLargest Free Block   = " );
      pbs( 'd', bfb );
      t_printf( "  0x" );
      pbs( 'x', bfb );
      }
#endif

   t_printf( "\n" );
   }

/*------------------------------------------------------------------------------
 * FUNC   : mem_delete_newest_file
 *
 * DESC   : Delete the first file in the RAM area
 *
 *          This function removes the file at the lowest address in the
 *          RAM memoery space.
 *
 * DESC   : the number of files left in the file area
 * ---------------------------------------------------------------------------*/

int mem_delete_newest_file()

   {
   assert( file_count >= 0 );

   if (file_count)
      {
      file_count--;

      heap_size += first_file -> buf_size;

      if (file_count > 0)
         first_file = ( FileDef * ) ( heap_base + heap_size );
      else
         first_file = NULL;
      }

   return file_count;
   }

/*------------------------------------------------------------------------------
 * FUNC   : mem_delete_all_files
 *
 * DESC   : Deletes all the files in the file area
 * ---------------------------------------------------------------------------*/

void mem_delete_all_files()

   {
   while (mem_delete_newest_file())
      {
      ;
      }
   }

/*------------------------------------------------------------------------------
 * FUNC   : mem_get_file_def
 *
 * DESC   : Gets the file defintion (FileDef*) for a specific file.
 *
 *          Give a file name, this function returns a pointer to the file
 *          defintion structure for the file. If the file does not exist
 *          then NULL is returned. The FileDef structure is documented in the
 *          THLIB.H file.
 *
 * PARAMS : fn - The index of the file to find.
 *               The most recent file downloaded has an index number of zero.
 *               The previouly downloaded file has index 1. etc. etc.
 *
 * RETURNS: A pointer to the FileDef struct or NULL if the file has not yet
 *          been downloaded
 * ---------------------------------------------------------------------------*/

FileDef *mem_get_file_def( const char *fn )

   {
   int i;
   FileDef *fd = NULL;

   assert( file_count >= 0 );

   for (i = 0, fd = first_file; i < file_count; i++)
      {
      if (strcmp( fd -> name, fn ) == 0)
         return fd;

      fd = (FileDef*)(((char*)fd ) + fd->buf_size ); /* next file */
      }

   return NULL;
   }

/*------------------------------------------------------------------------------
 * FUNC   : mem_get_file_num
 *
 * DESC   : Gets the file defintion (FileDef*) for a file by index number.
 *
 *          Give a file number index, this function returns a pointer to the
 *          file defintion structure for the file. If the file does not
 *          exist then NULL is returned. The FileDef structure is documented
 *          in the THLIB.H file.
 *
 * PARAMS : n - The index of the file to find. The most recent file
 *              downloaded has an index number of zero. The previous file
 *              has index 1. etc. etc.
 *
 * RETURNS: A pointer to the FileDef struct or NULL if the file has not yet
 *          been downloaded.
 * ---------------------------------------------------------------------------*/

FileDef *mem_get_file_num( int n )

   {
   int i;
   FileDef *fd;

   assert( file_count >= 0 );

   if (file_count == 0 || n >= file_count || n < 0)
      return NULL;

   for (i = 0, fd = first_file; i < file_count && i != n; i++)
      fd = (FileDef*)(((char*)fd) + fd->buf_size ); /* next file */

   return fd;
   }

