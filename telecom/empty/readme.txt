The following is the approved process for measuring code and data sizes
for Release 1 of the EEMBC Benchmarks.  This method is called "The
Subtraction Method" because, in general, you build an empty benchmark,
link it to the Test Harness, and subtract the code and data sizes from
a real benchmark linked to the Test Harness.
 
1.  TechTAG is providing an empty benchmark file.  This is to be
compiled and linked with the TH3.2E1 or TH3.3 as applicable in place of
the standard bmark.c file.
 
2.  The code and data sizes for this "null benchmark" must be
calculated by the benchmarking (submitting) company.
 
3.  The values for each will be constants and will be subtracted from
the values of the result of the builds for the real benchmarks+test
harnesses.
 
4.  The result code and data (where data does not include stack and
heap but all other data) will be reported for each kernel, and will be
verified by the certification process of ECL.
 
5, If your compiler does not easily emit code and data sizes, you must
create a .map file (or .lnk file, or equivalent) and manually sum these
up.  When you submit your scores to ECL for certification, you must
include the exact description of how you arrived at your answers.  

