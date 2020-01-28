#==============================================================================
#$RCSfile: makefile,v $
#
#   DESC : Make all app
#
# AUTHOR : Rick Foos, ECL, LLC 
#
#    CVS : $Revision: 1.14 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2002 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================
# Available commands:
#
# all - th regular, th lite build and run
# all-lite - th lite build and run
# all-regular - th regular build and run
# rerun - run and results for lite and regular
# clean - clean lite and regular for all toolchains
# distclean - clean, and delete makerule dependency files.


# Override to v2 from command line (make VER=v2)
VER=

# Automatic Override from toolchain.mak
PLATFORM=x86
TLOGTYP="_time"
SLOGTYP="_size"
THLITE="_lite"
ROOT=..
TCDIR=util/make

tchain= `ls $(TCDIR)/*.mak | sed -e 's/[^\/]*.[^\/]*.\([^\.]*\).*/\1/'`

app=8_16-bit automotive consumer networking office telecom voip

all: all-regular all-lite


.PHONY:all-regular
all-regular:
	@for j in $(tchain); do \
	for i in $(app); do \
	if [ -f "$$i/dirs$(VER)$(PLATFORM).mak" ]; then \
	cd $$i;\
	make TCDIR=$(ROOT)/$(TCDIR) VER=$(VER) TOOLCHAIN=$$j LITE= ;\
	if [ ! -f "$(ROOT)/$$j$(TLOGTYP)$(VER).log" ]; then \
	cat $(ROOT)/util/awk/titletime.txt >$(ROOT)/$$j$(TLOGTYP)$(VER).log;\
	fi; \
	cat $$j$(TLOGTYP)$(VER).log >>"$(ROOT)/$$j$(TLOGTYP)$(VER).log";\
	if [ ! -f "$(ROOT)/$$j$(SLOGTYP)$(VER).log" ]; then \
	cat $(ROOT)/util/awk/titlesize.txt >$(ROOT)/$$j$(SLOGTYP)$(VER).log;\
	fi; \
	cat $$j$(SLOGTYP)$(VER).log >>"$(ROOT)/$$j$(SLOGTYP)$(VER).log";\
	cd ..; \
	fi; \
	done; \
	done

.PHONY:all-lite
all-lite:
	@for j in $(tchain); do \
	for i in $(app); do \
	if [ -f "$$i/dirs$(VER)$(PLATFORM).mak" ]; then \
	cd $$i;\
	make TCDIR=$(ROOT)/$(TCDIR) VER=$(VER) TOOLCHAIN=$$j LITE=$(THLITE) ;\
	if [ ! -f "$(ROOT)/$$j$(TLOGTYP)$(VER)$(THLITE).log" ]; then \
	cat $(ROOT)/util/awk/titletime.txt >$(ROOT)/$$j$(TLOGTYP)$(VER)$(THLITE).log;\
	fi; \
	cat $$j$(TLOGTYP)$(VER)$(THLITE).log >>$(ROOT)/$$j$(TLOGTYP)$(VER)$(THLITE).log;\
	if [ ! -f "$(ROOT)/$$j$(SLOGTYP)$(VER)$(THLITE).log" ]; then \
	cat $(ROOT)/util/awk/titletime.txt >$(ROOT)/$$j$(SLOGTYP)$(VER)$(THLITE).log;\
	fi; \
	cat $$j$(SLOGTYP)$(VER)$(THLITE).log >>$(ROOT)/$$j$(SLOGTYP)$(VER)$(THLITE).log;\
	cd ..; \
	fi; \
	done; \
	done

clean:
	@for j in $(tchain); do \
	for i in $(app); do \
	if [ -f "$$i/dirs$(VER)$(PLATFORM).mak" ]; then \
	cd $$i;\
	make TCDIR=$(ROOT)/$(TCDIR) VER=$(VER) TOOLCHAIN=$$j LITE=$(THLITE) clean;\
	make TCDIR=$(ROOT)/$(TCDIR) VER=$(VER) TOOLCHAIN=$$j LITE=      clean;\
	cd ..; \
	fi; \
	done; \
	done

distclean:
	@for j in $(tchain); do \
	for i in $(app); do \
	if [ -f "$$i/dirs$(VER)$(PLATFORM).mak" ]; then \
	cd $$i;\
	make TCDIR=$(ROOT)/$(TCDIR) VER=$(VER) TOOLCHAIN=$$j LITE=$(THLITE) distclean;\
	make TCDIR=$(ROOT)/$(TCDIR) VER=$(VER) TOOLCHAIN=$$j LITE=      distclean;\
	cd ..; \
	fi; \
	done; \
	done

rerun:
	@for j in $(tchain); do \
	for i in $(app); do \
	if [ -f "$$i/dirs$(VER)$(PLATFORM).mak" ]; then \
	cd $$i;\
	make TCDIR=$(ROOT)/$(TCDIR) VER=$(VER) TOOLCHAIN=$$j LITE=$(THLITE) rerun;\
	make TCDIR=$(ROOT)/$(TCDIR) VER=$(VER) TOOLCHAIN=$$j LITE=      rerun;\
	cd ..; \
	fi; \
	done; \
	done

harness:
	@for j in $(tchain); do \
	for i in $(app); do \
	if [ -f "$$i/dirs$(VER)$(PLATFORM).mak" ]; then \
	cd $$i;\
	make TCDIR=$(ROOT)/$(TCDIR) VER=$(VER) TOOLCHAIN=$$j LITE=$(THLITE) harness;\
	make TCDIR=$(ROOT)/$(TCDIR) VER=$(VER) TOOLCHAIN=$$j LITE=      harness;\
	cd ..; \
	fi; \
	done; \
	done

