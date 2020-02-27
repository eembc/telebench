/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#include "eembc_dt.h"
#include "therror.h"

typedef struct error_desc
   {
   int error;
   const char *desc;
   }
error_desc;


static error_desc errors[] =
    {
    { THE_SUCCESS,            "Success" },
    { THE_FAILURE,            "Failure" },

    { THE_BAD_PTR,            "pointer parameter is NULL" },
    { THE_BAD_THDEF_VERSION,  "THDef pointer did not point to a valid structure", },
    { THE_BAD_TCDEF_VERSION,  "TCDef pointer did not point to a valid structure" },
    { THE_TC_INIT_FAILED,     "Test component intialization failed" },
    { THE_BAD_BASE_PTR,       "Bad base pointer for Malloc init" },
    { THE_BAD_SIZE,           "The size parameter is bad" },

    { -1, NULL }
    };

/*-----------------------------------------------------------------------------
 * FUNC   : th_error_str
 *
 * DESC   : Gets a textual description of an error
 *
 * PARAMS : the error value
 *
 * RETURNS: A pointer to a string describing the error.
 * --------------------------------------------------------------------------*/

const char *th_error_str( int error )

   {
   int                      i;
   static const char *unknown = "Undefined Error";

   /*YES!  This is a straight forward linear search!  Please keep it this way.
    *      This avoids having to keep the list sorted (YUCH!)  This is
    *      does not need to be a high peroformance function.
   */
   for (i = 0; errors[ i ] . desc != NULL; i++)
      {
      if (errors[ i ] . error == error)
         return errors[ i ] . desc;
      }

   return unknown;
   }
