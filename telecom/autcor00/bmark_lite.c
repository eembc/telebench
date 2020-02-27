/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#include "algo.h"

#if		VERIFY_FLOAT && FLOAT_SUPPORT
#include "verify.h"		/* diffmeasure */
#endif

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

TCDef the_tcdef = 
{
    "TEL autcor00   ",
    EEMBC_MEMBER_COMPANY, 
    EEMBC_PROCESSOR, 
    EEMBC_TARGET, 
   "Autocorrelation Bench Mark V1.0E0",
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

int t_run_test( struct TCDef *tcdef,int argc, const char *argv[] )
{    
	size_t			loop_cnt;
	e_f64			*golden_result; 
#if	VERIFY_FLOAT && FLOAT_SUPPORT
	d_union			dunion;
#endif

   /* this should accomodate a short + 2 symbols (\n) */ 
	const char		*outFilename;

	e_s16			*InputData,*AutoCorrData;
	e_s16			DataSize,NumberOfLags,Scale,TempVal;

	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	 * First, initialize the data structures we need for the test
	 */

   t_buf     = (n_char *) th_malloc( T_BSIZE );
   if( t_buf == NULL )
       th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );

   	golden_result= (e_f64 *)&test_buf; 

   /* When this is defined no file uploading necesary
    * we have all the data in the executable
	* so initialising is simplier
	*/ 
    InputData	 = (e_s16 *)&input_buf; 
    AutoCorrData = (e_s16 *)t_buf;
	DataSize     = MAX_DATA_SIZE;  

	/* outFilename is unused, in for command line compatibility */
	outFilename = OUTFILENAME;
		NumberOfLags = NUMBER_OF_LAGS;
	if (argc < 2)  
	{
		NumberOfLags = NUMBER_OF_LAGS;
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
      tcdef->CRC = 0;
   th_signal_start();  /* Tell the host that the test has begun */

   for ( loop_cnt = 0; loop_cnt < tcdef->rec_iterations ; loop_cnt++ )  /* no stopping! */
      {
   	fxpAutoCorrelation(InputData,AutoCorrData,DataSize,NumberOfLags,
	                   Scale
			   );
/* Bug 51 always true */
#if BMDEBUG
		if ( !th_harness_poll() )	break;
#endif
      }

    tcdef->duration		= th_signal_finished() ;
	tcdef->iterations	= tcdef->rec_iterations;
#if		VERIFY_FLOAT && FLOAT_SUPPORT
	dunion.d			= diffmeasure (golden_result, NumberOfLags, COMPLEX, AutoCorrData, NumberOfLags, COMPLEX);
	tcdef->v1			= dunion.v[0];
	tcdef->v2			= dunion.v[1];
#else
	tcdef->v1			= 0;
	tcdef->v2			= 0;
#endif
	tcdef->v3			= 0;
	tcdef->v4			= 0;

#if		NON_INTRUSIVE_CRC_CHECK
	tcdef->CRC = 0;
	for ( loop_cnt = 0; loop_cnt < (size_t) NumberOfLags;loop_cnt++)
		tcdef->CRC = Calc_crc16((e_u16) AutoCorrData[loop_cnt],tcdef->CRC);
#elif	CRC_CHECK
	tcdef->CRC=0;
#else
	tcdef->CRC=0;
#endif

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
