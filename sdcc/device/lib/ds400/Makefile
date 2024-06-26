# libc/ds400 Makefile


srcdir = .
top_builddir = ../../..

LIB_TYPE     = RANLIB

CC = $(top_builddir)/bin/sdcc

# override PORTDIR defined by super (parent) makefile
override PORTDIR = ../build/ds400

#VERBOSE = --verbose

OBJECTS = tinibios.rel memcpyx.rel ds400rom.rel

SOURCES = $(patsubst %.rel,%.c,$(OBJECTS))

CPPFLAGS = -I$(srcdir)/../../include -I$(srcdir)/../../include/ds400
CFLAGS = -mds400 $(CPPFLAGS) $(VERBOSE) --std-c2x

all: $(OBJECTS) $(PORTDIR)/libds400.lib

clean:
	rm -f *.lst *.rel *.sym *.cdb *.asm \#* *~ *.rst *.hex 
	rm -f *.ihx temp.lnk *.map *.lib

distclean: clean
	rm -f Makefile Makefile.dep

$(PORTDIR)/libds400.lib: $(OBJECTS)
ifeq ($(LIB_TYPE), SDCCLIB)
	rm -f $@; \
	$(top_builddir)/bin/sdcclib -a $@ $(OBJECTS)
else
  ifeq ($(LIB_TYPE), AR)
	$(SDAR) -rcSD $@ $(OBJECTS)
  else
    ifeq ($(LIB_TYPE), RANLIB)
	$(SDAR) -rcD $@ $(OBJECTS)
    else
	rm -f $@;
	for libfile in $(basename $(OBJECTS)); do echo $$libfile >>$@; done
	cp $(OBJECTS) $(PORTDIR)
    endif
  endif
endif

%.rel: %.c
	$(CC) -c $(CFLAGS) $<

# Creating dependencies
# ---------------------
depend: Makefile.dep

Makefile.dep: $(SOURCES)
	rm -f Makefile.dep
	for i in $^; do \
	  $(CC) -M $(CPPFLAGS) $$i >$${i}.dep; \
	  cat $${i}.dep >>Makefile.dep; \
	  rm $${i}.dep; \
	done

ifeq "$(findstring $(MAKECMDGOALS),clean distclean)" ""
  -include Makefile.dep
endif

Makefile: $(srcdir)/Makefile.in
	cd $(top_builddir); ./config.status device/lib/ds400/Makefile
