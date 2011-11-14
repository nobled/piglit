
/**
 * \file egl-util.h
 * Common framework for EGL tests.
 *
 * \author Kristian Høgsberg <krh@bitplanet.net>
 */

#ifndef EGL_UTIL_H
#define EGL_UTIL_H

#include <EGL/egl.h>
#include <EGL/eglext.h>

struct egl_platform;

struct egl_state {
	EGLDisplay egl_dpy;
	EGLConfig cfg;
	EGLContext ctx;
	EGLSurface surf;
	EGLint major, minor;
	int depth;
	int width;
	int height;
	const struct egl_platform *platform;
};

struct egl_test {
	const EGLint *config_attribs;
	const char **extensions;
	enum piglit_result (*draw)(struct egl_state *state);
	EGLint window_width;
	EGLint window_height;
	const struct egl_platform *platform;
};

struct egl_platform {
	struct egl_state *(*create_state)(void);
	EGLSurface (*create_window)(struct egl_state *);
	EGLSurface (*create_pixmap)(struct egl_state *state, int w, int h,
	                            const EGLint *attribs);
	enum piglit_result (*run)(struct egl_state *, const struct egl_test *);
	void (*destroy_state)(struct egl_state *);
};

#if defined(__unix__) || defined(__unix)
extern const struct egl_platform x11_platform;
#endif

static const EGLint egl_default_attribs[] = {
	EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PIXMAP_BIT | EGL_PBUFFER_BIT,
	EGL_RED_SIZE, 1,
	EGL_GREEN_SIZE, 1,
	EGL_BLUE_SIZE, 1,
	EGL_DEPTH_SIZE, 1,
	EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
	EGL_NONE
};

static const EGLint egl_default_window_width = 300;
static const EGLint egl_default_window_height = 300;

extern int automatic;

/**
 * \brief Initialize test to default values.
 */
void
egl_init_test(struct egl_test *test);

EGLSurface
egl_util_create_pixmap(struct egl_state *state,
		       int width, int height, const EGLint *attribs);

int egl_util_run(const struct egl_test *test, int argc, char *argv[]);

#endif
