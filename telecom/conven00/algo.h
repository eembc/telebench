/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef ALGO_H
#define ALGO_H

/*******************************************************************************
    Includes                                                                    
*******************************************************************************/
#include "thlib.h"

/*******************************************************************************
    Defines                                                                     
*******************************************************************************/
#define MAX_CODE_VECTORS 2
#define MAX_CONSTRAINT_LENGTH 8

/* Compile time Data set select for uuencode: 
 * DATA_1 through DATA_3
 * DATA_3 is default
 */ 
#if	(!defined(DATA_1) && !defined(DATA_2) && !defined(DATA_3))
#define DATA_3
#endif


/*******************************************************************************
    Global Variables                                                            
*******************************************************************************/

/*******************************************************************************
    Function Prototypes                                                         
*******************************************************************************/
void
convolutionalEncode (
    e_u8    *DataBits,                          /* Input data 1 bit per byte */
    e_s16   DataByteSize,                       /* Data size in bytes */
    e_s16   NumberCodeVectors,                  /* Number of code vectors (n) */
    e_s16   ConstraintLength,                   /* Constraint Length (K) */
    e_u8    (*CodeMatrix)[MAX_CODE_VECTORS],    /* Matrix of code vectors (column-wise) */
    e_u8    *BranchWords                        /* Output data 1 bit per byte */
);

#endif

