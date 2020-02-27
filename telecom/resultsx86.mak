# ============================================================================
#
# Copyright (C) EEMBC(R) All Rights Reserved
#
# This software is licensed with an Acceptable Use Agreement under Apache 2.0.
# Please refer to the license file (LICENSE.md) included with this code.
#
# ============================================================================

results:: alltime allsize

alltime:	$(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log

TIMELOGS	=	\
	$(RESULTS)/autcor00data_1.run.log \
	$(RESULTS)/autcor00data_2.run.log \
	$(RESULTS)/autcor00data_3.run.log \
	$(RESULTS)/conven00data_1.run.log \
	$(RESULTS)/conven00data_2.run.log \
	$(RESULTS)/conven00data_3.run.log \
	$(RESULTS)/fbital00data_2.run.log \
	$(RESULTS)/fbital00data_3.run.log \
	$(RESULTS)/fbital00data_6.run.log \
	$(RESULTS)/fft00data_1.run.log \
	$(RESULTS)/fft00data_2.run.log \
	$(RESULTS)/fft00data_3.run.log \
	$(RESULTS)/viterb00data_1.run.log \
	$(RESULTS)/viterb00data_2.run.log \
	$(RESULTS)/viterb00data_3.run.log \
	$(RESULTS)/viterb00data_4.run.log

$(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log:	 $(TIMELOGS)
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_1 $(RESULTS)/autcor00data_1.run.log > $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_2 $(RESULTS)/autcor00data_2.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_3 $(RESULTS)/autcor00data_3.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_1 $(RESULTS)/conven00data_1.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_2 $(RESULTS)/conven00data_2.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_3 $(RESULTS)/conven00data_3.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_2 $(RESULTS)/fbital00data_2.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_3 $(RESULTS)/fbital00data_3.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_6 $(RESULTS)/fbital00data_6.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_1 $(RESULTS)/fft00data_1.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_2 $(RESULTS)/fft00data_2.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_3 $(RESULTS)/fft00data_3.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_1 $(RESULTS)/viterb00data_1.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_2 $(RESULTS)/viterb00data_2.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_3 $(RESULTS)/viterb00data_3.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/awk/extracttime.awk -v DATASET=DATA_4 $(RESULTS)/viterb00data_4.run.log >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log

allsize:	$(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log

SIZELOGS	=	\
	$(RESULTS)/empty.size.log \
	$(RESULTS)/autcor00data_1.size.log \
	$(RESULTS)/autcor00data_2.size.log \
	$(RESULTS)/autcor00data_3.size.log \
	$(RESULTS)/conven00data_1.size.log \
	$(RESULTS)/conven00data_2.size.log \
	$(RESULTS)/conven00data_3.size.log \
	$(RESULTS)/fbital00data_2.size.log \
	$(RESULTS)/fbital00data_3.size.log \
	$(RESULTS)/fbital00data_6.size.log \
	$(RESULTS)/fft00data_1.size.log \
	$(RESULTS)/fft00data_2.size.log \
	$(RESULTS)/fft00data_3.size.log \
	$(RESULTS)/viterb00data_1.size.log \
	$(RESULTS)/viterb00data_2.size.log \
	$(RESULTS)/viterb00data_3.size.log \
	$(RESULTS)/viterb00data_4.size.log

$(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log:	 $(SIZELOGS)
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=telempty  $(RESULTS)/empty.size.log > $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=autcor00data_1  $(RESULTS)/autcor00data_1.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=autcor00data_2  $(RESULTS)/autcor00data_2.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=autcor00data_3  $(RESULTS)/autcor00data_3.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=conven00data_1  $(RESULTS)/conven00data_1.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=conven00data_2  $(RESULTS)/conven00data_2.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=conven00data_3  $(RESULTS)/conven00data_3.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=fbital00data_2  $(RESULTS)/fbital00data_2.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=fbital00data_3  $(RESULTS)/fbital00data_3.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=fbital00data_6  $(RESULTS)/fbital00data_6.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=fft00data_1  $(RESULTS)/fft00data_1.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=fft00data_2  $(RESULTS)/fft00data_2.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=fft00data_3  $(RESULTS)/fft00data_3.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=viterb00data_1  $(RESULTS)/viterb00data_1.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=viterb00data_2  $(RESULTS)/viterb00data_2.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=viterb00data_3  $(RESULTS)/viterb00data_3.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@gawk -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk -v BMARK=viterb00data_4  $(RESULTS)/viterb00data_4.size.log >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
	@echo >> $(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
