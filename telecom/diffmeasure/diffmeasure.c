/*==============================================================================
 *$RCSfile: diffmeasure.c,v $
 *
 *   DESC : Measurement of Signal to Noise Difference in DB
 *
 * AUTHOR : BP
 *
 *  EEMBC : Telecom Subcommittee 
 *
 *    CVS : $Revision: 1.7 $
 *          $Date: 2002/09/07 17:26:10 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/telecom/diffmeasure/diffmeasure.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 *
 *
 * $Log: diffmeasure.c,v $
 * Revision 1.7  2002/09/07 17:26:10  rick
 * Add TCDef stub for th lite build
 *
 * Revision 1.6  2002/09/07 16:58:41  rick
 * Add system headers for FILE, calloc, and exit
 *
 * Revision 1.5  2002/08/09 21:46:45  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.4  2002/05/10 13:10:00  Rob Whitton
 * Complete rehash to make it numerically correct. Also much simpler and shorter.
 * Changes include: Now computes SNR rather than NSR; Computation is now done
 * based on the power. Lots of extra error checking for user errors - still
 * not very robust but better; Normalisation between the two inputs was
 * previously done based on maximum amplitudes this has been replaced with an
 * average power algorithm.
 *
 *
 * Revision 1.3  2002/04/08 22:26:04  rick
 * Update Depgen for vc++ options
 *
 * Revision 1.2  2002/04/01 20:51:35  administrator
 * Apply Standard Comment Block
 *
 * Revision 1.3  2002/03/11 22:11:50  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
 *
 * Revision 1.2  2002/02/18 23:51:49  rick
 * Completed Telocom TH_Lite conversion
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

/*******************************************************************
*

This program computes the signal to noise ratio. According to:

SNR = 10 log10 (ErrorPower / SignalPower).

Execution:  diffmeasure [reference file] [outputted data file from benchmark] ([prompt])

Naming convention:

xdata = input files
vdata = golden files (not used as input or output)


***************************************************************************************/

#include "verify.h"
#include <stdio.h>  /* FILE definition */
#include <stdlib.h> /* calloc, exit definitions */

double diffmeasure (e_f64 *golden, int golden_size, DATA_TYPE RefType, e_s16 *calculated, int calculated_size, DATA_TYPE DataType); 

int main (int argc, char *argv[])
{
    double    RefReal,RefImag,DataReal,DataImag,RefPower,DataPower;
    double    RefScaleFactor,ErrorSum;
    int       RefNumPoints,DataNumPoints,i,j;
    char      InString[256];
    FILE     *RefFile, *DataFile;
    DATA_TYPE Type,RefType,DataType;
	double		*golden_file; 
	short		*data_file; 

   /* Check arguments */
   
	if (!((argc == 3) || (argc == 4))){
   		printf("ERROR: Incorrect arguments\n");
		printf("  Usage: diffmeasure reffile datafile [prompt]\n");
		printf("     Exiting...");
		return 1;
	}
	if ((RefFile = fopen(argv[1],"r")) == NULL){
   		printf("ERROR: Cannot open %s\n  Exiting...\n",argv[1]);
		return 1;
	}
	if ((DataFile = fopen(argv[2],"r")) == NULL){
   		printf("ERROR: Cannot open %s\n  Exiting...\n",argv[2]);
		return 1;
	}

	/* Determine Reference File Data Type (Real or Complex) */
   
	RefPower = 0.0;
	RefImag  = 0.0;
   
	fgets(InString,sizeof(InString) - 1,RefFile);
	RefType = (DATA_TYPE) sscanf(InString, " %lf %lf", &RefReal, &RefImag);
	if (RefType == BAD_F){
      printf("ERROR: No reference data.\n");
      return 1;
	}

	RefPower += (RefReal * RefReal) + (RefImag * RefImag);

	/* Count Number of Points in the Reference File and keep track of the
   	Maximum Amplitude */
	RefNumPoints = 1;
	while (fgets(InString,255,RefFile) != NULL){
		Type = (DATA_TYPE) sscanf(InString, " %lf %lf", &RefReal, &RefImag);
		if (Type == BAD_F)		break;
		if (Type != RefType)	printf("ERROR: Mixed real and complex in the reference file.\n");

		RefPower += (RefReal * RefReal) + (RefImag * RefImag);
   		RefNumPoints++;
	}

	/* Display Reference File Summary */
	printf("Reference File: %s\n",argv[1]);
	if (RefType == REAL)	printf("   Contains %d  REAL elements\n",RefNumPoints);
	else			   		printf("   Contains %d  COMPLEX elements\n",RefNumPoints);
	printf("   Average reference power = %lf\n\n", RefPower / RefNumPoints);

	if (RefType == COMPLEX)	golden_file = (double *)calloc(RefNumPoints*2,sizeof(double)); 
	else					golden_file = (double *)calloc(RefNumPoints,sizeof(double)); 
	fclose(RefFile);

	if(!golden_file)	exit(1); 

	/* Determine Data File Data Type (Real or Complex) */
	DataPower = 0.0;
	DataImag  = 0.0;

	fgets(InString,255,DataFile);

	DataType = (DATA_TYPE) sscanf(InString, " %lf %lf", &DataReal, &DataImag);
	if (DataType == BAD_F){
		printf("ERROR: No data.\n");
		return 1;
	}

	DataPower += (DataReal * DataReal) + (DataImag * DataImag);

	/* Count Number of Points in the Data File and keep track of the
   	Maximum Amplitude */
	DataNumPoints = 1;
	while (fgets(InString,255,DataFile) != NULL){
		Type = (DATA_TYPE) sscanf(InString, " %lf %lf", &DataReal, &DataImag);
		if (Type == BAD_F)		break;
		if (Type != DataType)	printf("ERROR: Mixed real and complex in the data file.\n");

		DataPower += (DataReal * DataReal) + (DataImag * DataImag);
   		DataNumPoints++;
	}

	/* Display Data File Summary */
	printf("Data File: %s\n",argv[2]);
	if (DataType == REAL)	printf("   Contains %d  REAL elements\n",DataNumPoints);
	else		   			printf("   Contains %d  COMPLEX elements\n",DataNumPoints);
   
	printf("   Average data power = %lf\n\n", DataPower / DataNumPoints);

	if (DataType != RefType){
		printf("ERROR: Unable to compare real with complex.\n");
		return 1;
	}

	if (DataNumPoints != RefNumPoints){
		printf("ERROR: Unable to compare sequences of different lengths.\n");
		return 1;
	}

	if (DataType == COMPLEX)	data_file = (short *)calloc(RefNumPoints*2,sizeof(short)); 
	else						data_file = (short *)calloc(RefNumPoints,sizeof(short)); 
	fclose(DataFile);

	if(!data_file)	exit(2); 

	if (DataPower == 0){
		printf("ERROR: No data power.\n");
		return 1;
	}

	/* Set up RefScaleFactor */
	printf("Maximum Amplitude Ratio %g\n",RefPower / DataPower);
	if (argc == 4) {
   		/* Prompt for Reference Scale Factor */
   		printf("Enter Reference Scale Factor (RefPower /  DataPower): ");
   		scanf("%lf",&RefScaleFactor);
   		printf("\n\n");
	}
	else {
      if (DataPower == 0){
         printf("ERROR: No data power.\n");
         return 1;
      }
   		RefScaleFactor = (RefPower / DataPower);
	}

	/* Open files and initialize variables */
	RefFile		= fopen(argv[1],"r");
	DataFile	= fopen(argv[2],"r");
   
	ErrorSum = 0.0;

	/* Compute the error power and the signal power */
	/* Process for the Number of Data Points */
	j	= 0; 
	for (i = 0; i < DataNumPoints; i++) {
		if (DataType == COMPLEX){
			fgets(InString,255,RefFile);
			sscanf(InString, " %lf %lf", &golden_file[j], &golden_file[j+1]);

			fgets(InString,255,DataFile);
			sscanf(InString, " %d %d", &data_file[j], &data_file[j+1]);
			j+=2; 
		}
		else{
			fgets(InString,255,RefFile);
			sscanf(InString, " %lf", &golden_file[i]);

			fgets(InString,255,DataFile);
			sscanf(InString, " %d", &data_file[i]);
		} 
	}

	if (DataType == COMPLEX){
		printf("\nDifference Measure (S/N) = %g (dB)\n",
			diffmeasure(golden_file,DataNumPoints,COMPLEX,data_file,DataNumPoints,COMPLEX)); 
	} 
	else{
		printf("\nDifference Measure (S/N) = %g (dB)\n",
			diffmeasure(golden_file,DataNumPoints,REAL,data_file,DataNumPoints,REAL)); 
	} 

   return 0;
}

/* 
 * Stub routine for linking with th regular (thlib.o) 
 * Stub TCDef (global) for linking with th lite (thal.o)
 */
TCDef	the_tcdef;
int		test_main( struct TCDef** tcdef, int argc, const char* argv[] );
int		test_main( struct TCDef** tcdef, int argc, const char* argv[] )
{
/*
 * This should NEVER be called from this environment.
 */

   return Failure;
}
