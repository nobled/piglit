/*
 * Copyright © 2009-2011 Intel Corporation
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
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *
 */

/** @file fbo-clear-formats.c
 *
 * Tests that glClear works correctly on all levels of 2D
 * texture-based FBOs of various internalformats.
 */

#include <stdbool.h>
#include "piglit-util.h"
#include "fbo-formats.h"

#define TEX_WIDTH 256
#define TEX_HEIGHT 256
int piglit_width = 700;
int piglit_height = 300;
int piglit_window_mode = GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA;

static const struct test_desc *test_set;
static int test_index;
static int format_index;

static GLboolean
supported(const struct test_desc *test)
{
	unsigned i;

	for (i = 0; i < 3; i++) {
		if (test->ext[i]) {
			if (!glutExtensionSupported(test->ext[i])) {
				return GL_FALSE;
			}
		}
	}

	return GL_TRUE;
}

static void
key_func(unsigned char key, int x, int y)
{
	switch (key) {
	case 'n': /* next test set */
		do {
			test_index++;
			if (test_index >= ARRAY_SIZE(test_sets)) {
				test_index = 0;
			}
		} while (!supported(&test_sets[test_index]));
		format_index = 0;
		printf("Using test set: %s\n", test_sets[test_index].param);
		break;

	case 'N': /* previous test set */
		do {
			test_index--;
			if (test_index < 0) {
				test_index = ARRAY_SIZE(test_sets) - 1;
			}
		} while (!supported(&test_sets[test_index]));
		format_index = 0;
		printf("Using test set: %s\n", test_sets[test_index].param);
		break;

	case 'm': /* next format */
		format_index++;
		if (format_index >= test_sets[test_index].num_formats) {
			format_index = 0;
		}
		break;

	case 'M': /* previous format */
		format_index--;
		if (format_index < 0) {
			format_index = test_sets[test_index].num_formats - 1;
		}
		break;
	}

	piglit_escape_exit_key(key, x, y);
}

/* Do piglit_rgbw_texture() image but using glClear */
static bool
do_rgba_clear(GLenum format, GLuint tex, int level, int size)
{
	float red[4]   = {1.0, 0.0, 0.0, 0.0};
	float green[4] = {0.0, 1.0, 0.0, 0.25};
	float blue[4]  = {0.0, 0.0, 1.0, 0.5};
	float white[4] = {1.0, 1.0, 1.0, 1.0};
	float *color;
	GLuint fb;
	GLenum status;

	glGenFramebuffersEXT(1, &fb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
				  GL_COLOR_ATTACHMENT0_EXT,
				  GL_TEXTURE_2D,
				  tex,
				  level);

	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if (status != GL_FRAMEBUFFER_COMPLETE_EXT) {
		printf("FBO incomplete\n");
		return false;
	}

	/* Handle the small sizes of compressed mipmap blocks */
	switch (format) {
	case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
	case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
	case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
	case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
	case GL_COMPRESSED_RGB_FXT1_3DFX:
	case GL_COMPRESSED_RGBA_FXT1_3DFX:
		if (size == 4)
			color = red;
		else if (size == 2)
			color = green;
		else if (size == 1)
			color = blue;
		glClearColor(color[0], color[1], color[2], color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		return true;
	}

	glEnable(GL_SCISSOR_TEST);

	glScissor(0, 0, size / 2, size / 2);
	glClearColor(red[0], red[1], red[2], red[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	glScissor(size / 2, 0, size / 2, size / 2);
	glClearColor(green[0], green[1], green[2], green[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	glScissor(0, size / 2, size / 2, size / 2);
	glClearColor(blue[0], blue[1], blue[2], blue[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	glScissor(size / 2, size / 2, size / 2, size / 2);
	glClearColor(white[0], white[1], white[2], white[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	glDisable(GL_SCISSOR_TEST);

	glDeleteFramebuffersEXT(1, &fb);

	return true;
}

static bool
do_depth_clear(GLenum format, GLuint tex, int level, int size)
{
	/* XXX: FINISHME */
	return false;
}

static bool
create_tex(GLenum internalformat, GLenum baseformat)
{
	GLuint tex;
	int level, dim;
	GLenum type, format;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	if (baseformat == GL_DEPTH_COMPONENT) {
		format = GL_DEPTH_COMPONENT;
		type = GL_FLOAT;
	} else if (baseformat == GL_DEPTH_STENCIL) {
		format = GL_DEPTH_STENCIL_EXT;
		type = GL_UNSIGNED_INT_24_8_EXT;
	} else {
		format = GL_RGBA;
		type = GL_FLOAT;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_NEAREST);

	for (level = 0, dim = TEX_WIDTH; dim > 0; level++, dim /= 2) {
		glTexImage2D(GL_TEXTURE_2D, level, internalformat,
			     dim, dim,
			     0,
			     format, type, NULL);
	}

	for (level = 0, dim = TEX_WIDTH; dim > 0; level++, dim /= 2) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, level);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, level);

		if (baseformat == GL_DEPTH_COMPONENT ||
		    baseformat == GL_DEPTH_STENCIL) {
			if (!do_depth_clear(format, tex, level, dim)) {
				glDeleteTextures(1, &tex);
				return 0;
			}
		} else {
			if (!do_rgba_clear(format, tex, level, dim)) {
				glDeleteTextures(1, &tex);
				return 0;
			}
		}
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, level - 1);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);

	assert(glGetError() == 0);
	return tex;
}

static void
draw_mipmap(int x, int y, int dim)
{
	glViewport(0, 0, piglit_width, piglit_height);
	piglit_ortho_projection(piglit_width, piglit_height, GL_FALSE);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	piglit_draw_rect_tex(x, y, dim, dim,
			     0, 0, 1, 1);

	glDisable(GL_TEXTURE_2D);
}

static GLboolean
test_mipmap_drawing(int x, int y, int dim, int level, GLuint internalformat)
{
	GLboolean pass = GL_TRUE;
	int half = dim / 2;
	int x1 = x, y1 = y, x2 = x + half, y2 = y + half;
	float r[] = {1, 0, 0, 0};
	float g[] = {0, 1, 0, 0.25};
	float b[] = {0, 0, 1, 0.5};
	float w[] = {1, 1, 1, 1};
	GLint r_size, g_size, b_size, l_size, a_size, d_size, i_size;
	GLint compressed;

	glGetTexLevelParameteriv(GL_TEXTURE_2D, level,
				 GL_TEXTURE_COMPRESSED, &compressed);
	if (compressed && dim < 8)
		return GL_TRUE;

	glGetTexLevelParameteriv(GL_TEXTURE_2D, level,
				 GL_TEXTURE_DEPTH_SIZE, &d_size);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, level,
				 GL_TEXTURE_LUMINANCE_SIZE, &l_size);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, level,
				 GL_TEXTURE_ALPHA_SIZE, &a_size);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, level,
				 GL_TEXTURE_INTENSITY_SIZE, &i_size);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, level,
				 GL_TEXTURE_RED_SIZE, &r_size);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, level,
				 GL_TEXTURE_GREEN_SIZE, &g_size);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, level,
				 GL_TEXTURE_BLUE_SIZE, &b_size);

	if (d_size) {
		for (x1 = x; x1 < x + dim; x1++) {
			float val = (x1 - x + 0.5) / (dim);
			float color[3] = {val, val, val};
			pass = pass && piglit_probe_rect_rgb(x1, y, 1, dim,
							     color);
		}
		return pass;
	}

	if (i_size || l_size) {
		r[0] = 1.0;
		r[1] = 1.0;
		r[2] = 1.0;

		g[0] = 0.0;
		g[1] = 0.0;
		g[2] = 0.0;

		b[0] = 0.0;
		b[1] = 0.0;
		b[2] = 0.0;

		if (i_size) {
			r[3] = 1.0;
			g[3] = 0.0;
			b[3] = 0.0;
		} else if (l_size && !a_size) {
			r[3] = 1.0;
			g[3] = 1.0;
			b[3] = 1.0;
			w[3] = 1.0;
		}
	} else if (a_size && !r_size && !l_size) {
		r[0] = 1.0;
		r[1] = 1.0;
		r[2] = 1.0;
		g[0] = 1.0;
		g[1] = 1.0;
		g[2] = 1.0;
		b[0] = 1.0;
		b[1] = 1.0;
		b[2] = 1.0;
	} else {
		if (!r_size) {
			r[0] = 0.0;
			w[0] = 0.0;
		}

		if (!g_size) {
			g[1] = 0.0;
			w[1] = 0.0;
		}

		if (!b_size) {
			b[2] = 0.0;
			w[2] = 0.0;
		}
		if (!a_size) {
			r[3] = 1.0;
			g[3] = 1.0;
			b[3] = 1.0;
			w[3] = 1.0;
		}
	}

	/* Clamp the bits for the framebuffer, except we aren't checking
	 * the actual framebuffer bits.
	 */
	if (l_size > 8)
		l_size = 8;
	if (i_size > 8)
		i_size = 8;
	if (r_size > 8)
		r_size = 8;
	if (g_size > 8)
		g_size = 8;
	if (b_size > 8)
		b_size = 8;
	if (a_size > 8)
		a_size = 8;

	if (d_size) {
		piglit_set_tolerance_for_bits(8, 8, 8, 8);
	} else if (i_size) {
		piglit_set_tolerance_for_bits(i_size, i_size, i_size, i_size);
	} else if (l_size) {
		piglit_set_tolerance_for_bits(l_size, l_size, l_size, a_size);
	} else {
		piglit_set_tolerance_for_bits(r_size, g_size, b_size, a_size);
	}

	if (internalformat == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ||
	    internalformat == GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT) {
		/* If alpha in DXT1 is < 0.5, the whole pixel should be black. */
		r[0] = r[1] = r[2] = r[3] = 0;
		g[0] = g[1] = g[2] = g[3] = 0;
		/* If alpha in DXT1 is >= 0.5, it should be white. */
		b[3] = 1;
	}

	pass = pass && piglit_probe_rect_rgba(x1, y1, half, half, r);
	pass = pass && piglit_probe_rect_rgba(x2, y1, half, half, g);
	pass = pass && piglit_probe_rect_rgba(x1, y2, half, half, b);
	pass = pass && piglit_probe_rect_rgba(x2, y2, half, half, w);

	return pass;
}

static GLboolean
test_format(const struct format_desc *format, GLenum baseformat)
{
	int dim;
	GLuint tex;
	int x;
	int level;
	GLboolean pass = GL_TRUE;

	printf("Testing %s\n", format->name);
	tex = create_tex(format->internalformat, baseformat);

	if (tex == 0)
		return PIGLIT_SKIP;

	x = 1;
	for (dim = TEX_WIDTH; dim > 1; dim /= 2) {
		draw_mipmap(x, 1, dim);
		x += dim + 1;
	}

	x = 1;
	level = 0;
	for (dim = TEX_WIDTH; dim > 1; dim /= 2) {
		pass = pass && test_mipmap_drawing(x, 1, dim, level,
						   format->internalformat);
		x += dim + 1;
		level++;
	}

	glDeleteTextures(1, &tex);

	return pass ? PIGLIT_SUCCESS : PIGLIT_FAILURE;
}

static void
add_result(bool *all_skip, enum piglit_result *end_result,
	   enum piglit_result new)
{
	if (new != PIGLIT_SKIP)
		*all_skip = false;

	if (new == PIGLIT_FAILURE)
		*end_result = new;
}

enum piglit_result
piglit_display(void)
{
	enum piglit_result result, end_result = PIGLIT_SUCCESS;
	bool all_skip = true;
	int i;

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glClearColor(0.5, 0.5, 0.5, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);

	if (piglit_automatic) {
		for (i = 0; i < test_set->num_formats; i++) {
			result = test_format(&test_set->format[i],
					     test_set->base);
			add_result(&all_skip, &end_result, result);
		}
	} else {
		result = test_format(&test_sets[test_index].format[format_index],
				     test_sets[test_index].base);
		add_result(&all_skip, &end_result, result);
	}

	glutSwapBuffers();

	if (all_skip)
		return PIGLIT_SKIP;
	return end_result;
}


void piglit_init(int argc, char **argv)
{
	int i, j, k;

	glutKeyboardFunc(key_func);

	piglit_require_extension("GL_EXT_framebuffer_object");

	test_set = &test_sets[0];

	for (i = 1; i < argc; i++) {
		for (j = 1; j < ARRAY_SIZE(test_sets); j++) {
			if (!strcmp(argv[i], test_sets[j].param)) {
				for (k = 0; k < 3; k++) {
					if (test_sets[j].ext[k]) {
						piglit_require_extension(test_sets[j].ext[k]);
					}
				}

				test_set = &test_sets[j];
				break;
			}
		}
		if (j == ARRAY_SIZE(test_sets)) {
			fprintf(stderr, "Unknown argument: %s\n", argv[i]);
			exit(1);
		}
	}

	if (!piglit_automatic) {
		printf("    -n   Next test set.\n"
		       "    -N   Previous test set.\n"
		       "    -m   Next format in the set.\n"
		       "    -M   Previous format in the set.\n");
	}

	printf("Using test set: %s\n", test_set->param);
}