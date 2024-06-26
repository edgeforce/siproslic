
srcdir = .

LYX        = lyx
LATEX      = latex
LATEX2HTML = latex2html
PDFLATEX   = pdflatex
MAKEINDEX  = makeindex
DVIPDFM    = dvipdfm

PDFLATEXARGS = -file-line-error -halt-on-error

include ../Makefile.common

MANUAL = sdccman

all: $(MANUAL).pdf $(MANUAL).html/index.html $(MANUAL).txt

install:
	$(INSTALL) -d $(DESTDIR)$(docdir)
	cp -rf $(srcdir)/*.txt $(DESTDIR)$(docdir)
	txtfiles=`echo *.txt | grep -v '\*\.txt' || true`
	if [    $(txtfiles)               ]; then cp     $(txtfiles)    $(DESTDIR)$(docdir); fi
	if [ -f $(MANUAL).html/index.html ]; then cp -rf $(MANUAL).html $(DESTDIR)$(docdir); fi
	if [ -f $(MANUAL).pdf             ]; then cp -rf $(MANUAL).pdf  $(DESTDIR)$(docdir); fi
	rm -rf `find $(DESTDIR)$(docdir) -name .svn -type d`
	rm -f $(DESTDIR)$(docdir)/*/images.*

uninstall:
	rm -rf $(DESTDIR)$(docdir)

$(MANUAL).html/index.html: $(MANUAL).tex $(MANUAL).aux ;#$(MANUAL).ind $(MANUAL).glo
	mkdir -p $(dir $@)
	@# fixes $(LATEX2HTML) problems with two consecutive dashes for long-options: --stack-auto
	@# fixes $(LATEX2HTML) problems with \tabularnewline
	sed -e 's,-\\/-,-\\/-\\/-,g' \
	    -e 's,\\tabularnewline$$,\\\\,g' < $< > $(dir $@)$(notdir $<)
	cp $(MANUAL).aux $(dir $@)
	-cd $(dir $@); $(LATEX2HTML) -split 5 -show_section_numbers -local_icons -info "" -nosubdir $(MANUAL) $(QUIET)
	rm -f $(dir $@)WARNINGS $(dir $@)labels.pl $(dir $@)$(notdir $<) $(dir $@)$*.aux

%.html/index.html: %.tex %.aux
	mkdir -p $(dir $@)
	@# fixes $(LATEX2HTML) problems with two consecutive dashes for long-options: --stack-auto
	@# fixes $(LATEX2HTML) problems with \tabularnewline
	sed -e 's,-\\/-,-\\/-\\/-,g' \
	    -e 's,\\tabularnewline$$,\\\\,g' < $< > $(dir $@)$(notdir $<)
	cp $*.aux $(dir $@)
	-cd $(dir $@); $(LATEX2HTML) -split 0 -local_icons -info "" -nosubdir $* $(QUIET)
	rm -f $(dir $@)WARNINGS $(dir $@)labels.pl $(dir $@)$(notdir $<) $(dir $@)$*.aux

%.txt: %.lyx
	@# $(LYX) will export the file in the directory of the $(LYX) file
	@# if VPATH is used the $(LYX) file is copied first
	if [ "$(srcdir)" != "." ]; then \
	  cp -f $(srcdir)/$(notdir $<) $(srcdir)/*.svg . ; \
	fi
	$(LYX) -e text $(notdir $<);

%.pdf %.aux: %.tex %.dvi %.ind
	which $(PDFLATEX) > /dev/null && $(PDFLATEX) $* || $(DVIPDFM) $*

#%.ps:  %.pdf
#	$(DVIPS) $*

%.dvi: %.tex
	$(LATEX) $<
	@# rerun to in include aux
	$(LATEX) $<

%.tex: %.lyx
	if [ "$(srcdir)" != "." ] ; then \
	  cp -f $(srcdir)/$(notdir $^) $(srcdir)/*.svg . ; \
	fi
	echo $(VERSION) > sdcc_version
	$(LYX) -e latex $(notdir $<);

%.ind: %.dvi
	$(LATEX) $*
	# is there an index?
	if [ -f $*.idx ] ; then \
	  $(MAKEINDEX) -q $*; \
	  $(LATEX) $*; \
	  $(LATEX) $*; \
	fi
#	  -$(MAKEINDEX) -s l2hidx.ist $*; \

#%.glo: %.dvi
#	# the glossary, not implemented yet
#	# $(MAKEINDEX) -s l2hglo.ist -o $@ $<

#%.pdf %.aux: %.tex
#	$(PDFLATEX) $* $(PDFLATEXARGS)
#	[ ! -e "$*.idx" ] || $(MAKEINDEX) $* $(QUIET)
#	$(PDFLATEX) $* $(PDFLATEXARGS)
#	[ ! -e "$*.idx" ] || $(MAKEINDEX) $* $(QUIET)
#	$(PDFLATEX) $* $(PDFLATEXARGS)

archive: all
	rm -rf sdcc-doc sdcc-doc.tar.bz2
	mkdir sdcc-doc
	rsync -rCt *.pdf *.txt $(srcdir)/*.txt sdcc-doc

	for doc in $(MANUAL); do \
	  rsync -Rt $$doc.html/*.html $$doc.html/*.png $$doc.html/*.css sdcc-doc/; \
	done

	mkdir sdcc-doc/as
	rsync -rCt $(top_srcdir)/sdas/doc/* sdcc-doc/as/

	mkdir sdcc-doc/ucsim
	cd $(top_srcdir)/sim/ucsim/doc; rsync *.html *.jpg *.fig ../../../doc/sdcc-doc/ucsim/

	tar -c sdcc-doc | bzip2 -9 > sdcc-doc.tar.bz2

include $(srcdir)/clean.mk
