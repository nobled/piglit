/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec4(1.81, -0.87, 0.81, 0.65) - transpose(mat4x2(1.81, -1.16, -0.87, -1.52, 0.81, 0.25, 0.65, -1.51))[0]) < 0.001 ? 1 : -1] array0;
float[length(vec4(-1.16, -1.52, 0.25, -1.51) - transpose(mat4x2(1.81, -1.16, -0.87, -1.52, 0.81, 0.25, 0.65, -1.51))[1]) < 0.001 ? 1 : -1] array1;
float[length(vec4(1.93, -1.63, 0.29, 1.6) - transpose(mat4x2(1.93, 0.49, -1.63, 0.27, 0.29, 0.14, 1.6, 0.94))[0]) < 0.001 ? 1 : -1] array2;
float[length(vec4(0.49, 0.27, 0.14, 0.94) - transpose(mat4x2(1.93, 0.49, -1.63, 0.27, 0.29, 0.14, 1.6, 0.94))[1]) < 0.001 ? 1 : -1] array3;

main()
{
  gl_Position  = vec4(array0.length()
			+ array1.length()
			+ array2.length()
			+ array3.length());
}
