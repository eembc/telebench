#==============================================================================
#$RCSfile: makerule.mak,v $
#
#   DESC : Makerule build script
#
# AUTHOR : Rick Foos, ECL, LLC
#
#  EEMBC : Technical Advisory Group (TechTAG)
#
#    CVS : $Revision: 1.1 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2002 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================

cleanrule:
	-rm -f targets_*.mak
	-find $(ROOT)/th -name harness.mak -exec rm -f {} \;
	-find $(ROOT)/th_lite -name harness.mak -exec rm -f {} \;

harness: targets$(VER)_$(TARGETS).mak $(TH)/$(TARGETS)/harness.mak

targets$(VER)_$(TARGETS).mak:	depgen$(VER)_$(TARGETS).cml $(ROOT)/util/perl/makerule.pl
	perl $(ROOT)/util/perl/makerule.pl -cmd depgen$(VER)_$(TARGETS).cml 


$(TH)/$(TARGETS)/harness.mak:	$(TH)/$(TARGETS)/depgen.cml $(ROOT)/util/perl/makerule.pl
	perl $(ROOT)/util/perl/makerule.pl -cmd $(TH)/$(TARGETS)/depgen.cml 


