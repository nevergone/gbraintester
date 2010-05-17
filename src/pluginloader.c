/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * pluginloader.c
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

#include "pluginloader.h"


/* reading "path" directory, and results list with plugin filename */
void plugin_list_filename (const gchar *path) {
	GDir *dir;
	const gchar *filename;
	TestPlugin *PluginEntity;

	dir = g_dir_open(path, 0, NULL);
	while ((filename = g_dir_read_name(dir))) { /* get file name in directory */
		if (!g_str_has_suffix(filename, G_MODULE_SUFFIX)) /* if not module */
			continue;
		/* create plugin entity */
		PluginEntity = g_new0(TestPlugin, 1);
		/* copy filename */
		PluginEntity->filename = g_malloc0(strlen(path)+strlen(filename));
		PluginEntity->filename = g_strconcat(path, filename, NULL);
		/* append plugin list */
		PluginList = g_list_append(PluginList, PluginEntity);
	}
	g_dir_close(dir);
}


gboolean plugin_list_create () {
	gchar *homedir;
	gchar *plugindir;
	GModule *module;
	GList *plugins;

	/* if plugins not supported */
	if (!g_module_supported())  {
		return FALSE;
	}
	/* scanning $HOME/.gbraintester/plugins/ */
	homedir = g_getenv("HOME");
	if (!homedir)
		homedir = g_get_home_dir();
	plugindir = g_strconcat(homedir, PLUGIN_HOME_DIR, NULL);
	plugin_list_filename(plugindir);
	/* scanning PACKAGE_LIB_DIR"/gbraintester/plugins/ */
	plugin_list_filename(PLUGIN_LIB_DIR);
	plugins = g_list_first(PluginList);
	while (plugins) {
		/* plugin-list processing and completion */
		module = g_module_open(((TestPlugin*)(plugins->data))->filename, G_MODULE_BIND_LAZY);
		((TestPlugin*)(plugins->data))->name = g_module_name(module);
		/* store plugin function pointers */
		g_module_symbol(module, "plugin_page", (gpointer*)&((TestPlugin*)(plugins->data))->plugin_page);
		g_module_symbol(module, "plugin_about", (gpointer*)&((TestPlugin*)(plugins->data))->plugin_about);
		g_module_symbol(module, "plugin_settings", (gpointer*)&((TestPlugin*)(plugins->data))->plugin_settings);
		g_module_symbol(module, "plugin_load", (gpointer*)&((TestPlugin*)(plugins->data))->plugin_load);
		g_module_symbol(module, "plugin_unload", (gpointer*)&((TestPlugin*)(plugins->data))->plugin_unload);
		g_module_symbol(module, "plugin_timer", (gpointer*)&((TestPlugin*)(plugins->data))->plugin_timer);
		g_module_symbol(module, "test_start", (gpointer*)&((TestPlugin*)(plugins->data))->test_start);
		g_module_symbol(module, "test_stop", (gpointer*)&((TestPlugin*)(plugins->data))->test_stop);
		g_module_symbol(module, "test_running", (gpointer*)&((TestPlugin*)(plugins->data))->test_running);
		/* store plugin version and title pointer */
		g_module_symbol(module, "version", (gpointer*)&((TestPlugin*)(plugins->data))->version);
		g_module_symbol(module, "title", (gpointer*)&((TestPlugin*)(plugins->data))->title);
		/* all plugins enabled */
		((TestPlugin*)(plugins->data))->enabled = TRUE;
		g_module_close(module);
		plugins = g_list_next(plugins); /* next plugin */
	}
	g_free(plugindir);
	return TRUE;
}


/* calling enabled plugins "plugin_load" function */
gboolean plugin_loader () {
	GList *plugins;
	GModule *module;
	gboolean result = TRUE;
	GtkWidget *page = NULL, *title = NULL, *notebook = NULL;

	notebook = GTK_WIDGET (gtk_builder_get_object(builder, "ntbTestTabs"));
	plugins = g_list_first(PluginList);
	while (plugins) {
		/* if enabled plugin, open module ... */
		if (((TestPlugin*)(plugins->data))->enabled) {
			module = g_module_open(((TestPlugin*)(plugins->data))->filename, G_MODULE_BIND_LAZY);
			/* ... calling "plugin_load" function */
			if (((TestPlugin*)(plugins->data))->plugin_load) {
				result = ((TestPlugin*)(plugins->data))->plugin_load();
				if (!result) {
					/* plugin load error */
					g_warning("plugin load error");
					return FALSE;
				}
			}
			/* calling "plugin_page" function, and create test page */
			if (((TestPlugin*)(plugins->data))->plugin_page) {
				page = ((TestPlugin*)(plugins->data))->plugin_page();
				if (!page) {
					/* plugin page error */
					g_warning("plugin page error");
					return FALSE;
				}
			}
			if (((TestPlugin*)(plugins->data))->title) {
				title = gtk_label_new(((TestPlugin*)(plugins->data))->title);
				gtk_notebook_append_page(GTK_NOTEBOOK (notebook), page, title);
			}
			/* close module */
			g_module_close(module);
		}
		plugins = g_list_next(plugins); /* next plugin */
	}
	return TRUE;
}
