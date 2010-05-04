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
	GtkWidget *lblStartStop, *imgStartStop;

	lblStartStop = GTK_WIDGET (gtk_builder_get_object(builder, "lblStartStop"));
	imgStartStop = GTK_WIDGET (gtk_builder_get_object(builder, "imgStartStop"));
	if (!timerId) {
		/* start estimatedTime() function by the seconds */
		timerId = g_timeout_add_seconds(1, (GtkFunction)estimatedTime, NULL);
		/* change icon and label */
		gtk_label_set_label(GTK_LABEL (lblStartStop), "Stop");
		gtk_image_set_from_icon_name(GTK_IMAGE (imgStartStop),
									"gtk-stop",
									GTK_ICON_SIZE_BUTTON);
	}
	else {
		/* remove timer */
		g_source_remove(timerId);
		timerId = 0;
		/* change icon and label */
		gtk_label_set_label(GTK_LABEL (lblStartStop), "Start");
		gtk_image_set_from_icon_name(GTK_IMAGE (imgStartStop),
									"gtk-yes",
									GTK_ICON_SIZE_BUTTON);
	}
}
