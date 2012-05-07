/*
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
 *
 */

#include "piglit-util.h"

#include <limits.h>

int piglit_width = 320, piglit_height = 320;
int piglit_window_mode = GLUT_RGB;

#define width (10)
#define height (12)
#define depth (3)

void piglit_init(int argc, char **argv)
{
    piglit_ortho_projection(piglit_width, piglit_height, GL_FALSE);

    piglit_require_extension("GL_ARB_robustness");
    piglit_require_extension("GL_ARB_pixel_buffer_object");

    glClearColor(0.2, 0.2, 0.2, 1.0);
}

static GLboolean
succeeded(GLsizei bufSize, GLsizei required)
{
    GLenum expected;
    GLuint pbo;
    glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING_ARB, (GLint*)&pbo);

    if (pbo == 0 && bufSize < required)
        expected = GL_INVALID_OPERATION;
    else
        expected = GL_NO_ERROR;

    if (!piglit_check_gl_error(expected)) {
        fprintf(stderr, "(PIXEL_PACK_BUFFER=%u, bufSize = %d,"
                        " expected %d bytes to be required)\n",
                          pbo, bufSize, required);
        return GL_FALSE;
    }
    return GL_TRUE;
}

static enum piglit_result
test_pixelmap(int offby)
{
#define MAPSIZE 32
    GLuint pbo;
    glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING_ARB, (GLint*)&pbo);

#define TEST_PIXMAP(type, t)\
do {\
    GL##type v[MAPSIZE], *data;\
    GLsizei bufSize = offby + (int)(sizeof v);\
    unsigned i;\
\
    memset(v, 0, sizeof v);\
    for (i = 0; i < MAPSIZE; i += 2)\
        v[i] = 1.0;\
\
    glClear(GL_COLOR_BUFFER_BIT);\
\
    glPixelTransferi(GL_MAP_COLOR, GL_FALSE);\
    glPixelMap##t##v(GL_PIXEL_MAP_R_TO_R, MAPSIZE, v);\
    glPixelMap##t##v(GL_PIXEL_MAP_G_TO_G, MAPSIZE, v);\
    glPixelMap##t##v(GL_PIXEL_MAP_B_TO_B, MAPSIZE, v);\
    glPixelMap##t##v(GL_PIXEL_MAP_A_TO_A, MAPSIZE, v);\
    if (!piglit_check_gl_error(GL_NO_ERROR))\
        return PIGLIT_FAIL;\
\
    if (pbo)\
        glBufferDataARB(GL_PIXEL_PACK_BUFFER, sizeof v, NULL, GL_STREAM_COPY);\
\
    data = (pbo == 0) ? v : NULL;\
\
    glGetnPixelMap##t##vARB(GL_PIXEL_MAP_R_TO_R, bufSize, data);\
    if (!succeeded(bufSize, sizeof v))\
        return PIGLIT_FAIL;\
    glGetnPixelMap##t##vARB(GL_PIXEL_MAP_G_TO_G, bufSize, data);\
    if (!succeeded(bufSize, sizeof v))\
        return PIGLIT_FAIL;\
    glGetnPixelMap##t##vARB(GL_PIXEL_MAP_B_TO_B, bufSize, data);\
    if (!succeeded(bufSize, sizeof v))\
        return PIGLIT_FAIL;\
    glGetnPixelMap##t##vARB(GL_PIXEL_MAP_A_TO_A, bufSize, data);\
    if (!succeeded(bufSize, sizeof v))\
        return PIGLIT_FAIL;\
} while (0)

    TEST_PIXMAP(float, f);
    TEST_PIXMAP(uint, ui);
    TEST_PIXMAP(ushort, us);

#undef TEST_PIXMAP
#undef MAPSIZE
  return PIGLIT_PASS;
}

static enum piglit_result
test_readpix(int offby)
{
    GLuint pbo;
    glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING_ARB, (GLint*)&pbo);

#define TEST_READPIX(gltype, enumtype) \
do {\
    GL##gltype v[4*width*height], *data;\
    GLsizei bufSize = offby + (int)(sizeof v);\
\
    memset(v, 0, sizeof v);\
    glClear(GL_COLOR_BUFFER_BIT);\
\
    if (pbo)\
        glBufferDataARB(GL_PIXEL_PACK_BUFFER, sizeof v, NULL, GL_STREAM_COPY);\
\
    data = (pbo == 0) ? v : NULL;\
\
    glReadnPixelsARB(0, 0, width, height, GL_RGBA,\
                     GL_##enumtype, bufSize, data);\
    if (!succeeded(bufSize, sizeof v))\
        return PIGLIT_FAIL;\
    glReadnPixelsARB(1, 1, width, height, GL_RGBA,\
                     GL_##enumtype, bufSize, data);\
    if (!succeeded(bufSize, sizeof v))\
        return PIGLIT_FAIL;\
} while (0)

  TEST_READPIX(float, FLOAT);
  TEST_READPIX(int, INT);
  TEST_READPIX(byte, BYTE);
#undef TEST_READPIX
  return PIGLIT_PASS;
}

static enum piglit_result
test_stipple(int offby)
{
    GLubyte v[4*32], *data;
    GLsizei bufSize = offby + (int)(sizeof v);
    unsigned i;
    GLuint pbo;

    glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING_ARB, (GLint*)&pbo);

    for (i = 0; i < sizeof v; i++)
        v[i] = 0x55;

    glPolygonStipple(v);
    if (!piglit_check_gl_error(GL_NO_ERROR))
        return PIGLIT_FAIL;

    if (pbo)
        glBufferDataARB(GL_PIXEL_PACK_BUFFER, sizeof v, NULL, GL_STREAM_COPY);

    data = (pbo == 0) ? v : NULL;

    glGetnPolygonStippleARB(bufSize, data);
    if (!succeeded(bufSize, sizeof v))
        return PIGLIT_FAIL;

    return PIGLIT_PASS;
}

static enum piglit_result
test_teximage1d(int offby);
static enum piglit_result
test_teximage2d(int offby);
static enum piglit_result
test_teximage3d(int offby);

static enum piglit_result
test_teximage(int offby)
{
    if (test_teximage1d(offby) != PIGLIT_PASS)
        return PIGLIT_FAIL;
    if (test_teximage2d(offby) != PIGLIT_PASS)
        return PIGLIT_FAIL;
    if (test_teximage3d(offby) != PIGLIT_PASS)
        return PIGLIT_FAIL;

    return PIGLIT_PASS;
}

static enum piglit_result
test_teximage1d(int offby)
{
    GLuint pbo;
    glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING_ARB, (GLint*)&pbo);

#define TEST_TEX1D(gltype, enumtype)\
do {\
    GL##gltype v[4*width], *data;\
    GLsizei bufSize = offby + (int)(sizeof v);\
\
    memset(v, 0, sizeof v);\
    glClear(GL_COLOR_BUFFER_BIT);\
\
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, width,\
                 0, GL_RGBA, GL_##enumtype, v);\
    if (!piglit_check_gl_error(GL_NO_ERROR))\
        return PIGLIT_FAIL;\
\
    if (pbo)\
        glBufferDataARB(GL_PIXEL_PACK_BUFFER, sizeof v, NULL, GL_STREAM_COPY);\
\
    data = (pbo == 0) ? v : NULL;\
\
    glGetnTexImageARB(GL_TEXTURE_1D, 0, GL_RGBA, GL_##enumtype, bufSize, data);\
    if (!succeeded(bufSize, sizeof v))\
        return PIGLIT_FAIL;\
} while(0)

    TEST_TEX1D(float, FLOAT);
    TEST_TEX1D(int, INT);
    TEST_TEX1D(byte, BYTE);
#undef TEST_TEX1D
    return PIGLIT_PASS;
}

static enum piglit_result
test_teximage2d(int offby)
{
    GLuint pbo;
    glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING_ARB, (GLint*)&pbo);

#define TEST_TEX2D(gltype, enumtype)\
do {\
    GL##gltype v[4*width*height], *data;\
    GLsizei bufSize = offby + (int)(sizeof v);\
\
    memset(v, 0, sizeof v);\
    glClear(GL_COLOR_BUFFER_BIT);\
\
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,\
                 0, GL_RGBA, GL_##enumtype, v);\
    if (!piglit_check_gl_error(GL_NO_ERROR))\
        return PIGLIT_FAIL;\
\
    if (pbo)\
        glBufferDataARB(GL_PIXEL_PACK_BUFFER, sizeof v, NULL, GL_STREAM_COPY);\
\
    data = (pbo == 0) ? v : NULL;\
\
    glGetnTexImageARB(GL_TEXTURE_2D, 0, GL_RGBA, GL_##enumtype, bufSize, data);\
    if (!succeeded(bufSize, sizeof v))\
        return PIGLIT_FAIL;\
} while(0)

    TEST_TEX2D(float, FLOAT);
    TEST_TEX2D(int, INT);
    TEST_TEX2D(byte, BYTE);
#undef TEST_TEX2D
    return PIGLIT_PASS;
}

static enum piglit_result
test_teximage3d(int offby)
{
    GLuint pbo;
    glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING_ARB, (GLint*)&pbo);

#define TEST_TEX3D(gltype, enumtype)\
do {\
    GL##gltype v[4*width*height*depth], *data;\
    GLsizei bufSize = offby + (int)(sizeof v);\
\
    memset(v, 0, sizeof v);\
    glClear(GL_COLOR_BUFFER_BIT);\
\
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, width, height, depth,\
                 0, GL_RGBA, GL_##enumtype, v);\
    if (!piglit_check_gl_error(GL_NO_ERROR))\
        return PIGLIT_FAIL;\
\
    if (pbo)\
        glBufferDataARB(GL_PIXEL_PACK_BUFFER, sizeof v, NULL, GL_STREAM_COPY);\
\
    data = (pbo == 0) ? v : NULL;\
\
    glGetnTexImageARB(GL_TEXTURE_3D, 0, GL_RGBA, GL_##enumtype, bufSize, data);\
    if (!succeeded(bufSize, sizeof v))\
        return PIGLIT_FAIL;\
} while(0)

    TEST_TEX3D(float, FLOAT);
    TEST_TEX3D(int, INT);
    TEST_TEX3D(byte, BYTE);
#undef TEST_TEX3D
    return PIGLIT_PASS;
}

static enum piglit_result
test(int offby)
{
    if (test_pixelmap(offby) != PIGLIT_PASS)
         return PIGLIT_FAIL;
    if (test_stipple(offby) != PIGLIT_PASS)
         return PIGLIT_FAIL;
    if (test_readpix(offby) != PIGLIT_PASS)
         return PIGLIT_FAIL;
    if (test_teximage(offby) != PIGLIT_PASS)
         return PIGLIT_FAIL;

    assert(glGetError() == GL_NO_ERROR);

    return PIGLIT_PASS;
}

enum piglit_result
piglit_display(void)
{
    GLuint pbo;
    int i;
    enum piglit_result res;

    glClear(GL_COLOR_BUFFER_BIT);

    glGenBuffersARB(1, &pbo);
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pbo);
#define TEST() \
do {\
    res = test(INT_MIN);\
    if (res != PIGLIT_PASS)\
        return res;\
\
    res = test(INT_MIN/2);\
    if (res != PIGLIT_PASS)\
        return res;\
\
    for (i = -9; i <= 1; ++i) {\
        res = test(i);\
        if (res != PIGLIT_PASS)\
            return res;\
    }\
} while(0)

    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);
    TEST();
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pbo);
    TEST();

    glDeleteBuffersARB(1, &pbo);
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);
    glFinish();

    return res;
}

