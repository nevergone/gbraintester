/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * callbacks.c
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

#include "callbacks.h"

guint timerId;


/* destroy application window */
void on_wndMain_destroy (GtkWidget *widget, gpointer data) {
	g_object_unref(builder); /* destroy GtkBuilder object */
	gtk_main_quit();
}


/* clicked About button */
void on_btnAbout_clicked (GtkButton *button, gpointer user_data) {
	GtkWidget *about;

	about = GTK_WIDGET (gtk_builder_get_object(builder, "wndAbout"));
	gtk_widget_show_all(about);
}


/* clicked Results button */
void on_btnResults_clicked (GtkButton *button, gpointer user_data) {
	GtkWidget *dialog, *toplevel;

	toplevel = gtk_widget_get_toplevel(GTK_WIDGET (button));
	dialog = gtk_message_dialog_new(GTK_WINDOW (toplevel),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE,
                                    "later ..."); /* TODO */
	/* signal: destroy dialog window */
	g_signal_connect(dialog, "response", G_CALLBACK (gtk_widget_destroy), NULL);
	gtk_widget_show(dialog);
}


/* clicked Start/Stop button */
void on_btnStartStop_clicked (GtkButton *button, gpointer user_data) {
	GtkWidget *lblStartStop, *imgStartStop, *ntbTestTabs;
	gint tab_id;
	gchar *icon_name;

	lblStartStop = GTK_WIDGET (gtk_builder_get_object(builder, "lblStartStop"));
	imgStartStop = GTK_WIDGET (gtk_builder_get_object(builder, "imgStartStop"));
	ntbTestTabs = GTK_WIDGET (gtk_builder_get_object(builder, "ntbTestTabs"));
	tab_id = gtk_notebook_get_current_page(GTK_NOTEBOOK (ntbTestTabs));
	if ((tab_id == 0) || (tab_id == 2)) { /* timer required */
		if (!timerId) {
			/* start estimatedTime() function by the seconds */
			timerId = g_timeout_add_seconds(1, (GtkFunction)estimatedTime, NULL);
		}
		else {
			/* remove timer */
			g_source_remove(timerId);
			timerId = 0;
		}
	}
	/* change icon and label */
	gtk_image_get_icon_name(GTK_IMAGE (imgStartStop), (gpointer)&icon_name, NULL); /* get icon name */
	if (g_strcmp0(icon_name, "gtk-yes") == 0) {
		gtk_label_set_label(GTK_LABEL (lblStartStop), "Stop");
		gtk_image_set_from_icon_name(GTK_IMAGE (imgStartStop),
									"gtk-stop",
									GTK_ICON_SIZE_BUTTON);
	}
	else {
		gtk_label_set_label(GTK_LABEL (lblStartStop), "Start");
		gtk_image_set_from_icon_name(GTK_IMAGE (imgStartStop),
									"gtk-yes",
									GTK_ICON_SIZE_BUTTON);
	}
}


void on_ntbTestTabs_switch_page  (GtkNotebook *notebook, GtkNotebookPage *page, guint page_num, gpointer user_data) {
	guint signal_id;
	gulong handler_id;

	signal_id = g_signal_lookup("switch-page", GTK_TYPE_NOTEBOOK); /* get signal_id */
    if (signal_id > 0) { /* if valid signal id found... */
		handler_id = g_signal_handler_find((gpointer)notebook, G_SIGNAL_MATCH_ID, signal_id, 0, 0, 0, 0);
		if (handler_id > 0) { /* if valid handler id found... */
			g_signal_handler_block((gpointer)notebook, handler_id);
			gtk_widget_show_all(GTK_WIDGET (notebook));
			gtk_notebook_set_current_page(GTK_NOTEBOOK (notebook), 0);
			g_signal_handler_unblock((gpointer)notebook, handler_id);
		}
	}
}
