/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[all(equal(bvec4(false, false, false, false), greaterThan(ivec4(1, 1, 1, 1), ivec4(1, 2, 3, 4)))) ? 1 : -1] array0;
float[all(equal(bvec4(true, false, false, false), greaterThan(ivec4(2, 2, 2, 2), ivec4(1, 2, 3, 4)))) ? 1 : -1] array1;
float[all(equal(bvec4(true, true, false, false), greaterThan(ivec4(3, 3, 3, 3), ivec4(1, 2, 3, 4)))) ? 1 : -1] array2;
float[all(equal(bvec4(true, true, true, false), greaterThan(ivec4(4, 4, 4, 4), ivec4(1, 2, 3, 4)))) ? 1 : -1] array3;

main()
{
  gl_FragColor = vec4(array0.length()
			+ array1.length()
			+ array2.length()
			+ array3.length());
}
