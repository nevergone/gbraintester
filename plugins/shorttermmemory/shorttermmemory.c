/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * shorttermmemory.c
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "shorttermmemory.h"


/* result plugin test page */
G_MODULE_EXPORT extern GtkWidget * plugin_page ()  {
	GtkBuilder *builder;
	GtkWidget *page;
	GError* error = NULL;

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file(builder, UI_FILE, &error)) {
		g_warning(_("Couldn't load builder file: %s"), error->message);
		g_error_free(error);
		return NULL;
	}
	gtk_builder_connect_signals(builder, NULL);
	page = GTK_WIDGET (gtk_builder_get_object(builder, "plugin_top"));
	return page;
}


/* result plugin about window */
G_MODULE_EXPORT extern GtkWidget * plugin_about ()  {
	return NULL;
}


/* result plugin settings window */
G_MODULE_EXPORT extern GtkWidget * plugin_settings ()  {
	return NULL;
}


/* plugin load function */
G_MODULE_EXPORT extern gboolean plugin_load ()  {
	return TRUE;
}


/* plugin unload function */
G_MODULE_EXPORT extern gboolean plugin_unload ()  {
	return TRUE;
}


/* get plugin timer value */
G_MODULE_EXPORT extern guint plugin_get_timer () {
	return TIMER;
}


/* plugin timer function */
G_MODULE_EXPORT extern void plugin_timer (guint timer_value)  {
}


/* test start function */
G_MODULE_EXPORT extern gboolean test_start ()  {
	return TRUE;
}


/* test stop function */
G_MODULE_EXPORT extern gboolean test_stop ()  {
	return TRUE;
}


/* if "test running" function */
G_MODULE_EXPORT extern gboolean test_running ()  {
	return TRUE;
}
