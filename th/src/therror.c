/*==============================================================================
 *$RCSfile: therror.c,v $
 *
 *   DESC : Test Harness error messages.
 *
 * AUTHOR : ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2002/04/23 18:33:56 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th/src/therror.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: therror.c,v $
 * Revision 1.5  2002/04/23 18:33:56  rick
 * Match eembc_dt with Lite, remove stdinc.h
 *
 * Revision 1.4  2002/04/02 17:06:27  administrator
 * Remove whitespace before # directives
 *
 * Revision 1.3  2002/03/23 00:41:19  rick
 * Fix misspelling THE_FAILURE
 *
 * Revision 1.2  2002/03/21 22:31:10  rick
 * Network Harness, and empty benchmark fixes
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
