/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

/*******************************************************************************
    Includes                                                                    
*******************************************************************************/

#include "algo.h"
#include "therror.h"
#include <ctype.h> /* isprintf */

/*******************************************************************************
    Defines
*******************************************************************************/



int t_run_test( size_t iterations, int argc, const char *argv[] ) ; 
int test_main( struct TCDef **tcdef, int argc, const char *argv[] ) ; 

/* Define iterations */
#if !defined(ITERATIONS) || CRC_CHECK || ITERATIONS==DEFAULT
#undef ITERATIONS
#if CRC_CHECK
#define ITERATIONS 3000	/* required iterations for crc */
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

static TCDef the_tcdef = 
{
    "TEL viterb00   ",
    EEMBC_MEMBER_COMPANY, 
    EEMBC_PROCESSOR, 
    EEMBC_TARGET, 
    "Algorithm #6 -- Viterbi Decoder Bench Mark V1.0E0", 
    TCDEF_REVISION, 
    NULL,   /* Pointer to the next TCDef */
    /* TH Version Number Required */
    { EEMBC_TH_MAJOR, EEMBC_TH_MINOR, EEMBC_TH_STEP, EEMBC_TH_REVISION }, 
    /* Target Hardware Version Number Required( make all zeros to ignore )*/
    { 0, 0, 0, 0 }, 
    /* The Version number of this Benchmark */
    { 1, 0, 'E', 0 }, 
    ITERATIONS,
    &t_run_test, 
    &test_main, 
    NULL,   /* There is no main funciton in this implimentation */
    NULL    /* There is no entry function in this implimentation */
} ; 


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



/* Note: verification is treating the golden data as if unsigned */
/* encapsulated data */ 
#ifdef DATA_1 
#define OUTFILENAME "gettiOutput.dat"
static  e_s16 input_buf[] = {
#include "getti.dat"
};
static e_s16 test_buf[] = { 
#include "gett_golden.dat"
}; 
#elif defined(DATA_2)
#define OUTFILENAME "toggleiOutput.dat"
static  e_s16 input_buf[] = {
#include "togglei.dat"
};
static e_s16 test_buf[] = { 
#include "toggle_golden.dat"
}; 
#elif defined(DATA_3)
#define OUTFILENAME "onesiOutput.dat"
static  e_s16 input_buf[] = {
#include "onesi.dat"
};
static e_s16 test_buf[] = { 
#include "ones_golden.dat"
}; 
#else /* default DATA_4 */  
#define OUTFILENAME "zerosiOutput.dat"
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

/*
* FUNC   : t_run_test
* 
* DESC   : Called to run the test
* 
*          This function is called to start the test. It does not return
*          until after the test is completed( finished ). Note, th_finished()
*          and th_report_results()MUST be called before this function
*          returns if results are to be report. If these are not called
*          then no results will be reported for the test.
*          
* NOTE   : After this function returns, no other functions in the test
*          will be called. EG, returning from this function is equivelent
*          to returning from a main()or calling th_exit()
* 
* RETURNS : Success if the test ran fine. If th_finished() and
*          th_report_results() were not called, then the test finished
*          successfully, but there were no results and the host will
*          not be able to measure the test's duration.
*/

int t_run_test( size_t iterations, int argc, const char* argv[] )
{
    THTestResults   results ; 
    static char     info[64] ;

    e_s16           *DataBits ;
    e_s16           *BranchWords ; 
    n_int           DataByteSize ;
	const char		*outFilename;
    n_int           i;
	size_t          loop_cnt;
	e_s16			*golden_result; 
#if	!CRC_CHECK && !NON_INTRUSIVE_CRC_CHECK
    e_u8			*out_symbol_buffer; 
    e_s8			*stringHeadPtr; /* changed 2-14-00 arw picky compilers */
	n_char			*tmp_buf;
    n_int           TempVal;
#endif

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * First, initialize the data structures we need for the test
    */
	argv=argv;
	golden_result	= (e_s16 *)&test_buf; 
	outFilename		= OUTFILENAME;


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

	if (argc < 2)
	{
		th_printf( "WARNING: Missing output filename  Using: %s\n",outFilename);
	}

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    * This is the actual benchmark
    *---------------------------------------------------------------------------*/

   th_signal_start();  /* Tell the host that the test has begun */

   for ( loop_cnt = 0; loop_cnt < iterations; loop_cnt++ )  /* no stopping! */
   {
       ViterbiDecoderIS136(BranchWords, DataBits);
   }

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
   for( i=0; i<MAX_DATA_SIZE/16+1; i++ ){

#if	NON_INTRUSIVE_CRC_CHECK
	  results.CRC = Calc_crc16((e_u16)DataBits[i],results.CRC);
#endif
		if(DataBits[i] != golden_result[i]){
		th_printf(">> Failure: At (%d) Actual(%x)!=Golden(%x)\n",i,DataBits[i],golden_result[i]); 
		results.v1         = i;
		results.v2         = DataBits[i];
		results.v3         = golden_result[i];
		break;
		}
#if BMDEBUG
		else
		th_printf("Pass at (%d) Actual(%x)!=Golden(%x)\n",i,DataBits[i],golden_result[i]); 
#endif

	}

#if	!CRC_CHECK && !NON_INTRUSIVE_CRC_CHECK
   /* Calculate the size of the output buffer */ 

   TempVal   = 0;             /* reuse this variable as a counter */ 

   tmp_buf   = (n_char *)th_malloc(16); /* should acommodate largest single token */

   if( tmp_buf == NULL )

            th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );



   

    for( i=0; i<MAX_DATA_SIZE/16+1; i++ ){

       TempVal += th_sprintf( tmp_buf, "%04x ", DataBits[i]&0xffff);

    }

	

    for( i=0; i<MAX_DATA_SIZE/16+1; i++ ){

	   n_char c1 = (DataBits[i]&0xff00)>>8;

	   n_char c2 = (DataBits[i]&0xff);

	   TempVal += th_sprintf( tmp_buf,(c1 >= ' ' && c1 <= '~') ? "%c" : "<%02x>", c1 & 0x0ff);

	   TempVal += th_sprintf( tmp_buf,(c1 >= ' ' && c1 <= '~') ? "%c" : "<%02x>", c2 & 0x0ff);

    }

    TempVal += 2; 

   th_free(tmp_buf); 



    out_symbol_buffer  = (e_u8 *)th_malloc(TempVal+1);
	if( out_symbol_buffer == NULL )
            th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );

    stringHeadPtr = (e_s8 *)out_symbol_buffer; 
    for( i=0; i<MAX_DATA_SIZE/16+1; i++ ){
       stringHeadPtr += th_sprintf( (char *)stringHeadPtr, "%04x ", DataBits[i]&0xffff);
    }
	stringHeadPtr += th_sprintf( (char *)stringHeadPtr, "\n"); 

	/* Now print as ascii */
    for( i=0; i<MAX_DATA_SIZE/16+1; i++ ){
	   n_char c1 = (DataBits[i]&0xff00)>>8;
	   n_char c2 = (DataBits[i]&0xff);
	   stringHeadPtr += th_sprintf( (char *)stringHeadPtr, 
	    (isprint(c1)) ? "%c" : "<%02x>", c1 & 0x0ff);
	   stringHeadPtr += th_sprintf( (char *)stringHeadPtr, 
	    (isprint(c2)) ? "%c" : "<%02x>", c2 & 0x0ff);
    }
    stringHeadPtr += th_sprintf( (char *)stringHeadPtr, "\n");

    th_send_buf_as_file((const char *)out_symbol_buffer,TempVal,outFilename);
#endif

	   return th_report_results( &results, EXPECTED_CRC );
}

/*
* FUNC   : test_main
*
* DESC   : the test( or bench mark )main entry point
*
* RETURNS : Any error value defined in th_error.h
*/    

int
test_main( struct TCDef **tcdef, int argc, const char *argv[] )
{        
    /* Unused */
    argc = argc ;
    argv = argv ;
    
    /* Point the test harness at our test defintion struction */    
    *tcdef = &the_tcdef ; 

    /* Now do any other low level, or basic initialization here */    
    return Success ; 
}

