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
GList * plugin_list_filename (const gchar *path) {
	GError *error = NULL;
	GDir *dir;
	const gchar *filename;
	TestPlugin *PluginEntity;

	dir = g_dir_open(path, 0, &error);
	if (!dir) { /* if not success */
		g_warning("%s", error->message);
		g_error_free(error);
		return NULL;
	}
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

gboolean plugin_loader() {
	gchar *module_path;
	gchar *homedir;
	gchar *plugindir;
	GModule *module;
	gboolean module_result;
	gboolean (*module_func) (void);
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
		if (!g_module_symbol(module, "plugin_load", &((TestPlugin*)(plugins->data))->plugin_load))
		g_module_close(module);
		plugins = g_list_next(plugins); /* next plugin */
	}
	g_free(plugindir);
	return TRUE;
}
