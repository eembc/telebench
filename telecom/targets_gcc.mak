# File generated by Makerule.pl - DO NOT EDIT
# Edit depgen_gcc.cml to change
# $Revision: 1.22 $ $Date: 2002/07/18 19:00:12 $

$(OBJBUILD)/empty/bmark$(LITE)$(OBJ) : empty/bmark$(LITE).c $(BMDEPS)
	$(COM) -Iempty -DITERATIONS=$(empty) $(CINCS) $(OBJOUT)$(OBJBUILD)/empty/bmark$(LITE)$(OBJ) empty/bmark$(LITE).c

EMPTY = \
    $(OBJBUILD)/empty/bmark$(LITE)$(OBJ) 

$(BINBUILD)/empty$(LITE)$(EXE):  $(EMPTY) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/empty$(LITE)$(EXE) $(EMPTY) $(THLIB)  


$(OBJBUILD)/autcor00data_1/autcor00$(OBJ) :                            \
                                            autcor00/algo.h
$(OBJBUILD)/autcor00data_1/autcor00$(OBJ) : autcor00/autcor00.c        \
                                            $(BMDEPS)
	$(COM) -Iautcor00 -Iautcor00/datasets -Idiffmeasure -DDATA_1 -DITERATIONS=$(autcor00data_1) $(CINCS) $(OBJOUT)$(OBJBUILD)/autcor00data_1/autcor00$(OBJ) autcor00/autcor00.c

$(OBJBUILD)/autcor00data_1/bmark$(LITE)$(OBJ) :                        \
                                                autcor00/algo.h        \
                                                diffmeasure/verify.h   \
                                                autcor00/datasets/xpulsei.dat \
                                                autcor00/datasets/vpulseai.dat \
                                                autcor00/datasets/xsinei.dat \
                                                autcor00/datasets/vsineai.dat \
                                                autcor00/datasets/xspeechi.dat \
                                                autcor00/datasets/vspeechai.dat
$(OBJBUILD)/autcor00data_1/bmark$(LITE)$(OBJ) : autcor00/bmark$(LITE).c \
                                                $(BMDEPS)
	$(COM) -Iautcor00 -Iautcor00/datasets -Idiffmeasure -DDATA_1 -DITERATIONS=$(autcor00data_1) $(CINCS) $(OBJOUT)$(OBJBUILD)/autcor00data_1/bmark$(LITE)$(OBJ) autcor00/bmark$(LITE).c

$(OBJBUILD)/autcor00data_1/verify$(OBJ) :                              \
                                          diffmeasure/verify.h
$(OBJBUILD)/autcor00data_1/verify$(OBJ) : diffmeasure/verify.c         \
                                          $(BMDEPS)
	$(COM) -Iautcor00 -Iautcor00/datasets -Idiffmeasure -DDATA_1 -DITERATIONS=$(autcor00data_1) $(CINCS) $(OBJOUT)$(OBJBUILD)/autcor00data_1/verify$(OBJ) diffmeasure/verify.c

AUTCOR00DATA_1 = \
    $(OBJBUILD)/autcor00data_1/autcor00$(OBJ) \
    $(OBJBUILD)/autcor00data_1/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/autcor00data_1/verify$(OBJ) 

$(BINBUILD)/autcor00data_1$(LITE)$(EXE):  $(AUTCOR00DATA_1) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/autcor00data_1$(LITE)$(EXE) $(AUTCOR00DATA_1) $(THLIB)  


$(OBJBUILD)/autcor00data_2/autcor00$(OBJ) :                            \
                                            autcor00/algo.h
$(OBJBUILD)/autcor00data_2/autcor00$(OBJ) : autcor00/autcor00.c        \
                                            $(BMDEPS)
	$(COM) -Iautcor00 -Iautcor00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(autcor00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/autcor00data_2/autcor00$(OBJ) autcor00/autcor00.c

$(OBJBUILD)/autcor00data_2/bmark$(LITE)$(OBJ) :                        \
                                                autcor00/algo.h        \
                                                diffmeasure/verify.h   \
                                                autcor00/datasets/xpulsei.dat \
                                                autcor00/datasets/vpulseai.dat \
                                                autcor00/datasets/xsinei.dat \
                                                autcor00/datasets/vsineai.dat \
                                                autcor00/datasets/xspeechi.dat \
                                                autcor00/datasets/vspeechai.dat
$(OBJBUILD)/autcor00data_2/bmark$(LITE)$(OBJ) : autcor00/bmark$(LITE).c \
                                                $(BMDEPS)
	$(COM) -Iautcor00 -Iautcor00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(autcor00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/autcor00data_2/bmark$(LITE)$(OBJ) autcor00/bmark$(LITE).c

$(OBJBUILD)/autcor00data_2/verify$(OBJ) :                              \
                                          diffmeasure/verify.h
$(OBJBUILD)/autcor00data_2/verify$(OBJ) : diffmeasure/verify.c         \
                                          $(BMDEPS)
	$(COM) -Iautcor00 -Iautcor00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(autcor00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/autcor00data_2/verify$(OBJ) diffmeasure/verify.c

AUTCOR00DATA_2 = \
    $(OBJBUILD)/autcor00data_2/autcor00$(OBJ) \
    $(OBJBUILD)/autcor00data_2/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/autcor00data_2/verify$(OBJ) 

$(BINBUILD)/autcor00data_2$(LITE)$(EXE):  $(AUTCOR00DATA_2) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/autcor00data_2$(LITE)$(EXE) $(AUTCOR00DATA_2) $(THLIB)  


$(OBJBUILD)/autcor00data_3/autcor00$(OBJ) :                            \
                                            autcor00/algo.h
$(OBJBUILD)/autcor00data_3/autcor00$(OBJ) : autcor00/autcor00.c        \
                                            $(BMDEPS)
	$(COM) -Iautcor00 -Iautcor00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(autcor00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/autcor00data_3/autcor00$(OBJ) autcor00/autcor00.c

$(OBJBUILD)/autcor00data_3/bmark$(LITE)$(OBJ) :                        \
                                                autcor00/algo.h        \
                                                diffmeasure/verify.h   \
                                                autcor00/datasets/xpulsei.dat \
                                                autcor00/datasets/vpulseai.dat \
                                                autcor00/datasets/xsinei.dat \
                                                autcor00/datasets/vsineai.dat \
                                                autcor00/datasets/xspeechi.dat \
                                                autcor00/datasets/vspeechai.dat
$(OBJBUILD)/autcor00data_3/bmark$(LITE)$(OBJ) : autcor00/bmark$(LITE).c \
                                                $(BMDEPS)
	$(COM) -Iautcor00 -Iautcor00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(autcor00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/autcor00data_3/bmark$(LITE)$(OBJ) autcor00/bmark$(LITE).c

$(OBJBUILD)/autcor00data_3/verify$(OBJ) :                              \
                                          diffmeasure/verify.h
$(OBJBUILD)/autcor00data_3/verify$(OBJ) : diffmeasure/verify.c         \
                                          $(BMDEPS)
	$(COM) -Iautcor00 -Iautcor00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(autcor00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/autcor00data_3/verify$(OBJ) diffmeasure/verify.c

AUTCOR00DATA_3 = \
    $(OBJBUILD)/autcor00data_3/autcor00$(OBJ) \
    $(OBJBUILD)/autcor00data_3/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/autcor00data_3/verify$(OBJ) 

$(BINBUILD)/autcor00data_3$(LITE)$(EXE):  $(AUTCOR00DATA_3) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/autcor00data_3$(LITE)$(EXE) $(AUTCOR00DATA_3) $(THLIB)  


$(OBJBUILD)/conven00data_1/bmark$(LITE)$(OBJ) :                        \
                                                conven00/algo.h        \
                                                conven00/datasets/xk5r2di.dat \
                                                conven00/datasets/vk5r2bwi.dat \
                                                conven00/datasets/xk4r2di.dat \
                                                conven00/datasets/vk4r2bwi.dat \
                                                conven00/datasets/xk3r2di.dat \
                                                conven00/datasets/vk3r2bwi.dat
$(OBJBUILD)/conven00data_1/bmark$(LITE)$(OBJ) : conven00/bmark$(LITE).c \
                                                $(BMDEPS)
	$(COM) -Iconven00 -Iconven00/datasets -Idiffmeasure -DDATA_1 -DITERATIONS=$(conven00data_1) $(CINCS) $(OBJOUT)$(OBJBUILD)/conven00data_1/bmark$(LITE)$(OBJ) conven00/bmark$(LITE).c

$(OBJBUILD)/conven00data_1/conven00$(OBJ) :                            \
                                            conven00/algo.h
$(OBJBUILD)/conven00data_1/conven00$(OBJ) : conven00/conven00.c        \
                                            $(BMDEPS)
	$(COM) -Iconven00 -Iconven00/datasets -Idiffmeasure -DDATA_1 -DITERATIONS=$(conven00data_1) $(CINCS) $(OBJOUT)$(OBJBUILD)/conven00data_1/conven00$(OBJ) conven00/conven00.c

$(OBJBUILD)/conven00data_1/verify$(OBJ) :                              \
                                          diffmeasure/verify.h
$(OBJBUILD)/conven00data_1/verify$(OBJ) : diffmeasure/verify.c         \
                                          $(BMDEPS)
	$(COM) -Iconven00 -Iconven00/datasets -Idiffmeasure -DDATA_1 -DITERATIONS=$(conven00data_1) $(CINCS) $(OBJOUT)$(OBJBUILD)/conven00data_1/verify$(OBJ) diffmeasure/verify.c

CONVEN00DATA_1 = \
    $(OBJBUILD)/conven00data_1/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/conven00data_1/conven00$(OBJ) \
    $(OBJBUILD)/conven00data_1/verify$(OBJ) 

$(BINBUILD)/conven00data_1$(LITE)$(EXE):  $(CONVEN00DATA_1) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/conven00data_1$(LITE)$(EXE) $(CONVEN00DATA_1) $(THLIB)  


$(OBJBUILD)/conven00data_2/bmark$(LITE)$(OBJ) :                        \
                                                conven00/algo.h        \
                                                conven00/datasets/xk5r2di.dat \
                                                conven00/datasets/vk5r2bwi.dat \
                                                conven00/datasets/xk4r2di.dat \
                                                conven00/datasets/vk4r2bwi.dat \
                                                conven00/datasets/xk3r2di.dat \
                                                conven00/datasets/vk3r2bwi.dat
$(OBJBUILD)/conven00data_2/bmark$(LITE)$(OBJ) : conven00/bmark$(LITE).c \
                                                $(BMDEPS)
	$(COM) -Iconven00 -Iconven00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(conven00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/conven00data_2/bmark$(LITE)$(OBJ) conven00/bmark$(LITE).c

$(OBJBUILD)/conven00data_2/conven00$(OBJ) :                            \
                                            conven00/algo.h
$(OBJBUILD)/conven00data_2/conven00$(OBJ) : conven00/conven00.c        \
                                            $(BMDEPS)
	$(COM) -Iconven00 -Iconven00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(conven00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/conven00data_2/conven00$(OBJ) conven00/conven00.c

$(OBJBUILD)/conven00data_2/verify$(OBJ) :                              \
                                          diffmeasure/verify.h
$(OBJBUILD)/conven00data_2/verify$(OBJ) : diffmeasure/verify.c         \
                                          $(BMDEPS)
	$(COM) -Iconven00 -Iconven00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(conven00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/conven00data_2/verify$(OBJ) diffmeasure/verify.c

CONVEN00DATA_2 = \
    $(OBJBUILD)/conven00data_2/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/conven00data_2/conven00$(OBJ) \
    $(OBJBUILD)/conven00data_2/verify$(OBJ) 

$(BINBUILD)/conven00data_2$(LITE)$(EXE):  $(CONVEN00DATA_2) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/conven00data_2$(LITE)$(EXE) $(CONVEN00DATA_2) $(THLIB)  


$(OBJBUILD)/conven00data_3/bmark$(LITE)$(OBJ) :                        \
                                                conven00/algo.h        \
                                                conven00/datasets/xk5r2di.dat \
                                                conven00/datasets/vk5r2bwi.dat \
                                                conven00/datasets/xk4r2di.dat \
                                                conven00/datasets/vk4r2bwi.dat \
                                                conven00/datasets/xk3r2di.dat \
                                                conven00/datasets/vk3r2bwi.dat
$(OBJBUILD)/conven00data_3/bmark$(LITE)$(OBJ) : conven00/bmark$(LITE).c \
                                                $(BMDEPS)
	$(COM) -Iconven00 -Iconven00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(conven00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/conven00data_3/bmark$(LITE)$(OBJ) conven00/bmark$(LITE).c

$(OBJBUILD)/conven00data_3/conven00$(OBJ) :                            \
                                            conven00/algo.h
$(OBJBUILD)/conven00data_3/conven00$(OBJ) : conven00/conven00.c        \
                                            $(BMDEPS)
	$(COM) -Iconven00 -Iconven00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(conven00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/conven00data_3/conven00$(OBJ) conven00/conven00.c

$(OBJBUILD)/conven00data_3/verify$(OBJ) :                              \
                                          diffmeasure/verify.h
$(OBJBUILD)/conven00data_3/verify$(OBJ) : diffmeasure/verify.c         \
                                          $(BMDEPS)
	$(COM) -Iconven00 -Iconven00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(conven00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/conven00data_3/verify$(OBJ) diffmeasure/verify.c

CONVEN00DATA_3 = \
    $(OBJBUILD)/conven00data_3/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/conven00data_3/conven00$(OBJ) \
    $(OBJBUILD)/conven00data_3/verify$(OBJ) 

$(BINBUILD)/conven00data_3$(LITE)$(EXE):  $(CONVEN00DATA_3) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/conven00data_3$(LITE)$(EXE) $(CONVEN00DATA_3) $(THLIB)  


$(OBJBUILD)/fbital00data_2/bmark$(LITE)$(OBJ) :                        \
                                                fbital00/algo.h        \
                                                fbital00/datasets/vtypbai.dat \
                                                fbital00/datasets/xtypsnri.dat \
                                                fbital00/datasets/xstepsnri.dat \
                                                fbital00/datasets/vstepbai.dat \
                                                fbital00/datasets/vpentbai.dat \
                                                fbital00/datasets/xpentsnri.dat \
                                                fbital00/datasets/allocmapi.dat
$(OBJBUILD)/fbital00data_2/bmark$(LITE)$(OBJ) : fbital00/bmark$(LITE).c \
                                                $(BMDEPS)
	$(COM) -Ifbital00 -Ifbital00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(fbital00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/fbital00data_2/bmark$(LITE)$(OBJ) fbital00/bmark$(LITE).c

$(OBJBUILD)/fbital00data_2/fbital00$(OBJ) :                            \
                                            fbital00/algo.h
$(OBJBUILD)/fbital00data_2/fbital00$(OBJ) : fbital00/fbital00.c        \
                                            $(BMDEPS)
	$(COM) -Ifbital00 -Ifbital00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(fbital00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/fbital00data_2/fbital00$(OBJ) fbital00/fbital00.c

$(OBJBUILD)/fbital00data_2/verify$(OBJ) :                              \
                                          diffmeasure/verify.h
$(OBJBUILD)/fbital00data_2/verify$(OBJ) : diffmeasure/verify.c         \
                                          $(BMDEPS)
	$(COM) -Ifbital00 -Ifbital00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(fbital00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/fbital00data_2/verify$(OBJ) diffmeasure/verify.c

FBITAL00DATA_2 = \
    $(OBJBUILD)/fbital00data_2/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/fbital00data_2/fbital00$(OBJ) \
    $(OBJBUILD)/fbital00data_2/verify$(OBJ) 

$(BINBUILD)/fbital00data_2$(LITE)$(EXE):  $(FBITAL00DATA_2) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/fbital00data_2$(LITE)$(EXE) $(FBITAL00DATA_2) $(THLIB)  


$(OBJBUILD)/fbital00data_3/bmark$(LITE)$(OBJ) :                        \
                                                fbital00/algo.h        \
                                                fbital00/datasets/vtypbai.dat \
                                                fbital00/datasets/xtypsnri.dat \
                                                fbital00/datasets/xstepsnri.dat \
                                                fbital00/datasets/vstepbai.dat \
                                                fbital00/datasets/vpentbai.dat \
                                                fbital00/datasets/xpentsnri.dat \
                                                fbital00/datasets/allocmapi.dat
$(OBJBUILD)/fbital00data_3/bmark$(LITE)$(OBJ) : fbital00/bmark$(LITE).c \
                                                $(BMDEPS)
	$(COM) -Ifbital00 -Ifbital00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(fbital00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/fbital00data_3/bmark$(LITE)$(OBJ) fbital00/bmark$(LITE).c

$(OBJBUILD)/fbital00data_3/fbital00$(OBJ) :                            \
                                            fbital00/algo.h
$(OBJBUILD)/fbital00data_3/fbital00$(OBJ) : fbital00/fbital00.c        \
                                            $(BMDEPS)
	$(COM) -Ifbital00 -Ifbital00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(fbital00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/fbital00data_3/fbital00$(OBJ) fbital00/fbital00.c

$(OBJBUILD)/fbital00data_3/verify$(OBJ) :                              \
                                          diffmeasure/verify.h
$(OBJBUILD)/fbital00data_3/verify$(OBJ) : diffmeasure/verify.c         \
                                          $(BMDEPS)
	$(COM) -Ifbital00 -Ifbital00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(fbital00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/fbital00data_3/verify$(OBJ) diffmeasure/verify.c

FBITAL00DATA_3 = \
    $(OBJBUILD)/fbital00data_3/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/fbital00data_3/fbital00$(OBJ) \
    $(OBJBUILD)/fbital00data_3/verify$(OBJ) 

$(BINBUILD)/fbital00data_3$(LITE)$(EXE):  $(FBITAL00DATA_3) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/fbital00data_3$(LITE)$(EXE) $(FBITAL00DATA_3) $(THLIB)  


$(OBJBUILD)/fbital00data_6/bmark$(LITE)$(OBJ) :                        \
                                                fbital00/algo.h        \
                                                fbital00/datasets/vtypbai.dat \
                                                fbital00/datasets/xtypsnri.dat \
                                                fbital00/datasets/xstepsnri.dat \
                                                fbital00/datasets/vstepbai.dat \
                                                fbital00/datasets/vpentbai.dat \
                                                fbital00/datasets/xpentsnri.dat \
                                                fbital00/datasets/allocmapi.dat
$(OBJBUILD)/fbital00data_6/bmark$(LITE)$(OBJ) : fbital00/bmark$(LITE).c \
                                                $(BMDEPS)
	$(COM) -Ifbital00 -Ifbital00/datasets -Idiffmeasure -DDATA_6 -DITERATIONS=$(fbital00data_6) $(CINCS) $(OBJOUT)$(OBJBUILD)/fbital00data_6/bmark$(LITE)$(OBJ) fbital00/bmark$(LITE).c

$(OBJBUILD)/fbital00data_6/fbital00$(OBJ) :                            \
                                            fbital00/algo.h
$(OBJBUILD)/fbital00data_6/fbital00$(OBJ) : fbital00/fbital00.c        \
                                            $(BMDEPS)
	$(COM) -Ifbital00 -Ifbital00/datasets -Idiffmeasure -DDATA_6 -DITERATIONS=$(fbital00data_6) $(CINCS) $(OBJOUT)$(OBJBUILD)/fbital00data_6/fbital00$(OBJ) fbital00/fbital00.c

$(OBJBUILD)/fbital00data_6/verify$(OBJ) :                              \
                                          diffmeasure/verify.h
$(OBJBUILD)/fbital00data_6/verify$(OBJ) : diffmeasure/verify.c         \
                                          $(BMDEPS)
	$(COM) -Ifbital00 -Ifbital00/datasets -Idiffmeasure -DDATA_6 -DITERATIONS=$(fbital00data_6) $(CINCS) $(OBJOUT)$(OBJBUILD)/fbital00data_6/verify$(OBJ) diffmeasure/verify.c

FBITAL00DATA_6 = \
    $(OBJBUILD)/fbital00data_6/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/fbital00data_6/fbital00$(OBJ) \
    $(OBJBUILD)/fbital00data_6/verify$(OBJ) 

$(BINBUILD)/fbital00data_6$(LITE)$(EXE):  $(FBITAL00DATA_6) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/fbital00data_6$(LITE)$(EXE) $(FBITAL00DATA_6) $(THLIB)  


$(OBJBUILD)/fft00data_1/bmark$(LITE)$(OBJ) :                           \
                                             fft00/algo.h              \
                                             diffmeasure/verify.h      \
                                             fft00/datasets/xtpulse256i.dat \
                                             fft00/datasets/vtpulse256i.dat \
                                             fft00/datasets/xspn256i.dat \
                                             fft00/datasets/vspn256i.dat \
                                             fft00/datasets/xsine256i.dat \
                                             fft00/datasets/golden_sine.dat \
                                             fft00/datasets/cstable256i.dat \
                                             fft00/datasets/stable256i.dat \
                                             fft00/datasets/ctable256i.dat \
                                             fft00/datasets/brind256i.dat
$(OBJBUILD)/fft00data_1/bmark$(LITE)$(OBJ) : fft00/bmark$(LITE).c      \
                                             $(BMDEPS)
	$(COM) -Ifft00 -Ifft00/datasets -Idiffmeasure -DDATA_1 -DITERATIONS=$(fft00data_1) $(CINCS) $(OBJOUT)$(OBJBUILD)/fft00data_1/bmark$(LITE)$(OBJ) fft00/bmark$(LITE).c

$(OBJBUILD)/fft00data_1/fft00$(OBJ) :                                  \
                                      fft00/algo.h
$(OBJBUILD)/fft00data_1/fft00$(OBJ) : fft00/fft00.c $(BMDEPS)
	$(COM) -Ifft00 -Ifft00/datasets -Idiffmeasure -DDATA_1 -DITERATIONS=$(fft00data_1) $(CINCS) $(OBJOUT)$(OBJBUILD)/fft00data_1/fft00$(OBJ) fft00/fft00.c

$(OBJBUILD)/fft00data_1/verify$(OBJ) :                                 \
                                       diffmeasure/verify.h
$(OBJBUILD)/fft00data_1/verify$(OBJ) : diffmeasure/verify.c $(BMDEPS)
	$(COM) -Ifft00 -Ifft00/datasets -Idiffmeasure -DDATA_1 -DITERATIONS=$(fft00data_1) $(CINCS) $(OBJOUT)$(OBJBUILD)/fft00data_1/verify$(OBJ) diffmeasure/verify.c

FFT00DATA_1 = \
    $(OBJBUILD)/fft00data_1/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/fft00data_1/fft00$(OBJ) \
    $(OBJBUILD)/fft00data_1/verify$(OBJ) 

$(BINBUILD)/fft00data_1$(LITE)$(EXE):  $(FFT00DATA_1) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/fft00data_1$(LITE)$(EXE) $(FFT00DATA_1) $(THLIB)  


$(OBJBUILD)/fft00data_2/bmark$(LITE)$(OBJ) :                           \
                                             fft00/algo.h              \
                                             diffmeasure/verify.h      \
                                             fft00/datasets/xtpulse256i.dat \
                                             fft00/datasets/vtpulse256i.dat \
                                             fft00/datasets/xspn256i.dat \
                                             fft00/datasets/vspn256i.dat \
                                             fft00/datasets/xsine256i.dat \
                                             fft00/datasets/golden_sine.dat \
                                             fft00/datasets/cstable256i.dat \
                                             fft00/datasets/stable256i.dat \
                                             fft00/datasets/ctable256i.dat \
                                             fft00/datasets/brind256i.dat
$(OBJBUILD)/fft00data_2/bmark$(LITE)$(OBJ) : fft00/bmark$(LITE).c      \
                                             $(BMDEPS)
	$(COM) -Ifft00 -Ifft00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(fft00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/fft00data_2/bmark$(LITE)$(OBJ) fft00/bmark$(LITE).c

$(OBJBUILD)/fft00data_2/fft00$(OBJ) :                                  \
                                      fft00/algo.h
$(OBJBUILD)/fft00data_2/fft00$(OBJ) : fft00/fft00.c $(BMDEPS)
	$(COM) -Ifft00 -Ifft00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(fft00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/fft00data_2/fft00$(OBJ) fft00/fft00.c

$(OBJBUILD)/fft00data_2/verify$(OBJ) :                                 \
                                       diffmeasure/verify.h
$(OBJBUILD)/fft00data_2/verify$(OBJ) : diffmeasure/verify.c $(BMDEPS)
	$(COM) -Ifft00 -Ifft00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(fft00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/fft00data_2/verify$(OBJ) diffmeasure/verify.c

FFT00DATA_2 = \
    $(OBJBUILD)/fft00data_2/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/fft00data_2/fft00$(OBJ) \
    $(OBJBUILD)/fft00data_2/verify$(OBJ) 

$(BINBUILD)/fft00data_2$(LITE)$(EXE):  $(FFT00DATA_2) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/fft00data_2$(LITE)$(EXE) $(FFT00DATA_2) $(THLIB)  


$(OBJBUILD)/fft00data_3/bmark$(LITE)$(OBJ) :                           \
                                             fft00/algo.h              \
                                             diffmeasure/verify.h      \
                                             fft00/datasets/xtpulse256i.dat \
                                             fft00/datasets/vtpulse256i.dat \
                                             fft00/datasets/xspn256i.dat \
                                             fft00/datasets/vspn256i.dat \
                                             fft00/datasets/xsine256i.dat \
                                             fft00/datasets/golden_sine.dat \
                                             fft00/datasets/cstable256i.dat \
                                             fft00/datasets/stable256i.dat \
                                             fft00/datasets/ctable256i.dat \
                                             fft00/datasets/brind256i.dat
$(OBJBUILD)/fft00data_3/bmark$(LITE)$(OBJ) : fft00/bmark$(LITE).c      \
                                             $(BMDEPS)
	$(COM) -Ifft00 -Ifft00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(fft00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/fft00data_3/bmark$(LITE)$(OBJ) fft00/bmark$(LITE).c

$(OBJBUILD)/fft00data_3/fft00$(OBJ) :                                  \
                                      fft00/algo.h
$(OBJBUILD)/fft00data_3/fft00$(OBJ) : fft00/fft00.c $(BMDEPS)
	$(COM) -Ifft00 -Ifft00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(fft00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/fft00data_3/fft00$(OBJ) fft00/fft00.c

$(OBJBUILD)/fft00data_3/verify$(OBJ) :                                 \
                                       diffmeasure/verify.h
$(OBJBUILD)/fft00data_3/verify$(OBJ) : diffmeasure/verify.c $(BMDEPS)
	$(COM) -Ifft00 -Ifft00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(fft00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/fft00data_3/verify$(OBJ) diffmeasure/verify.c

FFT00DATA_3 = \
    $(OBJBUILD)/fft00data_3/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/fft00data_3/fft00$(OBJ) \
    $(OBJBUILD)/fft00data_3/verify$(OBJ) 

$(BINBUILD)/fft00data_3$(LITE)$(EXE):  $(FFT00DATA_3) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/fft00data_3$(LITE)$(EXE) $(FFT00DATA_3) $(THLIB)  


$(OBJBUILD)/viterb00data_1/bmark$(LITE)$(OBJ) :                        \
                                                viterb00/algo.h        \
                                                viterb00/datasets/getti.dat \
                                                viterb00/datasets/gett_golden.dat \
                                                viterb00/datasets/togglei.dat \
                                                viterb00/datasets/toggle_golden.dat \
                                                viterb00/datasets/onesi.dat \
                                                viterb00/datasets/ones_golden.dat \
                                                viterb00/datasets/zerosi.dat \
                                                viterb00/datasets/zeros_golden.dat
$(OBJBUILD)/viterb00data_1/bmark$(LITE)$(OBJ) : viterb00/bmark$(LITE).c \
                                                $(BMDEPS)
	$(COM) -Iviterb00 -Iviterb00/datasets -Idiffmeasure -DDATA_1 -DITERATIONS=$(viterb00data_1) $(CINCS) $(OBJOUT)$(OBJBUILD)/viterb00data_1/bmark$(LITE)$(OBJ) viterb00/bmark$(LITE).c

$(OBJBUILD)/viterb00data_1/viterb00$(OBJ) :                            \
                                            viterb00/algo.h
$(OBJBUILD)/viterb00data_1/viterb00$(OBJ) : viterb00/viterb00.c        \
                                            $(BMDEPS)
	$(COM) -Iviterb00 -Iviterb00/datasets -Idiffmeasure -DDATA_1 -DITERATIONS=$(viterb00data_1) $(CINCS) $(OBJOUT)$(OBJBUILD)/viterb00data_1/viterb00$(OBJ) viterb00/viterb00.c

$(OBJBUILD)/viterb00data_1/verify$(OBJ) :                              \
                                          diffmeasure/verify.h
$(OBJBUILD)/viterb00data_1/verify$(OBJ) : diffmeasure/verify.c         \
                                          $(BMDEPS)
	$(COM) -Iviterb00 -Iviterb00/datasets -Idiffmeasure -DDATA_1 -DITERATIONS=$(viterb00data_1) $(CINCS) $(OBJOUT)$(OBJBUILD)/viterb00data_1/verify$(OBJ) diffmeasure/verify.c

VITERB00DATA_1 = \
    $(OBJBUILD)/viterb00data_1/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/viterb00data_1/viterb00$(OBJ) \
    $(OBJBUILD)/viterb00data_1/verify$(OBJ) 

$(BINBUILD)/viterb00data_1$(LITE)$(EXE):  $(VITERB00DATA_1) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/viterb00data_1$(LITE)$(EXE) $(VITERB00DATA_1) $(THLIB)  


$(OBJBUILD)/viterb00data_2/bmark$(LITE)$(OBJ) :                        \
                                                viterb00/algo.h        \
                                                viterb00/datasets/getti.dat \
                                                viterb00/datasets/gett_golden.dat \
                                                viterb00/datasets/togglei.dat \
                                                viterb00/datasets/toggle_golden.dat \
                                                viterb00/datasets/onesi.dat \
                                                viterb00/datasets/ones_golden.dat \
                                                viterb00/datasets/zerosi.dat \
                                                viterb00/datasets/zeros_golden.dat
$(OBJBUILD)/viterb00data_2/bmark$(LITE)$(OBJ) : viterb00/bmark$(LITE).c \
                                                $(BMDEPS)
	$(COM) -Iviterb00 -Iviterb00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(viterb00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/viterb00data_2/bmark$(LITE)$(OBJ) viterb00/bmark$(LITE).c

$(OBJBUILD)/viterb00data_2/viterb00$(OBJ) :                            \
                                            viterb00/algo.h
$(OBJBUILD)/viterb00data_2/viterb00$(OBJ) : viterb00/viterb00.c        \
                                            $(BMDEPS)
	$(COM) -Iviterb00 -Iviterb00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(viterb00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/viterb00data_2/viterb00$(OBJ) viterb00/viterb00.c

$(OBJBUILD)/viterb00data_2/verify$(OBJ) :                              \
                                          diffmeasure/verify.h
$(OBJBUILD)/viterb00data_2/verify$(OBJ) : diffmeasure/verify.c         \
                                          $(BMDEPS)
	$(COM) -Iviterb00 -Iviterb00/datasets -Idiffmeasure -DDATA_2 -DITERATIONS=$(viterb00data_2) $(CINCS) $(OBJOUT)$(OBJBUILD)/viterb00data_2/verify$(OBJ) diffmeasure/verify.c

VITERB00DATA_2 = \
    $(OBJBUILD)/viterb00data_2/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/viterb00data_2/viterb00$(OBJ) \
    $(OBJBUILD)/viterb00data_2/verify$(OBJ) 

$(BINBUILD)/viterb00data_2$(LITE)$(EXE):  $(VITERB00DATA_2) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/viterb00data_2$(LITE)$(EXE) $(VITERB00DATA_2) $(THLIB)  


$(OBJBUILD)/viterb00data_3/bmark$(LITE)$(OBJ) :                        \
                                                viterb00/algo.h        \
                                                viterb00/datasets/getti.dat \
                                                viterb00/datasets/gett_golden.dat \
                                                viterb00/datasets/togglei.dat \
                                                viterb00/datasets/toggle_golden.dat \
                                                viterb00/datasets/onesi.dat \
                                                viterb00/datasets/ones_golden.dat \
                                                viterb00/datasets/zerosi.dat \
                                                viterb00/datasets/zeros_golden.dat
$(OBJBUILD)/viterb00data_3/bmark$(LITE)$(OBJ) : viterb00/bmark$(LITE).c \
                                                $(BMDEPS)
	$(COM) -Iviterb00 -Iviterb00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(viterb00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/viterb00data_3/bmark$(LITE)$(OBJ) viterb00/bmark$(LITE).c

$(OBJBUILD)/viterb00data_3/viterb00$(OBJ) :                            \
                                            viterb00/algo.h
$(OBJBUILD)/viterb00data_3/viterb00$(OBJ) : viterb00/viterb00.c        \
                                            $(BMDEPS)
	$(COM) -Iviterb00 -Iviterb00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(viterb00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/viterb00data_3/viterb00$(OBJ) viterb00/viterb00.c

$(OBJBUILD)/viterb00data_3/verify$(OBJ) :                              \
                                          diffmeasure/verify.h
$(OBJBUILD)/viterb00data_3/verify$(OBJ) : diffmeasure/verify.c         \
                                          $(BMDEPS)
	$(COM) -Iviterb00 -Iviterb00/datasets -Idiffmeasure -DDATA_3 -DITERATIONS=$(viterb00data_3) $(CINCS) $(OBJOUT)$(OBJBUILD)/viterb00data_3/verify$(OBJ) diffmeasure/verify.c

VITERB00DATA_3 = \
    $(OBJBUILD)/viterb00data_3/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/viterb00data_3/viterb00$(OBJ) \
    $(OBJBUILD)/viterb00data_3/verify$(OBJ) 

$(BINBUILD)/viterb00data_3$(LITE)$(EXE):  $(VITERB00DATA_3) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/viterb00data_3$(LITE)$(EXE) $(VITERB00DATA_3) $(THLIB)  


$(OBJBUILD)/viterb00data_4/bmark$(LITE)$(OBJ) :                        \
                                                viterb00/algo.h        \
                                                viterb00/datasets/getti.dat \
                                                viterb00/datasets/gett_golden.dat \
                                                viterb00/datasets/togglei.dat \
                                                viterb00/datasets/toggle_golden.dat \
                                                viterb00/datasets/onesi.dat \
                                                viterb00/datasets/ones_golden.dat \
                                                viterb00/datasets/zerosi.dat \
                                                viterb00/datasets/zeros_golden.dat
$(OBJBUILD)/viterb00data_4/bmark$(LITE)$(OBJ) : viterb00/bmark$(LITE).c \
                                                $(BMDEPS)
	$(COM) -Iviterb00 -Iviterb00/datasets -Idiffmeasure -DDATA_4 -DITERATIONS=$(viterb00data_4) $(CINCS) $(OBJOUT)$(OBJBUILD)/viterb00data_4/bmark$(LITE)$(OBJ) viterb00/bmark$(LITE).c

$(OBJBUILD)/viterb00data_4/viterb00$(OBJ) :                            \
                                            viterb00/algo.h
$(OBJBUILD)/viterb00data_4/viterb00$(OBJ) : viterb00/viterb00.c        \
                                            $(BMDEPS)
	$(COM) -Iviterb00 -Iviterb00/datasets -Idiffmeasure -DDATA_4 -DITERATIONS=$(viterb00data_4) $(CINCS) $(OBJOUT)$(OBJBUILD)/viterb00data_4/viterb00$(OBJ) viterb00/viterb00.c

$(OBJBUILD)/viterb00data_4/verify$(OBJ) :                              \
                                          diffmeasure/verify.h
$(OBJBUILD)/viterb00data_4/verify$(OBJ) : diffmeasure/verify.c         \
                                          $(BMDEPS)
	$(COM) -Iviterb00 -Iviterb00/datasets -Idiffmeasure -DDATA_4 -DITERATIONS=$(viterb00data_4) $(CINCS) $(OBJOUT)$(OBJBUILD)/viterb00data_4/verify$(OBJ) diffmeasure/verify.c

VITERB00DATA_4 = \
    $(OBJBUILD)/viterb00data_4/bmark$(LITE)$(OBJ) \
    $(OBJBUILD)/viterb00data_4/viterb00$(OBJ) \
    $(OBJBUILD)/viterb00data_4/verify$(OBJ) 

$(BINBUILD)/viterb00data_4$(LITE)$(EXE):  $(VITERB00DATA_4) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/viterb00data_4$(LITE)$(EXE) $(VITERB00DATA_4) $(THLIB)  


$(OBJBUILD)/diffmeasure/diffmeasure$(OBJ) :                            \
                                            diffmeasure/verify.h
$(OBJBUILD)/diffmeasure/diffmeasure$(OBJ) : diffmeasure/diffmeasure.c  \
                                            $(BMDEPS)
	$(COM) -Idiffmeasure $(CINCS) $(OBJOUT)$(OBJBUILD)/diffmeasure/diffmeasure$(OBJ) diffmeasure/diffmeasure.c

$(OBJBUILD)/diffmeasure/verify$(OBJ) :                                 \
                                       diffmeasure/verify.h
$(OBJBUILD)/diffmeasure/verify$(OBJ) : diffmeasure/verify.c $(BMDEPS)
	$(COM) -Idiffmeasure $(CINCS) $(OBJOUT)$(OBJBUILD)/diffmeasure/verify$(OBJ) diffmeasure/verify.c

DIFFMEASURE = \
    $(OBJBUILD)/diffmeasure/diffmeasure$(OBJ) \
    $(OBJBUILD)/diffmeasure/verify$(OBJ) 

$(BINBUILD)/diffmeasure$(LITE)$(EXE):  $(DIFFMEASURE) $(THOBJS) 
	$(LINK) $(EXEOUT) $(BINBUILD)/diffmeasure$(LITE)$(EXE) $(DIFFMEASURE) $(THLIB)  


targets:: \
	$(BINBUILD)/empty$(LITE)$(EXE) \
	$(BINBUILD)/autcor00data_1$(LITE)$(EXE) \
	$(BINBUILD)/autcor00data_2$(LITE)$(EXE) \
	$(BINBUILD)/autcor00data_3$(LITE)$(EXE) \
	$(BINBUILD)/conven00data_1$(LITE)$(EXE) \
	$(BINBUILD)/conven00data_2$(LITE)$(EXE) \
	$(BINBUILD)/conven00data_3$(LITE)$(EXE) \
	$(BINBUILD)/fbital00data_2$(LITE)$(EXE) \
	$(BINBUILD)/fbital00data_3$(LITE)$(EXE) \
	$(BINBUILD)/fbital00data_6$(LITE)$(EXE) \
	$(BINBUILD)/fft00data_1$(LITE)$(EXE) \
	$(BINBUILD)/fft00data_2$(LITE)$(EXE) \
	$(BINBUILD)/fft00data_3$(LITE)$(EXE) \
	$(BINBUILD)/viterb00data_1$(LITE)$(EXE) \
	$(BINBUILD)/viterb00data_2$(LITE)$(EXE) \
	$(BINBUILD)/viterb00data_3$(LITE)$(EXE) \
	$(BINBUILD)/viterb00data_4$(LITE)$(EXE) \
	$(BINBUILD)/diffmeasure$(LITE)$(EXE) 


