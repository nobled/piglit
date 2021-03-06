/* Copyright © 2011 Intel Corporation
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

/** @file minmax.c
 *
 * Test for the minimum maximum values in section 6.2 "State Tables"
 * of the GL 3.0 spec.
 */

#include "piglit-util.h"

int piglit_width = 32;
int piglit_height = 32;
int piglit_window_mode = GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA;

enum piglit_result
piglit_display(void)
{
	/* UNREACHED */
	return PIGLIT_FAIL;
}

static bool pass = true;

static void
max_test_i(GLenum token, GLint max, const char *name)
{
	GLint val[2];

	glGetIntegerv(token, val);

	if (val[0] > max) {
		fprintf(stderr, "%-50s %8d %8d (ERROR)\n",
			name, max, val[0]);
		pass = false;
	} else {
		printf("%-50s %8d %8d\n", name, max, val[0]);
	}
}

static void
min_test_i(GLenum token, GLint min, const char *name)
{
	GLint val;

	glGetIntegerv(token, &val);

	if (val < min) {
		fprintf(stderr, "%-50s %8d %8d (ERROR)\n",
			name, min, val);
		pass = false;
	} else {
		printf("%-50s %8d %8d\n", name, min, val);
	}
}

static void
min_test_f(GLenum token, GLfloat min, const char *name)
{
	GLfloat val;

	glGetFloatv(token, &val);

	if (val < min) {
		fprintf(stderr, "%-50s %8f %8f (ERROR)\n",
			name, min, val);
		pass = false;
	} else {
		printf("%-50s %8f %8f\n", name, min, val);
	}
}

/* All the size requirements happen to only require a range covering
 * [1.0, 1.0].
 */
static void
size_range_test(GLenum token, const char *name)
{
	GLfloat vals[2];

	glGetFloatv(token, vals);

	if (vals[0] > 1.0 || vals[1] < 1.0) {
		fprintf(stderr, "%-50s %8s  %.1f-%.1f (ERROR)\n",
			name, "1-1", vals[0], vals[1]);
		pass = false;
	} else {
		printf("%-50s %8s  %.1f-%.1f\n",
		       name, "1-1", vals[0], vals[1]);
	}
}

static void
test_oq_bits()
{
	GLint dims[2];
	GLint minbits, oqbits;

	/* From the GL 3.0 specification, page 329:
	 *
	 *     "If pname is QUERY_COUNTER_BITS, the
	 *      implementation-dependent number of query counter bits
	 *      may be zero, in which case the counter contains no
	 *      useful information.
	 *
	 *      For occlusion queries (SAMPLES PASSED), if the number
	 *      of bits is non-zero, the minimum number of bits
	 *      allowed is a function of the implementation’s maximum
	 *      viewport dimensions (MAX VIEWPORT DIMS). The counter
	 *      must be able to represent at least two overdraws for
	 *      every pixel in the viewport. The formula to compute
	 *      the allowable minimum value (where n is the minimum
	 *      number of bits) is
	 *
	 *      n = min{32, log2(maxViewportWidth ∗ maxViewportHeight * 2}"
	 */

	glGetIntegerv(GL_MAX_VIEWPORT_DIMS, dims);
	minbits = log2((float)dims[0] * dims[1] * 2);
	if (minbits > 32)
		minbits = 32;

	glGetQueryiv(GL_SAMPLES_PASSED, GL_QUERY_COUNTER_BITS, &oqbits);
	if (oqbits == 0 || oqbits >= minbits) {
		printf("%-50s   0 / %2d %8d\n",
		       "GL_QUERY_COUNTER_BITS(GL_SAMPLES_PASSED)",
		       minbits, oqbits);
	} else {
		fprintf(stderr,
			"%-50s   0 / %2d %8d\n",
			"GL_QUERY_COUNTER_BITS(GL_SAMPLES_PASSED)",
			minbits, oqbits);
		pass = false;
	}
}

static void
test_tf_bits(GLenum target)
{
	GLint bits = -1;
	const char *name;

	if (target == GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN)
		name = "GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN bits";
	else
		name = "GL_PRIMITIVES_GENERATED bits";

	/* From the GL 3.0 specification, page 329:
	 *
	 *     "If pname is QUERY_COUNTER_BITS, the
	 *      implementation-dependent number of query counter bits
	 *      may be zero, in which case the counter contains no
	 *      useful information.
	 *
	 *      For primitive queries (PRIMITIVES GENERATED and
	 *      TRANSFORM FEEDBACK PRIMITIVES WRITTEN) if the number
	 *      of bits is non-zero, the minimum number of bits
	 *      allowed is 32."
	 */

	glGetQueryiv(target, GL_QUERY_COUNTER_BITS, &bits);
	if (bits == 0 || bits >= 32) {
		printf("%-50s %8s %8d\n", name, "0 / 32", bits);
	} else {
		fprintf(stderr, "%-50s %8s %8d (ERROR)\n",
			name, "0 / 32", bits);
		pass = false;
	}
}

#define MAX_INTEGER_TEST(token, max) max_test_i(token, max, #token)
#define MIN_INTEGER_TEST(token, min) min_test_i(token, min, #token)
#define MIN_FLOAT_TEST(token, min) min_test_f(token, min, #token)
#define TEST_SIZE_RANGE(token) size_range_test(token, #token)

void
piglit_init(int argc, char **argv)
{
	int rb_size;

	piglit_require_gl_version(30);

	printf("%-50s %8s %8s\n", "token", "minimum", "value");

	/* These should be in the section with "Minimum Value" but
	 * appear in the section with "Initial Value".
	 */
	MIN_INTEGER_TEST(GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS, 64);
	MIN_INTEGER_TEST(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS, 4);
	MIN_INTEGER_TEST(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS, 4);

	MIN_INTEGER_TEST(GL_MAX_LIGHTS, 8);
	MIN_INTEGER_TEST(GL_MAX_CLIP_PLANES, 6);
	if (piglit_is_extension_supported("GL_ARB_imaging"))
		MIN_INTEGER_TEST(GL_MAX_COLOR_MATRIX_STACK_DEPTH, 2);
	MIN_INTEGER_TEST(GL_MAX_MODELVIEW_STACK_DEPTH, 32);
	MIN_INTEGER_TEST(GL_MAX_PROJECTION_STACK_DEPTH, 2);
	MIN_INTEGER_TEST(GL_MAX_TEXTURE_STACK_DEPTH, 2);
	MIN_INTEGER_TEST(GL_SUBPIXEL_BITS, 4);
	MIN_INTEGER_TEST(GL_MAX_3D_TEXTURE_SIZE, 256);
	MIN_INTEGER_TEST(GL_MAX_TEXTURE_SIZE, 1024);
	MIN_FLOAT_TEST(GL_MAX_TEXTURE_LOD_BIAS, 2.0);
	MIN_INTEGER_TEST(GL_MAX_ARRAY_TEXTURE_LAYERS, 256);
	MIN_INTEGER_TEST(GL_MAX_CUBE_MAP_TEXTURE_SIZE, 1024);
	MIN_INTEGER_TEST(GL_MAX_RENDERBUFFER_SIZE, 1024);
	MIN_INTEGER_TEST(GL_MAX_PIXEL_MAP_TABLE, 32);
	MIN_INTEGER_TEST(GL_MAX_NAME_STACK_DEPTH, 64);
	MIN_INTEGER_TEST(GL_MAX_LIST_NESTING, 64);
	MIN_INTEGER_TEST(GL_MAX_EVAL_ORDER, 8);

	/* FINISHME:
	 *
	 *     "The maximum viewport dimensions must be greater than
	 *      or equal to the larger of the visible dimensions of
	 *      the display being rendered to (if a display exists),
	 *      and the largest renderbuffer image which can be
	 *      successfully created and attached to a framebuffer
	 *      object (see chapter 4).  INVALID VALUE is generated if
	 *      either w or h is negative."
	 *
	 * We're only looking at RB limits here.
	 */
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &rb_size);
	MIN_INTEGER_TEST(GL_MAX_VIEWPORT_DIMS, rb_size);

	MIN_INTEGER_TEST(GL_MAX_ATTRIB_STACK_DEPTH, 16);
	MIN_INTEGER_TEST(GL_MAX_CLIENT_ATTRIB_STACK_DEPTH, 16);

	TEST_SIZE_RANGE(GL_ALIASED_POINT_SIZE_RANGE);
	TEST_SIZE_RANGE(GL_SMOOTH_POINT_SIZE_RANGE);
	TEST_SIZE_RANGE(GL_ALIASED_LINE_WIDTH_RANGE);
	TEST_SIZE_RANGE(GL_SMOOTH_LINE_WIDTH_RANGE);

	test_tf_bits(GL_PRIMITIVES_GENERATED);
	test_tf_bits(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	test_oq_bits();

	if (piglit_is_extension_supported("GL_ARB_imaging")) {
		/* FINISHME: GL_MAX_CONVOLUTION_WIDTH */
		/* FINISHME: GL_MAX_CONVOLUTION_HEIGHT */
	}

	MIN_INTEGER_TEST(GL_MAX_TEXTURE_UNITS, 2);
	MIN_INTEGER_TEST(GL_MAX_VERTEX_ATTRIBS, 16);
	MIN_INTEGER_TEST(GL_MAX_VERTEX_UNIFORM_COMPONENTS, 1024);
	MIN_INTEGER_TEST(GL_MAX_VARYING_COMPONENTS, 64);
	MIN_INTEGER_TEST(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, 16);
	MIN_INTEGER_TEST(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, 16);
	MIN_INTEGER_TEST(GL_MAX_TEXTURE_IMAGE_UNITS, 16);
	MIN_INTEGER_TEST(GL_MAX_TEXTURE_COORDS, 8);
	MIN_INTEGER_TEST(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, 1024);

	MAX_INTEGER_TEST(GL_MIN_PROGRAM_TEXEL_OFFSET, -8);
	MIN_INTEGER_TEST(GL_MAX_PROGRAM_TEXEL_OFFSET, 7);

	MIN_INTEGER_TEST(GL_AUX_BUFFERS, 0);
	MIN_INTEGER_TEST(GL_MAX_DRAW_BUFFERS, 8);

	MIN_INTEGER_TEST(GL_SAMPLE_BUFFERS, 0);
	MIN_INTEGER_TEST(GL_SAMPLES, 0);
	MIN_INTEGER_TEST(GL_MAX_COLOR_ATTACHMENTS, 8);
	MIN_INTEGER_TEST(GL_MAX_SAMPLES, 4);

	piglit_report_result(pass ? PIGLIT_PASS : PIGLIT_FAIL);
}
