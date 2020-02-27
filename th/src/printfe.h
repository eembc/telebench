/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef   PRINTFE_H
#define   PRINTFE_H

#ifndef   THCFG_H
#include "thcfg.h"
#endif

#if USE_TH_PRINTF

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/

typedef int (*sender) ( char c, void *ptr );

int printfe( sender sf, void *ptr, const char *fmt, va_list args );

int sprintf( char *s, const char *fmt, ... );
int vsprintf( char *s, const char *fmt, va_list args );

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
   }
#endif

#endif /* #if USE_TH_PRINTF */


#endif /* file sentinal */

