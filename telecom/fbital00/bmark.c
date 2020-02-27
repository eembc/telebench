/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#include "algo.h"

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
#if defined(DATA_2)
#define EXPECTED_CRC	0x07e5
#elif defined(DATA_3)
#define EXPECTED_CRC	0x6da8
#elif defined(DATA_6)
#define EXPECTED_CRC	0x3a19
#else
#error "DATA_x required but not defined"
#endif
#else
#define EXPECTED_CRC	0x0000
#endif

static TCDef the_tcdef =
   {
   "TEL fbital00    ", 
   EEMBC_MEMBER_COMPANY,
   EEMBC_PROCESSOR,
   EEMBC_TARGET,
   "Bit Allocation Bench Mark V1.0E0",
   
   TCDEF_REVISION,       
   
   NULL, /* pointer to the next TCDef */

   /* TH Version Number Required */
   { EEMBC_TH_MAJOR, EEMBC_TH_MINOR, EEMBC_TH_STEP, EEMBC_TH_REVISION },  

   /* Target Hardware Version Number Required (make all zeros to ignore)*/
   { 0, 0, 0, 0 },  

   /* The Version number of this Benchmark */
   { 1, 0, 'E', 1 },  

   ITERATIONS,    /* recomended iterations */

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
#if defined(DATA_1)
#define MAX_CARRIERS		256  /* this is the actual file size */ 
#define	BITSPERDMTSYMBOL	1920
#define OUTFILENAME "vtypbaiOut.dat"
static  e_s16 input_buf[] = {
#include "vtypbai.dat"
};
static e_s16 test_buf[] = { 
#include "vtypbai.dat"
}; 
#elif defined(DATA_2)
#define MAX_CARRIERS		256  /* this is the actual file size */ 
#define	BITSPERDMTSYMBOL	1920
#define OUTFILENAME "xtypsnriOut.dat"
static  e_s16 input_buf[] = {
#include "xtypsnri.dat"
};
static e_s16 test_buf[] = { 
#include "vtypbai.dat"
}; 
#elif defined(DATA_3)
#define MAX_CARRIERS		20  /* this is the actual file size */ 
#define	BITSPERDMTSYMBOL	120
#define OUTFILENAME "xstepsnriOut.dat"
static  e_s16 input_buf[] = {
#include "xstepsnri.dat"
};
static e_s16 test_buf[] = { 
#include "vstepbai.dat"
}; 
#elif defined(DATA_4)
#define MAX_CARRIERS		20  /* this is the actual file size */ 
#define	BITSPERDMTSYMBOL	120
#define OUTFILENAME "vstepbaiOut.dat"
static  e_s16 input_buf[] = {
#include "vstepbai.dat"
};
static e_s16 test_buf[] = { 
#include "vstepbai.dat"
}; 
#elif defined(DATA_5)
#define MAX_CARRIERS		20  /* this is the actual file size */ 
#define	BITSPERDMTSYMBOL	120
#define OUTFILENAME "vpentbaiOut.dat"
static  e_s16 input_buf[] = {
#include "vpentbai.dat"
};
static e_s16 test_buf[] = { 
#include "vpentbai.dat"
}; 
#elif defined(DATA_6)

#define MAX_CARRIERS		100  /* this is the actual file size */ 
#define	BITSPERDMTSYMBOL	500
#define OUTFILENAME "xpentsnriOut.dat"
static  e_s16 input_buf[] = {
#include "xpentsnri.dat"
};
static e_s16 test_buf[] = { 
#include "vpentbai.dat"
}; 
#endif /* included data */

static e_s16 alloc_map_buf[] = {
#include "allocmapi.dat"
};
#define T_BSIZE (sizeof(e_s16)*(MAX_CARRIERS*2))

static n_char* t_buf = NULL;

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
*/

int t_run_test( size_t iterations, int argc, const char* argv[] )

   {
   size_t           loop_cnt;

   THTestResults    results;
   static n_char    info[64]; /* gotta be static */

	/* this should accomodate a short + 2 symbols (\r\n) */ 
	const char		*outFilename;
	e_s16            *CarrierSNRdB;
	e_s16            *AllocationMap;
	e_s16            *CarrierBitAllocation;
	e_s16            WaterLeveldB;
	e_s16            WaterLeveldB_out; /* fixed 5/4/00 arw bug#118 */
	e_u16            BitsPerDMTSymbol;
	n_int            i; 
	e_u16            NumberOfCarriers;
	e_s16			*golden_result; 
#if		!CRC_CHECK && !NON_INTRUSIVE_CRC_CHECK
	e_u8			    *out_symbol_buffer; 
	n_char			*stringHeadPtr,*tmp_buf;
	n_int            TempVal; 
#endif
   
    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
     * First, initialize the data structures we need for the test
     */
    t_buf     = (n_char *) th_malloc( T_BSIZE );
    if( t_buf == NULL )
       th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );
	golden_result		 = (e_s16 *)&test_buf; 


   /* When this is defined no file uploading necesary
    * we have all the data in the executable
	* so initialising is simplier
	*/ 
    CarrierSNRdB	     = (e_s16 *)&input_buf; 
	AllocationMap		 = (e_s16 *)&alloc_map_buf; 
    CarrierBitAllocation = (e_s16 *)t_buf; 
	NumberOfCarriers     = MAX_CARRIERS;  

	outFilename = OUTFILENAME;
	BitsPerDMTSymbol = BITSPERDMTSYMBOL;

	if (argc < 2)
	{
		th_printf( "WARNING: Missing output filename  Using: %s\n",outFilename);
        th_printf( "WARNING: Cannot determine bits per DMT symbol  Using: %d\n",BitsPerDMTSymbol);
	} else {
    if ((argc <3) || ((BitsPerDMTSymbol = atoi(argv[2])) == 0))
	{
	    outFilename = argv[1];
		BitsPerDMTSymbol = BITSPERDMTSYMBOL;
        th_printf( "WARNING: Cannot determine bits per DMT symbol  Using: %d\n",BitsPerDMTSymbol);
	}}
     
    WaterLeveldB     = -32768;
	for( i=0; i< MAX_CARRIERS; i++){ 
	    /* Save the maximum CarrierSNR as the inital WaterLevel */
    	if (CarrierSNRdB[i] > WaterLeveldB) {
	        WaterLeveldB = CarrierSNRdB[i];
        } 
	} 

    /* Fill Allocation Map */
    for (i = 0; i < ALLOCATION_MAP_SIZE; i++) {
	     if (AllocationMap[i] > MAX_BITS_PER_CARRIER) {
		        AllocationMap[i] = MAX_BITS_PER_CARRIER;    
	     }
    }

    /* Check if Bit Allocation is possible */    
    if (BitsPerDMTSymbol > (NumberOfCarriers*MAX_BITS_PER_CARRIER)) {
	    th_exit( THE_FAILURE, 
                "Cannot allocate %d bits over %d carriers\n with a maximum of %d bits/carrier.\nExiting...\n",
		        BitsPerDMTSymbol,NumberOfCarriers,MAX_BITS_PER_CARRIER);
    }
    /* Check if Bit Allocation is possible */    
    if (BitsPerDMTSymbol > (NumberOfCarriers*MAX_BITS_PER_CARRIER)) {
	    th_exit( THE_FAILURE, 
                "Cannot allocate %d bits over %d carriers\n with a maximum of %d bits/carrier.\nExiting...\n",
		        BitsPerDMTSymbol,NumberOfCarriers,MAX_BITS_PER_CARRIER);
    }

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
     * This is the actual benchmark
     */

    th_signal_start();  /* Tell the host that the test has begun */

     /* no stopping!  Do ALL the iterations */
 
	 for ( loop_cnt = 0; loop_cnt < iterations; loop_cnt++ ) {
        fxpBitAllocation(CarrierSNRdB,CarrierBitAllocation,NumberOfCarriers,
                         WaterLeveldB, &WaterLeveldB_out, AllocationMap, 
                         BitsPerDMTSymbol, loop_cnt );
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
  for( loop_cnt=0; loop_cnt<NumberOfCarriers; loop_cnt++ ){
#if	NON_INTRUSIVE_CRC_CHECK
	results.CRC = Calc_crc16(CarrierBitAllocation[loop_cnt],results.CRC);
#endif
    if(CarrierBitAllocation[loop_cnt] != golden_result[loop_cnt]){
      th_printf("Failure: Expected [%d] Actual(%d) != golden(%d)\n",loop_cnt,CarrierBitAllocation[loop_cnt],golden_result[loop_cnt]);
	  results.v1         = loop_cnt;
	  results.v2         = CarrierBitAllocation[loop_cnt];
	  results.v3         = golden_result[loop_cnt];
      break;
    }
  }


#if	!CRC_CHECK && !NON_INTRUSIVE_CRC_CHECK
	/* Calculate the size of the output buffer */ 
   TempVal   = 0;            
   tmp_buf   = (n_char *)th_malloc(16); /* should acommodate largest single token */
   if( tmp_buf == NULL )
            th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );

   for( i=0; i<NumberOfCarriers; i++ ){
       TempVal += th_sprintf( tmp_buf, " %d\n", CarrierBitAllocation[i]);
   }
   th_free(tmp_buf); 

   /* Uploading is different as well,
    * Since we do not have input buffer, we need to 
	* use one of our own 
    */ 
    out_symbol_buffer  = (e_u8 *)th_malloc(TempVal+1);
	if( out_symbol_buffer == NULL )
            th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );

    stringHeadPtr = (n_char *)out_symbol_buffer; 
    for( i=0; i<NumberOfCarriers; i++ ){
       stringHeadPtr += th_sprintf( (char *)stringHeadPtr, " %d\n", CarrierBitAllocation[i]);
    }
    th_send_buf_as_file((const char *)out_symbol_buffer,TempVal,outFilename);
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

int test_main( 
    struct TCDef**  tcdef, 
    int             argc, 
    const char*     argv[] 
)
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
