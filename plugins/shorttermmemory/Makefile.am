# Short-term memory test
plugindir = $(libdir)/gbraintester/plugins

INCLUDES = 							\
	-I$(top_srcdir) 					\
	$(GBRAINTESTER_CFLAGS)					\
	$(DEPS_CFLAGS)	 					\
	$(WARN_CFLAGS)						\
	$(DISABLE_DEPRECATED_CFLAGS)				

plugin_LTLIBRARIES = libshorttermmemory.la

libshorttermmemory_la_SOURCES = shorttermmemory.c \
				shorttermmemory.h

libshorttermmemory_la_LDFLAGS = $(PLUGIN_LIBTOOL_FLAGS)

gladedir = $(datadir)/gbraintester/plugins
glade_DATA = shorttermmemory.ui


EXTRA_DIST = $(glade_DATA) $(plugin_in_files)

CLEANFILES = $(plugin_DATA)
