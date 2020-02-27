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

#include "thlib.h"


/*
 * Test Component Defintion Structure
 */
int main(int argc, const char* argv[] );
int t_run_test(struct TCDef *tcdef, int argc, const char* argv[]);

/* Define iterations */
#if !defined(ITERATIONS) || CRC_CHECK || ITERATIONS==DEFAULT
#undef ITERATIONS
#if CRC_CHECK
#define ITERATIONS 5000	/* required iterations for crc */
#else
#define ITERATIONS 5000	/* recommended iterations for benchmark */
#endif
#endif

#if	CRC_CHECK
#define EXPECTED_CRC 0x0000
#elif NON_INTRUSIVE_CRC_CHECK
#define EXPECTED_CRC 0x0000
#else
#define EXPECTED_CRC 0x0000
#endif


TCDef the_tcdef = 
{
   "ALL empty    ",
	EEMBC_MEMBER_COMPANY, 
	EEMBC_PROCESSOR, 
	EEMBC_TARGET, 
	"Void Benchmark to measure size of Test Harness Lite",
	TCDEF_REVISION, 
	{ EEMBC_TH_MAJOR, EEMBC_TH_MINOR, EEMBC_TH_STEP, EEMBC_TH_REVISION },
	/* Target Hardware Version Number Required( make all zeros to ignore )*/
	{ 0, 0, 0, 0 },
	/* The Version number of this Benchmark */
	{ 1, 1, 'B', 1 },
	ITERATIONS,
	0,
	0,
	0,
	/* results */
	0,
	0,
	0,
	0
} ; 

/*
 * Local Declarations
 */

/*********************************************************************************
* FUNC	: int t_run_test( struct TCDef *tcdef,int argc, const char *argv[] )
* DESC  : This is the functions that carries out the algorithm. This function
*         is called from the main.  Same algorithm is called three times. Input
*         data for the algorithm is stored in 'algotst'c'.  All variables declared
*         and initialized in 'init.c'.  When 'BMDEBUG' and 'WINDOWS_EXAMPLE_CODE' 
*         defined in 'thcfg.h' it will write bunch of debug message in the RAM.  
*         All debug routines are in 'debug.c'. It calculates CRC using intermediate
*         values from the algorithms.  CRC is used to check if algorithm carried out
*         correctly.
* ARGUMENT: arc - not used
*           argv - not used
*           tcdef - structure defined in 'thlib.h'.  Following members of tcdef
*     			rec_iterations- recommend number of times algorithm should be carried out
*   			iterations  - actual number of times algorithm was carried
*                             most cases same as 'rec_iterations'
*               duration	- Total time to carry out the algorithm
*               CRC			- calculated CRC
*
* RETURNS : Success if the the CRC matches. 
*****************************************************************************************/    
int t_run_test( struct TCDef *tcdef,int argc, const char *argv[] )
{    
	e_u32	loop_cnt; /* Actual Iterations */

	/* Unused */
	argc=argc;
	argv=argv;

	/*
	 * This is the actual benchmark
	 */
	th_signal_start();

	/*
	 * Void - there is no benchmark.  
	 * Just get the size of the Test Harness
	 */

	loop_cnt = tcdef->rec_iterations;

	tcdef->duration   = th_signal_finished() ;
	tcdef->iterations = loop_cnt ;
	tcdef->v1         = 0;
	tcdef->v2         = 0;
	tcdef->v3         = 0;
	tcdef->v4         = 0;

#if		NON_INTRUSIVE_CRC_CHECK
	tcdef->CRC        = 0;
	tcdef->CRC = Calc_crc8((e_u8)0, tcdef->CRC);
#elif	CRC_CHECK
	tcdef->CRC=0;
	tcdef->CRC = Calc_crc8((e_u8)0, tcdef->CRC);
#else
	tcdef->CRC=0;
#endif

	return	th_report_results(tcdef,EXPECTED_CRC);
} 

/***************************************************************************/
int main(int argc, const char* argv[] )
{
	 /* target specific inititialization */
	al_main(argc, argv);
	/* Benchmark Execution */
	return	t_run_test(&the_tcdef,argc,argv); 
} 
