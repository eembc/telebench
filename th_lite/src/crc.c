/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */


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
