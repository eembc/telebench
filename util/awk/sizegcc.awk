#!/usr/local/bin/gawk -f

# NF -1 strips th regular ^Z or ^M character after algorithm.

BEGIN{error=0;}
(1==1) {

  if (($1=="text") && ($2=="data") && ($3=="bss")) {
  getline;#getline;
  TEXT=$1;
  DATA=$2;
  BSS=$3;
  TOTAL=$4;
  }
fflush();
}
  
END {
# Print out the benchmark
if ( error != 0 ) {TERROR = "ERROR"}
if ( BMARK == "" ) {BMARK = "Benchmark"}

  printf ("%-12s\t%d\t%d\t%d\t%d", 
  BMARK, TEXT, DATA, BSS, TOTAL);
  fflush();
}
    
    
