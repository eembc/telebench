/*==============================================================================
 *$RCSfile: crc.c,v $
 *
 *   DESC : TH_Lite Test Harness
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * AUTHOR : ARM Ltd., ECL, LLC
 *
 *    CVS : $Revision: 1.12 $
 *          $Date: 2002/09/12 19:04:47 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/th_lite/src/crc.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: crc.c,v $
 * Revision 1.12  2002/09/12 19:04:47  rick
 * Fix dbpf and | definitions
 *
 * Revision 1.11  2002/05/10 23:39:24  rick
 * Fix missing shifts in 16, and 32 bit CRC calculations
 *
 * Revision 1.10  2002/03/18 21:15:08  rick
 * Add al_report, cyclecount, crc fix in iirflt, and pktflow.
 *
 * Revision 1.7  2002/03/12 21:45:54  rick
 * TH Lite harness updates, and Build changes from directory changes
 *
 * Revision 1.9  2002/03/08 00:30:36  administrator
 * Fix Endian definition, vprintf, and rotate endian crc's
 *
 * Revision 1.8  2002/02/27 17:40:49  rick
 * Update Documentation and API comments for 0.3
 *
 * Revision 1.8  2002/02/25 17:15:35  rick
 * Add comment blocks, fix atime th_report call.
 *
 * Revision 1.6  2002/02/21 19:52:11  administrator
 * Build TH_Lite makefile for cygwin
 *
 * Revision 1.5  2002/02/19 20:12:09  rick
 * Add long copyright message per Alan.
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


#include "thlib.h" /* pick up prototypes from api */


/********************************************************************   
Function:  calc_crc
Purpose:  Compute crc16 a byte at a time 
Type: PUBLIC
********************************************************************/ 

#if	CRC_CHECK || NON_INTRUSIVE_CRC_CHECK  

e_u16 Calc_crc8(e_u8 data, e_u16 crc )
{
	e_u8 i,x16,carry;

	for (i = 0; i < 8; i++)
    {
		x16 = (e_u8)((data & 1) ^ ((e_u8)crc & 1));
		data >>= 1;
		if (x16 == 1)
		{
		   crc ^= 0x4002;
		   carry = 1;
		}
		else carry = 0;
		crc >>= 1;
		if (carry)
		   crc |= 0x8000;
		else
		   crc &= 0x7fff;
    }
	return crc;
} 
/*********************************************************************/
e_u16 Calc_crc16( e_u16 data, e_u16 crc )
{

	crc = Calc_crc8( (e_u8)(data & 0x00FF ), crc );
	crc = Calc_crc8( (e_u8)((data & 0xFF00)>>8), crc );
	return crc;
}


/*********************************************************************/
e_u16 Calc_crc32( e_u32 data, e_u16 crc )
{

	crc = Calc_crc8( (e_u8)(data & 0x000000FF), crc );
	crc = Calc_crc8( (e_u8)((data & 0x0000FF00)>>8), crc );
	crc = Calc_crc8( (e_u8)((data & 0x00FF0000)>>16), crc );
	crc = Calc_crc8( (e_u8)((data & 0xFF000000)>>24), crc );

	return crc;
}
#endif 
