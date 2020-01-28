/*==============================================================================
 *$RCSfile: verify.c,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 *  EEMBC : Network Subcommittee 
 *
 * AUTHOR : Sergei Lavin, ECL, LLC
 *
 *    CVS : $Revision: 1.7 $
 *          $Date: 2002/08/26 18:48:19 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/telecom/diffmeasure/verify.c,v $
 *
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: verify.c,v $
 * Revision 1.7  2002/08/26 18:48:19  rick
 * Bug #195: th_ calls not used
 *
 * Revision 1.6  2002/08/20 14:53:23  rick
 * Remove fprintf, incompatible with harness
 *
 * Revision 1.5  2002/08/09 21:46:45  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.4  2002/05/22 17:55:06  rick
 * Replace assert.h with thassert.h, add assert functions to th lite.
 *
 * Revision 1.3  2002/04/08 22:26:04  rick
 * Update Depgen for vc++ options
 *
 * Revision 1.2  2002/04/01 20:51:35  administrator
 * Apply Standard Comment Block
 *
 * Revision 1.1  2002/02/18 23:51:54  rick
 * Completed Telocom TH_Lite conversion
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

/*******************************************************************
*
This program computes the difference measure in dB
                          Sum of |Errors|
		DiffM = 10 log10  --------------------
                          Sum of |Signal|
                          
between two data sets, either Real (one value per line) or
Complex (two values per line).

One data set is the Reference (Floating Point) and the other is
the Data (Fixed Point).

A provision is included for supplying a Reference Scale Value to
bring the amplitude values of the floating point data in line
with the fixed point data. The program displays the maximum amplitude
value for both the Reference and Data files to assist the user in
determining the appropriate Reference Scale Value.

Operation:

    1) Check command line arguments and existance of input files.
    2) Read Reference file, determine the data type, count the number
   	of points and store the maximum amplitude value.
    3) Read Data file, determine the data type, count the number
   	of points and store the maximum amplitude value.
   	4) Display Reference and Data files parameters.
   	5) Prompt for the Reference Scale Value if indicated on command line
      or use maximum amplitude ratio.
    6) Calculate the Signal and Error sums for each Data file point.
    7) Compute and display the Difference Measure in dB.

Execution:  diffmeasure [reference file] [outputted data file from benchmark] ([prompt])

Naming convention:

xdata = input files
vdata = golden files (not used as input or output)


***************************************************************************************/

#include "eembc_dt.h"
#include "verify.h"
#include <math.h>

/* Local Prototypes */
double my_fabs(double ref);
double my_log (double x);
double log_10 (double num);

#define E 2.7182818
#define LN_10 2.30258509

double my_fabs(double ref)
{
	if(ref < 0.0)	return -ref; 
	else			return ref; 
}

double my_log (double x)
{
  double negx;
	double w=0.0,y=0.0,z=0.0;
	unsigned num = 1,dec=0;
  
	if(x==1.0) return (0.0);  
	for(dec=0; (my_fabs(x))>=(double)E; ++dec) x/=E; 
	x -= 1.0;
  negx = 0.0 - x;
	z	=x;
	y	=x;
	w	=1.0;
	while((y != y + w) && (num < 10000)) y += (w = (z *= negx)/(num += 1));
  
	return(y + dec);
}

double log_10 (double num)
{
   return(my_log(num)/LN_10);
}

double diffmeasure (e_f64 *golden, int golden_size, DATA_TYPE RefType, e_s16 *calculated, int calculated_size, DATA_TYPE DataType)
{
	e_f64	RefReal,DataReal,RefImag,DataImag,RefPower,DataPower;
	e_f64	RefScaleFactor,SignalSum,ErrorSum,SignalValue,ErrorValue,DiffM;
    e_f64   RealDiff, ImagDiff;
	int		i;

	/* Clear two warnings */
	if(RefType != DataType)				return  -999.999; 
	if(golden_size != calculated_size ||
	   golden == NULL ||
	   calculated == NULL)				return  -999.999; 

	/* determine maximum Power in golden array */
	RefPower = 0.0;
	RefImag  = 0.0;
	for(i=0;i<golden_size;i++)
	{ 
		RefReal		= golden[i]; 
		if(RefType == COMPLEX)	RefImag	= golden[++i];
		else					RefImag	= 0.0; 
		/*RefPower	+= (RefReal * RefReal) + (RefImag * RefImag);*/
		RefPower	+= (RefReal + RefImag); 
	}
	/*RefPower	= RefPower / golden_size; */

	/* determine maximum Power in calculated array */
	DataPower		= 0.0;
	DataImag		= 0.0;
	for(i=0;i<golden_size;i++)
	{ 
		DataReal		= (e_f64)calculated[i]; 
		if(DataType == COMPLEX)	DataImag	= (e_f64)calculated[++i];
		else					DataImag	= 0.0; 
		/*DataPower += (DataReal * DataReal) + (DataImag * DataImag);*/
		DataPower	+= (DataReal + DataImag); 
	} 
	/*DataPower	= DataPower / golden_size; */

	if(!DataPower){
		th_exit(1,"Error. DataPower == 0\n");
	} 
	/* Set up RefScaleFactor */
	RefScaleFactor	= (RefPower / DataPower);
	SignalSum		= 0.0;
	ErrorSum		= 0.0;

	/* Compute the Sum of |Signal| and the Sum of |Error| */
	/* Process for the Number of Data Points */
	for (i = 0; i < golden_size; i++)
	{
		RefReal	 = golden[i];
		if(RefType == COMPLEX)	RefImag	= golden[i+1];
		else					RefImag	= 0.0; 
		DataReal = (e_f64)calculated[i];
		if(DataType == COMPLEX)	DataImag	= (e_f64)calculated[++i];
		else					DataImag	= 0.0; 

		/* Scale */ 
		DataReal	= DataReal * RefScaleFactor;
		DataImag	= DataImag * RefScaleFactor;

		RealDiff	= RefReal - DataReal;
		ImagDiff	= RefImag - DataImag;
	
		SignalValue = (DataReal * DataReal) + (DataImag * DataImag);
		SignalSum  += SignalValue;
		ErrorValue  = (RealDiff * RealDiff) + (ImagDiff * ImagDiff);
		ErrorSum   += ErrorValue;
	}

	th_printf("SignalSum %g, ErrorSum is %g\n",SignalSum,ErrorSum); 

	/* calculate difference measure */
	if (ErrorSum == 0.0)  	return 99999.99; 
	else
	{
		/*DiffM = 10.0*log_10(SignalSum/ErrorSum);*/
		DiffM = 10.0*log10(SignalSum/ErrorSum);
		return	DiffM; 
	}
}
