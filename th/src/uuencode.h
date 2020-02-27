/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */


#ifndef   UUENCODE_H       
#define   UUENCODE_H

#include "thlib.h"

int uu_send_buf( const char*, int, const char*  );
int t_printf( const char *, ... );
n_void encode (const char *raw_buffer, n_int raw_buf_len);

#endif
