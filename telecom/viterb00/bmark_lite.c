/*==============================================================================
 *$RCSfile: bmark_lite.c,v $
 *
 *   DESC : This file contains the Main and other TH_Lite support functions
 *
 *  EEMBC : Telecom Subcommittee 
 *
 * AUTHOR : ARM Ltd., ECL, LLC
 *
 *    CVS : $Revision: 1.17 $
 *          $Date: 2002/08/09 21:47:01 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/telecom/viterb00/bmark_lite.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark_lite.c,v $
 * Revision 1.17  2002/08/09 21:47:01  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.16  2002/07/26 20:56:37  rick
 * Add harness.h for Application overrides
 *
 * Revision 1.15  2002/07/24 15:56:59  rick
 * Unique keys for all benchmarks, and generate tab delimited log files with column headers.
 *
 * Revision 1.14  2002/07/17 17:44:47  rick
 * Key outputdata files based on input filename
 *
 * Revision 1.13  2002/07/10 19:03:08  rick
 * Always initialize tcdef->CRC
 *
 * Revision 1.12  2002/07/10 15:52:34  rick
 * Bug #186: include ctype.h
 *
 * Revision 1.11  2002/05/29 22:26:50  rick
 * Set recommended iterations with make
 *
 * Revision 1.10  2002/05/22 17:55:28  rick
 * Replace assert.h with thassert.h, add assert functions to th lite.
 *
 * Revision 1.9  2002/05/13 20:26:03  rick
 * Fix missing shifts in 16, and 32 bit CRC
 *
 * Revision 1.8  2002/05/10 17:20:40  rick
 * Add al_main to API
 *
 * Revision 1.7  2002/05/03 15:30:21  rick
 * Add DATA_3, DATA_4 CRC values
 *
 * Revision 1.6  2002/04/25 23:20:30  rick
 * Cleanup after bug database scrub
 *
 * Revision 1.5  2002/04/25 23:14:19  rick
 * Add Viterbi CRC checks for data_1 and data_2
 *
 * Revision 1.4  2002/04/03 23:17:55  rick
 * Clear warnings from gcc
 *
 * Revision 1.3  2002/04/01 20:52:05  administrator
 * Apply Standard Comment Block
 *
 * Revision 1.2  2002/03/12 18:31:06  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE_CRC_CHECK, add standards headers
 *
 * Revision 1.1  2002/02/18 23:51:53  rick
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

#include "algo.h"
#include "thlib.h"
#include <ctype.h> /* isprintf */

/****************************************************************************/
/* Test Component Definition Structure                                      */
/****************************************************************************/
int t_run_test( TCDef *tcdef,int argc, const char *argv[] );

/* Define iterations */
#if !defined(ITERATIONS) || CRC_CHECK || ITERATIONS==DEFAULT
#undef ITERATIONS
#if CRC_CHECK
#define ITERATIONS 1000	/* required iterations for crc */
#else
#define ITERATIONS 3000	/* recommended iterations for benchmark */
#endif
#endif

/* Pre-caclculated CRC values */
#if	CRC_CHECK
#define EXPECTED_CRC	0x0000
#elif NON_INTRUSIVE_CRC_CHECK

#if   defined(DATA_1)
#define EXPECTED_CRC	0xfe1e
#elif defined(DATA_2)
#define EXPECTED_CRC	0xd48b
#elif defined(DATA_3)
#define EXPECTED_CRC	0x48bf
#elif defined(DATA_4)
#define EXPECTED_CRC	0x0000
#else
#error "DATA_x is not defined"
#endif

#else
#define EXPECTED_CRC	0x0000
#endif

TCDef the_tcdef = 
{
    "TEL viterb00   ",
    EEMBC_MEMBER_COMPANY, 
    EEMBC_PROCESSOR, 
    EEMBC_TARGET, 
    "Algorithm #6 -- Viterbi Decoder Bench Mark V1.0E0", 
    TCDEF_REVISION, 
    { EEMBC_TH_MAJOR, EEMBC_TH_MINOR, EEMBC_TH_STEP, EEMBC_TH_REVISION }, 
    { 0, 0, 0, 0 },   /* Target Hardware Version Number Required( make all zeros to ignore )*/
    { 1, 0, 'N', 0 }, /* The Version number of this Benchmark */
	ITERATIONS,
	0,
	0,
	0,
	0,
	0,
	0,
	0
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
#if defined(DATA_1)
static  e_s16 input_buf[] = {
#include "getti.dat"
};
static e_s16 test_buf[] = { 
#include "gett_golden.dat"
}; 
#elif defined(DATA_2)
static  e_s16 input_buf[] = {
#include "togglei.dat"
};
static e_s16 test_buf[] = { 
#include "toggle_golden.dat"
}; 
#elif defined(DATA_3)
static  e_s16 input_buf[] = {
#include "onesi.dat"
};
static e_s16 test_buf[] = { 
#include "ones_golden.dat"
}; 
#else /* default DATA_4 */  
static  e_s16 input_buf[] = {
#include "zerosi.dat"
};
static e_s16 test_buf[] = { 
#include "zeros_golden.dat"
}; 
#endif /* included data */ 

#define T_INPUT  (MAX_DATA_SIZE*sizeof(e_s16))
#define T_OUTPUT (1+(MAX_DATA_SIZE/16)*sizeof(e_s16))
#define	T_BSIZE	 (T_OUTPUT)

static n_char* g_pchBuf = NULL ; 

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

int t_run_test( TCDef *tcdef,int argc, const char *argv[] )
{    
    e_s16           *DataBits ;
    e_s16           *BranchWords ; 
    n_int           DataByteSize ;
    n_int           i;
	size_t          loop_cnt;
	e_s16			*golden_result; 

	argc	= argc;
	argv	= argv;
    tcdef->CRC = 0;
	golden_result		 = (e_s16 *)&test_buf; 

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * First, initialize the data structures we need for the test
   */

   /* When this is defined no file uploading necesary
    * we have all the data in the executable
	* so initialising is simplier
	*/ 

	g_pchBuf     = (n_char *) th_malloc( T_BSIZE );
    if( g_pchBuf == NULL )
       th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );

    BranchWords	 = (e_s16 *)&input_buf; 
    DataBits     = (e_s16 *)g_pchBuf;
	DataByteSize = MAX_DATA_SIZE;  


   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    * This is the actual benchmark
    *---------------------------------------------------------------------------*/

   th_signal_start();  /* Tell the host that the test has begun */

   for ( loop_cnt = 0; loop_cnt < tcdef->rec_iterations ; loop_cnt++ )  /* no stopping! */
   {
       ViterbiDecoderIS136(BranchWords, DataBits);
   }

    tcdef->duration		= th_signal_finished() ;
	tcdef->iterations	= tcdef->rec_iterations;

#if	NON_INTRUSIVE_CRC_CHECK
	tcdef->CRC = 0;
#elif	CRC_CHECK
	tcdef->CRC=0;
#else
	tcdef->CRC=0;
#endif


	/* Verification */
   for( i=0; i<MAX_DATA_SIZE/16+1; i++ ){

#if	NON_INTRUSIVE_CRC_CHECK
	  tcdef->CRC = Calc_crc16((e_u16)DataBits[i],tcdef->CRC);
#endif
		if(DataBits[i] != golden_result[i]){
		th_printf(">> Failure: At (%d) Actual(%x)!=Golden(%x)\n",i,DataBits[i],golden_result[i]); 
		tcdef->v1         = i;
		tcdef->v2         = DataBits[i];
		tcdef->v3         = golden_result[i];
		break;
		}
#if BMDEBUG
		else
		th_printf("Pass at (%d) Actual(%x)!=Golden(%x)\n",i,DataBits[i],golden_result[i]); 
#endif

	}

   return	th_report_results(tcdef,EXPECTED_CRC);

} 

/*------------------------------------------------------------------------------
 * FUNC   : test_main
 *
 * DESC   : the test (or bench mark) main entry point
 *
 * RETURNS: Any error value defined in th_error.h
 * ---------------------------------------------------------------------------*/

int main(int argc, const char* argv[] )
{
	/* target specific inititialization */
	al_main(argc, argv);
	/* Benchmark Execution */
	return	t_run_test(&the_tcdef,argc,argv); 
} 
