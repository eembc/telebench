/*==============================================================================
 *$RCSfile: bmark_lite.c,v $
 *
 *   DESC : TH Lite Test Harness routines for benchmarks
 *
 * AUTHOR : ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.13 $
 *          $Date: 2002/08/07 22:21:09 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/techtag/empty/bmark_lite.c,v $
 *          
 * NOTE   : Since benchmarks can be entered (run) multiple times, the benchmark
 *          MUST NOT depend on global data being initialized.  E.g. it must
 *          complelty initialize itself EVERY TIME its t_run_test() function
 *          is called.
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark_lite.c,v $
 * Revision 1.13  2002/08/07 22:21:09  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.12  2002/08/06 21:59:04  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.11  2002/07/22 16:10:12  rick
 * Fix iteration dependant NI CRC
 *
 * Revision 1.10  2002/07/10 19:03:05  rick
 * Always initialize tcdef->CRC
 *
 * Revision 1.9  2002/05/29 22:12:37  rick
 * Set recommended iterations with make
 *
 * Revision 1.8  2002/05/23 20:22:36  rick
 * Clear ansi warnings
 *
 * Revision 1.7  2002/05/10 16:10:16  rick
 * Add al_main to API
 *
 * Revision 1.6  2002/04/23 18:35:36  rick
 * Add reference to rec_iterations.
 *
 * Revision 1.5  2002/04/12 21:30:47  rick
 * Make Lite more consistent with Regular
 *
 * Revision 1.4  2002/03/20 23:19:26  rick
 * Empty Benchmarks
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
