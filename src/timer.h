/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * timer.h
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

#ifndef _TIMER_H_
#define _TIMER_H_


#include <stdlib.h>
#include <gtk/gtk.h>
#include "callbacks.h"
#include "pluginloader.h"


GtkBuilder *builder;
guint timerId;
gboolean test_running;


gboolean main_application_timer (gpointer plugin);


#endif /* _TIMER_H_ */
