/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * callbacks.h
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
#include <strings.h>


guint timerId;
gboolean test_running;
GtkBuilder *builder;

gint estimatedTime (gpointer user_data);
void short_term_memory_start();
void reaction_time_start();
void positioning_start();
void short_term_memory_stop();
void reaction_time_stop();
void positioning_stop();


void on_wndMain_destroy (GtkWidget *widget, gpointer data);

void on_btnAbout_clicked (GtkButton *button, gpointer user_data);

void on_btnResults_clicked (GtkButton *button, gpointer user_data);

void on_btnStartStop_clicked (GtkButton *button, gpointer user_data);

void on_ntbTestTabs_switch_page  (GtkNotebook *notebook, GtkNotebookPage *page, guint page_num, gpointer user_data);
