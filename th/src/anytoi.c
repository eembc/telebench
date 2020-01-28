/*==============================================================================
 *$RCSfile: anytoi.c,v $
 *
 *   DESC : Test Harness routines for benchmarks
 *
 * AUTHOR : ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2002/04/23 18:33:56 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th/src/anytoi.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: anytoi.c,v $
 * Revision 1.3  2002/04/23 18:33:56  rick
 * Match eembc_dt with Lite, remove stdinc.h
 *
 * Revision 1.2  2002/03/21 22:31:08  rick
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

 /*----------------------------------------------------------------------------
 *  ANYTOI.C
 */

#include <stdlib.h>  /* for atoi() */
#include <ctype.h>

#include "anytoi.h"

#define LOWCASE( c ) (((c) >= 'A' && (c) <= 'Z') ? (c)+' ' : (c))
#define UPWCASE( c ) (((c) >= 'a' && (c) <= 'z') ? (c)-' ' : (c))

/*----------------------------------------------------------------------------
 *  find_num_type()
 */

int find_num_type( const char *sp )

   {
   const char *tmp;

   for (tmp = sp; *tmp; tmp++)    /* Point tmp at the end of the string */
      {
      ;
      }

   tmp--;

   if (isdigit( sp[ 0 ] ) && sp[ 0 ] != '0' && ( *tmp == 'u' || *tmp == 'U' )) return (T_DEC);

   if (sp[ 0 ] == '0' && LOWCASE( sp[ 1 ] ) == 'x') return (T_HEX);

   if (isdigit( sp[ 0 ] ) && LOWCASE( *tmp ) == 'h') return (T_HEX);

   if (sp[ 0 ] == '0') return (T_OCT);

   if (isdigit( sp[ 0 ] ) || ( sp[ 0 ] == '-' && isdigit( sp[ 1 ] ))) return (T_INT);

   return (0);
   }

/*----------------------------------------------------------------------------
 *  hextoi()
 */

Word hextoi( const char *sp )

   {
   int i;
   Word rslt = 0;

   if (*sp == '\0') return (0);

   if (*sp == '0' && LOWCASE( sp[ 1 ] ) == 'x')
      sp += 2;
   else
      if (*sp == '0')
         sp++;


   for (i = 0; isxdigit( *sp ) && i < 4; sp++, i++)
      {
      rslt <<= 4;

      if (isdigit( *sp ))
         rslt += ( *sp - '0' );        /*lint !e737*/
      else
         rslt += UPWCASE( *sp ) - 55;  /*lint !e737*/
      }

   return (rslt);
   }


/*----------------------------------------------------------------------------
 *  octtoi()
 */

Word octtoi( const char *sp )

   {
   int i;
   Word rslt = 0;

   if (sp == NULL) return (0);

   for (i = 0; ( *sp >= '0' && *sp <= '7' ) && i < 6; sp++, i++)
      {
      rslt *= 010;

      rslt += ( *sp - '0' );           /*lint !e737*/
      }

   return (rslt);
   }

/*----------------------------------------------------------------------------
 *  dectoi()
 */

Word dectoi( const char *sp )

   {
   int i;
   Word rslt = 0;

   for (i = 0; isdigit( *sp ) && i < 5; sp++, i++)
      {
      rslt *= 10;

      rslt += ( *sp - '0' );           /*lint !e737*/
      }

   return (rslt);
   }

/*----------------------------------------------------------------------------
 *  anytoi()
 */

Word anytoi( const char *sp )

   {
   switch (find_num_type( sp ))
      {
      case T_DEC: return (dectoi( sp ));

      case T_INT: return (( Word ) atoi( sp ));

      case T_HEX: return (hextoi( sp ));

      case T_OCT: return (octtoi( sp ));

      default: return (0);
      }
   }

/*============================================================================== */
/* long versions */

/*----------------------------------------------------------------------------
 *  hextoi()
 */

Dword hextol( const char *sp )

   {
   int i;
   Dword rslt = 0;

   if (*sp == '\0') return (0);

   if (*sp == '0' && LOWCASE( sp[ 1 ] ) == 'x')
      sp += 2;
   else
      if (*sp == '0')
         sp++;

   for (i = 0; isxdigit( *sp ) && i < 8; sp++, i++)
      {
      rslt <<= 4;

      if (isdigit( *sp ))
         rslt += ( *sp - '0' );        /*lint !e737*/
      else
         rslt += UPWCASE( *sp ) - 55;  /*lint !e737*/
      }

   return (rslt);
   }


/*----------------------------------------------------------------------------
 *  octtoi()
 */

Dword octtol( const char *sp )

   {
   int i;
   Dword rslt = 0;

   if (sp == NULL) return (0);

   for (i = 0; ( *sp >= '0' && *sp <= '7' ) && i < 11; sp++, i++)
      {
      rslt *= 010;

      rslt += ( *sp - '0' );           /*lint !e737*/
      }

   return (rslt);
   }

/*----------------------------------------------------------------------------
 *  dectoi()
 */

Dword dectol( const char *sp )

   {
   int i;
   Dword rslt = 0;

   for (i = 0; isdigit( *sp ) && i < 10; sp++, i++)
      {
      rslt *= 10;

      rslt += ( *sp - '0' );           /*lint !e737*/
      }

   return (rslt);
   }

/*----------------------------------------------------------------------------
 *  anytoi()
 */

Dword anytol( const char *sp )

   {
   switch (find_num_type( sp ))
      {
      case T_DEC: return (dectol( sp ));

      case T_INT: return (( Dword ) atol( sp ));

      case T_HEX: return (hextol( sp ));

      case T_OCT: return (octtol( sp ));

      default: return (0);
      }
   }

/*----------------------------------------------------------------------------
 *  end of ANYTOI.C
 */
