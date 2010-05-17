# Reaction-time test
plugindir = $(libdir)/gbraintester/plugins

INCLUDES = 							\
	-I$(top_srcdir) 					\
	$(GBRAINTESTER_CFLAGS)					\
	$(DEPS_CFLAGS)	 					\
	$(WARN_CFLAGS)						\
	$(DISABLE_DEPRECATED_CFLAGS)				

CPPFLAGS =                                      \
	-DPLUGIN_GLADE_DIR=\""$(gladedir)"\"    \
	$(GBRAINTESTER_CFLAGS)

plugin_LTLIBRARIES = libreactiontime.la

libreactiontime_la_SOURCES = \
  reactiontime.c \
  reactiontime.h

libreactiontime_la_LDFLAGS = $(PLUGIN_LIBTOOL_FLAGS)

gladedir = $(datadir)/gbraintester/plugins
glade_DATA = reactiontime.ui


EXTRA_DIST = $(glade_DATA) $(plugin_in_files)

CLEANFILES = $(plugin_DATA)
