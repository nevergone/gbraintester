/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * reactiontime.h
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

#ifndef _REACTIONTIME_H_
#define _REACTIONTIME_H_


#include <stdlib.h>
#include <gtk/gtk.h>


#define UI_FILE PLUGIN_GLADE_DIR"/reactiontime.ui"
#define TIMER 0

G_MODULE_EXPORT extern const gchar title[] = "Reaction time";

G_MODULE_EXPORT extern const gchar version[] = "0.1-dev";

GtkBuilder *builder;


G_MODULE_EXPORT extern GtkWidget * plugin_page ();

G_MODULE_EXPORT extern GtkWidget * plugin_about ();

G_MODULE_EXPORT extern GtkWidget * plugin_settings ();

G_MODULE_EXPORT extern gboolean plugin_load ();

G_MODULE_EXPORT extern gboolean plugin_unload ();

G_MODULE_EXPORT extern guint plugin_get_timer ();

G_MODULE_EXPORT extern void plugin_timer (guint timer_value);

G_MODULE_EXPORT extern gboolean test_start ();

G_MODULE_EXPORT extern gboolean test_stop ();

G_MODULE_EXPORT extern gboolean test_running ();


#endif /* _REACTIONTIME_H_ */
