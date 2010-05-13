/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Kurucz István 2010 <kurucz.istvan@gmail.com>
 * 
 * gbraintester is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gbraintester is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <config.h>
#include <gtk/gtk.h>


/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif


#include "callbacks.h"
#include "pluginloader.h"


/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/gbraintester/ui/gbraintester.ui" */
#define UI_FILE "src/gbraintester.ui"
	
gboolean init_program (void) {
	GtkWidget *wndMain;
	GError* error = NULL;

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file(builder, UI_FILE, &error)) {
		g_warning(_("Couldn't load builder file: %s"), error->message);
		g_error_free(error);
		return FALSE;
	}
	/* This is important */
	gtk_builder_connect_signals(builder, NULL);
	wndMain = GTK_WIDGET (gtk_builder_get_object(builder, "wndMain"));
	gtk_widget_show(wndMain);
	return TRUE;
}


int main (int argc, char *argv[]) {

#ifdef ENABLE_NLS
	bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);
#endif
	gtk_set_locale();
	gtk_init(&argc, &argv);
	if (!init_program()) {
		/* error in program initialization */
	    g_error (_("exiting"));
	    return EXIT_FAILURE;
	}
	if (!plugin_loader()) { /* plugins does not work */
	    g_error (_("module not supported"));
	    return EXIT_FAILURE;
	}
	gtk_main();
	return 0;
}
