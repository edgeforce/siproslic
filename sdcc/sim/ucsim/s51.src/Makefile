#
# uCsim s51.src/Makefile
#
# (c) Drotos Daniel, Talker Bt. 1997
#

# tool name
TN		= 51

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

transform	= s,x,x,

DEFS            = $(subs -DHAVE_CONFIG_H,,-DHAVE_CONFIG_H)
PICOPT		= 
CPPFLAGS        =  -I$(srcdir) -I$(top_srcdir) -I$(top_builddir) \
		  -I$(top_srcdir)/cmd.src -I$(top_srcdir)/sim.src \
		  -I$(top_srcdir)/gui.src
CFLAGS          = -Wall -Wno-overloaded-virtual -g -O2
CXXFLAGS        = -Wall -Wno-overloaded-virtual -g -O2 -ggdb -pipe $(PICOPT)
LDFLAGS         = 
SHAREDLIB	= no

SDCC		= sdcc
SDCFLAGS	= --debug --stack-after-data --model-small
SDCPPFLAGS	= 

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


EXEEXT		= 

OBJECTS_SHARED	= glob.o sim$(TN).o \
		  inc.o jmp.o mov.o logic.o arith.o bit.o \
		  timer0.o timer1.o timer2.o serial.o port.o interrupt.o \
		  wdt.o pca.o mdu.o \
		  uc51.o uc52.o uc51r.o uc89c51r.o uc251.o uc517.o \
		  uc390.o uc390hw.o uc521.o uc88x.o uc320.o uc380.o
OBJECTS_EXE	= s$(TN).o 
OBJECTS		= $(OBJECTS_SHARED) $(OBJECTS_EXE)

# short/long exe and lib name
SEN		= s$(TN)$(EXEEXT)
LEN		= ucsim_$(TN)$(EXEEXT)
SONAME		= libucsim_$(TN).so

enable_dlso	= no
dlso_ok		= no


# Compiling entire program or any subproject
# ------------------------------------------
all: checkconf otherlibs s$(TN).src


# Compiling and installing everything and runing test
# ---------------------------------------------------
install: all installdirs install_shared_lib
	$(INSTALL) $(SEN) $(DESTDIR)$(bindir)/$(SEN)
	$(STRIP) $(DESTDIR)$(bindir)/$(SEN)
	$(INSTALL) $(LEN) $(DESTDIR)$(bindir)/$(LEN)
	$(STRIP) $(DESTDIR)$(bindir)/$(LEN)


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

#parser.cc: parser.y

#plex.cc: plex.l

# My rules
# --------
.SUFFIXES: .rel

s$(TN).src: $(SEN) $(LEN) shared_lib

$(SEN): $(OBJECTS) $(top_builddir)/libcmd.a $(top_builddir)/libguiucsim.a $(top_builddir)/libsim.a $(top_builddir)/libucsimutil.a
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

$(LEN): $(OBJECTS) $(top_builddir)/libcmd.a $(top_builddir)/libguiucsim.a $(top_builddir)/libsim.a $(top_builddir)/libucsimutil.a
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

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
	$(CXX) -shared $(LDFLAGS) $(OBJECTS_SHARED) -o $@

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
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

.c.rel:
	$(SDCC) $(SDCFLAGS) $(SDCPPFLAGS) -c $<


# Remaking configuration
# ----------------------
checkconf:
	@if [ -f $(top_builddir)/devel ]; then\
	  $(MAKE) -C $(top_builddir) -f conf.mk srcdir="$(srcdir)" top_builddir="$(top_builddir)" freshconf;\
	fi

# End of s51.src/Makefile.in
