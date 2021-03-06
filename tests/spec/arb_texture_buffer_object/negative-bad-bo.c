/* Copyright © 2012 Intel Corporation
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

/** @file negative-bad-bo.c
 *
 * From the GL_ARB_texture_buffer_object spec:
 *
 *     "If <buffer> is non-zero, but is not the name of an existing
 *      buffer object, the error INVALID_OPERATION is generated."
 */

#include "piglit-util.h"

int piglit_width = 32;
int piglit_height = 32;
int piglit_window_mode = GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA;

enum piglit_result
piglit_display(void)
{
	return PIGLIT_FAIL; /* UNREACHED */
}


void
piglit_init(int argc, char **argv)
{
	GLuint tex;

	piglit_require_extension("GL_ARB_texture_buffer_object");

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_BUFFER, tex);
	glTexBufferARB(GL_TEXTURE_BUFFER, GL_RGBA8, 0xd0d0d0d0);
	if (!piglit_check_gl_error(GL_INVALID_OPERATION))
		piglit_report_result(PIGLIT_FAIL);

	piglit_report_result(PIGLIT_PASS);
}
