/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#if	!defined(EEMBC_DT_H)
#define EEMBC_DT_H

/*----------------------------------------------------------------------------
 * Include the compilers STDDEF.H here so we get the correct defition
 * of size_t
 *----------------------------------------------------------------------------*/

#include <stddef.h>
#include "thcfg.h"

/*----------------------------------------------------------------------------
 * Some compilers do not define EOF in stdio.h, make sure it's defined.
 *----------------------------------------------------------------------------*/

#if	!defined(EOF)
#define EOF (-1)
#endif

/*------------------------------------------------------------------------------
 * The following data types are called the "Standard EEMBC Data Types".  Each
 * is defined appropriatly for the target exeuction environment and the
 * tool chain used to compile/link and possibly locate an instance of the
 * Test Harness and one or more benchmarks.
 *
 * Each of these data types MUST BE defined in a manner which gives
 * them a size of <<AT LEAST>> the number of bits indicated by its name.
 *
 * It is every important to note that a type MUST NOT be defined larger than
 * specified if the build and execution environments support the appropriatly
 * sized data type.
 *
 * For example, if a 'short' is 16bits on a target and an 'int' is 32bits,
 * then the 'e_u16' data type must be defined as 'unsigned short' and
 * not 'unsigned int'.
 *
 * The 8bit, 16bit, 24bit and 32bit integral data types are required.
 * The 48bit and 64bit integral types are optional.
 * The 32bit and 64bit floating point types are optional
 * ---------------------------------------------------------------------------*/

/* integral data types */
#define HAVE_64    (0)    /* at least 64 bits in size  */
#define HAVE_48    (0)    /* at least 48 bits in size  */

/* Floating Point data types */
#define HAVE_F32   (1)    /* at least 32 bits in size  */
#define HAVE_F64   (1)    /* at least 64 bits in size  */

/*----------------------------------------------------------------------------
 * EEMBC Standard Data Types
 * Note that these all  are prefixed with "e_"
 *----------------------------------------------------------------------------*/

typedef unsigned char           e_u8;
typedef signed   char           e_s8;

typedef unsigned short          e_u16;
typedef signed   short          e_s16;

typedef unsigned long           e_u24;
typedef signed   long           e_s24;

typedef unsigned long           e_u32;
typedef signed   long           e_s32;

#if HAVE_48
typedef unsigned long           e_u48;
typedef signed long             e_s48;
#endif

#if HAVE_64
typedef unsigned long           e_u64;
typedef signed long             e_s64;
#endif

#if HAVE_F32
typedef float                   e_f32;
#endif

#if HAVE_F64
typedef double                  e_f64;
#endif

/*----------------------------------------------------------------------------
 * Native Size Types
 *
 * Native types are used when you want to let the compiler
 *  figure out the native machine size (for optimizations)
 *  but should NOT be used when the sizeof() variable matters
 *  in the calculation
 *
 *----------------------------------------------------------------------------*/

typedef char                    n_char;
typedef unsigned char           n_uchar;
typedef short                   n_short;
typedef unsigned short          n_ushort;
typedef int                     n_int;
typedef unsigned int            n_uint;
typedef long                    n_long;
typedef unsigned long           n_ulong;
typedef float                   n_float;
typedef double                  n_double;
typedef void					n_void; 

/*------------------------------------------------------------------------------
 * This data type should be set to a type which will hold the larget
 * benchmark loop count used on your target system.  Generally, this will
 * be a 16bit or a 32bit unsigned type.
 *
 * By default, this type is typedefed as 'size_t'.
 *----------------------------------------------------------------------------*/

typedef size_t LoopCount;

/*------------------------------------------------------------------------------
 * Fixed Size Types
 *
 * These types are always set to be a specific size
 *
 * If the target does not support a type of the required size, then set the
 * type to the smallest size native data type that will hold the defined type.
 *
 * Note: These typedefs will all maintain there proper (indicatd) sizefor
 *       boht the 16 and 32 bit models for the 16/32 bit compilers listed
 *       in the module header.                                           
 *----------------------------------------------------------------------------*/

/*
 * Portable unsigned types
 */
typedef          e_u8   Byte;     /* Always  8 bits (unsigned) */
typedef          e_u16  Word;     /* Always 16 bits (unsigned) */
typedef          e_u32  Dword;    /* Always 32 bits (unsigned) */

/*
 * Portable signed types
 */
typedef          e_s8   Char;     /* Always  8 bits (signed)   */
typedef          e_s16  Short;    /* Always 16 bits (signed)   */
typedef          e_s16  Bool;     /* Always 16 Bits (signed)   */
typedef          e_s32  Long;     /* Always 32 bits (signed)   */

/*------------------------------------------------------------------------------
 * The status type is used by functions which return 'Success' or 'Failure' 
 * where 'Success' is always zero and 'Failure' is defined as default value
 * of '1' but is also considered to be any non zero value.  This is defied
 * as a short because we usually don't need 32bit value here.
 * BUT! Status >does< need to be a signed!
 *----------------------------------------------------------------------------*/
typedef          e_s16  Status;   /* Always 16 bits (signed)   */

/*------------------------------------------------------------------------------
 * Defines and Macros
 *----------------------------------------------------------------------------*/


#undef NULL                     /* Correctly Define NULL */

#if	defined(__cplusplus)
  #define NULL (0)
#else
  #define NULL ((void*)(0))
#endif

/* Ignore common defines from previous headers (this file does it right) */
#undef  FALSE
#undef  TRUE
#undef  NO
#undef  YES
#undef  BAD
#undef  GOOD
#undef  STOP
#undef  GO
#undef  CLEAR
#undef  SET
#undef  OFF
#undef  ON
#undef  OK
#undef  NOTOK
#undef  SUCCESS
#undef  FAILURE
#undef  ERROR
#undef  NOERR
#undef  ENABLE
#undef  DISABLE

#define FALSE   (0)                    /* See FN#2 */
#define TRUE    (!FALSE)
#define NO      (0)
#define YES     (1)
#define BAD     (0)
#define GOOD    (1)
#define STOP    (0)
#define GO      (1)
#define CLEAR   (0)
#define SET     (1)
#define OFF     (0)
#define ON      (1)

#define OK      (0)
#define NOTOK   (1)
#define SUCCESS (0)
#define FAILURE (1)
#define VALID   (1)
#define INVALID (0)

#define ENABLE  (1)
#define DISABLE (0)

/*------------------------------------------------------------------------------
 * Constants
 *----------------------------------------------------------------------------*/
#if	defined(__cplusplus)

   const Bool   False     =  0;         /* See FN#1 */
   const Bool   True      =  (!False);
   const Bool   No        =  0;
   const Bool   Yes       =  1;
   const Bool   Bad       =  0;
   const Bool   Good      =  1;
   const Bool   Stop      =  0;
   const Bool   Go        =  1;
   const Bool   Clear     =  0;
   const Bool   Set       =  1;
   const Bool   Off       =  0;
   const Bool   On        =  1;

   const Status Ok        =  0;
   const Status Success   =  0;
   const Status Valid     =  0;
   const Status Notok     =  1;
   const Status Failure   =  1;
   const Status Invalid   =  1;

   const short  Enable    =  1;
   const short  Disable   =  0;

#else

#define False     ((Bool)(0))
#define True      ((Bool)(1)) 

#define No        ((Bool)(0))
#define Yes       ((Bool)(1))
#define Bad       ((Bool)(0))
#define Good      ((Bool)(1))
#define Stop      ((Bool)(0))
#define Go        ((Bool)(1))
#define Clear     ((Bool)(0))
#define Set       ((Bool)(1))
#define Off       ((Bool)(0))
#define On        ((Bool)(1))

#define Ok        ((Status)(0))
#define Success   ((Status)(0))
   #define Valid     ((Status)(0))
   #define Notok     ((Status)(1))
   #define Failure   ((Status)(1))
   #define Invalid   ((Status)(1))

   #define Enable    ((Status)(1))
   #define Disable   ((Status)(0))

#endif /* if C++ */

/*---------------------------------------------------------------------------
 * Miscelaneous MACROS
 */

/* Round a value upward to the nearest multiple of 4 */
#define ROUNDUP4(x) (((x) + 3) & ~3)
#define ROUNDUP(x,y) ((((n_long)(x)) + (((n_long)(y))-1)) & (0-((n_long)(y))))

#endif /* EEMBC_DT_H */

