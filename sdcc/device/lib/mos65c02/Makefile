# libc/m65c02 Makefile


srcdir = .
top_builddir = ../../..

LIB_TYPE     = RANLIB

SCC = $(top_builddir)/bin/sdcc -mm65c02
SAS = $(top_builddir)/bin/sdas6500

# override PORTDIR defined by super (parent) makefile
override PORTDIR = ../build/m65c02

include $(srcdir)/../incl.mk

M6502_FLOAT = $(COMMON_FLOAT)

M6502_INT = $(COMMON_INT) \
  _divsint.c \
  _divuint.c \
  _modsint.c \
  _moduint.c

M6502_LONG = $(COMMON_LONG) \
  _mullong.c \
  _divulong.c

M6502_LONGLONG = $(COMMON_LONGLONG) \
  _rrulonglong.c \
  _rrslonglong.c \
  _rlulonglong.c \
  _rlslonglong.c \
  _mullonglong.c \
  _divslonglong.c \
  _divulonglong.c \
  _modslonglong.c \
  _modulonglong.c

M6502_SDCC = $(COMMON_SDCC) \
  __itoa.c \
  __ltoa.c \
  __memcpy.c \
  _heap.c \
  _memmove.c \
  _spx.c \
  _startup.c \
  _strcmp.c \
  _strcpy.c \
  _strlen.c \
  div.c \
  ldiv.c \
  memcpy.c \
  sprintf.c \
  vprintf.c \
  atomic_flag_clear.c

M6502SOURCES = $(addprefix ../,$(M6502_FLOAT) $(M6502_INT) $(M6502_LONG) $(M6502_LONGLONG) $(M6502_SDCC))
M6502OBJECTS = $(patsubst %.c,%.rel,$(M6502_FLOAT) $(M6502_INT) $(M6502_LONG) $(M6502_LONGLONG) $(M6502_SDCC))

OBJ = _ret.rel _setjmp.rel atomic_flag_test_and_set.rel __sdcc_indirect_jsr.rel

LIB = m65c02.lib
CC = $(SCC)
AS = $(SAS)
ASFLAGS = -plosgff

CFLAGS = -I$(srcdir)/../../include -I. --std-c2x

all: $(PORTDIR)/$(LIB)

$(PORTDIR)/$(LIB): $(OBJ) $(M6502OBJECTS) Makefile
ifeq ($(LIB_TYPE), SDCCLIB)
	rm -f $@; \
	$(top_builddir)/bin/sdcclib -a $@ $(OBJ) $(M6502OBJECTS)
else
  ifeq ($(LIB_TYPE), AR)
	$(SDAR) -rcSD $@ $(OBJ) $(M6502OBJECTS)
  else
    ifeq ($(LIB_TYPE), RANLIB)
	$(SDAR) -rcD $@ $(OBJ) $(M6502OBJECTS)
    else
	rm -f $@
	for i in $(basename $(OBJ) $(M6502OBJECTS)); do echo $$i >>$@; done
	cp $(OBJ) $(M6502OBJECTS) $(PORTDIR)
    endif
  endif
endif

%.rel: %.c
	$(CC) $(CFLAGS) -c $<

%.rel: ../%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.rel *.sym *.lst *~ $(CLEANSPEC) *.dump* *.asm *.lib

distclean: clean
	rm -f Makefile
