# Positioning test
plugindir = $(libdir)/gbraintester/plugins

INCLUDES = 								\
	-I$(top_srcdir) 					\
	$(DEPS_CFLAGS)	 					\
	$(WARN_CFLAGS)						\
	$(DISABLE_DEPRECATED_CFLAGS)				

plugin_LTLIBRARIES = libpositioning.la

libpositioning_la_SOURCES = positioning.c \
				positioning.h

libpositioning_la_LDFLAGS = $(PLUGIN_LIBTOOL_FLAGS)

gladedir = $(datadir)/gbraintester/glade
glade_DATA = positioning.ui


EXTRA_DIST = $(glade_DATA) $(plugin_in_files)

CLEANFILES = $(plugin_DATA)
