# ----------------------------------------------------------------------------
# SWK - A map/reduce framework written in C++.
# Copyright (c) 2010, Jeff Hung
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
#  - Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  - Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  - Neither the name of the copyright holders nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------
# $Date$
# $Rev$
# $Author$
# ----------------------------------------------------------------------------
# revid: "@(#) $Id$"
# ----------------------------------------------------------------------------

PREFIX ?= ../output

UNAME           = $(shell uname)

BINDIR         ?= bin
SBINDIR        ?= sbin
LIBEXECDIR     ?= libexec
DATADIR        ?= share
SYSCONFDIR     ?= etc
LOCALSTATEDIR  ?= var
LIBDIR         ?= lib
INCLUDEDIR     ?= include
INFODIR        ?= info
MANDIR         ?= man

# File name prefix and extension for shared libraries
ifeq ($(UNAME),windows32)
DLL_PRE        ?=
DLL_EXT        ?= .dll
else ifeq ($(UNAME),Darwin)
DLL_PRE        ?= lib
DLL_EXT        ?= .dylib
else
DLL_PRE        ?= lib
DLL_EXT        ?= .so
endif
# File name prefix and extension for static libraries
ifeq ($(UNAME),windows32)
LIB_PRE        ?=
LIB_EXT        ?= .lib
else
LIB_PRE        ?= lib
LIB_EXT        ?= .a
endif

LIBSWK_SRCS =#
LIBSWK_SRCS += swk.config
LIBSWK_SRCS += swk.str_split

LIBSWK_TESTS =#
LIBSWK_TESTS += swk_config_test
LIBSWK_TESTS += swk_dtool_test
LIBSWK_TESTS += swk_str_split_test

LIBSWK_EXAMPLES =#
LIBSWK_EXAMPLES += mr1.wordcount
LIBSWK_EXAMPLES += mr2.wordcount
LIBSWK_EXAMPLES += mr3.wordcount

LIBSWK_STATIC_OBJS = $(foreach item,$(LIBSWK_SRCS),src/$(item).o)
LIBSWK_SHARED_OBJS = $(foreach item,$(LIBSWK_SRCS),src/$(item).lo)

#
CFLAGS_MODES      =#
#CFLAGS_MODES      += -std=c99
ifdef NDEBUG
CFLAGS_MODES      += -DNDEBUG -O3
else
CFLAGS_MODES      += -g
endif
#
CFLAGS_INC_DIRS   =#
CFLAGS_INC_DIRS   += include
ifeq ($(UNAME),FreeBSD)
CFLAGS_INC_DIRS   += /usr/local/include
endif
ifeq ($(UNAME),windows32)
CFLAGS_INC_DIRS   += "$ProgramFiles\GnuWin32\include"
endif
#
CFLAGS_DEFINES    =#
ifeq ($(UNAME),windows32)
CFLAGS_DEFINES    += _WIN32_WINNT=0x0500
endif
CFLAGS_DEFINES    += WITH_SWK_DEBUG=1
#
CFLAGS_WARNINGS   =#
CFLAGS_WARNINGS   += -Wall   # Force to show most warnings.
CFLAGS_WARNINGS   += -Werror # Force to write warning-free code.
# jeffhung.20060727:
# - In GCC, warning options below are not include in -Wall, and I think they
#   are important to code quality, too.
CFLAGS_WARNINGS   += -Wshadow
CFLAGS_WARNINGS   += -Wcast-qual
CFLAGS_WARNINGS   += -Wcast-align
CFLAGS_WARNINGS   += -Wwrite-strings
CFLAGS_WARNINGS   += -Wconversion
CFLAGS_WARNINGS   += -Wredundant-decls
# jeffhung.20080702: We need to mix C99/C++98 features.
## Issue all the warnings demanded by strict ANSI standard  C;  reject all
## programs that use forbidden extensions.
#CFLAGS_WARNINGS   += -pedantic
CXXFLAGS_MODES    =#
# jeffhung.20080702: We need to mix C99/C++98 features.
## Issue all the warnings demanded by strict ANSI standard  C;  reject all
## programs that use forbidden extensions.
#CXXFLAGS_MODES    += -pedantic
# jeffhung.20080702: We need some non-ANSI functions, such as fdopen().
#CXXFLAGS_MODES    += -std=c++98
CXXFLAGS_WARNINGS += -Woverloaded-virtual
LDFLAGS_LIB_DIRS =#
LDFLAGS_LIBS     =#
ifeq ($(UNAME),FreeBSD)
LDFLAGS_LIB_DIRS += /usr/lib
LDFLAGS_LIBS     += kvm
endif
ifeq ($(UNAME),FreeBSD)
LDFLAGS_LIB_DIRS += /usr/local/lib
LDFLAGS_LIBS     += iconv
endif
ifeq ($(UNAME),Darwin)
LDFLAGS_LIB_DIRS += /usr/lib
LDFLAGS_LIBS     += iconv
endif
ifeq ($(UNAME),windows32)
LDFLAGS_LIB_DIRS += "$ProgramFiles\GnuWin32\lib"
LDFLAGS_LIBS     += iconv
endif

CC       ?= gcc
CXX      ?= g++
CFLAGS   =#
CFLAGS   += $(CFLAGS_MODES)
CFLAGS   += $(CFLAGS_WARNINGS)
CFLAGS   += $(foreach item,$(CFLAGS_DEFINES),-D$(item))
CFLAGS   += $(foreach item,$(CFLAGS_INC_DIRS),-I$(item))
CXXFLAGS =#
CXXFLAGS += $(CFLAGS_MODES)
CXXFLAGS += $(CXXFLAGS_MODES)
CXXFLAGS += $(CFLAGS_WARNINGS)
CXXFLAGS += $(CXXFLAGS_WARNINGS)
CXXFLAGS += $(foreach item,$(CFLAGS_DEFINES),-D$(item))
CXXFLAGS += $(foreach item,$(CFLAGS_INC_DIRS),-I$(item))
LDFLAGS  =#
LDFLAGS  += $(foreach item,$(LDFLAGS_LIB_DIRS),-L$(item))
LDFLAGS  += $(foreach item,$(LDFLAGS_LIBS),-l$(item))
PRODUCTS =#
#PRODUCTS += $(LIBDIR)/$(LIB_PRE)swk$(LIB_EXT)
#PRODUCTS += $(LIBDIR)/$(DLL_PRE)swk$(DLL_EXT)
ifeq ($(UNAME),windows32)
PRODUCTS += $(foreach item,$(LIBSWK_TESTS),test/$(item).exe)
PRODUCTS += $(foreach item,$(LIBSWK_EXAMPLES),example/$(item).exe)
else
PRODUCTS += $(foreach item,$(LIBSWK_TESTS),test/$(item))
PRODUCTS += $(foreach item,$(LIBSWK_EXAMPLES),example/$(item))
endif

.SUFFIXES: .c .cpp .o .lo .cpp.srcxml

.c.o:
	$(CC) $(CFLAGS) -o $*.o -c $<

.c.lo:
# -fPIC will be ignored for target windows32, since all code is position independent
ifeq ($(UNAME),windows32)
	$(CC) $(CFLAGS) -o $*.lo -c $<
else
	$(CC) $(CFLAGS) -fPIC -o $*.lo -c $<
endif

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $*.o -c $<

.cpp.lo:
# -fPIC will be ignored for target windows32, since all code is position independent
ifeq ($(UNAME),windows32)
	$(CXX) $(CXXFLAGS) -o $*.lo -c $<
else
	$(CXX) $(CXXFLAGS) -fPIC -o $*.lo -c $<
endif

.PHONY: all
all: build

.PHONY: debug
debug:
	@echo $(VN)=$($(VN));


.PHONY: build
build: $(PRODUCTS)

.PHONY: clean
clean:
	rm -f $(PRODUCTS)
	rm -f $(LIBSWK_STATIC_OBJS)
	rm -f $(LIBSWK_SHARED_OBJS)
	rm -f $(LIBDIR)/$(DLL_PRE)swk$(DLL_EXT)
	rm -f $(LIBDIR)/$(LIB_PRE)swk$(LIB_EXT)
#	rm -f $(LIBDIR)/swk.dll
#	rm -f $(LIBDIR)/libswk.dylib
#	rm -f $(LIBDIR)/libswk.a
#	rm -f $(LIBDIR)/libswk.so
	rm -rf test/*.dSYM;
	rm -rf example/*.dSYM;

.PHONY: doc
doc:
	rm -rf doc/ref;
	doxygen;

.PHONY: test
test: $(foreach item,$(LIBSWK_TESTS),test/$(item)-run)

$(LIBDIR)/libswk.a: $(LIBDIR) $(LIBSWK_STATIC_OBJS)
ifeq ($(UNAME),Darwin)
	libtool -static -o $@ $(LIBSWK_STATIC_OBJS)
else
	ar -rvs $@ $(LIBSWK_STATIC_OBJS)
endif

$(LIBDIR)/libswk.so: $(LIBDIR) $(LIBSWK_SHARED_OBJS)
	$(CXX) -shared -Wl,-soname,libswk.so -o $@ $(LIBSWK_SHARED_OBJS)

$(LIBDIR)/swk.dll: $(LIBDIR) $(LIBSWK_SHARED_OBJS)
	$(CXX) -shared -Wl,-soname,swk.dll -Wl,--out-implib,$(LIBDIR)/libswk.a -o $@ $(LIBSWK_SHARED_OBJS)

$(LIBDIR)/libswk.dylib: $(LIBDIR) $(LIBSWK_SHARED_OBJS)
	$(CXX) -dynamiclib -o $@ $(LIBSWK_SHARED_OBJS) $(LDFLAGS)

$(BINDIR):
	mkdir -p $(BINDIR);

$(LIBDIR):
	mkdir -p $(LIBDIR);

define build_test_rule
ifdef WITH_SHARED
$(1): $(LIBDIR)/libswk$(DLL_EXT) $(1).cpp #test/cli_test_main.cpp
#	$(CXX) -DUSE_SWK_DLL $(CXXFLAGS) -o $(1) $(1).cpp test/cli_test_main.cpp -Llib -lSWK $(LDFLAGS)
	$(CXX) -DUSE_SWK_DLL $(CXXFLAGS) -o $(1) $(1).cpp                        -Llib -lSWK $(LDFLAGS)
else
$(1): $(LIBDIR)/libswk$(LIB_EXT) $(1).cpp #test/cli_test_main.cpp
ifeq ($(UNAME),Darwin)
# According to gcc(1), the -static option will not work on Mac OS X unless
# all libraries (including libgcc.a) have also been compiled with -static.
# Since neither a static version of libSystem.dylib nor crt0.o are
# provided, this option is not useful to most people.
#	$(CXX) -DUSE_SWK_LIB $(CXXFLAGS) -o $(1) $(1).cpp test/cli_test_main.cpp -Llib         -lswk $(LDFLAGS)
	$(CXX) -DUSE_SWK_LIB $(CXXFLAGS) -o $(1) $(1).cpp                        -Llib         -lswk $(LDFLAGS)
else
#	$(CXX) -DUSE_SWK_LIB $(CXXFLAGS) -o $(1) $(1).cpp test/cli_test_main.cpp -Llib -static -lswk $(LDFLAGS)
	$(CXX) -DUSE_SWK_LIB $(CXXFLAGS) -o $(1) $(1).cpp                        -Llib -static -lswk $(LDFLAGS)
endif
endif
endef

ifeq ($(UNAME),windows32)
$(foreach tp,$(LIBSWK_TESTS),$(eval $(call build_test_rule,test/$(tp).exe)))
else
$(foreach tp,$(LIBSWK_TESTS),$(eval $(call build_test_rule,test/$(tp))))
endif

define run_test_rule
$(1)-run: build $(1)
	@echo ">>> [$(1)]";
ifeq ($(UNAME),windows32)
	@$(1);
else
	@env LD_LIBRARY_PATH=$(LIBDIR) time $(1);
endif
	@echo "";
endef

ifeq ($(UNAME),windows32)
$(foreach tp,$(LIBSWK_TESTS),$(eval $(call run_test_rule,test/$(tp).exe)))
else
$(foreach tp,$(LIBSWK_TESTS),$(eval $(call run_test_rule,test/$(tp))))
endif

define build_example_rule
ifdef WITH_SHARED
$(1): $(LIBDIR)/libswk$(DLL_EXT) $(1).cpp
	$(CXX) -DUSE_SWK_DLL $(CXXFLAGS) -o $(1) $(1).cpp -Llib -lSWK $(LDFLAGS)
else
$(1): $(LIBDIR)/libswk$(LIB_EXT) $(1).cpp
ifeq ($(UNAME),Darwin)
# According to gcc(1), the -static option will not work on Mac OS X unless
# all libraries (including libgcc.a) have also been compiled with -static.
# Since neither a static version of libSystem.dylib nor crt0.o are
# provided, this option is not useful to most people.
	$(CXX) -DUSE_SWK_LIB $(CXXFLAGS) -o $(1) $(1).cpp -Llib         -lswk $(LDFLAGS)
else
	$(CXX) -DUSE_SWK_LIB $(CXXFLAGS) -o $(1) $(1).cpp -Llib -static -lswk $(LDFLAGS)
endif
endif
endef

ifeq ($(UNAME),windows32)
$(foreach tp,$(LIBSWK_EXAMPLES),$(eval $(call build_example_rule,example/$(tp).exe)))
else
$(foreach tp,$(LIBSWK_EXAMPLES),$(eval $(call build_example_rule,example/$(tp))))
endif

