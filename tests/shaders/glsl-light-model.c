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
 */

/**
 * \file glsl-link-initializer-01.c
 * Test conflicting variable initializers.
 *
 * Each of the 3 shaders involved in this test have a global variable called
 * \c global_variable.  Two of the shaders have (differing) initializers for
 * this variable, and the other lacks an initalizer.  The test verifies that
 * linking the 3 shaders together results in an error due to the conflicting
 * initializer.
 *
 * \author Ian Romanick
 */

#include "piglit-util.h"

int piglit_width = 100, piglit_height = 100;
int piglit_window_mode = GLUT_RGB | GLUT_DOUBLE;

static const GLfloat verts[12] = {
	10.0, 10.0,
	20.0, 10.0,
	20.0, 20.0,
	10.0, 20.0
};

static const char *vs_code =
	"void main()\n"
	"{\n"
	"	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
	"}\n";

static const char *fs_code =
	"void main()\n"
	"{\n"
	"	gl_FragColor = gl_LightModel.ambient;\n"
	"}\n";


void
piglit_init(int argc, char **argv)
{
	GLuint vs, fs, prog;

	piglit_ortho_projection(piglit_width, piglit_height, GL_FALSE);

	if (piglit_get_gl_version() < 20) {
		printf("Requires OpenGL 2.0\n");
		piglit_report_result(PIGLIT_SKIP);
	}

	vs = piglit_compile_shader_text(GL_VERTEX_SHADER, vs_code);
	fs = piglit_compile_shader_text(GL_FRAGMENT_SHADER, fs_code);
	prog = piglit_link_simple_program(vs, fs);

	glUseProgram(prog);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),
			      verts);
	glEnableVertexAttribArray(0);
}


enum piglit_result
piglit_display(void)
{
	GLboolean pass = GL_TRUE;
	static const GLfloat green[4] = { 0.0, 1.0, 0.0, 1.0 };

	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, green);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	pass = pass && piglit_probe_pixel_rgb(15, 15, green);

	glutSwapBuffers();

	return pass ? PIGLIT_PASS : PIGLIT_FAIL;
}
