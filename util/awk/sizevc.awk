#!/usr/local/bin/gawk -f

# NF -1 strips th regular ^Z or ^M character after algorithm.

BEGIN{error=0;}
(1==1) {

  if ($2==".data") {
  DATA=$1;
  }
  if ($2==".text") {
  TEXT=$1;
  }
  if ($2==".rdata") {
  BSS=$1;
  }
}
  
END {
# Print out the benchmark
if ( error != 0 ) {TERROR = "ERROR"}
if ( BMARK == "" ) {BMARK = "Benchmark"}
TOTAL=DATA+BSS+TEXT;

  printf ("%-12s\t%d\t%d\t%d\t%d", 
  BMARK, TEXT, DATA, BSS, TOTAL);
  fflush();
}
    
    
