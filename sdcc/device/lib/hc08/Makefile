# libc/hc08 Makefile


srcdir = .
top_builddir = ../../..
abs_top_builddir = /data/pcbs/SIPROSLIC/sdcc

LIB_TYPE     = RANLIB

EXTRA_CFLAGS = -mhc08 --max-allocs-per-node 25000
SAS = $(top_builddir)/bin/sdas6808

# override PORTDIR defined by super (parent) makefile
override PORTDIR = ../build/hc08

include $(srcdir)/../incl.mk

HC08_FLOAT = $(COMMON_FLOAT)

HC08_INT = $(COMMON_INT) \
  _divsint.c \
  _divuint.c \
  _modsint.c \
  _moduint.c

HC08_LONG = $(COMMON_LONG) \
  _mullong.c \
  _divulong.c

HC08_LONGLONG = $(COMMON_LONGLONG) \
  _rrulonglong.c \
  _rrslonglong.c \
  _rlulonglong.c \
  _rlslonglong.c \
  _mullonglong.c \
  _divslonglong.c \
  _divulonglong.c \
  _modslonglong.c \
  _modulonglong.c

HC08_SDCC = $(COMMON_SDCC) \
  __itoa.c \
  __ltoa.c \
  _spx.c \
  _startup.c \
  _strcmp.c \
  _strlen.c \
  _strcpy.c \
  __memcpy.c \
  div.c \
  ldiv.c \
  memcpy.c \
  _memmove.c \
  _heap.c \
  sprintf.c \
  vprintf.c \
  atomic_flag_clear.c

HC08SOURCES = $(addprefix ../,$(HC08_FLOAT) $(HC08_INT) $(HC08_LONG) $(HC08_LONGLONG) $(HC08_SDCC))
HC08OBJECTS = $(patsubst %.c,%.rel,$(HC08_FLOAT) $(HC08_INT) $(HC08_LONG) $(HC08_LONGLONG) $(HC08_SDCC))

OBJ = _ret.rel _mulint.rel _setjmp.rel atomic_flag_test_and_set.rel

LIB = hc08.lib
AS = $(SAS)
ASFLAGS = -plosgff

CFLAGS = -I$(srcdir)/../../include -I. --std-c2x

all: $(PORTDIR)/$(LIB)

$(PORTDIR)/$(LIB): $(OBJ) $(HC08OBJECTS) Makefile
ifeq ($(LIB_TYPE), SDCCLIB)
	rm -f $@; \
	$(top_builddir)/bin/sdcclib -a $@ $(OBJ) $(HC08OBJECTS)
else
  ifeq ($(LIB_TYPE), AR)
	$(SDAR) -rcSD $@ $(OBJ) $(HC08OBJECTS)
  else
    ifeq ($(LIB_TYPE), RANLIB)
	$(SDAR) -rcD $@ $(OBJ) $(HC08OBJECTS)
    else
	rm -f $@
	for i in $(basename $(OBJ) $(HC08OBJECTS)); do echo $$i >>$@; done
	cp $(OBJ) $(HC08OBJECTS) $(PORTDIR)
    endif
  endif
endif

%.rel: %.c
	$(CC) $(CFLAGS) ${EXTRA_CFLAGS} -c $<

%.rel: ../%.c
	$(CC) $(CFLAGS) ${EXTRA_CFLAGS} -c $<

clean:
	rm -f *.rel *.sym *.lst *~ $(CLEANSPEC) *.dump* *.asm *.lib

distclean: clean
	rm -f Makefile

Makefile: $(srcdir)/Makefile.in
	cd $(top_builddir); ./config.status device/lib/hc08/Makefile
