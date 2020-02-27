/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#if	!defined(HEAPPORT_H)
#define   HEAPPORT_H

#include "thlib.h" 

/*------------------------------------------------------------------------------
 * Note, we use the !defined() test here  so that a value defined in
 * a make file or from an IDE will take precedence
 *----------------------------------------------------------------------------*/

#if !defined( TURN_ON_VERIFY_HEAP )
#define TURN_ON_VERIFY_HEAP 0
#endif

#if !defined( TURN_ON_DEBUG_HEAP )
#define TURN_ON_DEBUG_HEAP 0
#endif

/*------------------------------------------------------------------------------
 * Heap Porting Interface for 32bit x86
 *----------------------------------------------------------------------------*/

/* Both of these macros must resolve to the void pointer (void*) type */

#define PTR_ADD( ptr, offset ) ((void*)((char*)(ptr) + (offset)))
#define PTR_SUB( ptr, offset ) ((void*)((char*)(ptr) - (offset)))

#if	!defined(HEAP_ALIGN_V)
#error HEAP_ALIGN_V not defined! (must be an even power of 2)
#endif

/* 
 * This macro rounds up a number to an even power of HEAP_ALIGN_V
 */
#define HEAP_ALIGN(x) (((x) + ((HEAP_ALIGN_V)-1)) & ~((HEAP_ALIGN_V)-1))

#endif

