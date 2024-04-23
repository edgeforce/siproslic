#
# ucsim motorola.src/Makefile
#
# (c) Drotos Daniel, Talker Bt. 1997
#

STARTYEAR	= 1997

SHELL		= /bin/sh
CXX		= g++
CPP		= @CPP@
CXXCPP		= g++ -E
RANLIB		= ranlib
INSTALL	        = /usr/bin/install -c
MAKEDEP         = g++ -MM
AR		= ar

LEX		= flex
YACC		= bison -y

top_builddir	= ..
top_srcdir	= ..

DEFS            = $(subs -DHAVE_CONFIG_H,,-DHAVE_CONFIG_H)
CPPFLAGS        =  -I$(srcdir) -I$(top_srcdir) -I$(top_builddir) \
		  -I$(top_srcdir)/sim.src -I$(top_srcdir)/gui.src -I$(top_srcdir)/cmd.src
CFLAGS          = -Wall -Wno-overloaded-virtual -g -O2
CXXFLAGS        = -Wall -Wno-overloaded-virtual -g -O2 -ggdb -pipe
WINSOCK_AVAIL   = 0

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


OBJECTS         = pia.o cia.o

LOCAL_OBJECTS   = 

SOURCES         = $(addprefix $(srcdir)/, $(OBJECTS:.o=.cc))
LOCAL_SOURCES   = $(LOCAL_OBJECTS:.o=.cc)

# Compiling entire program or any subproject
# ------------------------------------------
all: checkconf motorolalib

motorola.src: all


# Compiling and installing everything and runing test
# ---------------------------------------------------
install: all installdirs


# Deleting all the installed files
# --------------------------------
uninstall:


# Performing self-test
# --------------------
check:

test:

baseline:


# Performing installation test
# ----------------------------
installcheck:


# Creating installation directories
# ---------------------------------
installdirs:


# Creating dependencies
# ---------------------
dep: $(LOCAL_SOURCES) Makefile.dep

Makefile.dep: $(SOURCES) $(LOCAL_SOURCES) $(srcdir)/*.h
	$(MAKEDEP) $(CPPFLAGS) $(SOURCES) $(LOCAL_SOURCES) >Makefile.dep

-include Makefile.dep
include $(srcdir)/clean.mk


# My rules
# --------

motorolalib: $(top_builddir)/libmotorola.a

$(top_builddir)/libmotorola.a: $(OBJECTS) $(LOCAL_OBJECTS)
	$(AR) -rc $@ $(OBJECTS) $(LOCAL_OBJECTS)
	$(RANLIB) $@

.cc.o:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $< -o $@


# Remaking configuration
# ----------------------
checkconf:
	@if [ -f $(top_builddir)/devel ]; then\
	  $(MAKE) -C $(top_builddir) -f conf.mk srcdir="$(srcdir)" top_builddir="$(top_builddir)" freshconf;\
	fi

# End of motorola.src/Makefile.in
