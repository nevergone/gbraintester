/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * pluginloader.h
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

#include <string.h>
#include <gtk/gtk.h>


/* PLUGIN_HOME_DIR "/.gbraintester/plugins/" */
/* PLUGIN_LIB_DIR PACKAGE_LIB_DIR"/gbraintester/plugins/" */
#define PLUGIN_HOME_DIR G_DIR_SEPARATOR_S".gbraintester"G_DIR_SEPARATOR_S"plugins"G_DIR_SEPARATOR_S
#define PLUGIN_LIB_DIR PACKAGE_LIB_DIR G_DIR_SEPARATOR_S"gbraintester"G_DIR_SEPARATOR_S"plugins"G_DIR_SEPARATOR_S

GtkBuilder *builder;

GList *PluginList;

typedef struct _Plugin_ {
	const gchar *name; /* plugin name */
	const gchar *filename; /* plugin filename */
	const gchar *version; /* plugin version */
	const gchar *title; /* plugin tab title */
	gboolean enabled; /* if TRUE, plugin enabled */
	GtkWidget *(*plugin_page) (void); /* test page for main application */
	GtkWidget *(*plugin_about) (void); /* about window (type: GtkAboutDialog) */
	GtkWidget *(*plugin_settings) (void); /* plugin settings window */
	gboolean (*plugin_load) (void); /* plugin load function, TRUE = success */
	gboolean (*plugin_unload) (void); /* plugin unload function, TRUE = success */
	guint (*plugin_get_timer) (void); /* set plugin timer value in seconds, 0 = no timer */
	void (*plugin_timer) (guint timer_value); /* plugin timer function, timer_value: estimated time in seconds */
	gboolean (*test_start) (void); /* test start function, TRUE = success */
	gboolean (*test_stop) (void); /* test stop function, TRUE = success */
	gboolean (*test_running) (void); /* test running? TRUE = running */
} TestPlugin;


void plugin_list_filename (const gchar *path);

gboolean plugin_list_create ();

gboolean plugin_loader ();
