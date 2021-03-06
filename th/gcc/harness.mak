# File generated by Makerule.pl - DO NOT EDIT
# Edit ../th/gcc/depgen.cml to change
# $Revision: 1.22 $ $Date: 2002/07/18 19:00:12 $
$(OBJBUILD)/thal$(OBJ) :                                               \
                         ../th/x86/al/eembc_dt.h ../th/x86/al/thcfg.h  \
                         ../th/src/thal.h ../th/src/thfl.h             \
                         ../th/src/thfli.h ../th/src/heap.h            \
                         ./harness.h ../th/src/thvinfo.h               \
                         ../th/x86/al/heapport.h ../th/src/thlib.h     \
                         ../th/src/therror.h
$(OBJBUILD)/thal$(OBJ) : ../th/x86/al/thal.c
	$(COM) $(OBJOUT)$(OBJBUILD)/thal$(OBJ) ../th/x86/al/thal.c

$(OBJBUILD)/anytoi$(OBJ) :                                             \
                           ../th/src/anytoi.h ../th/x86/al/eembc_dt.h  \
                           ../th/x86/al/thcfg.h ./harness.h            \
                           ../th/src/thvinfo.h
$(OBJBUILD)/anytoi$(OBJ) : ../th/src/anytoi.c
	$(COM) $(OBJOUT)$(OBJBUILD)/anytoi$(OBJ) ../th/src/anytoi.c

$(OBJBUILD)/crc$(OBJ) :                                                \
                        ../th/src/thlib.h ../th/x86/al/eembc_dt.h      \
                        ../th/src/thvinfo.h ../th/src/therror.h        \
                        ../th/x86/al/thcfg.h ./harness.h
$(OBJBUILD)/crc$(OBJ) : ../th/src/crc.c
	$(COM) $(OBJOUT)$(OBJBUILD)/crc$(OBJ) ../th/src/crc.c

$(OBJBUILD)/heap$(OBJ) :                                               \
                         ../th/x86/al/eembc_dt.h ../th/src/heap.h      \
                         ../th/src/thassert.h ../th/x86/al/thcfg.h     \
                         ./harness.h ../th/src/thvinfo.h               \
                         ../th/x86/al/heapport.h ../th/src/thlib.h     \
                         ../th/src/therror.h
$(OBJBUILD)/heap$(OBJ) : ../th/src/heap.c
	$(COM) $(OBJOUT)$(OBJBUILD)/heap$(OBJ) ../th/src/heap.c

$(OBJBUILD)/memmgr$(OBJ) :                                             \
                           ../th/src/thfl.h ../th/src/thfli.h          \
                           ../th/src/printfe.h ../th/src/thal.h        \
                           ../th/src/therror.h ../th/src/heap.h        \
                           ../th/src/ssubs.h ../th/src/memmgr.h        \
                           ../th/x86/al/thcfg.h ../th/src/thassert.h   \
                           ../th/src/thlib.h ../th/x86/al/eembc_dt.h   \
                           ../th/src/thvinfo.h ../th/x86/al/heapport.h \
                           ./harness.h
$(OBJBUILD)/memmgr$(OBJ) : ../th/src/memmgr.c
	$(COM) $(OBJOUT)$(OBJBUILD)/memmgr$(OBJ) ../th/src/memmgr.c

$(OBJBUILD)/printfe$(OBJ) :                                            \
                            ../th/x86/al/thcfg.h ../th/src/printfe.h   \
                            ./harness.h ../th/src/thvinfo.h
$(OBJBUILD)/printfe$(OBJ) : ../th/src/printfe.c
	$(COM) $(OBJOUT)$(OBJBUILD)/printfe$(OBJ) ../th/src/printfe.c

$(OBJBUILD)/ssubs$(OBJ) :                                              \
                          ../th/src/ssubs.h ../th/x86/al/eembc_dt.h    \
                          ../th/x86/al/thcfg.h ./harness.h             \
                          ../th/src/thvinfo.h
$(OBJBUILD)/ssubs$(OBJ) : ../th/src/ssubs.c
	$(COM) $(OBJOUT)$(OBJBUILD)/ssubs$(OBJ) ../th/src/ssubs.c

$(OBJBUILD)/therror$(OBJ) :                                            \
                            ../th/x86/al/eembc_dt.h                    \
                            ../th/src/therror.h ../th/x86/al/thcfg.h   \
                            ./harness.h ../th/src/thvinfo.h
$(OBJBUILD)/therror$(OBJ) : ../th/src/therror.c
	$(COM) $(OBJOUT)$(OBJBUILD)/therror$(OBJ) ../th/src/therror.c

$(OBJBUILD)/thfl$(OBJ) :                                               \
                         ../th/x86/al/thcfg.h ../th/src/thfl.h         \
                         ../th/src/thfli.h ../th/src/printfe.h         \
                         ../th/src/thal.h ../th/src/therror.h          \
                         ../th/src/heap.h ../th/src/memmgr.h           \
                         ../th/src/ssubs.h ../th/src/uuencode.h        \
                         ./harness.h ../th/src/thvinfo.h               \
                         ../th/src/thlib.h ../th/x86/al/eembc_dt.h     \
                         ../th/x86/al/heapport.h
$(OBJBUILD)/thfl$(OBJ) : ../th/src/thfl.c
	$(COM) $(OBJOUT)$(OBJBUILD)/thfl$(OBJ) ../th/src/thfl.c

$(OBJBUILD)/thlib$(OBJ) :                                              \
                          ../th/src/thfli.h ../th/src/thlib.h          \
                          ../th/src/therror.h ../th/src/printfe.h      \
                          ../th/x86/al/eembc_dt.h ../th/src/thvinfo.h  \
                          ../th/x86/al/thcfg.h ./harness.h
$(OBJBUILD)/thlib$(OBJ) : ../th/src/thlib.c
	$(COM) $(OBJOUT)$(OBJBUILD)/thlib$(OBJ) ../th/src/thlib.c

$(OBJBUILD)/uuencode$(OBJ) :                                           \
                             ../th/src/uuencode.h ../th/src/thlib.h    \
                             ../th/x86/al/eembc_dt.h                   \
                             ../th/src/thvinfo.h ../th/src/therror.h   \
                             ../th/x86/al/thcfg.h ./harness.h
$(OBJBUILD)/uuencode$(OBJ) : ../th/src/uuencode.c
	$(COM) $(OBJOUT)$(OBJBUILD)/uuencode$(OBJ) ../th/src/uuencode.c

THOBJS = \
    $(OBJBUILD)/thal$(OBJ) \
    $(OBJBUILD)/anytoi$(OBJ) \
    $(OBJBUILD)/crc$(OBJ) \
    $(OBJBUILD)/heap$(OBJ) \
    $(OBJBUILD)/memmgr$(OBJ) \
    $(OBJBUILD)/printfe$(OBJ) \
    $(OBJBUILD)/ssubs$(OBJ) \
    $(OBJBUILD)/therror$(OBJ) \
    $(OBJBUILD)/thfl$(OBJ) \
    $(OBJBUILD)/thlib$(OBJ) \
    $(OBJBUILD)/uuencode$(OBJ) 

$(OBJBUILD)/thobjs$(LITE)$(LIBTYPE):  $(THOBJS) 
	$(LIBRARY) $(LIBOUT) $(OBJBUILD)/thobjs$(LITE)$(LIBTYPE) $(THOBJS)  


targets:: \
	$(OBJBUILD)/thobjs$(LITE)$(LIBTYPE) 


