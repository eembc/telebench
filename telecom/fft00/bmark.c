/*==============================================================================
 *$RCSfile: bmark.c,v $
 *
 *   DESC : This file contains the Main and other TH_Lite support functions
 *
 *  EEMBC : Telecom Subcommittee 
 *
 * AUTHOR : RAP
 *
 *    CVS : $Revision: 1.16 $
 *          $Date: 2002/08/09 21:46:58 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/telecom/fft00/bmark.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark.c,v $
 * Revision 1.16  2002/08/09 21:46:58  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.15  2002/07/24 15:56:49  rick
 * Unique keys for all benchmarks, and generate tab delimited log files with column headers.
 *
 * Revision 1.14  2002/07/17 17:44:38  rick
 * Key outputdata files based on input filename
 *
 * Revision 1.13  2002/05/29 22:26:47  rick
 * Set recommended iterations with make
 *
 * Revision 1.12  2002/05/23 20:22:38  rick
 * Clear ansi warnings
 *
 * Revision 1.11  2002/05/22 22:07:25  rick
 * Float support fixes
 *
 * Revision 1.10  2002/05/13 20:26:03  rick
 * Fix missing shifts in 16, and 32 bit CRC
 *
 * Revision 1.9  2002/05/02 16:42:05  rick
 * Fix warning message on direction
 *
 * Revision 1.8  2002/04/25 16:09:01  rick
 * Bug #139: fft should not include  pow function
 *
 * Revision 1.7  2002/04/19 23:17:38  rick
 * Only include verify.h if FLOAT_SUPPORT
 *
 * Revision 1.6  2002/04/19 14:41:18  rick
 * Bug 157:Inconsistency in capitalization
 *
 * Revision 1.5  2002/04/04 21:36:30  rick
 * Iterations 1000, match th reg
 *
 * Revision 1.4  2002/03/23 00:51:48  rick
 * Visual C++ Build fixes
 *
 * Revision 1.3  2002/03/11 22:11:51  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
 *
 * Revision 1.2  2002/02/22 20:46:12  rick
 * Fix d_union conflict in verify.h, thlib.c
 *
 * Revision 1.1  2002/02/18 23:51:53  rick
 * Completed Telocom TH_Lite conversion
 *
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

#include "algo.h"

#if		VERIFY_FLOAT && FLOAT_SUPPORT
#include "verify.h"
#endif

#include <ctype.h> /* toupper */

typedef enum {FORWARD, REVERSE} FFT_DIRECTION;

/*------------------------------------------------------------------------------
 * Test Component Definition Structure
 */

int    t_run_test( size_t iterations, int argc, const char* argv[] );
int    test_main( struct TCDef** tcdef, int argc, const char* argv[] );

/* Define iterations */
#if !defined(ITERATIONS) || CRC_CHECK || ITERATIONS==DEFAULT
#undef ITERATIONS
#if CRC_CHECK
#define ITERATIONS 1000	/* required iterations for crc */
#else
#define ITERATIONS 1000	/* recommended iterations for benchmark */
#endif
#endif

#if NON_INTRUSIVE_CRC_CHECK
#if (defined(C_INTERLEAVED) && defined(D_INTERLEAVED))

#if defined(DATA_1)
#define EXPECTED_CRC			0x21a5
#elif defined(DATA_2)
#define EXPECTED_CRC			0x0527
#else
#define EXPECTED_CRC			0x7ace
#endif

#elif (defined(C_INTERLEAVED) && !defined(D_INTERLEAVED))

#if defined(DATA_1)
#define EXPECTED_CRC			0x2160
#elif defined(DATA_2)
#define EXPECTED_CRC			0x1b91
#else
#define EXPECTED_CRC			0x78af
#endif

#elif (!defined(C_INTERLEAVED) && defined(D_INTERLEAVED))

#if defined(DATA_1)
#define EXPECTED_CRC			0x7d1f
#elif defined(DATA_2)
#define EXPECTED_CRC			0xd7df
#else
#define EXPECTED_CRC			0xb3f9
#endif

#else

#if defined(DATA_1)
#define EXPECTED_CRC			0x2160
#elif defined(DATA_2)
#define EXPECTED_CRC			0x1b91
#else
#define EXPECTED_CRC			0x78af
#endif

#endif /* C_INTERLEAVED D_INTERLEAVED */

#else
#define EXPECTED_CRC			0x0000
#endif

static TCDef the_tcdef = 
   {
    "TEL fft00      ",
   EEMBC_MEMBER_COMPANY,
   EEMBC_PROCESSOR,
   EEMBC_TARGET,
   "FFT/IFFT Bench Mark V1.0E0",
   
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

	/* Default for all runs */
#define	DIRECTION	FORWARD

/* encapsulated data */ 
#if defined(DATA_1)

#define OUTFILENAME "xtpulse256iOutput.dat"
static  e_s16 input_buf[] = {
#include "xtpulse256i.dat"
};
static e_f64 test_buf[] = { 
#include "vtpulse256i.dat"
}; 
#elif defined(DATA_2)

#define OUTFILENAME "xspn256iOutput.dat"
static  e_s16 input_buf[] = {
#include "xspn256i.dat"
};
static e_f64 test_buf[] = { 
#include "vspn256i.dat"
}; 
#else /* default DATA_3 */  

#define OUTFILENAME "xsine256iOutput.dat"
static  e_s16 input_buf[] = {
#include "xsine256i.dat"
};
static e_f64 test_buf[] = { 
#include "golden_sine.dat"
}; 
#endif /* included data */ 

#if defined(C_INTERLEAVED)
static  e_s16 sin_buf[] = {0};
static  e_s16 cosin_buf[] = {
#include "cstable256i.dat"
};
#else
static  e_s16 sin_buf[] = {
#include "stable256i.dat"
}; 
static  e_s16 cosin_buf[] = {
#include "ctable256i.dat"
};
#endif

static  e_s16 index_buf[] = {
#include "brind256i.dat"
}; 

#define T_BSIZE (sizeof(e_s16)*(MAX_FFT_SIZE*2))

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
 *-------------------------------------------------------------------------------*/

int t_run_test( size_t iterations, int argc, const char* argv[] )

  {
	size_t          loop_cnt;
	THTestResults   results;
	static char     info[64]; /* gotta be static */


#if (defined(C_INTERLEAVED) && defined(D_INTERLEAVED))  
	e_s16		*InData,*OutData; 
#else 
	e_s16		*InRealData,*InImagData,*OutRealData,*OutImagData;
	e_s16		*out_buffer;
#endif   
	e_s16          *SineV,*CosineV;
	e_s16          *BitRevInd;
	e_s16          i,FFTSize,NumPoints,TempVal;
	const char		*outFilename;

#if	!CRC_CHECK && !NON_INTRUSIVE_CRC_CHECK
	e_u8			*out_symbol_buffer; 
	e_s8         *stringHeadPtr,*tmp_buf;
#endif

#if		VERIFY_FLOAT && FLOAT_SUPPORT
	e_f64			*golden_result; 
	d_union			dunion;
#endif
	FFT_DIRECTION  Direction;

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * First, initialize the data structures we need for the test
   */
   t_buf     = (n_char *) th_malloc( T_BSIZE );
   if( t_buf == NULL )
       th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );

#if		VERIFY_FLOAT && FLOAT_SUPPORT
   	golden_result	= (e_f64 *)&test_buf; 
#endif


#if (defined(C_INTERLEAVED) && defined(D_INTERLEAVED))
   InData      = (e_s16 *)input_buf; 
   OutData     = (e_s16 *)t_buf;  
#else
   InRealData  = (e_s16 *)t_buf;
   InImagData  = InRealData + (MAX_FFT_SIZE);
   OutRealData = InImagData + (MAX_FFT_SIZE);
   OutImagData = OutRealData + (MAX_FFT_SIZE);
   out_buffer	= (e_s16 *)th_malloc( T_BSIZE );
   if( out_buffer == NULL )
       th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );
#endif /* INTERLEAVED */ 
   
   /* When this is defined no file uploading necesary
    * we have all the data in the executable
	* so initialising is simplier
	*/ 
    SineV       = (e_s16 *)&sin_buf; 
    CosineV     = (e_s16 *)&cosin_buf; 
    BitRevInd   = (e_s16 *)&index_buf;

	if (argc < 2)
	{
		outFilename = OUTFILENAME;
		th_printf( "WARNING: Missing output filename  Using: %s\n",outFilename);
		Direction = DIRECTION;
        th_printf( "WARNING: Cannot determine Direction Using: %s\n",Direction?"Reverse":"Forward");
	} else 
    if (argc <3)
	{
	    outFilename = argv[1];
		Direction = DIRECTION;
        th_printf( "WARNING: Cannot determine Direction Using: %s\n",Direction?"Reverse":"Forward");
	} else {
	    outFilename = argv[1];
		if (toupper(argv[2][0]) == 'F')	Direction = FORWARD;
	    else							Direction = REVERSE;
	}

#if !(defined(C_INTERLEAVED) && defined(D_INTERLEAVED))  
	NumPoints     = 0;
    for(i=0; i < MAX_FFT_SIZE*2 ; i+=2){
      InRealData[NumPoints] = input_buf[i]; 
	  InImagData[NumPoints] = input_buf[i+1];
      NumPoints++;
    }
#else
    NumPoints = MAX_FFT_SIZE; 
#endif    
   /* FFTSize = (e_s16) ceil(log10(NumPoints)/log10(2.0));*/
   TempVal = 1;
   FFTSize = 0;
   while (TempVal < NumPoints)
     {
       FFTSize++;
       TempVal = TempVal << 1;
     }
  

/* prescale inputs to prevent overflow */
#if (defined(C_INTERLEAVED) && defined(D_INTERLEAVED))  
    for (i = 0; i < ipow(2,FFTSize); i++) {
        InData[2*i]   >>= FFTSize;
        InData[2*i+1] >>= FFTSize;
    } 
#else
	for (i = 0; i < ipow(2,FFTSize); i++) {
        InRealData[i] >>= FFTSize;
        InImagData[i] >>= FFTSize;
    } 
#endif 
   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    * This is the actual benchmark
    *---------------------------------------------------------------------------*/

   th_signal_start();  /* Tell the host that the test has begun */

   for ( loop_cnt = 0; loop_cnt < iterations; loop_cnt++ )  /* no stopping! */
     {
       if (Direction == FORWARD)
	 {
/* Define C_INTERLEAVED & D_INTERLEAVED at compile time for this */
#if (defined(C_INTERLEAVED) && defined(D_INTERLEAVED))  

    fxpfft (
        InData,                     /* real part of input data */
        NULL,                       /* imaginary part of input data */
        OutData,                    /* real part of output data */
        NULL,                       /* imaginary part of output data */
        FFTSize,                    /* size of data = 2**DataSizeExponent */
        SineV,                      /* Sine table */
        CosineV,                    /* Cosine table */
        BitRevInd                   /* bit reversal indicies */
    ) ;

#else  /* Define C_INTERLEAVED at compile time for this */

    fxpfft (
        InRealData,                 /* real part of input data */
        InImagData,                 /* imaginary part of input data */
        OutRealData,                /* real part of output data */
        OutImagData,                /* imaginary part of output data */
        FFTSize,                    /* size of data = 2**DataSizeExponent */
        SineV,                      /* Sine table */
        CosineV,                    /* Cosine table */
        BitRevInd                   /* bit reversal indicies */
    ) ;
#endif	
	 }
       else /* Reverse */ 
	 {
/* Define C_INTERLEAVED & D_INTERLEAVED at compile time for this */
#if (defined(C_INTERLEAVED) && defined(D_INTERLEAVED))  

    fxpifft (
        InData,                     /* real part of input data */
        NULL,                       /* imaginary part of input data */
        OutData,                    /* real part of output data */
        NULL,                       /* imaginary part of output data */
        FFTSize,                    /* size of data = 2**DataSizeExponent */
        SineV,                      /* Sine table */
        CosineV,                    /* Cosine table */
        BitRevInd                   /* bit reversal indicies */
    ) ;

#else  /* Define C_INTERLEAVED at compile time for this */

    fxpifft (
        InRealData,                 /* real part of input data */
        InImagData,                 /* imaginary part of input data */
        OutRealData,                /* real part of output data */
        OutImagData,                /* imaginary part of output data */
        FFTSize,                    /* size of data = 2**DataSizeExponent */
        SineV,                      /* Sine table */
        CosineV,                    /* Cosine table */
        BitRevInd                   /* bit reversal indicies */
    ) ;
#endif
	 }
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

	/* Verification with Diffmeasure */
#if (defined(C_INTERLEAVED) && defined(D_INTERLEAVED))

#if	 VERIFY_FLOAT && FLOAT_SUPPORT
	dunion.d = diffmeasure (golden_result, NumPoints, COMPLEX, OutData, NumPoints, COMPLEX);
#endif
#if	NON_INTRUSIVE_CRC_CHECK
  for( i=0; i<NumPoints; i++ )
	results.CRC = Calc_crc16(OutData[i],results.CRC);
#endif

#else
	for( i=0; i<NumPoints; i++ ){	/* Convert into interleaved form  */ 
		out_buffer[i*2]		= OutRealData[i];
		out_buffer[(i*2)+1]	= OutImagData[i]; 
#if	NON_INTRUSIVE_CRC_CHECK
		results.CRC = Calc_crc16(OutRealData[i],results.CRC);
		results.CRC = Calc_crc16(OutImagData[i],results.CRC);
#endif
	} 
#if	 VERIFY_FLOAT && FLOAT_SUPPORT
	dunion.d	= diffmeasure (golden_result, NumPoints, COMPLEX, out_buffer, NumPoints, COMPLEX);
#endif
#endif 

#if	 VERIFY_FLOAT && FLOAT_SUPPORT
	results.v1			= dunion.v[0];
	results.v2			= dunion.v[1];
#endif


#if	!CRC_CHECK && !NON_INTRUSIVE_CRC_CHECK
   /* Calculate the size of the output buffer */ 
   TempVal   = 0;             /* reuse this variable as a counter */ 
   tmp_buf   = (e_s8 *)th_malloc(16); /* should acommodate largest single token */
   if( tmp_buf == NULL )
            th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );

   for( i=0; i<NumPoints; i++ ){
#if (defined(C_INTERLEAVED) && defined(D_INTERLEAVED))	
        TempVal += th_sprintf( (char *)tmp_buf," %d %d\n", OutData[2*i], OutData[2*i+1]);
#else
        TempVal += th_sprintf( (char *)tmp_buf," %d %d\n", OutRealData[i], OutImagData[i]);
#endif
   } 
   th_free(tmp_buf); 

    out_symbol_buffer  = (e_u8 *)th_malloc(TempVal+1);
	if( out_symbol_buffer == NULL )
            th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );

    stringHeadPtr = (e_s8 *)out_symbol_buffer; 
    for( i=0; i<NumPoints; i++ ){
#if (defined(C_INTERLEAVED) && defined(D_INTERLEAVED))	
        stringHeadPtr += th_sprintf((char *) stringHeadPtr," %d %d\n", OutData[2*i], OutData[2*i+1]);
#else
        stringHeadPtr += th_sprintf( (char *)stringHeadPtr," %d %d\n", OutRealData[i], OutImagData[i]);
#endif
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

int test_main( struct TCDef** tcdef, int argc, const char* argv[])
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

