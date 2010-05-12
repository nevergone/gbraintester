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


/* plugin load function */
G_MODULE_EXPORT extern gboolean plugin_load ()  {
	return TRUE;
}


/* plugin unload function */
G_MODULE_EXPORT extern gboolean plugin_unload ()  {
	return TRUE;
}


/* test start function */
G_MODULE_EXPORT extern gboolean test_start ()  {
	return TRUE;
}


/* test stop function */
G_MODULE_EXPORT extern gboolean test_stop ()  {
	return TRUE;
}


/* if "test running" function */
G_MODULE_EXPORT extern gboolean test_running ()  {
	return TRUE;
}
