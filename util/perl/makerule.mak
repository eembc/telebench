# ============================================================================
#
# Copyright (C) EEMBC(R) All Rights Reserved
#
# This software is licensed with an Acceptable Use Agreement under Apache 2.0.
# Please refer to the license file (LICENSE.md) included with this code.
#
# ============================================================================

cleanrule:
	-rm -f targets_*.mak
	-find $(ROOT)/th -name harness.mak -exec rm -f {} \;
	-find $(ROOT)/th_lite -name harness.mak -exec rm -f {} \;

harness: targets$(VER)_$(TARGETS).mak $(TH)/$(TARGETS)/harness.mak

targets$(VER)_$(TARGETS).mak:	depgen$(VER)_$(TARGETS).cml $(ROOT)/util/perl/makerule.pl
	perl $(ROOT)/util/perl/makerule.pl -cmd depgen$(VER)_$(TARGETS).cml 


$(TH)/$(TARGETS)/harness.mak:	$(TH)/$(TARGETS)/depgen.cml $(ROOT)/util/perl/makerule.pl
	perl $(ROOT)/util/perl/makerule.pl -cmd $(TH)/$(TARGETS)/depgen.cml 


