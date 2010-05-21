/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * positioning.h
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

#ifndef _POSITIONING_H_
#define _POSITIONING_H_


#include <stdlib.h>
#include <gtk/gtk.h>


#define UI_FILE PLUGIN_GLADE_DIR"/positioning.ui"
#define TIMER 60

G_MODULE_EXPORT const gchar title[] = "Positioning";

G_MODULE_EXPORT const gchar version[] = "0.1-dev";

GtkBuilder *builder;


G_MODULE_EXPORT GtkWidget * plugin_page ();

G_MODULE_EXPORT GtkWidget * plugin_about ();

G_MODULE_EXPORT GtkWidget * plugin_settings ();

G_MODULE_EXPORT gboolean plugin_load ();

G_MODULE_EXPORT gboolean plugin_unload ();

G_MODULE_EXPORT guint plugin_get_timer ();

G_MODULE_EXPORT void plugin_timer (guint timer_value);

G_MODULE_EXPORT gboolean test_start ();

G_MODULE_EXPORT gboolean test_stop ();

G_MODULE_EXPORT gboolean test_running ();


#endif /* _POSITIONING_H_ */
