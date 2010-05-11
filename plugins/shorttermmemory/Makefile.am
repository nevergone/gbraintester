# Short-term memory test
plugindir = $(libdir)/gbraintester/plugins

INCLUDES = 								\
	-I$(top_srcdir) 					\
	$(DEPS_CFLAGS)	 					\
	$(WARN_CFLAGS)						\
	$(DISABLE_DEPRECATED_CFLAGS)				

plugin_LTLIBRARIES = libshorttermmemory.la

libshorttermmemory_la_SOURCES = shorttermmemory.c \
				shorttermmemory.h

libshorttermmemory_la_LDFLAGS = $(PLUGIN_LIBTOOL_FLAGS)

gladedir = $(datadir)/gbraintester/glade
glade_DATA = shorttermmemory.ui


EXTRA_DIST = $(glade_DATA) $(plugin_in_files)

CLEANFILES = $(plugin_DATA)
