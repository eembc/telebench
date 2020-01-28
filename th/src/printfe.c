/*==============================================================================
 *$RCSfile: printfe.c,v $
 *
 * DESC   : Contains a generic, stand-alone printf engine
 *
 *          int _printf( dosendf sf, void* ptr, const char* fmt, va_list args )
 *
 * AUTHOR : Richard Russel
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *          This implementation of printf is designed for embedded systems.
 *          ie. it does not have any linker dependancies on any other
 *          routines.  However, it does include stdarg.h.  Note that this
 *          is the only header file that this module uses!  Please try to
 *          keep it this way.
 *
 *          Also, this function does not build the entire output string in
 *          a temporary buffer before sending it.  It sends it a bit at a time.
 *          This means that this function can 'printf' any length string
 *          without running out of buffer space or stack space.
 *
 *          This function DOES NOT use recursion! (yay!) In other words
 *          it uses the same amount of stack space no matter how you
 *          call it.
 *
 * USAGE  : To use this module you will need to define at least one external
 *          function that sends characters (one at a time) to your output
 *          stream.  Note, this printf engine can support >multiple< output
 *          streams.  All you need to do is write several send functions.
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2002/05/23 20:22:40 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th/src/printfe.c,v $
 *
 * NOTES  : This module handles 16bit integers efficiently.  It uses
 *          two different functions to convert 16bit and 32bit values to
 *          ascii digits.  So, on systems where the int and long types are
 *          different sizes, this printf engine will work well
 *
 *        : The original block style comments have been preserved as comment
 *          blocks on the right and side of the code. Why throw away someone
 *          else's work.
 *
 *        : I have written this code to be compileable as a C or C++ module.
 *          Please try to keep it this way.  The define PDECL gives the
 *          public functions a "C" interface.
 *
 *        : When compiling C code, the GNU C++ compiler does not recognize
 *          C++ style comments, so only C style comments have been used.
 *
 *        : Also, this module is stand-alone.  It requires no other modules
 *          to work.  Ie. it uses slen() instead of strlen() etc.  It does
 *          not depend on itoa.  Please try to keep this module stand-alone.
 *          In other words, it requires no other header files except the
 *          stdarg.h file that comes with your compiler.  Please keep it
 *          this way.
 *
 *        : This module was coded using tab-3 and saved using all spaces.
 *
 *        : Because of the way printf() has to work, this module is not lint
 *          friendly, I have disabled most of the usefull lint messages.
 *          Unfortuneatly, this module needs more work than its worth to
 *          make it lint clean.  So, we just disable most of the lint message
 *
 * TODO   : Add floating point support (#ifdef'ed of course!)
 * ===========================================================================*/

#include "thcfg.h"

/* If USE_TH_PRINTF is not true, then 
 * just #ifdef out all the TH printf code
 */

/*----------------------------------------------------------------------------*/
/*lint -e652 */

#include <stddef.h>

#include "printfe.h"

#if USE_TH_PRINTF 

/*lint -e734 -e732 */
/*------------------------------------------------------------------------------
 * NAME   : slen
 *
 * DESC   : Computes the length of a string ( same as strlen() )
 * ---------------------------------------------------------------------------*/

static int slen( const char *s )

   {
   register int n = 0;
   while (*s++)
      n++;
   return (n);
   }

/*------------------------------------------------------------------------------
 * NAME   : prt_l
 *
 * DESC   : converts an unsigned long to an ascii string.
 *
 * PARAMS : prec - holds an integer containing the max number of chars
 *                 to be returned in the str.
 *          b    - base ( 8=octal 10=decimal 16=hex - surprise!
 *          x    - the unsigned integer that is the object of this exercise
 *          cset - use upper or lower case letters (for hex conversions)
 * ---------------------------------------------------------------------------*/

#define ptrbf (*_ptrbf)

static void prt_l( char **_ptrbf, int prec, unsigned int b, unsigned long x, int cset )

   {
   int   n;
   char  tmpbuf[ 12 ];
   char *cptr;

   cptr = tmpbuf;
   n = 0;

   do {
      if (cset == 0)
         *cptr++ = "0123456789abcdef"[ x % b ];
      else
         *cptr++ = "0123456789ABCDEF"[ x % b ];
      n++;
      x /= b;
      }
   while (x);

   if (( prec != 0 ) && ( n > prec ))
      cptr = tmpbuf + prec;

   while (n--)
      {
      *ptrbf++ = *--cptr;
      }
   }

/*------------------------------------------------------------------------------
 * NAME   : conv
 *
 * DESC   : converts digits in the fmt string to an integer
 *
 * NOTE   : This function WILL NOT convert negative values.  It assumes
 *          all values are >= zero.
 *
 * RETURNS: The converted value.  0 is guaranteed to be returned
 *          if no digits were found.
 * ---------------------------------------------------------------------------*/

#define pfmt (*__fmt)

static int conv( const char **__fmt )

   {                                           /*----------------------------*/
   register char c;                            /* Character temporary        */
   register int  n;                            /* Accumulator                */
                                               /*----------------------------*/
   n = 0;                                      /* Zero found so far          */
                                               /*                            */
   while ((( c = *pfmt++ ) >= '0' ) &&         /* While c is a digit         */
           ( c <= '9' )                        /*                            */
         )                                     /*                            */
      n = ( n * 10 ) + ( c - '0' );            /* Add c to accumulator       */
                                               /*                            */
   pfmt--;                                     /* Back up format pointer to  */
                                               /* character skipped above    */
   return (n);                                 /* See, wasn't that simple?   */
   }                                           /*----------------------------*/

/*------------------------------------------------------------------------------
 * NAME   : printfe
 *
 * DESC   : The printf engine
 *
 * PARAMS : sf   - the function used to send characters to the output stream
 *          ptr  - this is a void pointer that simply gets passed to the
 *                 send function.  It can be used to maintain state information
 *          fmt  - the format string
 *          args - the arguments to print
 *
 * RETURNS: The number of characters "sent" to the output stream.
 * ---------------------------------------------------------------------------*/

#define SEND( c )  {if ((srv=(*sf)(c,ptr))==0 ) return ccount; else ccount+=srv;}

int printfe( sender sf, void *ptr, const char *fmt, va_list args )

{                                  /*----------------------------------------*/
char     c;                        /* Format Character temp                  */
char     *s;                       /* SEND string pointer                    */
char     adj;                      /* Right/left adjust flag                 */
char     sign;                     /* Space for plus sign required? flag     */
char     buf[ 32 ];                /* Temporary buffer                       */
                                   /*----------------------------------------*/
int      srv;                      /* return value from the send function    */
int      padd;                     /* number of characters to padd           */
int      width;                    /* Field width                            */
int      prec = 0;                 /* Precision for "%x.y*"                  */
int      n;                        /* String Length Temp                     */
int      ccount;                   /* Character count                        */
int      b;                        /* base                                   */
int      cset;                     /* caps for hex or not 1=caps             */
int      is_long;                  /* indicates the argument is a long       */
int      sdec;                     /* format is 'D' or 'd'                   */
int      fmt_conv;                 /* Is flag an #?                          */
int      always_sign;              /* Flag if +/- sign is mandatory          */
int      sdouble;                  /* format is 'f' ifdef FLOAT_SUPPORT      */
long     xl;                       /* long conversion value                  */
#if FLOAT_SUPPORT
double   xd;                       /* double float conversion value          */
#endif
int      fdigit;                   /* Inverse value of next digit of mantissa*/
int      temp;
int      fprec = 6;                /* Precision for "%x.yf"; fprec = y;      */                                                /*                           */
char     padchar;                  /* '0' or ' ' (padding)                   */
char *_ptrbf;                      /* pointer to the conversion buffer       */
                                   /*----------------------------------------*/
cset = 0;                          /* lower case as default                  */
ccount = 0;                        /* Initially no characters                */
                                   /*                                        */
if (sf == NULL)                    /* Can't do output if its null            */
   return 0;                       /* No characters were sent                */
                                   /*                                        */
/*---------------------------------------------------------------------------*/
/* This is the main format conversion loop,  Load a character from the       */
/* format string.  If the character is '%', perform the appropriate          */
/* conversion.  Otherwise, just SEND the character.                          */
/*---------------------------------------------------------------------------*/
                                                /*                           */
while (( c = *fmt++ ) != 0)                     /* Pick up next format char  */
   {                                            /*                           */
   if (c != '%')                                /*---------------------------*/
      {                                         /*                           */
      if (c == '\n')                            /* is it a new line character*/
         {                                      /*                           */
         SEND( '\r' ); SEND( '\n' );            /* \n -->> \r\n              */
         }                                      /*                           */
      else                                      /*                           */
         SEND( c );                             /* If not '%', just SEND     */
      }                                         /*---------------------------*/
   else                                         /* It is a '%', convert      */
      {                                         /*---------------------------*/
/* Look for zero of more flag characters (-,+,0,#, or space)                 */
                                                /*---------------------------*/
      fmt_conv =  0;                            /* Assume no format convert  */
      adj = 'r';                                /* Assume right adjust       */
      sign = '+';                               /* Assume sign will be plus  */
      always_sign = 0;                          /* Assume only - sign, not + */
      padchar =  ' ';                           /* Use space Pad character   */
                                                /* as default padding        */
      while (*fmt == '#'||*fmt == '-'||*fmt == '+'||*fmt == ' '||*fmt == '0')
      {                                         /*        CJC 990905         */
      if (*fmt == '#')                          /* Going to use alternate    */
         {                                      /* conversion for e,E,f,g,G, */
         fmt_conv = 1;                          /* o,x, and X.               */
         ++fmt;                                 /* Bump past '#'             */
         }                                      /*---------------------------*/
      if (*fmt == '-')                          /* Check for left adjust     */
         {                                      /*                           */
         adj = 'l';                             /* Is left, set flag         */
         fmt++;                                 /* Bump format pointer       */
         }                                      /*---------------------------*/
      if (*fmt == '+')                          /* Check for always sign +/- */
         {                                      /*                           */
         always_sign = 1;                       /* Need a sign, set flag     */
         fmt++;                                 /* Bump format pointer       */
         }                                      /*---------------------------*/
      if (*fmt == ' ')                          /* If format is a space,     */
         {                                      /*                           */
         sign = ' ';                            /* leave blank for plus sign */
	 ++fmt;                                 /* Bump format pointer       */
         }                                      /*---------------------------*/
      if (*fmt == '0')                          /* Check for zero padding    */
         {                                      /*                           */
          padchar =  '0';                       /* Only pad w/zeroes if fmt  */                                                /* (A leading zero in fmt    */
          ++fmt;                                /* is actually '0'           */
	  }                                     /*---------------------------*/
      }                                         /* End of while for flags    */
/* Look for optional minimum field width */     /*---------------------------*/
      width = conv( &fmt );                     /* Convert width (if any)    */
/* Look for optional precision specification */ /*---------------------------*/
      prec = 0;                                 /* Return to default prec.   */
      if (*fmt == '.')                          /* '.' means precision spec  */
         {                                      /*                           */
         ++fmt;                                 /* Bump past '.'             */
         prec = fprec = conv( &fmt );           /* Convert precision spec    */
          }                                     /*                           */
/* Look for optional size specification L,l,or h                             */
      if (*fmt == 'L' || *fmt == 'l')           /* Long value??              */
         {                                      /*                           */
         fmt++;                                 /* Long conversion           */
         is_long = 1;                           /* remember this fact        */
         }                                      /*                           */
      else                                      /*                           */
         is_long = 0;                           /* nope, its an int          */
 /* Perform conversion operation */             /*---------------------------*/
      _ptrbf = buf;                             /* set buffer pointer        */
      s = 0;                                    /* Assume no SEND string     */
      b = 10;                                   /* Assume base 10            */
      sdec = 0;                                 /* assume not signed decimal */
      sdouble = 0;                              /* assume not a double float */                                                /*---------------------------*/
      switch (c = *fmt++)                       /* Next char is conversion   */
         {                                      /*                           */
         case 'D':                              /* Decimal                   */
         case 'd':                              /* base is already set       */
         case 'i':                              /* int is same as decimal    */
            sdec = 1;                           /* set the decimal flag      */
            break;                              /* Go do SEND                */
                                                /*---------------------------*/
         case 'U':                              /* Unsigned Decimal          */
         case 'u':                              /* base is already set       */
            break;                              /* Go do SEND                */
                                                /*---------------------------*/
         case 'o':                              /* Octal                     */
         case 'O':                              /*                           */
            b = 8;                              /* set base                  */
            break;                              /* Go do SEND                */
                                                /*---------------------------*/
         case 'X':                              /* Hex (uppercase)           */
            cset = 1;                           /* set base                  */
            b = 16;                             /* set base                  */
            break;                              /*                           */
                                                /*---------------------------*/
         case 'x':                              /* Hex (lowercase)           */
            cset = 0;                           /*                           */
            b = 16;                             /* set base                  */
            break;                              /* Go do SEND                */
                                                /*---------------------------*/
         case 'S':                              /* String                    */
         case 's':                              /*                           */
            s = (char*)va_arg(args,char*);      /* s points to the string    */
            break;                              /* Go do SEND                */
                                                /*---------------------------*/
         case 'C':                              /* Character                 */
         case 'c':                              /*      SEND?                */
            *_ptrbf++ = va_arg( args, int );    /* Just load buffer          */
            *_ptrbf = 0;                        /*                           */
            s = buf;                            /*                           */
         break;                                 /* Go do SEND                */
                                                /*---------------------------*/
         case 'p':                              /* pointer                   */
         case 'P':                              /*                           */
            xl = (long) va_arg(args,char*);     /* x = the pointer value     */
            cset = 1;                           /* set specs to same as      */
            b = 16;                             /* %08X                      */
            padchar = '0';                      /*                           */
            width = 8;                          /*                           */
                                                /* Assume 32bit pointers     */
            prt_l(&_ptrbf, prec, b, xl, cset);  /* convert arg to ascii      */
                                                /*                           */
            *_ptrbf = 0;                        /* Insure termination        */
            s = buf;                            /* Load the address          */
            break;                              /*                           */
#if FLOAT_SUPPORT                               /*---------------------------*/
         case 'f':                              /* double float              */
	    sdouble = 1;                        /* format %f                 */
	    fdigit = 1;                         /* Initial power of ten      */
            xd = va_arg(args,double);           /* xd = the float value      */
            if (xd <0)                          /* Is it negative?           */
            {
               sign = '-';                      /* output the minus sign     */
               xd *= -1;                        /* take absolute value       */
            }
            xl = (int) xd;                      /* Get the integer part      */
            xd -= (double) xl;                  /* Get the fractional part   */
            prt_l(&_ptrbf, 0, b, xl, cset);     /* Print int part            */
	    if ((fmt_conv == 1)||(fprec != 0))  /* If y != 0 or %#f,         */
	       *_ptrbf++ = '.';                 /* output the decimal point. */
	    while (fprec)                       /* --------------------------*/
	    {                                   /* Output digits right of    */
               fdigit *= 10;                    /* decimal point by promoting*/
               xl = (int) (xd * fdigit);        /* to single digit integers  */
                                                /* one  at a time.           */
               prt_l(&_ptrbf, 1, b, xl, cset);  /* base is already set (=10).*/
               xd -= ((double) xl )/fdigit ;    /* What's left of mantissa   */
               fprec --;                        /* until desired precision.  */
             }                                  /*                           */
            fprec = 6;                          /* Return to default prec.   */
            *_ptrbf = 0;                        /* Insure termination        */
            s = buf;                            /* Load the address          */
            break;                              /*                           */
#endif                                          /*---------------------------*/
         default:                               /* None of the above         */
            *_ptrbf++ = c;                      /*                           */
            *_ptrbf = 0;                        /*                           */
            s = buf;                            /*                           */
         }                                      /* End switch                */
                                                /*---------------------------*/
      if (s == 0)                               /* If s = 0 then             */
      {                                         /*    need to convert arg    */
         if (is_long)                           /* figure out what to cvt    */
	        xl = va_arg( args, long );          /* next arg is a long        */
	     else                                   /*                           */ 
	     {                                      /*                           */
	        if (sdec)                           /*                           */
	           xl = va_arg( args, int );        /* its a signed int          */
	        else                                /*                           */
	           xl = va_arg( args,unsigned int); /* its an unsigned int       */
	     }                                      /*                           */
         if (sdec && xl < 0)                    /* if 'D' && arg is < 0      */
         {                                      /*                           */
            sign = '-';                         /* output the minus sign     */
            xl *= -1;                           /* take absolute value       */
         }                                      /*                           */
	     prt_l(&_ptrbf, prec, b, xl, cset);     /* long sized arg to ascii   */
                                                /*                           */
         *_ptrbf = 0;                           /* Insure termination        */
         s = buf;                               /* Load address              */
      }                                         /*---------------------------*/
                                                /*                           */
      n = slen( s );                            /* Compute converted length  */
                                                /*---------------------------*/
      if (sdouble == 0)                         /* If not %f,                */
      {                                         /* and if precision was not  */
          if (prec == 0)                        /* specified, make same as   */	 
	    prec = n;                           /* string length.            */
       }                                        /*                           */
      else                                      /* If it was %x.yf, and no of*/
         if (n < width)                         /* characters needed is less */
	 {                                      /* than x, then print x      */
	       prec = width;                    /* characters.               */
	 }                                      /* Otherwise print           */
	 else                                   /* at least as many chars    */
	 {                                      /* as needed to represent the*/
	    width = n;                          /* number with y or default  */
	    prec = n;                           /* precision.                */
	  }                                     /*---------------------------*/
      padd = width - n;                         /* compute no of pad chars   */
	                                        /*---------------------------*/	 
      if (sign == '-' || always_sign || sign == ' ') /* Count sign as pad    */
         --padd;                                /* when padding to width.    */
      if (fmt_conv && b == 8)                   /* Count 0 as pad            */
         --padd;                                /* for %#o                   */
      if (fmt_conv && b == 16)                  /* Count 0x or 0X as pad     */
         padd -= 2;                             /* for %#x and %#X           */
      if (sdouble == 0 && prec > n)             /* Count zeroes added for    */
         padd = padd - (prec - n);              /* for precision as pad.     */	 
	                                        /*---------------------------*/
      if (adj == 'r' && padchar == ' ')         /* For right adjust with     */
         while (padd-- > 0)                     /* blank padding, pad        */
            {                                   /* in front of sign          */
            SEND( padchar );                    /* Thusly                    */
            }                                   /*                           */
                                                /*---------------------------*/			                        
      if (sign == '-')                          /* If neg number, always     */      
      {                                         /* put minus sign on front.  */
          SEND('-');                            /*                           */
      }                                         /*                           */
      else                                      /* Must be positive number.  */
      {                                         /*                           */
         if (always_sign)                       /* If format was %+***, then */
	 {                                      /* put a plus sign on front. */
	    SEND('+');                          /*                           */
         }                                      /*                           */
	 else                                   /* Must not have needed sign */
	 {                                      /*                           */
	 if (sign == ' ')                       /* If format was % ***(space)*/
	       SEND(' ');                       /* then put a blank          */
	 }                                      /* where plus sign would be  */
      }	                                        /*---------------------------*/
      if (fmt_conv == 1 && (b == 8 || b == 16)) /* If %#o or %#x or %#X,     */
      {                                         /* initiate output string w/ */
          SEND('0');                            /* Leading zero for %#o      */
	  if (b == 16)                          /* and x or X depending      */                        
	     SEND((cset == 0) ? 'x' : 'X');     /* on %#x or %#X             */
      }                                         /*---------------------------*/
      if (adj == 'r' && padchar == '0')         /* For right adjust with     */
         while (padd-- > 0)                     /* zero padding, pad behind  */
            {                                   /* sign                      */
            SEND( padchar );                    /* Thusly                    */
            }                                   /*                           */
                                                /*---------------------------*/
      if (sdouble == 0 && prec > n)          /* If precision specified    */
      {                                         /* for non-float is greater  */
            temp = prec - n;                    /* than string length,       */
            while (temp)                        /* have to pad to reach      */
            {                                   /* precision; zeroes for     */
               SEND((*fmt == 's' || *fmt == 'c' ) ? ' ' : '0' );  /* %d, %o, */
               --temp;                          /* %x, %X; blank for %s.     */
	    }
      }	                                        /*---------------------------*/
      while (( n-- ) && ( prec-- > 0 ))         /* SEND Converted data       */
         SEND( *s++ );                          /* Send it                   */
                                                /*---------------------------*/
      while (padd-- > 0)                        /* If left adjust,           */
         SEND( padchar );                       /* Send a padd character     */
      }                                         /* End else clause           */
      sdouble = 0;                              /* Clean up for next format. */
   }                                            /* End while                 */
va_end(args);                                   /*---------------------------*/
return (ccount);                                /* Return appropriate value  */
}                                               /*---------------------------*/

/*------------------------------------------------------------------------------
 * NAME   : sp
 *
 * DESC   : Sender function for sprintf
 *
 * PARAMS : c    - the character to write to the string
 *          ptr  - a pointer to a pointer to the string
 *
 * RETURNS: Always returns 1
 * ---------------------------------------------------------------------------*/

#define SS (*(char**)ptr)

static int sp( char c, void *ptr )

   {
   *SS++ = c;
   *SS = '\0';    /* keep the string null terminated */
   return 1;
   }

/*------------------------------------------------------------------------------
 * NAME   : sprintf
 *
 * DESC   : Sprintf
 *
 * PARAMS : s    - the string (buffer) to write to
 *          fmt  - the format string
 *
 * RETURNS: The number of characters written to the output stream.  This does
 *          not include the terminating '\0'
 * ---------------------------------------------------------------------------*/

int sprintf( char *s, const char *fmt, ... )

   {
   va_list args;
   va_start( args, fmt );                        /* star the argument scan  */

   return printfe( sp, &s, fmt, args );
   }

/*------------------------------------------------------------------------------
 * NAME   : vsprintf
 *
 * DESC   : vsprintf
 *
 * PARAMS : s    - the string (buffer) to write to
 *          fmt  - the format string
 *          args - the arguments to print
 *
 * RETURNS: The number of characters written to the output stream.  This does
 *          not include the terminating '\0'
 * ---------------------------------------------------------------------------*/

int vsprintf( char *s, const char *fmt, va_list args )

   {
   return printfe( sp, &s, fmt, args );
   }

#endif /* USE_TH_PRINTF */

