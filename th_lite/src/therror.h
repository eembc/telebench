/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef   TH_ERROR_H     /* File Sentinal */
#define   TH_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

   /*------------------------------------------------------------------------------
    * Error return values
   */
   enum TH_ERRORS
      {
      THE_SUCCESS,            /* Success! */
      THE_FAILURE,             /* Generic Failure... :( */

      THE_BAD_PTR,            /* a pointer parameter was NULL */
      THE_BAD_THDEF_VERSION,  /* the THDef pointer did not point to a valid structure */
      THE_BAD_TCDEF_VERSION,  /* the THDef pointer did not point to a valid structure */
      THE_TC_INIT_FAILED,     /* The test component intialization failed */
      THE_BAD_BASE_PTR,       /* Bad base pointer for Malloc init */
      THE_BAD_SIZE,           /* The size parameter is bad */
      THE_OUT_OF_MEMORY       /* The test ran out of memory */
      };

   const char *th_error_str( int error );

   /*----------------------------------------------------------------------------*/

#ifdef __cplusplus
   }
#endif

#endif                /* File Sentinal */

