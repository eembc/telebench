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

/****************************************************************************/
/* Test Component Definition Structure                                      */
/****************************************************************************/
int t_run_test( struct TCDef *tcdef,int argc, const char *argv[] );

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

TCDef the_tcdef = 
{
   "TEL fbital00", 
    EEMBC_MEMBER_COMPANY, 
    EEMBC_PROCESSOR, 
    EEMBC_TARGET, 
   "Bit Allocation Bench Mark V1.0E0",
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
 * ---------------------------------------------------------------------------*/

int t_run_test( struct TCDef *tcdef,int argc, const char *argv[] )
{    
	size_t		loop_cnt;

	/* this should accomodate a short + 2 symbols (\r\n) */ 
	const char	*outFilename;
	e_s16            *CarrierSNRdB;
	e_s16            *AllocationMap;
	e_s16            *CarrierBitAllocation;
	e_s16            WaterLeveldB;
	e_s16            WaterLeveldB_out; /* fixed 5/4/00 arw bug#118 */
	e_u16            BitsPerDMTSymbol;
	e_u16            NumberOfCarriers;
	e_s16			*golden_result; 

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
	for( loop_cnt=0; loop_cnt< MAX_CARRIERS; loop_cnt++){ 
	    /* Save the maximum CarrierSNR as the inital WaterLevel */
    	if (CarrierSNRdB[loop_cnt] > WaterLeveldB) {
	        WaterLeveldB = CarrierSNRdB[loop_cnt];
        } 
	} 

    /* Fill Allocation Map */
    for (loop_cnt = 0; loop_cnt < ALLOCATION_MAP_SIZE; loop_cnt++) {
	     if (AllocationMap[loop_cnt] > MAX_BITS_PER_CARRIER) {
		        AllocationMap[loop_cnt] = MAX_BITS_PER_CARRIER;    
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
 
	 for ( loop_cnt = 0; loop_cnt < tcdef->rec_iterations ; loop_cnt++ ) {
        fxpBitAllocation(CarrierSNRdB,CarrierBitAllocation,NumberOfCarriers,
                         WaterLeveldB, &WaterLeveldB_out, AllocationMap, 
                         BitsPerDMTSymbol, loop_cnt );
    } /* end for */


    tcdef->duration		= th_signal_finished() ;
	tcdef->iterations	= loop_cnt;

#if	NON_INTRUSIVE_CRC_CHECK
	tcdef->CRC = 0;
#elif	CRC_CHECK
	tcdef->CRC=0;
#else
	tcdef->CRC=0;
#endif

	/* Verification */ 
  for( loop_cnt=0; loop_cnt<NumberOfCarriers; loop_cnt++ ){
#if	NON_INTRUSIVE_CRC_CHECK
	tcdef->CRC = Calc_crc16(CarrierBitAllocation[loop_cnt],tcdef->CRC);
#endif
    if(CarrierBitAllocation[loop_cnt] != golden_result[loop_cnt]){
      th_printf("Failure: Expected [%d] Actual(%d) != golden(%d)\n",loop_cnt,CarrierBitAllocation[loop_cnt],golden_result[loop_cnt]);
	  tcdef->v1         = loop_cnt;
	  tcdef->v2         = CarrierBitAllocation[loop_cnt];
	  tcdef->v3         = golden_result[loop_cnt];
      break;
    }
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
