/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * timer.c
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

#include "timer.h"


/* run function by the seconds */
gboolean estimatedTime (gpointer plugin) {
	GtkWidget *lblTimer, *lblStartStop, *imgStartStop, *ntbTestTabs;
	const gchar *timer_oldtext;
	gchar timer_newtext[3];
	int timer_number, tab_id;
	GModule *module;

	lblTimer = GTK_WIDGET (gtk_builder_get_object(builder, "lblTimer"));
	timer_oldtext = gtk_label_get_text(GTK_LABEL (lblTimer));
	if (g_strcmp0(timer_oldtext, "--") != 0) { // running timer
		timer_number = atoi(timer_oldtext);
		timer_number--;
		sprintf(timer_newtext, "%d", timer_number);
		gtk_label_set_text(GTK_LABEL (lblTimer), timer_newtext);
		if (timer_number != 0) {
			gtk_label_set_text(GTK_LABEL (lblTimer), timer_newtext);
		}
		else { // ending timer
			gtk_label_set_text(GTK_LABEL (lblTimer), "--");
			timerId = 0;
			lblStartStop = GTK_WIDGET (gtk_builder_get_object(builder, "lblStartStop"));
			imgStartStop = GTK_WIDGET (gtk_builder_get_object(builder, "imgStartStop"));
			gtk_label_set_label(GTK_LABEL (lblStartStop), "Start");
			gtk_image_set_from_icon_name(GTK_IMAGE (imgStartStop),
										"gtk-yes",
										GTK_ICON_SIZE_BUTTON);
			ntbTestTabs = GTK_WIDGET (gtk_builder_get_object(builder, "ntbTestTabs"));
			g_signal_handlers_disconnect_by_func(ntbTestTabs, on_ntbTestTabs_switch_page, NULL); /* enable switch page */
			/* stop test */
			module = g_module_open(((TestPlugin*)plugin)->filename, G_MODULE_BIND_LAZY);
			if (!((TestPlugin*)plugin)->test_stop()) {
				g_warning("timer test stop error");
			}
			g_module_close(module);
			test_running = FALSE;
			ntbTestTabs = GTK_WIDGET (gtk_builder_get_object(builder, "ntbTestTabs"));
			tab_id = gtk_notebook_get_current_page(GTK_NOTEBOOK (ntbTestTabs));
			/* TODO */
			return FALSE;
		}
	}
	return TRUE; /* if TRUE, re-run this timer function */
}
