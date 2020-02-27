/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef   SSUBS_H
#define   SSUBS_H

#include "eembc_dt.h"


/*- Function Prototypes ------------------------------------------------------*/

char  last_char( char *s );

void  char_remove( char *s, int i );
void  char_remove_n( char *s, int i, int n );

void  strip_l_spaces( char *s );    /* Leading */
void  strip_lt_spaces( char *s );   /* Trailing */
void  strip_t_spaces( char *s );    /* Leading & Trailing */
void  strip_all_spaces( char *s );  /* All */

void  make_simple_nl( char *str );

int   is_all_white_space( const char *s );

int   cpystr( char *dest, const char *src, int len );
int   cpypaddstr( char *dest, const char *src, int len );

void  paddstr( char *s, int len );

int   tabs_to_spaces( char *line, int tab );

unsigned int conv_to_ui( const char *str );
unsigned long conv_to_ul( const char *str );

int str_cmp( const char *s1, const char *s2 );
int str_icmp( const char *s1, const char *s2 );

int xlate_nl_inplace( char *str );
int xlate_nl( const char *str, char *dest_buf );

#endif
