/*
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
 * \file initial-texture-state.c
 * Verify the state of a texture object before the client sets any state itself.
 */

#include "piglit-util.h"

int piglit_width = 0, piglit_height = 0;
int piglit_window_mode = GLUT_RGB;

enum piglit_result
piglit_display(void)
{
	/* unreachable */
	return PIGLIT_FAIL;
}

struct paramtest {
GLenum      pname;
GLint       expected;
const char *required_extension;
};

static const struct paramtest texstate[] = {
{ GL_TEXTURE_WRAP_S, GL_REPEAT, NULL },
{ GL_TEXTURE_MIN_LOD, -1000, "GL_SGIS_texture_lod" },
{ GL_TEXTURE_MAX_LOD,  1000, "GL_SGIS_texture_lod" },
{ GL_TEXTURE_BASE_LEVEL,  0, "GL_SGIS_texture_lod" },
{ GL_TEXTURE_MAX_LEVEL, 1000, "GL_SGIS_texture_lod" },
{ GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE, "GL_ARB_depth_texture"},
{ GL_TEXTURE_COMPARE_MODE, GL_NONE, "GL_ARB_shadow"},
{ GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL, "GL_ARB_shadow"},
{ GL_GENERATE_MIPMAP, GL_FALSE, "GL_SGIS_generate_mipmap"}
};

/**
 * From the GL 3.0 spec, page 215 (page 231 of the PDF):
 *    "Each initial texel array is null (zero width, height, and depth,
 *    zero border width, internal format 1, with the compressed flag set to
 *    FALSE, a zero compressed size, and zero-sized components)."
 *
 * See also the state table on page 361/377.
 */
static const struct paramtest levelstate[] = {
/* GL 1.0 state */
{ GL_TEXTURE_WIDTH,  0, NULL },
{ GL_TEXTURE_HEIGHT, 0, NULL },
{ GL_TEXTURE_DEPTH,  0, NULL },
{ GL_TEXTURE_BORDER, 0, NULL },
{ GL_TEXTURE_INTERNAL_FORMAT /* aka GL_TEXTURE_COMPONENTS */,
  1 /* GL 1.0 way of specifying luminance */, NULL },

{ GL_TEXTURE_RED_SIZE,       0, /* GL 1.1 (GL_EXT_texture) */ NULL },
{ GL_TEXTURE_GREEN_SIZE,     0, /* GL 1.1 (GL_EXT_texture) */ NULL },
{ GL_TEXTURE_BLUE_SIZE,      0, /* GL 1.1 (GL_EXT_texture) */ NULL },
{ GL_TEXTURE_ALPHA_SIZE,     0, /* GL 1.1 (GL_EXT_texture) */ NULL },
{ GL_TEXTURE_LUMINANCE_SIZE, 0, /* GL 1.1 (GL_EXT_texture) */ NULL },
{ GL_TEXTURE_INTENSITY_SIZE, 0, /* GL 1.1 (GL_EXT_texture) */ NULL },
{ GL_TEXTURE_DEPTH_SIZE,     0, /* GL 1.1 (GL_EXT_texture) */ NULL },
{ GL_TEXTURE_STENCIL_SIZE,   0, /* GL 1.1 (GL_EXT_texture) */ NULL },

{ GL_TEXTURE_SHARED_SIZE, 0, "GL_EXT_texture_shared_exponent" },

{ GL_TEXTURE_RED_TYPE,       GL_NONE, "GL_ARB_texture_float" },
{ GL_TEXTURE_GREEN_TYPE,     GL_NONE, "GL_ARB_texture_float" },
{ GL_TEXTURE_BLUE_TYPE,      GL_NONE, "GL_ARB_texture_float" },
{ GL_TEXTURE_ALPHA_TYPE,     GL_NONE, "GL_ARB_texture_float" },
{ GL_TEXTURE_LUMINANCE_TYPE, GL_NONE, "GL_ARB_texture_float" },
{ GL_TEXTURE_INTENSITY_TYPE, GL_NONE, "GL_ARB_texture_float" },
{ GL_TEXTURE_DEPTH_TYPE,     GL_NONE, "GL_ARB_texture_float" },

{ GL_TEXTURE_COMPRESSED, GL_FALSE, "GL_ARB_texture_compression" },

};

#define INVALID_PNAME GL_RED

static GLboolean test_target(GLenum target) {
	unsigned i;
	GLint value;
	GLboolean pass = GL_TRUE;

	for (i = 0; i < ARRAY_SIZE(texstate); ++i) {
		const GLenum pname = texstate[i].pname;
		const GLint expected = texstate[i].expected;
		const char *const ext = texstate[i].required_extension;
		if (ext && !piglit_is_extension_supported(ext))
			continue;

		glGetTexParameteriv(target, pname, &value);
		if (!piglit_check_gl_error(GL_NO_ERROR)) {
			fprintf(stderr, "Error querying %s from target %s\n",
				piglit_get_gl_enum_name(pname),
				piglit_get_gl_enum_name(target));
			pass = GL_FALSE;
		} else if (value != texstate[i].expected) {
			fprintf(stderr, "Expected initial value of %s to be %x,"
				" but got %x\n", piglit_get_gl_enum_name(pname),
				expected, value);
			pass = GL_FALSE;
		}
	}

	glGetTexParameteriv(target, INVALID_PNAME, &value);
	pass = piglit_check_gl_error(GL_INVALID_ENUM) && pass;
	glGetTexParameteriv(target, INVALID_PNAME, NULL);
	pass = piglit_check_gl_error(GL_INVALID_ENUM) && pass;

	for (i = 0; i < ARRAY_SIZE(levelstate); ++i) {
		const GLenum pname = levelstate[i].pname;
		const GLint expected = levelstate[i].expected;
		const char *const ext = levelstate[i].required_extension;
		if (ext && !piglit_is_extension_supported(ext))
			continue;

		glGetTexLevelParameteriv(target, 0, pname, &value);
		if (!piglit_check_gl_error(GL_NO_ERROR)) {
			fprintf(stderr, "Error querying %s from target %s\n",
				piglit_get_gl_enum_name(pname),
				piglit_get_gl_enum_name(target));
			pass = GL_FALSE;
		} else if (value != levelstate[i].expected) {
			fprintf(stderr, "Expected initial value of %s to be %x,"
				" but got %x\n", piglit_get_gl_enum_name(pname),
				expected, value);
			pass = GL_FALSE;
		}
	}

/* Page 319-320 of the GL 3.0 spec:
   "Querying TEXTURE_COMPRESSED_IMAGE_SIZE is not allowed on texture images with
   an uncompressed internal format or on proxy targets and will result in an
   INVALID_OPERATION error if attempted."
 */
	if (piglit_is_extension_supported("GL_ARB_texture_compression")) {
		GLenum pname = GL_TEXTURE_COMPRESSED_IMAGE_SIZE;
		glGetTexLevelParameteriv(target, 0, pname, &value);
		if (!piglit_check_gl_error(GL_INVALID_OPERATION))
			pass = GL_FALSE;
	}

	glGetTexLevelParameteriv(target, 0, INVALID_PNAME, &value);
	pass = piglit_check_gl_error(GL_INVALID_ENUM) && pass;
	glGetTexLevelParameteriv(target, 0, INVALID_PNAME, NULL);
	pass = piglit_check_gl_error(GL_INVALID_ENUM) && pass;

	return pass;
}

static const GLenum targets[] =
{ GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D };
static const GLenum bindings[] =
{ GL_TEXTURE_BINDING_1D, GL_TEXTURE_BINDING_2D, GL_TEXTURE_BINDING_3D };

void
piglit_init(int argc, char **argv)
{
	unsigned i, count = ARRAY_SIZE(targets);
	GLboolean pass = GL_TRUE;

	/* Test:
	   - The default texture objects.
	   - Application-generated object names.
	   - Implementation-generated object names.
	 */
	assert(sizeof targets == sizeof bindings);
	for (i = 0; i < count*3; ++i) {
		GLenum target = targets[i%count], binding = bindings[i%count];
		GLuint tex = 0;

		if (i >= count*2) {
			glGenTextures(1, &tex);
			/* "A name returned by GenTextures, but not yet bound,
			   is not the name of a texture object."
			 */
			if (glIsTexture(tex)) {
				fprintf(stderr, "IsTexture() returned true!\n");
				pass = GL_FALSE;
			}
		} else if (i >= count) {
			tex = 100 + i % count;
			assert(!glIsTexture(tex) && "name is used?");
		}

		glBindTexture(target, tex);
		pass = test_target(target) && pass;

		/* "If a texture that is currently bound [...] is deleted,
		   it is as though BindTexture had been executed with the same
		   target and texture zero." */
		glDeleteTextures(1, &tex);
		glGetIntegerv(binding, (GLint*)&tex);
		if (tex != 0) {
			fprintf(stderr, "deleted texture is still bound!\n");
			pass = GL_FALSE;
		}
	}

	pass = piglit_check_gl_error(GL_NO_ERROR) && pass;

	piglit_report_result(pass ? PIGLIT_PASS : PIGLIT_FAIL);
}
