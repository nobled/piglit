/*
 * Copyright © 2011 Marek Olšák <maraeo@gmail.com>
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
 * Basic EXT_transform_feedback test.
 *
 * Test writing vertex positions into a buffer object, with BindBufferBase,
 * BindBufferOffset, BindBufferRange, GL_RASTERIZER_DISCARD, and related queries.
 */

#include "piglit-util.h"

int piglit_width = 64;
int piglit_height = 32;
int piglit_window_mode = GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA;

static const char *vstext = {
	"void main() {"
	"  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
	"  gl_FrontColor = vec4(1.0);"
	"}"
};
static const char *vspassthrough = {
	"void main() {"
	"  gl_Position = gl_Vertex + vec4(0.5, 0.0, 0.0, 0.0);"
	"  gl_FrontColor = vec4(1.0, 0.0, 0.0, 1.0);"
	"}"
};

static const char *varyings[] = {"gl_Position"};
GLuint buf;
GLboolean discard;
unsigned offset, range;
GLuint prog, prog_passthrough;

enum {
	READBACK,
	RENDER,
	PRIMGEN,
	PRIMWRITTEN
};
int test = READBACK;

#define DEFAULT_VALUE 0.76543
#define MAX_RANGE (6*4)
#define OFFSET 20
#define BUF_FLOATS (OFFSET+MAX_RANGE)

void piglit_init(int argc, char **argv)
{
	GLuint vs;
	unsigned i;
	float data[BUF_FLOATS];

	for (i = 0; i < BUF_FLOATS; i++) {
		data[i] = DEFAULT_VALUE;
	}

	/* Parse params. */
	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "discard")) {
			discard = GL_TRUE;
		} else if (!strcmp(argv[i], "offset")) {
			/* BindBufferOffset only exists in the EXT specification */
			piglit_require_extension("GL_EXT_transform_feedback");
			offset = OFFSET;
		} else if (!strcmp(argv[i], "range")) {
			offset = OFFSET;
			range = MAX_RANGE-7;
		} else if (!strcmp(argv[i], "render")) {
			test = RENDER;
		} else if (!strcmp(argv[i], "primgen")) {
			test = PRIMGEN;
		} else if (!strcmp(argv[i], "primwritten")) {
			test = PRIMWRITTEN;
		}
	}

	piglit_ortho_projection(piglit_width, piglit_height, GL_FALSE);

	/* Check the driver. */
	if (!GLEW_VERSION_1_5) {
		fprintf(stderr, "OpenGL 1.5 required.\n");
		piglit_report_result(PIGLIT_SKIP);
	}
	piglit_require_GLSL();
	piglit_require_transform_feedback();

	/* Create shaders. */
	vs = piglit_compile_shader_text(GL_VERTEX_SHADER, vstext);
	prog = piglit_CreateProgram();
	piglit_AttachShader(prog, vs);
	piglit_TransformFeedbackVaryings(prog, 1, varyings, GL_INTERLEAVED_ATTRIBS_EXT);
	piglit_LinkProgram(prog);
	if (!piglit_link_check_status(prog)) {
		piglit_DeleteProgram(prog);
		piglit_report_result(PIGLIT_FAIL);
	}

	vs = piglit_compile_shader_text(GL_VERTEX_SHADER, vspassthrough);
	prog_passthrough = piglit_CreateProgram();
	piglit_AttachShader(prog_passthrough, vs);
	piglit_TransformFeedbackVaryings(prog_passthrough, 1, varyings, GL_INTERLEAVED_ATTRIBS_EXT);
	piglit_LinkProgram(prog_passthrough);
	if (!piglit_link_check_status(prog_passthrough)) {
		piglit_DeleteProgram(prog_passthrough);
		piglit_report_result(PIGLIT_FAIL);
	}

	/* Set up the transform feedback buffer. */
	glGenBuffers(1, &buf);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER_EXT, buf);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER_EXT,
		     BUF_FLOATS*sizeof(float), data, GL_STREAM_READ);

	assert(glGetError() == 0);

	if (range) {
		puts("Testing BindBufferRange.");
		piglit_BindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER_EXT,
				     0, buf, offset*sizeof(float), range*sizeof(float));
	} else if (offset) {
		puts("Testing BindBufferOffset.");
		glBindBufferOffsetEXT(GL_TRANSFORM_FEEDBACK_BUFFER_EXT,
				      0, buf, offset*sizeof(float));
	} else {
		puts("Testing BindBufferBase.");
		piglit_BindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER_EXT, 0, buf);
	}

	if (!range) {
		range = MAX_RANGE;
	} else {
		range = MAX_RANGE/2; /* just one primitive is going to be written */
	}

	assert(glGetError() == 0);

	glClearColor(0.2, 0.2, 0.2, 1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
}

enum piglit_result piglit_display(void)
{
	GLboolean pass = GL_TRUE;
	GLuint q;
	float *ptr;
	unsigned i, qresult;
	static const float verts[] = {
		10, 10,
		10, 20,
		20, 20,
		20, 10
	};
	static const float expected[] = {
		-0.687500, -0.375000, 0.000000, 1.000000,
		-0.687500, 0.250000, 0.000000, 1.000000,
		-0.375000, -0.375000, 0.000000, 1.000000,
		-0.687500, 0.250000, 0.000000, 1.000000,
		-0.375000, 0.250000, 0.000000, 1.000000,
		-0.375000, -0.375000, 0.000000, 1.000000,
	};
	static const unsigned indices[] = {
		0, 1, 3, 1, 2, 3
	};
	static const float clearcolor[] = {0.2, 0.2, 0.2};
	static const float white[] = {1, 1, 1};
	static const float red[] = {1, 0, 0};

	glClear(GL_COLOR_BUFFER_BIT);

	/* Set up queries. */
	switch (test) {
	case PRIMGEN:
		glGenQueries(1, &q);
		glBeginQuery(GL_PRIMITIVES_GENERATED_EXT, q);
		break;
	case PRIMWRITTEN:
		glGenQueries(1, &q);
		glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_EXT, q);
		break;
	}

	/* Render into TFBO. */
	glLoadIdentity();
	piglit_UseProgram(prog);
	if (discard)
		glEnable(GL_RASTERIZER_DISCARD_EXT);
	piglit_BeginTransformFeedback(GL_TRIANGLES);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexPointer(2, GL_FLOAT, 0, verts);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
	piglit_EndTransformFeedback();
	if (discard)
		glDisable(GL_RASTERIZER_DISCARD_EXT);

	assert(glGetError() == 0);

	switch (test) {
	case READBACK:
		puts("Testing readback.");
		ptr = glMapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER_EXT, GL_READ_ONLY);
		for (i = 0; i < BUF_FLOATS; i++) {
			float value = i >= offset && i < offset+range ? expected[i-offset] : DEFAULT_VALUE;
			//printf("%f, ", ptr[i]);

			if (fabs(ptr[i] - value) > 0.01) {
				printf("Buffer[%i]: %f,  Expected: %f\n", i, ptr[i], value);
				pass = GL_FALSE;
			}
		}
		glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER_EXT);
		break;

	case RENDER:
		puts("Testing rendering.");
		piglit_UseProgram(prog_passthrough);
		glBindBuffer(GL_ARRAY_BUFFER, buf);
		glVertexPointer(4, GL_FLOAT, 0, (void*)(intptr_t)(offset * sizeof(float)));
		glDrawArrays(GL_TRIANGLES, 0, range == MAX_RANGE ? 6 : 3);

		pass = piglit_probe_pixel_rgb(33, 18, range == MAX_RANGE ? red : clearcolor) && pass;
		pass = piglit_probe_pixel_rgb(28, 12, red) && pass;
		break;

	case PRIMGEN:
		puts("Testing a primitives-generated query.");
		glEndQuery(GL_PRIMITIVES_GENERATED_EXT);
		glGetQueryObjectuiv(q, GL_QUERY_RESULT, &qresult);
		{
			int expected = 2; /* RASTERIZER_DISCARD should not affect this. */
			if (qresult != expected) {
				printf("Primitives generated: %i,  Expected: %i\n", qresult, expected);
				pass = GL_FALSE;
			}
		}
		break;

	case PRIMWRITTEN:
		puts("Testing a primitives-written query.");
		glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_EXT);
		glGetQueryObjectuiv(q, GL_QUERY_RESULT, &qresult);
		{
			int expected = range == MAX_RANGE ? 2 : 1;
			if (qresult != expected) {
				printf("Primitives written: %i,  Expected: %i\n", qresult, expected);
				pass = GL_FALSE;
			}
		}
		break;

	default:
		piglit_report_result(PIGLIT_SKIP);
	}

	pass = piglit_probe_pixel_rgb(5, 5, clearcolor) && pass;
	pass = piglit_probe_pixel_rgb(15, 15, discard ? clearcolor : white) && pass;

	assert(glGetError() == 0);

	glutSwapBuffers();

	return pass ? PIGLIT_PASS : PIGLIT_FAIL;
}
