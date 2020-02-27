/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

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
