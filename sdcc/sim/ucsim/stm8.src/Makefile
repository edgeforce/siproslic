#
# uCsim stm8.src/Makefile
#
# (c) Drotos Daniel, Talker Bt. 1997
#

# tool name
TN		= stm8

STARTYEAR	= 1997

SHELL		= /bin/sh
CXX		= g++
CPP		= @CPP@
CXXCPP		= g++ -E
RANLIB		= ranlib
INSTALL		= /usr/bin/install -c
STRIP		= strip
MAKEDEP         = g++ -MM

top_builddir	= ..
top_srcdir	= ..

DEFS            = $(subs -DHAVE_CONFIG_H,,-DHAVE_CONFIG_H)
CPPFLAGS        =  -I$(srcdir) -I$(top_srcdir) -I$(top_builddir) \
		  -I$(top_srcdir)/cmd.src -I$(top_srcdir)/sim.src \
		  -I$(top_srcdir)/gui.src
CFLAGS          = -Wall -Wno-overloaded-virtual -g -O2
CXXFLAGS        = -Wall -Wno-overloaded-virtual -g -O2 -ggdb -pipe
LDFLAGS         = 
PICOPT		= 
SHAREDLIB	= no

EXEEXT          = 

LIBS		= -L$(top_builddir) -lsim -lucsimutil -lguiucsim -lcmd -lsim -lrt 
DL		= -ldl
dl_ok		= yes

prefix          = /usr/local
exec_prefix     = ${prefix}
bindir          = ${exec_prefix}/bin
libdir          = ${exec_prefix}/lib
datadir         = ${datarootdir}
datarootdir     = ${prefix}/share
includedir      = ${prefix}/include
mandir          = ${datarootdir}/man
man1dir         = $(mandir)/man1
man2dir         = $(mandir)/man2
infodir         = ${datarootdir}/info
srcdir          = .


OBJECTS_SHARED	= glob.o itc.o serial.o rst.o timer.o port.o clk.o \
		  uid.o bl.o flash.o \
		  inst.o \
		  sim$(TN).o $(TN).o
OBJECTS_EXE	= s$(TN).o
OBJECTS		= $(OBJECTS_SHARED) $(OBJECTS_EXE)

# short/long exe and lib name
SEN		= s$(TN)$(EXEEXT)
LEN		= ucsim_$(TN)$(EXEEXT)
SONAME		= libucsim_$(TN).so

enable_dlso	= no
dlso_ok		= no

STM8ASM		= 
#TEST_OBJ	= test_bit.hex test_dis.hex test_mov.hex test_jmp.hex \
#		  test_arith.hex

# Compiling entire program or any subproject
# ------------------------------------------
all: checkconf otherlibs $(TN).src

tests: $(TEST_OBJ)


# Compiling and installing everything and runing test
# ---------------------------------------------------
install: all installdirs install_shared_lib
	$(INSTALL) $(LEN) $(DESTDIR)$(bindir)/$(LEN)
	$(STRIP) $(DESTDIR)$(bindir)/$(LEN)
	rm -f $(DESTDIR)$(bindir)/$(SEN)


# Deleting all the installed files
# --------------------------------
uninstall:
	rm -f $(DESTDIR)$(bindir)/$(SEN)
	rm -f $(DESTDIR)$(bindir)/$(LEN)
	rm -f $(DESTDIR)$(libdir)/$(SONAME)


# Performing self-test
# --------------------
check: test

.PHONY:	test baseline
test:
	@$(MAKE) --no-print-directory -C test

baseline:
	@$(MAKE) --no-print-directory -C test baseline


# Performing installation test
# ----------------------------
installcheck:


# Creating installation directories
# ---------------------------------
installdirs:
	test -d $(DESTDIR)$(bindir) || $(INSTALL) -d $(DESTDIR)$(bindir)


# Creating dependencies
# ---------------------
dep: Makefile.dep

Makefile.dep: $(srcdir)/*.cc $(srcdir)/*.h
	$(MAKEDEP) $(CPPFLAGS) $(filter %.cc,$^) >Makefile.dep

-include Makefile.dep
include $(srcdir)/clean.mk

# My rules
# --------
.SUFFIXES: .asm .hex

$(TN).src: $(LEN) shared_lib

$(LEN): $(OBJECTS) $(top_builddir)/libcmd.a $(top_builddir)/libguiucsim.a $(top_builddir)/libsim.a $(top_builddir)/libucsimutil.a
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

#$(LEN): s$(TN)$(EXEEXT)
#	cp $< $@

ifeq ($(dlso_ok),yes)
shared_lib: $(top_builddir)/$(SONAME)
install_shared_lib: shared_lib
	test -d $(DESTDIR)$(libdir) || $(INSTALL) -d $(DESTDIR)$(libdir)
	$(INSTALL) $(top_builddir)/$(SONAME) $(DESTDIR)$(libdir)/$(SONAME)
else
shared_lib:
	@$(top_srcdir)/mkecho $(top_builddir) "No $(TN) shared lib made."
	@$(top_srcdir)/mkecho $(top_builddir) "(SHAREDLIB="$(SHAREDLIB)",dl_ok="$(dl_ok)",enable_dlso="$(enable_dlso)")"
install_shared_lib:
endif

$(top_builddir)/$(SONAME): $(OBJECTS_SHARED)
	$(CXX) -shared $(LDFLAGS) $(OBJECTS_SHARED) -o $(top_builddir)/s$(TN).so

otherlibs: $(top_builddir)/libcmd.a $(top_builddir)/libguiucsim.a $(top_builddir)/libsim.a $(top_builddir)/libucsimutil.a

$(top_builddir)/libcmd.a:
	$(MAKE) -C $(top_builddir)/cmd.src all

$(top_builddir)/libguiucsim.a:
	$(MAKE) -C $(top_builddir)/gui.src checkconf ucsim_lib

$(top_builddir)/libsim.a:
	$(MAKE) -C $(top_builddir)/sim.src all

$(top_builddir)/libucsimutil.a:
	$(MAKE) -C $(top_builddir) -f main.mk

.cc.o:
	$(CXX) $(CXXFLAGS) $(PICOPT) $(CPPFLAGS) $(TARGET_ARCH) -c $< -o $@

.asm.hex:
	$(STM8ASM) -l $< -o $@ -e $<.lst


# Remaking configuration
# ----------------------
checkconf:
	@if [ -f $(top_builddir)/devel ]; then\
	  $(MAKE) -C $(top_builddir) -f conf.mk srcdir="$(srcdir)" top_builddir="$(top_builddir)" freshconf;\
	fi

#bl_l15x46.hex: bl_l15x46.asc
#	$(SREC_CAT) $< -Ascii_Hex -Output $@ -Intel

#bl_l15x46.cc: bl_l15x46.asc
#	$(SREC_CAT) $< -Ascii_Hex -Output $@ -C-Array bl_l15x46 -INClude -No-CONST

#bl_s105.hex: bl_s105.asc
#	$(SREC_CAT) $< -Ascii_Hex -Output $@ -Intel

#bl_s105.cc: bl_s105.asc
#	$(SREC_CAT) $< -Ascii_Hex -Output $@ -C-Array bl_s105 -INClude -No-CONST

#bl_source: bl.cc bl.h

#bl.cc: bl_head.cc bl_l15x46.cc bl_s105.cc
#	cat bl_head.cc bl_l15x46.cc bl_s105.cc|sed 's/unsigned char/t_mem/' >$@

#bl.h: bl_l15x46.h bl_s105.h
#	cat bl_l15x46.h bl_s105.h|sed 's/unsigned char/t_mem/' >$@

# End of stm8.src/Makefile.in
