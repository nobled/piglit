/*
 * Copyright © 2010 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Author: Kristian Høgsberg <krh@bitplanet.net>
 */

/**
 * \file egl-util.c
 * Common framework for EGL tests.
 *
 * \author Kristian Høgsberg <krh@bitplanet.net>
 */

#include "piglit-util.h"
#include "egl-x11-util.h"

#include <X11/Xutil.h>
#include <X11/keysym.h>

static int automatic;

int depth;

void
egl_init_test(struct egl_test *test)
{
	static const char *no_extensions[] = { NULL };

	test->config_attribs = egl_default_attribs;
	test->draw = NULL;
	test->extensions = no_extensions;
	test->window_width = egl_default_window_width;
	test->window_height = egl_default_window_height;
}

EGLSurface
egl_util_create_pixmap(struct egl_state *state,
		       int width, int height, const EGLint *attribs)
{
	struct egl_x11_state *x11 = (struct egl_x11_state *)state;
	Pixmap pixmap;
	EGLSurface surf;

	pixmap = XCreatePixmap(x11->dpy, x11->win,
			       width, height, state->depth);

	surf = eglCreatePixmapSurface(state->egl_dpy, state->cfg,
				      pixmap, attribs);

	return surf;
}

static void
create_window(struct egl_x11_state *x11)
{
	struct egl_state *state = &x11->base;
	XSetWindowAttributes window_attr;
	XVisualInfo template, *vinfo;
	EGLint id;
	unsigned long mask;
	int screen = DefaultScreen(x11->dpy);
	Window root_win = RootWindow(x11->dpy, screen);
	int count;

	if (!eglGetConfigAttrib(state->egl_dpy,
				state->cfg, EGL_NATIVE_VISUAL_ID, &id)) {
		fprintf(stderr, "eglGetConfigAttrib() failed\n");
		piglit_report_result(PIGLIT_FAIL);
	}

	template.visualid = id;
	vinfo = XGetVisualInfo(x11->dpy, VisualIDMask, &template, &count);
	if (count != 1) {
		fprintf(stderr, "XGetVisualInfo() failed\n");
		piglit_report_result(PIGLIT_FAIL);
	}

	state->depth = vinfo->depth;
	window_attr.background_pixel = 0;
	window_attr.border_pixel = 0;
	window_attr.colormap = XCreateColormap(x11->dpy, root_win,
					       vinfo->visual, AllocNone);
	window_attr.event_mask =
		StructureNotifyMask | ExposureMask | KeyPressMask;
	mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;
	x11->win = XCreateWindow(x11->dpy, root_win, 0, 0,
				 state->width, state->height,
				 0, vinfo->depth, InputOutput,
				 vinfo->visual, mask, &window_attr);

	XMapWindow(x11->dpy, x11->win);

	XFree(vinfo);
}

static enum piglit_result
x11_event_loop(struct egl_state *state, const struct egl_test *test)
{
	struct egl_x11_state *x11 = (struct egl_x11_state *)state;
	XEvent event;
	enum piglit_result result = PIGLIT_FAIL;

	while (1) {
		XNextEvent (x11->dpy, &event);

		if (event.type == Expose) {
			result = test->draw(state);
			if (automatic)
				break;
		}

		if (event.type == KeyPress) {
			KeySym sym = XKeycodeToKeysym (x11->dpy,
						       event.xkey.keycode, 0);

			if (sym == XK_Escape || sym == XK_q || sym == XK_Q)
				break;
		}
	}

	return result;
}

static void
check_extensions(struct egl_state *state, const struct egl_test *test)
{
	const char *extensions;
	int i;

	extensions = eglQueryString(state->egl_dpy, EGL_EXTENSIONS);
	for (i = 0; test->extensions[i]; i++) {
		if (!strstr(extensions, test->extensions[i])) {
			fprintf(stderr, "missing extension %s\n",
				test->extensions[i]);
			piglit_report_result(PIGLIT_SKIP);
		}
	}
}

static struct egl_state *
x11_create_state(void)
{
	struct egl_x11_state *x11 = malloc(sizeof *x11);

	if (!x11) {
		fprintf(stderr, "Out of memory\n");
		piglit_report_result(PIGLIT_SKIP);
	}

	x11->dpy = XOpenDisplay(NULL);
	if (x11->dpy == NULL) {
		fprintf(stderr, "couldn't open display\n");
		piglit_report_result(PIGLIT_FAIL);
	}

	x11->base.egl_dpy = eglGetDisplay(x11->dpy);
	if (x11->base.egl_dpy == EGL_NO_DISPLAY) {
		fprintf(stderr, "eglGetDisplay() failed\n");
		piglit_report_result(PIGLIT_FAIL);
	}

	return &x11->base;
}

static void
x11_destroy_state(struct egl_state *state)
{
	struct egl_x11_state *x11 = (struct egl_x11_state*)state;

	free(x11);
}

static EGLSurface
x11_create_window(struct egl_state *state)
{
	struct egl_x11_state *x11 = (struct egl_x11_state*)state;
	EGLSurface surf;
	create_window(x11);

	surf = eglCreateWindowSurface(state->egl_dpy,
				      state->cfg, x11->win, NULL);
	if (surf == EGL_NO_SURFACE) {
		fprintf(stderr, "eglCreateWindowSurface() failed\n");
		piglit_report_result(PIGLIT_FAIL);
	}
	return surf;
}

int
egl_util_run(const struct egl_test *test, int argc, char *argv[])
{
	struct egl_state *state;
	EGLint count;
	enum piglit_result result;
	int i;

	for (i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "-auto"))
			automatic = 1;
		else
			fprintf(stderr, "Unknown option: %s\n", argv[i]);
	}

	for (count = 0; test->config_attribs[count] != EGL_NONE; count += 2) {
		if (test->config_attribs[count] == EGL_RENDERABLE_TYPE &&
		    test->config_attribs[count+1] == EGL_OPENGL_BIT) {
			eglBindAPI(EGL_OPENGL_API);
		}
	}

	state = x11_create_state();

	if (!eglInitialize(state->egl_dpy, &state->major, &state->minor)) {
		fprintf(stderr, "eglInitialize() failed\n");
		piglit_report_result(PIGLIT_FAIL);
	}

	check_extensions(state, test);

	if (!eglChooseConfig(state->egl_dpy, test->config_attribs,
	                     &state->cfg, 1, &count) || count == 0) {
		fprintf(stderr, "eglChooseConfig() failed\n");
		piglit_report_result(PIGLIT_FAIL);
	}

	state->ctx = eglCreateContext(state->egl_dpy, state->cfg,
				     EGL_NO_CONTEXT, NULL);
	if (state->ctx == EGL_NO_CONTEXT) {
		fprintf(stderr, "eglCreateContext() failed\n");
		piglit_report_result(PIGLIT_FAIL);
	}

	state->width = test->window_width;
	state->height = test->window_height;

	state->surf = x11_create_window(state);

	if (!eglMakeCurrent(state->egl_dpy,
			    state->surf, state->surf, state->ctx)) {
		fprintf(stderr, "eglMakeCurrent() failed\n");
		piglit_report_result(PIGLIT_FAIL);
	}

	result = x11_event_loop(state, test);

	eglTerminate(state->egl_dpy);

	x11_destroy_state(state);

	piglit_report_result(result);

	return EXIT_SUCCESS;
}
