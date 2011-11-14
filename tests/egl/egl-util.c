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
#include "egl-util.h"

int automatic;

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
#if defined(__unix__) || defined(__unix)
	test->platform = &x11_platform;
#else
#error Not implemented for this platform!
#endif
}

EGLSurface
egl_util_create_pixmap(struct egl_state *state,
		       int w, int h, const EGLint *attribs)
{
	return state->platform->create_pixmap(state, w, h, attribs);
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

	state = test->platform->create_state();
	state->platform = test->platform;

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

	state->surf = test->platform->create_window(state);

	if (!eglMakeCurrent(state->egl_dpy,
			    state->surf, state->surf, state->ctx)) {
		fprintf(stderr, "eglMakeCurrent() failed\n");
		piglit_report_result(PIGLIT_FAIL);
	}

	result = test->platform->run(state, test);

	eglTerminate(state->egl_dpy);

	test->platform->destroy_state(state);

	piglit_report_result(result);

	return EXIT_SUCCESS;
}
