# libc/pdk13 Makefile


srcdir = .
top_builddir = ../../..
abs_top_builddir = /data/pcbs/SIPROSLIC/sdcc

LIB_TYPE     = RANLIB

EXTRA_CFLAGS = -mpdk13 --max-allocs-per-node 25000
SAS = $(top_builddir)/bin/sdaspdk13

# override PORTDIR defined by super (parent) makefile
override PORTDIR = ../build/pdk13

%.rel: %.s
	@# TODO: sdas should place it\'s output in the current dir
	test $(srcdir) = . || cp $< .
	-$(AS) $(ASFLAGS) $(notdir $<)
	test $(srcdir) = . || rm $(notdir $<)

include $(srcdir)/../incl.mk

PDK13_FLOAT = $(COMMON_FLOAT)

PDK13_INT = $(COMMON_INT) \
  _muluchar.c \
  _mulschar.c \
  _mulint.c \
  _divuchar.c \
  _divschar.c \
  _divuint.c \
  _divsint.c \
  _moduchar.c \
  _modschar.c \
  _moduint.c \
  _modsint.c

PDK13_LONG = $(COMMON_LONG) \
  _divulong.c \
  _mullong.c

PDK13_LONGLONG = $(COMMON_LONGLONG) \
  _rrulonglong.c \
  _rrslonglong.c \
  _rlulonglong.c \
  _rlslonglong.c \
  _mullonglong.c \
  _divslonglong.c \
  _divulonglong.c \
  _modslonglong.c \
  _modulonglong.c

PDK13_SDCC = $(COMMON_SDCC) \
  __itoa.c \
  _startup.c \
  _strcmp.c \
  _strcpy.c \
  _strlen.c \
  _memmove.c \
  __memcpy.c \
  memcpy.c \
  div.c \
  ldiv.c \
  lldiv.c \
  sprintf.c \
  vprintf.c

PDK13SOURCES = $(addprefix ../,$(PDK13_FLOAT) $(PDK13_INT) $(PDK13_LONG) $(PDK13_LONGLONG) $(PDK13_SDCC))
PDK13OBJECTS = $(patsubst %.c,%.rel,$(PDK13_FLOAT) $(PDK13_INT) $(PDK13_LONG) $(PDK13_LONGLONG) $(PDK13_SDCC))

OBJ = __gptrget.rel __gptrget2.rel heap.rel __setjmp.rel

LIB = pdk13.lib
AS = $(SAS)
ASFLAGS = -plosgff

CFLAGS = -I$(srcdir)/../../include -I. --std-c2x

all: $(PORTDIR)/$(LIB)

$(PORTDIR)/$(LIB): $(OBJ) $(PDK13OBJECTS) Makefile
ifeq ($(LIB_TYPE), SDCCLIB)
	rm -f $@; \
	$(top_builddir)/bin/sdcclib -a $@ $(OBJ) $(PDK13OBJECTS)
else
  ifeq ($(LIB_TYPE), AR)
	$(SDAR) -rcSD $@ $(OBJ) $(PDK13OBJECTS)
  else
    ifeq ($(LIB_TYPE), RANLIB)
	$(SDAR) -rcD $@ $(OBJ) $(PDK13OBJECTS)
    else
	rm -f $@
	for i in $(basename $(OBJ) $(PDK13OBJECTS)); do echo $$i >>$@; done
	cp $(OBJ) $(PDK13OBJECTS) $(PORTDIR)
    endif
  endif
endif

clean:
	rm -f *.rel *.sym *.lst *~ $(CLEANSPEC) *.dump* *.asm *.lib

distclean: clean
	rm -f Makefile

Makefile: $(srcdir)/Makefile.in
	cd $(top_builddir); ./config.status device/lib/pdk13/Makefile
