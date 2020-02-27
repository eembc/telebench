/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

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
