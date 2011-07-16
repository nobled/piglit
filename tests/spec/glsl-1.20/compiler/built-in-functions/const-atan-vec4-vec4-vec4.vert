/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec4(-2.35619449019, -1.57079632679, -0.785398163397, 3.14159265359) - atan(vec4(-2.0, -2.0, -2.0, 0.0), vec4(-2.0, 0.0, 2.0, -2.0))) < 0.001 ? 1 : -1] array0;
float[length(vec4(0.0, 2.35619449019, 1.57079632679, 0.785398163397) - atan(vec4(0.0, 2.0, 2.0, 2.0), vec4(2.0, -2.0, 0.0, 2.0))) < 0.001 ? 1 : -1] array1;

main()
{
  gl_Position  = vec4(array0.length()
			    + array1.length());
}