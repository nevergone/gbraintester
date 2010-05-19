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
	GtkWidget *lblStartStop, *imgStartStop, *ntbTestTabs, *lblTimer, *plugin_page;
	gint tab_id;
	TestPlugin *plugin;
	GModule *module;
	guint timer_value;
	gchar text[5];

	lblStartStop = GTK_WIDGET (gtk_builder_get_object(builder, "lblStartStop"));
	imgStartStop = GTK_WIDGET (gtk_builder_get_object(builder, "imgStartStop"));
	ntbTestTabs = GTK_WIDGET (gtk_builder_get_object(builder, "ntbTestTabs"));
	lblTimer = GTK_WIDGET (gtk_builder_get_object(builder, "lblTimer"));
	tab_id = gtk_notebook_get_current_page(GTK_NOTEBOOK (ntbTestTabs));
	plugin_page = gtk_notebook_get_nth_page(GTK_NOTEBOOK (ntbTestTabs), tab_id); /* get current tab page widget */
	/* get active plugin descriptor and plugin */
	plugin = (TestPlugin*)g_object_get_data(G_OBJECT (plugin_page), "plugin-data");
	module = g_module_open(plugin->filename, G_MODULE_BIND_LAZY);
	timer_value = plugin->plugin_get_timer();
	if (timer_value != 0) { /* timer required */
		if (!timerId) {
			g_sprintf(text, "%u", timer_value);
			gtk_label_set_text(GTK_LABEL (lblTimer), text);
			/* start main_application_timer() function by the seconds */
			timerId = g_timeout_add_seconds(1, (GtkFunction)main_application_timer, plugin);
		}
		else {
			/* remove timer */
			g_source_remove(timerId);
			timerId = 0;
			gtk_label_set_text(GTK_LABEL (lblTimer), "--");
		}
	}
	/* change icon and label and start/stop test */
	if (!test_running) {
		test_running = TRUE;
		gtk_label_set_label(GTK_LABEL (lblStartStop), "Stop");
		gtk_image_set_from_icon_name(GTK_IMAGE (imgStartStop),
									"gtk-stop",
									GTK_ICON_SIZE_BUTTON);
		g_signal_connect(ntbTestTabs, "switch-page", G_CALLBACK (on_ntbTestTabs_switch_page), NULL); /* signal connect */
		/* start test */
		if (!plugin->test_start()) {
			g_warning("test start error");
		}
		/* TODO */
	}
	else {
		test_running = FALSE;
		gtk_label_set_label(GTK_LABEL (lblStartStop), "Start");
		gtk_image_set_from_icon_name(GTK_IMAGE (imgStartStop),
									"gtk-yes",
									GTK_ICON_SIZE_BUTTON);
		g_signal_handlers_disconnect_by_func(ntbTestTabs, on_ntbTestTabs_switch_page, NULL); /* enable switch page */
		/* stop test */
		if (!plugin->test_stop()) {
			g_warning("test stop error");
		}
		/* TODO */
	}
	g_module_close(module);
}


/* GtkNotebook switch-page signal handler */
void on_ntbTestTabs_switch_page (GtkNotebook *notebook, GtkNotebookPage *page, guint page_num, gpointer user_data) {
	g_signal_stop_emission_by_name(notebook, "switch-page"); /* stop signal emission: disable switch page */
}
