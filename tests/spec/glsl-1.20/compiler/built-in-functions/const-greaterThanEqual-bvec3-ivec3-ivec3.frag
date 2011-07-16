/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[all(equal(bvec3(true, false, false), greaterThanEqual(ivec3(1, 1, 1), ivec3(1, 2, 3)))) ? 1 : -1] array0;
float[all(equal(bvec3(false, true, true), greaterThanEqual(ivec3(1, 2, 2), ivec3(4, 1, 2)))) ? 1 : -1] array1;
float[all(equal(bvec3(false, false, true), greaterThanEqual(ivec3(2, 2, 3), ivec3(3, 4, 1)))) ? 1 : -1] array2;
float[all(equal(bvec3(true, true, false), greaterThanEqual(ivec3(3, 3, 3), ivec3(2, 3, 4)))) ? 1 : -1] array3;
float[all(equal(bvec3(true, true, true), greaterThanEqual(ivec3(4, 4, 4), ivec3(1, 2, 3)))) ? 1 : -1] array4;
float[all(equal(bvec3(true, true, false), greaterThanEqual(ivec3(4, 1, 1), ivec3(4, 1, 2)))) ? 1 : -1] array5;

main()
{
  gl_FragColor = vec4(array0.length()
			+ array1.length()
			+ array2.length()
			+ array3.length()
			+ array4.length()
			+ array5.length());
}
