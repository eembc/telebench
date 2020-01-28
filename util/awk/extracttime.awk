#!/usr/local/bin/gawk -f

# NF -1 strips th regular ^Z or ^M character after algorithm.

BEGIN{error=0;CRC="";ECRC="";}
(1==1) {

  if (($2=="Bench") && ($3=="Mark") && ($4==":")) {
    BM = "";
    for (i=5; i<=NF; i++) BM = BM $i " ";
    # Have to strip NL off the last field.
    BM=substr(BM,1,length(BM)-1);
# TH Regular put's a carriage return in here.
    THCR=match(BM,/\r/);
    if (THCR != 0 ) {BM=substr(BM,1,THCR-1);}
  }

  if ($2=="BM:") {
    BM = "";
    for (i=3; i<=NF; i++) BM = BM $i " ";
    BM=substr(BM,1,length(BM)-1);
# TH Regular put's a carriage return in here.
    THCR=match(BM,/\r/);
    if (THCR != 0 ) {BM=substr(BM,1,THCR-1);}
  }
  
  if ($2=="ID:") {
    IDSUB = substr($3,1,16);
    IDBM  = $4;
    if (IDSUB=="!!!!EEMBC-BM!!!!") {
    IDSUB = "EEMBC";
    IDBM  = "EEMBC";
    }
  }
  if (($2=="Iterations") && ($3=="=")) { IT = $4;  }
  if (($2=="Target") && ($3=="Duration")) { DU = $5; }
  if (($3=="CRC") && ($4=="=")) { CRC = substr($5,1,length($5)-1);  }
  if (($2=="Time") && ($3=="/") && ($4=="Iter")) { SECIT = $6; }

  if (($2=="Iterations/Sec") && ($3=="=")) { ITSEC = $4; }
  if (($2=="Total") && ($3=="Run") && ($4=="Time")) { RUNTIME = $6; }
  if (($2=="Failure:") && ($3=="CRC") && ($4=="is")) { ECRC = $8 }
# DONE replaced by Failure
  if (($2=="Failure:") && ($3!="CRC")) { error++; }
  if (($1=="ERROR")) { error++; }
}
  
END {
# Print out the benchmark
if ( error != 0 || BM=="") {TERROR = "ERROR"}
if (CRC != "")
  {
    CRC = "0x" CRC;
    if (ECRC == ""){ECRC=CRC;}
    else {ECRC = "0x" ECRC;}
  }

  DU=DU+0;
  printf ("%s\t%-12s\t%-11s\t%s\t%-30s\t%-6s\t%-6s\t%d\t%d\t%f\t%f\t%f", 
  IDSUB, IDBM, DATASET, TERROR, BM, ECRC, CRC, IT, DU, ITSEC, RUNTIME, SECIT);
  fflush();
}
    
    
