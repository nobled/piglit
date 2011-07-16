/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[equal(bvec2(false, false), bvec2(false, true))[0] ? 1 : -1] array0;
float[equal(bvec2(false, false), bvec2(false, true))[1] ? -1 : 1] array1;
float[equal(bvec2(true, true), bvec2(false, true))[0] ? -1 : 1] array2;
float[equal(bvec2(true, true), bvec2(false, true))[1] ? 1 : -1] array3;

main()
{
  gl_FragColor = vec4(array0.length()
                      + array1.length()
                      + array2.length()
                      + array3.length());
}
