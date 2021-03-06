/* -*- mode: c; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*-
 *
 * Conky, a system monitor, based on torsmo
 *
 * Please see COPYING for details
 *
 * Copyright (c) 2005-2010 Brenden Matthews, et. al.
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _CONKY_IMBLI2_H_
#define _CONKY_IMBLI2_H_

#include <X11/Xlib.h>

void cimlib_add_image(const char *name);
void cimlib_set_cache_size(long size);
void cimlib_set_cache_flush_interval(long interval);
void cimlib_init(Display *display, Window drawable, Visual *visual, Colormap colourmap);
void cimlib_deinit(void);
void cimlib_render(int x, int y, int width, int height);
void cimlib_cleanup(void);

#endif /* _CONKY_IMBLI2_H_ */
