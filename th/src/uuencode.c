/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

/*
 *		Simplified interface using UUENCODING
 *		(as specified in GNU)
 *		Writes it's output to stdout
 *		Adopted by Sergei Larin
 */ 

#include "uuencode.h" 

#include <stdio.h> 

/* 
 * commented out 2/15/00 because sys/stat.h is not ANSI std.  If you DO have this
 * file then uncomment this out and comment out the following two defines.  arw
 */
#ifdef	HAVE_SYS_STAT
#include <sys/stat.h> 
#else
#define _S_IREAD        0000400         /* read permission, owner */
#define _S_IWRITE       0000200         /* write permission, owner */
#endif


/* Standard encoding table. Base64 is not used*/
const Char uu_std[64] =
{
  '`', '!', '"', '#', '$', '%', '&', '\'',
  '(', ')', '*', '+', ',', '-', '.', '/',
  '0', '1', '2', '3', '4', '5', '6', '7',
  '8', '9', ':', ';', '<', '=', '>', '?',
  '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
  'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
  'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
  'X', 'Y', 'Z', '[', '\\', ']', '^', '_'
};

/* Pointer to the translation table we currently use.  */
const Char *trans_ptr = uu_std;

/* ENC is the basic 1 character encoding function to make a char printing.  */
#define ENC(Char) (trans_ptr[(Char) & 077])

/*
 *	Gnu style uuencoding routine
 *  encodes buffer raw_buffer of size raw_buf_len
 *
 */ 

n_void encode (const char *raw_buffer, n_int raw_buf_len)
{
  register n_int	ch, n	= 0;
  n_int			    buf_cnt = 0;
  Char			    buf[80];
  register Char     *p		= buf;
  

  if(!raw_buf_len || raw_buf_len <0 || !raw_buffer){
	  t_printf("Uuencode buffer parameters error.\n"); /* changed to t_printf() arw 2-14-00 */
	  return;
  } 

  trans_ptr = uu_std;	/* used by ENC macro */

  while (1){
	  for(n = 0; n<45;n++){
		  if(n+buf_cnt >= raw_buf_len) break; 
		  buf[n]	= raw_buffer[n+buf_cnt]; 
	  }
	  buf_cnt += 45; 

      if (n == 0)					break;
	  if (th_putchar (ENC (n)) == EOF)	break;

	  for (p = buf; n > 2; n -= 3, p += 3)
		{
			ch = *p >> 2;
			ch = ENC (ch);
			if (th_putchar ((Char) ch) == EOF)	break;
			ch = ((*p << 4) & 060) | ((p[1] >> 4) & 017);
			ch = ENC (ch);
			if (th_putchar ((Char) ch) == EOF)	break;
			ch = ((p[1] << 2) & 074) | ((p[2] >> 6) & 03);
			ch = ENC (ch);
			if (th_putchar ((Char) ch) == EOF)	break;
			ch = p[2] & 077;
			ch = ENC (ch);
			if (th_putchar ((Char) ch) == EOF)	break;
		}

		if (n != 0)						break;
		if (th_putchar ('\n') == EOF)		break;
    }

    while (n != 0){
		Char c1 = *p;
		Char c2 = (Char) (n == 1 ?  0 :  p[1]);

		ch = c1 >> 2;
		ch = ENC (ch);
		if (th_putchar ((Char) ch) == EOF)		break;

		ch = ((c1 << 4) & 060) | ((c2 >> 4) & 017);
		ch = ENC (ch);
		if (th_putchar ((Char) ch) == EOF)		break;

		if (n == 1)
			ch = ENC ('\0');
		else{
			ch = (c2 << 2) & 074;
			ch = ENC (ch);
		}
		if (th_putchar ((Char) ch) == EOF)		break;
		ch = ENC ('\0');
		if (th_putchar ((Char) ch) == EOF)		break;
		th_putchar ('\n');
		break;
    }

	th_putchar (ENC ('\0'));
	th_putchar ('\n');
}

/* Larin 
 * Code for uu pipe to upload file 
 */
 
n_int uu_send_buf( const char* buf, n_int length, const char* fn  )
{
   Dword	mode;

   /* Force the stream to be with r/w permition */ 
   mode = _S_IREAD | _S_IWRITE;
   /* write to the stdout */ 
   t_printf ("begin %lo %s\n",mode,fn);
   encode(buf,length);
   t_printf ("end\n\n");

   return 0; /* Success; */ 
}

