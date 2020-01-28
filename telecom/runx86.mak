#==============================================================================
#$RCSfile: runx86.mak,v $
#
#   DESC : Run Each Benchmark from Host
#
# AUTHOR : Rick Foos, ECL, LLC
#
#  EEMBC : Telecom
#
#    CVS : $Revision: 1.4 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2002 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================

run:: run_viterb00 run_fft00 run_fbital00 run_empty run_conven00 run_autcor00

run_empty:	\
	$(RESULTS)/empty.run.log $(RESULTS)/empty.size.log 

$(RESULTS)/empty.run.log:	 $(BINBUILD)/empty$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/empty$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/empty.run.log 

$(RESULTS)/empty.size.log:	 $(BINBUILD)/empty$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/empty$(LITE)$(EXE) > $(RESULTS)/empty.size.log

run_autcor00:	\
	$(RESULTS)/autcor00data_1.run.log $(RESULTS)/autcor00data_1.size.log \
	$(RESULTS)/autcor00data_2.run.log $(RESULTS)/autcor00data_2.size.log \
	$(RESULTS)/autcor00data_3.run.log $(RESULTS)/autcor00data_3.size.log \

$(RESULTS)/autcor00data_1.run.log:	 $(BINBUILD)/autcor00data_1$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/autcor00data_1$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/autcor00data_1.run.log 

$(RESULTS)/autcor00data_1.size.log:	 $(BINBUILD)/autcor00data_1$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/autcor00data_1$(LITE)$(EXE) > $(RESULTS)/autcor00data_1.size.log

$(RESULTS)/autcor00data_2.run.log:	 $(BINBUILD)/autcor00data_2$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/autcor00data_2$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/autcor00data_2.run.log 

$(RESULTS)/autcor00data_2.size.log:	 $(BINBUILD)/autcor00data_2$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/autcor00data_2$(LITE)$(EXE) > $(RESULTS)/autcor00data_2.size.log

$(RESULTS)/autcor00data_3.run.log:	 $(BINBUILD)/autcor00data_3$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/autcor00data_3$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/autcor00data_3.run.log 

$(RESULTS)/autcor00data_3.size.log:	 $(BINBUILD)/autcor00data_3$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/autcor00data_3$(LITE)$(EXE) > $(RESULTS)/autcor00data_3.size.log

run_conven00:	\
	$(RESULTS)/conven00data_1.run.log $(RESULTS)/conven00data_1.size.log \
	$(RESULTS)/conven00data_2.run.log $(RESULTS)/conven00data_2.size.log \
	$(RESULTS)/conven00data_3.run.log $(RESULTS)/conven00data_3.size.log \

$(RESULTS)/conven00data_1.run.log:	 $(BINBUILD)/conven00data_1$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/conven00data_1$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/conven00data_1.run.log 

$(RESULTS)/conven00data_1.size.log:	 $(BINBUILD)/conven00data_1$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/conven00data_1$(LITE)$(EXE) > $(RESULTS)/conven00data_1.size.log

$(RESULTS)/conven00data_2.run.log:	 $(BINBUILD)/conven00data_2$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/conven00data_2$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/conven00data_2.run.log 

$(RESULTS)/conven00data_2.size.log:	 $(BINBUILD)/conven00data_2$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/conven00data_2$(LITE)$(EXE) > $(RESULTS)/conven00data_2.size.log

$(RESULTS)/conven00data_3.run.log:	 $(BINBUILD)/conven00data_3$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/conven00data_3$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/conven00data_3.run.log 

$(RESULTS)/conven00data_3.size.log:	 $(BINBUILD)/conven00data_3$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/conven00data_3$(LITE)$(EXE) > $(RESULTS)/conven00data_3.size.log

run_fbital00:	\
	$(RESULTS)/fbital00data_2.run.log $(RESULTS)/fbital00data_2.size.log \
	$(RESULTS)/fbital00data_3.run.log $(RESULTS)/fbital00data_3.size.log \
	$(RESULTS)/fbital00data_6.run.log $(RESULTS)/fbital00data_6.size.log \

$(RESULTS)/fbital00data_2.run.log:	 $(BINBUILD)/fbital00data_2$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/fbital00data_2$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/fbital00data_2.run.log 

$(RESULTS)/fbital00data_2.size.log:	 $(BINBUILD)/fbital00data_2$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/fbital00data_2$(LITE)$(EXE) > $(RESULTS)/fbital00data_2.size.log

$(RESULTS)/fbital00data_3.run.log:	 $(BINBUILD)/fbital00data_3$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/fbital00data_3$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/fbital00data_3.run.log 

$(RESULTS)/fbital00data_3.size.log:	 $(BINBUILD)/fbital00data_3$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/fbital00data_3$(LITE)$(EXE) > $(RESULTS)/fbital00data_3.size.log

$(RESULTS)/fbital00data_6.run.log:	 $(BINBUILD)/fbital00data_6$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/fbital00data_6$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/fbital00data_6.run.log 

$(RESULTS)/fbital00data_6.size.log:	 $(BINBUILD)/fbital00data_6$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/fbital00data_6$(LITE)$(EXE) > $(RESULTS)/fbital00data_6.size.log

run_fft00:	\
	$(RESULTS)/fft00data_1.run.log $(RESULTS)/fft00data_1.size.log \
	$(RESULTS)/fft00data_2.run.log $(RESULTS)/fft00data_2.size.log \
	$(RESULTS)/fft00data_3.run.log $(RESULTS)/fft00data_3.size.log \

$(RESULTS)/fft00data_1.run.log:	 $(BINBUILD)/fft00data_1$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/fft00data_1$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/fft00data_1.run.log 

$(RESULTS)/fft00data_1.size.log:	 $(BINBUILD)/fft00data_1$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/fft00data_1$(LITE)$(EXE) > $(RESULTS)/fft00data_1.size.log

$(RESULTS)/fft00data_2.run.log:	 $(BINBUILD)/fft00data_2$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/fft00data_2$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/fft00data_2.run.log 

$(RESULTS)/fft00data_2.size.log:	 $(BINBUILD)/fft00data_2$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/fft00data_2$(LITE)$(EXE) > $(RESULTS)/fft00data_2.size.log

$(RESULTS)/fft00data_3.run.log:	 $(BINBUILD)/fft00data_3$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/fft00data_3$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/fft00data_3.run.log 

$(RESULTS)/fft00data_3.size.log:	 $(BINBUILD)/fft00data_3$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/fft00data_3$(LITE)$(EXE) > $(RESULTS)/fft00data_3.size.log

run_viterb00:	\
	$(RESULTS)/viterb00data_1.run.log $(RESULTS)/viterb00data_1.size.log \
	$(RESULTS)/viterb00data_2.run.log $(RESULTS)/viterb00data_2.size.log \
	$(RESULTS)/viterb00data_3.run.log $(RESULTS)/viterb00data_3.size.log \

$(RESULTS)/viterb00data_1.run.log:	 $(BINBUILD)/viterb00data_1$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/viterb00data_1$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/viterb00data_1.run.log 

$(RESULTS)/viterb00data_1.size.log:	 $(BINBUILD)/viterb00data_1$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/viterb00data_1$(LITE)$(EXE) > $(RESULTS)/viterb00data_1.size.log

$(RESULTS)/viterb00data_2.run.log:	 $(BINBUILD)/viterb00data_2$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/viterb00data_2$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/viterb00data_2.run.log 

$(RESULTS)/viterb00data_2.size.log:	 $(BINBUILD)/viterb00data_2$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/viterb00data_2$(LITE)$(EXE) > $(RESULTS)/viterb00data_2.size.log

$(RESULTS)/viterb00data_3.run.log:	 $(BINBUILD)/viterb00data_3$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/viterb00data_3$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/viterb00data_3.run.log 

$(RESULTS)/viterb00data_3.size.log:	 $(BINBUILD)/viterb00data_3$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/viterb00data_3$(LITE)$(EXE) > $(RESULTS)/viterb00data_3.size.log

$(RESULTS)/viterb00data_4.run.log:	 $(BINBUILD)/viterb00data_4$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $(BINBUILD)/viterb00data_4$(LITE)$(EXE) $(CMDLINE$(LITE)) > $(RESULTS)/viterb00data_4.run.log 

$(RESULTS)/viterb00data_4.size.log:	 $(BINBUILD)/viterb00data_4$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $(BINBUILD)/viterb00data_4$(LITE)$(EXE) > $(RESULTS)/viterb00data_4.size.log

