/*==============================================================================
 *$RCSfile: therror.h,v $
 *
 *   DESC : Error Value Defintions for the Test Harness
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * AUTHOR : ARM Ltd., ECL, LLC
 *
 *    CVS : $Revision: 1.11 $
 *          $Date: 2002/03/18 21:15:09 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th_lite/src/therror.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: therror.h,v $
 * Revision 1.11  2002/03/18 21:15:09  rick
 * Add al_report, cyclecount, crc fix in iirflt, and pktflow.
 *
 * Revision 1.7  2002/03/12 21:45:54  rick
 * TH Lite harness updates, and Build changes from directory changes
 *
 * Revision 1.7  2002/03/08 00:30:37  administrator
 * Fix Endian definition, vprintf, and rotate endian crc's
 *
 * Revision 1.4  2002/02/27 17:40:49  rick
 * Update Documentation and API comments for 0.3
 *
 * Revision 1.6  2002/02/25 17:15:35  rick
 * Add comment blocks, fix atime th_report call.
 *
 * Revision 1.2  2002/02/19 20:12:09  rick
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

