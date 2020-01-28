/*==============================================================================
 *$RCSfile: verify.h,v $
 *
 *   DESC : The Diffmeasure Utility
 *
 *  EEMBC : Telecom Subcommittee 
 *
 * AUTHOR : ARM Ltd., ECL, LLC
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2002/08/26 18:48:19 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/telecom/diffmeasure/verify.h,v $
 *
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: verify.h,v $
 * Revision 1.5  2002/08/26 18:48:19  rick
 * Bug #195: th_ calls not used
 *
 * Revision 1.4  2002/08/09 21:46:45  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.3  2002/04/01 20:51:35  administrator
 * Apply Standard Comment Block
 *
 * Revision 1.2  2002/02/22 20:46:12  rick
 * Fix d_union conflict in verify.h, thlib.c
 *
 * Revision 1.1  2002/02/18 23:51:54  rick
 * Completed Telocom TH_Lite conversion
 *
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
