/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef   ANYTOI_H
#define   ANYTOI_H

#include "eembc_dt.h"

/*------------------------------------------------------------------------------
 * Values returned by find_num_type()
 */

#define T_DEC    1
#define T_INT    2
#define T_OCT    3
#define T_HEX    4

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

   int find_num_type( const char *sp );

   /* All these (word and dword) conversions are unsigned. */
   /* Note that if the string holds a negative decimal value, the conversion */
   /* will be signed, but the aanytoi() and anytol() functions will return */
   /* the value as unsgined.  In this case, merely cast the return */
   /* value to an int or long. */

   Word  hextoi( const char *sp );
   Word  octtoi( const char *sp );
   Word  dectoi( const char *sp );
   Word  anytoi( const char *sp );

   Dword hextol( const char *sp );
   Dword octtol( const char *sp );
   Dword dectol( const char *sp );
   Dword anytol( const char *sp );

#ifdef __cplusplus
   }
#endif
#endif
/*==============================================================================
 * ENDOF  : ANYTOI.H
 * ===========================================================================*/
