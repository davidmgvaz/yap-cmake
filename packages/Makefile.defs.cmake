################################################################
# Share Prolog-independent bits of the package makefiles.
################################################################

.SUFFIXES: .tex .dvi .doc .pl

# This is to have a simple 'make' build `all' instead of the local
# targets.
top:	all

prefix=@prefix@
exec_prefix=@exec_prefix@
srcdir=@CMAKE_SOURCE_DIR@/packages$(PACKAGE) #TODO: remove packages hardcoded path
bindir=@bindir@
libdir=@libdir@
datarootdir = @datarootdir@
mandir=@mandir@

SHELL=@SHELL@
INSTALL=@INSTALL@
INSTALL_PROGRAM=@INSTALL_PROGRAM@
INSTALL_DATA=@INSTALL_DATA@
INSTALL_SCRIPT=@INSTALL_SCRIPT@

################################################################
# Documentation
################################################################

LATEX=latex
DOC2TEX=@abs_top_srcdir@/man/doc2tex
RUNTEX=@abs_top_srcdir@/man/runtex
TEX=$(DOC).tex $(SUBTEX)
DVI=$(DOC).dvi
PDF=$(DOC).pdf
HTML=$(DOC).html

ifneq ($(DOC),)
doc:		pdf html
pdf:		$(PDF)
html:		$(HTML)
else
doc::
		echo "No documentation provided"
pdf::
		echo "No documentation provided"
html::
		echo "No documentation provided"
endif

$(HTML):	$(TEX)
		latex2html -rootdir `pwd` -split 0 $(DOC)

$(PDF):		$(TEX)
		$(srcdir)/../../man/runtex --pdf $(DOC)

%.tex : $(srcdir)/%.doc 
		$(DOC2TEX) $< > $@

%.tex : $(srcdir)/%.txt 
		$(PUBLICPL) -f $(PLLIBDIR)/doc_latex -g "doc_latex('$<','$@',[stand_alone(false)]),halt" -t "halt(1)"

%.tex : $(srcdir)/%.pl 
		$(PLTOTEX) $< > $@ 

# Get the Prolog dialect specific part of the Makefiles

LIBSRCPL=$(addprefix $(srcdir)/, $(LIBPL))

LIBSRCALL=$(addprefix $(srcdir)/, $(LIBALL))

SRCXPCEPL=$(addprefix $(srcdir)/, $(XPCEPL))

include ../Dialect.defs

