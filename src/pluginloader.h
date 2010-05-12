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

#include <gtk/gtk.h>

/* PLUGIN_HOME_DIR "/.gbraintester/plugins/" */
/* PLUGIN_LIB_DIR PACKAGE_LIB_DIR"/gbraintester/plugins/" */
#define PLUGIN_HOME_DIR G_DIR_SEPARATOR_S".gbraintester"G_DIR_SEPARATOR_S"plugins"G_DIR_SEPARATOR_S
#define PLUGIN_LIB_DIR PACKAGE_LIB_DIR G_DIR_SEPARATOR_S"gbraintester"G_DIR_SEPARATOR_S"plugins"G_DIR_SEPARATOR_S

GList *PluginList;

typedef struct _Plugin_ {
	gchar *name; /* plugin name */
	gchar *filename; /* plugin filename */
	gchar *version; /* plugin version */
	gchar *title; /* plugin tab title */
	guint timer; /* timer in seconds, 0 = no timer */
	GtkWidget *page; /* test page for main application */
	GtkWidget *about; /* about window (type: GtkAboutDialog) */
	GtkWidget *settings; /* plugin settings window */
	gboolean (*test_load) (void); /* test plugin load function, TRUE = success */
	gboolean (*test_unload) (void); /* test plugin unload function, TRUE = success */
	gboolean (*test_start) (void); /* test start function, TRUE = success */
	gboolean (*test_stop) (void); /* test stop function, TRUE = success */
	gboolean (*test_running) (void); /* test running? TRUE = running */
} TestPlugin;


GList * plugin_list_filename (const gchar *path);

gboolean plugin_loader();
