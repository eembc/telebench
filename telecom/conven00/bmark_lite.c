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

#if		FLOAT_SUPPORT
#include "verify.h"
#endif


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

TCDef the_tcdef = 
{
    "TEL conven00   ",
    EEMBC_MEMBER_COMPANY, 
    EEMBC_PROCESSOR, 
    EEMBC_TARGET, 
   "Convolutional Encoder Bench Mark V1.0E0",
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

static n_char* t_buf = NULL;

/* encapsulated data */ 
#if defined( DATA_1 )
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
 * ---------------------------------------------------------------------------*/

int t_run_test( struct TCDef *tcdef,int argc, const char *argv[] )
{
	size_t		loop_cnt;
	e_u8		*golden_result;

	e_u8		*DataBits,*BranchWords;
	e_u8		(*CodeMatrix)[MAX_CODE_VECTORS];
	e_s16		i,DataByteSize,CodeIndex,NumberCodeVectors,ConstraintLength;

 
	const char	*outFilename;


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
    argc=argc;
    argv=argv;
   	golden_result = (e_u8 *)&test_buf;

   t_buf = th_malloc( T_BSIZE );
   if ( t_buf == NULL )
      {
      th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );
      }

   /*
    * When this is defined no file uploading necesary
    * we have all the data in the executable
	* so initialising is simplier
	*/ 
    DataBits     = (e_u8 *)&input_buf; 
    BranchWords  = (e_u8 *)t_buf;
    CodeMatrix   = (e_u8 (*)[2])(BranchWords+(MAX_DATA_SIZE_BYTES));
    DataByteSize =  MAX_DATA_SIZE_BYTES;
		outFilename = OUTFILENAME;
		CodeIndex = CODE_INDEX;

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

   for ( loop_cnt = 0; loop_cnt < tcdef->rec_iterations; loop_cnt++ )  /* no stopping! */
     {
       convolutionalEncode(DataBits, DataByteSize, NumberCodeVectors,
			   ConstraintLength, CodeMatrix,
			   BranchWords
			   );
     } /* end for */

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
    for( i=0; i<NumberCodeVectors*DataByteSize; i++ ){
#if	NON_INTRUSIVE_CRC_CHECK
	  tcdef->CRC = Calc_crc8(BranchWords[i],tcdef->CRC);
#endif
      if(BranchWords[i] != golden_result[i])
	  {
        th_printf("%x: Failed at[%d] calculated(%d) != golden(%d)\n",tcdef->CRC,i,BranchWords[i],golden_result[i]);
		tcdef->v1         = i;
		tcdef->v2         = BranchWords[i];
		tcdef->v3         = golden_result[i];
		break;
	  } 
#if	BMDEBUG
	  else
        th_printf("%x: Passed at[%d] calculated(%d)  = golden(%d)\n",tcdef->CRC,i,BranchWords[i],golden_result[i]);
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
