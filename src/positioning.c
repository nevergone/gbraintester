/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * positioning.c
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

#include "positioning.h"


/* start positioning test */
void positioning_start() {
	GtkWidget *tblPosElement;

	tblPosElement = GTK_WIDGET (gtk_builder_get_object(builder, "tblPosElement"));
	gtk_widget_set_sensitive(tblPosElement, TRUE);
}


/* stop positioning test */
void positioning_stop() {
	GtkWidget *tblPosElement;

	tblPosElement = GTK_WIDGET (gtk_builder_get_object(builder, "tblPosElement"));
	gtk_widget_set_sensitive(tblPosElement, FALSE);
}
