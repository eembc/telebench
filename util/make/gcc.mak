#==============================================================================
#$RCSfile: gcc.mak,v $
#
#   DESC : GCC Tool Definition, Host Compile and Run
#
# AUTHOR : Rick Foos, ECL, LLC
#
#  EEMBC : Technical Advisory Group (TechTAG)
#
#    CVS : $Revision: 1.4 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2002 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================
# For information on the GNU Win32 project (Cygwin), and gcc
#
# http://www.cygwin.com, http://gcc.gnu.org

# ARCHITECTURE SECTION
# Any specific options 

# SYSTEM ENVIRONMENT SECTION

# Tools Root Directory
TOOLS	= /usr
# For Solaris
#TOOLS	= /usr/local

# Tools Executables, Output File Flag and Output File Types

# NOTE:	Spacing between option and values can be compiler dependant.
#		The following is a trick to ensure that a space follows the -o flag. 
#		Do not remove the line continuation backslash or the following blank
#		line.
#		OBJOUT = -o \

CC		= $(TOOLS)/bin/gcc
OBJOUT	= -o
OBJ		= .o

AS		= $(TOOLS)/bin/as

LD		= $(TOOLS)/bin/gcc
EXEOUT	= -o
EXE		= .exe

AR		= $(TOOLS)/bin/ar
LIBTYPE	= .a
LIBOUT	= 

# COMPILER SECTION

# You may need to override the Environment variable INCLUDE.
# INCLUDE is used by most compilers, and should not 
# be passed to the compiler in the makefile.
INCLUDE = $(TOOLS)/include

# -c             compile but do not link
# -o             specify the output file name
# -march=i486    generate code for the intel 486
# -O0			 Do not optimize
# -O2			 Optimize for speed

COMPILER_FLAGS	= -O2 -D NDEBUG
COMPILER_DEBUG	= -O2 -g

# -ansi          Support all ANSI standard C programs. 
#                Turns off most of the GNU extensions
# -pedantic      Issue all the warnings demanded by strict ANSI standard C;
#                reject all programs that use forbidden extensions. 
# -fno-asm       do not allow the 'asm' keyword.  Eg. no inline asembly
# -fsigned-char  use signed characters
WARNING_OPTIONS	=	\
        -ansi -pedantic -Wcomment -fno-asm -fsigned-char \
		-W -Wparentheses	\
		-Wreturn-type -Wswitch -Wunused	\
		-Wsign-compare -Wimplicit -Wreturn-type	\
		-Wshadow -Wpointer-arith -Wwrite-strings	\
		-Wsign-compare -Wstrict-prototypes -Wmissing-prototypes	\
		-Wmissing-declarations

# Additional include files not in dependancies or system include.
COMPILER_INCLUDES =

# Optional: Passed to compiler, here or in makefile to override THCFG defines.
#COMPILER_DEFINES = 

# ASSEMBLER SECTION

ASSEMBLER_FLAGS		= 
ASSEMBLER_INCLUDES	=

# LINKER SECTION
# -lm is optional. Some linkers do not include math library by default.
LINKER_FLAGS	= -lm
LINKER_INCLUDES	=

# LIBRARIAN SECTION
LIBRARY_FLAGS	= scr

# SIZE SECTION
SIZE	= $(TOOLS)/bin/size
SIZE_FLAGS		= 
AWKSZ			= $(TOOLCHAIN)
AWKDIR			= awk

# IMAGE SECTION
IMAGE			= 
IM_FLAGS		= 
IMG				= 

# CONTROL SECTION
RUN_FLAGS		= 
RUN				=
ALL_TARGETS		= mkdir targets run results

# Optional specific files for specialized run and results
PLATFORM		= x86

# Optional re-use of dependancy files generated by makerule.pl
TARGETS			= $(TOOLCHAIN)