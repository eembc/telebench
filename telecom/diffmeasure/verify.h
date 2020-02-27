/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef	VERIFY_H
#define	VERIFY_H

#include <math.h>
#include "thlib.h"

/* typedef enum {REAL, COMPLEX} DATA_TYPE;*/
typedef 
enum {
	BAD_F = EOF, 
REAL = 1, 
COMPLEX = 2} 
DATA_TYPE;



double	diffmeasure (e_f64 *, int , DATA_TYPE , e_s16 *, int , DATA_TYPE );

/* Used to convert diffmeasure output into THResults */

	typedef union {
		double	d;
		size_t	v[2];
	} d_union;

#endif
