/*==============================================================================
 *$RCSfile: heap.h,v $
 *
 *   DESC : Heap Manager
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * AUTHOR : ARM Ltd., ECL, LLC
 *
 *    CVS : $Revision: 1.12 $
 *          $Date: 2002/03/18 21:15:08 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th_lite/src/heap.h,v $
 *          
 *   NOTE :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: heap.h,v $
 * Revision 1.12  2002/03/18 21:15:08  rick
 * Add al_report, cyclecount, crc fix in iirflt, and pktflow.
 *
 * Revision 1.7  2002/03/12 21:45:54  rick
 * TH Lite harness updates, and Build changes from directory changes
 *
 * Revision 1.8  2002/03/08 00:30:36  administrator
 * Fix Endian definition, vprintf, and rotate endian crc's
 *
 * Revision 1.6  2002/02/27 17:40:49  rick
 * Update Documentation and API comments for 0.3
 *
 * Revision 1.7  2002/02/25 17:15:35  rick
 * Add comment blocks, fix atime th_report call.
 *
 * Revision 1.4  2002/02/19 20:12:09  rick
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

#ifndef   HEAP_H
#define   HEAP_H



#ifndef   HEAPPORT_H
#include "heapport.h"
#endif



/*----------------------------------------------------------------------------*/

typedef struct
   {
   BlockSize size;         /* total size of the heap                 */
   BlockSize free;         /* free (useable) space in the heap       */
   BlockSize num_free;     /* number of free blocks                  */
   BlockSize num_alloced;  /* number of allocated blocks             */
   }
   HeapStats;

/*----------------------------------------------------------------------------*/

void *heap_initialize( char *start, BlockSize size );

void *heap_alloc( void *heap, BlockSize size );
void  heap_free( void *heap, void *buf );

/* Error values returned by heap_check() */
#define HEAP_OK              (0x00000000)
#define HERR_BAD_HEAP_STRUCT (0x00000001)
#define HERR_FIRST_BLOCK_BAD (0x00000002)
#define HERR_BLOCK_BAD       (0x00000004)
#define HERR_TOTAL_SIZE_BAD  (0x00000008)
#define HERR_FREE_SIZE_BAD   (0x00000010)
#define HERR_NUM_FREE_BAD    (0x00000020)
#define HERR_NUM_ALLOCED_BAD (0x00000040)
#define HERR_PSIZE_BAD       (0x00000080)
#define HERR_BLOCK_TOO_SMALL (0x00000100)
#define HERR_BLOCK_SIZE_MOD  (0x00000200)
#define HERR_FREE_ADJACENT   (0x00000400)
#define HERR_BAD_FREELPTR    (0x00000800)
#define HERR_FREELPTR_NN     (0x00001000) /* free list pointe not null */
#define HERR_BAD_FL_PREV     (0x00002000) /* bad free list previous ptr */
#define HERR_BAD_FL_NEXT     (0x00004000) /* bad free list previous ptr */
#define HERR_BAD_FL_TOO_MANY (0x00008000) /* too many items in the free list */
#define HERR_BAD_FL_NOT_NUFF (0x00010000) /* not enough items in the free list */
#define HERR_BAD_PREV_LINK   (0x00020000) /* bad previous link */
#define HERR_FL_BLOCK_BAD    (0x00040000) /* a block in the free list is bad */

   /*----------------------------------------------------------------------------*/


extern char		mem_base[];
extern size_t	mem_size; 


#ifdef __cplusplus
   }
#endif

#endif /* HEAP_H */

