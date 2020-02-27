/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */


#include <string.h>
#include <ctype.h>

#include "ssubs.h"

/*------------------------------------------------------------------------------
 * NAME   : last_char
 *
 * RETURNS: The last character in the string.  If the string is 0 length
 *          the null character is returned
 * ---------------------------------------------------------------------------*/

char last_char( char *s )

   {
   int i = strlen( s );

   if (i)
      return s[ i - 1 ];
   else
      return '\0';
   }

/*------------------------------------------------------------------------------
 * NAME   : char_remove
 *
 * ACTION : removes the character at postion i in the string pointed to
 *          by s.
 * ---------------------------------------------------------------------------*/

void char_remove( char *s, int i )

   {
   for (; s[ i ]; i++)
      s[ i ] = s[ i + 1 ];
   }

/*------------------------------------------------------------------------------
 * NAME   : char_remove
 *
 * ACTION : removes n characters at postion i in the string pointed to
 *          by s.
 * ---------------------------------------------------------------------------*/

void char_remove_n( char *s, int i, int n )

   {
   if (n > 0)
      for (; s[ i + n - 1 ]; i++)
         s[ i ] = s[ i + n ];
   }

/*------------------------------------------------------------------------------
 * NAME   : make_simple_nl
 *
 * DESC   : Change all \r\n to \n's
 *
 *          This function will handle multiple \r characters in front
 *          of a '\n'  for example \r\r\n -> \n
 *
 *          It leaves simple sequences of '\r' characters alone
 * ---------------------------------------------------------------------------*/

void make_simple_nl( char *str )

   {
   char *s;
   int   n;
   int   i;

   for (s = str; *s; s++)
      {
      if (*s == '\r')
         {
         for (n = 0; s[ n ] == '\r'; n++)
            {
            ;
            }

         if (s[ n ] == '\n')
            {
            for (i = 0; s[ i + n - 1 ]; i++)
               s[ i ] = s[ i + n ];
            }
         }
      }
   }

/*------------------------------------------------------------------------------
 * NAME   : strip_l_spaces
 *
 * ACTION : Strips leading white space from a string
 *
 * NOTE   : White space is any thing matched by the isspace() macro
 * ---------------------------------------------------------------------------*/

void strip_l_spaces( char *s )

   {
   int i;

   for (i = 0; isspace( s[ i ] ); i++)
      /* null statement */ ;

   char_remove_n( s, 0, i );
   }

/*------------------------------------------------------------------------------
 * NAME   : strip_t_spaces
 *
 * ACTION : Strips trailing white space from a string
 *
 * NOTE   : White space is any thing matched by the isspace() macro
 *
 *        : This routine could be written a little more efficiently if we
 *          allowed the index value i to go to -1 and just always
 *          set s[i] to '\0' at the end of the loop.  However, if s points
 *          to a protected piece of memory, or the compiler doesn't support
 *          negative indexes ( some don't) then this function would fail.
 * ---------------------------------------------------------------------------*/

void strip_t_spaces( char *s )

   {
   int i, eos;

   if (( eos = strlen( s )) > 0)
      {
      for (i = eos - 1; i >= 0 && isspace( s[ i ] ); i--)
         /* null statement */ ;

      s[ i + 1 ] = '\0';
      }
   }

/*------------------------------------------------------------------------------
 * NAME   : strip_lt_spaces
 *
 * ACTION : Strips leading and trailing white space from a string
 *
 * NOTE   : White space is any thing matched by the isspace() macro
 * ---------------------------------------------------------------------------*/

void strip_lt_spaces( char *s )

   {
   int i;

   for (i = 0; isspace( s[ i ] ); i++)
      /* null statement */ ;

   char_remove_n( s, 0, i );

   strip_t_spaces( s );
   }

/*------------------------------------------------------------------------------
 * NAME   : strip_all_spaces
 *
 * ACTION : Strips all white space from a string
 *
 * NOTE   : White space is any thing matched by the isspace() macro
 * ---------------------------------------------------------------------------*/

void strip_all_spaces( char *s )

   {
   int i;
   int span = 0;

   if (*s)
      {
      for (span = i = 0;; i++)
         {
         if (isspace( s[ i ] ))
            {
            span++;
            }
         else
            {
            if (span > 0)
               {
               if (( s[ i - span ] = s[ i ] ) == '\0')
                  break;
               }
            else
               {
               if (s[ i ] == '\0')
                  return;
               }
            }
         }
      }

   return;
   }

/*------------------------------------------------------------------------------
 * NAME   : cpystr
 *
 * ACTION : Copy a string to another string with a maximum length.
 *          dest is guaranteed to be null terminated even if maxlen == 0.
 *
 *          The src string is truncated if necessary.
 *
 * NOTE   : dest string must be maxlen bytes long physically.
 *
 *        : maxlen includes the null
 *
 * RETURNS: TRUE  if src string was truncated
 *          FALSE if it was completely copied
 * ---------------------------------------------------------------------------*/

int cpystr( char *dest, const char *src, int maxlen )

   {
   if (maxlen == 0)
      return True;

   while (maxlen != 0 && *src != '\0')
      {
      *dest = *src;

      maxlen--;

      if (!maxlen == 0 && *src != '\0')
         {
         dest++; src++;
         }
      }

   *dest = '\0';

   return *src != '\0';
   }

/*------------------------------------------------------------------------------
 * NAME   : cpypaddstr
 *
 * ACTION : Copy a string to another string with a maximum length.
 *          dest is guaranteed to be null terminated even if maxlen == 0.
 *
 *          If the length of the source string is < maxlen, then dest
 *          is padded on the right with spaces.
 *
 *          The src string is truncated if necessary.
 *
 * NOTE   : dest string must be maxlen bytes long physically.
 *
 *        : maxlen includes the null
 *
 * RETURNS: TRUE  if src string was truncated
 *          FALSE if it was completely copied
 * ---------------------------------------------------------------------------*/

int cpypaddstr( char *dest, const char *src, int maxlen )

   {
   int rf; /* return flag */

   if (maxlen == 0)
      return True;

   while (maxlen != 0 && *src != '\0')
      {
      *dest = *src;

      maxlen--;

      if (maxlen != 0 && *src != '\0')
         {
         dest++; src++;
         }
      }

   rf = ( *src != '\0' && maxlen == 0 );

   while (maxlen != 0)
      {
      *dest = ' ';

      maxlen--;

      if (maxlen != 0)
         dest++;
      }

   *dest = 0;

   return rf;
   }

/*------------------------------------------------------------------------------
 * NAME   : is_all_white_space
 *
 * ACTION : Scans a string to see if it contains nothing but spaces
 *
 * RETURNS: True if the string contains nothing but white space or is
 *               empty (zero length), or NULL
 *          Flase otherwise
 * ---------------------------------------------------------------------------*/

int is_all_white_space( const char *s )

   {
   if (s == NULL || *s == '\0')
      return True;

   while (*s)
      if (!isspace( *s++ ))
         return False;

   return True;
   }

/*------------------------------------------------------------------------------
 * NAME   : paddstr
 *
 * ACTION : make a string the given length, by adding spaces on the right
 *          or truncating as necessary.
 *
 * CAVEAT :dest string must be len+1 bytes long physically.
 * ---------------------------------------------------------------------------*/

void paddstr( char *s, int len )

   {
   while (*s && len) {
      len--; s++;
      }

   while (len > 0)
      {
      *s++ = ' ';
      len--;
      }

   *s = 0;
   }

/*------------------------------------------------------------------------------
 * NAME   : tabs_to_spaces
 *
 * DESC   : Convers all tabs in a string to spaces using the given
 *          tab size.
 *
 * RETURNS: the new length of the string
 *
 * CAVEAT : The conversion is done to a buffer, the the buffer is copyied
 *          back to the original string.  Make sure the original string
 *          is physicaly large enough to hold the expanded string.
 *
 *        : Since this function uses a static buffer for the translation,
 *          it is NOT re-entrant.
 *
 *        : Max lenght of the resultant string is 1024 characters
 * ---------------------------------------------------------------------------*/

static char tmp[ 1024 ];

#define PUT(c) { tmp[col++]=c; new_len++; }

int tabs_to_spaces( char *line, int tab )

   {
   int i, tab_cnt, col, incr, new_len;

   for (new_len = tab_cnt = i = col = 0; line[ i ]; i++)
      {
      if (line[ i ] == '\t')
         {
         for (incr = tab - (( col + tab ) % tab ); incr; incr--) PUT( ' ' );
         tab_cnt++;
         }
      else
         PUT( line[ i ] );
      }

   PUT( 0 );

   if (tab > 0)
      strcpy( line, tmp );

   return (new_len);
   }

/*------------------------------------------------------------------------------
 * NAME   : conv_to_ui
 *
 * DESC   : converts digits in a string to an unsigned integer
 *
 * NOTE   : This function WILL NOT convert negative values.  It assumes
 *          all vlues are >= zero.
 *
 * RETURNS: The converted value.  0 is guranteed to be returned
 *          if no digits were found.
 * ---------------------------------------------------------------------------*/

unsigned int conv_to_ui( const char *str )

   {
   register char c;                            /* Character temporary */
   register unsigned int n = 0;                 /* Accumulator */

   while ((( c = *str++ ) >= '0' ) && ( c <= '9' )) /* While c is a digit */
      n = ( n * 10 ) + ( c - '0' );            /* Add c to accumulator */

   return (n);
   }

/*------------------------------------------------------------------------------
 * NAME   : conv_to_ul
 *
 * DESC   : converts digits in a string to an unsigned long
 *
 * NOTE   : This function WILL NOT convert negative values.  It assumes
 *          all vlues are >= zero.
 *
 * RETURNS: The converted value.  0 is guranteed to be returned
 *          if no digits were found.
 * ---------------------------------------------------------------------------*/

unsigned long conv_to_ul( const char *str )

   {
   register char c;                            /* Character temporary        */
   register unsigned long n = 0l;              /* Accumulator                */

   while ((( c = *str++ ) >= '0' ) && ( c <= '9' )) /* While c is a digit         */
      n = ( n * 10 ) + ( c - '0' );            /* Add c to accumulator       */

   return (n);
   }

/*------------------------------------------------------------------------------
 * NAME   : str_cmp
 *
 * DESC   : works just like strcmp() but with a different name
 *
 * RETURNS:  0 if the strings are equal
 *          -1 if s1 is "less than" s2
 *          +1 if s1 is "greater than" s2
 * ---------------------------------------------------------------------------*/

int str_cmp( const char *s1, const char *s2 )
   {
   while (*s1 == *s2++)
      {
      if (*s1++ == '\0')
         return 0;
      }
   if (*s1 < *--s2)
      return -1;
   else
      return  1;
   }

/*------------------------------------------------------------------------------
 * NAME   : str_icmp
 *
 * DESC   : works just like stricmp() but with a different name
 *
 *          This is simply a case insensitive version of str_cmp()
 *
 * RETURNS:  0 if the strings are equal
 *          -1 if s1 is "less than" s2
 *          +1 if s1 is "greater than" s2
 * ---------------------------------------------------------------------------*/

#define TUPR(c) (((c) >= 'a' && (c) <= 'z') ? ((c)-' ') : (c))

int str_icmp( const char *s1, const char *s2 )

   {
   while (TUPR( *s1 ) == TUPR( *s2 ))
      {
      if (*s1++ == '\0')
         return 0;

      s2++;
      }

   s2--;

   if (TUPR( *s1 ) < TUPR( *s2 ))
      return -1;
   else
      return  1;
   }

/*------------------------------------------------------------------------------
 * FUNC   : xlate_nl
 *
 * DESC   : Translates \n to \n\r and puts in a buffer
 *
 *          This function takes a string and copies it to a buffer. During
 *          the copy translates \n charcters to the \r\n sequence.
 *
 * PARAMS : str      - the string to translate
 *          dest_buf - the translates string goes here
 *
 * RETURNS: The length of the string in the buffer
 * ---------------------------------------------------------------------------*/

#if !defined( NO_CRLF_XLATE )

int xlate_nl( const char *str, char *dest_buf )

   {
   int cnt = 0;
   char *s = dest_buf;

   while (*str)
      {
      if (*str == '\n')
         {
         cnt++;
         *s++ = '\r';
         }

      *s++ = *str++;
      cnt++;
      }

   *s = '\0'; /* terminate the new string in pf_buf */

   return cnt;
   }

#endif

/*------------------------------------------------------------------------------
 * FUNC   : xlate_nl_inplace
 *
 * DESC   : Translates \n to \n\r in place
 *
 *          This function translates \n characters to \n\r sequence in
 *          place.
 *
 * NOTE   : Use of this funciton assumes that the string can be made
 *          longer in place!!!
 *
 * RETURNS: The length of the translated string
 * ---------------------------------------------------------------------------*/

#if !defined( NO_CRLF_XLATE )

int xlate_nl_inplace( char *str )

   {
   int   nl_cnt;
   int   i;
   int   len;
   char *s;

   /* Count the new lines in the string */
   for (i = nl_cnt = 0, s = str; *s; s++, i++)
      if (*s == '\n')
         nl_cnt++;

   if (nl_cnt == 0)     /* if there are no '\n' characters */
      return i;         /* just return the length of the string */

   len = i + nl_cnt;    /* Compute the length of the new string */

   /* Copy the string to the destination buffer and insert '\r'
    * characters as required.
   */
   for (; nl_cnt; i--)
      {
      if (( str[ i + nl_cnt ] = str[ i ] ) == '\n')
         {
         nl_cnt--;
         str[ i + nl_cnt ] = '\r';
         }
      }

   return len; /* Return the length of the string in the destination buffer */
   }

#endif
