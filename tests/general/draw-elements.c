/*
 * Copyright © 2010 Marek Olšák <maraeo@gmail.com>
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
 * Authors:
 *    Marek Olšák <maraeo@gmail.com>
 */

/* The test for some tricky bits of the OpenGL vertex submission.
 * The emphasis is taken on non-dword-aligned offsets and various
 * elements formats.
 */

#include "piglit-util.h"

int piglit_width = 320, piglit_height = 60;
int piglit_window_mode = GLUT_RGB | GLUT_DOUBLE;

void piglit_init(int argc, char **argv)
{
    piglit_ortho_projection(piglit_width, piglit_height, GL_FALSE);

    if (!GLEW_VERSION_1_5) {
        printf("Requires OpenGL 1.5\n");
        piglit_report_result(PIGLIT_SKIP);
    }

    glShadeModel(GL_FLAT);
    glClearColor(0.2, 0.2, 0.2, 1.0);
}

static void test_ubyte_indices(float x1, float y1, float x2, float y2, int index)
{
    float v[] = {
        x1, y1,
        x1, y2,
        x2, y1,

        x1, y1,
        x1, y2,
        x2, y1,

        x1, y1,
        x1, y2,
        x2, y1,

        x1, y1,
        x1, y2,
        x2, y1
    };
    unsigned char indx[] = {
        /*aligned:*/ 0, 1, 2, /*unused:*/ 2,
        2, 2, 3, 3,
        3, /* unaligned:*/ 3, 4, 5,
        /*unused:*/ 5, 5, 5, 6,
        6, 6, /*unaligned:*/ 6, 7,
        8, /*unused:*/ 8, 8, 8,
        9, 9, 9, /*unaligned:*/ 9,
        10, 11, /*unused:*/ 11, 11,
        11, 11, 11, 11
    };
    GLuint buf;

    glGenBuffers(1, &buf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indx), indx, GL_STATIC_DRAW);

    glVertexPointer(2, GL_FLOAT, 0, v);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (void*)(intptr_t)(index*9));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &buf);
}

static void test_ushort_indices(float x1, float y1, float x2, float y2, int index)
{
    float v[] = {
        x1, y1,
        x1, y2,
        x2, y1,

        x1, y1,
        x1, y2,
        x2, y1
    };
    unsigned short indx[] = {
        /*aligned:*/ 0, 1,
        2, /*unused:*/ 2,
        2, 2,
        3, 3,
        3, /* unaligned:*/ 3,
        4, 5,
        /*unused:*/ 5, 5,
        5, 5
    };
    GLuint buf;

    glGenBuffers(1, &buf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indx), indx, GL_STATIC_DRAW);

    glVertexPointer(2, GL_FLOAT, 0, v);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)(intptr_t)(index*18));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &buf);
}

static void test_large_index_count(float x1, float y1, float x2, float y2, int index)
{
    float v[] = {
        x1, y1,
        x1, y2,
        x2, y1
    };
    unsigned tris = 100000;
    unsigned *indx = (unsigned*)malloc(sizeof(unsigned) * 3 * tris);
    unsigned i;

    // A large index count for DrawElements
    for (i = 0; i < tris*3; i += 3) {
        indx[i+0] = 0;
        indx[i+1] = 1;
        indx[i+2] = 2;
    }

    glVertexPointer(2, GL_FLOAT, 0, v);
    glDrawElements(GL_TRIANGLES, tris*3, GL_UNSIGNED_INT, indx);

    free(indx);
}

static void test_large_indexbuf_offset(float x1, float y1, float x2, float y2, int index)
{
    float v[] = {
        x1, y1,
        x1, y2,
        x2, y1
    };
    GLuint buf;
    unsigned *map;
    unsigned num = 1000000;

    glGenBuffers(1, &buf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, num*4, 0, GL_STATIC_DRAW);
    map = (unsigned*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    memset(map, 0, num*4);
    map[num-2] = 1;
    map[num-1] = 2;
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

    glVertexPointer(2, GL_FLOAT, 0, v);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(intptr_t)((num-3)*4));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &buf);
}

struct test {
    void (*test)(float x1, float y1, float x2, float y2, int index);
    int index;
    float expected_color[3];
    const char *name;
};

struct test tests[] = {
    {test_ubyte_indices, 0, {1, 1, 1}, "Ubyte indices - offset: 0"},
    {test_ubyte_indices, 1, {1, 1, 1}, "Ubyte indices - offset: 1"},
    {test_ubyte_indices, 2, {1, 1, 1}, "Ubyte indices - offset: 2"},
    {test_ubyte_indices, 3, {1, 1, 1}, "Ubyte indices - offset: 3"},

    {test_ushort_indices, 0, {1, 1, 1}, "Ushort indices - offset: 0"},
    {test_ushort_indices, 1, {1, 1, 1}, "Ushort indices - offset: 2"},

    {test_large_index_count, 1, {1, 1, 1}, "Large index count"},
    {test_large_indexbuf_offset, 0, {1, 1, 1}, "Large index offset"},

    {0}
};

enum piglit_result
piglit_display(void)
{
    GLboolean pass = GL_TRUE;
    unsigned i;
    float x = 0, y = 0;

    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);

    for (i = 0; tests[i].test; i++) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        printf("%s\n", tests[i].name);
        tests[i].test(x, y, x+20, y+20, tests[i].index);
        assert(glGetError() == 0);
        pass = piglit_probe_pixel_rgb(x+5, y+5, tests[i].expected_color) && pass;

        x += 20;
        if (x > 300) {
            x = 0;
            y += 20;
        }
    }

    glFinish();
    glutSwapBuffers();

    return pass ? PIGLIT_SUCCESS : PIGLIT_FAILURE;
}
