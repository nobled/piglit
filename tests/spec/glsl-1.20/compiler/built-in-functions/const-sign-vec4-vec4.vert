/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec4(-1.0, -1.0, 0.0, 1.0) - sign(vec4(-1.5, -0.75, 0.0, 0.75))) < 0.001 ? 1 : -1] array0;
float[length(vec4(1.0, -1.0, -1.0, 0.0) - sign(vec4(1.5, -1.5, -0.75, 0.0))) < 0.001 ? 1 : -1] array1;

main()
{
  gl_Position  = vec4(array0.length()
			+ array1.length());
}
