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


   /*------------------------------------------------------------------------------
    * The Test Harness Lite Application Layer API
    */

	size_t	al_ticks( void );
	size_t	al_ticks_per_sec( void );
	size_t	al_tick_granularity( void );

	void	al_signal_start( void );
	size_t	al_signal_finished( void );
	void	al_exit( int exit_code);
	int		al_printf(const char *fmt, va_list args);
	int		al_sprintf(char *str, const char *fmt, va_list args);
	void	al_report_results( void );
	void	al_main(int argc, const char* argv[]);

   /*----------------------------------------------------------------------------*/

#ifdef __cplusplus    /* Take this out if you don't need it */
   }
#endif

#endif                /*  File Sentinal */

