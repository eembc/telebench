/*==============================================================================
 *$RCSfile: heap.c,v $
 *
 *   DESC : TH Regular Test Harness
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * AUTHOR : ARM Ltd., ECL, LLC
 *
 *    CVS : $Revision: 1.20 $
 *          $Date: 2002/09/12 19:04:47 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th_lite/src/heap.c,v $
 *          
 * NOTE   :
 *    define TURN_ON_VERIFY_HEAP as 1 to turn on all the heap checking stuff
 *    define TURN_ON_DEBUG_HEAP  as 1 to turn on debug printf output
 *
 *    Note, this is usually done from a make file, IDE or HEAPPORT.H
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: heap.c,v $
 * Revision 1.20  2002/09/12 19:04:47  rick
 * Fix dbpf and | definitions
 *
 * Revision 1.19  2002/08/08 20:50:42  rick
 * Compile out command line -i (iterations) when CRC_CHECK enabled.
 *
 * Revision 1.18  2002/07/17 17:47:22  rick
 * Fix Heap warnings
 *
 * Revision 1.17  2002/07/11 22:50:37  rick
 * Fix lite Heap init, tcdef results init, and stig's suggestions
 *
 * Revision 1.16  2002/05/23 20:22:41  rick
 * Clear ansi warnings
 *
 * Revision 1.15  2002/05/22 17:55:26  rick
 * Replace assert.h with thassert.h, add assert functions to th lite.
 *
 * Revision 1.14  2002/03/18 21:15:08  rick
 * Add al_report, cyclecount, crc fix in iirflt, and pktflow.
 *
 * Revision 1.9  2002/03/12 21:45:54  rick
 * TH Lite harness updates, and Build changes from directory changes
 *
 * Revision 1.13  2002/03/08 00:30:36  administrator
 * Fix Endian definition, vprintf, and rotate endian crc's
 *
 * Revision 1.9  2002/03/07 00:25:31  administrator
 * Add redirection for Tensilica Tools
 *
 * Revision 1.7  2002/03/04 23:57:53  administrator
 * Modifications from ARM Tools port.
 *
 * Revision 1.6  2002/02/27 00:22:13  rick
 * Add HAVE_MALLOC_H, al_printf to harness.
 *
 * Revision 1.9  2002/02/25 19:33:57  rick
 * Add prototypes to heap, clear static tcdef and const char cast in rgyhsi
 *
 * Revision 1.5  2002/02/25 17:15:36  rick
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

#include "eembc_dt.h"
#include "heap.h"

#if	HAVE_MALLOC_H
#include <stdlib.h>
#endif

#if TURN_ON_VERIFY_HEAP
#include <stdlib.h>
#include <ctype.h>
#endif

#ifndef HEAP_ALIGN_V
#error HEAP_ALIGN_V not defined! (must be an even power of 2)
#endif

#include "thassert.h"

#if		HAVE_MALLOC_H
/* heap is compiled out */
#elif		COMPILE_OUT_HEAP
/* heap is compiled out */
#else
char    mem_base[HEAP_SIZE];
size_t	mem_size = HEAP_SIZE;
void	*th_heap	= NULL; 
#endif

/*----------------------------------------------------------------------------*/

typedef struct Blok
   {
   BlockSize tsize;       /* size of this block      */
   BlockSize psize;       /* size of previous block  */
   BlockSize flags;       /* flags for this block    */
#if       TURN_ON_VERIFY_HEAP
   char      magic[ 8 ];
#endif
   }
Blok;

typedef struct FreeBlok
   {
   BlockSize tsize;       /* size of this block      */
   BlockSize psize;       /* size of previous block  */
   BlockSize flags;       /* flags for this block    */
#if	TURN_ON_VERIFY_HEAP
   char      magic[ 8 ];
#endif
   struct FreeBlok *prev;
   struct FreeBlok *next;
   }
FreeBlok;

typedef struct Heap
   {
   BlockSize size;         /* total size of the heap                 */
   BlockSize free;         /* free (useable) space in the heap       */
   BlockSize num_free;     /* number of free blocks                  */
   BlockSize num_alloced;  /* number of allocated blocks             */
   Blok *first;            /* pointer to the first block in the heap */
   FreeBlok *freel;        /* the free list                          */
   Blok *llastb;           /* the logical last block in the heap     */

#if      TURN_ON_VERIFY_HEAP
   char     magic[ 8 ];
#endif
   }
Heap;


#if TURN_ON_DEBUG_HEAP
#define LO_MALLOC 1
#define LO_FREE   2
int last_op = 0;
#define REC_MALLOC (last_op = LO_MALLOC)
#define REC_FREE   (last_op = LO_FREE)
char *ops[] = { "INIT", "MALLOC", "FREE" };
#else
#define REC_MALLOC ((void)0)
#define REC_FREE   ((void)0)
#endif

/* 
 * Calculate the size of the Blok strucure, rounding up to the
 * nearest multiple of the heap alignment boundary
 */
#define BSIZE ((BlockSize)(HEAP_ALIGN(sizeof( Blok ))))

/* 
 * Calculate the size of the Heap strucure, rounding up to the
 * nearest multiple of the heap alignment boundary 
 */
#define HSIZE ((BlockSize)(HEAP_ALIGN(sizeof( Heap ))))

#if TURN_ON_DEBUG_HEAP
#define DECLARE_XHEAP Heap* xheap = (Heap*)theap
#define HEAP xheap
#else
#define DECLARE_XHEAP  /*empty define*/
#define HEAP ((Heap*)theap)
#endif

/* Return a pointer to the next block */
#define NEXT_BLOK( blk ) ((Blok*)( PTR_ADD( blk, ((Blok*)blk)->tsize )))

/* Return a pointer to the previous block */
#define PREV_BLOK( blk ) ((Blok*)( PTR_SUB( blk, (((Blok*)blk)->psize ))))

#define NEXT_PTR( blk ) ((FreeBlok*)blk)->next
#define PREV_PTR( blk ) ((FreeBlok*)blk)->prev

#define ALLOCED_BIT (1)
#define LAST_BIT    (2)
#define FIRST_BIT   (4)

#define IS_FREE( blk )      (!(blk->flags & ALLOCED_BIT))
#define IS_ALLOCTED( blk )    (blk->flags & ALLOCED_BIT)
#define IS_FIRST( blk )       (blk->flags & FIRST_BIT)
#define IS_LAST( blk )        (blk->flags & LAST_BIT)

#define MAGIC_SIZE 8
#define HEAP_MAGIC  "!!HEAP!!"
#define BLOCK_MAGIC "!!BLOK!!"
#define DEAD_BEAF   "\xDE\xAD\xBE\xAF\xDE\xAD\xBE\xAF"

#define HEAP_PTR_INVALID  0
#define BLOCK_PTR_INVALID 0

/*----------------------------------------------------------------------------*/
/* Lint Stuff */

#if TURN_ON_VERIFY_HEAP
static int cm( const char *magic, const char *value );
#endif

/*lint -e740*/

/*----------------------------------------------------------------------------*/

#if TURN_ON_VERIFY_HEAP
#define VERIFY_HEAP(h)  { assert( theap != NULL );                         \
                          assert( !cm(((Heap*)h)->magic,  HEAP_MAGIC  )); }

#define VERIFY_BLOK(b) { assert( b != NULL );                          \
                         assert( !cm(((Blok*)b)->magic, BLOCK_MAGIC )); }

#define INIT_MAGIC( b, m ) { int i; for(i=0;i<MAGIC_SIZE;i++) \
                             b->magic[i]=m[i]; }
#define ZAP_MAGIC( b     ) { int i; for(i=0;i<MAGIC_SIZE;i++) \
                             b->magic[i]=DEAD_BEAF[i]; }
#else
#define VERIFY_HEAP(h)   {((void)0);}
#define VERIFY_BLOK(b)   {((void)0);}
#define INIT_MAGIC(b,m)  {((void)0);}
#define ZAP_MAGIC(b)     {((void)0);}
#endif


#if TURN_ON_DEBUG_HEAP
#define dpf0( f ) th_printf( f )
#define dpf1( f, a1) th_printf( f, a1 )
#define dpf2( f, a1, a2 ) th_printf( f, a1, a2 )
#define dpf3( f, a1, a2, a3 ) th_printf( f, a1, a2, a3 )
#define dpf4( f, a1, a2, a3, a4 ) th_printf( f, a1, a2, a3, a4 )
#else
#define dpf0( f ) {((void)0);}
#define dpf1( f, a1) {((void)0);}
#define dpf2( f, a1, a2 ) {((void)0);}
#define dpf3( f, a1, a2, a3 ) {((void)0);}
#define dpf4( f, a1, a2, a3, a4 ) {((void)0);}
#endif

/*
 * Local Prototype
 */

void *i_malloc( size_t size, const char *file, int line );
void mem_heap_initialize(void);


/*------------------------------------------------------------------------------
 * FUNC   : heap_initialize
 *
 * DESC   : Initializes the heap from scratch
 * ---------------------------------------------------------------------------*/

void *heap_initialize( char *start, BlockSize size )

   {
#if	HAVE_MALLOC_H
	start=start;
	size=size;
	return NULL;
#elif COMPILE_OUT_HEAP
	start=start;
	size=size;
   return NULL;
#else

   Heap *xheap;

   dpf1( "BSIZE = %lu\n", BSIZE );
   dpf1( "HSIZE = %lu\n", HSIZE );

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * Initialize the heap structure */

   xheap = ( Heap * ) start;
   xheap -> size = size;
   xheap -> first = ( Blok * ) PTR_ADD( start, HSIZE );
   xheap -> free = xheap -> size - HSIZE - BSIZE;
   xheap -> num_free = 1;
   xheap -> num_alloced = 0;
   xheap -> freel = ( FreeBlok * ) xheap -> first;
   xheap -> llastb = ( Blok * ) PTR_ADD( xheap->first, (size - HSIZE - ( BSIZE * 2 )));

   INIT_MAGIC( xheap, HEAP_MAGIC );/* init the magic number */

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * Initialize the first block in the heap */

   xheap -> first -> psize = 0;
   xheap -> first -> tsize = xheap -> free + BSIZE;

   xheap -> first -> flags = FIRST_BIT | LAST_BIT; /* mark as both first and last block */

   NEXT_PTR( xheap -> first ) = NULL; /* terminate the free list */
   PREV_PTR( xheap -> first ) = NULL; /* terminate the free list */

   INIT_MAGIC( xheap -> first, BLOCK_MAGIC );  /* init the first block's magic number */

   dpf0( "\n" );
   dpf1( "Heap Ptr         = %p\n", xheap );
   dpf1( "Heap First       = %p\n", xheap -> first );
   dpf1( "Heap Free List   = %p\n", xheap -> freel );
   dpf1( "Heap End         = %p\n", PTR_ADD( xheap, xheap -> size - 1 ));
   dpf2( "Heap Size        = %ld (%08lX)\n", xheap -> size, xheap -> size );
   dpf2( "Heap Free        = %ld (%08lX)\n", xheap -> free, xheap -> free );
   dpf1( "Heap Num Free    = %ld\n", xheap -> num_free );
   dpf1( "Heap Num Alloced = %ld\n", xheap -> num_alloced );

   return (void *) xheap;
   
#endif
   }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#if COMPILE_OUT_HEAP
/* heap is compiled out! */
#else

/*------------------------------------------------------------------------------
 * FUNC   : cm
 *
 * DESC   : check magic
 *
 * RETURNS: TRUE if the magic value checks
 *          FALSE if not
 * ---------------------------------------------------------------------------*/

#if TURN_ON_VERIFY_HEAP
static int cm( const char *magic, const char *value )

   {
   int i;

   for (i = 0; i < MAGIC_SIZE; i++)
      if (magic[ i ] != value[ i ])
         return 1;

   return 0;
   }
#endif

/*------------------------------------------------------------------------------
 * FUNC   : heap_alloc
 *
 * DESC   : Allocates a block of memory from the heap
 *
 *          This function impliments a first fit algoritem.
 *
 * RETURNS: A pointer to the allocated buffer.  If there is not a free
 *          block big enough, then NULL is returned
 * ---------------------------------------------------------------------------*/

void *heap_alloc( void *theap, BlockSize size )

   {
   FreeBlok *blk;  /* the current block */

   DECLARE_XHEAP;

   VERIFY_HEAP( HEAP );

   if (HEAP -> num_free == 0)
      return 0;

   REC_MALLOC; /* record that a malloc happend */

   for (blk = HEAP -> freel; blk != NULL; blk = NEXT_PTR( blk ))
      {
      VERIFY_BLOK( blk );

      /* Is the block free and large enough for the required size? */
      if (size <= blk -> tsize - BSIZE)
         {
         /*       split( theap, blk, size );  * Now in-line here  SEE FN#1 */
         Blok *nblk;       /* the next block in memory */
         BlockSize asize;  /* requested size rounded up to an even multple of 4 */
         BlockSize xsize;  /* the actual size of the allocated block */

         /* Keep block sizes an even multiple of BSIZE
          * note, BSIZE is an even multiple of 4! */
         {
         BlockSize x = size % BSIZE;
         asize = (x!=0) ? size+(BSIZE-x) : size;
         }

         assert( (asize % 4)     == 0 ); /* better be an even multiple of 4 */
         assert( (asize % BSIZE) == 0 ); /* ... and BSIZE */
                     
         xsize = asize + BSIZE;

         /* Do we have an exact fit?? OR
          * Or will the resultant fragmented block be
          * less than (BSIZE*2) in size */
         if (size == ( blk -> tsize - BSIZE ) || ( blk -> tsize - xsize ) <= ( BSIZE * 2 ))
            {
            /* It doesn't make sense to split the block */
            HEAP -> num_free--;
            HEAP -> num_alloced++;
            HEAP -> free -= ( blk -> tsize - BSIZE );

            blk -> flags |= ALLOCED_BIT; /* Its allocated! */

            /* if this is the first block in the free list then we
             * gotta move the free list pointer in the heap structure.
             * Note, since we keep the linked list null terminated,
             * this works even when we remove the last block form the list. */
            if (HEAP -> freel == ( FreeBlok * ) blk)
               HEAP -> freel = NEXT_PTR( blk );

            /* Unlink this pointer from the free list */
            if (PREV_PTR( blk ) != NULL)
               NEXT_PTR( PREV_PTR( blk )) = NEXT_PTR( blk );
            if (NEXT_PTR( blk ) != NULL)
               PREV_PTR( NEXT_PTR( blk )) = PREV_PTR( blk );

            return (void *) PTR_ADD( blk, BSIZE );
            }

         blk -> tsize -= xsize;   /* Shrink the current block */

         nblk = NEXT_BLOK( blk ); /* Get a pointer to the new split block */

         nblk -> tsize = xsize;
         nblk -> psize = blk -> tsize;
         nblk -> flags = ALLOCED_BIT;      /* also set all other flag bits to zero */

         if (blk -> flags & LAST_BIT)      /* are we splitting the last one? */
            {
            nblk -> flags |= LAST_BIT;    /* new one is last */
            blk -> flags &= ~LAST_BIT;    /* previous one isn't */
            }

         /* Link the next block to the recently split block */
         if (!IS_LAST( nblk ))
            NEXT_BLOK( nblk ) -> psize = nblk -> tsize;

         INIT_MAGIC( nblk, BLOCK_MAGIC ); /* init the magic number */

         HEAP -> num_alloced++;
         HEAP -> free -= nblk -> tsize;

#if TURN_ON_VERIFY_HEAP
         if (!IS_FIRST( nblk ) && PREV_BLOK( nblk ) -> tsize != nblk -> psize)
            th_printf( "\nHEAP.C! Big Problem %d\n", __LINE__ );
#endif

         /* Note, since we are splitting the block, we don't have to
          * do any maintenance on the free list :) */

         /*----------------------------*/

         return (void *) PTR_ADD( nblk, BSIZE );
         }
      }

   /* Gee, we looked through the entire free list and couldn't find a block
    * Large enough for the requested size!  So, just return NULL
   */
   return NULL; /*lint !e527 : Unreachable code
                 * We'll never get here, but this keeps the compiler
                 * from griping. about no return value */
   }

/*------------------------------------------------------------------------------
 * FUNC   : heap_free
 *
 * DESC   : frees a block
 *
 *          Markes a block as free and coaleses it with adjacent blocks
 *          as necessary
 *
 * PARAMS : heap - a pointer to the heap structure that defines the heap
 *          buf  - the buffer to free
 * ---------------------------------------------------------------------------*/

void heap_free( void *theap, void *buff )

   {
   Blok *blk;      /* The block to be freed  */
   Blok *nblk;     /* The next block         */
   Blok *pblk;     /* the previous block     */
   int   combined; /* set if the block is combined */

   DECLARE_XHEAP;

   REC_FREE;       /* record that a free happend */

   VERIFY_HEAP( HEAP );

   if (buff == 0)
      return;

   combined = 0;   /* assume its not combined */

   blk = ( Blok * ) PTR_SUB( buff, BSIZE );

   VERIFY_BLOK( blk );

   blk -> flags &= ~ALLOCED_BIT;       /* Flag this block as free */

   HEAP -> num_free++;
   HEAP -> num_alloced--;

   HEAP -> free += ( blk -> tsize - BSIZE );

   /* If this is not the first block in the heap, then lets see if we
    * can combine it with the previous block */
   if (!IS_FIRST( blk ))
      {
      pblk = PREV_BLOK( blk );

      if (IS_FREE( pblk ))
         {
         ZAP_MAGIC( blk ); /* un-mark the block as being valid */

         /* Combine the block with the previous block */
         HEAP -> num_free--;

         pblk -> tsize += blk -> tsize;
         pblk -> flags |= blk -> flags & LAST_BIT;
         HEAP -> free += BSIZE;
         blk = pblk;

         /* Note, we are combining the block with one alread on the free
          * list so we don't have to do any free list maintenance here */
         combined = 1;
         }
      }

   /* If this is not the last block in the heap, then lets see if we
    * can combine it with the next block */
   if (!IS_LAST( blk ))
      {
      nblk = NEXT_BLOK( blk );

      if (IS_FREE( nblk ))
         {
         HEAP -> num_free--;

         blk -> tsize += nblk -> tsize;
         blk -> flags |= nblk -> flags & LAST_BIT;
         HEAP -> free += BSIZE;

         ZAP_MAGIC( nblk ); /* un-mark the block as being valid */

         /* gotta remove the next block from the free list because
          * it is getting combined with the one that was just freed */

         /* if this is the first block in the free list then we
          * gotta move the free list pointer in the heap structure.
          * Note, since we keep the linked list null terminated,
          * this works even when we remove the last block form the list. */
         if (HEAP -> freel == ( FreeBlok * ) nblk)
            HEAP -> freel = NEXT_PTR( nblk );

         /* Unlink this pointer from the free list */
         if (PREV_PTR( nblk ) != NULL)
            NEXT_PTR( PREV_PTR( nblk )) = NEXT_PTR( nblk );
         if (NEXT_PTR( nblk ) != NULL)
            PREV_PTR( NEXT_PTR( nblk )) = PREV_PTR( nblk );
         }
      }

   if (!combined)
      {
      /* The newly free'd block was not combined with the previous
       * block so we need to add it to the front of the free list */

      if (HEAP -> freel != NULL)
         {
         /* we have a list, so just add it to the front of the list */
         PREV_PTR( HEAP -> freel ) = ( FreeBlok * ) blk;
         NEXT_PTR( blk ) = HEAP -> freel;
         PREV_PTR( blk ) = NULL;
         }
      else
         {
         /* the list is empty, so make this block the only one in the list */
         NEXT_PTR( blk ) = NULL;
         PREV_PTR( blk ) = NULL;
         }

      HEAP -> freel = ( FreeBlok * ) blk; /* in any case, the free list
                                           * starts with this block */
      }
   /* else,
        * the recently free'd block was combined with the previous
        * block which (since it is free) is already a member of the free
        * list. So, we don't need to do any free list maintenance here */

   if (!IS_LAST( blk ))
      {
      NEXT_BLOK( blk ) -> psize = blk -> tsize;
      }
   }



#endif /* COMPILE_OUT_HEAP */

void mem_heap_initialize(void)
{
#if HAVE_MALLOC_H
/* do nothing */
#elif COMPILE_OUT_HEAP
/* do nothing */
#else
	th_heap = heap_initialize( mem_base, mem_size );
#endif
}


void *i_malloc( size_t size, const char *file, int line )

   {
#if HAVE_MALLOC_H
	file=file;
	line=line;
	return	malloc(size);
#elif COMPILE_OUT_HEAP
	size=size;
	th_printf( "** ERROR: Heap Routines are compiled out! %s:%d\n", file, line );
	th_exit( 1, "\n" );
	/* 
	 * NOTE : If this code executes, then the heap routines have been compiled
	 *        out by setting the COMPILE_OUT_HEAP define in THCFG.H.
	 *        This means you CANNOT run benchmarks that need the heap!
	 */
	return NULL;
#else
   void *block = heap_alloc( th_heap, size );

   if (block == NULL)
      {
         th_printf( "** ERROR:  Out Of memory! size=%ld %s:%d\n", size, file, line );
         th_exit( 1, "--      :  Detected in %s:%d\n", file, line );
      }

   return block;
#endif
   }

/*------------------------------------------------------------------------------
 * FUNC   : i_free
 *
 * DESC   : functional layer implimentation of i_free()
 * ---------------------------------------------------------------------------*/

void i_free( void *block, const char *file, int line ){
#if HAVE_MALLOC_H
	file=file;
	line=line;
	free(block);
#elif COMPILE_OUT_HEAP
/* do nothing */
	file=file;
	line=line;
	block=block;
#else
	file=file;
	line=line;
   heap_free( th_heap, block );
#endif
}


/*------------------------------------------------------------------------------
 * FUNC    : th_malloc_x
 *
 * DESC    : Test Harness malloc()
 *
 *           This works just like malloc() from the standard library.
 *
 * PARAMS  : size - is the size of the memory block neded
 *           file - the __FILE__ macro from where the call was made
 *           line - the __LINE__ macro from where the call was made
 *
 * NOTE    : This function is usually invoked by using th th_malloc()
 *           macro.
 *
 * RETURNS : A void pointer to the allocated block.  Use a cast to asssign
 *           it to the proper poitner type.
 *           The NULL value is returned if a block ofthe specified size cannot
 *           be allocated.
 * ---------------------------------------------------------------------------*/

void *th_malloc_x( size_t size, const char *file, int line )

   {
   return i_malloc( size, file, line );
   }

/*------------------------------------------------------------------------------
 * FUNC    : th_free_x
 *
 * DESC    : Test Harness free()
 *
 *           This works just like free() from the standard library.
 *
 * PARAMS  : ptr - points to the block pointer returned by th_malloc().
 *           file - the __FILE__ macro from where the call was made
 *           line - the __LINE__ macro from where the call was made
 *
 * NOTE    : This function is usually invoked by using th th_free()
 *           macro.
 *
 * NOTE    : It is valid to pass the null pointer to this function.
 * ---------------------------------------------------------------------------*/

void th_free_x( void *block, const char *file, int line ){
   i_free ( block, file, line );
}

