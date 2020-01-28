/*==============================================================================
 *$RCSfile: bmark.c,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : RP
 *
 *  EEMBC : Telecom Subcommittee 
 *
 *    CVS : $Revision: 1.16 $
 *          $Date: 2002/08/09 21:46:34 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/telecom/autcor00/bmark.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark.c,v $
 * Revision 1.16  2002/08/09 21:46:34  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.15  2002/07/24 15:56:46  rick
 * Unique keys for all benchmarks, and generate tab delimited log files with column headers.
 *
 * Revision 1.14  2002/07/17 17:44:28  rick
 * Key outputdata files based on input filename
 *
 * Revision 1.13  2002/05/29 22:26:43  rick
 * Set recommended iterations with make
 *
 * Revision 1.12  2002/05/23 20:22:23  rick
 * Clear ansi warnings
 *
 * Revision 1.11  2002/05/22 22:07:19  rick
 * Float support fixes
 *
 * Revision 1.10  2002/05/13 20:26:03  rick
 * Fix missing shifts in 16, and 32 bit CRC
 *
 * Revision 1.9  2002/04/25 19:54:22  rick
 * sprintf to th_sprintf
 *
 * Revision 1.8  2002/04/23 14:45:07  rick
 * Bug 51: ifdef BMDEBUG always true
 *
 * Revision 1.7  2002/04/19 23:17:37  rick
 * Only include verify.h if VERIFY_FLOAT && FLOAT_SUPPORT
 *
 * Revision 1.6  2002/04/01 20:51:22  administrator
 * Apply Standard Comment Block
 *
 * Revision 1.5  2002/03/23 00:51:47  rick
 * Visual C++ Build fixes
 *
 * Revision 1.4  2002/03/11 22:11:50  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
 *
 * Revision 1.3  2002/02/22 20:46:11  rick
 * Fix d_union conflict in verify.h, thlib.c
 *
 * Revision 1.2  2002/02/18 23:51:52  rick
 * Completed Telocom TH_Lite conversion
 *
 *
 *   5/26/99    rlr
 *       Initial cleanup
 *
 *   1/20/00    arw & sl
 *       Correction of minor Sev 3 defects, cleanup
 *       Change datafile naming semantics to eliminate underscores
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

#if		VERIFY_FLOAT && FLOAT_SUPPORT
#include "verify.h"		/* diffmeasure */
#endif

#include <stdlib.h> /* atoi */

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
#define EXPECTED_CRC	0x0000
#elif NON_INTRUSIVE_CRC_CHECK

#if defined(DATA_1)
#define EXPECTED_CRC			0x5943
#elif defined(DATA_2)
#define EXPECTED_CRC			0x9e45
#else
#define EXPECTED_CRC			0x981b
#endif

#else
#define EXPECTED_CRC	0x0000
#endif

static TCDef the_tcdef = 
   {
    "TEL autcor00   ",
   EEMBC_MEMBER_COMPANY,
   EEMBC_PROCESSOR,
   EEMBC_TARGET,
   "Autocorrelation Bench Mark V1.0E0",
   
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
   
   NULL,        /* there is no main function in this implimentation */
   NULL         /* there is no entry function in this implimentation */
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


/* encapsulated data */ 
#if	defined(DATA_1)
#define MAX_DATA_SIZE 16  /* this is the actual file size */ 
#define OUTFILENAME "xpulseiOutput.dat"
static  e_s16 input_buf[] = {
#include "xpulsei.dat"
};
static e_f64 test_buf[] = { 
#include "vpulseai.dat"
}; 
#define NUMBER_OF_LAGS	8

#elif defined(DATA_2)

#define MAX_DATA_SIZE 1024  /* this is the actual file size */ 
#define OUTFILENAME "xsineiOutput.dat"
static  e_s16 input_buf[] = {
#include "xsinei.dat"
};
static e_f64 test_buf[] = { 
#include "vsineai.dat"
};
#define NUMBER_OF_LAGS	16

#else /* default DATA_3 */  

#define MAX_DATA_SIZE 500  /* this is the actual file size */ 
#define OUTFILENAME "xspeechiOutput.dat"
static  e_s16 input_buf[] = {
#include "xspeechi.dat"
};
static e_f64 test_buf[] = { 
#include "vspeechai.dat"
};
#define NUMBER_OF_LAGS	32
#endif /* included data */ 

#define T_BSIZE   (MAX_DATA_SIZE*sizeof(e_s16)) /* for results only */ 

static n_char* t_buf = NULL ;

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
 * ---------------------------------------------------------------------------*/

int t_run_test( size_t iterations, int argc, const char* argv[] )

   {
	size_t			loop_cnt;
	THTestResults	results;
	static n_char	info[64]; /* gotta be static */

#if	VERIFY_FLOAT && FLOAT_SUPPORT
	e_f64			*golden_result; 
	d_union			dunion;
#endif

   /* this should accomodate a short + 2 symbols (\n) */ 
	const char		*outFilename;
	e_s16			*InputData,*AutoCorrData;
	e_s16			DataSize,NumberOfLags,Scale,TempVal;

#if	!CRC_CHECK && !NON_INTRUSIVE_CRC_CHECK
	e_s16			i;   
	e_u8			*out_symbol_buffer;
	e_u8			*stringHeadPtr;
	n_char			*tmp_buf;
#endif

	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    * First, initialize the data structures we need for the test
   */
	outFilename = OUTFILENAME;

   t_buf     = (n_char *) th_malloc( T_BSIZE );
   if( t_buf == NULL )
       th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );

#if	VERIFY_FLOAT && FLOAT_SUPPORT
   	golden_result= (e_f64 *)&test_buf; 
#endif
   /* When this is defined no file uploading necesary
    * we have all the data in the executable
	* so initializing is simplier
	*/ 
    InputData	 = (e_s16 *)&input_buf; 
    AutoCorrData = (e_s16 *)t_buf;
	DataSize     = MAX_DATA_SIZE;  

	if (argc < 2)  
	{
		th_printf( "WARNING: Missing output filename  Using: %s\n",outFilename);
		NumberOfLags = NUMBER_OF_LAGS;
        th_printf( "WARNING: Cannot determine lags  Using: %d\n",NumberOfLags);
	} else {
    if ((argc <3) || ((NumberOfLags = atoi(argv[2])) == 0))
	{
	    outFilename = argv[1];
		NumberOfLags = NUMBER_OF_LAGS;
        th_printf( "WARNING: Cannot determine lags  Using: %d\n",NumberOfLags);
	}}
     
   
     /* Compute partial product scale factor based on size of data 
      * Scale = (e_s16) ceil(log10(DataSize)/log10(2.0));
      */
     TempVal = 1;
     Scale = 0;
     while(TempVal < DataSize)
       {
	 Scale++;
	 TempVal = TempVal << 1;
       }

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    * This is the actual benchmark
   */
   th_signal_start();  /* Tell the host that the test has begun */

   for ( loop_cnt = 0; loop_cnt < iterations; loop_cnt++ )  /* no stopping! */
      {
   	fxpAutoCorrelation(InputData,AutoCorrData,DataSize,NumberOfLags,
	                   Scale
			   );
/* Bug 51 always true */
#if BMDEBUG
		if ( !th_harness_poll() )	break;
#endif
      }

   results.duration   = th_signal_finished();  /* signal that we are finished */
   
   results.iterations = iterations;
#if		VERIFY_FLOAT && FLOAT_SUPPORT
   dunion.d          = diffmeasure (golden_result, NumberOfLags, COMPLEX, AutoCorrData, NumberOfLags, COMPLEX);
   results.v1         = dunion.v[0];
   results.v2         = dunion.v[1];
#else
   results.v1         = 0;
   results.v2         = 0;
#endif
   results.v3         = 0;
   results.v4         = 0;
   results.info       = info;
   
   th_sprintf( info, "A note of basic info" );

#if		NON_INTRUSIVE_CRC_CHECK
	results.CRC = 0;
	for ( loop_cnt = 0; loop_cnt < (size_t) NumberOfLags;loop_cnt++)
		results.CRC = Calc_crc16((e_u16) AutoCorrData[loop_cnt],results.CRC);
#elif	CRC_CHECK
	results.CRC=0;
#else
	results.CRC=0;
   
   /* Calculate the size of the output buffer */ 
   TempVal   = 0;             /* reuse this variable as a counter */ 
   tmp_buf   = (n_char *)th_malloc(16); /* should acommodate largest single token */
   if( tmp_buf == NULL )
            th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );

   for( i=0; i<NumberOfLags; i++ ){
       TempVal += th_sprintf( tmp_buf, " %d\n", AutoCorrData[i]);
   }
   th_free(tmp_buf); 

   /* Uploading is different as well,
    * Since we do not have input buffer, we need to 
	* use one of our own 
    */ 
    out_symbol_buffer  = (e_u8 *)th_malloc(TempVal+1);
	if( out_symbol_buffer == NULL )
            th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );

    stringHeadPtr = out_symbol_buffer; 
    for( i=0; i<NumberOfLags; i++ ){
       stringHeadPtr += th_sprintf((char *) stringHeadPtr, " %d\n", AutoCorrData[i]);
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

int test_main( struct TCDef** tcdef, int argc, const char* argv[] )

{
   argc=argc;
   argv=argv;
   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -    
    *                  >>> GOTTA DO THIS FIRST <<<
    * Point the test harness at our test defintion struction
   */
   *tcdef = &the_tcdef;
   
   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    * Now do any other low level, or basic initialization here   
   */   
   return Success;
}
