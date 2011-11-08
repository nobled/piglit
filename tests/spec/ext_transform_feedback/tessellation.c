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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/**
 * \file tessellation.c
 *
 * Verify that transform feedback properly converts primitives of
 * types GL_LINE_LOOP, GL_LINE_STRIP, GL_TRIANGLE_STRIP,
 * GL_TRIANGLE_FAN, GL_QUADS, GL_QUAD_STRIP, and GL_POLYGON into
 * primitives of type GL_LINES or GL_TRIANGLES, as appropriate.
 *
 * According to the OpenGL 3.0 spec (section 2.15: Transform Feedback):
 *
 *     "When quads and polygons are provided to transform feedback
 *     with a primitive mode of TRIANGLES, they will be tessellated
 *     and recorded as triangles (the order of tessellation within a
 *     primitive is undefined). Individual lines or triangles of a
 *     strip or fan primitive will be extracted and recorded
 *     separately."
 *
 * Although it is not stated explicitly, it is clear from context that
 * individual lines of a LINE_LOOP primitive are also expected to be
 * extracted and recorded separately.  Also, the spec does not place
 * any requirement on the order in which vertices are output when
 * extracting individual lines or triangles of a strip, fan, or
 * LINE_LOOP primitive.
 *
 * Because the spec allows variability in how these primitives are
 * tessellated and extracted, we can't verify correct operation by
 * examining the vertices themselves.  However, we can check that if
 * the transform feedback output is fed back into the GL pipeline
 * (using GL_TRIANGLES or GL_LINES, as appropriate), the same image
 * will be rendered.
 *
 * This test operates by first rendering an image without transform
 * feedback, then rendering the same image with transform feedback,
 * then rendering the transform feedback output.  Then it checks that
 * the 3 generated images match exactly.
 *
 * In addition, the test verifies that the expected number of vertices
 * was output by transform feedback.
 *
 * The images are rendered using a fragment shader that attenuates the
 * color of back-facing primitives, so that the test will verify that
 * tesellation preserves winding order properly.
 *
 * The test can be run in four different coloring modes:
 *
 * - "monochrome", meaning that all vertices are assigned the same
 *   color.  A failure in this mode means that the tessellated image
 *   did not have the correct shape.
 *
 * - "smooth", meaning that all vertices are assigned different
 *   colors, and the primitives are drawn with smooth interpolation.
 *   A failure in this mode means that the tessellation performed by
 *   transform feedback failed to match the tessellation performed by
 *   the GL pipeline under normal operation.
 *
 * - "flat_last" or "flat_first", meaning that all vertices are
 *   assigned different colors, and the primitives are flatshaded.  In
 *   the "flat_last" case, they are flatshaded using the GL standard
 *   "last vertex" convention to select the provoking vertex.  In the
 *   "flat_first" case, they are flatshaded using the alternative
 *   "first vertex" convention provided by GL_EXT_provoking_vertex or
 *   GL_ARB_provoking_vertex.  A failure in one of these modes means
 *   that within at least one of the tessellated primitives, transform
 *   feedback failed to output the vertices in the correct order for
 *   proper flatshading.
 */

#include "piglit-util.h"

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

#define BUFFER_SIZE 20

#define Elements(array) (sizeof(array)/sizeof(array[0]))

int piglit_width = 256;
int piglit_height = 256;
int piglit_window_mode = GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA;

/* Test parameters */
static GLenum draw_mode;
static GLenum xfb_mode;
static unsigned num_input_vertices;
static unsigned expected_num_output_vertices;
static float (*vertex_positions)[2];
static GLboolean monochrome;
static GLboolean use_flat_color;

/* Other globals */
static GLuint normal_prog;
static GLuint xfb_prog;
static GLuint xfb_buf;
static float vertex_colors[][4] = {
	{ 0.00, 0.00, 0.00, 0.00 },
	{ 1.00, 0.25, 0.25, 1.00 },
	{ 0.15, 0.37, 0.98, 1.00 },
	{ 0.50, 0.93, 0.07, 1.00 },
	{ 0.85, 0.02, 0.63, 1.00 },
	{ 0.0,  0.75, 0.75, 1.00 },
	{ 0.85, 0.63, 0.02, 1.00 },
	{ 0.5,  0.07, 0.93, 1.00 },
	{ 0.15, 0.98, 0.37, 1.00 }
};

static struct vertex_data {
	float vertex[2];
	float smooth_color[4];
	float flat_color[4];
} verts[BUFFER_SIZE];

/* Note: vertices are chosen to be on pixel centers to minimize the
 * risk that rounding errors change the image.
 */
static float line_loop_vertices[][2] = {
	{  2.5,  2.5 },
	{  2.5, 62.5 },
	{ 62.5, 62.5 },
	{ 62.5,  2.5 }
};

/* Note: vertices are chosen to be on pixel centers to minimize the
 * risk that rounding errors change the image.
 */
static float line_strip_vertices[][2] = {
	{  2.5,  2.5 },
	{  2.5, 32.5 },
	{ 32.5, 32.5 },
	{ 32.5, 62.5 }
};

static float triangle_strip_vertices[][2] = {
	{  2,  2 },
	{  2, 62 },
	{ 42,  2 },
	{ 42, 62 },
	{ 82,  2 }
};

static float triangle_fan_vertices[][2] = {
	{  2,  2 },
	{  2, 62 },
	{ 32, 47 },
	{ 52, 27 },
	{ 57, 12 }
};

static float quads_vertices[][2] = {
	{   2,  2 },
	{   2, 62 },
	{  62, 62 },
	{  62,  2 },
	{ 102,  2 },
	{ 102, 62 },
	{ 162, 62 },
	{ 162,  2 }
};

static float quad_strip_vertices[][2] = {
	{   2,  2 },
	{   2, 62 },
	{  62,  2 },
	{  62, 62 },
	{ 122,  2 },
	{ 122, 62 }
};

static float polygon_vertices[][2] = {
	{ 12,  2 },
	{  2, 42 },
	{ 32, 62 },
	{ 62, 42 },
	{ 52,  2 }
};

static const char *vstext =
	"#version 130\n"
	"uniform vec2 vertex_offset;\n"
	"in vec2 vertex;\n"
	"in vec4 smooth_color;\n"
	"in vec4 flat_color;\n"
	"out vec2 vertex_varying;\n"
	"out vec4 smooth_color_varying;\n"
	"flat out vec4 flat_color_varying;\n"
	"\n"
	"void main()\n"
	"{\n"
	"  gl_Position = vec4(vertex + vertex_offset, 0, 128.0);\n"
	"  vertex_varying = vertex;\n"
	"  smooth_color_varying = smooth_color;\n"
	"  flat_color_varying = flat_color;\n"
	"}\n";

static const char *fstext =
	"#version 130\n"
	"uniform bool use_flat_color;\n"
	"in vec4 smooth_color_varying;\n"
	"flat in vec4 flat_color_varying;\n"
	"\n"
	"void main()\n"
	"{\n"
	"  vec4 color = use_flat_color ? flat_color_varying\n"
	"                              : smooth_color_varying;\n"
	"  if (!gl_FrontFacing)\n"
	"    color *= 0.5;\n"
	"  gl_FragColor = color;\n"
	"}\n";

static const char *varyings[] = {
	"vertex_varying", "smooth_color_varying", "flat_color_varying"
};

static void
initialize_shader_and_xfb()
{
	GLuint vs, fs;

	piglit_require_GLSL_version(130);
	piglit_require_transform_feedback();
	vs = piglit_compile_shader_text(GL_VERTEX_SHADER, vstext);
	fs = piglit_compile_shader_text(GL_FRAGMENT_SHADER, fstext);
	normal_prog = piglit_CreateProgram();
	piglit_AttachShader(normal_prog, vs);
	piglit_AttachShader(normal_prog, fs);
	piglit_LinkProgram(normal_prog);
	if (!piglit_link_check_status(normal_prog)) {
		piglit_report_result(PIGLIT_FAIL);
	}
	xfb_prog = piglit_CreateProgram();
	piglit_AttachShader(xfb_prog, vs);
	piglit_AttachShader(xfb_prog, fs);
	piglit_TransformFeedbackVaryings(xfb_prog, 3, varyings,
					 GL_INTERLEAVED_ATTRIBS);
	piglit_LinkProgram(xfb_prog);
	if (!piglit_link_check_status(xfb_prog)) {
		piglit_report_result(PIGLIT_FAIL);
	}
	glGenBuffers(1, &xfb_buf);
	glFrontFace(GL_CW);
	piglit_check_gl_error(0, PIGLIT_FAIL);
}

static void
setup_vertex_shader_inputs(GLuint prog)
{
	GLint vertex_index = glGetAttribLocation(prog, "vertex");
	GLint smooth_color_index = glGetAttribLocation(prog, "smooth_color");
	GLint flat_color_index = glGetAttribLocation(prog, "flat_color");

	glVertexAttribPointer(vertex_index, 2, GL_FLOAT, GL_FALSE,
			      sizeof(verts[0]), &verts[0].vertex);
	glVertexAttribPointer(smooth_color_index, 4, GL_FLOAT, GL_FALSE,
			      sizeof(verts[0]), &verts[0].smooth_color);
	glVertexAttribPointer(flat_color_index, 4, GL_FLOAT, GL_FALSE,
			      sizeof(verts[0]), &verts[0].flat_color);
	glEnableVertexAttribArray(vertex_index);
	glEnableVertexAttribArray(smooth_color_index);
	glEnableVertexAttribArray(flat_color_index);
	piglit_check_gl_error(0, PIGLIT_FAIL);
}

static void
initialize_vertex_shader_inputs()
{
	unsigned i;

	if (monochrome) {
		for (i = 1; i < Elements(vertex_colors); ++i) {
			vertex_colors[i][0] = 1.0;
			vertex_colors[i][1] = 1.0;
			vertex_colors[i][2] = 1.0;
			vertex_colors[i][3] = 1.0;
		}
	}

	for (i = 0; i < num_input_vertices; ++i) {
		memcpy(verts[i].vertex, vertex_positions[i],
		       sizeof(verts[i].vertex));
		memcpy(verts[i].smooth_color, vertex_colors[i+1],
		       sizeof(verts[i].smooth_color));
		memcpy(verts[i].flat_color, vertex_colors[i+1],
		       sizeof(verts[i].flat_color));
	}
}

/**
 * Determine how many vertices were output by transform feedback by
 * seeing which elements of the transform feedback buffer have been
 * changed from their zero-initialized value.
 */
static unsigned
count_output_vertices(struct vertex_data *vertices)
{
	struct vertex_data zero_initialized;
	unsigned i;

	memset(&zero_initialized, 0, sizeof(zero_initialized));

	for (i = 0; i < BUFFER_SIZE; ++i) {
		if (memcmp(&vertices[i], &zero_initialized,
			   sizeof(zero_initialized)) == 0)
			break;
	}
	return i;
}

/**
 * Check that two strips of the window match.  Strips are numbered
 * from the top from 0 to 3.
 */
static GLboolean
match_strips(int reference, int compare)
{
	int reference_offset = (3 - reference) * (piglit_height / 4);
	int compare_offset = (3 - compare) * (piglit_height / 4);
	int x, y;
	for (x = 0; x < piglit_width; ++x) {
		for (y = 0; y < piglit_height/4; ++y) {
			float probed[4];
			glReadPixels(x, y + reference_offset, 1, 1,
				     GL_RGBA, GL_FLOAT, &probed);
			if (!piglit_probe_pixel_rgba(x, y + compare_offset,
						     probed))
				return GL_FALSE;
		}
	}
	return GL_TRUE;
}

static void
draw(GLuint prog, bool use_xfb, float y_offset, GLenum mode,
     unsigned num_vertices)
{
	float vertex_offset[2] = { -82.0, y_offset };
	struct vertex_data buffer[BUFFER_SIZE];

	piglit_UseProgram(prog);
	setup_vertex_shader_inputs(prog);
	piglit_Uniform2fv(piglit_GetUniformLocation(prog, "vertex_offset"),
			  1, vertex_offset);
	piglit_Uniform1i(piglit_GetUniformLocation(prog, "use_flat_color"),
			 use_flat_color);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	if (use_xfb) {
		glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, xfb_buf);
		/* Initialize the buffer with 0 so that we will be
		 * able to identify membory that was not overwitten by
		 * the transform feedback.
		 */
		memset(buffer, 0, sizeof(buffer));
		glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(buffer),
			     buffer, GL_STREAM_READ);
		piglit_BindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0,
				      xfb_buf);
		piglit_BeginTransformFeedback(xfb_mode);
	}
	glDrawArrays(mode, 0, num_vertices);
	if (use_xfb)
		piglit_EndTransformFeedback();
	piglit_check_gl_error(0, PIGLIT_FAIL);
}

static void
print_usage_and_exit(char *prog_name)
{
	printf("Usage: %s <draw_mode> <shade_mode>\n"
	       "  where <draw_mode> is one of:\n"
	       "    line_loop\n"
	       "    line_strip\n"
	       "    triangle_strip\n"
	       "    triangle_fan\n"
	       "    quads\n"
	       "    quad_strip\n"
	       "    polygon\n"
	       "  and <shade_mode> is one of:\n"
	       "    monochrome\n"
	       "    smooth\n"
	       "    flat_first\n"
	       "    flat_last\n", prog_name);
	exit(1);
}

void
piglit_init(int argc, char **argv)
{
	/* Interpret command line args */
	if (argc != 3)
		print_usage_and_exit(argv[0]);
	if (strcmp(argv[1], "line_loop") == 0) {
		draw_mode = GL_LINE_LOOP;
		xfb_mode = GL_LINES;
		num_input_vertices = 4;
		expected_num_output_vertices = 8;
		vertex_positions = line_loop_vertices;
	} else if (strcmp(argv[1], "line_strip") == 0) {
		draw_mode = GL_LINE_STRIP;
		xfb_mode = GL_LINES;
		num_input_vertices = 4;
		expected_num_output_vertices = 6;
		vertex_positions = line_strip_vertices;
	} else if (strcmp(argv[1], "triangle_strip") == 0) {
		draw_mode = GL_TRIANGLE_STRIP;
		xfb_mode = GL_TRIANGLES;
		num_input_vertices = 5;
		expected_num_output_vertices = 9;
		vertex_positions = triangle_strip_vertices;
	} else if (strcmp(argv[1], "triangle_fan") == 0) {
		draw_mode = GL_TRIANGLE_FAN;
		xfb_mode = GL_TRIANGLES;
		num_input_vertices = 5;
		expected_num_output_vertices = 9;
		vertex_positions = triangle_fan_vertices;
	} else if (strcmp(argv[1], "quads") == 0) {
		draw_mode = GL_QUADS;
		xfb_mode = GL_TRIANGLES;
		num_input_vertices = 8;
		expected_num_output_vertices = 12;
		vertex_positions = quads_vertices;
	} else if (strcmp(argv[1], "quad_strip") == 0) {
		draw_mode = GL_QUAD_STRIP;
		xfb_mode = GL_TRIANGLES;
		num_input_vertices = 6;
		expected_num_output_vertices = 12;
		vertex_positions = quad_strip_vertices;
	} else if (strcmp(argv[1], "polygon") == 0) {
		draw_mode = GL_POLYGON;
		xfb_mode = GL_TRIANGLES;
		num_input_vertices = 5;
		expected_num_output_vertices = 9;
		vertex_positions = polygon_vertices;
	} else {
		print_usage_and_exit(argv[0]);
	}
	if (strcmp(argv[2], "monochrome") == 0) {
		monochrome = GL_TRUE;
		use_flat_color = GL_FALSE;
	} else if (strcmp(argv[2], "smooth") == 0) {
		monochrome = GL_FALSE;
		use_flat_color = GL_FALSE;
	} else if (strcmp(argv[2], "flat_last") == 0) {
		monochrome = GL_FALSE;
		use_flat_color = GL_TRUE;
	} else if (strcmp(argv[2], "flat_first") == 0) {
		monochrome = GL_FALSE;
		use_flat_color = GL_TRUE;
		if (piglit_is_extension_supported("GL_EXT_provoking_vertex")) {
			glProvokingVertexEXT(GL_FIRST_VERTEX_CONVENTION);
		} else if (piglit_is_extension_supported("GL_ARB_provoking_vertex")) {
			glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
		} else {
			printf("Test requires GL_EXT_provoking_vertex "
			       "or GL_ARB_provoking_vertex\n");
			piglit_report_result(PIGLIT_SKIP);
			exit(1);
		}
	} else {
		print_usage_and_exit(argv[0]);
	}

	initialize_shader_and_xfb();
}

enum piglit_result piglit_display(void)
{
	struct vertex_data *readback;
	unsigned num_output_vertices;
	GLboolean pass = GL_TRUE;

	initialize_vertex_shader_inputs();

	glClear(GL_COLOR_BUFFER_BIT);
	draw(normal_prog, false, 64.0, draw_mode, num_input_vertices);
	draw(xfb_prog, true, 0.0, draw_mode, num_input_vertices);

	pass = match_strips(0, 1) && pass;

	readback = glMapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, GL_READ_ONLY);
	piglit_check_gl_error(0, PIGLIT_FAIL);

	num_output_vertices = count_output_vertices(readback);
	if (num_output_vertices != expected_num_output_vertices) {
		printf("Expected %u output vertices, but got %u\n",
		       expected_num_output_vertices, num_output_vertices);
		pass = GL_FALSE;
	}

	memcpy(verts, readback, sizeof(verts));
	glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER);

	draw(normal_prog, false, -64.0, xfb_mode, num_output_vertices);

	pass = match_strips(0, 2) && pass;

	piglit_present_results();

	return pass ? PIGLIT_PASS : PIGLIT_FAIL;
}
