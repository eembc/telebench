/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#if	!defined(THCFG_H)
#define THCFG_H

/* something in eembc_dt.h is messing this up, re-define here. */
#if	!defined(FALSE)
#undef  FALSE
#define FALSE   (0)
#endif

#if	!defined(TRUE)
#undef  TRUE
#define TRUE    (!FALSE)
#endif

/* Application Specific Overrides */
#include "harness.h"

#include "thvinfo.h"

/*----------------------------------------------------------------------------
 * Company, Processor and Target specific information
 *
 * This data gets placed in the global THDef structure named the_thdef
 * in the adpataion layer file THAL.C.
 *---------------------------------------------------------------------------*/

#define EEMBC_MEMBER_COMPANY   "EEMBC"
#define EEMBC_PROCESSOR        "PC-32bit-X86"
#define EEMBC_TARGET           "PC-Win32"

#define TARGET_MAJOR           0
#define TARGET_MINOR           0
#define TARGET_STEP            'R'
#define TARGET_REVISION        0

/*------------------------------------------------------------------------------
 * Target Timer Defintion
 *---------------------------------------------------------------------------*/

#define TARGET_TIMER_AVAIL     (TRUE)
#define TARGET_TIMER_INTRUSIVE (TRUE)

/*------------------------------------------------------------------------------
 * Set BMDEBUG to a (TRUE) to enable debugging printf's etc etc.
 * Set it to a (FALSE) for the released version of the BM
 *---------------------------------------------------------------------------*/

#if !defined( BMDEBUG )
/* Define this if you don't define M_THDEBUG in the make file. */
#define BMDEBUG (FALSE)
#endif

/*------------------------------------------------------------------------------
 * Demo switch to enable Windows specific code for host build.
 *---------------------------------------------------------------------------*/

#define	WINDOWS_EXAMPLE_CODE	(TRUE) 

/*------------------------------------------------------------------------------
 * Define BIG or LITTLE Endian here.  Note, do not define both to a (TRUE) or
 * both to a (0), one (and only one) of these must be set to a (TRUE)
 *---------------------------------------------------------------------------*/

/* If not defined from compiler define, Set it here. Default Little. */

#if !defined( EE_BIG_ENDIAN ) && !defined( EE_LITTLE_ENDIAN)
#define EE_BIG_ENDIAN    (FALSE)
#define EE_LITTLE_ENDIAN (TRUE)
#endif

#if !defined( EE_LITTLE_ENDIAN ) 
#if EE_BIG_ENDIAN
#define EE_LITTLE_ENDIAN (FALSE)
#else
#define EE_LITTLE_ENDIAN (TRUE)
#endif
#endif

#if !defined( EE_BIG_ENDIAN )
#if EE_LITTLE_ENDIAN
#define EE_BIG_ENDIAN (FALSE)
#else
#define EE_BIG_ENDIAN (TRUE)
#endif
#endif

#if EE_BIG_ENDIAN && EE_LITTLE_ENDIAN
#error "Cannot have both Big and Little Endian Defined"
#endif

#if !EE_BIG_ENDIAN && !EE_LITTLE_ENDIAN
#error "Must have one of EE_BIG_ENDIAN or EE_LITTLE_ENDIAN defined"
#endif

/*------------------------------------------------------------------------------
 * Set FLOAT_SUPPORT to (TRUE) if the target has floating point, or compiler
 * supports floating point emulation.
 *
 * Set FLOAT_SUPPORT to (FALSE) if not.
 *
 *----------------------------------------------------------------------------*/

#if !defined( FLOAT_SUPPORT )
#define FLOAT_SUPPORT (TRUE)
#endif

/*------------------------------------------------------------------------------
 *  HEAP Control Section
 *  NOTE: See heapport.h for enabling debug on internal heap manager.
 */

/*---------------------------------------------------------------------------
 * Set COMPILE_OUT_HEAP to TRUE to completely 'compile out' the test harness
 * memory allocation routines.
 * To use compiler's malloc support, set HAVE_MALLOC_H to true.
 * 
 * COMPILE_OUT_HEAP	TRUE,	HAVE_MALLOC_H TRUE, use compiler's heap manager.
 * COMPILE_OUT_HEAP	FALSE,	HAVE_MALLOC_H FALSE, use internal heap manager.
 * COMPILE_OUT_HEAP	TRUE,	HAVE_MALLOC_H FALSE, minimize code size (no malloc).
 * COMPILE_OUT_HEAP	FALSE,	HAVE_MALLOC_H TRUE, maximize code size (invalid).
 *---------------------------------------------------------------------------*/

#if !defined (COMPILE_OUT_HEAP)
#define COMPILE_OUT_HEAP (TRUE)
#endif

#if !defined (HAVE_MALLOC_H)
#define HAVE_MALLOC_H (TRUE)
#endif

#if !COMPILE_OUT_HEAP && HAVE_MALLOC_H
#error	"COMPILE_OUT_HEAP is false, and HAVE_MALLOC_H is true. Cannot select both internal and compiler malloc functions."
#endif

/*---------------------------------------------------------------------------
 * Turn this on to map malloc() and free() calls to th_malloc()
 * and th_free().  Note: you only need to do this if you use
 * functions in your C library that indirectly call malloc() and free().
 *
 * WARNING: If malloc is called before C program start (by kernel or crt0)
 * this option CANNOT be used. The harness dectects, and attempts to fail with
 * exit code 8 (THE_OUT_OF_MEMORY). Trap code for this case cannot be 
 * guaranteed to work before C program load and initialization.
 *---------------------------------------------------------------------------*/

#if !defined ( MAP_MALLOC_TO_TH )
#define MAP_MALLOC_TO_TH (FALSE)
#endif

#if COMPILE_OUT_HEAP && MAP_MALLOC_TO_TH
#error "COMPILE_OUT_HEAP && MAP_MALLOC_TO_TH invalid. Set one to FALSE"
#endif

/*---------------------------------------------------------------------------
 * Set this define to TRUE if your compiler has assert.h.
 *---------------------------------------------------------------------------*/

#if !defined (HAVE_ASSERT_H)
#define HAVE_ASSERT_H (TRUE)
#endif

/*------------------------------------------------------------------------------
 *  CRC Verification Section
 */

/*---------------------------------------------------------------------------
 * Set CRC_CHECK to TRUE to enable Intrusive CRC checking.
 * When CRC_CHECK is enabled, required # of iterations set during compile.
 * Do NOT use when measuring timing for certification.
 * 
 * Set NON_INTRUSIVE_CRC_CHECK to TRUE to enable Non-Intrusive CRC checking.
 * Non Intrusive CRC check is done outside of benchmark timing, and
 * is independent of the number of iterations.
 * You MAY use when measuring timing for certification.
 * 
 *---------------------------------------------------------------------------*/

#if	!defined(CRC_CHECK)
#define CRC_CHECK				(FALSE)
#endif

#if	!defined(NON_INTRUSIVE_CRC_CHECK)
#define	NON_INTRUSIVE_CRC_CHECK	(TRUE)
#endif

#if		CRC_CHECK && NON_INTRUSIVE_CRC_CHECK
#error	"CRC_CHECK and NON_INTRUSIVE_CRC_CHECK are enabled. Set one of them to FALSE"
#endif

/*------------------------------------------------------------------------------
 * Display verification 
 * VERIFY_INT - v1, v2, v3, v4 as size_t
 * VERIFY_FLOAT - v1,v2 -> double v1v2, and v3,v4 -> double v3v4
 *
 * NOTE: VERIFY_FLOAT can be used in telecom benchmarks to display 
 * automatically calculated diffmeasure results 
 *----------------------------------------------------------------------------*/

#if !defined(VERIFY_INT)
#define VERIFY_INT (TRUE)
#endif

#if !defined(VERIFY_FLOAT)
#define	VERIFY_FLOAT (FALSE)
#endif

/*------------------------------------------------------------------------------
 * Set USE_TH_PRINTF to (FALSE) to use the printf engine that comes with
 * your compiler's C Library.
 *
 * Set USE_TH_PRINTF to (TRUE) to use the printf engine that is built into
 * the Test Harness.
 *---------------------------------------------------------------------------*/

#if !defined( USE_TH_PRINTF )
#define USE_TH_PRINTF (FALSE)
#endif

/*------------------------------------------------------------------------------
 * This define is used to set the size of the buffer used to hold the
 * benchmark command line.  E.g. the 'argc' and 'argv' arguments will
 * be in this buffer.
 *
 * Note that two buffers of CMD_LINE_SIZE are allocated.  Normaly, you will not
 * have to change this.  But, if your systme is low on memory, you can make
 * CMD_LINE_SIZE smaller.  Note, its not a good idea to go below 128 bytes.
 *---------------------------------------------------------------------------*/

#define CMD_LINE_SIZE         (1024)
#define MAX_ARGC              (128)


/*---------------------------------------------------------------------------
 * EEMBC Member Company and Target specific defines go here
 *---------------------------------------------------------------------------*/

#if !defined( HEAP_ALIGN_V )
#define HEAP_ALIGN_V	8
#endif

#if !defined(HEAP_SIZE)
#define HEAP_SIZE	(1024*1024*4)	/* 4 Mb */
#endif

#endif /* THCFG_H */

