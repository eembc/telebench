/*==============================================================================
 *$RCSfile: bmark.c,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : RP
 *
 *  EEMBC : Telecom Subcommittee 
 *
 *    CVS : $Revision: 1.14 $
 *          $Date: 2002/09/23 15:30:50 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/telecom/conven00/bmark.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark.c,v $
 * Revision 1.14  2002/09/23 15:30:50  rick
 * Remove incomplete INTERMED define
 *
 * Revision 1.13  2002/08/09 21:46:37  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.12  2002/07/24 15:56:48  rick
 * Unique keys for all benchmarks, and generate tab delimited log files with column headers.
 *
 * Revision 1.11  2002/07/17 17:44:29  rick
 * Key outputdata files based on input filename
 *
 * Revision 1.10  2002/05/29 22:26:45  rick
 * Set recommended iterations with make
 *
 * Revision 1.9  2002/05/23 20:22:34  rick
 * Clear ansi warnings
 *
 * Revision 1.8  2002/05/13 20:26:03  rick
 * Fix missing shifts in 16, and 32 bit CRC
 *
 * Revision 1.7  2002/04/26 19:22:50  rick
 * Add crc for DATA 1,2. Add BMDEBUG printing.
 *
 * Revision 1.6  2002/04/23 22:21:26  rick
 * Bug #129: Spelling errors
 *
 * Revision 1.5  2002/04/01 20:51:29  administrator
 * Apply Standard Comment Block
 *
 * Revision 1.4  2002/03/23 00:51:47  rick
 * Visual C++ Build fixes
 *
 * Revision 1.3  2002/03/11 22:11:51  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
 *
 * Revision 1.2  2002/02/23 22:20:03  rick
 * patrick fixes
 *
 * Revision 1.1  2002/02/19 00:44:26  rick
 * Add/Remove files from build test
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

#include "algo.h"
#include "therror.h"
#include <stdlib.h>

/*------------------------------------------------------------------------------
 * Test Component Definition Structure
 */

int    t_run_test( size_t iterations, int argc, const char* argv[] );
int    test_main( struct TCDef** tcdef, int argc, const char* argv[] );

/* Define iterations */
#if !defined(ITERATIONS) || CRC_CHECK || ITERATIONS==DEFAULT
#undef ITERATIONS
#if CRC_CHECK
#define ITERATIONS 5000	/* required iterations for crc */
#else
#define ITERATIONS 5000	/* recommended iterations for benchmark */
#endif
#endif

#if CRC_CHECK
#define EXPECTED_CRC     0x0000
#elif NON_INTRUSIVE_CRC_CHECK

#if defined(DATA_1)
#define EXPECTED_CRC		0xf210
#elif defined(DATA_2)
#define EXPECTED_CRC		0x183d
#else
#define EXPECTED_CRC		0x5697
#endif

#else
#define EXPECTED_CRC	0x0000
#endif

static TCDef the_tcdef = 
   {
    "TEL conven00   ",
   EEMBC_MEMBER_COMPANY,
   EEMBC_PROCESSOR,
   EEMBC_TARGET,
   "Convolutional Encoder Bench Mark V1.0E0",
   TCDEF_REVISION,       
   NULL, /* pointer to the next TCDef */
   /* TH Version Number Required */
   { EEMBC_TH_MAJOR, EEMBC_TH_MINOR, EEMBC_TH_STEP, EEMBC_TH_REVISION },  
   /* Target Hardware Version Number Required (make all zeros to ignore)*/
   { 0, 0, 0, 0 },  
   /* The Version number of this Benchmark */
   { 1, 0, 'E', 1 },  
   ITERATIONS,
   &t_run_test, 
   &test_main,
   NULL,        /* there is no main function in this implementation */
   NULL         /* there is no entry function in this implementation */
   };

/*------------------------------------------------------------------------------
 * Local Data
*/

/* >> IMPORTANT NOTE << 
 *
 * Since benchmarks can be entered (run) multiple times, the benchmark
 * MUST NOT depend on global data being initialized.  E.g. it must
 * complelty initialize itself EVERY TIME its t_run_test() function
 * is called.
 *
*/

static n_char* t_buf = NULL;

/* encapsulated data */ 
#if defined(DATA_1)
#define MAX_DATA_SIZE_BYTES 512  /* this is the actual file size */ 
#define OUTFILENAME "xk5r2diOutput.dat"
static  e_u8 input_buf[] = {
#include "xk5r2di.dat"
};
static e_u8 test_buf[] = { 
#include "vk5r2bwi.dat"
}; 
#define		CODE_INDEX	3
#elif defined(DATA_2)

#define MAX_DATA_SIZE_BYTES 512  /* this is the actual file size */ 
#define OUTFILENAME "xk4r2diOutput.dat"
static  e_u8 input_buf[] = {
#include "xk4r2di.dat"
};
static e_u8 test_buf[] = { 
#include "vk4r2bwi.dat"
}; 
#define		CODE_INDEX	2
#else /* default DATA_3 */  

#define MAX_DATA_SIZE_BYTES 512  /* this is the actual file size */ 
#define OUTFILENAME "xk3r2diOutput.dat"
static  e_u8 input_buf[] = {
#include "xk3r2di.dat"
};
static e_u8 test_buf[] = { 
#include "vk3r2bwi.dat"
}; 
#define		CODE_INDEX	1
#endif /* included data */

#define T_BSIZE ((MAX_DATA_SIZE_BYTES*2)+(2*(MAX_CODE_VECTORS*MAX_CONSTRAINT_LENGTH)))

/*------------------------------------------------------------------------------
 * FUNC   : t_run_test
 *
 * DESC   : called to run the test
 *
 *          This function is called to start the test.  It does not return
 *          until after the test is completed (finished).  Note, th_finished()
 *          and th_report_results() MUST be called before this function
 *          returns if results are to be report.  If these are not called
 *          then no results will be reported for the test.
 *
 * NOTE   : after this function returns, no other functions in the test
 *          will be called.  EG, returning from this function is equivelent
 *          to returning from a main() or calling th_exit()
 *
 * RETURNS: Success if the test ran fine.  If th_finished() and
 *          th_report_results() were not called, then the test finished
 *          successfully, but there were no results and the host will
 *          not be able to measure the test's duration.
 *-------------------------------------------------------------------------------*/

int t_run_test( size_t iterations, int argc, const char* argv[] )

  {
   size_t         loop_cnt;
   THTestResults   results;
   static char     info[64]; /* gotta be static */

	e_u8			*golden_result;

	e_u8          *DataBits,*BranchWords;
	e_u8         (*CodeMatrix)[MAX_CODE_VECTORS];
	e_s16        i,DataByteSize,CodeIndex,NumberCodeVectors,ConstraintLength;

	const char		*outFilename;
#if		!CRC_CHECK && !NON_INTRUSIVE_CRC_CHECK
	e_s8		*out_symbol_buffer; 
	e_s8        *stringHeadPtr;  /* changed for compatibility arw 2-14-00 */
	n_char		*tmp_buf;
	e_s16		TempVal;
#endif

   /* Rate 1/2, Constraint Length 3, Free Distance 5  Convolutional Code */
   e_u8 CM_ONE[3][2] = {{1,1},
			  {1,0},
			  {1,1}};

   /* Rate 1/2, Constraint Length 4, Free Distance 6  Convolutional Code */
   e_u8 CM_TWO[4][2] = {{1,1},
			  {1,0},
			  {1,1},
			  {1,1}};

   /* Rate 1/2, Constraint Length 5, Free Distance 7  Convolutional Code */
   e_u8 CM_THREE[5][2] = {{1,1},
			    {0,1},
			    {1,0},
			    {1,0},
			    {1,1}};


   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    * First, initialize the data structures we need for the test
   */
	outFilename = OUTFILENAME;
	NumberCodeVectors = 0;
	ConstraintLength = 0;

   	golden_result = (e_u8 *)&test_buf;

   t_buf = th_malloc( T_BSIZE );
   if ( t_buf == NULL )
      {
      th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );
      }

	/* When this is defined no file uploading necesary
	 * we have all the data in the executable
	 * so initialising is simplier
	 */ 
    DataBits     = (e_u8 *)&input_buf; 
    BranchWords  = (e_u8 *)t_buf;
    CodeMatrix   = (e_u8 (*)[2])(BranchWords+(MAX_DATA_SIZE_BYTES));
    DataByteSize =  MAX_DATA_SIZE_BYTES;

    if (argc < 2)
	{
		th_printf( "WARNING: Missing output filename  Using: %s\n",outFilename);
		CodeIndex = CODE_INDEX;
        th_printf( "WARNING: Cannot determine Code Index  Using: %d\n",CodeIndex);
	} else {
    if ((argc <3) || ((CodeIndex = atoi(argv[2])) == 0))
	{
	    outFilename = argv[1];
		CodeIndex = CODE_INDEX;
        th_printf( "WARNING: Cannot determine Code Index  Using: %d\n",CodeIndex);
	}}

   switch (CodeIndex) 
     {
   case 1 : CodeMatrix = CM_ONE;
     NumberCodeVectors = 2;
     ConstraintLength = 3;
     break;
   case 2 : CodeMatrix = CM_TWO;
     NumberCodeVectors = 2;
     ConstraintLength = 4;
     break;
   case 3 : CodeMatrix = CM_THREE;
     NumberCodeVectors = 2;
     ConstraintLength = 5;
     break;
   }


   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    * This is the actual benchmark
    *---------------------------------------------------------------------------*/

   th_signal_start();  /* Tell the host that the test has begun */

   for ( loop_cnt = 0; loop_cnt < iterations; loop_cnt++ )  /* no stopping! */
     {
       convolutionalEncode(DataBits, DataByteSize, NumberCodeVectors,
			   ConstraintLength, CodeMatrix,
			   BranchWords
			   );
     } /* end for */

   results.duration   = th_signal_finished();  /* signal that we are finished */
   results.iterations = iterations;
   results.v1         = 0;
   results.v2         = 0;
   results.v3         = 0;
   results.v4         = 0;
   results.info       = info;

   th_sprintf( info, "A note of basic info" );

#if	NON_INTRUSIVE_CRC_CHECK
	results.CRC = 0;
#elif	CRC_CHECK
	results.CRC=0;
#else
	results.CRC=0;
#endif
		/* Verification */ 
    for( i=0; i<NumberCodeVectors*DataByteSize; i++ ){
#if	NON_INTRUSIVE_CRC_CHECK
	  results.CRC = Calc_crc8(BranchWords[i],results.CRC);
#endif
      if(BranchWords[i] != golden_result[i])
	  {
        th_printf("%x: Failed at[%d] calculated(%d) != golden(%d)\n",results.CRC,i,BranchWords[i],golden_result[i]);
		results.v1         = i;
		results.v2         = BranchWords[i];
		results.v3         = golden_result[i];
		break;
	  } 
#if	BMDEBUG
	  else
        th_printf("%x: Passed at[%d] calculated(%d)  = golden(%d)\n",results.CRC,i,BranchWords[i],golden_result[i]);
#endif
	}

#if		!CRC_CHECK && !NON_INTRUSIVE_CRC_CHECK
   /* Calculate the size of the output buffer */ 
   TempVal   = 0;             /* reuse this variable as a counter */ 
   tmp_buf   = (n_char *)th_malloc(16); /* should acommodate largest single token */
   if( tmp_buf == NULL )
            th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );

   for( i=0; i<NumberCodeVectors*DataByteSize; i++ ){
       TempVal += th_sprintf( tmp_buf, " %d\n", BranchWords[i]);
   }

   th_free(tmp_buf); 

   /* Uploading is different as well,
    * Since we do not have input buffer, we need to 
	* use one of our own 
    */ 

    out_symbol_buffer  = (e_s8 *)th_malloc(TempVal+1);
	if( out_symbol_buffer == NULL )
            th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );

    stringHeadPtr = out_symbol_buffer; 
    for( i=0; i<NumberCodeVectors*DataByteSize; i++ ){
       stringHeadPtr += th_sprintf((char *) stringHeadPtr, " %d\n", BranchWords[i]);
    }
    th_send_buf_as_file((char *)out_symbol_buffer,TempVal,outFilename);

#endif

		return th_report_results( &results, EXPECTED_CRC );
 }

/*------------------------------------------------------------------------------
 * FUNC   : test_main
 *
 * DESC   : the test (or bench mark) main entry point
 *
 * RETURNS: Any error value defined in th_error.h
 * ---------------------------------------------------------------------------*/

int test_main( struct TCDef** tcdef, int argc, const char* argv[])
{
	argc=argc;
	argv=argv;
   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -    
    *                  >>> GOTTA DO THIS FIRST <<<
    * Point the test harness at our test definition structure
   */
   *tcdef = &the_tcdef;

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    * Now do any other low level, or basic initialization here
   */   
   return Success;
   }
