## Process this file with automake to produce Makefile.in

## Created by Anjuta

uidir = $(datadir)/gbraintester/ui
ui_DATA = gbraintester.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_LIB_DIR=\""$(libdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(GBRAINTESTER_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = gbraintester

gbraintester_SOURCES = \
	main.c \
	callbacks.c \
	callbacks.h \
	timer.c \
	timer.h

gbraintester_LDFLAGS = \
	-Wl,--export-dynamic

gbraintester_LDADD = $(GBRAINTESTER_LIBS)

EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/gbraintester
