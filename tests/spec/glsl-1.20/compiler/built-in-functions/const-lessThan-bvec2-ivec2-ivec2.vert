/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[all(equal(bvec2(false, true), lessThan(ivec2(1, 1), ivec2(1, 2)))) ? 1 : -1] array0;
float[all(equal(bvec2(true, true), lessThan(ivec2(1, 1), ivec2(3, 4)))) ? 1 : -1] array1;
float[all(equal(bvec2(false, false), lessThan(ivec2(2, 2), ivec2(1, 2)))) ? 1 : -1] array2;
float[all(equal(bvec2(true, true), lessThan(ivec2(2, 2), ivec2(3, 4)))) ? 1 : -1] array3;
float[all(equal(bvec2(false, false), lessThan(ivec2(3, 3), ivec2(1, 2)))) ? 1 : -1] array4;
float[all(equal(bvec2(false, true), lessThan(ivec2(3, 3), ivec2(3, 4)))) ? 1 : -1] array5;
float[all(equal(bvec2(false, false), lessThan(ivec2(4, 4), ivec2(1, 2)))) ? 1 : -1] array6;
float[all(equal(bvec2(false, false), lessThan(ivec2(4, 4), ivec2(3, 4)))) ? 1 : -1] array7;

main()
{
  gl_Position  = vec4(array0.length()
                      + array1.length()
                      + array2.length()
                      + array3.length()
                      + array4.length()
                      + array5.length()
                      + array6.length()
                      + array7.length());
}
