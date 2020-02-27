# ============================================================================
#
# Copyright (C) EEMBC(R) All Rights Reserved
#
# This software is licensed with an Acceptable Use Agreement under Apache 2.0.
# Please refer to the license file (LICENSE.md) included with this code.
#
# ============================================================================

cleanlogs:
	@rm -f $(RESULTS)/*.log
	@rm -f $(RESULTS)/*.size
	@rm -f $(TOOLCHAIN)_time$(LITE)$(VER).log
	@rm -f $(TOOLCHAIN)$(PLATFORM)$(LITE).log

clean:: cleanlogs
	@rm -f $(OBJBUILD)/*$(OBJ)
	@rm -f $(OBJBUILD)/*$(LIBTYPE)
	@rm -f $(OBJBUILD)/diffmeasure/*$(OBJ)
	@rm -f $(OBJBUILD)/empty/*$(OBJ)
	@rm -f $(OBJBUILD)/autcor00data_1/*$(OBJ)
	@rm -f $(OBJBUILD)/autcor00data_2/*$(OBJ)
	@rm -f $(OBJBUILD)/autcor00data_3/*$(OBJ)
	@rm -f $(OBJBUILD)/conven00data_1/*$(OBJ)
	@rm -f $(OBJBUILD)/conven00data_2/*$(OBJ)
	@rm -f $(OBJBUILD)/conven00data_3/*$(OBJ)
	@rm -f $(OBJBUILD)/fbital00data_2/*$(OBJ)
	@rm -f $(OBJBUILD)/fbital00data_3/*$(OBJ)
	@rm -f $(OBJBUILD)/fbital00data_6/*$(OBJ)
	@rm -f $(OBJBUILD)/fft00data_1/*$(OBJ)
	@rm -f $(OBJBUILD)/fft00data_2/*$(OBJ)
	@rm -f $(OBJBUILD)/fft00data_3/*$(OBJ)
	@rm -f $(OBJBUILD)/viterb00data_1/*$(OBJ)
	@rm -f $(OBJBUILD)/viterb00data_2/*$(OBJ)
	@rm -f $(OBJBUILD)/viterb00data_3/*$(OBJ)
	@rm -f $(OBJBUILD)/viterb00data_4/*$(OBJ)
	@rm -f $(BINBUILD)/empty$(LITE)$(EXE)
	@rm -f $(BINBUILD)/autcor00data_1$(LITE)$(EXE)
	@rm -f $(BINBUILD)/autcor00data_2$(LITE)$(EXE)
	@rm -f $(BINBUILD)/autcor00data_3$(LITE)$(EXE)
	@rm -f $(BINBUILD)/conven00data_1$(LITE)$(EXE)
	@rm -f $(BINBUILD)/conven00data_2$(LITE)$(EXE)
	@rm -f $(BINBUILD)/conven00data_3$(LITE)$(EXE)
	@rm -f $(BINBUILD)/fbital00data_2$(LITE)$(EXE)
	@rm -f $(BINBUILD)/fbital00data_3$(LITE)$(EXE)
	@rm -f $(BINBUILD)/fbital00data_6$(LITE)$(EXE)
	@rm -f $(BINBUILD)/fft00data_1$(LITE)$(EXE)
	@rm -f $(BINBUILD)/fft00data_2$(LITE)$(EXE)
	@rm -f $(BINBUILD)/fft00data_3$(LITE)$(EXE)
	@rm -f $(BINBUILD)/viterb00data_1$(LITE)$(EXE)
	@rm -f $(BINBUILD)/viterb00data_2$(LITE)$(EXE)
	@rm -f $(BINBUILD)/viterb00data_3$(LITE)$(EXE)
	@rm -f $(BINBUILD)/viterb00data_4$(LITE)$(EXE)
	@rm -f $(BINBUILD)/diffmeasure$(LITE)$(EXE)

mkdir:
	@mkdir -p $(BINBUILD)
	@mkdir -p $(OBJBUILD)
	@mkdir -p $(RESULTS)
	@mkdir -p $(OBJBUILD)/empty
	@mkdir -p $(OBJBUILD)/diffmeasure
	@mkdir -p $(OBJBUILD)/autcor00data_1
	@mkdir -p $(OBJBUILD)/autcor00data_2
	@mkdir -p $(OBJBUILD)/autcor00data_3
	@mkdir -p $(OBJBUILD)/conven00data_1
	@mkdir -p $(OBJBUILD)/conven00data_2
	@mkdir -p $(OBJBUILD)/conven00data_3
	@mkdir -p $(OBJBUILD)/fbital00data_2
	@mkdir -p $(OBJBUILD)/fbital00data_3
	@mkdir -p $(OBJBUILD)/fbital00data_6
	@mkdir -p $(OBJBUILD)/fft00data_1
	@mkdir -p $(OBJBUILD)/fft00data_2
	@mkdir -p $(OBJBUILD)/fft00data_3
	@mkdir -p $(OBJBUILD)/viterb00data_1
	@mkdir -p $(OBJBUILD)/viterb00data_2
	@mkdir -p $(OBJBUILD)/viterb00data_3
	@mkdir -p $(OBJBUILD)/viterb00data_4

rmdir:
	@rm -rf $(BINBUILD)
	@rm -rf $(OBJBUILD)
	@rm -rf $(RESULTS)
