/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec2(-6.64385618977, -0.570607207744) - log2(vec2(0.01, 0.673333333333))) < 0.001 ? 1 : -1] array0;
float[length(vec2(0.418639735959, 1.0) - log2(vec2(1.33666666667, 2.0))) < 0.001 ? 1 : -1] array1;

main()
{
  gl_Position  = vec4(array0.length()
			+ array1.length());
}
