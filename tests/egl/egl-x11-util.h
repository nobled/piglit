
/**
 * \file egl-x11-util.h
 * Common framework for EGL tests specific to X11.
 *
 */

#ifndef EGL_X11_UTIL_H
#define EGL_X11_UTIL_H

#include "egl-util.h"

#include <X11/Xlib.h>

struct egl_x11_state {
	struct egl_state base;
	Display *dpy;
	Window win;
};

#endif
