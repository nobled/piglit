/*
 * Copyright © 2011 Intel Corporation
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
 */

/** @file fbo-readpixels-depth-formats.c
 *
 * Tests that various formats of depth renderbuffers can be read
 * correctly using glReadPixels() with various format/type
 * combinations.
 */

#include "piglit-util.h"

#define BUF_WIDTH 15
#define BUF_HEIGHT 15
int piglit_window_mode = GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA;
int piglit_width = BUF_WIDTH;
int piglit_height = BUF_WIDTH;

/* Width of our stripes of z = 0.0, 0.5, 1.0 */
static int w = BUF_WIDTH / 3;

int depth_bits;

static bool
test_pixel(int x, int y, uint32_t value)
{
	uint32_t expected;

	if (x < w)
		expected = 0x00000000;
	else if (x < w * 2)
		expected = 0x80000001;
	else
		expected = 0xffffff02;

	/* Compare depth and stencil separately. Use 1-bit tolerance for depth. */
	if ((value & 0xff) - (expected & 0xff) != 0 ||
	    abs((value >> 8) - (expected >> 8)) > 1) {
		fprintf(stderr,
			"Expected 0x%08x at (%d,%d), found 0x%08x\n",
			expected, x, y, value);
		return false;
	}

	return true;
}

static bool
test()
{
	GLuint tex, fb;
	GLenum status;
	bool pass = true;
	uint32_t values[BUF_WIDTH * BUF_HEIGHT];
	int x, y;

	glGenFramebuffersEXT(1, &fb);
	glBindFramebufferEXT(GL_FRAMEBUFFER, fb);
	assert(glGetError() == 0);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8,
		     BUF_WIDTH, BUF_HEIGHT, 0,
		     GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
				  GL_DEPTH_ATTACHMENT_EXT,
				  GL_TEXTURE_2D,
				  tex,
				  0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
				  GL_STENCIL_ATTACHMENT_EXT,
				  GL_TEXTURE_2D,
				  tex,
				  0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	status = glCheckFramebufferStatusEXT (GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		fprintf(stderr, "framebuffer incomplete\n");
		goto done;
	}

	glGetIntegerv(GL_DEPTH_BITS, &depth_bits);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	glViewport(0, 0, BUF_WIDTH, BUF_HEIGHT);
	piglit_ortho_projection(BUF_WIDTH, BUF_HEIGHT, false);
	glStencilFunc(GL_ALWAYS, 0, ~0);
	piglit_draw_rect_z(1.0, 0,     0, w,     BUF_HEIGHT);
	glStencilFunc(GL_ALWAYS, 1, ~0);
	piglit_draw_rect_z(0.0, w,     0, w * 2, BUF_HEIGHT);
	glStencilFunc(GL_ALWAYS, 2, ~0);
	piglit_draw_rect_z(-1.0, w * 2, 0, w * 3, BUF_HEIGHT);

	glReadPixels(0, 0, BUF_WIDTH, BUF_HEIGHT,
		     GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, values);

	for (y = 0; y < BUF_HEIGHT; y++) {
		for (x = 0; x < BUF_WIDTH; x++) {
			if (!test_pixel(x, y, values[y * BUF_WIDTH + x])) {
				pass = false;
				break;
			}
		}
		if (x != BUF_WIDTH)
			break;

	}

done:
	glDeleteFramebuffersEXT(1, &fb);
	glDeleteTextures(1, &tex);
	return pass;
}

void piglit_init(int argc, char **argv)
{
	bool pass = true;

	piglit_require_extension("GL_EXT_framebuffer_object");
	piglit_require_extension("GL_EXT_packed_depth_stencil");

	pass = test();

	piglit_report_result(pass ? PIGLIT_PASS : PIGLIT_FAIL);
}

enum piglit_result
piglit_display(void)
{
	/* UNREACHED */
	return PIGLIT_FAIL;
}
